#include "preprocessor.h"

#define line_pos(lexer, pos) ((pos >= lexer->length) ? lexer->line_map[lexer->length] : lexer->line_map[pos])
#define column_pos(lexer, pos) ((pos >= lexer->length) ? lexer->column_map[lexer->length] : lexer->column_map[pos])
#define peek_char(lexer) ((lexer->pos >= lexer->length) ? '\0' : lexer->source_code[lexer->pos])
#define next_char(lexer) ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1])
#define unget_char(lexer) \
    if (lexer->pos > 0) lexer->pos -= 1
#define is_hex_digit(c) (is_digit(c) || ((c) >= 'a' && (c) <= 'f') || ((c) >= 'A' && (c) <= 'F'))
#define is_oct_digit(c) ((c) >= '0' && (c) <= '7')
#define pp_lexer_error(message, pos) fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", (has_error = true, lexer->filename), line_pos(lexer, pos), column_pos(lexer, pos), message)
#define content_string(start) create_string(&lexer->source_code[start], min(lexer->pos, lexer->length) - start)

static bool has_error = false;

static void track_include(ppLexer* lx, ppToken* t) {
    if (t->type == PP_SYMBOL && t->value == SYMBOL_HASH && t->at_line_start)
        lx->include_state = 1;
    else if (lx->include_state == 1 && t->type == PP_IDENTIFIER && t->value == P_INCLUDE)
        lx->include_state = 2;
    else
        lx->include_state = 0;
}

static void add_pp_token(ppLexer* lexer, ppTokenType type, string value, size_t pos) {
    ppToken* t = create_pp_token(type, value, lexer, pos);
    t->space_before = lexer->pending_space;
    t->at_line_start = lexer->line_start;
    track_include(lexer, t);
    append(lexer->pp_tokens, t);
    lexer->pending_space = false;
    lexer->line_start = (type == PP_NEWLINE);
}

ppToken* create_pp_token(ppTokenType type, string value, ppLexer* lexer, size_t pos) {
    ppToken* t = create_struct(ppToken);
    t->type = type;
    t->value = value;
    t->line = line_pos(lexer, pos);
    t->column = column_pos(lexer, pos);
    t->filename = lexer->filename;
    t->space_before = false;
    t->at_line_start = false;
    t->hideset = NULL;
    t->expanded_from = NULL;
    return t;
}

static void normalize(ppLexer* lexer, string source_code) {
    const string src = source_code;
    size_t source_len = strlen(source_code);
    string buffer = (string)alloc_memory(source_len + 2, false);
    lexer->line_map = alloc_memory(sizeof(size_t) * (source_len + 2), true);
    lexer->column_map = alloc_memory(sizeof(size_t) * (source_len + 2), true);
    size_t size = 0;
    size_t line = 1, column = 1;
    for (size_t i = 0; i < source_len;) {
        char c = src[i];
        if (c == '\r') {
            if (i + 1 < source_len && src[i + 1] == '\n')
                i++;
            c = '\n';
        }
        if (c == '\\') {
            size_t j = i + 1;
            bool has_space = false;
            while (j < source_len && (src[j] == ' ' || src[j] == '\t')) {
                j++;
                has_space = true;
            }
            char n = (j < source_len) ? src[j] : '\0';
            bool newline = false;
            if (n == '\n') {
                j++;
                newline = true;
            } else if (n == '\r') {
                j++;
                if (j < source_len && src[j] == '\n')
                    j++;
                newline = true;
            }
            if (newline) {
                if (has_space)
                    fprintf(stderr, "[Syntax Warning] at %s:%zu:%zu: Backslash and newline separated by space\n", lexer->filename, line, column);
                line++;
                column = 1;
                i = j;
                continue;
            }
        }
        buffer[size] = c;
        lexer->line_map[size] = line;
        lexer->column_map[size] = column;
        size++;
        if (c == '\n') {
            line++;
            column = 1;
        } else
            column++;
        i++;
    }
    if (size == 0 || buffer[size - 1] != '\n') {
        lexer->line_map[size] = line;
        lexer->column_map[size] = column;
        buffer[size++] = '\n';
        column = 1;
        line++;
    }
    buffer[size] = '\0';
    lexer->line_map[size] = line;
    lexer->column_map[size] = column;
    lexer->source_code = buffer;
    lexer->length = size;
}

