/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file parser.c
 * @brief Syntakticky analyzator pre IFJ26 (rekurzivny zostup).
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "parser.h"
#include "scanner.h"
#include "error.h"
#include "symtable.h"
#include "utils.h"

#define EXPR_STACK_INIT 16 // zaciatocna velkost zasobnikov vyrazu

// pomocna funkcia na ziskanie indexu pre precedencu tabulku
// poradie podla hlavicky tabulky: + - * / < <= > >= == != ( ) $
static int get_op_index(TokenType type) {
    switch (type) {
        case TOKEN_TYPE_PLUS: return 0;
        case TOKEN_TYPE_MINUS: return 1;
        case TOKEN_TYPE_MUL: return 2;
        case TOKEN_TYPE_DIV: return 3;
        case TOKEN_TYPE_LT: return 4;
        case TOKEN_TYPE_LEQ: return 5;
        case TOKEN_TYPE_GT: return 6;
        case TOKEN_TYPE_GEQ: return 7;
        case TOKEN_TYPE_EQ: return 8;
        case TOKEN_TYPE_NEQ: return 9;
        case TOKEN_TYPE_LEFT_PAREN: return 10;
        case TOKEN_TYPE_RIGHT_PAREN: return 11;
        case TOKEN_TYPE_EOL: return 12; // EOL je koniec vyrazu ($)
        default: return -1; // iny token (napr. cislo)
    }
}

