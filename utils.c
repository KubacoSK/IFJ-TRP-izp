/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file utils.c
 * @brief Implementacia pomocnych funkcii pre prekladac IFJ26.
 */

#include "utils.h"
#include <stdlib.h>
#include <string.h>

// Bezpecna duplikacia retazca v ISO C99
char *str_dup(const char *s) {
  if (!s)
    return NULL;
  size_t len = strlen(s);
  char *copy = (char *)malloc(len + 1);
  if (copy) {
    memcpy(copy, s, len + 1);
  }
  return copy;
}
