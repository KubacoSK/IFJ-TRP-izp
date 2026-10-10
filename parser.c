/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file parser.c
 * @brief Syntakticky analyzator pre IFJ26 (rekurzivny zostup).
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parser.h"
#include "scanner.h"
#include "error.h"
#include "symtable.h"

// Aktualny nacitany token (lookahead)
static Token current_tok;

// Ukazovatel na tabulku symbolov
static Symtable *symtab = NULL;

// Uvolni stary token a nacita dalsi token zo scanneru
static int next_token(void) {
    free_token_attribute(&current_tok);
    return get_token(&current_tok);
}

// Zisti, ci ma aktualny token dany typ bez posunu
static bool check(TokenType type) {
    return current_tok.type == type;
}

// Zisti, ci je aktualny token konkretne klucove slovo
static bool check_kw(Keyword kw) {
    return current_tok.type == TOKEN_TYPE_KEYWORD && current_tok.attribute.keyword == kw;
}

// Overi ocakavany typ tokenu a posunie sa na dalsi
static int expect(TokenType type) {
    if (!check(type)) {
        return ERROR_SYNTAX;
    }
    return next_token();
}

// Overi ocakavane klucove slovo a posunie sa na dalsi
static int expect_kw(Keyword kw) {
    if (!check_kw(kw)) {
        return ERROR_SYNTAX;
    }
    return next_token();
}

// Prototypy pravidiel rekurzivneho zostupu
static int parse_function(bool is_main);
static int parse_params(void);
static int parse_block(void);
static int parse_statement(void);
static int parse_var_def(void);
static int parse_id_statement(void);
static int parse_if(void);
static int parse_while(void);
static int parse_return(void);
static int parse_simple_expr(void);

// Spracovanie jednoducheho vyrazu (literal, premenna alebo volanie funkcie)
static int parse_simple_expr(void) {
    if (check(TOKEN_TYPE_INT_NUMBER) || check(TOKEN_TYPE_DOUBLE_NUMBER) || check(TOKEN_TYPE_STRING)) {
        return next_token();
    }
    if (check(TOKEN_TYPE_IDENTIFIER)) {
        int res = next_token();
        if (res != SCANNER_TOKEN_OK) return res;

        // Volanie funkcie v ramci vyrazu: id(arg1, arg2)
        if (check(TOKEN_TYPE_LEFT_PAREN)) {
            res = next_token();
            if (res != SCANNER_TOKEN_OK) return res;

            if (!check(TOKEN_TYPE_RIGHT_PAREN)) {
                while (1) {
                    res = parse_simple_expr();
                    if (res != SCANNER_TOKEN_OK) return res;

                    if (check(TOKEN_TYPE_COMMA)) {
                        res = next_token();
                        if (res != SCANNER_TOKEN_OK) return res;
                        continue;
                    }
                    break;
                }
            }
            return expect(TOKEN_TYPE_RIGHT_PAREN);
        }
        return SCANNER_TOKEN_OK;
    }
    return ERROR_SYNTAX;
}

// Deklaracia a definicia premennej: val x [: Type] = expr  alebo  var x [: Type] = expr
static int parse_var_def(void) {
    int res = next_token(); // preskocime 'val' alebo 'var'
    if (res != SCANNER_TOKEN_OK) return res;

    if (!check(TOKEN_TYPE_IDENTIFIER)) return ERROR_SYNTAX;
    res = next_token();
    if (res != SCANNER_TOKEN_OK) return res;

    // Volitelna specifikacia typu: ": Type"
    if (check(TOKEN_TYPE_COLON)) {
        res = next_token();
        if (res != SCANNER_TOKEN_OK) return res;

        if (check_kw(KEYWORD_INT) || check_kw(KEYWORD_DOUBLE) || check_kw(KEYWORD_STRING)) {
            res = next_token();
            if (res != SCANNER_TOKEN_OK) return res;
        } else {
            return ERROR_SYNTAX;
        }
    }

    res = expect(TOKEN_TYPE_ASSIGN);
    if (res != SCANNER_TOKEN_OK) return res;

    res = parse_simple_expr();
    if (res != SCANNER_TOKEN_OK) return res;

    return expect(TOKEN_TYPE_EOL);
}