ppLexer* create_pp_lexer(string filename, string source_code) {
    ppLexer* lexer = create_struct(ppLexer);
    if (source_code == NULL) {
        fprintf(stderr, "[Preprocessor Error] at <create_pp_lexer>: Failed to create ppLexer, source_code is NULL\n");
        has_error = true;
        return NULL;
    }
    lexer->source_code = NULL;
    lexer->length = 0;
    lexer->pos = 0;
    lexer->filename = filename;
    lexer->pp_tokens = create_list(ppToken*);
    lexer->line_map = NULL;
    lexer->column_map = NULL;
    lexer->include_state = 0;
    lexer->pending_space = false;
    lexer->line_start = true;
    normalize(lexer, source_code);
    return lexer;
}

bool pp_lexer(ppLexer* lexer) {
    has_error = false;
    while (true) {
        char c = next_char(lexer);
        if (c == '\0') {
            add_pp_token(lexer, PP_EOF, NULL, lexer->length);
            return has_error;
        } else if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f') {
            if (c == '\n') add_pp_token(lexer, PP_NEWLINE, NULL, lexer->pos - 1);
            else lexer->pending_space = true;
        } else if (is_alphabet(c) || c == '_') {
            size_t start = lexer->pos - 1;
            do {
                c = next_char(lexer);
            } while (is_alphabet(c) || is_digit(c) || c == '_');
            unget_char(lexer);
            add_pp_token(lexer, PP_IDENTIFIER, content_string(start), start);
        } else if (is_digit(c) || (is_digit(peek_char(lexer)) && (c == '.'))) {
            size_t start = lexer->pos - 1;
            char p = '\0';
            c = next_char(lexer);
            while (is_digit(c) || is_alphabet(c) || c == '_' || c == '.') {
                p = c;
                c = next_char(lexer);
                if (p == 'e' || p == 'E' || p == 'p' || p == 'P') {
                    if (c == '+' || c == '-') {
                        p = c;
                        c = next_char(lexer);
                    }
                }
            }
            unget_char(lexer);
            add_pp_token(lexer, PP_NUMBER, content_string(start), start);
        } else if (c == '"') {
            bool is_header_name = (lexer->include_state == 2);
            size_t start = lexer->pos - 1;
            do {
                c = next_char(lexer);
                if (c == '\\' && !is_header_name && peek_char(lexer) != '\0' && peek_char(lexer) != '\n') next_char(lexer);
                if (c == '\0' || c == '\n') {
                    pp_lexer_error("Unterminated string literal", start);
                    if (c == '\n') unget_char(lexer);
                    break;
                }
            } while (c != '"');
            add_pp_token(lexer, is_header_name ? PP_HEADER_NAME : PP_STRING, content_string(start), start);
        } else if (c == '\'') {
            size_t start = lexer->pos - 1;
            do {
                c = next_char(lexer);
                if (c == '\\' && peek_char(lexer) != '\0' && peek_char(lexer) != '\n') next_char(lexer);
                if (c == '\0' || c == '\n') {
                    pp_lexer_error("Unterminated char literal", start);
                    if (c == '\n') unget_char(lexer);
                    break;
                }
            } while (c != '\'');
            add_pp_token(lexer, PP_CHAR, content_string(start), start);
        } else if (c == '/') {
            size_t start = lexer->pos - 1;
            c = next_char(lexer);
            if (c == '/') {
                do {
                    c = next_char(lexer);
                } while (c != '\n' && c != '\0');
                lexer->pending_space = true;
                unget_char(lexer);
            } else if (c == '*') {
                while (true) {
                    c = next_char(lexer);
                    if (c == '\0') {
                        pp_lexer_error("Unterminated comment", start);
                        break;
                    } else if (c == '*') {
                        c = next_char(lexer);
                        if (c == '/') break;
                        unget_char(lexer);
                    }
                }
                lexer->pending_space = true;
            } else if (c == '=') add_pp_token(lexer, PP_SYMBOL, SYMBOL_DIV_ASSIGN, start);
            else {
                unget_char(lexer);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_DIV, start);
            }
        } else if (c == '-') {
            c = next_char(lexer);
            if (c == '-') add_pp_token(lexer, PP_SYMBOL, SYMBOL_DECREMENT, lexer->pos - 2);
            else if (c == '=') add_pp_token(lexer, PP_SYMBOL, SYMBOL_SUB_ASSIGN, lexer->pos - 2);
            else if (c == '>') add_pp_token(lexer, PP_SYMBOL, SYMBOL_ARROW, lexer->pos - 2);
            else {
                unget_char(lexer);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_SUB, lexer->pos - 1);
            }
        } else if (c == '!') {
            if (peek_char(lexer) == '=') {
                c = next_char(lexer);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_NE, lexer->pos - 2);
            } else add_pp_token(lexer, PP_SYMBOL, SYMBOL_LOGICAL_NOT, lexer->pos - 1);
        } else if (c == '*') {
            if (peek_char(lexer) == '=') {
                c = next_char(lexer);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_MUL_ASSIGN, lexer->pos - 2);
            } else add_pp_token(lexer, PP_SYMBOL, SYMBOL_MUL, lexer->pos - 1);
        } else if (c == '.') {
            c = next_char(lexer);
            if (c == '.' && peek_char(lexer) == '.') {
                next_char(lexer);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_ELLIPSIS, lexer->pos - 3);
            } else {
                unget_char(lexer);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_DOT, lexer->pos - 1);
            }
        } else if (c == '&') {
            c = next_char(lexer);
            if (c == '&') add_pp_token(lexer, PP_SYMBOL, SYMBOL_LOGICAL_AND, lexer->pos - 2);
            else if (c == '=') add_pp_token(lexer, PP_SYMBOL, SYMBOL_AND_ASSIGN, lexer->pos - 2);
            else {
                unget_char(lexer);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_BITWISE_AND, lexer->pos - 1);
            }
        } else if (c == '%') {
            if (peek_char(lexer) == '=') {
                next_char(lexer);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_MOD_ASSIGN, lexer->pos - 2);
            } else add_pp_token(lexer, PP_SYMBOL, SYMBOL_MOD, lexer->pos - 1);
        } else if (c == '^') {
            if (peek_char(lexer) == '=') {
                next_char(lexer);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_XOR_ASSIGN, lexer->pos - 2);
            } else add_pp_token(lexer, PP_SYMBOL, SYMBOL_XOR, lexer->pos - 1);
        } else if (c == '=') {
            if (peek_char(lexer) == '=') {
                next_char(lexer);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_EQ, lexer->pos - 2);
            } else add_pp_token(lexer, PP_SYMBOL, SYMBOL_ASSIGN, lexer->pos - 1);
        } else if (c == '+') {
            c = next_char(lexer);
            if (c == '+') add_pp_token(lexer, PP_SYMBOL, SYMBOL_INCREMENT, lexer->pos - 2);
            else if (c == '=') add_pp_token(lexer, PP_SYMBOL, SYMBOL_ADD_ASSIGN, lexer->pos - 2);
            else {
                unget_char(lexer);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_ADD, lexer->pos - 1);
            }
        } else if (c == '<') {
            if (lexer->include_state == 2) {
                size_t start = lexer->pos - 1;
                while (true) {
                    c = next_char(lexer);
                    if (c == '\0' || c == '\n') {
                        pp_lexer_error("Unterminated #include <...>", start);
                        if (c == '\n') unget_char(lexer);
                        break;
                    } else if (c == '>') {
                        add_pp_token(lexer, PP_HEADER_NAME, content_string(start), start);
                        break;
                    }
                }
                lexer->include_state = 0;
                continue;
            }
            c = next_char(lexer);
            if (c == '=') add_pp_token(lexer, PP_SYMBOL, SYMBOL_LE, lexer->pos - 2);
            else if (c == '<') {
                if (peek_char(lexer) == '=') {
                    c = next_char(lexer);
                    add_pp_token(lexer, PP_SYMBOL, SYMBOL_L_SHIFT_ASSIGN, lexer->pos - 3);
                } else add_pp_token(lexer, PP_SYMBOL, SYMBOL_L_SHIFT, lexer->pos - 2);
            } else {
                unget_char(lexer);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_LT, lexer->pos - 1);
            }
        } else if (c == '>') {
            c = next_char(lexer);
            if (c == '=') add_pp_token(lexer, PP_SYMBOL, SYMBOL_GE, lexer->pos - 2);
            else if (c == '>') {
                if (peek_char(lexer) == '=') {
                    c = next_char(lexer);
                    add_pp_token(lexer, PP_SYMBOL, SYMBOL_R_SHIFT_ASSIGN, lexer->pos - 3);
                } else add_pp_token(lexer, PP_SYMBOL, SYMBOL_R_SHIFT, lexer->pos - 2);
            } else {
                unget_char(lexer);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_GT, lexer->pos - 1);
            }
        } else if (c == '|') {
            c = next_char(lexer);
            if (c == '|') add_pp_token(lexer, PP_SYMBOL, SYMBOL_LOGICAL_OR, lexer->pos - 2);
            else if (c == '=') add_pp_token(lexer, PP_SYMBOL, SYMBOL_OR_ASSIGN, lexer->pos - 2);
            else {
                unget_char(lexer);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_BITWISE_OR, lexer->pos - 1);
            }
        } else if (c == ',') add_pp_token(lexer, PP_SYMBOL, SYMBOL_COMMA, lexer->pos - 1);
        else if (c == ';') add_pp_token(lexer, PP_SYMBOL, SYMBOL_SEMICOLON, lexer->pos - 1);
        else if (c == ':') add_pp_token(lexer, PP_SYMBOL, SYMBOL_COLON, lexer->pos - 1);
        else if (c == '?') add_pp_token(lexer, PP_SYMBOL, SYMBOL_QUESTION, lexer->pos - 1);
        else if (c == '(') add_pp_token(lexer, PP_SYMBOL, SYMBOL_L_PARENTHESIS, lexer->pos - 1);
        else if (c == ')') add_pp_token(lexer, PP_SYMBOL, SYMBOL_R_PARENTHESIS, lexer->pos - 1);
        else if (c == '[') add_pp_token(lexer, PP_SYMBOL, SYMBOL_L_BRACKET, lexer->pos - 1);
        else if (c == ']') add_pp_token(lexer, PP_SYMBOL, SYMBOL_R_BRACKET, lexer->pos - 1);
        else if (c == '{') add_pp_token(lexer, PP_SYMBOL, SYMBOL_L_BRACE, lexer->pos - 1);
        else if (c == '}') add_pp_token(lexer, PP_SYMBOL, SYMBOL_R_BRACE, lexer->pos - 1);
        else if (c == '~') add_pp_token(lexer, PP_SYMBOL, SYMBOL_BITWISE_NOT, lexer->pos - 1);
        else if (c == '#') {
            if (peek_char(lexer) == '#') {
                next_char(lexer);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_DOUBLE_HASH, lexer->pos - 2);
            } else add_pp_token(lexer, PP_SYMBOL, SYMBOL_HASH, lexer->pos - 1);
        } else add_pp_token(lexer, PP_OTHER, create_string(&lexer->source_code[lexer->pos - 1], 1), lexer->pos - 1);
    }
}
