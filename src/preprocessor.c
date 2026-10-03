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
#define pp_lexer_error(message, pos) fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", lexer->filename, line(lexer, pos), column(lexer, pos), message)
#define preprocessor_error(message, line, column) fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", ctx->lexer->filename, line, column, message)
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

#ifdef DEBUG_PP_LEXER
ppLexer* create_pp_lexer(string filename, string source_code) {
#else
static ppLexer* create_pp_lexer(string filename, string source_code) {
#endif
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

#ifdef DEBUG_PP_LEXER
void pp_lexer(ppLexer* lexer) {
#else
static void pp_lexer(ppLexer* lexer) {
#endif
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

static ppCondFrame* create_pp_cond_frame(void) {
    ppCondFrame* frame = create_struct(ppCondFrame);
    frame->active = false;
    frame->taken = false;
    frame->in_else = false;
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
    while (ctx->current != NULL) {
        if (ctx->current->data == NULL) return;
        ppToken* t = (ppToken*)ctx->current->data;
        if (t->type == PP_NEWLINE || t->type == PP_EOF) return;
        ctx->current = ctx->current->next;
    }
}
static ppMacro* find_macro(ppContext* ctx, string name) {
    foreach (ppMacro*, macro, ctx->macros) {
        if (macro->name == name) return macro;
    }
    return NULL;
}
static ppCondFrame* current_cond_frame(ppContext* ctx) {
    if (list_empty(ctx->cond_stack))
        return NULL;
    return (ppCondFrame*)ctx->cond_stack->tail->data;
}
static bool cond_active(ppContext* ctx) {
    ppCondFrame* top = current_cond_frame(ctx);
    if (top == NULL)
        return true;
    return top->active;
}

static string P_DEFINED = NULL;
static string P_DEFINE = NULL;
static string P_UNDEF = NULL;
static string P_IF = NULL;
static string P_IFDEF = NULL;
static string P_IFNDEF = NULL;
static string P_ELIF = NULL;
static string P_ELSE = NULL;
static string P_ENDIF = NULL;
static string P_INCLUDE = NULL;
static string P_LINE = NULL;
static string P_ERROR = NULL;
static string P_PRAGMA = NULL;

// ===========================
// 回傳 0 = 不是二元運算子
// 回傳 0 = 不是二元運算子
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
    string v = op->value;
    if (v == SYMBOL_LOGICAL_OR) return (lhs || rhs) ? 1 : 0;
    if (v == SYMBOL_LOGICAL_AND) return (lhs && rhs) ? 1 : 0;
    if (v == SYMBOL_BITWISE_OR) return lhs | rhs;
    if (v == SYMBOL_XOR) return lhs ^ rhs;
    if (v == SYMBOL_BITWISE_AND) return lhs & rhs;
    if (v == SYMBOL_EQ) return lhs == rhs;
    if (v == SYMBOL_NE) return lhs != rhs;
    if (v == SYMBOL_LT) return lhs < rhs;
    if (v == SYMBOL_GT) return lhs > rhs;
    if (v == SYMBOL_LE) return lhs <= rhs;
    if (v == SYMBOL_GE) return lhs >= rhs;
    if (v == SYMBOL_L_SHIFT) return lhs << rhs;
    if (v == SYMBOL_R_SHIFT) return lhs >> rhs;
    if (v == SYMBOL_ADD) return lhs + rhs;
    if (v == SYMBOL_SUB) return lhs - rhs;
    if (v == SYMBOL_MUL) return lhs * rhs;
    if (v == SYMBOL_DIV) return rhs == 0 ? 0 : lhs / rhs;
    if (v == SYMBOL_MOD) return rhs == 0 ? 0 : lhs % rhs;
    return 0;
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
    if (is_unsigned) {
        unsigned long long v = strtoull(p, NULL, base);
        return (long long)v;
    }
    return strtoll(p, NULL, base);
}

static long long eval_expr(ppContext* ctx, int min_prec);

// TODO: 查表 → 把 body 插到 ctx->current 之前 → 遞迴 eval_expr
static long long expand_macro(ppContext* ctx, ppToken* name) {
    return 0;
}

static long long eval_primary(ppContext* ctx) {
    if (ctx->current == NULL || ctx->current->data == NULL) {
        abort();
    }
    ppToken* t = (ppToken*)ctx->current->data;
    if (t->type == PP_NEWLINE || t->type == PP_EOF) {
        preprocessor_error("Unexpected end of #if expression", t->line, t->column);
        return 0;
    }
    if (t->type == PP_NUMBER) {
        ctx->current = ctx->current->next;
        return parse_int_literal(t->value);
    }
    if (t->type == PP_SYMBOL && t->value == SYMBOL_L_PARENTHESIS) {
        ctx->current = ctx->current->next;
        long long v = eval_expr(ctx, 0);
        if (ctx->current == NULL || ctx->current->data == NULL) {
            preprocessor_error("Expected ) in #if expression", t->line, t->column);
            return v;
        }
        ppToken* r = (ppToken*)ctx->current->data;
        if (r->type != PP_SYMBOL || r->value != SYMBOL_R_PARENTHESIS) {
            preprocessor_error("Expected ) in #if expression", t->line, t->column);
            return v;
        }
        ctx->current = ctx->current->next;
        return v;
    }
    if (t->type == PP_IDENTIFIER) {
        ctx->current = ctx->current->next;
        return expand_macro(ctx, t);
    }
    preprocessor_error("Unexpected token in #if expression", t->line, t->column);
    ctx->current = ctx->current->next;
    return 0;
}

static long long eval_unary(ppContext* ctx) {
    if (ctx->current == NULL || ctx->current->data == NULL) {
        abort();
    }
    ppToken* t = (ppToken*)ctx->current->data;

    if (t->type == PP_IDENTIFIER && t->value == P_DEFINED) {
        ctx->current = ctx->current->next;
        if (ctx->current == NULL || ctx->current->data == NULL) {
            preprocessor_error("Expected identifier after defined", t->line, t->column);
            return 0;
        }
        ppToken* nt = (ppToken*)ctx->current->data;
        if (nt->type == PP_SYMBOL && nt->value == SYMBOL_L_PARENTHESIS) {
            ctx->current = ctx->current->next;
            if (ctx->current == NULL || ctx->current->data == NULL) {
                preprocessor_error("Expected identifier in defined(...)", t->line, t->column);
                return 0;
            }
            ppToken* name = (ppToken*)ctx->current->data;
            if (name->type != PP_IDENTIFIER) {
                preprocessor_error("Expected identifier in defined(...)", t->line, t->column);
                return 0;
            }
            ctx->current = ctx->current->next;
            if (ctx->current == NULL || ctx->current->data == NULL) {
                preprocessor_error("Expected ) in defined(...)", t->line, t->column);
                return 0;
            }
            ppToken* r = (ppToken*)ctx->current->data;
            if (r->type != PP_SYMBOL || r->value != SYMBOL_R_PARENTHESIS) {
                preprocessor_error("Expected ) in defined(...)", t->line, t->column);
                return 0;
            }
            ctx->current = ctx->current->next;
            return find_macro(ctx, name->value) != NULL ? 1 : 0;
        }
        if (nt->type == PP_IDENTIFIER) {
            ctx->current = ctx->current->next;
            return find_macro(ctx, nt->value) != NULL ? 1 : 0;
        }
        preprocessor_error("Expected identifier after defined", t->line, t->column);
        return 0;
    }

    if (t->type == PP_SYMBOL && (t->value == SYMBOL_ADD || t->value == SYMBOL_SUB || t->value == SYMBOL_LOGICAL_NOT || t->value == SYMBOL_BITWISE_NOT)) {
        ctx->current = ctx->current->next;
        long long v = eval_unary(ctx);
        if (t->value == SYMBOL_ADD) return v;
        if (t->value == SYMBOL_SUB) return -v;
        if (t->value == SYMBOL_BITWISE_NOT) return ~v;
        return v == 0 ? 1 : 0;
    }

    return eval_primary(ctx);
}

static long long eval_expr(ppContext* ctx, int min_prec) {
    long long lhs = eval_unary(ctx);
    while (ctx->current != NULL && ctx->current->data != NULL) {
        ppToken* t = (ppToken*)ctx->current->data;
        int prec = op_prec(t);
        if (prec == 0 || prec < min_prec) break;
        ctx->current = ctx->current->next;
        lhs = apply_binop(t, lhs, eval_expr(ctx, prec + 1));
    }
    return lhs;
}

static bool evaluate_pp_expression(ppContext* ctx) {
    long long v = eval_expr(ctx, 0);
    skip_to_newline(ctx);
    return v != 0;
}
// ===========================

static void handle_directive(ppContext* ctx) {
    ctx->current = ctx->current->next;  // '#' -> directive
    if (ctx->current == NULL || ctx->current->data == NULL) {
        preprocessor_error("Expected identifier after #", ((ppToken*)ctx->current->data)->line, ((ppToken*)ctx->current->data)->column);
        return;
    }
    ppToken* directive = (ppToken*)ctx->current->data;
    if (directive->type != PP_IDENTIFIER) {
        preprocessor_error(string_splice("Expected identifier after #, got %s", directive->value), directive->line, directive->column);
        return;
    }
    ctx->current = ctx->current->next;  // directive -> next token

    if (directive->value == P_DEFINE) {
        // TODO: handle_define
    } else if (directive->value == P_UNDEF) {
        if (ctx->current == NULL || ctx->current->data == NULL) {
            preprocessor_error("Expected macro name after #undef", directive->line, directive->column);
            return;
        } else if (list_empty(ctx->macros)) {
            // skip
        } else {
            ppToken* name = (ppToken*)ctx->current->data;
            if (name->type != PP_IDENTIFIER) {
                preprocessor_error("Expected macro name after #undef", name->line, name->column);
                return;
            }
            ctx->current = ctx->current->next;  // name -> next token
            ListNode* prev = NULL;
            foreach (ppMacro*, macro, ctx->macros) {
                if (macro->name == name->value) {
                    if (prev == NULL)
                        ctx->macros->head = macro__n->next;
                    else
                        prev->next = macro__n->next;
                    if (macro__n == ctx->macros->tail)
                        ctx->macros->tail = prev;
                    goto skip_foreach_in_undef;
                }
                prev = macro__n;
            }
        }
    skip_foreach_in_undef:
        if (ctx->current == NULL || ctx->current->data == NULL) {
            preprocessor_error("Expected newline after #undef", directive->line, directive->column);
            return;
        }
        ppToken* t = (ppToken*)ctx->current->data;
        if (t->type != PP_NEWLINE && t->type != PP_EOF)
            preprocessor_error("Expected newline after #undef", t->line, t->column);
    } else if (directive->value == P_IF || directive->value == P_IFDEF || directive->value == P_IFNDEF) {
        bool outer_active = cond_active(ctx);
        bool inner_active = false;
        if (outer_active) {
            if (directive->value == P_IF) {
                inner_active = evaluate_pp_expression(ctx);
            } else {
                if (ctx->current == NULL || ctx->current->data == NULL) {
                    preprocessor_error("Expected identifier after #if[n]def", directive->line, directive->column);
                    return;
                }
                ppToken* t = (ppToken*)ctx->current->data;
                if (t->type != PP_IDENTIFIER) {
                    preprocessor_error("Expected identifier after #if[n]def", t->line, t->column);
                    return;
                }
                inner_active = (directive->value == P_IFDEF) == (find_macro(ctx, t->value) != NULL);
                ctx->current = ctx->current->next;  // name -> newline
                if (ctx->current == NULL || ctx->current->data == NULL) {
                    preprocessor_error("Expected newline after #if[n]def", directive->line, directive->column);
                    return;
                }
                t = (ppToken*)ctx->current->data;
                if (t->type != PP_NEWLINE && t->type != PP_EOF) {
                    preprocessor_error("Expected newline after #if[n]def", t->line, t->column);
                    return;
                }
            }
        }
        ppCondFrame* frame = create_pp_cond_frame();
        frame->active = outer_active && inner_active;
        frame->taken = !outer_active || inner_active;
        append(ctx->cond_stack, frame);
    } else if (directive->value == P_ELIF) {
        // TODO
    } else if (directive->value == P_ELSE) {
        // TODO
    } else if (directive->value == P_ENDIF) {
        // TODO
    } else if (directive->value == P_INCLUDE) {
        // TODO
    } else if (directive->value == P_LINE) {
        // skip, not currently supported
        return;
    } else if (directive->value == P_ERROR) {
        string msg = "Encountered #error directive";
        ListNode* n = ctx->current->next;
        bool first = true;
        while (n != NULL) {
            ppToken* t = (ppToken*)n->data;
            if (t->type == PP_NEWLINE || t->type == PP_EOF) break;
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
    return;
}

string preprocess(string filename, string source_code) {
    P_DEFINE = create_string("define", 6);
    P_DEFINED = create_string("defined", 7);
    P_UNDEF = create_string("undef", 5);
    P_IF = create_string("if", 2);
    P_IFDEF = create_string("ifdef", 5);
    P_IFNDEF = create_string("ifndef", 6);
    P_ELIF = create_string("elif", 4);
    P_ELSE = create_string("else", 4);
    P_ENDIF = create_string("endif", 5);
    P_INCLUDE = create_string("include", 7);
    P_LINE = create_string("line", 4);
    P_ERROR = create_string("error", 5);
    P_PRAGMA = create_string("pragma", 6);
    ppLexer* lexer = create_pp_lexer(filename, source_code);
    pp_lexer(lexer);

    ppContext* ctx = create_pp_context(lexer);
    ListNode* prev = NULL;
    ctx->current = lexer->pp_tokens->head;

    while (ctx->current != NULL) {
        ppToken* token = (ppToken*)ctx->current->data;
        if (token->type == PP_EOF)
            break;
        bool at_line_start = (prev == NULL) || ((ppToken*)prev->data)->type == PP_NEWLINE;
        if (at_line_start && token->type == PP_SYMBOL && token->value == SYMBOL_HASH) {
            handle_directive(ctx);
            skip_to_newline(ctx);
        } else {
            // TODO: expand / output
        }
        prev = ctx->current;
        ctx->current = ctx->current->next;
    }

    return NULL;  // placeholder
}
