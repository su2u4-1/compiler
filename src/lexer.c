#include "lexer.h"

static string is_keyword(string str) {
    for (size_t i = 0; i < keyword_count; ++i) {
        if (str == keywordList[i]) {
            return keywordList[i];
        }
    }
    return NULL;
}

static Token* create_token(TokenType type, string value, size_t line, size_t column) {
    Token* token = create_struct(Token);
    token->line = line;
    token->column = column;
    if (type == TOKEN_IDENTIFIER) {
        string keyword = is_keyword(value);
        if (keyword != NULL) {
            token->type = TOKEN_KEYWORD;
            token->value = keyword;
            return token;
        }
    }
    token->type = type;
    token->value = value;
    return token;
}

#define is_digit(c) ((c) >= '0' && (c) <= '9')
#define is_alphabet(c) ((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z')
#define is_hex_digit(c) (is_digit(c) || ((c) >= 'a' && (c) <= 'f') || ((c) >= 'A' && (c) <= 'F'))
#define is_oct_digit(c) ((c) >= '0' && (c) <= '7')
#define lexer_error(message, line, column) fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", lexer->filename, line + 1, column + 1, message)

static char peek_char(Lexer* lexer) {
    if (lexer->pos >= lexer->length)
        return '\0';
    return lexer->source_code[lexer->pos];
}
static char next_char(Lexer* lexer) {
    if (lexer->pos >= lexer->length)
        return '\0';
    char c = lexer->source_code[lexer->pos++];
    lexer->column++;
    if (c == '\n') {
        lexer->prev_line_column = lexer->column - 1;
        lexer->line++;
        lexer->column = 1;
    }
    return c;
}
static void unget_char(Lexer* lexer) {
    if (lexer->pos == 0)
        return;
    lexer->pos--;
    lexer->column--;
    if (lexer->source_code[lexer->pos] == '\n') {
        lexer->line--;
        lexer->column = lexer->prev_line_column + 1;
    }
}

