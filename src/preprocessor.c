#include "preprocessor.h"

#define line(lexer, pos) ((pos >= lexer->length) ? lexer->line_map[lexer->length] : lexer->line_map[pos])
#define column(lexer, pos) ((pos >= lexer->length) ? lexer->column_map[lexer->length] : lexer->column_map[pos])
#define peek_char(lexer) ((lexer->pos >= lexer->length) ? '\0' : lexer->source_code[lexer->pos])
#define next_char(lexer) ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1])
#define unget_char(lexer) \
    if (lexer->pos > 0) lexer->pos -= 1
#define pp_token(type, value, pos) append(lexer->pp_tokens, create_pp_token(type, value, lexer, pos))
#define is_digit(c) ((c) >= '0' && (c) <= '9')
#define is_alphabet(c) ((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z')
#define is_hex_digit(c) (is_digit(c) || ((c) >= 'a' && (c) <= 'f') || ((c) >= 'A' && (c) <= 'F'))
#define is_oct_digit(c) ((c) >= '0' && (c) <= '7')
#define pp_lexer_error(message, pos) fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", (has_error = true, lexer->filename), line(lexer, pos), column(lexer, pos), message)
#define preprocessor_error(message, line, column) fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = true, ctx->lexer->filename), line, column, message)
#define preprocessor_warn(message, line, column) fprintf(stderr, "[Preprocess Warning] at %s:%zu:%zu: %s\n", ctx->lexer->filename, line, column, message)
#define content_string(start) create_string(&lexer->source_code[start], lexer->pos - start)
#define is_eof(t) ((t) == NULL || (t)->type == PP_EOF)

static bool has_error = false;

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

