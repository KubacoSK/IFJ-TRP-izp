/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file codegen.h
 * @brief Generator cieloveho kodu IFJcode26.
 *
 */

#ifndef _CODEGEN_H
#define _CODEGEN_H

#include <stdbool.h>
#include <stdio.h>

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

/**
 * Vypis celeho programu: hlavicka, vstupny bod a vsetky funkcie.
 * Volat iba ked preklad prebehol bez chyby.
 * @return ERROR_OK alebo ERROR_INTERNAL pri chybe alokacie pocas generovania
 */
int gen_write(FILE *out);

/** Uvolnenie vsetkych bufferov generatora. */
void gen_free(void);

#endif // _CODEGEN_H
