/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file hashtable.c
 */

#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

// hash funkcia 
unsigned long ht_hash(unsigned char* str) {
    unsigned long hash = 5381; // incializacia 5831
    int c = 0;
    while(( c = *str++))

      hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash;
}