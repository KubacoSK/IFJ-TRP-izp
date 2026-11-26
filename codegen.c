/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 * Autori:
 * @author xodrasa00, Aleš Odráška
 * @author xgazdaa00, Adam Gazdarica
 * @author xkrpeld00, Dominik Krpelan
 * @author xpetraj00, Jakub Petrán
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
static int current = -1;         // aktualna funkcia
static int main_idx = -1;        // funkcia s @main
static bool gen_error = false;   // chyba alokacie pocas generovania
static unsigned label_count = 0; // pocitadlo navesti if/while

// Claude Opus 5.5
// "Vystup nech ide do bufferu co sa sam zvacsuje, nie rovno na stdout"
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

// Claude Opus 5.5
// "kazda funkcia bude mat svoj kod zvlast, parser moze skocit do inej
// funkcie v strede tej prvej. pole nech rastie podla potreby"
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

// Claude Opus 5.5
// "Ked parser zacne novu funkciu tak ju treba ulozit a vsetko dalsie pisat
// do nej taktiez treba skontrolovat aj ktora je main"
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

// vysledok je uz na zasobniku, epilog funkcie je rovnaky
void gen_return(void) {
  gen_emit("POPFRAME");
  gen_emit("RETURN");
}

// vysledok tela (po pripadnej konverzii) je na zasobniku
void gen_function_end(void) {
  gen_return();
}

// volanie uzivatelskej funkcie, argumenty su na zasobniku zlava doprava
void gen_call(const char *name) { gen_emit("CALL $f$%s", name); }

// prepnutie aktualnej funkcie, zaporny idx instrukcie zahodi
void gen_select(int idx) { current = ((size_t)idx < func_cap) ? idx : -1; }

// Claude Sonnet 5.5
// "definicie premennych daj na zaciatok funkcie"
void gen_def(const char *fmt, ...) {
  if (current < 0)
    return;
  va_list args;
  va_start(args, fmt);
  buf_vappend(&funcs[current].defs, fmt, args);
  va_end(args);
}

// Claude Sonnet 5.5
// "Zvysne instrukcie nech idu normalne do tela aktualnej funkcie,
// parser nema riesit nic nizkourovnove"
void gen_emit(const char *fmt, ...) {
  if (current < 0)
    return;
  va_list args;
  va_start(args, fmt);
  buf_vappend(&funcs[current].body, fmt, args);
  va_end(args);
}

//  PUSHS int@
void gen_push_int(int64_t value) {
  gen_emit("PUSHS int@%lld", (long long)value);
}

// desatinne cislo vo formate floatu
void gen_push_double(double value) { gen_emit("PUSHS float@%a", value); }

// PUSHS string@ s escape sekvenciami \xyz
void gen_push_string(const char *value) {
  if (current < 0)
    return;

  // kazdy znak ako \xyz (4 znaky)
  size_t len = strlen(value);
  char *esc = malloc(len * 4 + 1);
  if (!esc) {
    gen_error = true;
    return;
  }

  size_t j = 0;
  for (size_t i = 0; i < len; i++) {
    unsigned char c = (unsigned char)value[i];
    // escape: biele a riadiace znaky, '#', '\', DEL a ne-ASCII bajty
    if (c <= 32 || c == '#' || c == '\\' || c >= 127) {
      j += (size_t)sprintf(esc + j, "\\%03u", (unsigned)c);
    } else {
      esc[j++] = (char)c;
    }
  }
  esc[j] = '\0';

  gen_emit("PUSHS string@%s", esc);
  free(esc);
}

// PUSHS nil@nil (hodnota Unit)
void gen_push_unit(void) { gen_emit("PUSHS nil@nil"); }

// DEFVAR LF@name$id, id rozlisi zatienene premenne
void gen_defvar(const char *name, unsigned id) {
  gen_def("DEFVAR LF@%s$%u", name, id);
}

