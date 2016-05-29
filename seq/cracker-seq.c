#include "../hasher/hasher.h"
#include "../common/common.h"
#include "cracker-seq.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void crack(unsigned int low, unsigned int high, char *alphabet, char *secret)
{
    int found = 0, current = 0;
    char hash[65];
    unsigned long keyspace = get_keyspace(low, high, alphabet);
    char *candidate = malloc(sizeof(high) * (high + 1));
    
    for (current = 0; ((unsigned) current < keyspace) && !found; current++) {
        next_candidate(candidate, current, high, low, alphabet);
        sha256(candidate, hash);
        if (strncmp(secret, hash, 64) == 0)
            found = 1;
    }
    if (found) {
        printf("\n The hash matches '%s'\n", candidate);
    } else {
        printf("\n We could not crack the hash.\n");
    }
    free(candidate);
}

int main(int argc, char **argv)
{
    banner("bruteforce");
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
            abort();
        }
    }
    if (argc != 9 || high < low) {
        usage(argv[0]);
        return 1;
    }
    crack(low, high, alph, secret);
    return 0;
}
