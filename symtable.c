/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file symtable.c
 * @brief Implementacia tabulky symbolov (Symtable) pre jazyk IFJ26.
 */

#include <stdlib.h>
#include <string.h>
#include "symtable.h"
#include "utils.h"

// Uvolnenie pamate alokovaneho symbolu a jeho parametrov
static void free_symbol(void *ptr) {
    if (!ptr) return;
    Symbol *sym = (Symbol *)ptr;
    if (sym->name) {
        free(sym->name);
    }
    if (sym->kind == SYM_FUNCTION && sym->data.func.params) {
        for (size_t i = 0; i < sym->data.func.param_count; i++) {
            if (sym->data.func.params[i].name) {
                free(sym->data.func.params[i].name);
            }
        }
        free(sym->data.func.params);
    }
    free(sym);
}

// Inicializacia prazdnej tabulky symbolov
void symtable_init(Symtable *st) {
    if (!st) return;
    ht_init(&st->global_table);
    st->current_scope = NULL;
}

// Uvolnenie vsetkych zdrojov tabulky symbolov
void symtable_free(Symtable *st) {
    if (!st) return;
    while (st->current_scope) {
        symtable_pop_scope(st);
    }
    ht_clear(&st->global_table, free_symbol);
}

// Vytvorenie a otvorenie noveho lokalneho ramca
bool symtable_push_scope(Symtable *st) {
    if (!st) return false;
    Scope *new_scope = (Scope *)malloc(sizeof(Scope));
    if (!new_scope) return false;

    ht_init(&new_scope->table);
    new_scope->parent = st->current_scope;
    st->current_scope = new_scope;
    return true;
}

// Uzatvorenie a uvolnenie aktualneho lokalneho ramca
void symtable_pop_scope(Symtable *st) {
    if (!st || !st->current_scope) return;
    Scope *top = st->current_scope;
    st->current_scope = top->parent;
    ht_clear(&top->table, free_symbol);
    free(top);
}

// Pridanie premennej do aktualneho lokalneho ramca
Symbol *symtable_add_var(Symtable *st, const char *name, DataType type, bool is_constant, bool is_initialized) {
    if (!st || !st->current_scope || !name) return NULL;

    Symbol *sym = (Symbol *)malloc(sizeof(Symbol));
    if (!sym) return NULL;

    sym->name = str_dup(name);
    if (!sym->name) {
        free(sym);
        return NULL;
    }
    sym->kind = SYM_VARIABLE;
    sym->data.var.type = type;
    sym->data.var.is_constant = is_constant;
    sym->data.var.is_initialized = is_initialized;

    if (!ht_insert(&st->current_scope->table, name, sym)) {
        free_symbol(sym);
        return NULL;
    }
    return sym;
}

// Vyhladanie premennej v najvnutornejsom aktualnom ramci
Symbol *symtable_find_var_current_scope(const Symtable *st, const char *name) {
    if (!st || !st->current_scope || !name) return NULL;
    HTItem *item = ht_search(&st->current_scope->table, name);
    return item ? (Symbol *)item->value : NULL;
}

// Vyhladanie premennej postupne cez vsetky viditelne ramce (od aktualneho k vonkajsim)
Symbol *symtable_find_var(const Symtable *st, const char *name) {
    if (!st || !name) return NULL;
    for (Scope *sc = st->current_scope; sc != NULL; sc = sc->parent) {
        HTItem *item = ht_search(&sc->table, name);
        if (item) {
            return (Symbol *)item->value;
        }
    }
    return NULL;
}

// Pridanie funkcie do globalnej tabulky
Symbol *symtable_add_func(Symtable *st, const char *name, DataType return_type, size_t param_count, const Param *params, bool is_defined, bool is_builtin) {
    if (!st || !name) return NULL;

    Symbol *sym = (Symbol *)malloc(sizeof(Symbol));
    if (!sym) return NULL;

    sym->name = str_dup(name);
    if (!sym->name) {
        free(sym);
        return NULL;
    }
    sym->kind = SYM_FUNCTION;
    sym->data.func.return_type = return_type;
    sym->data.func.param_count = param_count;
    sym->data.func.is_defined = is_defined;
    sym->data.func.is_builtin = is_builtin;
    sym->data.func.params = NULL;

    if (param_count > 0 && params) {
        sym->data.func.params = (Param *)malloc(sizeof(Param) * param_count);
        if (!sym->data.func.params) {
            free_symbol(sym);
            return NULL;
        }
        for (size_t i = 0; i < param_count; i++) {
            sym->data.func.params[i].name = str_dup(params[i].name);
            sym->data.func.params[i].type = params[i].type;
        }
    }

    if (!ht_insert(&st->global_table, name, sym)) {
        free_symbol(sym);
        return NULL;
    }
    return sym;
}

// Vyhladanie funkcie v globalnej tabulke
Symbol *symtable_find_func(const Symtable *st, const char *name) {
    if (!st || !name) return NULL;
    HTItem *item = ht_search(&st->global_table, name);
    return item ? (Symbol *)item->value : NULL;
}

// Prevod DataType na citatelny retazec
const char *datatype_to_string(DataType type) {
    switch (type) {
        case TYPE_INT:    return "Int";
        case TYPE_DOUBLE: return "Double";
        case TYPE_STRING: return "String";
        case TYPE_UNIT:   return "Unit";
        case TYPE_ANY:    return "Any";
        case TYPE_BOOL:   return "Boolean";
        case TYPE_UNDEF:
        default:          return "Undef";
    }
}
