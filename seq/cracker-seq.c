#include "hasher.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int getkeyspace();

void crack
(char *to_crack, unsigned int lower, unsigned int higher, char *alphabet)
{
    unsigned int found = 0;
    int current = 0;
    int keyspace = getkeyspace();
    char *candidate = malloc(sizeof(higher) * (higher + 1));

    for (current = 0; current < keyspace; current++) {
        
    }
    
    free(candidate);
}


int main(int argc, char **argv)
{
    int opt;
    char *alph;
    int high, low;
    while ((opt = getopt(argc, argv, "h:l:a:")) != -1) {
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
        default:
            abort();
        }
    }
    printf("high: %d, low: %d, alphabet: %s\n", high, low, alph);
}
