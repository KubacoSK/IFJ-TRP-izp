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

// inicializacia hash tabulky
void ht_init(HashTable *table){

  table->count = 0;
  for (int i = 0; i < HT_CAPACITY; i++) { // prechadzame cez vsetky
    table->items[i].key = NULL;
    table->items[i].value = NULL;
    table->items[i].state = HT_SLOT_EMPTY;
  }
}