// PUSHS LF@name$id
void gen_push_var(const char *name, unsigned id) {
  gen_emit("PUSHS LF@%s$%u", name, id);
}

// POPS LF@name$id
void gen_pop_var(const char *name, unsigned id) {
  gen_emit("POPS LF@%s$%u", name, id);
}

// konverzia Int -> Double na vrchu zasobnika (INT2FLOATS)
void gen_convert_top(void) { gen_emit("INT2FLOATS"); }

// Claude Opus 5.5
// "<= a >= sprav ako kombinaciu mensie/vacsie alebo rovne"
// neostra nerovnost: (a >< b) OR (a == b), operandy sa zduplikuju
static void gen_rel_or_eq(const char *strict) {
  gen_emit("POPS LF@%%t2");
  gen_emit("POPS LF@%%t1");
  gen_emit("PUSHS LF@%%t1");
  gen_emit("PUSHS LF@%%t2");
  gen_emit("%s", strict);
  gen_emit("PUSHS LF@%%t1");
  gen_emit("PUSHS LF@%%t2");
  gen_emit("EQS");
  gen_emit("ORS");
}

// Claude Opus 5.5
// "pre binarne operatory vygeneruj spravnu instrukciu podla typov.
// ked je jeden int a druhy double tak treba int prekonvertovat, delenie
// dvoch intov je celociselne a retazce sa spajaju inak lebo na to nie
// je zasobnikova verzia"
void gen_binary(TokenType op, DataType left, DataType right) {
  // Int -> Double, ak je druhy operand Double
  if (left == TYPE_INT && right == TYPE_DOUBLE) {
    // lavy je pod pravym: pravy odlozit, konvertovat, vratit
    gen_emit("POPS LF@%%t1");
    gen_emit("INT2FLOATS");
    gen_emit("PUSHS LF@%%t1");
  } else if (left == TYPE_DOUBLE && right == TYPE_INT) {
    gen_convert_top();
  }

  switch (op) {
  case TOKEN_TYPE_PLUS:
    if (left == TYPE_STRING) {
      // CONCAT nema zasobnikovu verziu
      gen_emit("POPS LF@%%t2");
      gen_emit("POPS LF@%%t1");
      gen_emit("CONCAT LF@%%t1 LF@%%t1 LF@%%t2");
      gen_emit("PUSHS LF@%%t1");
    } else {
      gen_emit("ADDS");
    }
    break;
  case TOKEN_TYPE_MINUS:
    gen_emit("SUBS");
    break;
  case TOKEN_TYPE_MUL:
    gen_emit("MULS");
    break;
  case TOKEN_TYPE_DIV:
    // Int / Int je celociselne delenie (zaokruhluje k nule)
    gen_emit("%s", (left == TYPE_INT && right == TYPE_INT) ? "IDIVS" : "DIVS");
    break;
  case TOKEN_TYPE_LT:
    gen_emit("LTS");
    break;
  case TOKEN_TYPE_GT:
    gen_emit("GTS");
    break;
  case TOKEN_TYPE_LEQ:
    gen_rel_or_eq("LTS");
    break;
  case TOKEN_TYPE_GEQ:
    gen_rel_or_eq("GTS");
    break;
  case TOKEN_TYPE_EQ:
    gen_emit("EQS");
    break;
  case TOKEN_TYPE_NEQ:
    gen_emit("EQS");
    gen_emit("NOTS");
    break;
  default:
    break;
  }
}

// unarne + / - pre Int alebo Double
void gen_unary(TokenType op, DataType type) {
  if (op != TOKEN_TYPE_MINUS)
    return; // unarne + hodnotu nemeni

  // IFJ kod nema negaciu: nasobenie -1 (pri Double zachova aj -0.0)
  if (type == TYPE_DOUBLE)
    gen_emit("PUSHS float@%a", -1.0);
  else
    gen_emit("PUSHS int@-1");
  gen_emit("MULS");
}

// zahodenie hodnoty na vrchu zasobnika
void gen_drop(void) { gen_emit("POPS LF@%%t1"); }

