/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file test_hashtable.c
 * @brief Unit testy pre rozptylovaciu tabulku s otvorenou adresaciou (TRP-izp).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "../hashtable.h"

#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED   "\033[0;31m"
#define COLOR_BLUE  "\033[0;34m"
#define COLOR_RESET "\033[0m"

static int total_tests = 0;
static int passed_tests = 0;
static int failed_tests = 0;

#define TEST_ASSERT(cond, name) do { \
    total_tests++; \
    if (cond) { \
        printf("  " COLOR_GREEN "[PASS]" COLOR_RESET " %s\n", name); \
        passed_tests++; \
    } else { \
        printf("  " COLOR_RED "[FAIL]" COLOR_RESET " %s\n", name); \
        failed_tests++; \
    } \
} while (0)

static void test_init(void) {
    printf("--- Test: Inicializacia ---\n");
    HashTable ht;
    ht_init(&ht);
    TEST_ASSERT(ht.count == 0, "ht_init nastavi count na 0");
    bool all_empty = true;
    for (size_t i = 0; i < HT_CAPACITY; i++) {
        if (ht.items[i].state != HT_SLOT_EMPTY || ht.items[i].key != NULL) {
            all_empty = false;
            break;
        }
    }
    TEST_ASSERT(all_empty, "Vsetky sloty su inicializovane na HT_SLOT_EMPTY");
}

static void test_insert_search(void) {
    printf("\n--- Test: Zakladne vkladanie a vyhladavanie ---\n");
    HashTable ht;
    ht_init(&ht);

    int val1 = 42;
    int val2 = 100;
    bool ins1 = ht_insert(&ht, "myVar", &val1);
    bool ins2 = ht_insert(&ht, "myFunc", &val2);

    TEST_ASSERT(ins1 && ins2, "Vlozenie novych klucov vrati true");
    TEST_ASSERT(ht.count == 2, "Pocet prvkov sa zvysi na 2");

    HTItem *item1 = ht_search(&ht, "myVar");
    TEST_ASSERT(item1 != NULL && item1->value == &val1, "Vyhladanie 'myVar' najde spravnu hodnotu");

    HTItem *item2 = ht_search(&ht, "myFunc");
    TEST_ASSERT(item2 != NULL && item2->value == &val2, "Vyhladanie 'myFunc' najde spravnu hodnotu");

    HTItem *item_missing = ht_search(&ht, "nonExistent");
    TEST_ASSERT(item_missing == NULL, "Vyhladanie neexistujuceho kluca vrati NULL");

    ht_clear(&ht, NULL);
}

static void test_update_duplicate(void) {
    printf("\n--- Test: Aktualizacia pri existujucom kluci ---\n");
    HashTable ht;
    ht_init(&ht);

    int val1 = 10;
    int val2 = 20;

    ht_insert(&ht, "counter", &val1);
    TEST_ASSERT(ht.count == 1, "Pocet prvkov je 1 po prvom vlozeni");

    ht_insert(&ht, "counter", &val2);
    TEST_ASSERT(ht.count == 1, "Pocet prvkov zostava 1 po vlozeni duplicitneho kluca");

    HTItem *item = ht_search(&ht, "counter");
    TEST_ASSERT(item != NULL && item->value == &val2, "Hodnota bola aktualizovana na novy ukazovatel");

    ht_clear(&ht, NULL);
}

static void test_delete_and_tombstone(void) {
    printf("\n--- Test: Mazanie a hrobceky v otvorenej adresacii ---\n");
    HashTable ht;
    ht_init(&ht);

    int v1 = 1, v2 = 2, v3 = 3;
    ht_insert(&ht, "alpha", &v1);
    ht_insert(&ht, "beta", &v2);
    ht_insert(&ht, "gamma", &v3);

    TEST_ASSERT(ht_delete(&ht, "beta"), "ht_delete vrati true pri zmazani existujuceho kluca");
    TEST_ASSERT(ht.count == 2, "Pocet prvkov klesne po zmazani");
    TEST_ASSERT(ht_search(&ht, "beta") == NULL, "Zmazany kluc sa uz nenajde");

    // Kluce pred a za zmazanym sa musia stale najst
    TEST_ASSERT(ht_search(&ht, "alpha") != NULL, "Kluc 'alpha' sa stale najde aj po zmazani 'beta'");
    TEST_ASSERT(ht_search(&ht, "gamma") != NULL, "Kluc 'gamma' sa stale najde aj po zmazani 'beta'");

    // Opatovne vlozenie zmazaneho kluca
    int v4 = 4;
    TEST_ASSERT(ht_insert(&ht, "beta", &v4), "Opatovne vlozenie zmazaneho kluca uspeje");
    TEST_ASSERT(ht.count == 3, "Pocet prvkov je znova 3");
    HTItem *item = ht_search(&ht, "beta");
    TEST_ASSERT(item != NULL && item->value == &v4, "Vyhladanie najde znovu vlozeny kluc s novou hodnotou");

    // Zmazanie neexistujuceho kluca
    TEST_ASSERT(!ht_delete(&ht, "ghost"), "Mazanie neexistujuceho kluca vrati false");

    ht_clear(&ht, NULL);
}

