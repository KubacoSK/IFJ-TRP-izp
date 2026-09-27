/**
 * Project: Implementation of a Compiler for the Imperative Language IFJ26.
 *
 * @file scanner.c
 * @brief Clean, robust lexical analyzer for IFJ26 base language (Scala 3 subset).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include "scanner.h"
#include "error.h"

#define BUFFER_CHUNK 32
#define MAX_INDENT_LEVELS 128
#define UNGET_BUFFER_SIZE 5

typedef struct {
    char *data;
    size_t len;
    size_t cap;
} Buffer;

static bool buf_init(Buffer *b) {
    b->len = 0; b->cap = BUFFER_CHUNK;
    if (!(b->data = (char *)malloc(b->cap))) return false;
    b->data[0] = '\0';
    return true;
}

static bool buf_add(Buffer *b, char c) {
    if (b->len + 1 >= b->cap) {
        char *ndata = (char *)realloc(b->data, b->cap * 2);
        if (!ndata) return false;
        b->data = ndata; b->cap *= 2;
    }
    b->data[b->len++] = c;
    b->data[b->len] = '\0';
    return true;
}

static void buf_free(Buffer *b) {
    if (b->data) free(b->data);
    b->data = NULL; b->len = b->cap = 0;
}

static const struct { const char *name; Keyword kw; } KEYWORDS[] = {
    {"def", KEYWORD_DEF},       {"do", KEYWORD_DO},
    {"Double", KEYWORD_DOUBLE}, {"else", KEYWORD_ELSE},
    {"if", KEYWORD_IF},         {"import", KEYWORD_IMPORT},
    {"Int", KEYWORD_INT},       {"return", KEYWORD_RETURN},
    {"String", KEYWORD_STRING}, {"then", KEYWORD_THEN},
    {"Unit", KEYWORD_UNIT},     {"val", KEYWORD_VAL},
    {"var", KEYWORD_VAR},       {"while", KEYWORD_WHILE}
};
#define NUM_KEYWORDS (sizeof(KEYWORDS) / sizeof(KEYWORDS[0]))

// InternÃ½ stav scanneru
static FILE *source_file = NULL;
static int indent_stack[MAX_INDENT_LEVELS];
static int indent_level = 0;
static int pending_dedents = 0;
static int paren_depth = 0;
static int logical_line_indent = 0;
static bool is_at_line_start = true;
static bool logical_line_has_tokens = false;
static bool eof_reached = false;
static Token unget_buf[UNGET_BUFFER_SIZE];
static int unget_top = -1;

void set_source_file(FILE *f) {
    source_file = f;
    reset_scanner();
}

void reset_scanner(void) {
    indent_stack[0] = indent_level = pending_dedents = paren_depth = logical_line_indent = 0;
    is_at_line_start = true;
    logical_line_has_tokens = eof_reached = false;
    while (unget_top >= 0) free_token_attribute(&unget_buf[unget_top--]);
}

void free_token_attribute(Token *token) {
    if (token && (token->type == TOKEN_TYPE_IDENTIFIER || token->type == TOKEN_TYPE_STRING)) {
        free(token->attribute.string);
        token->attribute.string = NULL;
    }
}

int unget_token(Token token) {
    if (unget_top >= UNGET_BUFFER_SIZE - 1) {
        free_token_attribute(&token);
        return ERROR_INTERNAL;
    }
    if (token.type == TOKEN_TYPE_LEFT_PAREN && paren_depth > 0) paren_depth--;
    else if (token.type == TOKEN_TYPE_RIGHT_PAREN) paren_depth++;
    unget_buf[++unget_top] = token;
    return SCANNER_TOKEN_OK;
}

static inline int emit_token(Token *token, TokenType type) {
    logical_line_has_tokens = true;
    token->type = type;
    return SCANNER_TOKEN_OK;
}

static inline int get_char(void) {
    int c = getc(source_file);
    if (c == '\r') {
        int next = getc(source_file);
        if (next == '\n') return '\n';
        if (next != EOF) ungetc(next, source_file);
    }
    return c;
}

static int handle_eof(Token *token) {
    eof_reached = true;
    if (logical_line_has_tokens) {
        logical_line_has_tokens = false;
        token->type = TOKEN_TYPE_EOL;
        return SCANNER_TOKEN_OK;
    }
    if (indent_level > 0) {
        indent_level--;
        token->type = TOKEN_TYPE_DEDENT;
        return SCANNER_TOKEN_OK;
    }
    token->type = TOKEN_TYPE_EOF;
    return SCANNER_TOKEN_OK;
}

static int skip_block_comment(bool *out_has_newline) {
    int nest = 1;
    *out_has_newline = false;
    while (nest > 0) {
        int c = get_char();
        if (c == EOF) return SCANNER_ERROR_LEX;
        if (c == '\n') *out_has_newline = true;
        else if (c == '/' || c == '*') {
            int n = getc(source_file);
            if (c == '/' && n == '*') nest++;
            else if (c == '*' && n == '/') nest--;
            else if (n != EOF) ungetc(n, source_file);
        }
    }
    return SCANNER_TOKEN_OK;
}

static int verify_rest_of_multiline_line(void) {
    int c;
    while ((c = get_char()) != '\n' && c != EOF) {
        if (c == ' ' || c == '\t') continue;
        if (c == '/') {
            int n = getc(source_file);
            if (n == '/') {
                while ((c = get_char()) != '\n' && c != EOF);
                return SCANNER_TOKEN_OK;
            }
            if (n == '*') {
                bool nl = false;
                int res = skip_block_comment(&nl);
                if (res != SCANNER_TOKEN_OK) return res;
                continue;
            }
            if (n != EOF) ungetc(n, source_file);
        }
        return SCANNER_ERROR_LEX;
    }
    return SCANNER_TOKEN_OK;
}

static int skip_to_next_char(int *out_char, int *spaces, bool *tab_found) {
    while (1) {
        int c = get_char();
        if (c == ' ') { if (spaces) (*spaces)++; continue; }
        if (c == '\t') { if (tab_found) *tab_found = true; continue; }
        if (c == '/') {
            int n = getc(source_file);
            if (n == '/') {
                while ((c = get_char()) != '\n' && c != EOF);
                *out_char = c;
                return SCANNER_TOKEN_OK;
            }
            if (n == '*') {
                bool nl = false;
                int res = skip_block_comment(&nl);
                if (res != SCANNER_TOKEN_OK) return res;
                if (nl) {
                    int chk = verify_rest_of_multiline_line();
                    if (chk != SCANNER_TOKEN_OK) return chk;
                    *out_char = '\n';
                    return SCANNER_TOKEN_OK;
                }
                continue;
            }
            if (n != EOF) ungetc(n, source_file);
        }
        *out_char = c;
        return SCANNER_TOKEN_OK;
    }
}

static int scan_digits_with_underscores(Buffer *buf, int *next_char) {
    int c = get_char();
    while (isdigit(c) || c == '_') {
        if (c == '_') {
            int peek = get_char();
            if (!isdigit(peek)) return SCANNER_ERROR_LEX;
            c = peek;
        }
        if (!buf_add(buf, (char)c)) return ERROR_INTERNAL;
        c = get_char();
    }
    *next_char = c;
    return SCANNER_TOKEN_OK;
}

static int scan_number(Token *token, int first_char) {
    Buffer buf;
    if (!buf_init(&buf)) return ERROR_INTERNAL;
    bool is_double = false;
    int c = first_char, res;

#define SCAN_MORE() do { \
        if ((res = scan_digits_with_underscores(&buf, &c)) != SCANNER_TOKEN_OK) { \
            buf_free(&buf); return res; \
        } \
    } while (0)

    if (c == '.') {
        is_double = true;
        int frac = get_char();
        if (!isdigit(frac)) { buf_free(&buf); return SCANNER_ERROR_LEX; }
        if (!buf_add(&buf, '0') || !buf_add(&buf, '.') || !buf_add(&buf, (char)frac)) {
            buf_free(&buf); return ERROR_INTERNAL;
        }
        SCAN_MORE();
    } else if (c == '0') {
        if (!buf_add(&buf, '0')) { buf_free(&buf); return ERROR_INTERNAL; }
        int next = get_char();
        if (next == 'x' || next == 'X' || isdigit(next) || next == '_') {
            buf_free(&buf); return SCANNER_ERROR_LEX;
        }
        c = next;
    } else {
        if (!buf_add(&buf, (char)c)) { buf_free(&buf); return ERROR_INTERNAL; }
        SCAN_MORE();
    }

    if (!is_double && c == '.') {
        int peek = get_char();
        if (isdigit(peek)) {
            is_double = true;
            if (!buf_add(&buf, '.') || !buf_add(&buf, (char)peek)) {
                buf_free(&buf); return ERROR_INTERNAL;
            }
            SCAN_MORE();
        } else {
            if (peek != EOF) ungetc(peek, source_file);
            Token dot_tok = {.type = TOKEN_TYPE_DOT, .attribute = {.string = NULL}};
            if (unget_token(dot_tok) != SCANNER_TOKEN_OK) { buf_free(&buf); return ERROR_INTERNAL; }
            c = EOF;
        }
    }

    if (c == 'e' || c == 'E') {
        is_double = true;
        if (!buf_add(&buf, (char)c)) { buf_free(&buf); return ERROR_INTERNAL; }
        int peek = get_char();
        if (peek == '+' || peek == '-') {
            if (!buf_add(&buf, (char)peek)) { buf_free(&buf); return ERROR_INTERNAL; }
            peek = get_char();
        }
        if (!isdigit(peek) || !buf_add(&buf, (char)peek)) {
            buf_free(&buf); return isdigit(peek) ? ERROR_INTERNAL : SCANNER_ERROR_LEX;
        }
        SCAN_MORE();
    }
#undef SCAN_MORE

    if (c == 'd' || c == 'D') {
        int peek = get_char();
        if (isalnum(peek) || peek == '_') {
            if (peek != EOF) ungetc(peek, source_file);
            buf_free(&buf);
            return SCANNER_ERROR_LEX;
        }
        if (peek != EOF) ungetc(peek, source_file);
        is_double = true;
        c = EOF;
    }

    if (c != EOF) {
        if (isalnum(c) || c == '_') { buf_free(&buf); return SCANNER_ERROR_LEX; }
        ungetc(c, source_file);
    }

    token->type = is_double ? TOKEN_TYPE_DOUBLE_NUMBER : TOKEN_TYPE_INT_NUMBER;
    if (is_double) token->attribute.decimal = strtod(buf.data, NULL);
    else token->attribute.integer = (int64_t)strtoll(buf.data, NULL, 10);
    buf_free(&buf);
    return SCANNER_TOKEN_OK;
}

static int scan_singleline_string(Token *token) {
    Buffer buf;
    if (!buf_init(&buf)) return ERROR_INTERNAL;
    int c;
    while ((c = get_char()) != '"') {
        if (c == EOF || c == '\n' || (unsigned char)c < 32) {
            buf_free(&buf);
            return SCANNER_ERROR_LEX;
        }
        if (c == '\\') {
            switch (c = get_char()) {
                case '\\': case '"': break;
                case 'n': c = '\n'; break;
                case 'r': c = '\r'; break;
                case 't': c = '\t'; break;
                default: buf_free(&buf); return SCANNER_ERROR_LEX;
            }
        }
        if (!buf_add(&buf, (char)c)) { buf_free(&buf); return ERROR_INTERNAL; }
    }
    token->type = TOKEN_TYPE_STRING;
    token->attribute.string = buf.data;
    return SCANNER_TOKEN_OK;
}

static int scan_multiline_string(Token *token) {
    Buffer buf;
    if (!buf_init(&buf)) return ERROR_INTERNAL;
    int quotes = 0, c;
    while ((c = get_char()) != EOF) {
        if (c == '"') {
            if (++quotes == 3) {
                token->type = TOKEN_TYPE_STRING;
                token->attribute.string = buf.data;
                return SCANNER_TOKEN_OK;
            }
        } else {
            while (quotes > 0) {
                if (!buf_add(&buf, '"')) { buf_free(&buf); return ERROR_INTERNAL; }
                quotes--;
            }
            if (!buf_add(&buf, (char)c)) { buf_free(&buf); return ERROR_INTERNAL; }
        }
    }
    buf_free(&buf);
    return SCANNER_ERROR_LEX;
}

static int scan_string(Token *token) {
    int c2 = get_char();
    if (c2 == '"') {
        int c3 = get_char();
        if (c3 == '"') return scan_multiline_string(token);
        if (c3 != EOF) ungetc(c3, source_file);
        token->type = TOKEN_TYPE_STRING;
        token->attribute.string = (char *)calloc(1, 1);
        return token->attribute.string ? SCANNER_TOKEN_OK : ERROR_INTERNAL;
    }
    if (c2 != EOF) ungetc(c2, source_file);
    return scan_singleline_string(token);
}

static int scan_identifier_or_keyword(Token *token, int first_char) {
    Buffer buf;
    if (!buf_init(&buf)) return ERROR_INTERNAL;
    if (!buf_add(&buf, (char)first_char)) { buf_free(&buf); return ERROR_INTERNAL; }
    int c;
    while ((c = get_char()) != EOF) {
        if (isalnum(c) || c == '_') {
            if (!buf_add(&buf, (char)c)) { buf_free(&buf); return ERROR_INTERNAL; }
        } else {
            ungetc(c, source_file);
            break;
        }
    }
    if (strcmp(buf.data, "_") == 0) {
        buf_free(&buf);
        token->type = TOKEN_TYPE_UNDERSCORE;
        return SCANNER_TOKEN_OK;
    }
    for (size_t i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(buf.data, KEYWORDS[i].name) == 0) {
            token->type = TOKEN_TYPE_KEYWORD;
            token->attribute.keyword = KEYWORDS[i].kw;
            buf_free(&buf);
            return SCANNER_TOKEN_OK;
        }
    }
    token->type = TOKEN_TYPE_IDENTIFIER;
    token->attribute.string = buf.data;
    return SCANNER_TOKEN_OK;
}

static int scan_annotation_main(Token *token) {
    char buf[5] = {0};
    for (int i = 0; i < 4; i++) {
        int ch = get_char();
        if (ch == EOF) return SCANNER_ERROR_LEX;
        buf[i] = (char)ch;
    }
    if (strcmp(buf, "main") != 0) return SCANNER_ERROR_LEX;
    int next = get_char();
    if (next != EOF) {
        ungetc(next, source_file);
        if (isalnum(next) || next == '_') return SCANNER_ERROR_LEX;
    }
    return emit_token(token, TOKEN_TYPE_MAIN);
}

static int emit_match_or_single(Token *token, char expected, TokenType matched, TokenType single) {
    int next = get_char();
    if (next == expected) return emit_token(token, matched);
    if (next != EOF) ungetc(next, source_file);
    return (single == (TokenType)-1) ? SCANNER_ERROR_LEX : emit_token(token, single);
}

int get_token(Token *token) {
    if (!token || !source_file) return ERROR_INTERNAL;
    token->attribute.string = NULL;

    if (unget_top >= 0) {
        *token = unget_buf[unget_top--];
        if (token->type == TOKEN_TYPE_LEFT_PAREN) paren_depth++;
        else if (token->type == TOKEN_TYPE_RIGHT_PAREN && paren_depth > 0) paren_depth--;
        return SCANNER_TOKEN_OK;
    }

    if (pending_dedents > 0) {
        pending_dedents--;
        token->type = TOKEN_TYPE_DEDENT;
        return SCANNER_TOKEN_OK;
    }

    if (eof_reached) return handle_eof(token);

    while (1) {
        // Kontrola odsadenia na zaÄiatku novÃ©ho fyzickÃ©ho riadku
        while (is_at_line_start) {
            int spaces = 0;
            bool tab_found = false;
            int c;
            int res = skip_to_next_char(&c, &spaces, &tab_found);
            if (res != SCANNER_TOKEN_OK) return res;

            if (c == '\n') continue;
            if (c == EOF) return handle_eof(token);
            if (tab_found) return SCANNER_ERROR_LEX;

            if (paren_depth > 0) {
                if (c == ')' ? spaces < logical_line_indent : spaces <= logical_line_indent) {
                    return SCANNER_ERROR_LEX;
                }
                is_at_line_start = false;
                ungetc(c, source_file);
                break;
            }

            int current_indent = indent_stack[indent_level];
            logical_line_indent = spaces;
            is_at_line_start = false;
            ungetc(c, source_file);

            if (spaces > current_indent) {
                if (indent_level + 1 >= MAX_INDENT_LEVELS) return ERROR_INTERNAL;
                indent_stack[++indent_level] = spaces;
                token->type = TOKEN_TYPE_INDENT;
                return SCANNER_TOKEN_OK;
            }
            if (spaces < current_indent) {
                int target = -1;
                for (int i = indent_level - 1; i >= 0; i--) {
                    if (indent_stack[i] == spaces) { target = i; break; }
                }
                if (target == -1) return SCANNER_ERROR_LEX;
                pending_dedents = (indent_level - target) - 1;
                indent_level = target;
                token->type = TOKEN_TYPE_DEDENT;
                return SCANNER_TOKEN_OK;
            }
            break;
        }

        // ÄŒÃtanie tokenu na logickom riadku
        int c;
        int res = skip_to_next_char(&c, NULL, NULL);
        if (res != SCANNER_TOKEN_OK) return res;

        if (c == '\n') {
            is_at_line_start = true;
            if (paren_depth > 0 || !logical_line_has_tokens) continue;
            logical_line_has_tokens = false;
            token->type = TOKEN_TYPE_EOL;
            return SCANNER_TOKEN_OK;
        }

        if (c == EOF) return handle_eof(token);
        if (c == '/') return emit_token(token, TOKEN_TYPE_DIV);

        switch (c) {
            case '(': paren_depth++; return emit_token(token, TOKEN_TYPE_LEFT_PAREN);
            case ')': if (paren_depth > 0) paren_depth--; return emit_token(token, TOKEN_TYPE_RIGHT_PAREN);
            case '+': return emit_token(token, TOKEN_TYPE_PLUS);
            case '-': return emit_token(token, TOKEN_TYPE_MINUS);
            case '*': return emit_token(token, TOKEN_TYPE_MUL);
            case ',': return emit_token(token, TOKEN_TYPE_COMMA);
            case ':': return emit_token(token, TOKEN_TYPE_COLON);
            case ';': return emit_token(token, TOKEN_TYPE_SEMICOLON);
            case '=': return emit_match_or_single(token, '=', TOKEN_TYPE_EQ, TOKEN_TYPE_ASSIGN);
            case '!': return emit_match_or_single(token, '=', TOKEN_TYPE_NEQ, (TokenType)-1);
            case '<': return emit_match_or_single(token, '=', TOKEN_TYPE_LEQ, TOKEN_TYPE_LT);
            case '>': return emit_match_or_single(token, '=', TOKEN_TYPE_GEQ, TOKEN_TYPE_GT);
            case '@': return scan_annotation_main(token);
            case '.': {
                int next = get_char();
                if (isdigit(next)) {
                    ungetc(next, source_file);
                    int nres = scan_number(token, '.');
                    if (nres == SCANNER_TOKEN_OK) logical_line_has_tokens = true;
                    return nres;
                }
                if (next != EOF) ungetc(next, source_file);
                return emit_token(token, TOKEN_TYPE_DOT);
            }
            case '"': {
                int sres = scan_string(token);
                if (sres == SCANNER_TOKEN_OK) logical_line_has_tokens = true;
                return sres;
            }
            default: {
                int dres;
                if (isalpha(c) || c == '_') dres = scan_identifier_or_keyword(token, c);
                else if (isdigit(c)) dres = scan_number(token, c);
                else return SCANNER_ERROR_LEX;
                if (dres == SCANNER_TOKEN_OK) logical_line_has_tokens = true;
                return dres;
            }
        }
    }
}