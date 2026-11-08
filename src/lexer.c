#include "lexer.h"

#include <math.h>

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
    token->type = type;
    token->value = t->value;
    memset(&token->literal, 0, sizeof(token->literal));
    token->filename = t->filename;
    token->space_before = t->space_before;
    token->at_line_start = t->at_line_start;
    if (type == TOKEN_IDENTIFIER) {
        string keyword = is_keyword(t->value);
        if (keyword != NULL) {
            token->type = TOKEN_KEYWORD;
            token->value = keyword;
        }
    }
    return token;
}

#define is_digit(c) ((c) >= '0' && (c) <= '9')
#define lexer_error(message, t, line_, column_) fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", t->filename, t->line + line_, t->column + column_, message)
#define lexer_warn(message, t, line_, column_) fprintf(stderr, "[Syntax Warning] at %s:%zu:%zu: %s\n", t->filename, t->line + line_, t->column + column_, message)

static Token* int_token(ppToken* t) {
    string s = t->value;
    IntLiteral literal = parse_int_digits(s);
    size_t i = literal.digits_end;

    bool is_unsigned = false;
    size_t long_count = 0;
    for (; s[i] != '\0'; ++i) {
        if (s[i] == 'u' || s[i] == 'U')
            is_unsigned = true;
        else
            long_count++;
    }

    if (literal.overflow)
        lexer_warn("Integer constant is too large", t, 0, 0);
    else if (literal.base == 10 && !is_unsigned && literal.value > (uintmax_t)INTMAX_MAX)
        lexer_warn("Integer constant is so large that it is unsigned", t, 0, 0);

    Token* token = create_token(TOKEN_INT, t);
    token->literal.integer.data = literal.value;
    if (is_unsigned)
        token->literal.integer.suffix = long_count == 0 ? SUFFIX_U : (long_count == 1 ? SUFFIX_UL : SUFFIX_ULL);
    else
        token->literal.integer.suffix = long_count == 0 ? SUFFIX_NONE : (long_count == 1 ? SUFFIX_L : SUFFIX_LL);
    token->literal.integer.is_decimal = literal.base == 10;
    return token;
}

static bool has_nonzero_digit(string s) {
    bool is_hex = s[0] == '0' && (s[1] == 'x' || s[1] == 'X');
    for (size_t i = is_hex ? 2 : 0; s[i] != '\0'; ++i) {
        if (is_hex ? (s[i] == 'p' || s[i] == 'P') : (s[i] == 'e' || s[i] == 'E'))
            break;
        if (is_hex ? hex_digit_value(s[i]) > 0 : (s[i] >= '1' && s[i] <= '9'))
            return true;
    }
    return false;
}

static Token* float_token(ppToken* t) {
    string s = t->value;
    char last = s[strlen(s) - 1];
    NumberSuffix suffix = SUFFIX_NONE;
    long double value;
    if (last == 'f' || last == 'F') {
        suffix = SUFFIX_F;
        value = (long double)strtof(s, NULL);
    } else if (last == 'l' || last == 'L') {
        suffix = SUFFIX_LD;
        value = strtold(s, NULL);
    } else {
        value = (long double)strtod(s, NULL);
    }

    if (isinf(value))
        lexer_warn("Floating constant exceeds the range of its type", t, 0, 0);
    else if (value <= 0 && has_nonzero_digit(s))
        lexer_warn("Floating constant truncated to zero", t, 0, 0);

    Token* token = create_token(TOKEN_FLOAT, t);
    token->literal.floating.data = value;
    token->literal.floating.suffix = suffix;
    return token;
}

