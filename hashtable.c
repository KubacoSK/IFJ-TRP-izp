/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file hashtable.c
 * @brief Implementacia rozptylovacej tabulky s otvorenou adresaciou (TRP-izp).
 */

#include "hashtable.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

// Hashovacia funkcia djb2
size_t ht_hash(const char *key) {
  size_t hash = 5381;
  int c;
  while ((c = (unsigned char)*key++)) {
    hash = ((hash << 5) + hash) + (size_t)c; /* hash * 33 + c */
  }
  return hash;
}

void ht_init(HashTable *table) {
  if (!table)
    return;
  table->count = 0;
  for (size_t i = 0; i < HT_CAPACITY; i++) {
    table->items[i].key = NULL;
    table->items[i].value = NULL;
    table->items[i].state = HT_SLOT_EMPTY;
  }
}

HTItem *ht_search(const HashTable *table, const char *key) {
  if (!table || !key)
    return NULL;

  size_t start_idx = ht_hash(key) % HT_CAPACITY;

  for (size_t step = 0; step < HT_CAPACITY; step++) {
    size_t idx = (start_idx + step) % HT_CAPACITY;

    // Ak je slot prazdny, kluc sa v tomto retazci nenachadza
    if (table->items[idx].state == HT_SLOT_EMPTY) {
      return NULL;
    }

    // Ak je slot obsadeny, skontrolujeme zhodu kluca
    if (table->items[idx].state == HT_SLOT_OCCUPIED) {
      if (strcmp(table->items[idx].key, key) == 0) {
        return (HTItem *)&table->items[idx];
      }
    }
    // Ak je stav HT_SLOT_DELETED, pokracujeme v linearnom preberani
  }

  return NULL;
}

bool ht_insert(HashTable *table, const char *key, void *value) {
  if (!table || !key)
    return false;

  // Najprv skontrolujeme, ci kluc uz existuje, a aktualizujeme hodnotu
  HTItem *existing = ht_search(table, key);
  if (existing) {
    existing->value = value;
    return true;
  }

  // Kontrola zaplnenia tabulky
  if (table->count >= HT_CAPACITY) {
    return false;
  }

  size_t start_idx = ht_hash(key) % HT_CAPACITY;

  // Linearne preberanie pre najdenie prveho volneho slotu (EMPTY alebo DELETED)
  for (size_t step = 0; step < HT_CAPACITY; step++) {
    size_t idx = (start_idx + step) % HT_CAPACITY;

    if (table->items[idx].state == HT_SLOT_EMPTY ||
        table->items[idx].state == HT_SLOT_DELETED) {
      char *kcopy = str_dup(key);
      if (!kcopy)
        return false;

      table->items[idx].key = kcopy;
      table->items[idx].value = value;
      table->items[idx].state = HT_SLOT_OCCUPIED;
      table->count++;
      return true;
    }
  }

  return false;
}

bool ht_delete(HashTable *table, const char *key) {
  if (!table || !key)
    return false;

  size_t start_idx = ht_hash(key) % HT_CAPACITY;

  for (size_t step = 0; step < HT_CAPACITY; step++) {
    size_t idx = (start_idx + step) % HT_CAPACITY;

    if (table->items[idx].state == HT_SLOT_EMPTY) {
      return false;
    }

    if (table->items[idx].state == HT_SLOT_OCCUPIED) {
      if (strcmp(table->items[idx].key, key) == 0) {
        free(table->items[idx].key);
        table->items[idx].key = NULL;
        table->items[idx].value = NULL;
        table->items[idx].state = HT_SLOT_DELETED; // Oznacenie hrobceka
        table->count--;
        return true;
      }
    }
  }

  return false;
}

void ht_clear(HashTable *table, void (*free_val)(void *)) {
  if (!table)
    return;

  for (size_t i = 0; i < HT_CAPACITY; i++) {
    if (table->items[i].state == HT_SLOT_OCCUPIED) {
      if (table->items[i].key) {
        free(table->items[i].key);
        table->items[i].key = NULL;
      }
      if (free_val && table->items[i].value) {
        free_val(table->items[i].value);
      }
      table->items[i].value = NULL;
    }
    table->items[i].state = HT_SLOT_EMPTY;
  }
  table->count = 0;
}