static void test_collisions(void) {
    printf("\n--- Test: Kolicie a linearne preberanie ---\n");
    HashTable ht;
    ht_init(&ht);

    // Vlozenie 50 premennych
    char keys[50][16];
    int values[50];
    for (int i = 0; i < 50; i++) {
        snprintf(keys[i], sizeof(keys[i]), "var_%d", i);
        values[i] = i * 7;
        ht_insert(&ht, keys[i], &values[i]);
    }

    TEST_ASSERT(ht.count == 50, "Uspesne vlozenych 50 prvkov");

    bool all_found = true;
    for (int i = 0; i < 50; i++) {
        HTItem *item = ht_search(&ht, keys[i]);
        if (!item || item->value != &values[i]) {
            all_found = false;
            break;
        }
    }
    TEST_ASSERT(all_found, "Vsetkych 50 prvkov sa spravne naslo aj pri koliciach");

    // Zmazanie kazdeho druheho kluca
    for (int i = 0; i < 50; i += 2) {
        ht_delete(&ht, keys[i]);
    }
    TEST_ASSERT(ht.count == 25, "Pocet prvkov je 25 po zmazani 25 klucov");

    // Zvysne neparne kluce sa musia najst cez hrobceky
    bool odd_found = true;
    for (int i = 1; i < 50; i += 2) {
        HTItem *item = ht_search(&ht, keys[i]);
        if (!item || item->value != &values[i]) {
            odd_found = false;
            break;
        }
    }
    TEST_ASSERT(odd_found, "Zvysne prvky sa nasli cez zmazane hrobceky");

    ht_clear(&ht, NULL);
}

static void test_clear(void) {
    printf("\n--- Test: Vycistenie tabulky ---\n");
    HashTable ht;
    ht_init(&ht);

    int val = 99;
    ht_insert(&ht, "x", &val);
    ht_insert(&ht, "y", &val);
    ht_insert(&ht, "z", &val);

    ht_clear(&ht, NULL);
    TEST_ASSERT(ht.count == 0, "ht_clear resetuje count na 0");
    TEST_ASSERT(ht_search(&ht, "x") == NULL, "Kluce sa po vycisteni nenajdu");

    // Tabulka je po vycisteni znovu pouzitelna
    ht_insert(&ht, "w", &val);
    TEST_ASSERT(ht.count == 1 && ht_search(&ht, "w") != NULL, "Tabulka je pouzitelna po vycisteni");

    ht_clear(&ht, NULL);
}

int main(void) {
    printf(COLOR_BLUE "========================================================\n" COLOR_RESET);
    printf(COLOR_BLUE "       TRP-izp TESTOVACIA SADA ROZPTYLOVACEJ TABULKY    \n" COLOR_RESET);
    printf(COLOR_BLUE "========================================================\n\n" COLOR_RESET);

    test_init();
    test_insert_search();
    test_update_duplicate();
    test_delete_and_tombstone();
    test_collisions();
    test_clear();

    printf("\n" COLOR_BLUE "========================================================\n" COLOR_RESET);
    printf("CELKOVO TESTOV: %d\n", total_tests);
    printf("USPESNYCH:      %d\n", passed_tests);
    printf("NEUSPESNYCH:    %d\n", failed_tests);
    if (failed_tests == 0) {
        printf(COLOR_GREEN "VSETKY TESTY TABULKY PRESLI!\n" COLOR_RESET);
    } else {
        printf(COLOR_RED "NIEKTORE TESTY ZLYHALI!\n" COLOR_RESET);
    }
    printf(COLOR_BLUE "========================================================\n" COLOR_RESET);

    return (failed_tests == 0) ? 0 : 1;
}