// Spracovanie prikazu zacinajuceho identifikatorom (priradenie x = expr alebo volanie f())
static int parse_id_statement(void) {
    int res = next_token(); // preskocime identifikator
    if (res != SCANNER_TOKEN_OK) return res;

    // Priradenie do premennej: x = expr EOL
    if (check(TOKEN_TYPE_ASSIGN)) {
        res = next_token();
        if (res != SCANNER_TOKEN_OK) return res;

        res = parse_simple_expr();
        if (res != SCANNER_TOKEN_OK) return res;

        return expect(TOKEN_TYPE_EOL);
    }

    // Samostatne volanie funkcie ako prikaz: foo(arg1, arg2) EOL
    if (check(TOKEN_TYPE_LEFT_PAREN)) {
        res = next_token();
        if (res != SCANNER_TOKEN_OK) return res;

        if (!check(TOKEN_TYPE_RIGHT_PAREN)) {
            while (1) {
                res = parse_simple_expr();
                if (res != SCANNER_TOKEN_OK) return res;

                if (check(TOKEN_TYPE_COMMA)) {
                    res = next_token();
                    if (res != SCANNER_TOKEN_OK) return res;
                    continue;
                }
                break;
            }
        }

        res = expect(TOKEN_TYPE_RIGHT_PAREN);
        if (res != SCANNER_TOKEN_OK) return res;

        return expect(TOKEN_TYPE_EOL);
    }

    return ERROR_SYNTAX;
}

// Podmienka: if expr then EOL INDENT blok DEDENT else EOL INDENT blok DEDENT
static int parse_if(void) {
    int res = next_token(); // preskocime 'if'
    if (res != SCANNER_TOKEN_OK) return res;

    res = parse_simple_expr();
    if (res != SCANNER_TOKEN_OK) return res;

    res = expect_kw(KEYWORD_THEN);
    if (res != SCANNER_TOKEN_OK) return res;

    res = expect(TOKEN_TYPE_EOL);
    if (res != SCANNER_TOKEN_OK) return res;

    res = parse_block();
    if (res != SCANNER_TOKEN_OK) return res;

    res = expect_kw(KEYWORD_ELSE);
    if (res != SCANNER_TOKEN_OK) return res;

    res = expect(TOKEN_TYPE_EOL);
    if (res != SCANNER_TOKEN_OK) return res;

    return parse_block();
}

// Cyklus: while expr do EOL INDENT blok DEDENT
static int parse_while(void) {
    int res = next_token(); // preskocime 'while'
    if (res != SCANNER_TOKEN_OK) return res;

    res = parse_simple_expr();
    if (res != SCANNER_TOKEN_OK) return res;

    res = expect_kw(KEYWORD_DO);
    if (res != SCANNER_TOKEN_OK) return res;

    res = expect(TOKEN_TYPE_EOL);
    if (res != SCANNER_TOKEN_OK) return res;

    return parse_block();
}

// Prikaz navratu: return [expr] EOL
static int parse_return(void) {
    int res = next_token(); // preskocime 'return'
    if (res != SCANNER_TOKEN_OK) return res;

    if (!check(TOKEN_TYPE_EOL)) {
        res = parse_simple_expr();
        if (res != SCANNER_TOKEN_OK) return res;
    }
    return expect(TOKEN_TYPE_EOL);
}

// Spracovanie jedneho prikazu v bloku
static int parse_statement(void) {
    if (check_kw(KEYWORD_VAL) || check_kw(KEYWORD_VAR)) {
        return parse_var_def();
    }
    if (check_kw(KEYWORD_IF)) {
        return parse_if();
    }
    if (check_kw(KEYWORD_WHILE)) {
        return parse_while();
    }
    if (check_kw(KEYWORD_RETURN)) {
        return parse_return();
    }
    if (check(TOKEN_TYPE_IDENTIFIER)) {
        return parse_id_statement();
    }
    return ERROR_SYNTAX;
}

// Spracovanie bloku prikazov ohraniceneho INDENT a DEDENT
static int parse_block(void) {
    int res = expect(TOKEN_TYPE_INDENT);
    if (res != SCANNER_TOKEN_OK) return res;

    symtable_push_scope(symtab);

    while (!check(TOKEN_TYPE_DEDENT) && !check(TOKEN_TYPE_EOF)) {
        if (check(TOKEN_TYPE_EOL)) {
            res = next_token();
            if (res != SCANNER_TOKEN_OK) goto cleanup;
            continue;
        }

        res = parse_statement();
        if (res != SCANNER_TOKEN_OK) goto cleanup;
    }

    res = expect(TOKEN_TYPE_DEDENT);

cleanup:
    symtable_pop_scope(symtab);
    return res;
}

