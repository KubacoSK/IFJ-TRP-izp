/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file test_symtable.c
 * @brief Unit testy pre tabulku symbolov (Symtable).
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../symtable.h"

#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED "\033[0;31m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_RESET "\033[0m"

static int total_tests = 0;
static int passed_tests = 0;
static int failed_tests = 0;

#define TEST_ASSERT(cond, name)                                                \
  do {                                                                         \
    total_tests++;                                                             \
    if (cond) {                                                                \
      printf("  " COLOR_GREEN "[PASS]" COLOR_RESET " %s\n", name);             \
      passed_tests++;                                                          \
    } else {                                                                   \
      printf("  " COLOR_RED "[FAIL]" COLOR_RESET " %s\n", name);               \
      failed_tests++;                                                          \
    }                                                                          \
  } while (0)

// AI (Claude Code, Claude Opus 5.5)
// Prompt: "Uprav tabulku symbolov na 100 % skryty (opaque) ADT: ...
// symtable_init nahrad symtable_create, uprav main.c a test_symtable.c."
// (vsetky testy v subore pouzivaju Symtable * zo symtable_create)
// Test inicializacie tabulky symbolov
static void test_init_table(void) {
  printf("--- Test: Inicializacia tabulky symbolov ---\n");
  Symtable *st = symtable_create();

  TEST_ASSERT(symtable_add_var(st, "x", TYPE_INT, true, true) == NULL,
              "Pociatocny lokalny ramec neexistuje (premennu nemozno pridat)");
  TEST_ASSERT(symtable_find_func(st, "foo") == NULL,
              "Prazdna tabulka neobsahuje ziadne funkcie");

  symtable_free(st);
}

// Test prace s funkciami v globalnej tabulke
static void test_functions(void) {
  printf("\n--- Test: Funkcie v globalnej tabulke ---\n");
  Symtable *st = symtable_create();

  Param params[] = {{"a", TYPE_INT}, {"b", TYPE_INT}};
  Symbol *f_add =
      symtable_add_func(st, "add", TYPE_INT, 2, params, true, false);
  TEST_ASSERT(f_add != NULL, "Pridanie funkcie 'add(a: Int, b: Int): Int'");

  Symbol *found = symtable_find_func(st, "add");
  TEST_ASSERT(
      found != NULL && found->data.func.param_count == 2 &&
          found->data.func.return_type == TYPE_INT,
      "Vyhladanie funkcie 'add' najde spravne parametre a navratovy typ");
  TEST_ASSERT(strcmp(found->data.func.params[0].name, "a") == 0 &&
                  found->data.func.params[0].type == TYPE_INT,
              "Prvy parameter funkcie 'a: Int'");
  TEST_ASSERT(strcmp(found->data.func.params[1].name, "b") == 0 &&
                  found->data.func.params[1].type == TYPE_INT,
              "Druhy parameter funkcie 'b: Int'");

  // Funkcia bez parametrov
  Symbol *f_void =
      symtable_add_func(st, "run", TYPE_UNIT, 0, NULL, true, false);
  TEST_ASSERT(f_void != NULL && f_void->data.func.param_count == 0 &&
                  f_void->data.func.return_type == TYPE_UNIT,
              "Pridanie funkcie bez parametrov 'run(): Unit'");

  Symbol *f_missing = symtable_find_func(st, "neexistujuca");
  TEST_ASSERT(f_missing == NULL, "Vyhladanie neexistujucej funkcie vrati NULL");

  symtable_free(st);
}

// Test spravy premennych a ramcov (scopov)
static void test_variables_and_scopes(void) {
  printf("\n--- Test: Premenne a ramce (scopy) ---\n");
  Symtable *st = symtable_create();

  // Otvorenie urovne funkcie
  TEST_ASSERT(symtable_push_scope(st),
              "Otvorenie lokalneho ramca (push scope)");

  Symbol *v1 = symtable_add_var(st, "x", TYPE_INT, true, true);
  Symbol *v2 = symtable_add_var(st, "msg", TYPE_STRING, false, true);
  TEST_ASSERT(v1 != NULL && v2 != NULL,
              "Pridanie premennych x (val) a msg (var)");

  Symbol *fx = symtable_find_var(st, "x");
  TEST_ASSERT(fx != NULL && fx->data.var.type == TYPE_INT &&
                  fx->data.var.is_constant == true,
              "Vyhladanie x (val Int)");

  Symbol *fmsg = symtable_find_var(st, "msg");
  TEST_ASSERT(fmsg != NULL && fmsg->data.var.type == TYPE_STRING &&
                  fmsg->data.var.is_constant == false,
              "Vyhladanie msg (var String)");

  // Vnoreny blok (napr. vetva if)
  symtable_push_scope(st);
  Symbol *v_inner =
      symtable_add_var(st, "x", TYPE_DOUBLE, false, true); // Zatienenie x
  TEST_ASSERT(v_inner != NULL,
              "Zatienenie premennej x vo vnutornom bloku (var Double)");

  Symbol *f_shadowed = symtable_find_var(st, "x");
  TEST_ASSERT(
      f_shadowed != NULL && f_shadowed->data.var.type == TYPE_DOUBLE &&
          f_shadowed->data.var.is_constant == false,
      "Vyhladanie x vo vnutornom bloku vrati zatienenu Double premennu");

  Symbol *f_outer_visible = symtable_find_var(st, "msg");
  TEST_ASSERT(f_outer_visible != NULL &&
                  f_outer_visible->data.var.type == TYPE_STRING,
              "Vonkajsia premenna msg je stale viditelna vo vnutornom bloku");

  // Detekcia redefinicie v rovnakom bloku
  TEST_ASSERT(symtable_find_var_current_scope(st, "x") != NULL,
              "find_var_current_scope deteguje premennu v aktualnom bloku");
  TEST_ASSERT(symtable_find_var_current_scope(st, "msg") == NULL,
              "find_var_current_scope nevidi premennu z vonkajsieho bloku");

  // Opustenie vnutorneho bloku
  symtable_pop_scope(st);

  Symbol *f_restored = symtable_find_var(st, "x");
  TEST_ASSERT(f_restored != NULL && f_restored->data.var.type == TYPE_INT &&
                  f_restored->data.var.is_constant == true,
              "Po opusteni vnutorneho bloku sa x vrati na povodny val Int");

  // Opustenie urovne funkcie
  symtable_pop_scope(st);
  TEST_ASSERT(symtable_find_var(st, "x") == NULL,
              "Po ukonceni funkcie nie su premenne viditelne");

  symtable_free(st);
}

