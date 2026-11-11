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

#define MAX_EXPR_DEPTH 100

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

static Token current_tok;

// Ukazovatel na tabulku symbolov
static Symtable *symtab = NULL;

// aktualny navratovy typ, v ktorej sa nachadzame
static DataType current_func_return_type = TYPE_UNDEF;

// explicitny Unit
static bool current_func_explicit_unit = false;

// typ v hlavicke
static bool current_func_explicit_type = false;

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
    if (check(TOKEN_TYPE_SEMICOLON)) return next_token();
    return expect(TOKEN_TYPE_EOL);
}

// Prototypy pravidiel rekurzivneho zostupu
static int parse_function(bool is_main);
static int parse_params(Param **out_params, size_t *param_count);
static int parse_block(Param *params, size_t param_count);
static int parse_statement(void);
static int parse_var_def(void);
static int parse_id_statement(void);
static int parse_if(void);
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

// precedencna analyza vyrazou
static int parse_expression(DataType *out_type) {

    // zasobniky
    TokenType op_stack[MAX_EXPR_DEPTH];
    DataType type_stack[MAX_EXPR_DEPTH];
    int op_top = -1;
    int type_top = -1;

    // koniec vyrazu na spodok zasobnika ($)
    op_stack[++op_top] = TOKEN_TYPE_EOL;

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

            DataType t;
            int res = parse_term(&t); // nacitanie operandu
            if (res != SCANNER_TOKEN_OK) return res;

            type_stack[++type_top] = t;
            expect_opd = false; // po operande uz ocakavame operator
            continue; 
        }

        // ak je na vstupe operator (alebo koniec)
        TokenType curr_op = current_tok.type;

        // zistime co je na vrchu zasobnika
        TokenType top_op = op_stack[op_top];

        // ziskame indexy pre precedencnu tabulku
        int top_index = get_op_index(top_op);
        int curr_index = get_op_index(curr_op);

        // ak je nieco, co neni v tabulke, vezmeme to ako koniec vyrazu
        if (curr_index == -1 ) curr_index = 12; // EOL

        // cudzia ) je koniec
        if (curr_op == TOKEN_TYPE_RIGHT_PAREN && open_parens == 0) curr_index = 12;

        // ak sme na konci vyrazu ($), skoncime
        if(top_op == TOKEN_TYPE_EOL && curr_index == 12) {
            break;
        }

        char action = prec_table[top_index][curr_index];

        if (action == '<') {
            // SHIFT: posunieme operator na zasobnik a precitame dalsi token
            op_stack[++op_top] = curr_op;
            if (curr_op == TOKEN_TYPE_LEFT_PAREN) open_parens++;
            expect_opd = true; // po operatori ocakavame operand
            int res = next_token();
            if (res != SCANNER_TOKEN_OK) return res;
        }
        else if (action == '=') {
            // MATCH: zahodine '(' zo zasobnika a precitame ')'
            op_top--;
            open_parens--;

            // osetrenie prazdnych zatvoriek
            if(type_top < op_top) {
                type_stack[++type_top] = TYPE_UNIT;
            }

            expect_opd = false; // po uzatvoreni zatvorky mame hotovu hodnotu
            int res = next_token();
            if (res != SCANNER_TOKEN_OK) return res;
        }
        else if (action == '>') {

            TokenType op = op_stack[op_top--]; // zobereme operator
            if (type_top < 1) return ERROR_SYNTAX; // chyba, malo operandov

            DataType right = type_stack[type_top--]; 
            DataType left = type_stack[type_top--];
            DataType result;
            
            // sematicka kontrola pre operator
            int res = reduce_operation(op, left, right, &result);
            if (res != SCANNER_TOKEN_OK) return res;

            type_stack[++type_top] = result; // vysledok dame spat na zasobnik
            expect_opd = false; // vysledok redukcie je operand
        }
        else {
            // chyba v precedencnej tabulke
            return ERROR_SYNTAX;
        }
    }

    // prave jeden vysledny typ na zasobniku by mal ostat
    if (type_top != 0) return ERROR_SYNTAX;
    
    *out_type = type_stack[0];
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

        if(check_kw(KEYWORD_INT)) var_type = TYPE_INT;
        else if(check_kw(KEYWORD_DOUBLE)) var_type = TYPE_DOUBLE;
        else if(check_kw(KEYWORD_STRING)) var_type = TYPE_STRING;
        else if(check_kw(KEYWORD_UNIT)) var_type = TYPE_UNIT;
        else {
            free(var_name);
            return ERROR_SYNTAX;
        }

        res = next_token();
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

// vyraz ako prikaz
static int parse_expr_statement(void) {
    DataType expr_type;
    int res = parse_expression(&expr_type);
    if (res != SCANNER_TOKEN_OK) return res;

    // bool len v podmienke
    if (expr_type == TYPE_BOOL) return ERROR_SEM_TYPE; // chyba 6

    return expect_stmt_end();
}

