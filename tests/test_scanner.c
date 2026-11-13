/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file test_scanner.c
 * @brief Testovacia sada pre lexikalny analyzator (scanner).
 */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../error.h"
#include "../scanner.h"

// ANSI farby pre vystup testov
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED "\033[0;31m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_RESET "\033[0m"

static int total_tests = 0;
static int passed_tests = 0;
static int failed_tests = 0;

/**
 * Posle retazec do scanneru a overi, ci prijate tokeny zodpovedaju ocakavanym
 * typom.
 */
static bool check_tokens(const char *test_name, const char *input,
                         const int expected_types[], int count) {
  total_tests++;
  FILE *f = tmpfile();
  if (!f) {
    fprintf(stderr, "Nie je mozne vytvorit docasny subor\n");
    return false;
  }
  fputs(input, f);
  rewind(f);

  set_source_file(f);

  Token tok;
  bool ok = true;
  for (int i = 0; i < count; i++) {
    int res = get_token(&tok);
    if (res != SCANNER_TOKEN_OK) {
      printf(
          "  " COLOR_RED "[FAIL]" COLOR_RESET
          " %s: neocakavany chybovy kod %d na tokene %d (ocakavany typ %d)\n",
          test_name, res, i, expected_types[i]);
      ok = false;
      break;
    }
    if ((int)tok.type != expected_types[i]) {
      printf("  " COLOR_RED "[FAIL]" COLOR_RESET
             " %s: nezhoda tokenu na indexe %d: ziskany typ %d, ocakavany %d\n",
             test_name, i, tok.type, expected_types[i]);
      ok = false;
      free_token_attribute(&tok);
      break;
    }
    free_token_attribute(&tok);
  }

  fclose(f);
  if (ok) {
    printf("  " COLOR_GREEN "[PASS]" COLOR_RESET " %s\n", test_name);
    passed_tests++;
  } else {
    failed_tests++;
  }
  return ok;
}

/**
 * Posle neplatny retazec a overi, ci scanner vrati ocakavany chybovy kod.
 */
static bool check_error(const char *test_name, const char *input,
                        int expected_err) {
  total_tests++;
  FILE *f = tmpfile();
  if (!f)
    return false;
  fputs(input, f);
  rewind(f);

  set_source_file(f);

  Token tok;
  int res = SCANNER_TOKEN_OK;
  while ((res = get_token(&tok)) == SCANNER_TOKEN_OK) {
    if (tok.type == TOKEN_TYPE_EOF)
      break;
    free_token_attribute(&tok);
  }

  fclose(f);
  if (res == expected_err) {
    printf("  " COLOR_GREEN "[PASS]" COLOR_RESET
           " %s (odmietnute s kodom %d)\n",
           test_name, res);
    passed_tests++;
    return true;
  } else {
    printf("  " COLOR_RED "[FAIL]" COLOR_RESET
           " %s: ocakavana chyba %d, ale scanner vratil %d\n",
           test_name, expected_err, res);
    failed_tests++;
    return false;
  }
}

int main(void) {
  printf(
      COLOR_BLUE
      "========================================================\n" COLOR_RESET);
  printf(
      COLOR_BLUE
      "       IFJ26 TESTOVACIA SADA PRE SCANNER                \n" COLOR_RESET);
  printf(COLOR_BLUE "========================================================"
                    "\n\n" COLOR_RESET);

  // ---------------------------------------------------------
  // KATEGORIA 1: ZAKLADNE KLUCOVE SLOVA (14 slov)
  // ---------------------------------------------------------
  printf("--- Kategoria 1: Zakladne klucove slova (14 slov) ---\n");
  {
    const char *kw_input = "def do Double else if import Int return String "
                           "then Unit val var while";
    int kw_types[] = {
        TOKEN_TYPE_KEYWORD, TOKEN_TYPE_KEYWORD, TOKEN_TYPE_KEYWORD,
        TOKEN_TYPE_KEYWORD, TOKEN_TYPE_KEYWORD, TOKEN_TYPE_KEYWORD,
        TOKEN_TYPE_KEYWORD, TOKEN_TYPE_KEYWORD, TOKEN_TYPE_KEYWORD,
        TOKEN_TYPE_KEYWORD, TOKEN_TYPE_KEYWORD, TOKEN_TYPE_KEYWORD,
        TOKEN_TYPE_KEYWORD, TOKEN_TYPE_KEYWORD, TOKEN_TYPE_EOL,
        TOKEN_TYPE_EOF};
    check_tokens("Vsetkych 14 zakladnych klucovych slov bolo rozpoznanych",
                 kw_input, kw_types, sizeof(kw_types) / sizeof(kw_types[0]));

    // Citlivost na velkost pismen: slova s inou velkostou su identifikatory
    const char *case_input = "Def DO double IF Val";
    int case_types[] = {TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_IDENTIFIER,
                        TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_IDENTIFIER,
                        TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_EOL,
                        TOKEN_TYPE_EOF};
    check_tokens(
        "Klucove slova rozlisuju velkost pismen (Def/DO/Val su identifikatory)",
        case_input, case_types, sizeof(case_types) / sizeof(case_types[0]));
  }

  // ---------------------------------------------------------
  // KATEGORIA 2: IDENTIFIKATORY A PRAVIDLA PRE PODTRZITKA
  // ---------------------------------------------------------
  printf("\n--- Kategoria 2: Identifikatory a pravidla pre podtrzitka ---\n");
  {
    const char *id_input = "x myVar _internal __private counter123 a_b_c";
    int id_types[] = {TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_IDENTIFIER,
                      TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_IDENTIFIER,
                      TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_IDENTIFIER,
                      TOKEN_TYPE_EOL,        TOKEN_TYPE_EOF};
    check_tokens("Platne identifikatory zacinajuce pismenom alebo podtrzitkom",
                 id_input, id_types, sizeof(id_types) / sizeof(id_types[0]));

    // Samostatne podtrzitko vrati token TOKEN_TYPE_UNDERSCORE
    const char *underscore_input = "_";
    int underscore_types[] = {TOKEN_TYPE_UNDERSCORE, TOKEN_TYPE_EOL,
                              TOKEN_TYPE_EOF};
    check_tokens("Samostatne podtrzitko vrati TOKEN_TYPE_UNDERSCORE",
                 underscore_input, underscore_types,
                 sizeof(underscore_types) / sizeof(underscore_types[0]));

    const char *underscore_expr = "val x = _";
    int underscore_expr_types[] = {TOKEN_TYPE_KEYWORD, TOKEN_TYPE_IDENTIFIER,
                                   TOKEN_TYPE_ASSIGN,  TOKEN_TYPE_UNDERSCORE,
                                   TOKEN_TYPE_EOL,     TOKEN_TYPE_EOF};
    check_tokens("Podtrzitko vo vyraze vrati TOKEN_TYPE_UNDERSCORE",
                 underscore_expr, underscore_expr_types,
                 sizeof(underscore_expr_types) /
                     sizeof(underscore_expr_types[0]));
  }

  // ---------------------------------------------------------
  // KATEGORIA 3: ANOTACIA @main
  // ---------------------------------------------------------
  printf("\n--- Kategoria 3: Anotacia @main ---\n");
  {
    const char *main_input = "@main def run(): Unit =";
    int main_types[] = {TOKEN_TYPE_MAIN,          TOKEN_TYPE_KEYWORD,
                        TOKEN_TYPE_IDENTIFIER,    TOKEN_TYPE_LEFT_BRACKET,
                        TOKEN_TYPE_RIGHT_BRACKET, TOKEN_TYPE_COLON,
                        TOKEN_TYPE_KEYWORD,       TOKEN_TYPE_ASSIGN,
                        TOKEN_TYPE_EOL,           TOKEN_TYPE_EOF};
    check_tokens("Platna anotacia @main pred funkciou", main_input, main_types,
                 sizeof(main_types) / sizeof(main_types[0]));

    // Znak @ sa v inom kontexte nepouziva
    check_error("Neplatna anotacia @foo", "@foo", SCANNER_ERROR_LEX);
    check_error("Medzera medzi @ a main '@ main'", "@ main", SCANNER_ERROR_LEX);
    check_error("Identifikator @mainApp", "@mainApp", SCANNER_ERROR_LEX);
    check_error("Samostatny znak '@'", "@", SCANNER_ERROR_LEX);
  }

  // ---------------------------------------------------------
  // KATEGORIA 4: CELOCISELNE LITERALY
  // ---------------------------------------------------------
  printf("\n--- Kategoria 4: Celociselne literaly ---\n");
  {
    const char *int_input = "0 42 1_000_000 12_34_56";
    int int_types[] = {TOKEN_TYPE_INT_NUMBER, TOKEN_TYPE_INT_NUMBER,
                       TOKEN_TYPE_INT_NUMBER, TOKEN_TYPE_INT_NUMBER,
                       TOKEN_TYPE_EOL,        TOKEN_TYPE_EOF};
    check_tokens("Platne cele cisla s podtrzitkami aj bez nich", int_input,
                 int_types, sizeof(int_types) / sizeof(int_types[0]));

    // Nenulovy literal nesmie zacinat nulou
    check_error("Uvodna nula '01' zamietnuta", "01", SCANNER_ERROR_LEX);
    check_error("Uvodna nula '00' zamietnuta", "00", SCANNER_ERROR_LEX);
    check_error("Uvodna nula '0123' zamietnuta", "0123", SCANNER_ERROR_LEX);

    // Ine ciselne sustavy a sufix L nie su podporovane
    check_error("Hexadecimalne '0x10' zamietnute", "0x10", SCANNER_ERROR_LEX);
    check_error("Hexadecimalne '0XFF' zamietnute", "0XFF", SCANNER_ERROR_LEX);
    check_error("Sufix '12L' zamietnuty", "12L", SCANNER_ERROR_LEX);
    check_error("Sufix '42l' zamietnuty", "42l", SCANNER_ERROR_LEX);

    // Podtrzitko musi byt medzi dvoma cislicami
    check_error("Koncove podtrzitko '123_' zamietnute", "123_",
                SCANNER_ERROR_LEX);
    check_error("Dve podtrzitka za sebou '1__0' zamietnute", "1__0",
                SCANNER_ERROR_LEX);
    check_error("Podtrzitko na nule '0_' zamietnute", "0_", SCANNER_ERROR_LEX);
  }

  // ---------------------------------------------------------
  // KATEGORIA 5: DESATINNE LITERALY
  // ---------------------------------------------------------
  printf("\n--- Kategoria 5: Desatinne literaly ---\n");
  {
    const char *double_input = "12.34 .5 1.2e-3 12e3 1.5d 10.0D";
    int double_types[] = {TOKEN_TYPE_DOUBLE_NUMBER, TOKEN_TYPE_DOUBLE_NUMBER,
                          TOKEN_TYPE_DOUBLE_NUMBER, TOKEN_TYPE_DOUBLE_NUMBER,
                          TOKEN_TYPE_DOUBLE_NUMBER, TOKEN_TYPE_DOUBLE_NUMBER,
                          TOKEN_TYPE_EOL,           TOKEN_TYPE_EOF};
    check_tokens(
        "Platne formaty desatinnych cisiel (standard, bodka, exponent, d/D)",
        double_input, double_types,
        sizeof(double_types) / sizeof(double_types[0]));

    // Pristup k metode na Int: 12.toString sa musi nacitat ako INT(12), BODKA,
    // IDENTIFIKATOR
    const char *member_input = "12.toString";
    int member_types[] = {TOKEN_TYPE_INT_NUMBER, TOKEN_TYPE_DOT,
                          TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_EOL,
                          TOKEN_TYPE_EOF};
    check_tokens("Pristup k clenu '12.toString' spravne oddeleny", member_input,
                 member_types, sizeof(member_types) / sizeof(member_types[0]));

    // Sufixy f a F nie su podporovane
    check_error("Sufix '1.5f' zamietnuty", "1.5f", SCANNER_ERROR_LEX);
    check_error("Sufix '1.5F' zamietnuty", "1.5F", SCANNER_ERROR_LEX);

    // Neplatne exponenty a podtrzitka v desatinnych cislach
    check_error("Prazdny exponent '1.2e' zamietnuty", "1.2e",
                SCANNER_ERROR_LEX);
    check_error("Iba znamienko v exponente '1.2e+' zamietnute", "1.2e+",
                SCANNER_ERROR_LEX);
    check_error("Podtrzitko pri bodke '1_.2' zamietnute", "1_.2",
                SCANNER_ERROR_LEX);
    check_error("Koncove podtrzitko v desatinnom cisle '1.2_' zamietnute",
                "1.2_", SCANNER_ERROR_LEX);
    check_error("Podtrzitko pri exponente '1.2e_3' zamietnute", "1.2e_3",
                SCANNER_ERROR_LEX);
  }

  // ---------------------------------------------------------
  // KATEGORIA 6: RETAZCE A ESCAPE SEKVENCIE
  // ---------------------------------------------------------
  printf("\n--- Kategoria 6: Retazce a escape sekvencie ---\n");
  {
    // Jednoriadkove retazce s povolenymi escape sekvenciami
    const char *str_input = "\"hello world\" \"\\n\\t\\r\\\\\\\"\" \"\"";
    int str_types[] = {TOKEN_TYPE_STRING, TOKEN_TYPE_STRING, TOKEN_TYPE_STRING,
                       TOKEN_TYPE_EOL, TOKEN_TYPE_EOF};
    check_tokens(
        "Jednoriadkove retazce s platnymi escape sekvenciami a prazdny retazec",
        str_input, str_types, sizeof(str_types) / sizeof(str_types[0]));

    // Viacriadkove retazce """..."""
    const char *multiline_input = "\"\"\"line 1\nline 2\nline 3\"\"\"";
    int multiline_types[] = {TOKEN_TYPE_STRING, TOKEN_TYPE_EOL, TOKEN_TYPE_EOF};
    check_tokens("Viacriadkovy retazec zachovavajuci nove riadky",
                 multiline_input, multiline_types,
                 sizeof(multiline_types) / sizeof(multiline_types[0]));

    // V jednoriadkovych retazcoch su povolene len \\, \", \n, \r, \t
    check_error("Neplatny hexadecimalny escape '\\x41' zamietnuty", "\"\\x41\"",
                SCANNER_ERROR_LEX);
    check_error("Neplatny escape '\\a' zamietnuty", "\"\\a\"",
                SCANNER_ERROR_LEX);
    check_error("Neplatny escape '\\0' zamietnuty", "\"\\0\"",
                SCANNER_ERROR_LEX);

    // Neukoncene retazce
    check_error("Neukonceny jednoriadkovy retazec zamietnuty", "\"unclosed",
                SCANNER_ERROR_LEX);
    check_error("Neukonceny viacriadkovy retazec zamietnuty", "\"\"\"unclosed",
                SCANNER_ERROR_LEX);
    check_error(
        "Literalny neosetreny novy riadok v jednoriadkovom retazci zamietnuty",
        "\"line1\nline2\"", SCANNER_ERROR_LEX);
  }

  // ---------------------------------------------------------
  // KATEGORIA 7: KOMENTARE
  // ---------------------------------------------------------
  printf("\n--- Kategoria 7: Komentare ---\n");
  {
    const char *comments_input =
        "val a = 1 // riadkovy komentar\n"
        "val b = /* inline blokovy */ 2\n"
        "val c = /* vnoreny /* blokovy */ komentar */ 3";
    int comments_types[] = {
        TOKEN_TYPE_KEYWORD,    TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_ASSIGN,
        TOKEN_TYPE_INT_NUMBER, TOKEN_TYPE_EOL,        TOKEN_TYPE_KEYWORD,
        TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_ASSIGN,     TOKEN_TYPE_INT_NUMBER,
        TOKEN_TYPE_EOL,        TOKEN_TYPE_KEYWORD,    TOKEN_TYPE_IDENTIFIER,
        TOKEN_TYPE_ASSIGN,     TOKEN_TYPE_INT_NUMBER, TOKEN_TYPE_EOL,
        TOKEN_TYPE_EOF};
    check_tokens(
        "Riadkove komentare, inline blokove a vnorene blokove komentare",
        comments_input, comments_types,
        sizeof(comments_types) / sizeof(comments_types[0]));

    // Za viacriadkovym blokovym komentarom nesmu byt dalsie tokeny na rovnakom
    // riadku
    const char *invalid_multi = "/* viacriadkovy\n"
                                "   blokovy komentar */ val x = 1";
    check_error(
        "Token na rovnakom riadku po viacriadkovom komentari zamietnuty",
        invalid_multi, SCANNER_ERROR_LEX);
    check_error("Neukonceny blokovy komentar zamietnuty", "/* neukonceny",
                SCANNER_ERROR_LEX);
    check_error("Neukonceny vnoreny blokovy komentar zamietnuty",
                "/* /* vnoreny */", SCANNER_ERROR_LEX);
  }

  // ---------------------------------------------------------
  // KATEGORIA 8: ZAKLADNE OPERATORY A ODDELOVACE
  // ---------------------------------------------------------
  printf("\n--- Kategoria 8: Zakladne operatory a oddelovace ---\n");
  {
    const char *ops_input = "+ - * / == != < <= > >= = ( ) , . : ;";
    int ops_types[] = {TOKEN_TYPE_PLUS,
                       TOKEN_TYPE_MINUS,
                       TOKEN_TYPE_MUL,
                       TOKEN_TYPE_DIV,
                       TOKEN_TYPE_EQ,
                       TOKEN_TYPE_NEQ,
                       TOKEN_TYPE_LT,
                       TOKEN_TYPE_LEQ,
                       TOKEN_TYPE_GT,
                       TOKEN_TYPE_GEQ,
                       TOKEN_TYPE_ASSIGN,
                       TOKEN_TYPE_LEFT_BRACKET,
                       TOKEN_TYPE_RIGHT_BRACKET,
                       TOKEN_TYPE_COMMA,
                       TOKEN_TYPE_DOT,
                       TOKEN_TYPE_COLON,
                       TOKEN_TYPE_SEMICOLON,
                       TOKEN_TYPE_EOL,
                       TOKEN_TYPE_EOF};
    check_tokens("Vsetky zakladne aritmeticke, relacne a interpunkcne tokeny",
                 ops_input, ops_types,
                 sizeof(ops_types) / sizeof(ops_types[0]));

    // Unarne minus je operator MINUS, nie sucast literalu
    const char *neg_input = "-42";
    int neg_types[] = {TOKEN_TYPE_MINUS, TOKEN_TYPE_INT_NUMBER, TOKEN_TYPE_EOL,
                       TOKEN_TYPE_EOF};
    check_tokens("Zaporne cele cislo '-42' spracovane ako MINUS a INT(42)",
                 neg_input, neg_types,
                 sizeof(neg_types) / sizeof(neg_types[0]));

    // Samostatne ! je neplatne (povolene len !=)
    check_error("Samostatne '!' v zakladnej specifikacii zamietnute", "!",
                SCANNER_ERROR_LEX);
    check_error("Logicke AND '&' zamietnute", "&", SCANNER_ERROR_LEX);
    check_error("Logicke OR '|' zamietnute", "|", SCANNER_ERROR_LEX);
    check_error("Hranata zatvorka '[' zamietnuta", "[", SCANNER_ERROR_LEX);
    check_error("Hranata zatvorka ']' zamietnuta", "]", SCANNER_ERROR_LEX);
    check_error("Zlozena zatvorka '{' zamietnuta", "{", SCANNER_ERROR_LEX);
    check_error("Zlozena zatvorka '}' zamietnuta", "}", SCANNER_ERROR_LEX);
    check_error("Ne-ASCII znak '$' zamietnuty", "$", SCANNER_ERROR_LEX);
  }

  // ---------------------------------------------------------
  // KATEGORIA 9: ODSADENIE A OFF-SIDE PRAVIDLO
  // ---------------------------------------------------------
  printf("\n--- Kategoria 9: Odsadenie a off-side pravidlo ---\n");
  {
    const char *indent_input = "def foo():\n"
                               "    val a = 1\n"
                               "    val b = 2\n"
                               "val c = 3";
    int indent_types[] = {TOKEN_TYPE_KEYWORD,      TOKEN_TYPE_IDENTIFIER,
                          TOKEN_TYPE_LEFT_BRACKET, TOKEN_TYPE_RIGHT_BRACKET,
                          TOKEN_TYPE_COLON,        TOKEN_TYPE_EOL,
                          TOKEN_TYPE_INDENT,       TOKEN_TYPE_KEYWORD,
                          TOKEN_TYPE_IDENTIFIER,   TOKEN_TYPE_ASSIGN,
                          TOKEN_TYPE_INT_NUMBER,   TOKEN_TYPE_EOL,
                          TOKEN_TYPE_KEYWORD,      TOKEN_TYPE_IDENTIFIER,
                          TOKEN_TYPE_ASSIGN,       TOKEN_TYPE_INT_NUMBER,
                          TOKEN_TYPE_EOL,          TOKEN_TYPE_DEDENT,
                          TOKEN_TYPE_KEYWORD,      TOKEN_TYPE_IDENTIFIER,
                          TOKEN_TYPE_ASSIGN,       TOKEN_TYPE_INT_NUMBER,
                          TOKEN_TYPE_EOL,          TOKEN_TYPE_EOF};
    check_tokens("Prechody odsadenia blokov (INDENT a DEDENT)", indent_input,
                 indent_types, sizeof(indent_types) / sizeof(indent_types[0]));

    // Tabulator na zaciatku neprazdneho riadku je lexikalna chyba 1
    check_error("Tabulator na zaciatku neprazdneho riadku zamietnuty",
                "\tval x = 1", SCANNER_ERROR_LEX);
    check_error("Tabulator vo vnutri bloku zamietnuty", "def f():\n\tval x = 1",
                SCANNER_ERROR_LEX);

    // V zatvorkach musi byt pokracovaci riadok odsadeny viac nez zaciatok
    // logickeho riadku
    const char *bad_paren_indent = "val x = (\n"
                                   "1 + 2\n"
                                   ")";
    check_error(
        "Pokracovaci riadok v zatvorkach nie je odsadeny viac nez zaciatok",
        bad_paren_indent, SCANNER_ERROR_LEX);
  }

  // ---------------------------------------------------------
  // ZAVERECNE VYHODNOTENIE
  // ---------------------------------------------------------
  printf(
      "\n" COLOR_BLUE
      "========================================================\n" COLOR_RESET);
  printf("CELKOVO TESTOV: %d\n", total_tests);
  printf("USPESNYCH:      %d\n", passed_tests);
  printf("NEUSPESNYCH:    %d\n", failed_tests);
  if (failed_tests == 0) {
    printf(COLOR_GREEN
           "VSETKY TESTY PRESLI SO 100%% USPESNOSTOU!\n" COLOR_RESET);
  } else {
    printf(COLOR_RED "NIEKTORE TESTY ZLYHALI!\n" COLOR_RESET);
  }
  printf(
      COLOR_BLUE
      "========================================================\n" COLOR_RESET);

  return (failed_tests == 0) ? 0 : 1;
}