// nove cislo navestia pre if/while
unsigned gen_new_label(void) { return ++label_count; }

// podmienka if na zasobniku, pri false skok na $if$n$else
void gen_if_cond(unsigned n) {
  gen_emit("PUSHS bool@true");
  gen_emit("JUMPIFNEQS $if$%u$else", n);
}

// koniec vetvy then, zaciatok vetvy else
void gen_if_else(unsigned n) {
  gen_emit("JUMP $if$%u$end", n);
  gen_emit("LABEL $if$%u$else", n);
}

// koniec if, navestie $if$N$end  
void gen_if_end(unsigned n) { gen_emit("LABEL $if$%u$end", n); }

// zaciatok cyklu while pred podmienkou
void gen_while_start(unsigned n) { gen_emit("LABEL $while$%u$start", n); }

// podmienka while na zasobniku, pri false skok na $while$n$end
void gen_while_cond(unsigned n) {
  gen_emit("PUSHS bool@true");
  gen_emit("JUMPIFNEQS $while$%u$end", n);
}

// koniec tela while, skok na zaciatok, vysledok Unit
void gen_while_end(unsigned n) {
  gen_drop(); // hodnota tela sa v cykle nepouzije
  gen_emit("JUMP $while$%u$start", n);
  gen_emit("LABEL $while$%u$end", n);
  gen_push_unit(); // cyklus ako prikaz ma hodnotu Unit
}

// print(x): hodnota je na zasobniku, vysledok je Unit
static void gen_print(DataType arg_type) {
  gen_emit("POPS LF@%%t1");
  if (arg_type == TYPE_UNIT) {
    // nil by sa vypisal ako "nil", Unit sa vypisuje ako ()
    gen_emit("WRITE string@()");
  } else {
    gen_emit("WRITE LF@%%t1");
  }
  gen_push_unit();
}

// Claude Sonnet 5.5
// "toStr rob podla typu ktory uz pozname pri preklade,
// string nechaj tak"
// toStr(x): typ argumentu je znamy pri preklade
static void gen_to_str(DataType arg_type) {
  switch (arg_type) {
  case TYPE_INT:
    gen_emit("INT2STRS");
    break;
  case TYPE_DOUBLE:
    gen_emit("FLOAT2STRS"); // format %.2f
    break;
  case TYPE_UNIT:
    gen_drop();
    gen_emit("PUSHS string@()");
    break;
  default:
    break; // String ostava tak ako je
  }
}

// strLength(x): retazec na zasobniku, vysledok Int
static void gen_str_length(void) {
  gen_emit("POPS LF@%%t1");
  gen_emit("STRLEN LF@%%t1 LF@%%t1");
  gen_emit("PUSHS LF@%%t1");
}

// vstavane funkcie generovane ako knizicne funkcie $b$meno
static const char *const lib_names[] = {"readLine", "readInt", "readDouble",
                                        "ord", "subStr"};
// Claude Opus 5.5
// "Jednoduche vstavane funkcie generuj priamo a zlozitejsie ako samostatne
// funkcie co sa volaju. Po volani ma na zasobniku zostat
// presne jeden vysledok"
void gen_builtin_call(const char *name, const DataType *arg_types,
                      size_t arg_count) {
  if (strcmp(name, "print") == 0 && arg_count == 1) {
    gen_print(arg_types[0]);
  } else if (strcmp(name, "toStr") == 0 && arg_count == 1) {
    gen_to_str(arg_types[0]);
  } else if (strcmp(name, "toInt") == 0) {
    gen_emit("FLOAT2INTS"); // Int argument uz skonvertoval parser
  } else if (strcmp(name, "chr") == 0) {
    gen_emit("INT2CHARS"); // mimo 0-127 chyba 58 interpretu
  } else if (strcmp(name, "strLength") == 0) {
    gen_str_length();
  } else {
    for (size_t i = 0; i < sizeof(lib_names) / sizeof(lib_names[0]); i++) {
      if (strcmp(name, lib_names[i]) == 0) {
        gen_emit("CALL $b$%s", name);
        return;
      }
    }
    gen_error = true; // neznama vstavana funkcia, zasobnik by nesedel
  }
}

