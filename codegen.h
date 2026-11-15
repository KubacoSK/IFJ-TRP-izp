/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file codegen.h
 * @brief Generator cieloveho kodu IFJcode26.
 *
 */

#ifndef _CODEGEN_H
#define _CODEGEN_H

#include "scanner.h"
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
 * Epilog aktualnej funkcie: POPFRAME, RETURN. Vysledok tela (hodnota
 * posledneho prikazu) uz je na zasobniku.
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
 * Definicia premennej LF@name$id do bufferu defs aktualnej funkcie.
 * id je jedinecne cislo z tabulky symbolov (VarData.id), rozlisi zatienenie.
 */
void gen_defvar(const char *name, unsigned id);

/** PUSHS LF@name$id */
void gen_push_var(const char *name, unsigned id);

/** POPS LF@name$id */
void gen_pop_var(const char *name, unsigned id);

/** Konverzia Int -> Double hodnoty na vrchu zasobnika (INT2FLOATS). */
void gen_convert_top(void);

/**
 * Binarny operator nad dvoma hodnotami na zasobniku (lava je pod pravou).
 * Podla typov prida konverziu Int -> Double, vyberie IDIVS/DIVS a pre
 * String + String pouzije CONCAT. Vysledok ostane na zasobniku.
 */
void gen_binary(TokenType op, DataType left, DataType right);

/** Unarne + / - nad hodnotou na vrchu zasobnika typu Int alebo Double. */
void gen_unary(TokenType op, DataType type);

/**
 * Zahodenie hodnoty na vrchu zasobnika (POPS LF@%t1). Kazdy prikaz necha
 * prave jednu hodnotu, pred dalsim prikazom v bloku sa zahodi.
 */
void gen_drop(void);

/** Nove cislo pre navestia if/while (globalne pocitadlo). */
unsigned gen_new_label(void);

/** Podmienka if je na zasobniku: pri false skok na $if$n$else. */
void gen_if_cond(unsigned n);

/** Koniec vetvy then: skok na koniec, zaciatok vetvy else. */
void gen_if_else(unsigned n);

/** Koniec if, na zasobniku je hodnota vykonanej vetvy. */
void gen_if_end(unsigned n);

/** Zaciatok cyklu while (pred podmienkou). */
void gen_while_start(unsigned n);

/** Podmienka while je na zasobniku: pri false skok na koniec cyklu. */
void gen_while_cond(unsigned n);

/** Koniec tela while: zahodi hodnotu tela, skok na zaciatok, vysledok Unit. */
void gen_while_end(unsigned n);

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