static Token* number_token(Lexer* lexer) {
    size_t start = lexer->pos - 1;
    size_t column_start = lexer->column - 1;
    char p = '\0';
    char c = next_char(lexer);
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
    size_t size = lexer->pos - start;
    string C = create_string(&lexer->source_code[start], size);
    // ^ pp-number

    bool is_float = false;
    bool is_hex = false;
    bool error = false;
    size_t i = 0;

    if (is_digit(C[0]) && C[0] != '0') {
        i = 1;
        while (is_digit(C[i])) i++;
        if (C[i] == '.') {
            is_float = true;
            i++;
            while (is_digit(C[i])) i++;
        }
    } else if (C[0] == '0') {
        if (C[1] == 'x' || C[1] == 'X') {
            is_hex = true;
            i = 2;
            size_t t0 = 0;
            while (is_hex_digit(C[i])) {
                i++;
                t0++;
            }
            if (C[i] == '.') {
                is_float = true;
                i++;
                size_t t1 = 0;
                while (is_hex_digit(C[i])) {
                    i++;
                    t1++;
                }
                if (t0 == 0 && t1 == 0) {
                    error = true;
                    lexer_error("Invalid number format, hex number must have at least one digit", lexer->line, column_start);
                }
            } else if (t0 == 0) {
                error = true;
                lexer_error("Invalid number format, hex number must have at least one digit", lexer->line, column_start);
            }
        } else if (C[1] == 'b' || C[1] == 'B') {
            i = 2;
            size_t t0 = 0;
            while (C[i] == '0' || C[i] == '1') {
                i++;
                t0++;
            }
            if ((is_digit(C[i]) && C[i] != '0' && C[i] != '1') || C[i] == '.' || C[i] == 'e' || C[i] == 'E' || C[i] == 'p' || C[i] == 'P') {
                error = true;
                lexer_error("Invalid number format, binary number can only contain 0 and 1", lexer->line, column_start);
            }
            if (t0 == 0) {
                error = true;
                lexer_error("Invalid number format, binary number must have at least one digit", lexer->line, column_start);
            }
        } else if (C[1] == '.') {
            is_float = true;
            i = 2;
            while (is_digit(C[i])) i++;
        } else {
            i = 1;
            while (is_digit(C[i])) i++;
            if (C[i] == '.') {
                is_float = true;
                i++;
                while (is_digit(C[i])) i++;
            } else if (C[i] == 'e' || C[i] == 'E') {
                is_float = true;
            } else {
                for (size_t k = 0; k < i; k++) {
                    if (C[k] == '8' || C[k] == '9') {
                        error = true;
                        lexer_error("Invalid number format, octal number can only contain digits 0-7", lexer->line, column_start);
                        break;
                    }
                }
            }
        }
    } else if (C[0] == '.') {
        is_float = true;
        i = 1;
        size_t t1 = 0;
        while (is_digit(C[i])) {
            i++;
            t1++;
        }
        if (t1 == 0) {
            error = true;
            lexer_error("Invalid number format, float number must have at least one digit after decimal point", lexer->line, column_start);
        }
    }

    if (is_float && is_hex && C[i] != 'p' && C[i] != 'P') {
        error = true;
        lexer_error("Invalid number format, hex float number must have 'p' or 'P' exponent", lexer->line, column_start);
    }

    if (C[i] == 'p' || C[i] == 'P' || C[i] == 'e' || C[i] == 'E') {
        char ec = C[i];
        if (is_hex && ec != 'p' && ec != 'P') {
            error = true;
            lexer_error("Invalid number format, hex float number must have 'p' or 'P' exponent", lexer->line, column_start);
        }
        if (!is_hex && (ec == 'p' || ec == 'P')) {
            error = true;
            lexer_error("Invalid number format, decimal float number must have 'e' or 'E' exponent", lexer->line, column_start);
        }
        is_float = true;
        i++;
        if (C[i] == '+' || C[i] == '-') i++;
        size_t t1 = 0;
        while (is_digit(C[i])) {
            i++;
            t1++;
        }
        if (t1 == 0) {
            error = true;
            lexer_error("Invalid number format, exponent must have at least one digit", lexer->line, column_start);
        }
    }

    if (is_float) {
        if (C[i] == 'f' || C[i] == 'F') i++;
        else if (C[i] == 'l' || C[i] == 'L') i++;
    } else {
        if (C[i] == 'u' || C[i] == 'U') {
            i++;
            if (C[i] == 'l' || C[i] == 'L') {
                i++;
                if (C[i - 1] == C[i]) i++;
            }
        } else if (C[i] == 'l' || C[i] == 'L') {
            i++;
            if (C[i - 1] == C[i]) i++;
            if (C[i] == 'u' || C[i] == 'U') i++;
        }
    }
    if (C[i] != '\0')
        error = true;

    if (error) {
        lexer_error("Invalid number format", lexer->line, column_start);
        return create_token(TOKEN_SYNTAX_ERROR_NUMBER, C, lexer->line, column_start);
    } else if (is_float)
        return create_token(TOKEN_FLOAT, C, lexer->line, column_start);
    else
        return create_token(TOKEN_INT, C, lexer->line, column_start);
}

static bool escape_sequence(Lexer* lexer) {
    char c = next_char(lexer);
    if (c == 'a' || c == 'b' || c == 'f' || c == 'n' || c == 'r' || c == 't' || c == 'v' || c == '\\' || c == '\'' || c == '"' || c == '?') {  // simple escape sequence
        return true;
    } else if (is_oct_digit(c)) {  // oct escape sequence
        if (is_oct_digit(peek_char(lexer))) {
            next_char(lexer);
            if (is_oct_digit(peek_char(lexer))) next_char(lexer);
        }
        // TODO: the value must be within the range of unsigned char
        return true;
    } else if (c == 'x') {  // hex escape sequence
        if (!is_hex_digit(peek_char(lexer))) return false;
        while (is_hex_digit(peek_char(lexer))) next_char(lexer);
        // TODO: the value must be within the range of unsigned char
        return true;
    } else if (c == 'u' || c == 'U') {  // universal character name
        int length = (c == 'u') ? 4 : 8;
        for (int i = 0; i < length; ++i) {
            if (!is_hex_digit(peek_char(lexer))) return false;
            next_char(lexer);
        }
        // TODO: check UCN value: ( > 00A0 || 0024, 0040, 0060 ) && not in D800..DFFF && <= 10FFFF
        return true;
    } else
        return false;
}