// Spracovanie zoznamu formalnych parametrov funkcie: ( [ id : Type , ... ] )
static int parse_params(void) {
    int res = expect(TOKEN_TYPE_LEFT_PAREN);
    if (res != SCANNER_TOKEN_OK) return res;

    if (check(TOKEN_TYPE_RIGHT_PAREN)) {
        return next_token();
    }

    while (1) {
        if (!check(TOKEN_TYPE_IDENTIFIER)) return ERROR_SYNTAX;
        res = next_token();
        if (res != SCANNER_TOKEN_OK) return res;

        res = expect(TOKEN_TYPE_COLON);
        if (res != SCANNER_TOKEN_OK) return res;

        if (check_kw(KEYWORD_INT) || check_kw(KEYWORD_DOUBLE) ||
            check_kw(KEYWORD_STRING) || check_kw(KEYWORD_UNIT)) {
            res = next_token();
            if (res != SCANNER_TOKEN_OK) return res;
        } else {
            return ERROR_SYNTAX;
        }

        if (check(TOKEN_TYPE_COMMA)) {
            res = next_token();
            if (res != SCANNER_TOKEN_OK) return res;
            continue;
        }
        break;
    }

    return expect(TOKEN_TYPE_RIGHT_PAREN);
}

// Definicia funkcie: [ @main ] def id ( parametre ) : Typ = EOL INDENT blok DEDENT
static int parse_function(bool is_main) {
    (void)is_main;
    int res = expect_kw(KEYWORD_DEF);
    if (res != SCANNER_TOKEN_OK) return res;

    if (!check(TOKEN_TYPE_IDENTIFIER)) return ERROR_SYNTAX;
    res = next_token();
    if (res != SCANNER_TOKEN_OK) return res;

    res = parse_params();
    if (res != SCANNER_TOKEN_OK) return res;

    res = expect(TOKEN_TYPE_COLON);
    if (res != SCANNER_TOKEN_OK) return res;

    if (check_kw(KEYWORD_INT) || check_kw(KEYWORD_DOUBLE) ||
        check_kw(KEYWORD_STRING) || check_kw(KEYWORD_UNIT)) {
        res = next_token();
        if (res != SCANNER_TOKEN_OK) return res;
    } else {
        return ERROR_SYNTAX;
    }

    res = expect(TOKEN_TYPE_ASSIGN);
    if (res != SCANNER_TOKEN_OK) return res;

    res = expect(TOKEN_TYPE_EOL);
    if (res != SCANNER_TOKEN_OK) return res;

    return parse_block();
}

// Hlavny vstupny bod parsera: spracuje postupnost funkcii
int parse_program(Symtable *st) {
    symtab = st;

    int res = next_token();
    if (res != SCANNER_TOKEN_OK && res != TOKEN_TYPE_EOF) {
        return res;
    }

    while (!check(TOKEN_TYPE_EOF)) {
        if (check(TOKEN_TYPE_EOL)) {
            res = next_token();
            if (res != SCANNER_TOKEN_OK) return res;
            continue;
        }

        if (check_kw(KEYWORD_IMPORT)) {
            while (!check(TOKEN_TYPE_EOL) && !check(TOKEN_TYPE_EOF)) {
                res = next_token();
                if (res != SCANNER_TOKEN_OK) return res;
            }
            if (check(TOKEN_TYPE_EOL)) next_token();
            continue;
        }

        if (check(TOKEN_TYPE_MAIN)) {
            res = next_token();
            if (res != SCANNER_TOKEN_OK) return res;
            res = parse_function(true);
            if (res != SCANNER_TOKEN_OK) return res;
            continue;
        }

        if (check_kw(KEYWORD_DEF)) {
            res = parse_function(false);
            if (res != SCANNER_TOKEN_OK) return res;
            continue;
        }

        return ERROR_SYNTAX;
    }

    free_token_attribute(&current_tok);
    return ERROR_OK;
}
