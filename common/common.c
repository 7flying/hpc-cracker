#include "common.h"


void banner(char *version)
{
    printf("  _                              _\n");
    printf(" | |_ ___ ___    ___ ___ ___ ___| |_ ___ ___ \n");
    printf(" |   | . |  _|  |  _|  _| .'|  _| '_| -_|  _|\n");
    printf(" |_|_|  _|___|  |___|_| |__,|___|_,_|___|_|  \n");
    printf("     |_|\n");
    printf("             ~ powered by %s\n\n", version);
}

void usage(char *arg)
{
    printf("\n Usage: \n %s -h <max num of characters>", arg);
    printf(" -l <min num of characters>\n               -a <alphabet>");
    printf(" -s <secret to crack>\n");
}

unsigned long get_keyspace(unsigned int min, unsigned int max, char *alphabet)
{
	unsigned int i, alphabetlen = strlen(alphabet);
	unsigned long size = 0;
	for (i = max; i > min; i--)
		size += (unsigned long) pow(alphabetlen, i);
	return size;
}

void next_candidate(char *cand, int index, int high, int low, char *alphabet)
{
    int size = low;
    int indexs = index;
    int long_alf = strlen(alphabet);

    while(pow(long_alf, size) < indexs) {
        indexs -= pow(long_alf, size);
        size++;
    }
    char *caracters = malloc(size + 1);
    int i;
    for (i = 0; i < size; i++) {
        caracters[i] = alphabet[0];
    }
    caracters[size] = '\0';
    i = 0;

    while (indexs % long_alf != 0) {
        caracters[i] = alphabet[indexs % long_alf];
        i++;
        indexs /= long_alf;
    }
    strcpy(cand, caracters);
    free(caracters);
}