static ppLexer* create_pp_lexer(string filename, string source_code) {
    ppLexer* lexer = create_struct(ppLexer);
    if (source_code == NULL) {
        fprintf(stderr, "[preprocessor Error] at <create_pp_lexer>: Failed to create ppLexer, source_code is NULL\n");
        has_error = true;
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

static void pp_lexer(ppLexer* lexer) {
    while (true) {
        char c = next_char(lexer);
        if (c == '\0') {
            pp_token(PP_EOF, NULL, lexer->length);
            return;
        } else if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f') {
            if (c == '\n') pp_token(PP_NEWLINE, NULL, lexer->pos - 1);
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
                    pp_lexer_error("Unterminated string literal", start);
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
                    pp_lexer_error("Unterminated char literal", start);
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
                        pp_lexer_error("Unterminated comment", start);
                        break;
                    } else if (c == '*') {
                        c = next_char(lexer);
                        if (c == '/') break;
                    }
                }
            } else if (c == '=') pp_token(PP_SYMBOL, SYMBOL_DIV_ASSIGN, start);
            else {
                unget_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_DIV, start);
            }
        } else if (c == '-') {
            c = next_char(lexer);
            if (c == '-') pp_token(PP_SYMBOL, SYMBOL_DECREMENT, lexer->pos - 2);
            else if (c == '=') pp_token(PP_SYMBOL, SYMBOL_SUB_ASSIGN, lexer->pos - 2);
            else if (c == '>') pp_token(PP_SYMBOL, SYMBOL_ARROW, lexer->pos - 2);
            else {
                unget_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_SUB, lexer->pos - 1);
            }
        } else if (c == '!') {
            if (peek_char(lexer) == '=') {
                c = next_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_NE, lexer->pos - 2);
            } else pp_token(PP_SYMBOL, SYMBOL_LOGICAL_NOT, lexer->pos - 1);
        } else if (c == '*') {
            if (peek_char(lexer) == '=') {
                c = next_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_MUL_ASSIGN, lexer->pos - 2);
            } else pp_token(PP_SYMBOL, SYMBOL_MUL, lexer->pos - 1);
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
            if (c == '&') pp_token(PP_SYMBOL, SYMBOL_LOGICAL_AND, lexer->pos - 2);
            else if (c == '=') pp_token(PP_SYMBOL, SYMBOL_AND_ASSIGN, lexer->pos - 2);
            else {
                unget_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_BITWISE_AND, lexer->pos - 1);
            }
        } else if (c == '%') {
            if (peek_char(lexer) == '=') {
                next_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_MOD_ASSIGN, lexer->pos - 2);
            } else pp_token(PP_SYMBOL, SYMBOL_MOD, lexer->pos - 1);
        } else if (c == '^') {
            if (peek_char(lexer) == '=') {
                next_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_XOR_ASSIGN, lexer->pos - 2);
            } else pp_token(PP_SYMBOL, SYMBOL_XOR, lexer->pos - 1);
        } else if (c == '=') {
            if (peek_char(lexer) == '=') {
                next_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_EQ, lexer->pos - 2);
            } else pp_token(PP_SYMBOL, SYMBOL_ASSIGN, lexer->pos - 1);
        } else if (c == '+') {
            c = next_char(lexer);
            if (c == '+') pp_token(PP_SYMBOL, SYMBOL_INCREMENT, lexer->pos - 2);
            else if (c == '=') pp_token(PP_SYMBOL, SYMBOL_ADD_ASSIGN, lexer->pos - 2);
            else {
                unget_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_ADD, lexer->pos - 1);
            }
        } else if (c == '<') {
            c = next_char(lexer);
            if (c == '=') pp_token(PP_SYMBOL, SYMBOL_LE, lexer->pos - 2);
            else if (c == '<') {
                if (peek_char(lexer) == '=') {
                    c = next_char(lexer);
                    pp_token(PP_SYMBOL, SYMBOL_L_SHIFT_ASSIGN, lexer->pos - 3);
                } else pp_token(PP_SYMBOL, SYMBOL_L_SHIFT, lexer->pos - 2);
            } else {
                unget_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_LT, lexer->pos - 1);
            }
        } else if (c == '>') {
            c = next_char(lexer);
            if (c == '=') pp_token(PP_SYMBOL, SYMBOL_GE, lexer->pos - 2);
            else if (c == '>') {
                if (peek_char(lexer) == '=') {
                    c = next_char(lexer);
                    pp_token(PP_SYMBOL, SYMBOL_R_SHIFT_ASSIGN, lexer->pos - 3);
                } else pp_token(PP_SYMBOL, SYMBOL_R_SHIFT, lexer->pos - 2);
            } else {
                unget_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_GT, lexer->pos - 1);
            }
        } else if (c == '|') {
            c = next_char(lexer);
            if (c == '|') pp_token(PP_SYMBOL, SYMBOL_LOGICAL_OR, lexer->pos - 2);
            else if (c == '=') pp_token(PP_SYMBOL, SYMBOL_OR_ASSIGN, lexer->pos - 2);
            else {
                unget_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_BITWISE_OR, lexer->pos - 1);
            }
        } else if (c == ',') pp_token(PP_SYMBOL, SYMBOL_COMMA, lexer->pos - 1);
        else if (c == ';') pp_token(PP_SYMBOL, SYMBOL_SEMICOLON, lexer->pos - 1);
        else if (c == ':') pp_token(PP_SYMBOL, SYMBOL_COLON, lexer->pos - 1);
        else if (c == '?') pp_token(PP_SYMBOL, SYMBOL_QUESTION, lexer->pos - 1);
        else if (c == '(') pp_token(PP_SYMBOL, SYMBOL_L_PARENTHESIS, lexer->pos - 1);
        else if (c == ')') pp_token(PP_SYMBOL, SYMBOL_R_PARENTHESIS, lexer->pos - 1);
        else if (c == '[') pp_token(PP_SYMBOL, SYMBOL_L_BRACKET, lexer->pos - 1);
        else if (c == ']') pp_token(PP_SYMBOL, SYMBOL_R_BRACKET, lexer->pos - 1);
        else if (c == '{') pp_token(PP_SYMBOL, SYMBOL_L_BRACE, lexer->pos - 1);
        else if (c == '}') pp_token(PP_SYMBOL, SYMBOL_R_BRACE, lexer->pos - 1);
        else if (c == '~') pp_token(PP_SYMBOL, SYMBOL_BITWISE_NOT, lexer->pos - 1);
        else if (c == '#') {
            if (peek_char(lexer) == '#') {
                next_char(lexer);
                pp_token(PP_SYMBOL, SYMBOL_DOUBLE_HASH, lexer->pos - 2);
            } else pp_token(PP_SYMBOL, SYMBOL_HASH, lexer->pos - 1);
        } else pp_token(PP_OTHER, create_string(&lexer->source_code[lexer->pos - 1], 1), lexer->pos - 1);
    }
}

static ppCondFrame* create_pp_cond_frame(ppToken* directive) {
    ppCondFrame* frame = create_struct(ppCondFrame);
    frame->active = false;
    frame->taken = false;
    frame->in_else = false;
    frame->directive = directive;
    return frame;
}
static ppMacro* create_pp_macro(string name, bool is_function) {
    ppMacro* macro = create_struct(ppMacro);
    macro->name = name;
    macro->params = NULL;
    if (is_function)
        macro->params = create_list(string);
    macro->is_variadic = false;
    macro->body = create_list(ppToken*);
    return macro;
}
static ppContext* create_pp_context(ppLexer* lexer) {
    ppContext* context = create_struct(ppContext);
    context->macros = create_list(ppMacro*);
    context->cond_stack = create_list(ppCondFrame*);
    context->current = NULL;
    context->output = create_list(ppToken*);
    context->lexer = lexer;
    return context;
}

static void skip_to_newline(ppContext* ctx) {
    assert(ctx != NULL);
    while (ctx->current != NULL) {
        if (ctx->current->data == NULL)
            return;
        ppToken* t = (ppToken*)ctx->current->data;
        if (is_eof(t) || t->type == PP_NEWLINE)
            return;
        ctx->current = ctx->current->next;
    }
}
static ppMacro* find_macro(ppContext* ctx, string name) {
    assert(ctx != NULL);
    foreach (ppMacro*, macro, ctx->macros)
        if (macro->name == name)
            return macro;
    return NULL;
}
static bool cond_active(ppContext* ctx) {
    assert(ctx != NULL);
    if (list_empty(ctx->cond_stack))
        return true;
    return ((ppCondFrame*)ctx->cond_stack->tail->data)->active;
}

