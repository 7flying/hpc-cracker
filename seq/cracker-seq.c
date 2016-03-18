#include "hasher.h"
#include <stdlib.h>



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
