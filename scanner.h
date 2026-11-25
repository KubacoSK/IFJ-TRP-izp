/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 * Autori:
 * @author xodrasa00, Aleš Odráška
 * @author xgazdaa00, Adam Gazdarica
 * @author xkrpeld00, Dominik Krpelan
 * @author xpetraj00, Jakub Petrán
 * @file scanner.h
 * @brief Rozhranie lexikalneho analyzatora pre IFJ26.
 */

#ifndef _SCANNER_H
#define _SCANNER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/**
 * @enum Rezervovane klucove slova pre IFJ26
 */
typedef enum {
  KEYWORD_DEF,    // def
  KEYWORD_DO,     // do
  KEYWORD_DOUBLE, // Double
  KEYWORD_ELSE,   // else
  KEYWORD_IF,     // if
  KEYWORD_IMPORT, // import
  KEYWORD_INT,    // Int
  KEYWORD_RETURN, // return
  KEYWORD_STRING, // String
  KEYWORD_THEN,   // then
  KEYWORD_UNIT,   // Unit
  KEYWORD_VAL,    // val
  KEYWORD_VAR,    // var
  KEYWORD_WHILE   // while
} Keyword;

/**
 * @enum Typ tokenu pre IFJ26.
 */
typedef enum {
  TOKEN_TYPE_EOF,    // Koniec suboru
  TOKEN_TYPE_EOL,    // Koniec logickeho riadku
  TOKEN_TYPE_INDENT, // Zvysenie urovne odsadenia (zaciatok bloku)
  TOKEN_TYPE_DEDENT, // Znizenie urovne odsadenia (koniec bloku)
  TOKEN_TYPE_EMPTY,  // Prazdny / neinicializovany

  // Identifikatory a literaly
  TOKEN_TYPE_IDENTIFIER,    // Identifikator (foo, _bar, x1)
  TOKEN_TYPE_KEYWORD,       // Klucove slovo (z enum Keyword)
  TOKEN_TYPE_UNDERSCORE,    // Samostatne podtrzitko '_'
  TOKEN_TYPE_INT_NUMBER,    // Celociselny literal (123, 1_000_000)
  TOKEN_TYPE_DOUBLE_NUMBER, // Desatinny literal (12.34, 1.2e-3, .5, 12e3, 1.5d)
  TOKEN_TYPE_STRING,        // Retazcovy literal ("..." alebo """...""")

  // Anotacia
  TOKEN_TYPE_MAIN, // Anotacia @main

  // Operatory
  TOKEN_TYPE_PLUS,  // +
  TOKEN_TYPE_MINUS, // -
  TOKEN_TYPE_MUL,   // *
  TOKEN_TYPE_DIV,   // /

  // Porovnavacie operatory
  TOKEN_TYPE_EQ,  // ==
  TOKEN_TYPE_NEQ, // !=
  TOKEN_TYPE_LT,  // <
  TOKEN_TYPE_LEQ, // <=
  TOKEN_TYPE_GT,  // >
  TOKEN_TYPE_GEQ, // >=

  // Priradenie
  TOKEN_TYPE_ASSIGN, // =

  // Oddelovace a interpunkcia
  TOKEN_TYPE_LEFT_PAREN,  // (
  TOKEN_TYPE_RIGHT_PAREN, // )
  TOKEN_TYPE_COMMA,       // ,
  TOKEN_TYPE_DOT,         // .
  TOKEN_TYPE_COLON,       // :
  TOKEN_TYPE_SEMICOLON,   // ;
  TOKEN_TYPE_LEFT_BRACE,  // { (IFJ26 ho nepodporuje, parser hlasi chybu 2)
  TOKEN_TYPE_RIGHT_BRACE, // } (IFJ26 ho nepodporuje, parser hlasi chybu 2)

  // Aliasy pre kompatibilitu
  TOKEN_TYPE_LEFT_BRACKET = TOKEN_TYPE_LEFT_PAREN,
  TOKEN_TYPE_RIGHT_BRACKET = TOKEN_TYPE_RIGHT_PAREN
} TokenType;

typedef TokenType Token_type;

/**
 * @union Atribut tokenu.
 */
typedef union {
  char *string;    // Hodnota retazca alebo identifikatora
  int64_t integer; // Hodnota celeho cisla
  Keyword keyword; // Hodnota klucoveho slova
  double decimal;  // Hodnota desatinneho cisla
} Token_attribute;

/**
 * @struct Reprezentacia tokenu.
 */
typedef struct {
  TokenType type;             // Typ tokenu
  Token_attribute attribute;  // Atribut tokenu
  bool had_preceding_newline; // Priznak, ci tokenu predchadzal novy riadok
} Token;

/**
 * Nastavi zdrojovy subor pre scanner a resetuje jeho stav.
 * Ak nie je zavolana (alebo s NULL), scanner cita zo stdin.
 * @param f Ukazovatel na zdrojovy subor.
 */
void set_source_file(FILE *f);

/**
 * Resetuje vnutorny stav scanneru.
 */
void reset_scanner(void);

/**
 * Nacita dalsi token zo zdrojoveho suboru.
 * @param token Ukazovatel na vystupny token.
 * @return SCANNER_TOKEN_OK (0) pri uspechu, inak chybovy kod.
 */
int get_token(Token *token);

/**
 * Uvolni dynamicky alokovanu pamat atributu tokenu (napr. retazec).
 * @param token Ukazovatel na token.
 */
void free_token_attribute(Token *token);

/**
 * Vrati token spat do vyrovnavacej pamate lookaheadu.
 * @param token Token na vratenie.
 * @return SCANNER_TOKEN_OK pri uspechu, ERROR_INTERNAL pri preteceni.
 */
int unget_token(Token token);

#endif // _SCANNER_H