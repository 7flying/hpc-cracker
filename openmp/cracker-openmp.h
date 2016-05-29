#ifndef CRACKER_SEQ
#define CRACKER_SEQ


/**
 * get_keyspace - gives the number of possible keys for the given alphabet
 **/ 
unsigned long get_keyspace(unsigned int min, unsigned int max, char *alphabet);

/**
 * next_candidate - leaves the next candidate key on cand for the given alphabet
 * and key size constraints.
 **/
void next_candidate(char *cand, int index, int high, int low, char *alphabet);

/**
 * crack - cracks secrets
 **/
void crack(unsigned int low, unsigned int high, char *alphabet, char *secret);

#endif // CRACKER_SEQ
