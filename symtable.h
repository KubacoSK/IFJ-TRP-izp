/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file symtable.h
 * @brief Abstraktny datovy typ (ADT) tabulky symbolov pre jazyk IFJ26.
 */

#ifndef _SYMTABLE_H
#define _SYMTABLE_H

#include "hashtable.h"
#include <stdbool.h>
#include <stddef.h>

// Datove typy jazyka IFJ26
typedef enum {
  TYPE_UNDEF = 0, // Nedefinovany typ (vyuziva sa pri typovej inferencii)
  TYPE_INT,       // Cele cislo (Int)
  TYPE_DOUBLE,    // Desatinne cislo (Double)
  TYPE_STRING,    // Retazec (String)
  TYPE_UNIT,      // Prazdny navratovy typ (Unit)
  TYPE_ANY,       // Zastupny typ pre lubovolnu hodnotu
  TYPE_BOOL       // Pravdivostna hodnota (Boolean) len pre podmienky
} DataType;

// Druh symbolu
typedef enum {
  SYM_VARIABLE, // Premenna
  SYM_FUNCTION  // Funkcia
} SymbolKind;

// Formalny parameter funkcie
typedef struct {
  char *name;    // Nazov parametra
  DataType type; // Datovy typ parametra
} Param;

// Data premennej
typedef struct {
  unsigned id; // jedinecne cislo pre premenovanie v generatore
  DataType type;       // Datovy typ premennej
  bool is_constant;    // True pre val (nemennu), false pre var (menitelnu)
  bool is_initialized; // Priznak inicializacie premennej
} VarData;

// Data funkcie
typedef struct {
  DataType return_type; // Navratovy typ funkcie
  size_t param_count;   // Pocet formalnych parametrov
  Param *params;        // Pole formalnych parametrov
  bool is_defined;      // True ak je telo funkcie definovane
  bool is_builtin;      // True pre vstavane funkcie
} FuncData;

// Struktura symbolu v tabulke
typedef struct {
  char *name;      // Nazov identifikatora
  SymbolKind kind; // Druh symbolu (premenna / funkcia)
  union {
    VarData var;   // Data premennej
    FuncData func; // Data funkcie
  } data;
} Symbol;

// Lokalny ramec (scope) pre premenne
typedef struct Scope {
  HashTable table;      // Tabulka symbolov pre dany ramec
  struct Scope *parent; // Ukazovatel na nadradeny ramec
} Scope;

// Hlavna struktura tabulky symbolov prekladaca
typedef struct {
  unsigned next_var_id; // pocitadlo ID premennych
  HashTable global_table; // Globalna tabulka funkcii
  Scope *current_scope;   // Aktualny lokalny ramec premennych
} Symtable;

// Inicializacia prazdnej tabulky symbolov
void symtable_init(Symtable *st);

// Uvolnenie celej tabulky symbolov a vsetkych ramcov
void symtable_free(Symtable *st);

// Otvorenie noveho lokalneho ramca pri vstupe do bloku
bool symtable_push_scope(Symtable *st);

// Uzatvorenie aktualneho lokalneho ramca pri opusteni bloku
void symtable_pop_scope(Symtable *st);

// Pridanie premennej do aktualneho ramca
Symbol *symtable_add_var(Symtable *st, const char *name, DataType type,
                         bool is_constant, bool is_initialized);

// Vyhladanie premennej v aktualnom alebo nadradenych ramcoch
Symbol *symtable_find_var(const Symtable *st, const char *name);

// Vyhladanie premennej iba v aktualnom najvnutornejsom ramci
Symbol *symtable_find_var_current_scope(const Symtable *st, const char *name);

// Pridanie funkcie do globalnej tabulky
Symbol *symtable_add_func(Symtable *st, const char *name, DataType return_type,
                          size_t param_count, const Param *params,
                          bool is_defined, bool is_builtin);

// Vyhladanie funkcie v globalnej tabulke
Symbol *symtable_find_func(const Symtable *st, const char *name);

// Prevod DataType na citatelny retazec (pre ladenie a chybove hlasky)
const char *datatype_to_string(DataType type);

// Pridanie vstavanych funkcii do tabulky symbolov
void symtable_add_builtins(Symtable *st);

#endif // _SYMTABLE_H
