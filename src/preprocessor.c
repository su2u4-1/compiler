#include "preprocessor.h"

#define line(lexer, pos) ((pos >= lexer->length) ? lexer->line_map[lexer->length] : lexer->line_map[pos])
#define column(lexer, pos) ((pos >= lexer->length) ? lexer->column_map[lexer->length] : lexer->column_map[pos])
#define peek_char(lexer) ((lexer->pos >= lexer->length) ? '\0' : lexer->source_code[lexer->pos])
#define next_char(lexer) ((lexer->pos >= lexer->length) ? '\0' : lexer->source_code[lexer->pos++])
#define unget_char(lexer) \
    if (lexer->pos > 0) lexer->pos -= (lexer->pos >= lexer->length ? 0 : 1)
#define pp_token(type, value, pos) append(lexer->pp_tokens, create_pp_token(type, value, lexer, pos))
#define is_digit(c) ((c) >= '0' && (c) <= '9')
#define is_alphabet(c) ((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z')
#define is_hex_digit(c) (is_digit(c) || ((c) >= 'a' && (c) <= 'f') || ((c) >= 'A' && (c) <= 'F'))
#define is_oct_digit(c) ((c) >= '0' && (c) <= '7')
#define preprocessor_error(message, pos) fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", lexer->filename, line(lexer, pos), column(lexer, pos), message)
#define content_string(start) create_string(&lexer->source_code[start], lexer->pos - start)

static ppToken* create_pp_token(ppTokenType type, string value, ppLexer* lexer, size_t pos) {
    ppToken* token = create_struct(ppToken);
    token->line = line(lexer, pos);
    token->column = column(lexer, pos);
    token->type = type;
    token->value = value;
    return token;
}

static void normalize(ppLexer* lexer, string source_code) {
    const string src = source_code;
    size_t source_len = strlen(source_code);
    string buffer = (string)alloc_memory(source_len + 1, false);
    lexer->line_map = alloc_memory(sizeof(size_t) * (source_len + 1), false);
    lexer->column_map = alloc_memory(sizeof(size_t) * (source_len + 1), false);
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
    buffer[size] = '\0';
    lexer->line_map[size] = line;
    lexer->column_map[size] = column;
    lexer->source_code = buffer;
    lexer->length = size;
}

ppLexer* create_pp_lexer(string filename, string source_code) {
    ppLexer* lexer = create_struct(ppLexer);
    if (source_code == NULL) {
        fprintf(stderr, "[preprocessor Error] at <create_pp_lexer>: Failed to create ppLexer, source_code is NULL\n");
        return NULL;
    }
    lexer->source_code = NULL;
    lexer->length = 0;
    lexer->pos = 0;
    lexer->prev_line_column = 0;
    lexer->line = 1;
    lexer->column = 0;
    lexer->current_token = NULL;
    lexer->next_token = NULL;
    lexer->filename = filename;
    lexer->pp_tokens = create_list(ppToken*);
    lexer->line_map = NULL;
    lexer->column_map = NULL;
    normalize(lexer, source_code);
    return lexer;
}