static ppToken* pp_peek(ppContext* ctx) {
    if (ctx == NULL) return NULL;
    if (ctx->current == NULL || ctx->current->data == NULL)
        return create_pp_token(PP_EOF, NULL, ctx->lexer, ctx->lexer->length);
    return (ppToken*)ctx->current->data;
}

static ppToken* pp_get(ppContext* ctx) {
    if (ctx == NULL) return NULL;
    if (ctx->current == NULL || ctx->current->data == NULL)
        return create_pp_token(PP_EOF, NULL, ctx->lexer, ctx->lexer->length);
    ppToken* t = (ppToken*)ctx->current->data;
    ctx->current = ctx->current->next;
    return t;
}

static bool expect_token(ppContext* ctx, char* message, size_t line, size_t column, ppTokenType type, string value) {
    ppToken* t = pp_peek(ctx);
    if (is_eof(t) || t->type != type || (value != NULL && t->value != value)) {
        preprocessor_error(message, line, column);
        return false;
    }
    pp_get(ctx);
    return true;
}

static int op_prec(ppToken* t) {
    if (t == NULL || t->type != PP_SYMBOL) return 0;
    string v = t->value;
    if (v == SYMBOL_LOGICAL_OR) return 1;
    if (v == SYMBOL_LOGICAL_AND) return 2;
    if (v == SYMBOL_BITWISE_OR) return 3;
    if (v == SYMBOL_XOR) return 4;
    if (v == SYMBOL_BITWISE_AND) return 5;
    if (v == SYMBOL_EQ || v == SYMBOL_NE) return 6;
    if (v == SYMBOL_LT || v == SYMBOL_GT || v == SYMBOL_LE || v == SYMBOL_GE) return 7;
    if (v == SYMBOL_L_SHIFT || v == SYMBOL_R_SHIFT) return 8;
    if (v == SYMBOL_ADD || v == SYMBOL_SUB) return 9;
    if (v == SYMBOL_MUL || v == SYMBOL_DIV || v == SYMBOL_MOD) return 10;
    return 0;
}

static long long apply_binop(ppToken* op, long long lhs, long long rhs) {
    if (op == NULL || op->type != PP_SYMBOL) return 0;
    else if (op->value == SYMBOL_LOGICAL_OR) return (lhs || rhs) ? 1 : 0;
    else if (op->value == SYMBOL_LOGICAL_AND) return (lhs && rhs) ? 1 : 0;
    else if (op->value == SYMBOL_BITWISE_OR) return lhs | rhs;
    else if (op->value == SYMBOL_XOR) return lhs ^ rhs;
    else if (op->value == SYMBOL_BITWISE_AND) return lhs & rhs;
    else if (op->value == SYMBOL_EQ) return lhs == rhs;
    else if (op->value == SYMBOL_NE) return lhs != rhs;
    else if (op->value == SYMBOL_LT) return lhs < rhs;
    else if (op->value == SYMBOL_GT) return lhs > rhs;
    else if (op->value == SYMBOL_LE) return lhs <= rhs;
    else if (op->value == SYMBOL_GE) return lhs >= rhs;
    else if (op->value == SYMBOL_L_SHIFT) return lhs << rhs;
    else if (op->value == SYMBOL_R_SHIFT) return lhs >> rhs;
    else if (op->value == SYMBOL_ADD) return lhs + rhs;
    else if (op->value == SYMBOL_SUB) return lhs - rhs;
    else if (op->value == SYMBOL_MUL) return lhs * rhs;
    else if (op->value == SYMBOL_DIV) return rhs == 0 ? 0 : lhs / rhs;
    else if (op->value == SYMBOL_MOD) return rhs == 0 ? 0 : lhs % rhs;
    else return 0;
}

static long long parse_int_literal(string s) {
    string p = s;
    int base = 0;
    if (p[0] == '0' && (p[1] == 'b' || p[1] == 'B')) {
        base = 2;
        p += 2;
    }
    string q = p;
    bool is_unsigned = false;
    while (q[0] != '\0') {
        if (q[0] == 'u' || q[0] == 'U')
            is_unsigned = true;
        q++;
    }
    char* endptr;
    if (is_unsigned) {
        unsigned long long v = strtoull(p, &endptr, base);
        if (*endptr != '\0') {
            fprintf(stderr, "[Preprocessor Error] at <parse_int_literal>: Invalid integer literal: %s\n", s);
            has_error = true;
            return 0;
        }
        return (long long)v;
    }
    long long v = strtoll(p, &endptr, base);
    if (*endptr != '\0') {
        fprintf(stderr, "[Preprocessor Error] at <parse_int_literal>: Invalid integer literal: %s\n", s);
        has_error = true;
        return 0;
    }
    return v;
}

static void skip_conditional(ppContext* ctx);

