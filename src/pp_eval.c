#include "lib.h"
#include "preprocessor.h"

ppToken* pp_peek(ppContext* ctx) {
    if (ctx == NULL) return NULL;
    if (ctx->current == NULL || ctx->current->data == NULL)
        return create_pp_token(PP_EOF, NULL, ctx->lexer, ctx->lexer->length);
    return (ppToken*)ctx->current->data;
}

ppToken* pp_get(ppContext* ctx) {
    if (ctx == NULL) return NULL;
    if (ctx->current == NULL || ctx->current->data == NULL)
        return create_pp_token(PP_EOF, NULL, ctx->lexer, ctx->lexer->length);
    ppToken* t = (ppToken*)ctx->current->data;
    ctx->current = ctx->current->next;
    return t;
}

static bool has_error = false;

static bool expect_token(ppContext* ctx, char* message, size_t line, size_t column, ppTokenType type, string value) {
    ppToken* t = pp_peek(ctx);
    if (is_eof(t) || t->type != type || (value != NULL && t->value != value)) {
        preprocessor_error(message, line, column);
        return false;
    }
    pp_get(ctx);
    return true;
}

typedef struct {
    union {
        intmax_t sign;
        uintmax_t unsign;
    } value;
    bool is_unsigned;
} ppIntValue;

#define pp_sign(v) ((ppIntValue){.value.sign = (v), .is_unsigned = false})
#define pp_unsign(v) ((ppIntValue){.value.unsign = (v), .is_unsigned = true})
static inline bool is_true(ppIntValue v) { return v.is_unsigned ? v.value.unsign != 0 : v.value.sign != 0; }
static inline intmax_t get_sign(ppIntValue v) { return v.is_unsigned ? (intmax_t)v.value.unsign : v.value.sign; }
static inline uintmax_t get_unsign(ppIntValue v) { return v.is_unsigned ? v.value.unsign : (uintmax_t)v.value.sign; }
static inline ppIntValue pp_bool(ppIntValue b) { return pp_sign(is_true(b) ? 1 : 0); }
#define pp_true pp_sign(1)
#define pp_false pp_sign(0)

// v-- by ai, need review --v
static int digit_value(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

static ppIntValue eval_number_literal(ppContext* ctx, ppToken* t) {
    assert(t != NULL && t->type == PP_NUMBER);
    string s = t->value;
    size_t i = 0;
    unsigned base = 10;
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        base = 16;
        i = 2;
    } else if (s[0] == '0' && (s[1] == 'b' || s[1] == 'B')) {
        base = 2;
        i = 2;
    } else if (s[0] == '0') base = 8;

    uintmax_t v = 0;
    bool overflow = false;
    size_t start = i;
    for (;; i++) {
        int d = digit_value(s[i]);
        if (d < 0 || (unsigned)d >= base) break;
        if (v > (UINTMAX_MAX - (uintmax_t)d) / base) overflow = true;
        else v = v * base + (uintmax_t)d;
    }

    char e = s[i];
    if (e == '.' || (base == 16 ? (e == 'p' || e == 'P') : (e == 'e' || e == 'E'))) {
        preprocessor_error("Floating constant in preprocessor expression", t->line, t->column);
        return pp_sign(0);
    }
    if (i == start && base != 8) {
        preprocessor_error("Integer constant has no digits", t->line, t->column);
        return pp_sign(0);
    }
    if (digit_value(s[i]) >= 0) {
        preprocessor_error("Invalid digit in integer constant", t->line, t->column);
        return pp_sign(0);
    }

    bool u = false;
    int l = 0;
    while (s[i]) {
        if ((s[i] == 'u' || s[i] == 'U') && !u) {
            u = true;
            i++;
        } else if ((s[i] == 'l' || s[i] == 'L') && l == 0) {
            l = 1;
            i++;
            if (s[i] == s[i - 1]) {
                l = 2;
                i++;
            }
        } else
            break;
    }
    if (s[i] != '\0') {
        preprocessor_error("Invalid suffix on integer constant", t->line, t->column);
        return pp_sign(0);
    }

    if (overflow) {
        preprocessor_error("Integer constant is too large", t->line, t->column);
        return pp_sign(0);
    }
    if (u) return pp_unsign(v);
    if (v > (uintmax_t)INTMAX_MAX) {
        if (base == 10)
            preprocessor_warn("Integer constant is so large that it is unsigned", t->line, t->column);
        return pp_unsign(v);
    }
    return pp_sign((intmax_t)v);
}

