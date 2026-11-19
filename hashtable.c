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
    table->items[i].state = HT_SLOT_EMPTY; // nastavenie slotu
  }
}

// vyhladanie v tabulke
HTItem* ht_search(HashTable *table, unsigned char *key) {
  unsigned long hash = ht_hash(key); // ziskame hash podla kluca
    int ind = hash % HT_CAPACITY; // pociatocny index h1
    int step = (hash % (HT_CAPACITY - 1)) + 1; // krok na posun pre h2
    for (int i = 0; i < HT_CAPACITY; i++) { // prechadzane tabulku
        if (table->items[ind].state == HT_SLOT_EMPTY) { // ak je slot prazdny, prvok v tabulke nieje
            return NULL; 
        }
        if (table->items[ind].state == HT_SLOT_OCCUPIED && strcmp((char *)table->items[ind].key, (char *)key) == 0) { // ak sme nasli zhodu kluca
            return &table->items[ind]; // vratime najdeny prvok
        }
        ind = (ind + step) % HT_CAPACITY;  // posun na dalsi index podla kroku
    }
    return NULL;
}

// vkladaie do tabulky
bool ht_insert(HashTable *table, unsigned char *key, void *value) {
  HTItem *found = ht_search(table, key); // hladanie ci je prvok uz v tabulke
    if (found != NULL) { // ak existuje len prepiseme hodnotu
        found->value = value;
        return true;
    }
    if (table->count >= HT_CAPACITY) { // kontrola ci nieje tabulka plna
        return false;
    }
    unsigned long hash = ht_hash(key); // ziskame hash podla kluca
    int ind = hash % HT_CAPACITY; // pociatocny index h1
    int step = (hash % (HT_CAPACITY - 1)) + 1; // krok na posun pre h2
    for (int i = 0; i < HT_CAPACITY; i++) { // prechadzanie tabulky
        if (table->items[ind].state == HT_SLOT_EMPTY || table->items[ind].state == HT_SLOT_DELETED) {
            char *kcopy = malloc(strlen((char *)key) + 1);
            if (!kcopy) return false;
            strcpy(kcopy, (char *)key);
            table->items[ind].key = kcopy;
            table->items[ind].value = value;
            table->items[ind].state = HT_SLOT_OCCUPIED;
            table->count++;
            return true;
        }
        ind = (ind + step) % HT_CAPACITY;
    }
    return false; 
}

bool ht_delete(HashTable *table, unsigned char *key) {
  unsigned long hash = ht_hash(key); // ziskame hash podla kluca
    int ind = hash % HT_CAPACITY; // pociatocny index h1
    int step = (hash % (HT_CAPACITY - 1)) + 1; // krok na posun pre h2
    for (int i = 0; i < HT_CAPACITY; i++) { // prechadzanie tabulky

      if (table->items[ind].state == HT_SLOT_EMPTY) { // ak narazime na prazdny slot, prvok v tabulke urcite nie je
        return false;
      }

      if (table->items[ind].state == HT_SLOT_OCCUPIED && strcmp((char *)table->items[ind].key, (char *)key) == 0) {
        table->items[ind].key = NULL;
            table->items[ind].value = NULL;
            table->items[ind].state = HT_SLOT_DELETED;
            table->count--;
            return true;
      }
      ind = (ind + step) % HT_CAPACITY;
    }
    return false;
}    