// Claude Opus 5.5
// "Kniznica vstavanych funkcii sa bude vypisovat cela, kazda funkcia ma
// rovnaky zaciatok ako uzivateske funkcie s LF1 a LF2, readdouble
// vrati pri EOF alebo chybnom vstupe 0.0, readInt 0, ord vrati mimo rozsahu
// -1 a subStr skonci pri chybnych indexoch chybou 40"
// kniznica vstavanych funkcii, vypisuje sa vzdy cela (iba text, bez printf)
static const char *const builtin_lib[] = {
    // readLine(): vracia riadok vratane LF, po EOF prazdny retazec ""
    "\nLABEL $b$readLine\n"
    "CREATEFRAME\n"
    "PUSHFRAME\n"
    "DEFVAR LF@%t1\n"
    "READ LF@%t1 string\n"
    "JUMPIFNEQ $b$readLine$ok LF@%t1 nil@nil\n"
    "MOVE LF@%t1 string@\n"
    "LABEL $b$readLine$ok\n"
    "PUSHS LF@%t1\n"
    "POPFRAME\n"
    "RETURN\n",
    // readInt(): pri EOF alebo chybnom vstupe 0 alebo prekroceni 32-bit rozsahu
    // Int
    "\nLABEL $b$readInt\n"
    "CREATEFRAME\n"
    "PUSHFRAME\n"
    "DEFVAR LF@%t1\n"
    "DEFVAR LF@%t2\n"
    "READ LF@%t1 int\n"
    "JUMPIFEQ $b$readInt$zero LF@%t1 nil@nil\n"
    "GT LF@%t2 LF@%t1 int@2147483647\n"
    "JUMPIFEQ $b$readInt$zero LF@%t2 bool@true\n"
    "LT LF@%t2 LF@%t1 int@-2147483648\n"
    "JUMPIFEQ $b$readInt$zero LF@%t2 bool@true\n"
    "JUMP $b$readInt$ok\n"
    "LABEL $b$readInt$zero\n"
    "MOVE LF@%t1 int@0\n"
    "LABEL $b$readInt$ok\n"
    "PUSHS LF@%t1\n"
    "POPFRAME\n"
    "RETURN\n",

    // readDouble(): pri EOF alebo chybnom vstupe 0.0
    "\nLABEL $b$readDouble\n"
    "CREATEFRAME\n"
    "PUSHFRAME\n"
    "DEFVAR LF@%t1\n"
    "DEFVAR LF@%t2\n"
    "READ LF@%t1 float\n"
    "JUMPIFNEQ $b$readDouble$ok LF@%t1 nil@nil\n"
    "MOVE LF@%t1 float@0x0p+0\n"
    "LABEL $b$readDouble$ok\n"
    "PUSHS LF@%t1\n"
    "POPFRAME\n"
    "RETURN\n",

    // ord(s, i): ASCII kod znaku, mimo rozsah (aj prazdny retazec) -1
    "\nLABEL $b$ord\n"
    "CREATEFRAME\n"
    "PUSHFRAME\n"
    "DEFVAR LF@%t1\n"
    "DEFVAR LF@%t2\n"
    "DEFVAR LF@s\n"
    "DEFVAR LF@i\n"
    "DEFVAR LF@len\n"
    "DEFVAR LF@cond\n"
    "POPS LF@i\n"
    "POPS LF@s\n"
    "STRLEN LF@len LF@s\n"
    "LT LF@cond LF@i int@0\n"
    "JUMPIFEQ $b$ord$bad LF@cond bool@true\n"
    "LT LF@cond LF@i LF@len\n"
    "JUMPIFEQ $b$ord$bad LF@cond bool@false\n"
    "STRI2INT LF@%t1 LF@s LF@i\n"
    "PUSHS LF@%t1\n"
    "POPFRAME\n"
    "RETURN\n"
    "LABEL $b$ord$bad\n"
    "PUSHS int@-1\n"
    "POPFRAME\n"
    "RETURN\n",

    // subStr(s, start, end): podretazec [start, end), inak chyba 40
    "\nLABEL $b$subStr\n"
    "CREATEFRAME\n"
    "PUSHFRAME\n"
    "DEFVAR LF@%t1\n"
    "DEFVAR LF@%t2\n"
    "DEFVAR LF@s\n"
    "DEFVAR LF@start\n"
    "DEFVAR LF@end\n"
    "DEFVAR LF@len\n"
    "DEFVAR LF@res\n"
    "DEFVAR LF@cond\n"
    "POPS LF@end\n"
    "POPS LF@start\n"
    "POPS LF@s\n"
    "STRLEN LF@len LF@s\n"
    "LT LF@cond LF@start int@0\n"
    "JUMPIFEQ $b$subStr$err LF@cond bool@true\n"
    "LT LF@cond LF@end int@0\n"
    "JUMPIFEQ $b$subStr$err LF@cond bool@true\n"
    "GT LF@cond LF@start LF@end\n"
    "JUMPIFEQ $b$subStr$err LF@cond bool@true\n"
    "LT LF@cond LF@start LF@len\n"
    "JUMPIFEQ $b$subStr$err LF@cond bool@false\n"
    "GT LF@cond LF@end LF@len\n"
    "JUMPIFEQ $b$subStr$err LF@cond bool@true\n"
    "MOVE LF@res string@\n"
    "LABEL $b$subStr$loop\n"
    "LT LF@cond LF@start LF@end\n"
    "JUMPIFEQ $b$subStr$done LF@cond bool@false\n"
    "GETCHAR LF@%t1 LF@s LF@start\n"
    "CONCAT LF@res LF@res LF@%t1\n"
    "ADD LF@start LF@start int@1\n"
    "JUMP $b$subStr$loop\n"
    "LABEL $b$subStr$done\n"
    "PUSHS LF@res\n"
    "POPFRAME\n"
    "RETURN\n"
    "LABEL $b$subStr$err\n"
    "EXIT int@40\n",
};

