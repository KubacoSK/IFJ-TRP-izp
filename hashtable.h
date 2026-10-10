/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file hashtable.h
 * @brief Rozhranie pre rozptylovaciu tabulku s otvorenou adresaciou (TRP-izp).
 */

#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <stddef.h>
#include <stdbool.h>

//Fixna kapacita tabulky

#define HT_CAPACITY 2039

//Stav slotu v tabulke

typedef enum {
    HT_SLOT_EMPTY = 0,      // Prazdny slot
    HT_SLOT_OCCUPIED,       // Obsadeny slot s aktivnym klucom a hodnotou
    HT_SLOT_DELETED         // Zmazany slot
} HTSlotState;

typedef struct {
    char *key;              // Dynamicky alokovany retazec kluca
    void *value;            // Ukazovatel na lubovolne data
    HTSlotState state;      // Stav slotu
} HTItem;

typedef struct {
    HTItem items[HT_CAPACITY];
    size_t count;           // Pocet aktivnych obsadenych prvkov
} HashTable;

// Vypocita hash pre dany kluc (algoritmus djb2)

size_t ht_hash(const char *key);

// Inicializuje tabulku do prazdneho stavu
void ht_init(HashTable *table);

// Vyhlada polozku s danym klucom v tabulke

HTItem *ht_search(const HashTable *table, const char *key);

// Vlozi dvojicu kluc-hodnota do tabulky.

bool ht_insert(HashTable *table, const char *key, void *value);

// Zmaze polozku s danym klucom z tabulky.

bool ht_delete(HashTable *table, const char *key);

// Vymaze vsetky polozky z tabulky a uvolni kluce.

void ht_clear(HashTable *table, void (*free_val)(void *));

#endif // _HASHTABLE_H
