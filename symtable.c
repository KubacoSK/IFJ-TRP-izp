/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 * Autori:
  * @author xodrasa00, Aleš Odráška
  * @author xgazdaa00, Adam Gazdarica
  * @author xkrpeld00, Dominik Krpelan
  * @author xpetraj00, Jakub Petrán
 * 
 * @file symtable.c
 * @brief Implementacia tabulky symbolov (Symtable) pre jazyk IFJ26.
 */

#include "symtable.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

// Uvolnenie pamate alokovaneho symbolu a jeho parametrov
static void free_symbol(void *ptr) {
  if (!ptr)
    return;
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
  if (!st)
    return;
  st->next_var_id = 1;
  ht_init(&st->global_table);
  st->current_scope = NULL;
}

// Uvolnenie vsetkych zdrojov tabulky symbolov
void symtable_free(Symtable *st) {
  if (!st)
    return;
  while (st->current_scope) {
    symtable_pop_scope(st);
  }
  ht_clear(&st->global_table, free_symbol);
}

// Vytvorenie a otvorenie noveho lokalneho ramca
bool symtable_push_scope(Symtable *st) {
  if (!st)
    return false;
  Scope *new_scope = (Scope *)malloc(sizeof(Scope));
  if (!new_scope)
    return false;

  ht_init(&new_scope->table);
  new_scope->parent = st->current_scope;
  st->current_scope = new_scope;
  return true;
}

// Uzatvorenie a uvolnenie aktualneho lokalneho ramca
void symtable_pop_scope(Symtable *st) {
  if (!st || !st->current_scope)
    return;
  Scope *top = st->current_scope;
  st->current_scope = top->parent;
  ht_clear(&top->table, free_symbol);
  free(top);
}

// Pridanie premennej do aktualneho lokalneho ramca
Symbol *symtable_add_var(Symtable *st, const char *name, DataType type,
                         bool is_constant, bool is_initialized) {
  if (!st || !st->current_scope || !name)
    return NULL;

  Symbol *sym = (Symbol *)malloc(sizeof(Symbol));
  if (!sym)
    return NULL;

  sym->name = str_dup(name);
  if (!sym->name) {
    free(sym);
    return NULL;
  }
  sym->data.var.id = st->next_var_id++;
  sym->kind = SYM_VARIABLE;
  sym->data.var.type = type;
  sym->data.var.is_constant = is_constant;
  sym->data.var.is_initialized = is_initialized;

  if (!ht_insert(&st->current_scope->table, (unsigned char *)name, sym)) {
    free_symbol(sym);
    return NULL;
  }
  return sym;
}

// Vyhladanie premennej v najvnutornejsom aktualnom ramci
Symbol *symtable_find_var_current_scope(const Symtable *st, const char *name) {
  if (!st || !st->current_scope || !name)
    return NULL;
  HTItem *item = ht_search(&st->current_scope->table, (unsigned char *)name);
  return item ? (Symbol *)item->value : NULL;
}

// Vyhladanie premennej postupne cez vsetky viditelne ramce (od aktualneho k
// vonkajsim)
Symbol *symtable_find_var(const Symtable *st, const char *name) {
  if (!st || !name)
    return NULL;
  for (Scope *sc = st->current_scope; sc != NULL; sc = sc->parent) {
    HTItem *item = ht_search(&sc->table, (unsigned char *)name);
    if (item) {
      return (Symbol *)item->value;
    }
  }
  return NULL;
}

// Pridanie funkcie do globalnej tabulky
Symbol *symtable_add_func(Symtable *st, const char *name, DataType return_type,
                          size_t param_count, const Param *params,
                          bool is_defined, bool is_builtin) {
  if (!st || !name)
    return NULL;

  Symbol *sym = (Symbol *)malloc(sizeof(Symbol));
  if (!sym)
    return NULL;

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
    sym->data.func.params = (Param *)calloc(param_count, sizeof(Param));
    if (!sym->data.func.params) {
      free_symbol(sym);
      return NULL;
    }
    for (size_t i = 0; i < param_count; i++) {
      sym->data.func.params[i].name = str_dup(params[i].name);
      // Kontrola alokacie
      if (!sym->data.func.params[i].name) {
        free_symbol(sym);
        return NULL;
      }
      sym->data.func.params[i].type = params[i].type;
    }
  }

  if (!ht_insert(&st->global_table, (unsigned char *)name, sym)) {
    free_symbol(sym);
    return NULL;
  }
  return sym;
}

// Vyhladanie funkcie v globalnej tabulke
Symbol *symtable_find_func(const Symtable *st, const char *name) {
  if (!st || !name)
    return NULL;
  HTItem *item =
      ht_search((HashTable *)&st->global_table, (unsigned char *)name);
  return item ? (Symbol *)item->value : NULL;
}

// Prevod DataType na citatelny retazec
const char *datatype_to_string(DataType type) {
  switch (type) {
  case TYPE_INT:
    return "Int";
  case TYPE_DOUBLE:
    return "Double";
  case TYPE_STRING:
    return "String";
  case TYPE_UNIT:
    return "Unit";
  case TYPE_ANY:
    return "Any";
  case TYPE_BOOL:
    return "Boolean";
  case TYPE_UNDEF:
  default:
    return "Undef";
  }
}

// Registracia vstavanych funkcii do tabulky symbolov
void symtable_add_builtins(Symtable *st) {
  if (!st)
    return;

  Param p_print[] = {{"value", TYPE_ANY}};
  symtable_add_func(st, "print", TYPE_UNIT, 1, p_print, true, true);

  symtable_add_func(st, "readLine", TYPE_STRING, 0, NULL, true, true);
  symtable_add_func(st, "readInt", TYPE_INT, 0, NULL, true, true);
  symtable_add_func(st, "readDouble", TYPE_DOUBLE, 0, NULL, true, true);

  Param p_toStr[] = {{"value", TYPE_ANY}};
  symtable_add_func(st, "toStr", TYPE_STRING, 1, p_toStr, true, true);

  Param p_toInt[] = {{"value", TYPE_DOUBLE}};
  symtable_add_func(st, "toInt", TYPE_INT, 1, p_toInt, true, true);

  Param p_strLength[] = {{"value", TYPE_STRING}};
  symtable_add_func(st, "strLength", TYPE_INT, 1, p_strLength, true, true);

  Param p_subStr[] = {
      {"value", TYPE_STRING}, {"start", TYPE_INT}, {"end", TYPE_INT}};
  symtable_add_func(st, "subStr", TYPE_STRING, 3, p_subStr, true, true);

  Param p_ord[] = {{"value", TYPE_STRING}, {"index", TYPE_INT}};
  symtable_add_func(st, "ord", TYPE_INT, 2, p_ord, true, true);

  Param p_chr[] = {{"value", TYPE_INT}};
  symtable_add_func(st, "chr", TYPE_STRING, 1, p_chr, true, true);
}