// prikaz s id
static int parse_id_statement(void) {
    // lookahead
    Token next_tok;
    int res = get_token(&next_tok);
    if (res != SCANNER_TOKEN_OK) return res;

    // samotny vyraz
    if (next_tok.type != TOKEN_TYPE_ASSIGN && next_tok.type != TOKEN_TYPE_LEFT_PAREN) {
        // vratit token
        res = unget_token(next_tok);
        if (res != SCANNER_TOKEN_OK) return res;
        return parse_expr_statement();
    }

    // ulozenie nazvu funkcie/premennej pre pouzitie
    char *id_name = str_dup(current_tok.attribute.string);
    if (!id_name) {
        free_token_attribute(&next_tok);
        return ERROR_INTERNAL;
    }

    // posun za id
    free_token_attribute(&current_tok);
    current_tok = next_tok;

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

        free(id_name);
        return expect_stmt_end();
    }

    free(id_name); // nedosiahnutelne
    return ERROR_SYNTAX;
}

// Podmienka: if expr then EOL INDENT blok DEDENT else EOL INDENT blok DEDENT
static int parse_if(void) {
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

    res = parse_block(NULL, 0);
    if (res != SCANNER_TOKEN_OK) return res;

    res = expect_kw(KEYWORD_ELSE);
    if (res != SCANNER_TOKEN_OK) return res;

    res = expect(TOKEN_TYPE_EOL);
    if (res != SCANNER_TOKEN_OK) return res;
    
    return parse_block(NULL, 0);
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

    return parse_block(NULL, 0);
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

    // Samostatne stojaci vyraz (napr. cislo)
    if (check(TOKEN_TYPE_INT_NUMBER) || check(TOKEN_TYPE_DOUBLE_NUMBER) ||
        check(TOKEN_TYPE_STRING) || check(TOKEN_TYPE_LEFT_PAREN) ||
        check(TOKEN_TYPE_PLUS) || check(TOKEN_TYPE_MINUS)) {
        return parse_expr_statement();
    }
    return ERROR_SYNTAX;
}

// Spracovanie bloku prikazov ohraniceneho INDENT a DEDENT
static int parse_block(Param *params, size_t param_count) {
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

    while (!check(TOKEN_TYPE_DEDENT) && !check(TOKEN_TYPE_EOF)) {
        if (check(TOKEN_TYPE_EOL)) {
            res = next_token();
            if (res != SCANNER_TOKEN_OK) goto cleanup;
            continue;
        }

        has_statements = true;
        res = parse_statement(); // ; spracuje prikaz
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
        if(check_kw(KEYWORD_INT)) params[count - 1].type = TYPE_INT;
        else if(check_kw(KEYWORD_DOUBLE)) params[count - 1].type = TYPE_DOUBLE;
        else if(check_kw(KEYWORD_STRING)) params[count - 1].type = TYPE_STRING;
        else if(check_kw(KEYWORD_UNIT)) params[count - 1].type = TYPE_UNIT;
        else {
            res = ERROR_SYNTAX;
            goto error;
        }

        res = next_token();
        if (res != SCANNER_TOKEN_OK) goto error;

        // ciarka alebo koniec
        if(check(TOKEN_TYPE_COMMA)) {
            res = next_token();
            if (res != SCANNER_TOKEN_OK) goto error;

            // osetrenie koncovej ciarky, ak nasleduje ), cyklus sa skonci
            if(check(TOKEN_TYPE_RIGHT_PAREN)) {
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

        if(check_kw(KEYWORD_INT)) return_type = TYPE_INT;
        else if(check_kw(KEYWORD_DOUBLE)) return_type = TYPE_DOUBLE;
        else if(check_kw(KEYWORD_STRING)) return_type = TYPE_STRING;
        else if(check_kw(KEYWORD_UNIT)) return_type = TYPE_UNIT;
        else {
            free(func_name);
            free_params(temp_params, param_count);
            return ERROR_SYNTAX;
        }

        res = next_token();
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
    if (!is_from_first_pass) {
        Symbol *sym = symtable_add_func(symtab, func_name, return_type, param_count, temp_params, true, false);
        if (!sym) {
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
        block_res = parse_block(temp_params, param_count);
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
    int res = next_token();
    if (res != SCANNER_TOKEN_OK && res != TOKEN_TYPE_EOF) return res;

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

                if (check_kw(KEYWORD_INT)) return_type = TYPE_INT;
                else if (check_kw(KEYWORD_DOUBLE)) return_type = TYPE_DOUBLE;
                else if (check_kw(KEYWORD_STRING)) return_type = TYPE_STRING;
                else if (check_kw(KEYWORD_UNIT)) return_type = TYPE_UNIT;
                else {
                    free(func_name);
                    free_params(temp_params, param_count);
                    return ERROR_SYNTAX;
                }

                res = next_token();
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

    int res = next_token();
    if (res != SCANNER_TOKEN_OK && res != TOKEN_TYPE_EOF) {
        return res;
    }

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

    free_token_attribute(&current_tok);
    return ERROR_OK;
}