static void skip_primary(ppContext* ctx) {
    ppToken* t = pp_peek(ctx);
    if (is_eof(t) || t->type == PP_NEWLINE) return;

    if (t->type == PP_SYMBOL && t->value == SYMBOL_L_PARENTHESIS) {
        pp_get(ctx);
        skip_conditional(ctx);
        expect_token(ctx, "Expected ) in expression end", t->line, t->column, PP_SYMBOL, SYMBOL_R_PARENTHESIS);
        return;
    }
    pp_get(ctx);
}

static void skip_unary(ppContext* ctx) {
    ppToken* t = pp_peek(ctx);
    if (is_eof(t) || t->type == PP_NEWLINE) return;

    // defined / defined(...)
    if (t->type == PP_IDENTIFIER && t->value == P_DEFINED) {
        pp_get(ctx);
        ppToken* nt = pp_peek(ctx);
        if (is_eof(nt) || nt->type == PP_NEWLINE) return;
        if (nt->type == PP_SYMBOL && nt->value == SYMBOL_L_PARENTHESIS) {
            pp_get(ctx);
            ppToken* name = pp_peek(ctx);
            if (!is_eof(name) && name->type == PP_IDENTIFIER)
                pp_get(ctx);
            expect_token(ctx, "Expected ) in defined(...)", t->line, t->column, PP_SYMBOL, SYMBOL_R_PARENTHESIS);
            return;
        }
        if (nt->type == PP_IDENTIFIER) {
            pp_get(ctx);
            return;
        }
        return;
    }

    // unary operators: +, -, !, ~
    if (t->type == PP_SYMBOL && (t->value == SYMBOL_ADD || t->value == SYMBOL_SUB || t->value == SYMBOL_LOGICAL_NOT || t->value == SYMBOL_BITWISE_NOT)) {
        pp_get(ctx);
        skip_unary(ctx);
        return;
    }

    skip_primary(ctx);
}

static void skip_expr(ppContext* ctx, int min_prec) {
    skip_unary(ctx);
    while (true) {
        ppToken* t = pp_peek(ctx);
        if (is_eof(t)) break;
        int prec = op_prec(t);
        if (prec == 0 || prec < min_prec) break;
        pp_get(ctx);
        skip_expr(ctx, prec + 1);
    }
}

static void skip_conditional(ppContext* ctx) {
    skip_expr(ctx, 0);
    ppToken* t = pp_peek(ctx);
    if (is_eof(t)) return;
    if (t->type != PP_SYMBOL || t->value != SYMBOL_QUESTION) return;
    pp_get(ctx);  // consume '?'

    skip_conditional(ctx);  // then branch
    expect_token(ctx, "Expected : in skipped expression", t->line, t->column, PP_SYMBOL, SYMBOL_COLON);
    skip_conditional(ctx);  // else branch
}

static list(list(ppToken*)) collect_args(ppContext* ctx, ppToken* name, size_t expected, bool is_variadic) {
    expect_token(ctx, "Expected ( in macro invocation", name->line, name->column, PP_SYMBOL, SYMBOL_L_PARENTHESIS);
    size_t count = 0;
    list(list(ppToken*)) args = create_list(list(ppToken*));
    list(ppToken*) cur = create_list(ppToken*);
    int depth = 0;
    while (true) {
        ppToken* t = pp_get(ctx);
        if (is_eof(t)) {
            preprocessor_error("Unterminated macro arguments", name->line, name->column);
            return NULL;
        } else if (t->type == PP_NEWLINE) {
            continue;
        } else if (t->type == PP_SYMBOL && t->value == SYMBOL_L_PARENTHESIS) {
            depth++;
        } else if (t->type == PP_SYMBOL && t->value == SYMBOL_R_PARENTHESIS) {
            if (depth == 0)
                break;
            depth--;
        } else if (t->type == PP_SYMBOL && t->value == SYMBOL_COMMA && depth == 0) {
            count++;
            if (!(is_variadic && count > expected)) {
                append(args, cur);
                cur = create_list(ppToken*);
                continue;
            }
        }
        append(cur, t);
    }
    if (expected == 0 && list_empty(cur) && list_empty(args))
        return args;  // empty list
    count++;
    append(args, cur);
    if ((!is_variadic && count != expected) || (is_variadic && count < expected)) {
        preprocessor_error("Incorrect number of macro arguments", name->line, name->column);
        return NULL;
    }
    return args;
}

static ppToken* copy_pp_token(ppTokenType type, string value, ppToken* name) {
    ppToken* new_token = create_struct(ppToken);
    new_token->type = type;
    new_token->value = value;
    new_token->line = name->line;
    new_token->column = name->column;
    return new_token;
}