static Token* get_next_token(Lexer* lexer) {
    if (lexer->pos >= lexer->length)
        return create_token(TOKEN_EOF, NULL, lexer->line, lexer->column);
    while (true) {
        char c = next_char(lexer);
        if (c == '\0') {
            return create_token(TOKEN_EOF, NULL, lexer->line, lexer->column);
        } else if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
            continue;
        } else if (is_alphabet(c) || c == '_') {
            size_t start = lexer->pos - 1;
            do {
                c = next_char(lexer);
            } while (is_alphabet(c) || is_digit(c) || c == '_');
            unget_char(lexer);
            string content = create_string(&lexer->source_code[start], lexer->pos - start);
            return create_token(TOKEN_IDENTIFIER, content, lexer->line, lexer->column - 1);
        } else if (is_digit(c) || (is_digit(peek_char(lexer)) && (c == '.'))) {
            return number_token(lexer);
        } else if (c == '"') {
            size_t start = lexer->pos - 1;
            size_t column_start = lexer->column - 1;
            do {
                c = next_char(lexer);
                if (c == '\\') next_char(lexer);
                if (c == '\0' || c == '\n') {
                    lexer_error("Unterminated string literal", lexer->line, lexer->column);
                    return create_token(TOKEN_STRING, create_string(&lexer->source_code[start], lexer->pos - start), lexer->line, column_start);
                }
            } while (c != '"');
            // TODO: Handle escape sequences in string literals
            return create_token(TOKEN_STRING, create_string(&lexer->source_code[start], lexer->pos - start), lexer->line, column_start);
        } else if (c == '\'') {
            size_t start = lexer->pos - 1;
            size_t column_start = lexer->column - 1;
            c = next_char(lexer);
            if (c == '\0' || c == '\n' || c == '\'') {
                lexer_error("Invalid character literal", lexer->line, lexer->column);
                return create_token(TOKEN_CHAR, create_string(&lexer->source_code[start], lexer->pos - start), lexer->line, column_start);
            }
            if (c == '\\' && !escape_sequence(lexer))
                lexer_error("Invalid escape sequence in character literal", lexer->line, lexer->column);
            c = next_char(lexer);
            if (c != '\'')
                lexer_error("Invalid character literal", lexer->line, lexer->column);
            return create_token(TOKEN_CHAR, create_string(&lexer->source_code[start], lexer->pos - start), lexer->line, column_start);
        }  // TODO
    }
    lexer_error("Unrecognized token", lexer->line, lexer->column);
    return NULL;
}

static Token* get(Lexer* lexer) {
    Token* token;
    do {
        token = get_next_token(lexer);
        if (token == NULL) {
            fprintf(stderr, "[lexer Error] at <get>: Failed to get next token\n");
            return NULL;
        }
    } while (lexer->skip_comment && token->type == TOKEN_COMMENT);
    return token;
}

Lexer* create_lexer(string filename) {
    Lexer* lexer = create_struct(Lexer);
    lexer->source_code = get_source(filename);
    lexer->length = strlen(lexer->source_code);
    lexer->pos = 0;
    lexer->prev_line_column = 0;
    lexer->line = 1;
    lexer->column = 1;
    lexer->current_token = NULL;
    lexer->next_token = NULL;
    lexer->filename = filename;
    lexer->skip_comment = true;
    return lexer;
}

Token* next(Lexer* lexer) {
    lexer->current_token = lexer->next_token ? lexer->next_token : get(lexer);
    lexer->next_token = get(lexer);
    return lexer->current_token;
}

Token* peek(Lexer* lexer) {
    if (lexer->next_token == NULL)
        lexer->next_token = get(lexer);
    return lexer->next_token;
}
