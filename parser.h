/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file parser.h
 * @brief Rozhranie syntaktickeho analyzatora (Parser) pre IFJ26.
 */

#ifndef _PARSER_H
#define _PARSER_H

#include "symtable.h"

// Hlavna funkcia syntaktickej analyzy: spracuje cely program zo vstupu
// Vracia 0 pri uspechu, alebo chybovy kod (1, 2, 3, 4, 5, 6, 7, 10, 99)
int parse_program(Symtable *st);

#endif // _PARSER_H