static bool decode_escape(ppContext* ctx, ppToken* t, string s, size_t* i, size_t end, unsigned long* out) {
    char c = s[(*i)++];
    switch (c) {
        case 'a': *out = 7; return true;
        case 'b': *out = 8; return true;
        case 'f': *out = 12; return true;
        case 'n': *out = 10; return true;
        case 'r': *out = 13; return true;
        case 't': *out = 9; return true;
        case 'v': *out = 11; return true;
        case '\\':
        case '\'':
        case '"':
        case '?': *out = (unsigned char)c; return true;
        case 'x': {
            uintmax_t v = 0;
            size_t digits = 0;
            while (*i < end && digit_value(s[*i]) >= 0) {
                if (v <= 0xFFFFFFFFul) v = v * 16 + (unsigned)digit_value(s[*i]);
                (*i)++;
                digits++;
            }
            if (digits == 0) {
                preprocessor_error("\\x used with no following hex digits", t->line, t->column);
                return false;
            }
            if (v > 0xFF) {
                preprocessor_warn("Hex escape sequence out of range", t->line, t->column);
                v &= 0xFF;
            }
            *out = (unsigned long)v;
            return true;
        }
        case 'u':
        case 'U':
            // skip, not currently supported
            preprocessor_warn("Universal character name in character constant is not supported", t->line, t->column);
            return false;
        default:
            if (c >= '0' && c <= '7') {
                unsigned long v = (unsigned long)(c - '0');
                for (int k = 0; k < 2 && *i < end && s[*i] >= '0' && s[*i] <= '7'; k++)
                    v = v * 8 + (unsigned long)(s[(*i)++] - '0');
                if (v > 0xFF) {
                    preprocessor_warn("Octal escape sequence out of range", t->line, t->column);
                    v &= 0xFF;
                }
                *out = v;
                return true;
            }
            preprocessor_error("Unknown escape sequence in character constant", t->line, t->column);
            return false;
    }
}

static int eval_char_literal(ppContext* ctx, ppToken* t) {
    assert(t != NULL && t->type == PP_CHAR);
    string s = t->value;
    size_t end = strlen(s) - 1;
    size_t i = 1;
    size_t count = 0;
    unsigned int acc = 0;
    int first = 0;
    while (i < end) {
        unsigned long c;
        if (s[i] == '\\') {
            i++;
            if (!decode_escape(ctx, t, s, &i, end, &c))
                return 0;
        } else
            c = (unsigned char)s[i++];
        if (count == 0)
            first = (int)(char)c;
        acc = (acc << 8) | (unsigned int)(c & 0xFF);
        count++;
    }
    if (count == 0) {
        preprocessor_error("Empty character constant", t->line, t->column);
        return 0;
    }
    if (count == 1) return first;
    else if (count > 4) preprocessor_warn("Multi-character character constant and character constant too long", t->line, t->column);
    else preprocessor_warn("Multi-character character constant", t->line, t->column);
    return (int)acc;
}
// ^-- by ai, need review --^

static ppIntValue eval_conditional_expr(ppContext* ctx, bool skip);

