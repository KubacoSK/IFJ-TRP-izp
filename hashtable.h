
#include <stdbool.h>
#include <stddef.h>

#define HT_CAPACITY 4093


#ifndef _HASHTABLE_H
#define _HASHTABLE_H

typedef enum { // stavy pre sloty
  HT_SLOT_EMPTY = 0,
  HT_SLOT_OCCUPIED,
  HT_SLOT_DELETE,
}HTslot;
typedef struct { // Struktura pre vytvorenie celej hash tabulky
  char *key; // Kluc, teda nejaky indetifikator my mam djb2 alg.  
  void *value; // hodnota, teda premena co davame do tabulky
  HTslot slot; // v akom stave je slot prazdny, obsadeny, vymazany
}HTitem;

typedef struct { // cela tabulka
  HTitem *items[HT_CAPACITY]; // jeden prvok v tabulke
  int count; // pocitadlo na kolko je tabulka plna
}HashTable;

unsigned long ht_hash(unsigned char *str);
void ht_init(HashTable *table);
#endif