/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file main.c
 * @brief Vstupny bod prekladaca IFJ26.
 */

#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "symtable.h"
#include "parser.h"
#include "error.h"

int main(void) {
    // Nastavenie citania zo standardneho vstupu
    set_source_file(stdin);

    // Inicializacia tabulky symbolov
    Symtable st;
    symtable_init(&st);

    // Spustenie syntaktickej a semantickej analyzy
    int result = parse_program(&st);

    // Uvolnenie zdrojov
    symtable_free(&st);

    return result;
}