static string create_string_from_tokens(list(ppToken*) tokens) {
    if (list_empty(tokens))
        return create_string("", 0);
    size_t len = 0;
    size_t n = 0;
    foreach (ppToken*, t, tokens) {
        len += strlen(t->value);
        n++;
    }
    string buf = malloc(len * 3 + n + 5);
    size_t p = 0;
    ppToken* prev = NULL;
    buf[p++] = '"';
    foreach (ppToken*, t, tokens) {
        if (prev != NULL) {
            if (!(prev->line == t->line && prev->column + strlen(prev->value) == t->column))
                buf[p++] = ' ';
        }
        prev = t;
        for (string s = t->value; *s != '\0'; s++) {
            if (*s == '\\' || *s == '"')
                buf[p++] = '\\';
            buf[p++] = *s;
        }
    }
    buf[p++] = '"';
    buf[p] = '\0';
    string result = create_string(buf, p);
    free(buf);
    return result;
}

static list(ppToken*) paste_tokens(ppContext* ctx, list(ppToken*) tokens) {
    list(ppToken*) out = create_list(ppToken*);
    ListNode* node = tokens->head;
    while (node != NULL) {
        ppToken* t = (ppToken*)node->data;
        if (t->type == PP_SYMBOL && t->value == SYMBOL_DOUBLE_HASH) {
            if (out->tail == NULL || node->next == NULL) {
                preprocessor_error("## cannot appear at boundary", t->line, t->column);
                node = node->next;
                continue;
            }
            ppToken* left = (ppToken*)out->tail->data;
            ppToken* right = (ppToken*)node->next->data;
            size_t len_l = strlen(left->value);
            size_t len_r = strlen(right->value);
            string buf = malloc(len_l + len_r + 1);
            memcpy(buf, left->value, len_l);
            memcpy(buf + len_l, right->value, len_r);
            buf[len_l + len_r] = '\0';
            string new_value = create_string(buf, len_l + len_r);
            free(buf);

            char c = new_value[0];
            ppTokenType type = PP_SYMBOL;
            if (c == '\0')
                type = PP_OTHER;
            else if (is_alphabet(c) || c == '_')
                type = PP_IDENTIFIER;
            else if (is_digit(c) || c == '.')
                type = PP_NUMBER;
            out->tail->data = copy_pp_token(type, new_value, left);
            node = node->next->next;
        } else {
            append(out, t);
            node = node->next;
        }
    }
    return out;
}

static list(ppToken*) substitute(ppContext* ctx, ppMacro* macro, list(list(ppToken*)) args, ppToken* name) {
    list(ppToken*) result = create_list(ppToken*);
    if (list_empty(macro->body))
        return result;
    if (macro->params == NULL) {
        foreach (ppToken*, t, macro->body)
            append(result, copy_pp_token(t->type, t->value, name));
        return result;
    }
    bool stringize = false;
    ppToken* hash_token = NULL;
    foreach (ppToken*, t, macro->body) {
        if (t->type == PP_IDENTIFIER) {
            ListNode* arg__n = args->head;
            bool matched = false;
            foreach (string, param, macro->params) {
                assert(arg__n != NULL);
                list(ppToken*) arg = (list(ppToken*))arg__n->data;
                if (param == t->value) {
                    if (stringize) {
                        append(result, copy_pp_token(PP_STRING, create_string_from_tokens(arg), name));
                        stringize = false;
                    } else {
                        foreach (ppToken*, arg_t, arg)
                            append(result, copy_pp_token(arg_t->type, arg_t->value, name));
                    }
                    matched = true;
                    break;
                }
                arg__n = arg__n->next;
            }
            if (!matched && t->value == P_VA_ARGS && macro->is_variadic) {
                list(ppToken*) arg = (arg__n != NULL) ? (list(ppToken*))arg__n->data : create_list(ppToken*);
                if (stringize) {
                    append(result, copy_pp_token(PP_STRING, create_string_from_tokens(arg), name));
                    stringize = false;
                } else {
                    foreach (ppToken*, arg_t, arg)
                        append(result, copy_pp_token(arg_t->type, arg_t->value, name));
                }
                matched = true;
            }
            if (matched) continue;
        }
        if (t->type == PP_SYMBOL && t->value == SYMBOL_HASH) {
            if (stringize) {
                preprocessor_error("Invalid use of # operator in macro", hash_token->line, hash_token->column);
                stringize = false;
                continue;
            }
            stringize = true;
            hash_token = t;
        } else {
            if (stringize) {
                preprocessor_error("Invalid use of # operator in macro", hash_token->line, hash_token->column);
                stringize = false;
            } else
                append(result, copy_pp_token(t->type, t->value, name));
        }
    }
    if (stringize)
        preprocessor_error("Invalid use of # operator in macro", hash_token->line, hash_token->column);
    return paste_tokens(ctx, result);
}

static bool expand_macro(ppContext* ctx, ppToken* name) {
    ppMacro* macro = find_macro(ctx, name->value);
    if (macro == NULL) return false;

    list(list(ppToken*)) args = NULL;
    if (macro->params != NULL) {
        size_t expected = 0;
        foreach (string, param, macro->params) expected++;
        ListNode* t = ctx->current;
        args = collect_args(ctx, name, expected, macro->is_variadic);
        if (args == NULL) {
            ctx->current = t;
            return false;
        }
    } else {
        args = NULL;
    }
    list(ppToken*) result = substitute(ctx, macro, args, name);
    if (list_empty(result))
        return true;
    result->tail->next = ctx->current;
    ctx->current = result->head;
    return true;
}

