/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 * Autori:
  * @author xodrasa00, Aleš Odráška
  * @author xgazdaa00, Adam Gazdarica
  * @author xkrpeld00, Dominik Krpelan
  * @author xpetraj00, Jakub Petrán
 * @file parser.h
 * @brief Rozhranie syntaktickeho analyzatora (Parser) pre IFJ26.
 */

#ifndef _PARSER_H
#define _PARSER_H

#include "symtable.h"

// Hlavna funkcia syntaktickej analyzy: spracuje hlavicky vsetkych funkcii do
// tabulky symbolov Tym umozni volat funkcie pred ich lexikalnou definiciou
int parse_headers(Symtable *st);

// Hlavna funkcia syntaktickej analyzy: spracuje cely program zo vstupu
// Vracia 0 pri uspechu, alebo chybovy kod (1, 2, 3, 4, 5, 6, 7, 10, 99)
int parse_program(Symtable *st);

// Uvolni pole tokenov, volat po oboch priechodoch (aj pri chybe)
void parser_free(void);

#endif // _PARSER_H