// AI (Claude Code, Claude Opus 5.5)
// Prompt: "Doplnit testy na jedinecne ID premennej (VarData.id): start
// pocitadla, jedinecnost v rozsahu, zatienenie, surodenecke rozsahy a ID
// vratene pri vyhladani."
// Test jedinecneho ID premennej (premenovanie x -> x$id v generatore)
static void test_variable_ids(void) {
  printf("\n--- Test: Jedinecne ID premennych ---\n");
  Symtable *st = symtable_create();
  symtable_push_scope(st);

  Symbol *a = symtable_add_var(st, "a", TYPE_INT, true, true);
  Symbol *b = symtable_add_var(st, "b", TYPE_INT, true, true);
  TEST_ASSERT(a != NULL && a->data.var.id == 1,
              "Prva premenna po inicializacii ma ID 1");
  TEST_ASSERT(b != NULL && b->data.var.id != a->data.var.id,
              "Dve premenne v jednom rozsahu maju rozne ID");

  // Zatienenie: rovnake meno vo vnorenom rozsahu
  Symbol *x_outer = symtable_add_var(st, "x", TYPE_INT, true, true);
  symtable_push_scope(st);
  Symbol *x_then = symtable_add_var(st, "x", TYPE_STRING, true, true);
  TEST_ASSERT(x_outer != NULL && x_then != NULL &&
                  x_then->data.var.id != x_outer->data.var.id,
              "Zatienene x ma ine ID ako vonkajsie x");

  Symbol *found = symtable_find_var(st, "x");
  TEST_ASSERT(found != NULL && found->data.var.id == x_then->data.var.id,
              "Vyhladanie x vo vnutornom rozsahu vrati ID zatienenej x");

  // ID sa ulozi, pop_scope symbol x_then uvolni
  unsigned then_id = x_then ? x_then->data.var.id : 0;

  // Surodenecke rozsahy (vetvy then/else) maju rovnaku hlbku
  symtable_pop_scope(st);
  symtable_push_scope(st);
  Symbol *x_else = symtable_add_var(st, "x", TYPE_STRING, true, true);
  TEST_ASSERT(x_else != NULL && x_else->data.var.id != x_outer->data.var.id,
              "x v druhom surodeneckom rozsahu ma ine ID ako vonkajsie x");
  TEST_ASSERT(x_else != NULL && x_else->data.var.id != then_id,
              "x v surodeneckych rozsahoch (then/else) maju rozne ID");
  symtable_pop_scope(st);

  found = symtable_find_var(st, "x");
  TEST_ASSERT(found != NULL && found->data.var.id == x_outer->data.var.id,
              "Po opusteni rozsahu vyhladanie x vrati ID vonkajsej x");

  symtable_pop_scope(st);
  symtable_free(st);

  // nova tabulka zacina pocitadlo znova od 1
  st = symtable_create();
  symtable_push_scope(st);
  Symbol *c = symtable_add_var(st, "c", TYPE_INT, true, true);
  TEST_ASSERT(c != NULL && c->data.var.id == 1,
              "Po novej inicializacii zacina ID znova od 1");
  symtable_pop_scope(st);
  symtable_free(st);
}

int main(void) {
  printf(
      COLOR_BLUE
      "========================================================\n" COLOR_RESET);
  printf(
      COLOR_BLUE
      "       IFJ26 TESTOVACIA SADA PRE TABULKU SYMBOLOV       \n" COLOR_RESET);
  printf(COLOR_BLUE "========================================================"
                    "\n\n" COLOR_RESET);

  test_init_table();
  test_functions();
  test_variables_and_scopes();
  test_variable_ids();

  printf(
      "\n" COLOR_BLUE
      "========================================================\n" COLOR_RESET);
  printf("CELKOVO TESTOV: %d\n", total_tests);
  printf("USPESNYCH:      %d\n", passed_tests);
  printf("NEUSPESNYCH:    %d\n", failed_tests);
  if (failed_tests == 0) {
    printf(COLOR_GREEN "VSETKY TESTY TABULKY SYMBOLOV PRESLI!\n" COLOR_RESET);
  } else {
    printf(COLOR_RED "NIEKTORE TESTY ZLYHALI!\n" COLOR_RESET);
  }
  printf(
      COLOR_BLUE
      "========================================================\n" COLOR_RESET);

  return (failed_tests == 0) ? 0 : 1;
}
