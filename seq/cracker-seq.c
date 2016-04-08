#include "hasher.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>



unsigned long getKeySpace(unsigned int min, unsigned int max, char *alphabet)
{
	unsigned int i, alphabetlen = strlen(alphabet);
	unsigned long size = 0;
	for(i = max; i > min; i--) {
		size += (unsigned long) pow(alphabetlen, i);
	}

	printf("Keyspace size: %lu\n", size);

	return size;
}

void crack(unsigned int lower, unsigned int higher, char *alphabet)
{
    unsigned int found = 0;
    int current = 0;
    double keyspace = getKeySpace(lower, higher, alphabet);
    char *candidate = malloc(sizeof(higher) * (higher + 1));

    for (current = 0; current < keyspace; current++) {
        
    }
    
    free(candidate);
}

int main(int argc, char *argv[]) {
	crack(4, 8, "012345678");

	return 0;
}