// Precedencna tabulka, E znaci error
static const char prec_table[13][13] = {
    // +    -    *    /    <    <=   >    >=   ==   !=   (    )    $
    {'>', '>', '<', '<', '>', '>', '>', '>', '>', '>', '<', '>', '>'}, // +
    {'>', '>', '<', '<', '>', '>', '>', '>', '>', '>', '<', '>', '>'}, // -
    {'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '>'}, // *
    {'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '>'}, // /
    {'<', '<', '<', '<', '>', '>', '>', '>', '>', '>', '<', '>', '>'}, // <
    {'<', '<', '<', '<', '>', '>', '>', '>', '>', '>', '<', '>', '>'}, // <=
    {'<', '<', '<', '<', '>', '>', '>', '>', '>', '>', '<', '>', '>'}, // >
    {'<', '<', '<', '<', '>', '>', '>', '>', '>', '>', '<', '>', '>'}, // >=
    {'<', '<', '<', '<', '<', '<', '<', '<', '>', '>', '<', '>', '>'}, // ==
    {'<', '<', '<', '<', '<', '<', '<', '<', '>', '>', '<', '>', '>'}, // !=
    {'<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '=', 'E'}, // (
    {'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', 'E', '>', '>'}, // )
    {'<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', 'E', 'E'}  // $
};

// pole tokenov, naplni ho prvy priechod
static Token *tokens = NULL;
static size_t token_count = 0;
static size_t token_cap = 0;
static size_t pos = 0;                      // index aktualneho tokenu
static int lex_error = SCANNER_TOKEN_OK;    // chyba na zarazke

// aktualny token
#define current_tok (tokens[pos])

// Ukazovatel na tabulku symbolov
static Symtable *symtab = NULL;

// aktualny navratovy typ, v ktorej sa nachadzame
static DataType current_func_return_type = TYPE_UNDEF;

// explicitny Unit
static bool current_func_explicit_unit = false;

// typ v hlavicke
static bool current_func_explicit_type = false;

// prikaz za ;
static bool after_semicolon = false;

// pridaj token do pola
static int push_token(Token tok) {
    if (token_count == token_cap) {
        size_t new_cap = token_cap ? token_cap * 2 : 256;
        Token *tmp = realloc(tokens, new_cap * sizeof(Token));
        if (!tmp) {
            free_token_attribute(&tok);
            return ERROR_INTERNAL;
        }
        tokens = tmp;
        token_cap = new_cap;
    }
    tokens[token_count++] = tok;
    return SCANNER_TOKEN_OK;
}

// nacita cely vstup do pola, lexikalna chyba = zarazka na konci
static int tokenize(void) {
    while (1) {
        Token tok;
        int res = get_token(&tok);
        if (res != SCANNER_TOKEN_OK) {
            // chyba sa vrati az ked k nej parser dojde
            lex_error = res;
            Token stop = {.type = TOKEN_TYPE_EMPTY, .attribute = {.string = NULL}};
            return push_token(stop);
        }
        res = push_token(tok);
        if (res != SCANNER_TOKEN_OK) return res;
        if (tok.type == TOKEN_TYPE_EOF) return SCANNER_TOKEN_OK;
    }
}

// chyba na zarazke
static int token_status(void) {
    return tokens[pos].type == TOKEN_TYPE_EMPTY ? lex_error : SCANNER_TOKEN_OK;
}

// zaciatok priechodu
static int first_token(void) {
    pos = 0;
    return token_status();
}

// Posun na dalsi token, na EOF a zarazke sa stoji
static int next_token(void) {
    if (tokens[pos].type != TOKEN_TYPE_EOF && tokens[pos].type != TOKEN_TYPE_EMPTY) pos++;
    return token_status();
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

// preskoc EOL
static int skip_eols(void) {
    while (check(TOKEN_TYPE_EOL)) {
        int res = next_token();
        if (res != SCANNER_TOKEN_OK) return res;
    }
    return SCANNER_TOKEN_OK;
}

// koniec prikazu
static bool at_stmt_end(void) {
    return check(TOKEN_TYPE_EOL) || check(TOKEN_TYPE_SEMICOLON);
}

// EOL alebo ;
static int expect_stmt_end(void) {
    after_semicolon = check(TOKEN_TYPE_SEMICOLON);
    if (after_semicolon) return next_token();
    return expect(TOKEN_TYPE_EOL);
}

// nazov typu, neznamy id = chyba 3
static int parse_type(DataType *out) {
    if (check_kw(KEYWORD_INT)) *out = TYPE_INT;
    else if (check_kw(KEYWORD_DOUBLE)) *out = TYPE_DOUBLE;
    else if (check_kw(KEYWORD_STRING)) *out = TYPE_STRING;
    else if (check_kw(KEYWORD_UNIT)) *out = TYPE_UNIT;
    else if (check(TOKEN_TYPE_IDENTIFIER)) return ERROR_SEM_UNDEF; // chyba 3
    else return ERROR_SYNTAX;
    return next_token();
}

// vysledok prikazu alebo bloku (pravidla navratovej hodnoty 2.3)
typedef struct {
    DataType type;      // typ vysledku, definicia/priradenie/cyklus = Unit
    bool ends_with_if;  // posledny prikaz je if
    bool all_return;    // vsetky vetvy koncia return
    bool all_unit;      // vysledky vsetkych vetiev su Unit
} StmtResult;

// jednoduchy prikaz s typom
static void set_result(StmtResult *out, DataType type) {
    out->type = type;
    out->ends_with_if = false;
    out->all_return = false;
    out->all_unit = (type == TYPE_UNIT);
}

// typ source mozno pouzit ako target
static bool is_compatible(DataType target, DataType source) {
    return target == source || (target == TYPE_DOUBLE && source == TYPE_INT);
}

// Prototypy pravidiel rekurzivneho zostupu
static int parse_function(bool is_main);
static int parse_params(Param **out_params, size_t *param_count);
static int parse_block(Param *params, size_t param_count, StmtResult *out);
static int parse_statement(StmtResult *out);
static int parse_var_def(void);
static int parse_id_statement(StmtResult *out);
static int parse_if(StmtResult *out);
static int parse_while(void);
static int parse_return(void);
static int parse_term(DataType *out_type);
static int parse_expression(DataType *out_type);

// vyraz v zatvorke
static int parse_paren_expr(DataType *out_type) {
    int res = next_token(); // (
    if (res != SCANNER_TOKEN_OK) return res;

    // prazdne ()
    if (check(TOKEN_TYPE_RIGHT_PAREN)) {
        *out_type = TYPE_UNIT;
        return next_token();
    }

    res = parse_expression(out_type);
    if (res != SCANNER_TOKEN_OK) return res;
    return expect(TOKEN_TYPE_RIGHT_PAREN);
}

// Spracovanie jednoducheho vyrazu (literal, premenna alebo volanie funkcie)
static int parse_term(DataType *out_type) {

    // Unarne operatory (+, -)
    if (check(TOKEN_TYPE_PLUS) || check(TOKEN_TYPE_MINUS)) {
        int res = next_token();
        if (res != SCANNER_TOKEN_OK) return res;
        // -(...) cely vyraz
        if (check(TOKEN_TYPE_LEFT_PAREN)) res = parse_paren_expr(out_type);
        else res = parse_term(out_type); // rekurzivne precitanie operandu
        if (res != SCANNER_TOKEN_OK) return res;

        // unarne operatory su povolene len pre cisla
        if(*out_type != TYPE_INT && *out_type != TYPE_DOUBLE) {
            return ERROR_SEM_TYPE; 
        }
        return SCANNER_TOKEN_OK;
    }


    // Literaly
    if(check(TOKEN_TYPE_INT_NUMBER)) {
        *out_type = TYPE_INT;
        return next_token();
    }
    if(check(TOKEN_TYPE_DOUBLE_NUMBER)) {
        *out_type = TYPE_DOUBLE;
        return next_token();
    }
    if(check(TOKEN_TYPE_STRING)) {
        *out_type = TYPE_STRING;
        return next_token();
    }
    // prazdne zatvorky pre Unit ()
    if(check(TOKEN_TYPE_LEFT_PAREN)) {
        int res = next_token(); // (
        if (res != SCANNER_TOKEN_OK) return res;

        if (!check(TOKEN_TYPE_RIGHT_PAREN)) {
            return ERROR_SYNTAX;
        }
        *out_type = TYPE_UNIT;
        return next_token(); // )
    }
    
    // Identifikator (premmena alebo funkcia)
    if(check(TOKEN_TYPE_IDENTIFIER)) {
        char *id_name = str_dup(current_tok.attribute.string);
        int res = next_token();
        if(res != SCANNER_TOKEN_OK) {
            free(id_name);
            return res;
        }

        // volanie funkcie?
        if(check(TOKEN_TYPE_LEFT_PAREN)) {
            Symbol *func = symtable_find_func(symtab, id_name);
            if(!func) {
                free(id_name);
                return ERROR_SEM_UNDEF; // Chyba 3
            }

            res = next_token(); // (
            if (res != SCANNER_TOKEN_OK) {
                free(id_name);
                return res;
            }

            // pocitadlo precitanych argumentov
            size_t arg_index_count = 0;

            // docasne preskocenie argumentov (potom treba pridat ich kontrolu)
            if (!check(TOKEN_TYPE_RIGHT_PAREN)) {
                while (1) {
                    DataType arg_type;
                    res = parse_term(&arg_type); // nacitanie argumentu
                    if(res != SCANNER_TOKEN_OK) {
                        free(id_name);
                        return res;
                    }

                    // kontrola ci neposielame prilis vela argumentov nez funkcia ocakava
                    if(arg_index_count >= func->data.func.param_count) {
                        free(id_name);
                        return ERROR_SEM_PARAM; // Chyba 5
                    }

                    // kontrola typu argumentu
                    DataType expected_type = func->data.func.params[arg_index_count].type;
                    if(expected_type != arg_type && expected_type != TYPE_ANY) {
                        // povolime konverziu Int -> Double
                        if(!(expected_type == TYPE_DOUBLE && arg_type == TYPE_INT)) {
                            free(id_name);
                            return ERROR_SEM_PARAM; // Chyba 5
                        }
                    }

                    arg_index_count++; // posunieme sa na dalsi parameter

                    if(check(TOKEN_TYPE_COMMA)) {
                        res = next_token();
                        if(res != SCANNER_TOKEN_OK) {
                            free(id_name);
                            return res;
                        }
                        // koncova ciarka len pred novym riadkom
                        if (check(TOKEN_TYPE_RIGHT_PAREN) && current_tok.had_preceding_newline) break;
                        continue;
                    }
                    break;
                }
            }

            // kontrola, ci vsetky argumenty boli poslane
            if (arg_index_count < func->data.func.param_count) {
                free(id_name);
                return ERROR_SEM_PARAM; // Chyba 5
            }

            res = expect(TOKEN_TYPE_RIGHT_PAREN);
            *out_type = func->data.func.return_type;
            free(id_name);
            return res;
    }

    // premenna?
    else {
        Symbol *var = symtable_find_var(symtab, id_name);
        if(!var) {
            free(id_name);
            return ERROR_SEM_UNDEF; // Chyba 3
        }
        *out_type = var->data.var.type;
        free(id_name);
        return SCANNER_TOKEN_OK;
        }
    } 

return ERROR_SYNTAX;
}

// pomocna funkcia na spracovanie redukcie (sematika)
static int reduce_operation(TokenType op, DataType left, DataType right, DataType *result) {
    
    // aritmeticke operatory
    if(op == TOKEN_TYPE_PLUS || op == TOKEN_TYPE_MINUS ||
       op == TOKEN_TYPE_MUL || op == TOKEN_TYPE_DIV) {

        // konkatenacia retazcov (iba pre +)
        if (op == TOKEN_TYPE_PLUS && left == TYPE_STRING && right == TYPE_STRING) {
            *result = TYPE_STRING;
            return SCANNER_TOKEN_OK;
        }

        // Oba Int = vysledok Int
        if (left == TYPE_INT && right == TYPE_INT) {
            *result = TYPE_INT;
            return SCANNER_TOKEN_OK;
        }

        // ak je aspon jeden double = vysledok double
        if ((left == TYPE_DOUBLE || right == TYPE_DOUBLE) &&
            (left == TYPE_INT || left == TYPE_DOUBLE) &&
            (right == TYPE_INT || right == TYPE_DOUBLE)) {
                *result = TYPE_DOUBLE;
                return SCANNER_TOKEN_OK;
            }

            // vsetko ostatne chyba 6 (napr. string + int)
            return ERROR_SEM_TYPE;

       }

       // relacne operatory
       if (op == TOKEN_TYPE_LT || op == TOKEN_TYPE_LEQ || op == TOKEN_TYPE_GT ||
           op == TOKEN_TYPE_GEQ || op == TOKEN_TYPE_EQ || op == TOKEN_TYPE_NEQ) {

            bool left_num = (left == TYPE_INT || left == TYPE_DOUBLE);
            bool right_num = (right == TYPE_INT || right == TYPE_DOUBLE);
           

           // porovnat mozeme cisla alebo 2 stringy
           if ((left_num && right_num) || (left == TYPE_STRING && right == TYPE_STRING)) {
                *result = TYPE_BOOL; // vysledok porovnania Boolean
                return SCANNER_TOKEN_OK;
           }

           return ERROR_SEM_TYPE; // chyba 6
        }

    return ERROR_SYNTAX;
}

// zasobniky vyrazu
typedef struct {
    TokenType *ops;
    DataType *types;
    int op_top;
    int type_top;
    int op_cap;
    int type_cap;
} ExprStack;

// push operator
static int push_op(ExprStack *s, TokenType op) {
    if (s->op_top + 1 >= s->op_cap) {
        int new_cap = s->op_cap * 2;
        TokenType *tmp = realloc(s->ops, (size_t)new_cap * sizeof(TokenType));
        if (!tmp) return ERROR_INTERNAL;
        s->ops = tmp;
        s->op_cap = new_cap;
    }
    s->ops[++s->op_top] = op;
    return SCANNER_TOKEN_OK;
}

// push typ
static int push_type(ExprStack *s, DataType type) {
    if (s->type_top + 1 >= s->type_cap) {
        int new_cap = s->type_cap * 2;
        DataType *tmp = realloc(s->types, (size_t)new_cap * sizeof(DataType));
        if (!tmp) return ERROR_INTERNAL;
        s->types = tmp;
        s->type_cap = new_cap;
    }
    s->types[++s->type_top] = type;
    return SCANNER_TOKEN_OK;
}

static int parse_expression_inner(ExprStack *s, DataType *out_type);

// precedencna analyza vyrazou
static int parse_expression(DataType *out_type) {
    ExprStack s = {NULL, NULL, -1, -1, EXPR_STACK_INIT, EXPR_STACK_INIT};
    s.ops = malloc(EXPR_STACK_INIT * sizeof(TokenType));
    s.types = malloc(EXPR_STACK_INIT * sizeof(DataType));

    int res = ERROR_INTERNAL;
    if (s.ops && s.types) res = parse_expression_inner(&s, out_type);

    free(s.ops);
    free(s.types);
    return res;
}

// telo precedencnej analyzy, zasobniky uvolni volajuci
static int parse_expression_inner(ExprStack *s, DataType *out_type) {

    // koniec vyrazu na spodok zasobnika ($)
    int res = push_op(s, TOKEN_TYPE_EOL);
    if (res != SCANNER_TOKEN_OK) return res;

    // priznak, ci ocakavame operand
    bool expect_opd = true;

    // otvorene (
    int open_parens = 0;

    while(1) {

        // zistime ci je + alebo - unarne
        bool is_unary = (current_tok.type == TOKEN_TYPE_PLUS ||
                         current_tok.type == TOKEN_TYPE_MINUS) && expect_opd;

        // ak na vstupe je operand (cislo, premenna) alebo unary operator
        if (current_tok.type == TOKEN_TYPE_INT_NUMBER ||
           current_tok.type == TOKEN_TYPE_DOUBLE_NUMBER ||
           current_tok.type == TOKEN_TYPE_STRING ||
           current_tok.type == TOKEN_TYPE_IDENTIFIER || is_unary) {

            // operand za operandom
            if (!expect_opd) return ERROR_SYNTAX;

            DataType t;
            res = parse_term(&t); // nacitanie operandu
            if (res != SCANNER_TOKEN_OK) return res;

            res = push_type(s, t);
            if (res != SCANNER_TOKEN_OK) return res;
            expect_opd = false; // po operande uz ocakavame operator
            continue;
        }

        // ak je na vstupe operator (alebo koniec)
        TokenType curr_op = current_tok.type;

        // zistime co je na vrchu zasobnika
        TokenType top_op = s->ops[s->op_top];

        // ziskame indexy pre precedencnu tabulku
        int top_index = get_op_index(top_op);
        int curr_index = get_op_index(curr_op);

        // ak je nieco, co neni v tabulke, vezmeme to ako koniec vyrazu
        if (curr_index == -1 ) curr_index = 12; // EOL

        // cudzia ) je koniec
        if (curr_op == TOKEN_TYPE_RIGHT_PAREN && open_parens == 0) curr_index = 12;

        // chyba operand
        if (expect_opd && curr_index != 10 && curr_index != 11) return ERROR_SYNTAX;

        // ( za operandom
        if (!expect_opd && curr_index == 10) return ERROR_SYNTAX;

        // ak sme na konci vyrazu ($), skoncime
        if(top_op == TOKEN_TYPE_EOL && curr_index == 12) {
            break;
        }

        char action = prec_table[top_index][curr_index];

        if (action == '<') {
            // SHIFT: posunieme operator na zasobnik a precitame dalsi token
            res = push_op(s, curr_op);
            if (res != SCANNER_TOKEN_OK) return res;
            if (curr_op == TOKEN_TYPE_LEFT_PAREN) open_parens++;
            expect_opd = true; // po operatori ocakavame operand
            res = next_token();
            if (res != SCANNER_TOKEN_OK) return res;
        }
        else if (action == '=') {
            // MATCH: zahodine '(' zo zasobnika a precitame ')'
            s->op_top--;
            open_parens--;

            // prazdne () = Unit
            if(expect_opd) {
                res = push_type(s, TYPE_UNIT);
                if (res != SCANNER_TOKEN_OK) return res;
            }

            expect_opd = false; // po uzatvoreni zatvorky mame hotovu hodnotu
            res = next_token();
            if (res != SCANNER_TOKEN_OK) return res;
        }
        else if (action == '>') {

            TokenType op = s->ops[s->op_top--]; // zobereme operator
            if (s->type_top < 1) return ERROR_SYNTAX; // chyba, malo operandov

            DataType right = s->types[s->type_top--];
            DataType left = s->types[s->type_top--];
            DataType result;

            // sematicka kontrola pre operator
            res = reduce_operation(op, left, right, &result);
            if (res != SCANNER_TOKEN_OK) return res;

            s->types[++s->type_top] = result; // vysledok dame spat na zasobnik
            expect_opd = false; // vysledok redukcie je operand
        }
        else {
            // chyba v precedencnej tabulke
            return ERROR_SYNTAX;
        }
    }

    // prave jeden vysledny typ na zasobniku by mal ostat
    if (s->type_top != 0) return ERROR_SYNTAX;

    *out_type = s->types[0];
    return SCANNER_TOKEN_OK;

}
    
// Deklaracia a definicia premennej: val x [: Type] = expr  alebo  var x [: Type] = expr
static int parse_var_def(void) {
    bool is_constant = check_kw(KEYWORD_VAL); // zistime ci ide o val (true) alebo var (false)
    int res = next_token(); // preskocime 'val' alebo 'var'
    if (res != SCANNER_TOKEN_OK) return res;

    if (!check(TOKEN_TYPE_IDENTIFIER)) return ERROR_SYNTAX;
    
    // ulozime nazov premennej lebo next_var ho prepise
    char *var_name = str_dup(current_tok.attribute.string);
    if (!var_name) return ERROR_INTERNAL;

    // sematicka kontrola - redefinicia premennej v aktualnom scope
    if(symtable_find_var_current_scope(symtab, var_name) != NULL) {
        free(var_name);
        return ERROR_SEM_REDEF;
    }

    res = next_token();
    if (res != SCANNER_TOKEN_OK) {
        free(var_name);
        return res;
    }
    
    // spracovanie volitelneho typu (este sa len zistuje)
    DataType var_type = TYPE_UNDEF;
    if(check(TOKEN_TYPE_COLON)) {

        res = next_token();
        if (res != SCANNER_TOKEN_OK) {
            free(var_name);
            return res;
        }

        res = parse_type(&var_type);
        if(res != SCANNER_TOKEN_OK) {
            free(var_name);
            return res;
        }
    }

    res = expect(TOKEN_TYPE_ASSIGN);
    if (res != SCANNER_TOKEN_OK) {
        free(var_name);
        return res;
    }

    // spracovanie vyrazu pomocou precedencnej analyzy
    DataType expr_type;
    res = parse_expression(&expr_type);
    if (res != SCANNER_TOKEN_OK) {
        free(var_name);
        return res;
    }

    // kontrola typov
    if (var_type != TYPE_UNDEF) {
        //ak su rozdielne, ale ide o konverziu int na double, je to ok
        if(var_type != expr_type && !(var_type == TYPE_DOUBLE && expr_type == TYPE_INT)) {
            free(var_name);
            return ERROR_SEM_TYPE; // chyba 6
        }
    } else {
        // ak nebol zadany, odvodime z vyrazu
        var_type = expr_type;
    }

    // zakaz ukladanie bool do premennej 
    if(var_type == TYPE_BOOL) {
        free(var_name);
        return ERROR_SEM_TYPE; // chyba 6
    }

    // pridanie do tabulky symbolov
    if(symtable_add_var(symtab, var_name, var_type, is_constant, true) == NULL) {
        free(var_name);
        return ERROR_INTERNAL;
    }

    free(var_name); // symtable urobilo vlastnu kopiu, toto teda mozeme uvolnit
    return expect_stmt_end();
}

// vyraz ako prikaz, vysledok je typ vyrazu
static int parse_expr_statement(StmtResult *out) {
    DataType expr_type;
    int res = parse_expression(&expr_type);
    if (res != SCANNER_TOKEN_OK) return res;

    // bool len v podmienke
    if (expr_type == TYPE_BOOL) return ERROR_SEM_TYPE; // chyba 6

    set_result(out, expr_type);
    return expect_stmt_end();
}

// prikaz s id
static int parse_id_statement(StmtResult *out) {
    // lookahead, za id je vzdy aspon EOF alebo zarazka
    TokenType next_type = tokens[pos + 1].type;

    // samotny vyraz
    if (next_type != TOKEN_TYPE_ASSIGN && next_type != TOKEN_TYPE_LEFT_PAREN) {
        return parse_expr_statement(out);
    }

    // ulozenie nazvu funkcie/premennej pre pouzitie
    char *id_name = str_dup(current_tok.attribute.string);
    if (!id_name) return ERROR_INTERNAL;

    // posun za id
    int res = next_token();
    if (res != SCANNER_TOKEN_OK) {
        free(id_name);
        return res;
    }

    // Priradenie do premennej: x = expr EOL
    if (check(TOKEN_TYPE_ASSIGN)) {

        // Najdenie premennej v tabulke
        Symbol *var = symtable_find_var(symtab, id_name);
        if (!var) {
            free(id_name);
            return ERROR_SEM_UNDEF; // Chyba 3
        }

        // kontrola ci nie je konstantna
        if (var->data.var.is_constant) {
            free(id_name);
            return ERROR_SEM_CONST; // Chyba 7
        }

        // preskocenie '='
        res = next_token();
        if (res != SCANNER_TOKEN_OK) {
            free(id_name);
            return res;
        }

        DataType expr_type;
        res = parse_expression(&expr_type);
        if (res != SCANNER_TOKEN_OK) {
            free(id_name);
            return res;
        }
        
        // kontrola typov (ci sedi typ vyrazu s typom premennej)
        if(var->data.var.type != expr_type) {
            // povolime konverziu Int -> Double
            if(!(var->data.var.type == TYPE_DOUBLE && expr_type == TYPE_INT)) {
                free(id_name);
                return ERROR_SEM_TYPE; // chyba 6
            }

        }

        set_result(out, TYPE_UNIT); // priradenie = Unit
        free(id_name);
        return expect_stmt_end();
    }

    // Samostatne volanie funkcie ako prikaz: foo(arg1, arg2) EOL
    if (check(TOKEN_TYPE_LEFT_PAREN)) {
        // overenie ci funkcia existuje
        Symbol *func = symtable_find_func(symtab, id_name);
        if (!func) {
            free(id_name);
            return ERROR_SEM_UNDEF; // Chyba 3
        }

        res = next_token();
        if (res != SCANNER_TOKEN_OK) {
            free(id_name);
            return res;
        }

        size_t arg_index_count = 0; // pocitadlo argumentov

        if (!check(TOKEN_TYPE_RIGHT_PAREN)) {
            while (1) {
                DataType arg_type;
                res = parse_term(&arg_type);
                if (res != SCANNER_TOKEN_OK) {
                    free(id_name);
                    return res;
                }

                // kontrola poctu a typu argumentov
                if(arg_index_count >= func->data.func.param_count) {
                    free(id_name);
                    return ERROR_SEM_PARAM; 
                }

                DataType expected_type = func->data.func.params[arg_index_count].type;
                if(expected_type != arg_type && expected_type != TYPE_ANY) {
                    if(!(expected_type == TYPE_DOUBLE && arg_type == TYPE_INT)) {
                        free(id_name);
                        return ERROR_SEM_PARAM; 
                    }
                }
                arg_index_count++;

                if (check(TOKEN_TYPE_COMMA)) {
                    res = next_token();
                    if (res != SCANNER_TOKEN_OK) {
                        free(id_name);
                        return res;
                    }
                    // koncova ciarka len pred novym riadkom
                    if (check(TOKEN_TYPE_RIGHT_PAREN) && current_tok.had_preceding_newline) break;
                    continue;
                }
                break;
            }
        }

        // kontrola, ci vsetky argumenty boli poslane
        if (arg_index_count < func->data.func.param_count) {
            free(id_name);
            return ERROR_SEM_PARAM;
        }

        res = expect(TOKEN_TYPE_RIGHT_PAREN);
        if (res != SCANNER_TOKEN_OK){
            free(id_name);
            return res;
        }

        set_result(out, func->data.func.return_type); // vysledok volania
        free(id_name);
        return expect_stmt_end();
    }

    free(id_name); // nedosiahnutelne
    return ERROR_SYNTAX;
}

// Podmienka: if expr then EOL INDENT blok DEDENT else EOL INDENT blok DEDENT
static int parse_if(StmtResult *out) {
    int res = next_token(); // preskocime 'if'
    if (res != SCANNER_TOKEN_OK) return res;

    DataType cond_type;
    res = parse_expression(&cond_type);
    if (res != SCANNER_TOKEN_OK) return res;

    if(cond_type != TYPE_BOOL) return ERROR_SEM_TYPE;

    res = expect_kw(KEYWORD_THEN);
    if (res != SCANNER_TOKEN_OK) return res;

    res = expect(TOKEN_TYPE_EOL);
    if (res != SCANNER_TOKEN_OK) return res;

    StmtResult then_res;
    res = parse_block(NULL, 0, &then_res);
    if (res != SCANNER_TOKEN_OK) return res;

    res = expect_kw(KEYWORD_ELSE);
    if (res != SCANNER_TOKEN_OK) return res;

    res = expect(TOKEN_TYPE_EOL);
    if (res != SCANNER_TOKEN_OK) return res;

    StmtResult else_res;
    res = parse_block(NULL, 0, &else_res);
    if (res != SCANNER_TOKEN_OK) return res;

    // if nie je vyraz, rozhoduju vetvy
    out->type = TYPE_UNIT;
    out->ends_with_if = true;
    out->all_return = then_res.all_return && else_res.all_return;
    out->all_unit = then_res.all_unit && else_res.all_unit;
    return SCANNER_TOKEN_OK;
}

// Cyklus: while expr do EOL INDENT blok DEDENT
static int parse_while(void) {
    int res = next_token(); // preskocime 'while'
    if (res != SCANNER_TOKEN_OK) return res;

    DataType cond_type;
    res = parse_expression(&cond_type);
    if (res != SCANNER_TOKEN_OK) return res;

    if(cond_type != TYPE_BOOL) return ERROR_SEM_TYPE;

    res = expect_kw(KEYWORD_DO);
    if (res != SCANNER_TOKEN_OK) return res;

    res = expect(TOKEN_TYPE_EOL);
    if (res != SCANNER_TOKEN_OK) return res;

    // vysledok tela cyklu sa neprenasa
    StmtResult body_res;
    return parse_block(NULL, 0, &body_res);
}

// Prikaz navratu: return [expr] EOL
static int parse_return(void) {
    int res = next_token(); // preskocime 'return'
    if (res != SCANNER_TOKEN_OK) return res;

    DataType ret_type = TYPE_UNIT; // Predvolene, ak nasleduje EOL

    if (!at_stmt_end()) {
        res = parse_expression(&ret_type);
        if (res != SCANNER_TOKEN_OK) return res;
    }

    // return bez typu v hlavicke
    if (!current_func_explicit_type) return ERROR_SEM_TYPE; // chyba 6

    // bool len v podmienke
    if (ret_type == TYPE_BOOL) return ERROR_SEM_TYPE; // chyba 6

    // kontrola ci sa typ zhoduje s navratovym typom funkcie (pri Unit sa zahodi)
    if(!current_func_explicit_unit) {
        // Ak sa typy nezhoduju a neni to konverzia Int -> Double
        if(current_func_return_type != ret_type && 
         !(current_func_return_type == TYPE_DOUBLE && ret_type == TYPE_INT)) {
            return ERROR_SEM_TYPE; // chyba 6
        }
    }


    return expect_stmt_end();
}

// Spracovanie jedneho prikazu v bloku, out = vysledok prikazu
static int parse_statement(StmtResult *out) {
    // definicia a cyklus = Unit
    set_result(out, TYPE_UNIT);

    if (check_kw(KEYWORD_VAL) || check_kw(KEYWORD_VAR)) {
        return parse_var_def();
    }
    if (check_kw(KEYWORD_IF)) {
        return parse_if(out);
    }
    if (check_kw(KEYWORD_WHILE)) {
        return parse_while();
    }
    if (check_kw(KEYWORD_RETURN)) {
        out->all_return = true; // vetva konci return
        out->all_unit = false;
        return parse_return();
    }
    if (check(TOKEN_TYPE_IDENTIFIER)) {
        return parse_id_statement(out);
    }

    // Samostatne stojaci vyraz (napr. cislo)
    if (check(TOKEN_TYPE_INT_NUMBER) || check(TOKEN_TYPE_DOUBLE_NUMBER) ||
        check(TOKEN_TYPE_STRING) || check(TOKEN_TYPE_LEFT_PAREN)) {
        return parse_expr_statement(out);
    }

    // unarne +/- len za ;, riadok nesmie zacinat operatorom
    if (after_semicolon && (check(TOKEN_TYPE_PLUS) || check(TOKEN_TYPE_MINUS))) {
        return parse_expr_statement(out);
    }
    return ERROR_SYNTAX;
}

// Spracovanie bloku prikazov ohraniceneho INDENT a DEDENT
// out = vysledok posledneho prikazu priamo v bloku
static int parse_block(Param *params, size_t param_count, StmtResult *out) {
    int res = expect(TOKEN_TYPE_INDENT);
    if (res != SCANNER_TOKEN_OK) return res;

    symtable_push_scope(symtab);

    // vlozenie parametrov do lokalneho scope
    if(params != NULL) {
        for(size_t i = 0; i < param_count; i++) {
            // parametre vzdy incializovane a konstantne
            if(symtable_add_var(symtab, params[i].name, params[i].type, true, true) == NULL) {
                symtable_pop_scope(symtab);
                return ERROR_INTERNAL;
            }
        }
    }
    bool has_statements = false;
    after_semicolon = false; // novy riadok

    while (!check(TOKEN_TYPE_DEDENT) && !check(TOKEN_TYPE_EOF)) {
        if (check(TOKEN_TYPE_EOL)) {
            after_semicolon = false; // novy riadok
            res = next_token();
            if (res != SCANNER_TOKEN_OK) goto cleanup;
            continue;
        }

        has_statements = true;
        res = parse_statement(out); // ; spracuje prikaz, out prepise dalsi
        if (res != SCANNER_TOKEN_OK) goto cleanup;
    }
    if(!has_statements) {
        symtable_pop_scope(symtab);
        return ERROR_SYNTAX;
    }

    res = expect(TOKEN_TYPE_DEDENT);

cleanup:
    symtable_pop_scope(symtab);
    return res;
}

// uvolni parametre
static void free_params(Param *params, size_t count) {
    if (!params) return;
    for (size_t i = 0; i < count; i++) free(params[i].name);
    free(params);
}

// Spracovanie zoznamu formalnych parametrov funkcie: ( [ id : Type , ... ] )
// pole alokuje, uvolnuje volajuci cez free_params
static int parse_params(Param **out_params, size_t *param_count) {
    *out_params = NULL;
    *param_count = 0; // inicializacia poctu parametrov na 0

    Param *params = NULL;
    size_t count = 0;
    size_t capacity = 0;

    int res = expect(TOKEN_TYPE_LEFT_PAREN);
    if (res != SCANNER_TOKEN_OK) return res;

    // prazdny zoznam parametrov
    if (check(TOKEN_TYPE_RIGHT_PAREN)) {
        return next_token();
    }

    while (1) {
        // nacitanie mena parametra
        if(!check(TOKEN_TYPE_IDENTIFIER)) {
            res = ERROR_SYNTAX;
            goto error;
        }

        // duplicitny parameter
        for (size_t i = 0; i < count; i++) {
            if (strcmp(params[i].name, current_tok.attribute.string) == 0) {
                res = ERROR_SEM_REDEF; // chyba 4
                goto error;
            }
        }

        // zvacsit pole
        if (count == capacity) {
            size_t new_capacity = capacity ? capacity * 2 : 4;
            Param *tmp = realloc(params, new_capacity * sizeof(Param));
            if (!tmp) {
                res = ERROR_INTERNAL;
                goto error;
            }
            params = tmp;
            capacity = new_capacity;
        }

        // ulozenie mena parametra
        params[count].name = str_dup(current_tok.attribute.string);
        if (!params[count].name) {
            res = ERROR_INTERNAL;
            goto error;
        }
        params[count].type = TYPE_UNDEF;
        count++; // zvysenie poctu parametrov

        res = next_token();
        if (res != SCANNER_TOKEN_OK) goto error;

        // dvojbodka
        res = expect(TOKEN_TYPE_COLON);
        if (res != SCANNER_TOKEN_OK) goto error;

        // typ parametra
        res = parse_type(&params[count - 1].type);
        if (res != SCANNER_TOKEN_OK) goto error;

        // ciarka alebo koniec
        if(check(TOKEN_TYPE_COMMA)) {
            res = next_token();
            if (res != SCANNER_TOKEN_OK) goto error;

            // koncova ciarka len pred novym riadkom
            if(check(TOKEN_TYPE_RIGHT_PAREN)) {
                if (!current_tok.had_preceding_newline) {
                    res = ERROR_SYNTAX;
                    goto error;
                }
                break;
            }
            continue; // ide sa na dalsi parameter
        }
        break; // ak nie je ciarka, ocakava sa koniec zatvorky
    }

    res = expect(TOKEN_TYPE_RIGHT_PAREN);
    if (res != SCANNER_TOKEN_OK) goto error;

    *out_params = params;
    *param_count = count;
    return SCANNER_TOKEN_OK;

error:
    free_params(params, count);
    return res;
}

// kontrola vysledku tela funkcie (2.3), pri funkcii bez typu ho odvodi do inferred
static int check_body_result(const StmtResult *body, DataType return_type,
                             bool explicit_type, bool explicit_unit, DataType *inferred) {
    *inferred = return_type;

    // explicitny Unit, hodnota sa zahodi
    if (explicit_unit) return SCANNER_TOKEN_OK;

    // telo konci if
    if (body->ends_with_if) {
        // s typom musia vsetky vetvy koncit return
        if (explicit_type) return body->all_return ? SCANNER_TOKEN_OK : ERROR_SEM_TYPE;

        // bez typu musia byt vsetky vetvy Unit
        if (!body->all_unit) return ERROR_SEM_TYPE; // chyba 6
        *inferred = TYPE_UNIT;
        return SCANNER_TOKEN_OK;
    }

    // telo konci return, typ uz overil parse_return
    if (body->all_return) return SCANNER_TOKEN_OK;

    // neznamy typ volanej funkcie
    if (body->type == TYPE_UNDEF) {
        if (!explicit_type) *inferred = TYPE_UNDEF;
        return SCANNER_TOKEN_OK;
    }

    if (explicit_type) {
        return is_compatible(return_type, body->type) ? SCANNER_TOKEN_OK : ERROR_SEM_TYPE;
    }

    // bez typu: typ posledneho prikazu
    *inferred = body->type;
    return SCANNER_TOKEN_OK;
}

// Definicia funkcie: [ @main ] def id ( parametre ) : Typ = EOL INDENT blok DEDENT
static int parse_function(bool is_main) {

    int res = expect_kw(KEYWORD_DEF);
    if (res != SCANNER_TOKEN_OK) return res;

    if (!check(TOKEN_TYPE_IDENTIFIER)) return ERROR_SYNTAX;
    
    // ulozenie nazvu funkcie
    char *func_name = str_dup(current_tok.attribute.string);
    if (!func_name) return ERROR_INTERNAL;

    // sematicka kontrola - redefinicia funkcie
    Symbol *existing_func = symtable_find_func(symtab, func_name);
    bool is_from_first_pass = false;
    if (existing_func != NULL) {
        if (existing_func->data.func.is_defined) {
            free(func_name);
            return ERROR_SEM_REDEF; // Chyba 4
        }
        // existuje z prveho priechodu, potvrdime definiciu
        existing_func->data.func.is_defined = true;
        is_from_first_pass = true;
    }

    res = next_token();
    if (res != SCANNER_TOKEN_OK) {
        free(func_name);
        return res;
    }

    // dynamicke pole parametrov
    Param *temp_params = NULL;
    size_t param_count = 0;

    res = parse_params(&temp_params, &param_count);
    if (res != SCANNER_TOKEN_OK) {
        free(func_name);
        return res;
    }

    // ulozenie navratoveho type (nepovinny)
    DataType return_type = TYPE_UNDEF;
    if (check(TOKEN_TYPE_COLON)) {
        res = next_token(); // preskocime ':'
        if (res != SCANNER_TOKEN_OK) {
            free(func_name);
            free_params(temp_params, param_count);
            return res;
        }

        res = parse_type(&return_type);
        if (res != SCANNER_TOKEN_OK) {
            free(func_name);
            free_params(temp_params, param_count);
            return res;
        }
    }
    // Unit v hlavicke
    bool explicit_unit = (return_type == TYPE_UNIT);
    bool explicit_type = (return_type != TYPE_UNDEF);

    // sematicka kontrola - @main
    if(is_main) {
        if(param_count > 0) {
            free(func_name);
            free_params(temp_params, param_count);
            return ERROR_SEM_PARAM; // Chyba 5
        }
        if(return_type != TYPE_UNIT && return_type != TYPE_UNDEF) {
            free(func_name);
            free_params(temp_params, param_count);
            return ERROR_SEM_TYPE; // Chyba 6
        }
        if(return_type == TYPE_UNDEF) return_type = TYPE_UNIT; // odvodeny Unit
    }

    res = expect(TOKEN_TYPE_ASSIGN);
    if (res != SCANNER_TOKEN_OK) {
        free(func_name);
        free_params(temp_params, param_count);
        return res;
    }

    // pridanie do symtable (iba ak nie je z prveho priechodu)
    Symbol *func_sym = existing_func;
    if (!is_from_first_pass) {
        func_sym = symtable_add_func(symtab, func_name, return_type, param_count, temp_params, true, false);
        if (!func_sym) {
            free(func_name);
            free_params(temp_params, param_count);
            return ERROR_INTERNAL;
        }
    }
    free(func_name); // symtable urobilo kopiu, mozeme uvolnit

    // Ulozenie navratoveho typu pre prikazy 'return' v tele funkcie
    current_func_return_type = return_type;
    current_func_explicit_unit = explicit_unit;
    current_func_explicit_type = explicit_type;

    // spracovanie tela funkcie
    int block_res;
    // ak nasleduje EOL, ide o viacriadkovu funkciu
    if(check(TOKEN_TYPE_EOL)) {
        res = next_token();
        if (res != SCANNER_TOKEN_OK) {
            free_params(temp_params, param_count);
            return res;
        }
        StmtResult body;
        block_res = parse_block(temp_params, param_count, &body);

        // vysledok tela
        if (block_res == SCANNER_TOKEN_OK) {
            DataType inferred;
            block_res = check_body_result(&body, return_type, explicit_type, explicit_unit, &inferred);

            // @main bez typu musi mat vysledok Unit
            if (block_res == SCANNER_TOKEN_OK && is_main && !explicit_type &&
                inferred != TYPE_UNIT && inferred != TYPE_UNDEF) {
                block_res = ERROR_SEM_TYPE; // chyba 6
            }

            // ulozenie odvodeneho typu
            if (block_res == SCANNER_TOKEN_OK && !explicit_type && !is_main) {
                func_sym->data.func.return_type = inferred;
            }
        }
    }

    // inak to je jednoriadkova funkcia
    else {
        // vytvorime scope pre telo jednoriadkovej funkcie
        symtable_push_scope(symtab);

        // vlozenie parametrov do tohto scope
        for(size_t i = 0 ; i < param_count; i++) {
            if(symtable_add_var(symtab, temp_params[i].name, temp_params[i].type, true, true) == NULL) {
                symtable_pop_scope(symtab);
                free_params(temp_params, param_count);
                return ERROR_INTERNAL;
            }
        }

        DataType expr_type;
        res = parse_expression(&expr_type);
        if (res != SCANNER_TOKEN_OK) {
            symtable_pop_scope(symtab);
            free_params(temp_params, param_count);
            return res;
        }

        // bool len v podmienke
        if(expr_type == TYPE_BOOL) {
            symtable_pop_scope(symtab);
            free_params(temp_params, param_count);
            return ERROR_SEM_TYPE; // chyba 6
        }

        // typova kontrola navratoveho typu (pri Unit sa zahodi)
        if(return_type != TYPE_UNDEF && !explicit_unit) {
            if(return_type != expr_type && !(return_type == TYPE_DOUBLE && expr_type == TYPE_INT)) {
                symtable_pop_scope(symtab);
                free_params(temp_params, param_count);
                return ERROR_SEM_TYPE; // chyba 6
            }
        }

        // ulozenie odvodeneho typu
        if (!explicit_type && !is_main) func_sym->data.func.return_type = expr_type;

        block_res = expect(TOKEN_TYPE_EOL);

        symtable_pop_scope(symtab);
        }

    
    // uvolnenie docasnych parametrov
    free_params(temp_params, param_count);

    return block_res;
}

// Pomocna funkcia na preskocenie tela funkcie (blok)
static int skip_block(void) {
    // ak nasleduje EOL, ide o viac riadkovu funkciu
    if(check(TOKEN_TYPE_EOL)) {
        int res = next_token(); // preskocime EOL
        if (res != SCANNER_TOKEN_OK) return res;

        res = expect(TOKEN_TYPE_INDENT);
        if (res != SCANNER_TOKEN_OK) return res;

        int depth = 1;
        while (depth > 0 && !check(TOKEN_TYPE_EOF)) {
            if (check(TOKEN_TYPE_INDENT)) depth++;
            else if (check(TOKEN_TYPE_DEDENT)) depth--;
            res = next_token();
            if (res != SCANNER_TOKEN_OK) return res;
        }
        return SCANNER_TOKEN_OK;
    }
    
    // ak tam nie je EOL, ide o jednoriadkovu funkciu, preskocime vsetko az do konca riadku
    else {
        while (!check(TOKEN_TYPE_EOL) && !check(TOKEN_TYPE_EOF)) {
            int res = next_token();
            if (res != SCANNER_TOKEN_OK) return res;
        }
        return expect(TOKEN_TYPE_EOL);
    }
}
// Prvy priechod, zbieraju su hlavicky funkcii
int parse_headers(Symtable *st) {
    symtab = st;

    // cely vstup do pola tokenov
    int res = tokenize();
    if (res != SCANNER_TOKEN_OK) return res;

    res = first_token();
    if (res != SCANNER_TOKEN_OK) return res;

    while (!check(TOKEN_TYPE_EOF)) {
        if(check(TOKEN_TYPE_EOL)) {
            res = next_token();
            if (res != SCANNER_TOKEN_OK) return res;
            continue;
        }

        // Preskocenie importov
        if (check_kw(KEYWORD_IMPORT)) {
            while (!check(TOKEN_TYPE_EOL) && !check(TOKEN_TYPE_EOF)) {
                res = next_token();
                if(res != SCANNER_TOKEN_OK) return res;
            }
            continue;
        }

        // ak vidime @main, preskocime ho
        if (check(TOKEN_TYPE_MAIN)) {
            res = next_token();
            if (res != SCANNER_TOKEN_OK) return res;
            res = skip_eols(); // @main na riadku
            if (res != SCANNER_TOKEN_OK) return res;
        }

        if (check_kw(KEYWORD_DEF)) {
            res = next_token();
            if (res != SCANNER_TOKEN_OK) return res;

            if(!check(TOKEN_TYPE_IDENTIFIER)) return ERROR_SYNTAX;

            char *func_name = str_dup(current_tok.attribute.string);
            res = next_token();
            if (res != SCANNER_TOKEN_OK) {
                free(func_name);
                return res;
            }

            // kontrola redefinicie
            if (symtable_find_func(symtab, func_name) != NULL) {
                free(func_name);
                return ERROR_SEM_REDEF;
            }

            Param *temp_params = NULL;
            size_t param_count = 0;
            res = parse_params(&temp_params, &param_count);
            if (res != SCANNER_TOKEN_OK) {
                free(func_name);
                return res;
            }
            // ulozenie navratoveho typu (nepovinny)
            DataType return_type = TYPE_UNDEF;
            if (check(TOKEN_TYPE_COLON)) {
                res = next_token(); // preskocime ':'
                if (res != SCANNER_TOKEN_OK) {
                    free(func_name);
                    free_params(temp_params, param_count);
                    return res;
                }

                res = parse_type(&return_type);
                if (res != SCANNER_TOKEN_OK) {
                    free(func_name);
                    free_params(temp_params, param_count);
                    return res;
                }
            }
            // Ulozenie hlavicky do tabulky
            if (symtable_add_func(symtab, func_name, return_type, param_count, temp_params, false, false) == NULL) {
                free(func_name);
                free_params(temp_params, param_count);
                return ERROR_INTERNAL;
            }

            free(func_name);
            free_params(temp_params, param_count);

            res = expect(TOKEN_TYPE_ASSIGN);
            if (res != SCANNER_TOKEN_OK) return res;

            // Preskocenie tela funkcie
            res = skip_block();
            if (res != SCANNER_TOKEN_OK) return res;
        } else {
            return ERROR_SYNTAX;
        }   
    }
    return ERROR_OK;
}
// Hlavny vstupny bod parsera: spracuje postupnost funkcii
int parse_program(Symtable *st) {
    symtab = st;
    int main_count = 0; // pocitadlo vyskytu @main

    // druhy priechod od zaciatku pola
    int res = first_token();
    if (res != SCANNER_TOKEN_OK) return res;

    // preskocenie prazdnych riadkov na zaciatku
    while (check(TOKEN_TYPE_EOL)) {
        res = next_token();
        if (res != SCANNER_TOKEN_OK) return res;
    }
    
    // povinny prolog import ifj26*
    if (!check_kw(KEYWORD_IMPORT))  return ERROR_SYNTAX; // chyba 2

    res = next_token();
    if(res != SCANNER_TOKEN_OK) return res;

    // Ocakavame 'ifj26'
    if(!check(TOKEN_TYPE_IDENTIFIER) || strcmp(current_tok.attribute.string, "ifj26") != 0) return ERROR_SYNTAX;

    res = next_token();
    if(res != SCANNER_TOKEN_OK) return res;

    // ocakavame '.'
    if(!check(TOKEN_TYPE_DOT)) return ERROR_SYNTAX;

    res = next_token();
    if(res != SCANNER_TOKEN_OK) return res;

    // ocakavame '*'
    if(!check(TOKEN_TYPE_MUL)) return ERROR_SYNTAX;

    res = next_token();
    if(res != SCANNER_TOKEN_OK) return res;

    // koniec riadku za prologom
    res = expect(TOKEN_TYPE_EOL);
    if(res != SCANNER_TOKEN_OK) return res;

    // spracovanie zvysku programu
    while (!check(TOKEN_TYPE_EOF)) {
        if(check(TOKEN_TYPE_EOL)) {
            res = next_token();
            if (res != SCANNER_TOKEN_OK) return res;
            continue;
        }

        // ak by sa vyskytol import, je to chyba
        if (check_kw(KEYWORD_IMPORT)) {
            return ERROR_SYNTAX;
        }

        if (check(TOKEN_TYPE_MAIN)) {
            main_count++;
            if(main_count > 1) return ERROR_SEM_REDEF; // Chyba 4: viacero @main
            res = next_token();
            if (res != SCANNER_TOKEN_OK) return res;
            res = skip_eols(); // @main na riadku
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

    // overime ci main vobec existoval
    if (main_count == 0) return ERROR_SEM_UNDEF; // Chyba 3: @main neexistuje

    return ERROR_OK;
}

// uvolni pole tokenov
void parser_free(void) {
    for (size_t i = 0; i < token_count; i++) free_token_attribute(&tokens[i]);
    free(tokens);
    tokens = NULL;
    token_count = 0;
    token_cap = 0;
    pos = 0;
    lex_error = SCANNER_TOKEN_OK;
}
