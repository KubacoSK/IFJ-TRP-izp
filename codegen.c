/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file codegen.c
 * @brief Generator cieloveho kodu IFJcode26.
 *
 */

#include "codegen.h"
#include "error.h"
#include "utils.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define BUF_INIT 256 // zaciatocna velkost bufferu

// rastuci retazec
typedef struct {
  char *data;
  size_t len;
  size_t cap;
} StrBuf;

// kod jednej funkcie
typedef struct {
  char *name;  // meno funkcie v IFJ26, NULL = este negenerovana
  StrBuf defs; // DEFVAR na zaciatku funkcie
  StrBuf body; // telo funkcie
} FuncCode;

static FuncCode *funcs = NULL; // indexy rovnake ako v parseri
static size_t func_cap = 0;
static int current = -1;       // aktualna funkcia
static int main_idx = -1;      // funkcia s @main
static bool gen_error = false; // chyba alokacie pocas generovania

// pridanie formatovaneho riadku do bufferu
static void buf_vappend(StrBuf *b, const char *fmt, va_list args) {
  va_list copy;
  va_copy(copy, args);
  int n = vsnprintf(NULL, 0, fmt, copy);
  va_end(copy);
  if (n < 0) {
    gen_error = true;
    return;
  }

  // +2 = '\n' a '\0'
  size_t need = b->len + (size_t)n + 2;
  if (need > b->cap) {
    size_t new_cap = b->cap ? b->cap : BUF_INIT;
    while (new_cap < need)
      new_cap *= 2;
    char *tmp = realloc(b->data, new_cap);
    if (!tmp) {
      gen_error = true;
      return;
    }
    b->data = tmp;
    b->cap = new_cap;
  }

  vsnprintf(b->data + b->len, (size_t)n + 1, fmt, args);
  b->len += (size_t)n;
  b->data[b->len++] = '\n';
  b->data[b->len] = '\0';
}

// zaistenie miesta pre funkciu idx
static bool ensure_func(int idx) {
  if ((size_t)idx < func_cap)
    return true;
  size_t new_cap = func_cap ? func_cap : 16;
  while (new_cap <= (size_t)idx)
    new_cap *= 2;
  FuncCode *tmp = realloc(funcs, new_cap * sizeof(FuncCode));
  if (!tmp)
    return false;
  memset(tmp + func_cap, 0, (new_cap - func_cap) * sizeof(FuncCode));
  funcs = tmp;
  func_cap = new_cap;
  return true;
}

void gen_function_begin(int idx, const char *name, bool is_main) {
  if (idx < 0 || !ensure_func(idx)) {
    gen_error = true;
    current = -1;
    return;
  }
  free(funcs[idx].name);
  funcs[idx].name = str_dup(name);
  if (!funcs[idx].name)
    gen_error = true;
  if (is_main)
    main_idx = idx;
  current = idx;
}

void gen_function_end(void) {
  // vysledok funkcie je zatial vzdy Unit (hodnoty tela doplni krok 5)
  gen_emit("PUSHS nil@nil");
  gen_emit("POPFRAME");
  gen_emit("RETURN");
}

void gen_select(int idx) {
  current = ((size_t)idx < func_cap) ? idx : -1;
}

void gen_def(const char *fmt, ...) {
  if (current < 0)
    return;
  va_list args;
  va_start(args, fmt);
  buf_vappend(&funcs[current].defs, fmt, args);
  va_end(args);
}

void gen_emit(const char *fmt, ...) {
  if (current < 0)
    return;
  va_list args;
  va_start(args, fmt);
  buf_vappend(&funcs[current].body, fmt, args);
  va_end(args);
}

int gen_write(FILE *out) {
  if (gen_error || main_idx < 0)
    return ERROR_INTERNAL;

  // hlavicka a vstupny bod (R12): vysledok @main (Unit) sa zahodi
  fprintf(out, ".IFJcode26\n");
  fprintf(out, "DEFVAR GF@%%t1\n");
  fprintf(out, "DEFVAR GF@%%t2\n");
  fprintf(out, "CALL $f$%s\n", funcs[main_idx].name);
  fprintf(out, "POPS GF@%%t1\n");
  fprintf(out, "EXIT int@0\n");

  // funkcie: prolog, defs, telo (epilog je na konci tela)
  for (size_t i = 0; i < func_cap; i++) {
    FuncCode *f = &funcs[i];
    if (!f->name)
      continue;
    fprintf(out, "\nLABEL $f$%s\n", f->name);
    fprintf(out, "CREATEFRAME\n");
    fprintf(out, "PUSHFRAME\n");
    if (f->defs.data)
      fputs(f->defs.data, out);
    if (f->body.data)
      fputs(f->body.data, out);
  }
  return ERROR_OK;
}

void gen_free(void) {
  for (size_t i = 0; i < func_cap; i++) {
    free(funcs[i].name);
    free(funcs[i].defs.data);
    free(funcs[i].body.data);
  }
  free(funcs);
  funcs = NULL;
  func_cap = 0;
  current = -1;
  main_idx = -1;
  gen_error = false;
}