// vypisanie celeho vygenerovaneho kodu do suboru out, vracia ERROR_OK alebo ERROR_INTERNAL
// vypis je az na konci, ak parser narazi na chybu tak sa uz nic nevypisuje
int gen_write(FILE *out) {
  if (gen_error || main_idx < 0)
    return ERROR_INTERNAL;

  // hlavicka a vstupny bod: vysledok @main (Unit) zmaze CLEARS
  fprintf(out, ".IFJcode26\n");
  fprintf(out, "CALL $f$%s\n", funcs[main_idx].name);
  fprintf(out, "CLEARS\n");
  fprintf(out, "EXIT int@0\n");

  // funkcie: prolog, pomocne premenne, defs, telo (epilog je na konci tela)
  for (size_t i = 0; i < func_cap; i++) {
    FuncCode *f = &funcs[i];
    if (!f->name)
      continue;
    fprintf(out, "\nLABEL $f$%s\n", f->name);
    fprintf(out, "CREATEFRAME\n");
    fprintf(out, "PUSHFRAME\n");
    fprintf(out, "DEFVAR LF@%%t1\n");
    fprintf(out, "DEFVAR LF@%%t2\n");
    if (f->defs.data)
      fputs(f->defs.data, out);
    if (f->body.data)
      fputs(f->body.data, out);
  }

  // kniznica vstavanych funkcii
  for (size_t i = 0; i < sizeof(builtin_lib) / sizeof(builtin_lib[0]); i++)
    fputs(builtin_lib[i], out);
  return ERROR_OK;
}

// uvolnenie vsetkych alokovanych bufferov a reset generatora
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
  label_count = 0;
}
