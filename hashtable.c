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
  for (int i = 0; i < HT_CAPACITY; i++) { // prechadzame cez vsetky podla kapacity
    table->items[i].key = NULL; // nastvanie kluca
    table->items[i].value = NULL; // nastavenie hodnoty
    table->items[i].slot = HT_SLOT_EMPTY; // nastavenie slotu
  }
}

HTitem* ht_search(HashTable *table, unsigned char *key) {
  unsigned long hash = ht_hash(key);
    int ind = hash % HT_CAPACITY;
    int step = (hash % (HT_CAPACITY - 1)) + 1;
    for (int i = 0; i < HT_CAPACITY; i++) {
        if (table->items[ind].slot == HT_SLOT_EMPTY) {
            return NULL;
        }
        if (table->items[ind].slot == HT_SLOT_OCCUPIED && strcmp((char *)table->items[ind].key, (char *)key) == 0) {
            return &table->items[ind];
        }
        ind = (ind + step) % HT_CAPACITY;
    }
    return NULL;
  
}