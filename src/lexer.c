#include "lexer.h"

#include "preprocessor.h"

static string is_keyword(string str) {
    for (size_t i = 0; i < keyword_count; ++i)
        if (str == keywordList[i])
            return keywordList[i];
    return NULL;
}

static Token* create_token(TokenType type, ppToken* t) {
    Token* token = create_struct(Token);
    token->line = t->line;
    token->column = t->column;
    if (type == TOKEN_IDENTIFIER) {
        string keyword = is_keyword(t->value);
        if (keyword != NULL) {
            token->type = TOKEN_KEYWORD;
            token->value = keyword;
            return token;
        }
    }
    token->type = type;
    token->value = t->value;
    token->filename = t->filename;
    token->space_before = t->space_before;
    token->at_line_start = t->at_line_start;
    return token;
}

#define is_digit(c) ((c) >= '0' && (c) <= '9')
#define is_hex_digit(c) (is_digit(c) || ((c) >= 'a' && (c) <= 'f') || ((c) >= 'A' && (c) <= 'F'))
#define is_oct_digit(c) ((c) >= '0' && (c) <= '7')
#define lexer_error(message, line, column) fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", filename, line, column, message)

static Token* number_token(ppToken* t) {
    bool is_float = false;
    bool is_hex = false;
    bool error = false;
    size_t i = 0;
    string C = t->value;
    string filename = t->filename;

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
                    lexer_error("Invalid number format, hex number must have at least one digit", t->line, t->column);
                }
            } else if (t0 == 0) {
                error = true;
                lexer_error("Invalid number format, hex number must have at least one digit", t->line, t->column);
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
                lexer_error("Invalid number format, binary number can only contain 0 and 1", t->line, t->column);
            }
            if (t0 == 0) {
                error = true;
                lexer_error("Invalid number format, binary number must have at least one digit", t->line, t->column);
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
                        lexer_error("Invalid number format, octal number can only contain digits 0-7", t->line, t->column);
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
            lexer_error("Invalid number format, float number must have at least one digit after decimal point", t->line, t->column);
        }
    }

    if (is_float && is_hex && C[i] != 'p' && C[i] != 'P') {
        error = true;
        lexer_error("Invalid number format, hex float number must have 'p' or 'P' exponent", t->line, t->column);
    }

    if (C[i] == 'p' || C[i] == 'P' || C[i] == 'e' || C[i] == 'E') {
        char ec = C[i];
        if (is_hex && ec != 'p' && ec != 'P') {
            error = true;
            lexer_error("Invalid number format, hex float number must have 'p' or 'P' exponent", t->line, t->column);
        }
        if (!is_hex && (ec == 'p' || ec == 'P')) {
            error = true;
            lexer_error("Invalid number format, decimal float number must have 'e' or 'E' exponent", t->line, t->column);
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
            lexer_error("Invalid number format, exponent must have at least one digit", t->line, t->column);
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
        lexer_error("Invalid number format", t->line, t->column);
        return create_token(TOKEN_SYNTAX_ERROR_NUMBER, t);
    } else if (is_float)
        return create_token(TOKEN_FLOAT, t);
    else
        return create_token(TOKEN_INT, t);
}

static size_t escape_sequence(char* str, size_t start) {
    size_t index = start;
    char c = str[index++];
    if (c == 'a' || c == 'b' || c == 'f' || c == 'n' || c == 'r' || c == 't' || c == 'v' || c == '\\' || c == '\'' || c == '"' || c == '?') {
        // simple escape sequence
        return index;
    } else if (is_oct_digit(c)) {
        // oct escape sequence
        if (is_oct_digit(str[index])) {
            ++index;
            if (is_oct_digit(str[index]))
                ++index;
        }
        // TODO: the value must be within the range of unsigned char
        return index;
    } else if (c == 'x') {
        // hex escape sequence
        if (!is_hex_digit(str[index++]))
            return 0;
        while (is_hex_digit(str[index]))
            ++index;
        // TODO: the value must be within the range of unsigned char
        return index;
    } else if (c == 'u' || c == 'U') {
        // universal character name
        int length = (c == 'u') ? 4 : 8;
        for (int i = 0; i < length; ++i) {
            if (!is_hex_digit(str[index++]))
                return 0;
        }
        // TODO: check UCN value: ( > 00A0 || 0024, 0040, 0060 ) && not in D800..DFFF && <= 10FFFF
        return index;
    } else
        return 0;
}

list(Token*) pp_to_tokens(list(ppToken*) pp_tokens) {
    list(Token*) tokens = create_list(Token*);
    foreach (ppToken*, t, pp_tokens) {
        string filename = t->filename;
        switch (t->type) {
            case PP_IDENTIFIER:
                append(tokens, create_token(TOKEN_IDENTIFIER, t));
                break;
            case PP_NUMBER:
                append(tokens, number_token(t));
                break;
            case PP_CHAR: {
                if (strlen(t->value) < 3) {
                    lexer_error("Invalid character literal", t->line, t->column);
                    append(tokens, create_token(TOKEN_SYNTAX_ERROR_CHAR, t));
                    break;
                }
                if (t->value[0] != '\'') {
                    lexer_error("Invalid character literal", t->line, t->column);
                    append(tokens, create_token(TOKEN_SYNTAX_ERROR_CHAR, t));
                    break;
                }
                size_t i = 2;
                if (t->value[1] == '\\') {
                    i = escape_sequence(t->value, 2);
                    if (i == 0) {
                        lexer_error("Invalid escape sequence in character literal", t->line, t->column);
                        append(tokens, create_token(TOKEN_SYNTAX_ERROR_CHAR, t));
                        break;
                    }
                }
                if (t->value[i] != '\'' || t->value[i + 1] != '\0') {
                    lexer_error("Invalid character literal", t->line, t->column);
                    append(tokens, create_token(TOKEN_SYNTAX_ERROR_CHAR, t));
                    break;
                }
                append(tokens, create_token(TOKEN_CHAR, t));
                break;
            }
            case PP_STRING: {
                size_t len = strlen(t->value);
                if (len < 2 || t->value[0] != '"' || t->value[len - 1] != '"') {
                    lexer_error("Invalid string literal: missing opening or closing quote", t->line, t->column);
                    append(tokens, create_token(TOKEN_SYNTAX_ERROR_STRING, t));
                    break;
                }
                for (size_t i = 1; i < len - 1; ++i) {
                    if (t->value[i] == '\\') {
                        size_t next_index = escape_sequence(t->value, i + 1);
                        if (next_index == 0) {
                            lexer_error("Invalid escape sequence in string literal", t->line, t->column + i);
                            append(tokens, create_token(TOKEN_SYNTAX_ERROR_STRING, t));
                            break;
                        }
                        if (next_index >= len) {
                            lexer_error("Invalid string literal: unterminated escape sequence", t->line, t->column + i);
                            append(tokens, create_token(TOKEN_SYNTAX_ERROR_STRING, t));
                            break;
                        }
                        i = next_index - 1;
                    } else if (t->value[i] == '\n') {
                        lexer_error("Invalid string literal: contains newline", t->line, t->column + i);
                        append(tokens, create_token(TOKEN_SYNTAX_ERROR_STRING, t));
                        break;
                    }
                }
                append(tokens, create_token(TOKEN_STRING, t));
                break;
            }
            case PP_SYMBOL:
                append(tokens, create_token(TOKEN_SYMBOL, t));
                break;
            case PP_EOF:
                return tokens;
            case PP_NEWLINE:
            case PP_OTHER:
            case PP_PLACE_MARKER:
            case PP_HEADER_NAME:
            default:
                break;
        }
    }
    return tokens;
}