static ppIntValue eval_unary_expr(ppContext* ctx, bool skip) {
    ppToken* t = pp_peek(ctx);
    if (is_eof(t) || t->type == PP_NEWLINE) {
        preprocessor_error("Expected primary expression", t == NULL ? 0 : t->line, t == NULL ? 0 : t->column);
        return pp_sign(0);
    } else if (t->type == PP_IDENTIFIER && t->value == P_DEFINED) {
        pp_get(ctx);  // consume 'defined'
        t = pp_peek(ctx);
        bool has_parens = false;
        if (!is_eof(t) && t->type == PP_SYMBOL && t->value == SYMBOL_L_PARENTHESIS) {
            has_parens = true;
            pp_get(ctx);  // consume '('
        }
        ppToken* name_token = pp_peek(ctx);
        if (!expect_token(ctx, "Expected identifier after defined", name_token->line, name_token->column, PP_IDENTIFIER, NULL))
            return pp_sign(0);
        if (has_parens) {
            if (!expect_token(ctx, "Expected ) after defined(identifier)", name_token->line, name_token->column, PP_SYMBOL, SYMBOL_R_PARENTHESIS))
                return pp_sign(0);
        }
        return find_macro(ctx, name_token->value) != NULL ? pp_true : pp_false;
    } else if (t->type == PP_SYMBOL && (t->value == SYMBOL_ADD || t->value == SYMBOL_SUB || t->value == SYMBOL_BITWISE_NOT || t->value == SYMBOL_LOGICAL_NOT)) {
        pp_get(ctx);  // consume '+', '-', '~', or '!'
        ppIntValue operand = eval_unary_expr(ctx, skip);
        if (t->value == SYMBOL_ADD)
            return operand;
        else if (t->value == SYMBOL_SUB) {
            if (operand.is_unsigned)
                return pp_unsign(0U - operand.value.unsign);
            else
                return pp_sign((intmax_t)(0 - (uintmax_t)get_sign(operand)));
        } else if (t->value == SYMBOL_BITWISE_NOT) {
            if (operand.is_unsigned)
                return pp_unsign(~operand.value.unsign);
            else
                return pp_sign(~operand.value.sign);
        } else
            return is_true(operand) ? pp_false : pp_true;
    } else if (t->type == PP_IDENTIFIER && t->value == P_PRAGMA_) {
        pp_get(ctx);  // consume '_Pragma'
        if (expect_token(ctx, "Expected ( after _Pragma", t->line, t->column, PP_SYMBOL, SYMBOL_L_PARENTHESIS))
            if (expect_token(ctx, "Expected string literal after _Pragma(", t->line, t->column, PP_STRING, NULL))
                expect_token(ctx, "Expected ) after _Pragma(string)", t->line, t->column, PP_SYMBOL, SYMBOL_R_PARENTHESIS);
        return pp_sign(0);
    } else if (t->type == PP_IDENTIFIER) {
        pp_get(ctx);  // consume identifier
        if (expand_macro(ctx, t))
            return eval_unary_expr(ctx, skip);
        return pp_sign(0);
    } else if (t->type == PP_NUMBER) {
        t = pp_get(ctx);  // consume number
        return eval_number_literal(ctx, t);
    } else if (t->type == PP_CHAR) {
        t = pp_get(ctx);  // consume char literal
        return pp_sign((intmax_t)eval_char_literal(ctx, t));
    } else if (t->type == PP_SYMBOL && t->value == SYMBOL_L_PARENTHESIS) {
        t = pp_get(ctx);  // consume '('
        ppIntValue result = eval_conditional_expr(ctx, skip);
        t = pp_peek(ctx);
        if (!expect_token(ctx, "Expected ) after expression", t->line, t->column, PP_SYMBOL, SYMBOL_R_PARENTHESIS))
            return pp_sign(0);
        return result;
    } else {
        preprocessor_error("Expected primary expression", t->line, t->column);
        return pp_sign(0);
    }
}