static long long eval_conditional(ppContext* ctx);

static long long eval_primary(ppContext* ctx) {
    ppToken* t = pp_peek(ctx);
    if (is_eof(t) || t->type == PP_NEWLINE) {
        preprocessor_error("Unexpected end of #if expression", t == NULL ? 0 : t->line, t == NULL ? 0 : t->column);
        return 0;
    }
    if (t->type == PP_NUMBER) {
        pp_get(ctx);
        return parse_int_literal(t->value);
    }
    // TODO: handle string and char literals in #if expressions
    if (t->type == PP_SYMBOL && t->value == SYMBOL_L_PARENTHESIS) {
        pp_get(ctx);
        long long v = eval_conditional(ctx);
        if (!expect_token(ctx, "Expected ) in #if expression", t->line, t->column, PP_SYMBOL, SYMBOL_R_PARENTHESIS))
            return v;
        return v;
    }
    if (t->type == PP_IDENTIFIER) {
        pp_get(ctx);
        if (expand_macro(ctx, t))
            return eval_primary(ctx);
        return 0;
    }
    preprocessor_error("Unexpected token in #if expression", t->line, t->column);
    return 0;
}

static long long eval_unary(ppContext* ctx) {
    ppToken* t = pp_peek(ctx);
    if (is_eof(t) || t->type == PP_NEWLINE) {
        preprocessor_error("Unexpected end in #if expression", t == NULL ? 0 : t->line, t == NULL ? 0 : t->column);
        return 0;
    }

    // defined
    if (t->type == PP_IDENTIFIER && t->value == P_DEFINED) {
        pp_get(ctx);
        ppToken* nt = pp_peek(ctx);
        if (is_eof(nt)) {
            preprocessor_error("Expected identifier after defined", t->line, t->column);
            return 0;
        }
        // defined(NAME)
        if (nt->type == PP_SYMBOL && nt->value == SYMBOL_L_PARENTHESIS) {
            pp_get(ctx);
            ppToken* name = pp_peek(ctx);
            if (is_eof(name) || name->type != PP_IDENTIFIER) {
                preprocessor_error("Expected identifier in defined(...)", t->line, t->column);
                return 0;
            }
            pp_get(ctx);
            if (!expect_token(ctx, "Expected ) in defined(...)", t->line, t->column, PP_SYMBOL, SYMBOL_R_PARENTHESIS))
                return 0;
            return find_macro(ctx, name->value) != NULL ? 1 : 0;
        }
        // defined NAME
        if (nt->type == PP_IDENTIFIER) {
            pp_get(ctx);
            return find_macro(ctx, nt->value) != NULL ? 1 : 0;
        }
        preprocessor_error("Expected identifier after defined", t->line, t->column);
        return 0;
    }

    // unary operators: +, -, !, ~
    if (t->type == PP_SYMBOL && (t->value == SYMBOL_ADD || t->value == SYMBOL_SUB || t->value == SYMBOL_LOGICAL_NOT || t->value == SYMBOL_BITWISE_NOT)) {
        pp_get(ctx);
        long long v = eval_unary(ctx);
        if (t->value == SYMBOL_SUB) return -v;
        if (t->value == SYMBOL_LOGICAL_NOT) return !v;
        if (t->value == SYMBOL_BITWISE_NOT) return ~v;
        return v;
    }

    return eval_primary(ctx);
}

static long long eval_expr(ppContext* ctx, int min_prec) {
    long long lhs = eval_unary(ctx);
    while (true) {
        ppToken* t = pp_peek(ctx);
        if (is_eof(t)) break;
        int prec = op_prec(t);
        if (prec == 0 || prec < min_prec) break;
        pp_get(ctx);

        // short-circuit evaluation for logical AND and OR
        if (t->value == SYMBOL_LOGICAL_AND && lhs == 0) {
            skip_expr(ctx, prec + 1);
            lhs = 0;
            continue;
        }
        if (t->value == SYMBOL_LOGICAL_OR && lhs != 0) {
            skip_expr(ctx, prec + 1);
            lhs = 1;
            continue;
        }
        lhs = apply_binop(t, lhs, eval_expr(ctx, prec + 1));
    }
    return lhs;
}

static long long eval_conditional(ppContext* ctx) {
    long long cond = eval_expr(ctx, 0);
    ppToken* t = pp_peek(ctx);
    if (is_eof(t)) return cond;
    if (t->type != PP_SYMBOL || t->value != SYMBOL_QUESTION) return cond;
    pp_get(ctx);  // consume '?'

    if (cond) {
        long long then_val = eval_conditional(ctx);
        if (!expect_token(ctx, "Expected : in #if expression", t->line, t->column, PP_SYMBOL, SYMBOL_COLON))
            return then_val;
        skip_conditional(ctx);
        return then_val;
    } else {
        skip_conditional(ctx);
        if (!expect_token(ctx, "Expected : in #if expression", t->line, t->column, PP_SYMBOL, SYMBOL_COLON))
            return 0;
        return eval_conditional(ctx);
    }
}

