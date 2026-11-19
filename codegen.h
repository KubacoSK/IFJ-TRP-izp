/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 * Autori:
  * @author xodrasa00, Aleš Odráška
  * @author xgazdaa00, Adam Gazdarica
  * @author xkrpeld00, Dominik Krpelan
  * @author xpetraj00, Jakub Petrán
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

// zaciatok funkcie idx, dalsie instrukcie idu do jej bufferov
void gen_function_begin(int idx, const char *name, bool is_main);

// epilog funkcie (POPFRAME, RETURN), vysledok je uz na zasobniku
void gen_function_end(void);

// prikaz return (POPFRAME, RETURN), hodnota je uz na zasobniku
void gen_return(void);

// volanie uzivatelskej funkcie, argumenty su na zasobniku zlava doprava
void gen_call(const char *name);

// prepnutie aktualnej funkcie, zaporny idx instrukcie zahodi
void gen_select(int idx);

// instrukcia do bufferu defs (DEFVAR), bez '\n'
void gen_def(const char *fmt, ...);

// instrukcia do bufferu body, bez '\n'
void gen_emit(const char *fmt, ...);

// PUSHS int@
void gen_push_int(int64_t value);

// PUSHS float@ vo formate %a
void gen_push_double(double value);

// PUSHS string@ s escape sekvenciami \xyz
void gen_push_string(const char *value);

// PUSHS nil@nil (hodnota Unit)
void gen_push_unit(void);

// DEFVAR LF@name$id, id rozlisi zatienene premenne
void gen_defvar(const char *name, unsigned id);

// PUSHS LF@name$id
void gen_push_var(const char *name, unsigned id);

// POPS LF@name$id
void gen_pop_var(const char *name, unsigned id);

// konverzia Int -> Double na vrchu zasobnika (INT2FLOATS)
void gen_convert_top(void);

// binarny operator, podla typov prida konverziu, IDIVS/DIVS alebo CONCAT
void gen_binary(TokenType op, DataType left, DataType right);

// unarne + / - pre Int alebo Double
void gen_unary(TokenType op, DataType type);

// zahodenie hodnoty na vrchu zasobnika
void gen_drop(void);

// nove cislo navestia pre if/while
unsigned gen_new_label(void);

// podmienka if na zasobniku, pri false skok na $if$n$else
void gen_if_cond(unsigned n);

// koniec vetvy then, zaciatok vetvy else
void gen_if_else(unsigned n);

// koniec if, na zasobniku je hodnota vykonanej vetvy
void gen_if_end(unsigned n);

// zaciatok cyklu while pred podmienkou
void gen_while_start(unsigned n);

// podmienka while na zasobniku, pri false skok na koniec
void gen_while_cond(unsigned n);

// koniec tela while, skok na zaciatok, vysledok Unit
void gen_while_end(unsigned n);

// volanie vstavanej funkcie, po volani ostane na zasobniku jeden vysledok
void gen_builtin_call(const char *name, const DataType *arg_types,
                      size_t arg_count);

// vypis celeho programu, vracia ERROR_OK alebo ERROR_INTERNAL
int gen_write(FILE *out);

// uvolnenie vsetkych bufferov generatora
void gen_free(void);

#endif // _CODEGEN_H
