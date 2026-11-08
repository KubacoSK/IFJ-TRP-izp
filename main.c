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
    // Vytvorenie docasneho suboru a skopirovanie stdin do neho
    FILE *temp_file = tmpfile();
    if (!temp_file) return ERROR_INTERNAL;

    int c;
    while ((c = getchar()) != EOF) {
        fputc(c, temp_file);
    }
    rewind(temp_file);

    // Inicializacia tabulky symbolov
    Symtable st;
    symtable_init(&st);

    // Pridanie vstavanych funkcii
    symtable_add_builtins(&st);

    // prvy priechod - zber hlaviciek funkcii
    set_source_file(temp_file);
    int result = parse_headers(&st);

    if(result == ERROR_OK) {
        // druhy priechod - plna analyza tela funkcii
        rewind(temp_file); // vratenie sa na zaciatok suboru
        set_source_file(temp_file); // reset scannera
        result = parse_program(&st);
    }

    // Uvolnenie zdrojov
    symtable_free(&st);
    fclose(temp_file);

    return result;
}