static void handle_define(ppContext* ctx) {
    ppToken* name = pp_peek(ctx);
    if (is_eof(name) || name->type != PP_IDENTIFIER) {
        preprocessor_error("Expected macro name after #define", name == NULL ? 0 : name->line, name == NULL ? 0 : name->column);
        return;
    }
    pp_get(ctx);  // consume macro name

    ppMacro* macro = NULL;
    ppToken* t = pp_peek(ctx);
    if (!is_eof(t) && t->type == PP_SYMBOL && t->value == SYMBOL_L_PARENTHESIS && t->line == name->line && t->column == name->column + strlen(name->value)) {
        macro = create_pp_macro(name->value, true);
        pp_get(ctx);  // consume '('

        t = pp_peek(ctx);
        while (t->type != PP_SYMBOL || t->value != SYMBOL_R_PARENTHESIS) {
            if (is_eof(t)) {
                preprocessor_error("Expected parameter or ) in macro definition", t == NULL ? 0 : t->line, t == NULL ? 0 : t->column);
                return;
            }
            if (t->type == PP_SYMBOL && t->value == SYMBOL_ELLIPSIS) {
                pp_get(ctx);  // consume '...'
                macro->is_variadic = true;
                t = pp_peek(ctx);
                if (t->type != PP_SYMBOL || t->value != SYMBOL_R_PARENTHESIS) {
                    preprocessor_error("Expected ) after ... in macro definition", t->line, t->column);
                    return;
                }
                break;
            }
            if (t->type != PP_IDENTIFIER) {
                preprocessor_error("Expected parameter name in macro definition", t->line, t->column);
                return;
            }
            foreach (string, p, macro->params) {
                if (p == t->value) {
                    preprocessor_error("Duplicate macro parameter name", t->line, t->column);
                    return;
                }
            }
            pp_get(ctx);  // consume parameter name
            append(macro->params, t->value);

            t = pp_peek(ctx);
            if (t->type == PP_SYMBOL && t->value == SYMBOL_COMMA) {
                pp_get(ctx);  // consume ','
                t = pp_peek(ctx);
                if (t->type == PP_SYMBOL && t->value == SYMBOL_R_PARENTHESIS) {
                    preprocessor_error("Expected parameter name after , in macro definition", t->line, t->column);
                    return;
                }
            } else if (t->type != PP_SYMBOL || t->value != SYMBOL_R_PARENTHESIS) {
                preprocessor_error("Expected , or ) in macro definition", t->line, t->column);
                return;
            }
            t = pp_peek(ctx);
        }
        pp_get(ctx);  // consume ')'
    } else
        macro = create_pp_macro(name->value, false);

    while (true) {
        t = pp_peek(ctx);
        if (is_eof(t) || t->type == PP_NEWLINE)
            break;
        pp_get(ctx);  // consume token
        append(macro->body, t);
    }

    foreach (ppMacro*, m, ctx->macros) {
        if (m->name == macro->name) {
            preprocessor_warn("Macro redefined", name->line, name->column);
            // TODO: compare old and new definition for full equality
            m->params = macro->params;
            m->is_variadic = macro->is_variadic;
            m->body = macro->body;
            return;
        }
    }
    append(ctx->macros, macro);
}