void pp_lexer(ppLexer* lexer) {
    while (true) {
        char c = next_char(lexer);
        if (c == '\0') {
            pp_token(PP_EOF, NULL, lexer->length);
            return;
        } else if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f') {
            if (c == '\n')
                pp_token(PP_NEWLINE, NULL, lexer->pos - 1);
        } else if (is_alphabet(c) || c == '_') {
            size_t start = lexer->pos - 1;
            do {
                c = next_char(lexer);
            } while (is_alphabet(c) || is_digit(c) || c == '_');
            unget_char(lexer);
            pp_token(PP_IDENTIFIER, content_string(start), start);
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
            pp_token(PP_NUMBER, content_string(start), start);
        } else if (c == '"') {
            size_t start = lexer->pos - 1;
            do {
                c = next_char(lexer);
                if (c == '\\') next_char(lexer);
                if (c == '\0' || c == '\n') {
                    preprocessor_error("Unterminated string literal", start);
                    if (c == '\n') unget_char(lexer);
                    break;
                }
            } while (c != '"');
            pp_token(PP_STRING, content_string(start), start);
        } else if (c == '\'') {
            size_t start = lexer->pos - 1;
            do {
                c = next_char(lexer);
                if (c == '\\') next_char(lexer);
                if (c == '\0' || c == '\n') {
                    preprocessor_error("Unterminated char literal", start);
                    if (c == '\n') unget_char(lexer);
                    break;
                }
            } while (c != '\'');
            pp_token(PP_CHAR, content_string(start), start);
        } else if (c == '/') {
            size_t start = lexer->pos - 1;
            c = next_char(lexer);
            if (c == '/') {
                do {
                    c = next_char(lexer);
                } while (c != '\n' && c != '\0');
                unget_char(lexer);
            } else if (c == '*') {
                while (true) {
                    c = next_char(lexer);
                    if (c == '\0') {
                        preprocessor_error("Unterminated comment", start);
                        break;
                    } else if (c == '*') {
                        c = next_char(lexer);
                        if (c == '/') break;
                    }
                }
            } else if (c == '=')
                pp_token(PP_SYMBOL, SYMBOL_DIV_ASSIGN, start);
            else {
                unget_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_DIV, start);
            }
        } else if (c == '-') {
            c = next_char(lexer);
            if (c == '-')
                pp_token(PP_SYMBOL, SYMBOL_DECREMENT, lexer->pos - 2);
            else if (c == '=')
                pp_token(PP_SYMBOL, SYMBOL_SUB_ASSIGN, lexer->pos - 2);
            else if (c == '>')
                pp_token(PP_SYMBOL, SYMBOL_ARROW, lexer->pos - 2);
            else {
                unget_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_SUB, lexer->pos - 1);
            }
        } else if (c == '!') {
            if (peek_char(lexer) == '=') {
                c = next_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_NE, lexer->pos - 2);
            } else
                pp_token(PP_SYMBOL, SYMBOL_LOGICAL_NOT, lexer->pos - 1);
        } else if (c == '*') {
            if (peek_char(lexer) == '=') {
                c = next_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_MUL_ASSIGN, lexer->pos - 2);
            } else
                pp_token(PP_SYMBOL, SYMBOL_MUL, lexer->pos - 1);
        } else if (c == '.') {
            c = next_char(lexer);
            if (c == '.' && peek_char(lexer) == '.') {
                next_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_ELLIPSIS, lexer->pos - 3);
            } else {
                unget_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_DOT, lexer->pos - 1);
            }
        } else if (c == '&') {
            c = next_char(lexer);
            if (c == '&')
                pp_token(PP_SYMBOL, SYMBOL_LOGICAL_AND, lexer->pos - 2);
            else if (c == '=')
                pp_token(PP_SYMBOL, SYMBOL_AND_ASSIGN, lexer->pos - 2);
            else {
                unget_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_BITWISE_AND, lexer->pos - 1);
            }
        } else if (c == '%') {
            if (peek_char(lexer) == '=') {
                next_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_MOD_ASSIGN, lexer->pos - 2);
            } else
                pp_token(PP_SYMBOL, SYMBOL_MOD, lexer->pos - 1);
        } else if (c == '^') {
            if (peek_char(lexer) == '=') {
                next_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_XOR_ASSIGN, lexer->pos - 2);
            } else
                pp_token(PP_SYMBOL, SYMBOL_XOR, lexer->pos - 1);
        } else if (c == '=') {
            if (peek_char(lexer) == '=') {
                next_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_EQ, lexer->pos - 2);
            } else
                pp_token(PP_SYMBOL, SYMBOL_ASSIGN, lexer->pos - 1);
        } else if (c == '+') {
            c = next_char(lexer);
            if (c == '+')
                pp_token(PP_SYMBOL, SYMBOL_INCREMENT, lexer->pos - 2);
            else if (c == '=')
                pp_token(PP_SYMBOL, SYMBOL_ADD_ASSIGN, lexer->pos - 2);
            else {
                unget_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_ADD, lexer->pos - 1);
            }
        } else if (c == '<') {
            c = next_char(lexer);
            if (c == '=')
                pp_token(PP_SYMBOL, SYMBOL_LE, lexer->pos - 2);
            else if (c == '<') {
                if (peek_char(lexer) == '=') {
                    c = next_char(lexer);
                    pp_token(PP_SYMBOL, SYMBOL_L_SHIFT_ASSIGN, lexer->pos - 3);
                } else
                    pp_token(PP_SYMBOL, SYMBOL_L_SHIFT, lexer->pos - 2);
            } else {
                unget_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_LT, lexer->pos - 1);
            }
        } else if (c == '>') {
            c = next_char(lexer);
            if (c == '=')
                pp_token(PP_SYMBOL, SYMBOL_GE, lexer->pos - 2);
            else if (c == '>') {
                if (peek_char(lexer) == '=') {
                    c = next_char(lexer);
                    pp_token(PP_SYMBOL, SYMBOL_R_SHIFT_ASSIGN, lexer->pos - 3);
                } else
                    pp_token(PP_SYMBOL, SYMBOL_R_SHIFT, lexer->pos - 2);
            } else {
                unget_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_GT, lexer->pos - 1);
            }
        } else if (c == '|') {
            c = next_char(lexer);
            if (c == '|')
                pp_token(PP_SYMBOL, SYMBOL_LOGICAL_OR, lexer->pos - 2);
            else if (c == '=')
                pp_token(PP_SYMBOL, SYMBOL_OR_ASSIGN, lexer->pos - 2);
            else {
                unget_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_BITWISE_OR, lexer->pos - 1);
            }
        } else if (c == ',')
            pp_token(PP_SYMBOL, SYMBOL_COMMA, lexer->pos - 1);
        else if (c == ';')
            pp_token(PP_SYMBOL, SYMBOL_SEMICOLON, lexer->pos - 1);
        else if (c == ':')
            pp_token(PP_SYMBOL, SYMBOL_COLON, lexer->pos - 1);
        else if (c == '?')
            pp_token(PP_SYMBOL, SYMBOL_QUESTION, lexer->pos - 1);
        else if (c == '(')
            pp_token(PP_SYMBOL, SYMBOL_L_PARENTHESIS, lexer->pos - 1);
        else if (c == ')')
            pp_token(PP_SYMBOL, SYMBOL_R_PARENTHESIS, lexer->pos - 1);
        else if (c == '[')
            pp_token(PP_SYMBOL, SYMBOL_L_BRACKET, lexer->pos - 1);
        else if (c == ']')
            pp_token(PP_SYMBOL, SYMBOL_R_BRACKET, lexer->pos - 1);
        else if (c == '{')
            pp_token(PP_SYMBOL, SYMBOL_L_BRACE, lexer->pos - 1);
        else if (c == '}')
            pp_token(PP_SYMBOL, SYMBOL_R_BRACE, lexer->pos - 1);
        else if (c == '~')
            pp_token(PP_SYMBOL, SYMBOL_BITWISE_NOT, lexer->pos - 1);
        else if (c == '#') {
            if (peek_char(lexer) == '#') {
                next_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_DOUBLE_HASH, lexer->pos - 2);
            } else
                pp_token(PP_SYMBOL, SYMBOL_HASH, lexer->pos - 1);
        } else
            pp_token(PP_OTHER, create_string(&lexer->source_code[lexer->pos - 1], 1), lexer->pos - 1);
    }
}

string preprocess(string filename, string source_code) {
    ppLexer* lexer = create_pp_lexer(filename, source_code);
    pp_lexer(lexer);
    return NULL;  // placeholder
}