static ppIntValue eval_multiplicative_expr(ppContext* ctx, bool skip) {
    ppIntValue result = eval_unary_expr(ctx, skip);
    ppToken* t = pp_peek(ctx);
    while (!is_eof(t) && t->type == PP_SYMBOL && (t->value == SYMBOL_MUL || t->value == SYMBOL_DIV || t->value == SYMBOL_MOD)) {
        t = pp_get(ctx);  // consume '*', '/', or '%'
        ppIntValue right = eval_unary_expr(ctx, skip);
        if (t->value == SYMBOL_MUL) {
            if (!result.is_unsigned && !right.is_unsigned)
                result = pp_sign((intmax_t)((uintmax_t)get_sign(result) * (uintmax_t)get_sign(right)));
            else
                result = pp_unsign(get_unsign(result) * get_unsign(right));
        } else if (t->value == SYMBOL_DIV) {
            if (!is_true(right)) {  // right == 0
                if (!skip) {
                    preprocessor_error("Division by zero", t->line, t->column);
                    result = pp_sign(0);
                    break;
                }
            } else if (!result.is_unsigned && !right.is_unsigned) {
                if (!right.is_unsigned && get_sign(right) == -1)
                    result = pp_sign((intmax_t)(0U - (uintmax_t)get_sign(result)));
                else
                    result = pp_sign(get_sign(result) / get_sign(right));
            } else
                result = pp_unsign(get_unsign(result) / get_unsign(right));
        } else {
            if (!is_true(right)) {  // right == 0
                if (!skip) {
                    preprocessor_error("Modulo by zero", t->line, t->column);
                    result = pp_sign(0);
                    break;
                }
            } else if (!result.is_unsigned && !right.is_unsigned) {
                if (!right.is_unsigned && get_sign(right) == -1)
                    result = pp_sign(0);
                else
                    result = pp_sign(get_sign(result) % get_sign(right));
            } else
                result = pp_unsign(get_unsign(result) % get_unsign(right));
        }
        t = pp_peek(ctx);
    }
    return result;
}

static ppIntValue eval_additive_expr(ppContext* ctx, bool skip) {
    ppIntValue result = eval_multiplicative_expr(ctx, skip);
    ppToken* t = pp_peek(ctx);
    while (!is_eof(t) && t->type == PP_SYMBOL && (t->value == SYMBOL_ADD || t->value == SYMBOL_SUB)) {
        t = pp_get(ctx);  // consume '+' or '-'
        ppIntValue right = eval_multiplicative_expr(ctx, skip);
        if (t->value == SYMBOL_ADD) {
            if (!result.is_unsigned && !right.is_unsigned)
                result = pp_sign((intmax_t)((uintmax_t)get_sign(result) + (uintmax_t)get_sign(right)));
            else
                result = pp_unsign(get_unsign(result) + get_unsign(right));
        } else {
            if (!result.is_unsigned && !right.is_unsigned)
                result = pp_sign((intmax_t)((uintmax_t)get_sign(result) - (uintmax_t)get_sign(right)));
            else
                result = pp_unsign(get_unsign(result) - get_unsign(right));
        }
        t = pp_peek(ctx);
    }
    return result;
}

static ppIntValue eval_shift_expr(ppContext* ctx, bool skip) {
    ppIntValue result = eval_additive_expr(ctx, skip);
    ppToken* t = pp_peek(ctx);
    while (!is_eof(t) && t->type == PP_SYMBOL && (t->value == SYMBOL_L_SHIFT || t->value == SYMBOL_R_SHIFT)) {
        t = pp_get(ctx);  // consume '<<' or '>>'
        ppIntValue right = eval_additive_expr(ctx, skip);
        uintmax_t n = 0;
        if (right.is_unsigned)
            n = get_unsign(right);
        else if (get_sign(right) < 0) {
            if (!skip) {
                preprocessor_error("Negative shift count", t->line, t->column);
                result = pp_sign(0);
                break;
            }
        } else
            n = (uintmax_t)get_sign(right);

        if (n >= sizeof(intmax_t) * CHAR_BIT) {
            if (!skip) {
                preprocessor_error("Shift count too large", t->line, t->column);
                result = pp_sign(0);
                break;
            }
            n = 0;
        }

        if (t->value == SYMBOL_L_SHIFT) {
            if (result.is_unsigned)
                result = pp_unsign(get_unsign(result) << n);
            else
                result = pp_sign((intmax_t)((uintmax_t)get_sign(result) << n));
        } else {
            if (result.is_unsigned)
                result = pp_unsign(get_unsign(result) >> n);
            else
                result = pp_sign(get_sign(result) >> n);
        }
        t = pp_peek(ctx);
    }
    return result;
}

