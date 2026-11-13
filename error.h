/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file error.h
 * @brief Definicia chybovych kodov prekladaca IFJ26.
 */

#ifndef _ERROR_H
#define _ERROR_H

// Uspech
#define SCANNER_TOKEN_OK 0
#define ERROR_OK 0

// Lexikalna chyba
#define ERROR_LEX 1
#define SCANNER_ERROR_LEX 1

// Syntakticka chyba
#define ERROR_SYNTAX 2
#define SCANNER_ERROR_SYNTAX 2

// Semanticka chyba: nedefinovana funkcia alebo premenna, chybajuci @main
#define ERROR_SEM_UNDEF 3

// Semanticka chyba: neplatna redefinicia funkcie alebo premennej
#define ERROR_SEM_REDEF 4

// Semanticka chyba: nespravny pocet alebo typ parametrov funkcie
#define ERROR_SEM_PARAM 5

// Semanticka chyba: typova nekompatibilita vo vyraze alebo priradeni
#define ERROR_SEM_TYPE 6

// Semanticka chyba: zapis do nemenneho identifikatora (val) alebo parametra
#define ERROR_SEM_CONST 7

// Semanticka chyba: ostatne semanticke chyby (neplatny return)
#define ERROR_SEM_OTHER 10

// Behova chyba (index mimo rozsah, delenie nulou)
#define ERROR_RUNTIME 40

// Interna chyba prekladaca (zlyhanie alokacie pamate)
#define ERROR_INTERNAL 99

#endif // _ERROR_H
