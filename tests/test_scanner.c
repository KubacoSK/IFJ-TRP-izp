/**
 * Black-Box Test Suite for IFJ26 Scanner (Base Specification)
 * Derived strictly from: Specifikace_IFJ26_a_IFJcode26.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "../error.h"
#include "../scanner.h"

// ANSI colors for clean test reporting
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED   "\033[0;31m"
#define COLOR_BLUE  "\033[0;34m"
#define COLOR_RESET "\033[0m"

static int total_tests = 0;
static int passed_tests = 0;
static int failed_tests = 0;

/**
 * Feeds a string into the scanner and checks if the expected tokens match.
 */
static bool check_tokens(const char *test_name, const char *input, const int expected_types[], int count) {
    total_tests++;
    FILE *f = tmpfile();
    if (!f) {
        fprintf(stderr, "Cannot create temp file\n");
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
            printf("  " COLOR_RED "[FAIL]" COLOR_RESET " %s: unexpected error code %d at token index %d (expected type %d)\n",
                   test_name, res, i, expected_types[i]);
            ok = false;
            break;
        }
        if ((int)tok.type != expected_types[i]) {
            printf("  " COLOR_RED "[FAIL]" COLOR_RESET " %s: token mismatch at index %d: got type %d, expected %d\n",
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
 * Feeds an invalid string and verifies that scanner returns the expected error code.
 */
static bool check_error(const char *test_name, const char *input, int expected_err) {
    total_tests++;
    FILE *f = tmpfile();
    if (!f) return false;
    fputs(input, f);
    rewind(f);

    set_source_file(f);

    Token tok;
    int res = SCANNER_TOKEN_OK;
    while ((res = get_token(&tok)) == SCANNER_TOKEN_OK) {
        if (tok.type == TOKEN_TYPE_EOF) break;
        free_token_attribute(&tok);
    }

    fclose(f);
    if (res == expected_err) {
        printf("  " COLOR_GREEN "[PASS]" COLOR_RESET " %s (rejected with code %d)\n", test_name, res);
        passed_tests++;
        return true;
    } else {
        printf("  " COLOR_RED "[FAIL]" COLOR_RESET " %s: expected error %d, but scanner returned %d\n",
               test_name, expected_err, res);
        failed_tests++;
        return false;
    }
}

int main(void) {
    printf(COLOR_BLUE "========================================================\n" COLOR_RESET);
    printf(COLOR_BLUE "       IFJ26 SCANNER STRICT BLACK-BOX TEST SUITE        \n" COLOR_RESET);
    printf(COLOR_BLUE "========================================================\n\n" COLOR_RESET);

    // ---------------------------------------------------------
    // CATEGORY 1: BASE KEYWORDS (Section 1.1)
    // ---------------------------------------------------------
    printf("--- Category 1: Base Keywords (14 keywords) ---\n");
    {
        const char *kw_input = "def do Double else if import Int return String then Unit val var while";
        int kw_types[] = {
            TOKEN_TYPE_KEYWORD, TOKEN_TYPE_KEYWORD, TOKEN_TYPE_KEYWORD, TOKEN_TYPE_KEYWORD,
            TOKEN_TYPE_KEYWORD, TOKEN_TYPE_KEYWORD, TOKEN_TYPE_KEYWORD, TOKEN_TYPE_KEYWORD,
            TOKEN_TYPE_KEYWORD, TOKEN_TYPE_KEYWORD, TOKEN_TYPE_KEYWORD, TOKEN_TYPE_KEYWORD,
            TOKEN_TYPE_KEYWORD, TOKEN_TYPE_KEYWORD,
            TOKEN_TYPE_EOL, TOKEN_TYPE_EOF
        };
        check_tokens("All 14 base keywords recognized", kw_input, kw_types, sizeof(kw_types)/sizeof(kw_types[0]));

        // Case-sensitivity: Keywords with different case are IDENTIFIERS, not keywords
        const char *case_input = "Def DO double IF Val";
        int case_types[] = {
            TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_IDENTIFIER,
            TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_IDENTIFIER,
            TOKEN_TYPE_EOL, TOKEN_TYPE_EOF
        };
        check_tokens("Keywords are case-sensitive (Def/DO/Val are identifiers)", case_input, case_types, sizeof(case_types)/sizeof(case_types[0]));
    }

    // ---------------------------------------------------------
    // CATEGORY 2: IDENTIFIERS & UNDERSCORE RULES
    // ---------------------------------------------------------
    printf("\n--- Category 2: Identifiers & Underscore Rules ---\n");
    {
        const char *id_input = "x myVar _internal __private counter123 a_b_c";
        int id_types[] = {
            TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_IDENTIFIER,
            TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_IDENTIFIER,
            TOKEN_TYPE_EOL, TOKEN_TYPE_EOF
        };
        check_tokens("Valid identifiers starting with letter or underscore", id_input, id_types, sizeof(id_types)/sizeof(id_types[0]));

        // Spec 1.1: "Samotné podtržítko není identifikátor a využito bude v rozšířeních."
        // Scanner emits distinct TOKEN_TYPE_UNDERSCORE token
        const char *underscore_input = "_";
        int underscore_types[] = { TOKEN_TYPE_UNDERSCORE, TOKEN_TYPE_EOL, TOKEN_TYPE_EOF };
        check_tokens("Standalone underscore emits TOKEN_TYPE_UNDERSCORE", underscore_input, underscore_types, sizeof(underscore_types)/sizeof(underscore_types[0]));

        const char *underscore_expr = "val x = _";
        int underscore_expr_types[] = {
            TOKEN_TYPE_KEYWORD, TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_ASSIGN, TOKEN_TYPE_UNDERSCORE,
            TOKEN_TYPE_EOL, TOKEN_TYPE_EOF
        };
        check_tokens("Underscore in expression emits TOKEN_TYPE_UNDERSCORE", underscore_expr, underscore_expr_types, sizeof(underscore_expr_types)/sizeof(underscore_expr_types[0]));
    }

    // ---------------------------------------------------------
    // CATEGORY 3: @main ANNOTATION
    // ---------------------------------------------------------
    printf("\n--- Category 3: @main Annotation ---\n");
    {
        const char *main_input = "@main def run(): Unit =";
        int main_types[] = {
            TOKEN_TYPE_MAIN, TOKEN_TYPE_KEYWORD, TOKEN_TYPE_IDENTIFIER,
            TOKEN_TYPE_LEFT_BRACKET, TOKEN_TYPE_RIGHT_BRACKET,
            TOKEN_TYPE_COLON, TOKEN_TYPE_KEYWORD, TOKEN_TYPE_ASSIGN,
            TOKEN_TYPE_EOL, TOKEN_TYPE_EOF
        };
        check_tokens("Valid @main annotation on function", main_input, main_types, sizeof(main_types)/sizeof(main_types[0]));

        // Spec 2: "@ se v jiném kontextu nepoužívá, mezi ním a main nesmí být žádný znak"
        check_error("Invalid annotation @foo", "@foo", SCANNER_ERROR_LEX);
        check_error("Space between @ and main '@ main'", "@ main", SCANNER_ERROR_LEX);
        check_error("Prefix identifier @mainApp", "@mainApp", SCANNER_ERROR_LEX);
        check_error("Standalone '@'", "@", SCANNER_ERROR_LEX);
    }

    // ---------------------------------------------------------
    // CATEGORY 4: INTEGER LITERALS (Section 1.1)
    // ---------------------------------------------------------
    printf("\n--- Category 4: Integer Literals ---\n");
    {
        const char *int_input = "0 1 42 1_000_000 9_9_9";
        int int_types[] = {
            TOKEN_TYPE_INT_NUMBER, TOKEN_TYPE_INT_NUMBER, TOKEN_TYPE_INT_NUMBER,
            TOKEN_TYPE_INT_NUMBER, TOKEN_TYPE_INT_NUMBER,
            TOKEN_TYPE_EOL, TOKEN_TYPE_EOF
        };
        check_tokens("Valid integers with and without underscores", int_input, int_types, sizeof(int_types)/sizeof(int_types[0]));

        // Spec 1.1: "Nenulový literál nesmí začínat nulou."
        check_error("Leading zero '01' rejected", "01", SCANNER_ERROR_LEX);
        check_error("Leading zero '00' rejected", "00", SCANNER_ERROR_LEX);
        check_error("Leading zero '0123' rejected", "0123", SCANNER_ERROR_LEX);

        // Spec 1.1: "Jiné číselné soustavy a sufix L nejsou podporovány."
        check_error("Hexadecimal '0x10' rejected", "0x10", SCANNER_ERROR_LEX);
        check_error("Hexadecimal '0XFF' rejected", "0XFF", SCANNER_ERROR_LEX);
        check_error("Suffix '12L' rejected", "12L", SCANNER_ERROR_LEX);
        check_error("Suffix '42l' rejected", "42l", SCANNER_ERROR_LEX);

        // Spec 1.1: Underscores must be between two digits
        check_error("Trailing underscore '123_' rejected", "123_", SCANNER_ERROR_LEX);
        check_error("Consecutive underscores '1__0' rejected", "1__0", SCANNER_ERROR_LEX);
        check_error("Underscore on zero '0_' rejected", "0_", SCANNER_ERROR_LEX);
    }

    // ---------------------------------------------------------
    // CATEGORY 5: DOUBLE LITERALS (Section 1.1)
    // ---------------------------------------------------------
    printf("\n--- Category 5: Double Literals ---\n");
    {
        const char *dbl_input = "0.0 12.34 .5 1.2e-3 12E+5 10e2 1.5d 100D";
        int dbl_types[] = {
            TOKEN_TYPE_DOUBLE_NUMBER, TOKEN_TYPE_DOUBLE_NUMBER, TOKEN_TYPE_DOUBLE_NUMBER,
            TOKEN_TYPE_DOUBLE_NUMBER, TOKEN_TYPE_DOUBLE_NUMBER, TOKEN_TYPE_DOUBLE_NUMBER,
            TOKEN_TYPE_DOUBLE_NUMBER, TOKEN_TYPE_DOUBLE_NUMBER,
            TOKEN_TYPE_EOL, TOKEN_TYPE_EOF
        };
        check_tokens("Valid double formats (standard, dot-start, exp, d/D suffix)", dbl_input, dbl_types, sizeof(dbl_types)/sizeof(dbl_types[0]));

        // Method call on Int: 12.toString MUST scan as INT(12), DOT, IDENTIFIER("toString")
        const char *dot_call = "12.toString";
        int dot_call_types[] = {
            TOKEN_TYPE_INT_NUMBER, TOKEN_TYPE_DOT, TOKEN_TYPE_IDENTIFIER,
            TOKEN_TYPE_EOL, TOKEN_TYPE_EOF
        };
        check_tokens("Int member access '12.toString' separated cleanly", dot_call, dot_call_types, sizeof(dot_call_types)/sizeof(dot_call_types[0]));

        // Spec 1.1: "Sufixy f a F podporovány nejsou."
        check_error("Suffix '1.5f' rejected", "1.5f", SCANNER_ERROR_LEX);
        check_error("Suffix '1.5F' rejected", "1.5F", SCANNER_ERROR_LEX);

        // Invalid exponents and underscores in double
        check_error("Empty exponent '1.2e' rejected", "1.2e", SCANNER_ERROR_LEX);
        check_error("Sign-only exponent '1.2e+' rejected", "1.2e+", SCANNER_ERROR_LEX);
        check_error("Underscore adjacent to dot '1_.2' rejected", "1_.2", SCANNER_ERROR_LEX);
        check_error("Trailing underscore in double '1.2_' rejected", "1.2_", SCANNER_ERROR_LEX);
        check_error("Underscore adjacent to exp '1.2e_3' rejected", "1.2e_3", SCANNER_ERROR_LEX);
    }

    // ---------------------------------------------------------
    // CATEGORY 6: STRINGS & ESCAPE SEQUENCES (Section 1.1)
    // ---------------------------------------------------------
    printf("\n--- Category 6: Strings & Escape Sequences ---\n");
    {
        // Single line strings with all allowed escapes: \\, \", \n, \r, \t
        const char *str_input = "\"hello\" \"escapes: \\\\ \\\" \\n \\r \\t\" \"\"";
        int str_types[] = {
            TOKEN_TYPE_STRING, TOKEN_TYPE_STRING, TOKEN_TYPE_STRING,
            TOKEN_TYPE_EOL, TOKEN_TYPE_EOF
        };
        check_tokens("Single-line strings with valid escapes and empty string", str_input, str_types, sizeof(str_types)/sizeof(str_types[0]));

        // Multi-line strings """..."""
        const char *multi_input = "\"\"\"Line 1\nLine 2\nLine 3\"\"\"";
        int multi_types[] = {
            TOKEN_TYPE_STRING,
            TOKEN_TYPE_EOL, TOKEN_TYPE_EOF
        };
        check_tokens("Multi-line string preserving literal newlines", multi_input, multi_types, sizeof(multi_types)/sizeof(multi_types[0]));

        // Spec 1.1: Only \\, \", \n, \r, \t are allowed in single-line strings
        check_error("Invalid hex escape '\\x41' rejected", "\"hello \\x41\"", SCANNER_ERROR_LEX);
        check_error("Invalid escape '\\a' rejected", "\"hello \\a\"", SCANNER_ERROR_LEX);
        check_error("Invalid escape '\\0' rejected", "\"hello \\0\"", SCANNER_ERROR_LEX);

        // Unclosed strings
        check_error("Unclosed single-line string rejected", "\"unclosed string", SCANNER_ERROR_LEX);
        check_error("Unclosed multi-line string rejected", "\"\"\"unclosed multiline", SCANNER_ERROR_LEX);
        check_error("Literal unescaped newline in single-line string rejected", "\"first\nsecond\"", SCANNER_ERROR_LEX);
    }

    // ---------------------------------------------------------
    // CATEGORY 7: COMMENTS (Section 1.1)
    // ---------------------------------------------------------
    printf("\n--- Category 7: Comments ---\n");
    {
        const char *cmt_input =
            "val a = 1 // line comment\n"
            "val b = /* inline block */ 2\n"
            "val c = /* nested /* comment */ here */ 3";
        int cmt_types[] = {
            TOKEN_TYPE_KEYWORD, TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_ASSIGN, TOKEN_TYPE_INT_NUMBER, TOKEN_TYPE_EOL,
            TOKEN_TYPE_KEYWORD, TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_ASSIGN, TOKEN_TYPE_INT_NUMBER, TOKEN_TYPE_EOL,
            TOKEN_TYPE_KEYWORD, TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_ASSIGN, TOKEN_TYPE_INT_NUMBER, TOKEN_TYPE_EOL,
            TOKEN_TYPE_EOF
        };
        check_tokens("Line comments, inline block comments, and nested block comments", cmt_input, cmt_types, sizeof(cmt_types)/sizeof(cmt_types[0]));

        // Spec 1.1: Multiline block comment rule:
        // "V opačném případě se chová jako jeden konec řádku a za jeho koncem nesmí být další tokeny"
        check_error("Token on same line after multi-line comment rejected", "/* line1\nline2 */ val x = 1", SCANNER_ERROR_LEX);
        check_error("Unclosed block comment rejected", "/* unclosed comment", SCANNER_ERROR_LEX);
        check_error("Unclosed nested block comment rejected", "/* outer /* inner */", SCANNER_ERROR_LEX);
    }

    // ---------------------------------------------------------
    // CATEGORY 8: BASE OPERATORS & DELIMITERS (Section 3)
    // ---------------------------------------------------------
    printf("\n--- Category 8: Base Operators & Delimiters ---\n");
    {
        const char *op_input = "+ - * / == != < <= > >= = ( ) , : ;";
        int op_types[] = {
            TOKEN_TYPE_PLUS, TOKEN_TYPE_MINUS, TOKEN_TYPE_MUL, TOKEN_TYPE_DIV,
            TOKEN_TYPE_EQ, TOKEN_TYPE_NEQ, TOKEN_TYPE_LT, TOKEN_TYPE_LEQ, TOKEN_TYPE_GT, TOKEN_TYPE_GEQ,
            TOKEN_TYPE_ASSIGN,
            TOKEN_TYPE_LEFT_BRACKET, TOKEN_TYPE_RIGHT_BRACKET,
            TOKEN_TYPE_COMMA, TOKEN_TYPE_COLON, TOKEN_TYPE_SEMICOLON,
            TOKEN_TYPE_EOL, TOKEN_TYPE_EOF
        };
        check_tokens("All base arithmetic, relational, and punctuation tokens", op_input, op_types, sizeof(op_types)/sizeof(op_types[0]));

        // Unary minus is an operator, not part of integer literal
        const char *unary_input = "-42";
        int unary_types[] = {
            TOKEN_TYPE_MINUS, TOKEN_TYPE_INT_NUMBER,
            TOKEN_TYPE_EOL, TOKEN_TYPE_EOF
        };
        check_tokens("Negative integer '-42' parsed as MINUS and INT(42)", unary_input, unary_types, sizeof(unary_types)/sizeof(unary_types[0]));

        // Operators that only belong to extensions MUST be rejected in Base spec:
        check_error("Standalone '!' rejected in base spec (only != allowed)", "!", SCANNER_ERROR_LEX);
        check_error("Logical AND '&' rejected", "&", SCANNER_ERROR_LEX);
        check_error("Logical OR '|' rejected", "|", SCANNER_ERROR_LEX);
        check_error("Square bracket '[' rejected", "[", SCANNER_ERROR_LEX);
        check_error("Square bracket ']' rejected", "]", SCANNER_ERROR_LEX);
        check_error("Curly bracket '{' rejected", "{", SCANNER_ERROR_LEX);
        check_error("Curly bracket '}' rejected", "}", SCANNER_ERROR_LEX);
        check_error("Non-ASCII character '$' rejected", "$", SCANNER_ERROR_LEX);
    }

    // ---------------------------------------------------------
    // CATEGORY 9: INDENTATION & OFF-SIDE RULE (Section 1.2)
    // ---------------------------------------------------------
    printf("\n--- Category 9: Indentation & Off-side Rule ---\n");
    {
        const char *indent_input =
            "def test(): Unit =\n"
            "    val a = 1\n"
            "    val b = 2\n"
            "val c = 3";
        int indent_types[] = {
            TOKEN_TYPE_KEYWORD, TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_LEFT_BRACKET, TOKEN_TYPE_RIGHT_BRACKET,
            TOKEN_TYPE_COLON, TOKEN_TYPE_KEYWORD, TOKEN_TYPE_ASSIGN, TOKEN_TYPE_EOL,
            TOKEN_TYPE_INDENT,
            TOKEN_TYPE_KEYWORD, TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_ASSIGN, TOKEN_TYPE_INT_NUMBER, TOKEN_TYPE_EOL,
            TOKEN_TYPE_KEYWORD, TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_ASSIGN, TOKEN_TYPE_INT_NUMBER, TOKEN_TYPE_EOL,
            TOKEN_TYPE_DEDENT,
            TOKEN_TYPE_KEYWORD, TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_ASSIGN, TOKEN_TYPE_INT_NUMBER, TOKEN_TYPE_EOL,
            TOKEN_TYPE_EOF
        };
        check_tokens("Block indentation transitions (INDENT and DEDENT)", indent_input, indent_types, sizeof(indent_types)/sizeof(indent_types[0]));

        // Spec 1.2: "tabulátor na začátku neprázdného řádku je lexikální chyba 1"
        check_error("Tab character at start of non-empty line rejected", "\tval x = 1", SCANNER_ERROR_LEX);
        check_error("Tab indentation inside block rejected", "def foo(): Unit =\n\tval x = 1", SCANNER_ERROR_LEX);

        // Spec 1.2: Inside parentheses, continuation line MUST be indented more than logical line start
        check_error("Parentheses continuation line not indented more than start", "val x = foo(\n1)", SCANNER_ERROR_LEX);
    }

    // ---------------------------------------------------------
    // FINAL RESULTS
    // ---------------------------------------------------------
    printf(COLOR_BLUE "\n========================================================\n" COLOR_RESET);
    printf("TOTAL TESTS:  %d\n", total_tests);
    printf("PASSED:       " COLOR_GREEN "%d" COLOR_RESET "\n", passed_tests);
    if (failed_tests > 0) {
        printf("FAILED:       " COLOR_RED "%d" COLOR_RESET "\n", failed_tests);
    } else {
        printf("FAILED:       0\n");
        printf(COLOR_GREEN "ALL TESTS PASSED WITH 100%% SUCCESS!\n" COLOR_RESET);
    }
    printf(COLOR_BLUE "========================================================\n" COLOR_RESET);

    return failed_tests > 0 ? 1 : 0;
}