static void handle_directive(ppContext* ctx) {
    ppToken* directive = pp_peek(ctx);
    if (is_eof(directive) || directive->type != PP_IDENTIFIER) {
        if (!is_eof(directive) && directive->type == PP_NEWLINE) {
            pp_get(ctx);  // consume newline
            return;
        }
        preprocessor_error("Expected directive after #", directive == NULL ? 0 : directive->line, directive == NULL ? 0 : directive->column);
        return;
    }
    pp_get(ctx);  // consume directive token

    bool is_cond = directive->value == P_IF || directive->value == P_IFDEF || directive->value == P_IFNDEF || directive->value == P_ELIF || directive->value == P_ELSE || directive->value == P_ENDIF;
    if (!is_cond && !cond_active(ctx))
        return;

    if (directive->value == P_DEFINE) {
        handle_define(ctx);
    } else if (directive->value == P_UNDEF) {
        ppToken* name = pp_peek(ctx);
        if (is_eof(name) || name->type != PP_IDENTIFIER) {
            preprocessor_error("Expected macro name after #undef", directive->line, directive->column);
            return;
        }
        pp_get(ctx);

        if (!list_empty(ctx->macros)) {
            ListNode* prev = NULL;
            foreach (ppMacro*, macro, ctx->macros) {
                if (macro->name == name->value) {
                    if (prev == NULL)
                        ctx->macros->head = macro__n->next;
                    else
                        prev->next = macro__n->next;
                    if (macro__n == ctx->macros->tail)
                        ctx->macros->tail = prev;
                    return;
                }
                prev = macro__n;
            }
        }
    } else if (directive->value == P_IF || directive->value == P_IFDEF || directive->value == P_IFNDEF) {
        bool outer_active = cond_active(ctx);
        bool inner_active = false;
        if (outer_active) {
            if (directive->value == P_IF) {
                inner_active = eval_conditional(ctx) != 0;
            } else {
                ppToken* name = pp_peek(ctx);
                if (is_eof(name) || name->type != PP_IDENTIFIER) {
                    preprocessor_error("Expected identifier after #if[n]def", directive->line, directive->column);
                    return;
                }
                pp_get(ctx);
                inner_active = (directive->value == P_IFDEF) == (find_macro(ctx, name->value) != NULL);
            }
        }
        ppCondFrame* frame = create_pp_cond_frame(directive);
        frame->active = outer_active && inner_active;
        frame->taken = !outer_active || inner_active;
        append(ctx->cond_stack, frame);
    } else if (directive->value == P_ELIF) {
        if (list_empty(ctx->cond_stack)) {
            preprocessor_error("#elif without #if", directive->line, directive->column);
            return;
        }
        ppCondFrame* frame = (ppCondFrame*)ctx->cond_stack->tail->data;
        if (frame->in_else) {
            preprocessor_error("#elif after #else", directive->line, directive->column);
            return;
        }
        if (frame->taken) {
            frame->active = false;
        } else {
            bool cond = eval_conditional(ctx) != 0;
            frame->active = cond;
            frame->taken = frame->taken || cond;
        }
    } else if (directive->value == P_ELSE) {
        if (list_empty(ctx->cond_stack)) {
            preprocessor_error("#else without #if", directive->line, directive->column);
            return;
        }
        ppCondFrame* frame = (ppCondFrame*)ctx->cond_stack->tail->data;
        if (frame->in_else) {
            preprocessor_error("#else after #else", directive->line, directive->column);
            return;
        }
        frame->in_else = true;
        frame->active = !frame->taken;
        frame->taken = true;
    } else if (directive->value == P_ENDIF) {
        if (list_empty(ctx->cond_stack)) {
            preprocessor_error("#endif without #if", directive->line, directive->column);
            return;
        }
        if (ctx->cond_stack->head == ctx->cond_stack->tail) {
            ctx->cond_stack->head = NULL;
            ctx->cond_stack->tail = NULL;
        } else {
            ListNode* n = ctx->cond_stack->head;
            while (n->next != ctx->cond_stack->tail)
                n = n->next;
            n->next = NULL;
            ctx->cond_stack->tail = n;
        }
    } else if (directive->value == P_INCLUDE) {
        // TODO: include file handle
    } else if (directive->value == P_LINE) {
        // skip, not currently supported
        return;
    } else if (directive->value == P_ERROR) {
        string msg = "Encountered #error directive";
        ListNode* n = ctx->current;
        bool first = true;
        while (n != NULL) {
            ppToken* t = (ppToken*)n->data;
            if (t == NULL || t->type == PP_NEWLINE || t->type == PP_EOF) break;
            msg = string_splice((first ? "%s: %s" : "%s %s"), msg, t->value);
            first = false;
            n = n->next;
        }
        preprocessor_error(msg, directive->line, directive->column);
        return;
    } else if (directive->value == P_PRAGMA) {
        // skip, not currently supported
        return;
    } else {
        preprocessor_error("Unknown preprocessor directive", directive->line, directive->column);
        return;
    }
}

list(ppToken*) preprocess(string filename, string source_code, bool* error_flag) {
    has_error = false;
    ppLexer* lexer = create_pp_lexer(filename, source_code);
    if (lexer == NULL) {
        *error_flag = true;
        return NULL;
    }
    pp_lexer(lexer);

    ppContext* ctx = create_pp_context(lexer);
    ctx->current = lexer->pp_tokens->head;

    bool at_line_start = true;
    while (true) {
        ppToken* token = pp_peek(ctx);
        if (is_eof(token)) break;

        if (at_line_start && token->type == PP_SYMBOL && token->value == SYMBOL_HASH) {
            pp_get(ctx);  // consume '#'
            handle_directive(ctx);
            skip_to_newline(ctx);
            at_line_start = true;
        } else {
            token = pp_get(ctx);
            at_line_start = (token->type == PP_NEWLINE);
            if (!cond_active(ctx))
                continue;
            if (token->type == PP_OTHER)
                preprocessor_error(string_splice("Unexpected token: %s", token->value == NULL ? "(null)" : token->value), token->line, token->column);
            if (token->type == PP_IDENTIFIER && expand_macro(ctx, token))
                continue;
            append(ctx->output, token);
        }
    }
    if (!list_empty(ctx->cond_stack)) {
        size_t line = 0, column = 0;
        ppCondFrame* frame = peek_back(ctx->cond_stack, ppCondFrame*);
        if (frame != NULL && frame->directive != NULL) {
            line = frame->directive->line;
            column = frame->directive->column;
        }
        preprocessor_error("Unterminated conditional directive", line, column);
    }
    *error_flag = has_error;
    return ctx->output;
}

// TODO: macro recursion check
// TODO: __FILE__, __LINE__, __DATE__, __TIME__, ...
