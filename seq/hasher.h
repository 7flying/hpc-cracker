#ifndef HASHER_H
#define HASHER_H

#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void sha256(char *string, char outputBuffer[65]);

#endif // HASHER_H
