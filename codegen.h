/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file codegen.h
 * @brief Generator cieloveho kodu IFJcode26.
 *
 */

#ifndef _CODEGEN_H
#define _CODEGEN_H

#include "symtable.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

// najvacsi pocet argumentov vstavanej funkcie (subStr)
#define BUILTIN_MAX_ARGS 3

/**
 * Zaciatok generovania funkcie s indexom idx (index z tabulky funkcii
 * parsera). Funkcia sa stane aktualnou, dalsie instrukcie idu do jej bufferov.
 * Volat raz na funkciu pred analyzou jej tela.
 */
void gen_function_begin(int idx, const char *name, bool is_main);

/**
 * Epilog aktualnej funkcie: na zasobniku necha Unit (nil@nil), POPFRAME,
 * RETURN.
 */
void gen_function_end(void);

/**
 * Prepnutie aktualnej funkcie (navrat po analyze na poziadanie).
 * Zaporny index = ziadna funkcia, instrukcie sa zahodia.
 */
void gen_select(int idx);

/** Instrukcia do bufferu defs aktualnej funkcie (DEFVAR), bez '\n'. */
void gen_def(const char *fmt, ...);

/** Instrukcia do bufferu body aktualnej funkcie, bez '\n'. */
void gen_emit(const char *fmt, ...);

/** PUSHS celociselneho literalu (int@...). */
void gen_push_int(int64_t value);

/** PUSHS desatinneho literalu (float@ vo formate %a). */
void gen_push_double(double value);

/**
 * PUSHS retazcoveho literalu. Retazec je uz dekodovany scannerom, znaky
 * 0-32, '#', '\\' a ne-ASCII bajty sa zapisu ako escape \xyz.
 */
void gen_push_string(const char *value);

/** PUSHS hodnoty typu Unit (nil@nil). */
void gen_push_unit(void);

/**
 * Volanie vstavanej funkcie. Argumenty su uz na zasobniku zlava doprava,
 * po volani na zasobniku ostane prave jeden vysledok.
 * @param name meno funkcie v IFJ26
 * @param arg_types typy argumentov (vyber instrukcie pri preklade)
 * @param arg_count pocet argumentov
 */
void gen_builtin_call(const char *name, const DataType *arg_types,
                      size_t arg_count);

/**
 * Vypis celeho programu: hlavicka, vstupny bod a vsetky funkcie.
 * Volat iba ked preklad prebehol bez chyby.
 * @return ERROR_OK alebo ERROR_INTERNAL pri chybe alokacie pocas generovania
 */
int gen_write(FILE *out);

/** Uvolnenie vsetkych bufferov generatora. */
void gen_free(void);

#endif // _CODEGEN_H