static Token* number_token(ppToken* t) {
    bool is_float = false;
    bool is_hex = false;
    bool error = false;
    size_t i = 0;
    string C = t->value;

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
            while (hex_digit_value(C[i]) >= 0) {
                i++;
                t0++;
            }
            if (C[i] == '.') {
                is_float = true;
                i++;
                size_t t1 = 0;
                while (hex_digit_value(C[i]) >= 0) {
                    i++;
                    t1++;
                }
                if (t0 == 0 && t1 == 0) {
                    if (!error)
                        lexer_error("Invalid number format, hex number must have at least one digit", t, 0, 0);
                    error = true;
                }
            } else if (t0 == 0) {
                if (!error)
                    lexer_error("Invalid number format, hex number must have at least one digit", t, 0, 0);
                error = true;
            }
        } else if (C[1] == 'b' || C[1] == 'B') {
            i = 2;
            size_t t0 = 0;
            while (C[i] == '0' || C[i] == '1') {
                i++;
                t0++;
            }
            if ((is_digit(C[i]) && C[i] != '0' && C[i] != '1') || C[i] == '.' || C[i] == 'e' || C[i] == 'E' || C[i] == 'p' || C[i] == 'P') {
                if (!error)
                    lexer_error("Invalid number format, binary number can only contain 0 and 1", t, 0, 0);
                error = true;
            }
            if (t0 == 0) {
                if (!error)
                    lexer_error("Invalid number format, binary number must have at least one digit", t, 0, 0);
                error = true;
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
                        if (!error)
                            lexer_error("Invalid number format, octal number can only contain digits 0-7", t, 0, 0);
                        error = true;
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
            if (!error)
                lexer_error("Invalid number format, float number must have at least one digit after decimal point", t, 0, 0);
            error = true;
        }
    }

    if (is_float && is_hex && C[i] != 'p' && C[i] != 'P') {
        if (!error)
            lexer_error("Invalid number format, hex float number must have 'p' or 'P' exponent", t, 0, 0);
        error = true;
    }

    if (C[i] == 'p' || C[i] == 'P' || C[i] == 'e' || C[i] == 'E') {
        char ec = C[i];
        if (is_hex && ec != 'p' && ec != 'P') {
            if (!error)
                lexer_error("Invalid number format, hex float number must have 'p' or 'P' exponent", t, 0, 0);
            error = true;
        }
        if (!is_hex && (ec == 'p' || ec == 'P')) {
            if (!error)
                lexer_error("Invalid number format, decimal float number must have 'e' or 'E' exponent", t, 0, 0);
            error = true;
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
            if (!error)
                lexer_error("Invalid number format, exponent must have at least one digit", t, 0, 0);
            error = true;
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
    if (C[i] != '\0') {
        if (!error)
            lexer_error("Invalid number format", t, 0, 0);
        error = true;
    }

    if (error)
        return create_token(TOKEN_SYNTAX_ERROR_NUMBER, t);
    else if (is_float)
        return float_token(t);
    else
        return int_token(t);
}

static bool report_escape(ppToken* t, EscapeResult result, size_t offset) {
    if (result == ESC_OK)
        return true;
    if (result == ESC_NO_HEX_DIGITS || result == ESC_UNSUPPORTED) {
        lexer_error(escape_message(result), t, 0, offset);
        return false;
    }
    lexer_warn(escape_message(result), t, 0, offset);
    return true;
}

static Token* char_token(ppToken* t) {
    size_t end = strlen(t->value) - 1;
    assert(end >= 1 && t->value[0] == '\'' && t->value[end] == '\'');
    size_t i = 1;
    size_t count = 0;
    unsigned int acc = 0;
    while (i < end) {
        size_t start = i;
        unsigned int c;
        if (!report_escape(t, decode_literal_char(t->value, &i, &c), start))
            return create_token(TOKEN_SYNTAX_ERROR_CHAR, t);
        acc = (acc << 8) | c;  // acc * 256 + c
        count++;
    }
    if (count == 0) {
        lexer_error("Empty character constant", t, 0, 0);
        return create_token(TOKEN_SYNTAX_ERROR_CHAR, t);
    }
    if (count > 1) {
        lexer_warn("Multi-character character constant", t, 0, 0);
        if (count > 4)
            lexer_warn("character constant too long", t, 0, 0);
    }
    Token* token = create_token(TOKEN_CHAR, t);
    token->literal.character = count == 1 ? (int)(char)acc : (int)acc;
    return token;
}

static Token* string_token(ppToken* t) {
    size_t end = strlen(t->value) - 1;
    assert(end >= 1 && t->value[0] == '"' && t->value[end] == '"');
    char* data = (char*)alloc_memory(end - 1, false);
    size_t length = 0;
    size_t i = 1;
    while (i < end) {
        if (t->value[i] == '\\' && i + 1 == end) {
            lexer_error("Invalid string literal, ends with a lone '\\'", t, 0, i);
            return create_token(TOKEN_SYNTAX_ERROR_STRING, t);
        }
        size_t start = i;
        unsigned int c;
        if (!report_escape(t, decode_literal_char(t->value, &i, &c), start))
            return create_token(TOKEN_SYNTAX_ERROR_STRING, t);
        data[length++] = (char)c;
    }
    Token* token = create_token(TOKEN_STRING, t);
    token->literal.str.data = data;
    token->literal.str.length = length;
    return token;
}

static list(Token*) splice_adjacent_string(list(Token*) tokens) {
    list(Token*) result = create_list(Token*);
    ListNode* n = tokens->head;
    while (n != NULL) {
        Token* first = (Token*)n->data;
        append(result, first);
        ListNode* end = n;
        size_t value_len = 0;
        size_t data_len = 0;
        for (; end != NULL && end->data != NULL && ((Token*)end->data)->type == TOKEN_STRING; end = end->next) {
            value_len += strlen(((Token*)end->data)->value);
            data_len += ((Token*)end->data)->literal.str.length;
        }
        if (end == n || end == n->next) {
            n = n->next;
            continue;
        }
        char* value = (char*)malloc(value_len);
        char* data = (char*)malloc(data_len + 1);
        if (value == NULL || data == NULL) {
            fprintf(stderr, "[lexer Fatal] at <splice_adjacent_string>: Cannot allocate memory\n");
            abort();
        }
        value_len = 0;
        data_len = 0;
        for (; n != end; n = n->next) {
            Token* t = (Token*)n->data;
            size_t len = strlen(t->value);
            memcpy(value + value_len, t->value, len);
            memcpy(data + data_len, t->literal.str.data, t->literal.str.length);
            value_len += len;
            data_len += t->literal.str.length;
        }
        first->value = create_string(value, value_len);
        first->literal.str.data = create_string(data, data_len);
        first->literal.str.length = data_len;
        free(value);
        free(data);
    }
    return result;
}

list(Token*) pp_to_tokens(list(ppToken*) pp_tokens) {
    list(Token*) tokens = create_list(Token*);
    foreach (ppToken*, t, pp_tokens) {
        switch (t->type) {
            case PP_IDENTIFIER:
                append(tokens, create_token(TOKEN_IDENTIFIER, t));
                break;
            case PP_NUMBER:
                append(tokens, number_token(t));
                break;
            case PP_CHAR:
                append(tokens, char_token(t));
                break;
            case PP_STRING:
                append(tokens, string_token(t));
                break;
            case PP_SYMBOL:
                append(tokens, create_token(TOKEN_SYMBOL, t));
                break;
            case PP_EOF:
                append(tokens, create_token(TOKEN_EOF, t));
                return splice_adjacent_string(tokens);
            case PP_OTHER:
            case PP_PLACE_MARKER:
            case PP_HEADER_NAME:
                assert(false);
            case PP_NEWLINE:
            default:
                break;
        }
    }
    return splice_adjacent_string(tokens);
}
