#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


/**
 * banner - very useful function
 **/
void banner(char *version);

/**
 * usage - shows usage
 **/
void usage(char *arg);

/**
 * get_keyspace - gives the number of possible keys for the given alphabet
 **/ 
unsigned long get_keyspace(unsigned int min, unsigned int max, char *alphabet);

/**
 * next_candidate - leaves the next candidate key on cand for the given alphabet
 * and key size constraints.
 **/
void next_candidate(char *cand, int index, int high, int low, char *alphabet);


#endif // COMMON_H
