/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file error.h
 * @brief Definicia chybovych kodov prekladaca IFJ26.
 */

#ifndef _ERROR_H
#define _ERROR_H

// Uspech
#define SCANNER_TOKEN_OK        0
#define ERROR_OK                0

// 1: Lexikalna chyba (chybna struktura lexemy, komentare, odsadenie)
#define ERROR_LEX               1
#define SCANNER_ERROR_LEX       1

// 2: Syntakticka chyba (chybna syntax, chybajuci prolog, nepovolena konstrukcia)
#define ERROR_SYNTAX            2
#define SCANNER_ERROR_SYNTAX    2

// 3: Semanticka chyba - nedefinovana funkcia, premenna, typ; chybajuci @main
#define ERROR_SEM_UNDEF         3

// 4: Semanticka chyba - neplatna redefinicia funkcie, premennej alebo typu
#define ERROR_SEM_REDEF         4

// 5: Semanticka chyba - nespravny pocet alebo typ parametrov funkcie; neplatne parametre @main
#define ERROR_SEM_PARAM         5

// 6: Semanticka chyba - typova kompatibilita vo vyraze, priradeni, navrate
#define ERROR_SEM_TYPE          6

// 7: Semanticka chyba - zapis do nemenneho identifikatora (val) alebo formalneho parametra
#define ERROR_SEM_CONST         7

// 10: Ostatne semanticke chyby (neplatny return atd.)
#define ERROR_SEM_OTHER         10

// 40: Chyba behu (index mimo rozsah, delenie nulou atd.)
#define ERROR_RUNTIME           40

// 99: Interna chyba prekladaca (zlyhanie alokacie pamate atd.)
#define ERROR_INTERNAL          99

#endif // _ERROR_H
