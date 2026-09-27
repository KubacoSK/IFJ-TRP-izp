/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file scanner.h
 * @brief Scanner interface for IFJ26
 *
 */

#ifndef _SCANNER_H
#define _SCANNER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * @enum Reserved keywords for IFJ26 Base specification
 */
typedef enum {
    KEYWORD_DEF,        // def
    KEYWORD_DO,         // do
    KEYWORD_DOUBLE,     // Double
    KEYWORD_ELSE,       // else
    KEYWORD_IF,         // if
    KEYWORD_IMPORT,     // import
    KEYWORD_INT,        // Int
    KEYWORD_RETURN,     // return
    KEYWORD_STRING,     // String
    KEYWORD_THEN,       // then
    KEYWORD_UNIT,       // Unit
    KEYWORD_VAL,        // val
    KEYWORD_VAR,        // var
    KEYWORD_WHILE       // while
} Keyword;

/**
 * @enum Type of token for IFJ26 Base specification.
 */
typedef enum {
    TOKEN_TYPE_EOF,             // End of file
    TOKEN_TYPE_EOL,             // End of logical line
    TOKEN_TYPE_INDENT,          // Indentation increase (block start)
    TOKEN_TYPE_DEDENT,          // Indentation decrease (block end)
    TOKEN_TYPE_EMPTY,           // Empty / uninitialized

    // Identifiers and literals
    TOKEN_TYPE_IDENTIFIER,      // Identifier (foo, _bar, x1)
    TOKEN_TYPE_KEYWORD,         // Keyword (from Keyword enum)
    TOKEN_TYPE_UNDERSCORE,      // Wildcard identifier '_'
    TOKEN_TYPE_INT_NUMBER,      // Integer literal (123, 1_000_000)
    TOKEN_TYPE_DOUBLE_NUMBER,   // Double literal (12.34, 1.2e-3, .5, 12e3, 1.5d)
    TOKEN_TYPE_STRING,          // String literal ("..." or """...""")

    // Annotation
    TOKEN_TYPE_MAIN,            // @main annotation

    // Operators
    TOKEN_TYPE_PLUS,            // +
    TOKEN_TYPE_MINUS,           // -
    TOKEN_TYPE_MUL,             // *
    TOKEN_TYPE_DIV,             // /

    // Comparison operators
    TOKEN_TYPE_EQ,              // ==
    TOKEN_TYPE_NEQ,             // !=
    TOKEN_TYPE_LT,              // <
    TOKEN_TYPE_LEQ,             // <=
    TOKEN_TYPE_GT,              // >
    TOKEN_TYPE_GEQ,             // >=

    // Assignment
    TOKEN_TYPE_ASSIGN,          // =

    // Delimiters & punctuation
    TOKEN_TYPE_LEFT_PAREN,      // (
    TOKEN_TYPE_RIGHT_PAREN,     // )
    TOKEN_TYPE_COMMA,           // ,
    TOKEN_TYPE_DOT,             // .
    TOKEN_TYPE_COLON,           // :
    TOKEN_TYPE_SEMICOLON,       // ;

    // Compatibility aliases
    TOKEN_TYPE_LEFT_BRACKET = TOKEN_TYPE_LEFT_PAREN,
    TOKEN_TYPE_RIGHT_BRACKET = TOKEN_TYPE_RIGHT_PAREN
} TokenType;

typedef TokenType Token_type;

/**
 * @union Token attribute.
 */
typedef union {
    char *string;           // String or identifier value
    int64_t integer;        // Integer value or indentation column
    Keyword keyword;        // Keyword enum value
    double decimal;         // Double value
} Token_attribute;

/**
 * @struct Token representation.
 */
typedef struct {
    TokenType type;             // Token type
    Token_attribute attribute;   // Token attribute
    bool had_preceding_newline; // True if immediately preceded by a newline (for trailing comma rule)
} Token;

/**
 * Optional: Sets source file to be scanned and resets scanner state.
 * If not called (or called with NULL), the scanner automatically reads from stdin.
 * @param f Pointer to source file (optional).
 */
void set_source_file(FILE *f);

/**
 * Resets the scanner internal state.
 */
void reset_scanner(void);

/**
 * Scans the next token from the source file.
 * @param token Pointer to output token.
 * @return SCANNER_TOKEN_OK (0) if successful, otherwise error code (1 for lexical, 2 for syntax, 99 internal).
 */
int get_token(Token *token);

/**
 * Frees dynamically allocated memory in a token (e.g. string).
 * @param token Pointer to token to free.
 */
void free_token_attribute(Token *token);

/**
 * Returns a token back to the lookahead buffer.
 * @param token Token to put back.
 * @return SCANNER_TOKEN_OK if successful, ERROR_INTERNAL on overflow.
 */
int unget_token(Token token);

#endif // _SCANNER_H