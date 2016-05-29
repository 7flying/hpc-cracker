#ifndef HASHER_H
#define HASHER_H

#include <openssl/sha.h>
#include <string.h>
#include <stdio.h>


void sha256(char *string, char output[65]);

#endif // HASHER_H