static ppIntValue eval_relational_expr(ppContext* ctx, bool skip) {
    ppIntValue result = eval_shift_expr(ctx, skip);
    ppToken* t = pp_peek(ctx);
    while (!is_eof(t) && t->type == PP_SYMBOL && (t->value == SYMBOL_LT || t->value == SYMBOL_GT || t->value == SYMBOL_LE || t->value == SYMBOL_GE)) {
        t = pp_get(ctx);  // consume '<', '>', '<=', '>='
        ppIntValue right = eval_shift_expr(ctx, skip);
        bool cmp;
        if (!result.is_unsigned && !right.is_unsigned) {
            intmax_t left_val = get_sign(result);
            intmax_t right_val = get_sign(right);
            if (t->value == SYMBOL_LT)
                cmp = left_val < right_val;
            else if (t->value == SYMBOL_GT)
                cmp = left_val > right_val;
            else if (t->value == SYMBOL_LE)
                cmp = left_val <= right_val;
            else
                cmp = left_val >= right_val;
        } else {
            uintmax_t left_val = get_unsign(result);
            uintmax_t right_val = get_unsign(right);
            if (t->value == SYMBOL_LT)
                cmp = left_val < right_val;
            else if (t->value == SYMBOL_GT)
                cmp = left_val > right_val;
            else if (t->value == SYMBOL_LE)
                cmp = left_val <= right_val;
            else
                cmp = left_val >= right_val;
        }
        result = cmp ? pp_true : pp_false;
        t = pp_peek(ctx);
    }
    return result;
}

static ppIntValue eval_equality_expr(ppContext* ctx, bool skip) {
    ppIntValue result = eval_relational_expr(ctx, skip);
    ppToken* t = pp_peek(ctx);
    while (!is_eof(t) && t->type == PP_SYMBOL && (t->value == SYMBOL_EQ || t->value == SYMBOL_NE)) {
        t = pp_get(ctx);  // consume '==' or '!='
        ppIntValue right = eval_relational_expr(ctx, skip);
        bool eq;
        if (!result.is_unsigned && !right.is_unsigned)
            eq = get_sign(result) == get_sign(right);
        else
            eq = get_unsign(result) == get_unsign(right);
        result = ((t->value == SYMBOL_EQ) == eq) ? pp_true : pp_false;
        t = pp_peek(ctx);
    }
    return result;
}

static ppIntValue eval_and_expr(ppContext* ctx, bool skip) {
    ppIntValue result = eval_equality_expr(ctx, skip);
    ppToken* t = pp_peek(ctx);
    while (!is_eof(t) && t->type == PP_SYMBOL && t->value == SYMBOL_BITWISE_AND) {
        pp_get(ctx);  // consume '&'
        ppIntValue right = eval_equality_expr(ctx, skip);
        if (!result.is_unsigned && !right.is_unsigned)
            result = pp_sign(get_sign(result) & get_sign(right));
        else
            result = pp_unsign(get_unsign(result) & get_unsign(right));
        t = pp_peek(ctx);
    }
    return result;
}

static ppIntValue eval_exclusive_or_expr(ppContext* ctx, bool skip) {
    ppIntValue result = eval_and_expr(ctx, skip);
    ppToken* t = pp_peek(ctx);
    while (!is_eof(t) && t->type == PP_SYMBOL && t->value == SYMBOL_XOR) {
        pp_get(ctx);  // consume '^'
        ppIntValue right = eval_and_expr(ctx, skip);
        if (!result.is_unsigned && !right.is_unsigned)
            result = pp_sign(get_sign(result) ^ get_sign(right));
        else
            result = pp_unsign(get_unsign(result) ^ get_unsign(right));
        t = pp_peek(ctx);
    }
    return result;
}

