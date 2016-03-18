#include "hasher.h"

void sha256(char *string, char outputBuffer[65])
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, string, strlen(string));
    SHA256_Final(hash, &sha256);
    int i = 0;
    for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0;
}

int main(int argc, char **argv)
{
    if(argc == 2) {
        static unsigned char buffer[65];
        sha256("string", buffer);
        printf("%s\n", buffer);
    } else {
        printf("You must introduce the string of the word you want to hash as parameter.\n");
        return 1;
    }

    return 0;
}