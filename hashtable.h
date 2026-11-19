/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 * Autori:
 * @author xodrasa00, Aleš Odráška
 * @author xgazdaa00, Adam Gazdarica
 * @author xkrpeld00, Dominik Krpelan
 * @author xpetraj00, Jakub Petrán
 * @file hashtable.h
 * @brief Implementacia hashovacej tabulky.
 */

#include <stdbool.h>
#include <stddef.h>

#define HT_CAPACITY 4093

#ifndef _HASHTABLE_H
#define _HASHTABLE_H

typedef enum { // stavy pre sloty
  HT_SLOT_EMPTY = 0,
  HT_SLOT_OCCUPIED,
  HT_SLOT_DELETED,
} HTslot;
typedef struct { // Struktura pre vytvorenie celej hash tabulky
  char *key;     // Kluc, teda nejaky indetifikator my mam djb2 alg.
  void *value;   // hodnota, teda premena co davame do tabulky
  HTslot state;  // v akom stave je slot prazdny, obsadeny, vymazany
} HTItem;

typedef struct {             // cela tabulka
  HTItem items[HT_CAPACITY]; // jeden prvok v tabulke
  int count;                 // pocitadlo na kolko je tabulka plna
} HashTable;

typedef void (*free_func_t)(void *); // funkcia na uvolnenie hodnoty

unsigned long ht_hash(unsigned char *str);
void ht_init(HashTable *table);
HTItem *ht_search(HashTable *table, unsigned char *key);
bool ht_insert(HashTable *table, unsigned char *key, void *value);
bool ht_delete(HashTable *table, unsigned char *key);
void ht_clear(HashTable *table, free_func_t free_val);
#endif