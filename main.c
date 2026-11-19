/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 * Autori:
  * @author xodrasa00, Aleš Odráška
  * @author xgazdaa00, Adam Gazdarica
  * @author xkrpeld00, Dominik Krpelan
  * @author xpetraj00, Jakub Petrán
 * @file main.c
 * @brief Vstupny bod prekladaca IFJ26.
 */

#include "codegen.h"
#include "error.h"
#include "parser.h"
#include "scanner.h"
#include "symtable.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // scanner cita priamo stdin, tokeny drzi parser v pamati
  set_source_file(stdin);

  // Inicializacia tabulky symbolov
  Symtable st;
  symtable_init(&st);

  // Pridanie vstavanych funkcii
  symtable_add_builtins(&st);

  // prvy priechod - nacitanie tokenov a zber hlaviciek funkcii
  int result = parse_headers(&st);

  if (result == ERROR_OK) {
    // druhy priechod - plna analyza tela funkcii nad polom tokenov
    result = parse_program(&st);
  }

  if (result == ERROR_OK) {
    result = gen_write(stdout);
  }

  // Uvolnenie zdrojov
  gen_free();
  parser_free();
  symtable_free(&st);

  return result;
}
