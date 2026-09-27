/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file error.h
 * @brief Error code definitions according to IFJ26 specification
 
 */

#ifndef _ERROR_H
#define _ERROR_H

// Success
#define SCANNER_TOKEN_OK        0
#define ERROR_OK                0

// 1: Lexical error (invalid structure of lexeme, comments, indentation)
#define ERROR_LEX               1
#define SCANNER_ERROR_LEX       1

// 2: Syntax error (syntax error, missing prologue, forbidden construct, block structure violation)
#define ERROR_SYNTAX            2
#define SCANNER_ERROR_SYNTAX    2

// 3: Semantic error - undefined function, variable, or type; missing @main
#define ERROR_SEM_UNDEF         3

// 4: Semantic error - invalid redefinition of function, variable, or type
#define ERROR_SEM_REDEF         4

// 5: Semantic error - incorrect count or type of function arguments; invalid params of @main
#define ERROR_SEM_PARAM         5

// 6: Semantic error - type compatibility or inference in expr, assignment, init, return, control
#define ERROR_SEM_TYPE          6

// 7: Semantic error - attempt to write to immutable variable or formal parameter
#define ERROR_SEM_CONST         7

// 10: Other semantic errors (e.g. invalid return, non-exhaustive match, zero range step)
#define ERROR_SEM_OTHER         10

// 40: Runtime error (e.g. string index out of bounds, head of empty list)
#define ERROR_RUNTIME           40

// 99: Internal compiler error (memory allocation failure, etc.)
#define ERROR_INTERNAL          99

#endif // _ERROR_H
