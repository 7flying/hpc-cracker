#include "hasher.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>


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

int main(int argc, char **argv)
{
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
    if (argc != 5) {
        printf("Usage: \n\t%s -h <max num of characters>", argv[0]);
        printf(" -l <min num of characters>\n\t\t-a <alphabet>");
        printf(" -s <secret to crack>\n");
        return 1;
    }
    printf("high: %d, low: %d, alphabet: %s, secret: %s\n", high, low, alph, secret);
    getKeySpace(low, high, alph);
}