static ppIntValue eval_inclusive_or_expr(ppContext* ctx, bool skip) {
    ppIntValue result = eval_exclusive_or_expr(ctx, skip);
    ppToken* t = pp_peek(ctx);
    while (!is_eof(t) && t->type == PP_SYMBOL && t->value == SYMBOL_BITWISE_OR) {
        pp_get(ctx);  // consume '|'
        ppIntValue right = eval_exclusive_or_expr(ctx, skip);
        if (!result.is_unsigned && !right.is_unsigned)
            result = pp_sign(get_sign(result) | get_sign(right));
        else
            result = pp_unsign(get_unsign(result) | get_unsign(right));
        t = pp_peek(ctx);
    }
    return result;
}

static ppIntValue eval_logic_and_expr(ppContext* ctx, bool skip) {
    ppIntValue result = eval_inclusive_or_expr(ctx, skip);
    ppToken* t = pp_peek(ctx);
    while (!is_eof(t) && t->type == PP_SYMBOL && t->value == SYMBOL_LOGICAL_AND) {
        pp_get(ctx);  // consume '&&'
        if (is_true(result))
            result = pp_bool(eval_inclusive_or_expr(ctx, skip));
        else {
            eval_inclusive_or_expr(ctx, true);  // skip the right side
            result = pp_false;
        }
        t = pp_peek(ctx);
    }
    return result;
}

static ppIntValue eval_logic_or_expr(ppContext* ctx, bool skip) {
    ppIntValue result = eval_logic_and_expr(ctx, skip);
    ppToken* t = pp_peek(ctx);
    while (!is_eof(t) && t->type == PP_SYMBOL && t->value == SYMBOL_LOGICAL_OR) {
        pp_get(ctx);  // consume '||'
        if (!is_true(result))
            result = pp_bool(eval_logic_and_expr(ctx, skip));
        else {
            eval_logic_and_expr(ctx, true);  // skip the right side
            result = pp_true;
        }
        t = pp_peek(ctx);
    }
    return result;
}

static ppIntValue eval_conditional_expr(ppContext* ctx, bool skip) {
    ppIntValue result = eval_logic_or_expr(ctx, skip);
    ppToken* t = pp_peek(ctx);
    if (!is_eof(t) && t->type == PP_SYMBOL && t->value == SYMBOL_QUESTION) {
        pp_get(ctx);  // consume '?'
        ppIntValue skipped = result.is_unsigned ? pp_unsign(0) : pp_sign(0);
        if (is_true(result)) {
            result = eval_conditional_expr(ctx, skip);
            t = pp_peek(ctx);
            if (!expect_token(ctx, "Expected : in conditional expression", t->line, t->column, PP_SYMBOL, SYMBOL_COLON))
                result = pp_sign(0);
            else
                skipped = eval_conditional_expr(ctx, true);  // skip the false branch
        } else {
            skipped = eval_conditional_expr(ctx, true);  // skip the true branch
            t = pp_peek(ctx);
            if (!expect_token(ctx, "Expected : in conditional expression", t->line, t->column, PP_SYMBOL, SYMBOL_COLON))
                result = pp_sign(0);
            else
                result = eval_conditional_expr(ctx, skip);
        }
        if (skipped.is_unsigned && !result.is_unsigned)
            result = pp_unsign((uintmax_t)get_sign(result));
    }
    return result;
}

bool eval_conditional(ppContext* ctx, bool* eval_error) {
    has_error = false;
    bool result = is_true(eval_conditional_expr(ctx, false));
    ppToken* t = pp_peek(ctx);
    if (!is_eof(t) && t->type != PP_NEWLINE)
        preprocessor_error("Unexpected token after conditional expression", t->line, t->column);
    if (has_error) {
        *eval_error = true;
        return false;
    }
    return result;
}
