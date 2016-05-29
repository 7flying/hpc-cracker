#include "../hasher/hasher.h"
#include "../common/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

#define CHUNK 50
#define DEBUG 0


int main(int argc, char **argv)
{
    char OK = 'o', ERROR = 'e', MORE_KEYS = 'k', KEY_FOUND = 'f';
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    // parse all the arguments by all threads
    int opt;
    char *alph;
    char *secret;
    int high, low;
    while ((opt = getopt(argc, argv, "h:l:a:s:")) != -1) {
        switch (opt) {
        case 'h':
            high = atoi(optarg);
            break;
        case 'l':
            low = atoi(optarg);
            break;
        case 'a':
            alph = optarg;
            break;
        case 's':
            secret = optarg;
            break;
        default:
            usage(argv[0]);
        }
    }
    if (rank == 0) {
        banner("MPI");
        if (argc != 9 || high < low) {
            usage(argv[0]);
        } else {
            unsigned long keyspace = get_keyspace(low, high, alph);
            unsigned long last_key = 0;
            int num_finished = 0;
            int found = 0;
            char buf;
            MPI_Status status;
            if (DEBUG) {
                printf("\n [M] SIZE: %d\n", size);
                printf("\n [M] wait until %d", size -1);
            }
            while (num_finished != (size -1)) {
                if (DEBUG)
                    printf("\n [M] num finished %d\n", num_finished);
                // listen for request
                // if request = k -> wants keys
                //    send keys if we have and not found, else send ok and num_finished++
                //    (when keys tag = 0 -> unsigned long, else tag = 1 -> int)
                // else if request = f -> has found the key
                //    found = 1, send 'o'(k) as a confirmation
                // else send message not understood (tag = 2, mesage = 'e', type char)
                MPI_Recv(&buf, 1, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG,
                         MPI_COMM_WORLD, &status);
                if (buf == MORE_KEYS) {
                    if (last_key < keyspace && !found) {
                        MPI_Send(&last_key, 1, MPI_UNSIGNED_LONG,
                                 status.MPI_SOURCE, 0, MPI_COMM_WORLD);
                        if (DEBUG) {
                            printf(" [M] Master got MORE_KEYS, from %d, sending KEY %lu\n",
                                   status.MPI_SOURCE, last_key);
                        }
                        last_key += CHUNK;
                    } else {
                        MPI_Send(&OK, 1, MPI_CHAR, status.MPI_SOURCE, 2,
                                 MPI_COMM_WORLD);
                        num_finished++;
                        if (DEBUG) {
                            printf(" [M] Master got MORE_KEYS, from %d, sending QUIT\n",
                                   status.MPI_SOURCE);
                        }
                    }
                } else if (buf == KEY_FOUND) {
                    found = 1;
                    num_finished++;
                    MPI_Send(&OK, 1, MPI_CHAR, status.MPI_SOURCE, 2,
                             MPI_COMM_WORLD);
                    if (DEBUG) {
                        printf(" [M] Master got KEY_FOUND, from %d, sending QUIT\n",
                               status.MPI_SOURCE);
                    }
                } else {
                    MPI_Send(&ERROR, 1, MPI_CHAR, status.MPI_SOURCE, 3,
                             MPI_COMM_WORLD);
                    if (DEBUG) {
                        printf(" [M] Master got UNKNOWN, from %d, sending ERROR\n",
                               status.MPI_SOURCE);
                    }
                }
            }
            if (DEBUG)
                printf("\n [M] MASTER QUITS \n");
            if (!found)
                printf(" We could not crack the hash.\n");
        }
    } else {
        if (argc == 9 && high >= low) {
            // the workers can work
            unsigned long keyspace = get_keyspace(low, high, alph);
            char *candidate = malloc(sizeof(high) * (high +1));
            char hash[65];
            int w_found = 0;
            // request keys
            // if we receive -1 finish thread
            // else process
            //      if found, send F to master, print result and finish
            //      else goto ini
            int finished = 0;
            while (!finished) {
                unsigned long from = -1;
                MPI_Send(&MORE_KEYS, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
                if (DEBUG)
                    printf(" [%d] request MORE_KEYS\n", rank);
                MPI_Status status;
                MPI_Recv(&from, 1, MPI_UNSIGNED_LONG, 0, MPI_ANY_TAG,
                         MPI_COMM_WORLD, &status);
                // check tag (0: unsigned log, 1: no more keys,
                // 2: ok confirmation, finish, 3: error, retry message
                unsigned long init = from;
                switch (status.MPI_TAG) {
                case 0:
                    if (DEBUG) {
                        printf(" [%d] processing from %lu to %lu\n", rank,
                           from, init + CHUNK);
                    }
                    // we got more keys
                    for (from; from < init + CHUNK && !w_found && (from < keyspace); from++) {
                        next_candidate(candidate, from, high, low, alph);
                        sha256(candidate, hash);
                        if (strncmp(secret, hash, 64) == 0)
                            w_found = 1;
                    }
                    if (w_found) {
                        if (DEBUG) {
                            printf(" [%d] The hash matches '%s'\n", rank,
                                   candidate);
                        } else {
                            printf(" The hash matches '%s'\n", candidate);
                        }
                        MPI_Send(&KEY_FOUND, 1, MPI_CHAR, 0, 0,
                                 MPI_COMM_WORLD);
                        char end = 'e';
                        MPI_Recv(&from, 1, MPI_CHAR, 0, MPI_ANY_TAG,
                                 MPI_COMM_WORLD, &status);
                        finished = 1;
                        if (DEBUG)
                            printf(" [%d] quiting\n", rank);
                    }
                    break;
                case 2:
                    // no more keys
                    finished = 1;
                    if (DEBUG)
                        printf(" [%d] quiting\n", rank);
                    break;
                case 3:
                    // there was an error, continue to next loop
                    if (DEBUG)
                        printf(" [%d] There was an error\n", rank);
                    break;
                default:
                    // the master is crazy, continue to next loop
                    if (DEBUG)
                        printf(" [%d] The master is crazy\n", rank);
                    break;
                }
            }
            free(candidate);
        }
    }
    
    MPI_Finalize();
    return 0;
}
