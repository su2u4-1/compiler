#include "preprocessor.h"

#include "lib.h"

#define preprocessor_error(message, line, column) fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = true, ctx->lexer->filename), line, column, message)
#define preprocessor_warn(message, line, column) fprintf(stderr, "[Preprocess Warning] at %s:%zu:%zu: %s\n", ctx->lexer->filename, line, column, message)
#define is_eof(t) ((t) == NULL || (t)->type == PP_EOF)

static bool has_error = false;

static ppCondFrame* create_pp_cond_frame(ppToken* directive) {
    ppCondFrame* frame = create_struct(ppCondFrame);
    frame->active = false;
    frame->taken = false;
    frame->in_else = false;
    frame->directive = directive;
    return frame;
}
static ppMacro* create_pp_macro(ppToken* name, bool is_function) {
    ppMacro* macro = create_struct(ppMacro);
    macro->name = name;
    macro->params = NULL;
    if (is_function)
        macro->params = create_list(ppToken*);
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
    context->in_directive = false;
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
        if (macro->name->value == name)
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

static list(list(ppToken*)) handle_macro_args(ppContext* ctx, ppMacro* macro, ppToken* name) {
    size_t expected = 0;
    foreach (ppToken*, param, macro->params)
        expected++;
    size_t count = 0;
    list(list(ppToken*)) args = create_list(list(ppToken*));
    list(ppToken*) cur = create_list(ppToken*);

    int depth = 0;
    bool space = false;
    while (true) {
        ppToken* t = pp_peek(ctx);
        if (is_eof(t)) {
            preprocessor_error("Unterminated macro arguments", name->line, name->column);
            return NULL;
        } else if (t->type == PP_NEWLINE) {
            if (ctx->in_directive) {
                preprocessor_error("Unterminated macro arguments", t->line, t->column);
                return NULL;
            }
            space = true;
            pp_get(ctx);
            continue;
        } else if (t->type == PP_SYMBOL && t->value == SYMBOL_L_PARENTHESIS) {
            depth++;
        } else if (t->type == PP_SYMBOL && t->value == SYMBOL_R_PARENTHESIS) {
            if (depth == 0)
                break;
            depth--;
        } else if (t->type == PP_SYMBOL && t->value == SYMBOL_COMMA && depth == 0) {
            if (!(macro->is_variadic && count >= expected)) {
                count++;
                append(args, cur);
                cur = create_list(ppToken*);
                pp_get(ctx);
                continue;
            }
        }
        pp_get(ctx);
        if (space) {
            ppToken* new = create_struct(ppToken);
            memcpy(new, t, sizeof(ppToken));
            new->space_before = true;
            append(cur, new);
            space = false;
        } else
            append(cur, t);
    }
    if (expected == 0 && list_empty(cur) && list_empty(args) && !macro->is_variadic)
        return args;  // empty list
    count++;
    append(args, cur);
    if ((!macro->is_variadic && count != expected) || (macro->is_variadic && count < expected)) {
        preprocessor_error("Incorrect number of macro arguments", name->line, name->column);
        return NULL;
    }
    if (macro->is_variadic && count == expected)
        append(args, create_list(ppToken*));
    return args;
}

static int find_arg_index(list(ppToken*) params, ppToken* param, size_t expected) {
    if (param == NULL || param->type != PP_IDENTIFIER)
        return -1;
    int index = 0;
    foreach (ppToken*, p, params) {
        if (p->value == param->value)
            return index;
        index++;
    }
    if (param->value == P_VA_ARGS_ && expected > 0)
        return (int)expected - 1;
    return -1;
}

static string stringize_tokens(list(ppToken*) tokens) {
    bool first = true;
    size_t len = 2;
    foreach (ppToken*, t, tokens) {
        len += strlen(t->value) + ((t->space_before && !first) ? 1 : 0);
        if (t->type == PP_STRING || t->type == PP_CHAR) {
            for (size_t i = 0; i < strlen(t->value); i++) {
                char c = t->value[i];
                if (c == '"' || c == '\\')
                    len++;
            }
        }
        first = false;
    }
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        fprintf(stderr, "[preprocessor Fatal] at <stringize_tokens>: Cannot allocate memory\n");
        abort();
    }
    result[0] = '"';
    size_t pos = 1;
    first = true;
    foreach (ppToken*, t, tokens) {
        if (t->space_before && !first)
            result[pos++] = ' ';
        first = false;
        for (size_t i = 0; i < strlen(t->value); i++) {
            char c = t->value[i];
            if ((t->type == PP_STRING || t->type == PP_CHAR) && (c == '"' || c == '\\'))
                result[pos++] = '\\';
            result[pos++] = c;
        }
    }
    result[pos++] = '"';
    result[pos] = '\0';
    string str = create_string(result, pos);
    free(result);
    return str;
}

static ppToken* create_pp_token_in_macro(ppTokenType type, string value, ppToken* name, bool space_before, list(string) hideset) {
    ppToken* new_token = create_struct(ppToken);
    new_token->type = type;
    new_token->value = value;
    new_token->line = name->line;
    new_token->column = name->column;
    new_token->filename = name->filename;
    new_token->space_before = space_before;
    new_token->at_line_start = false;
    new_token->hideset = hideset;
    new_token->expanded_from = name;
    while (new_token->expanded_from->expanded_from != NULL)
        new_token->expanded_from = new_token->expanded_from->expanded_from;
    return new_token;
}

static bool expand_macro(ppContext* ctx, ppToken* name);

static list(ppToken*) expand_tokens(ppContext* ctx, list(ppToken*) tokens) {
    ppContext* sub_ctx = create_pp_context(ctx->lexer);
    sub_ctx->macros = ctx->macros;
    sub_ctx->in_directive = ctx->in_directive;
    sub_ctx->current = tokens->head;
    while (true) {
        ppToken* t = pp_peek(sub_ctx);
        if (is_eof(t)) break;
        pp_get(sub_ctx);
        if (t->type == PP_IDENTIFIER && expand_macro(sub_ctx, t))
            continue;
        append(sub_ctx->output, t);
    }
    return sub_ctx->output;
}

static bool hideset_contains(list(string) hideset, string name) {
    foreach (string, s, hideset)
        if (s == name)
            return true;
    return false;
}

static list(string) hideset_union(list(string) a, list(string) b) {
    if (a == NULL) return b;
    if (b == NULL) return a;
    list(string) result = create_list(string);
    foreach (string, s, a)
        append(result, s);
    foreach (string, t, b)
        if (!hideset_contains(a, t))
            append(result, t);
    return result;
}

static list(string) hideset_append(list(string) hideset, string name) {
    if (hideset_contains(hideset, name))
        return hideset;
    list(string) new_hideset = create_list(string);
    foreach (string, s, hideset)
        append(new_hideset, s);
    append(new_hideset, name);
    return new_hideset;
}

static list(string) hideset_intersect(list(string) a, list(string) b, string name) {
    list(string) result = create_list(string);
    foreach (string, s, a)
        foreach (string, t, b)
            if (s == t)
                append(result, s);
    if (name != NULL && !hideset_contains(result, name))
        append(result, name);
    return result;
}

static ppToken* paste_two_tokens(ppContext* ctx, ppToken* lhs, ppToken* rhs, ppToken* name) {
    string str = string_splice("%s%s", lhs->value, rhs->value);
    ppLexer* lexer = create_pp_lexer(name->filename, str);
    if (lexer == NULL) {
        fprintf(stderr, "[preprocessor Fatal] at <paste_two_tokens>: Cannot create lexer for token pasting\n");
        abort();
    }
    bool lex_error = pp_lexer(lexer);

    ppToken* pasted = NULL;
    size_t count = 0;
    foreach (ppToken*, token, lexer->pp_tokens) {
        if (token->type == PP_EOF || token->type == PP_NEWLINE)
            continue;
        if (count++ == 0)
            pasted = token;
    }
    if (lex_error || count != 1) {
        preprocessor_error(string_splice("Pasting \"%s\" and \"%s\" does not give a valid preprocessing token", lhs->value, rhs->value), name->line, name->column);
        return NULL;
    }
    return create_pp_token_in_macro(pasted->type, pasted->value, name, lhs->space_before, hideset_intersect(lhs->hideset, rhs->hideset, NULL));
}

static list(ppToken*) paste_macro_body(ppContext* ctx, ppMacro* macro, list(list(ppToken*)) args, ppToken* name, list(string) hideset) {
    if (macro == NULL || name == NULL)
        return NULL;
    if (list_empty(macro->body))
        return create_list(ppToken*);  // empty list

    size_t expected = 0;
    if (macro->params != NULL) {
        assert(args != NULL);
        foreach (ppToken*, param, macro->params) expected++;
        if (macro->is_variadic) expected++;
    }
    list(ppToken*)* expanded = NULL;
    list(ppToken*)* arg_arr = NULL;
    if (expected > 0) {
        expanded = calloc(expected, sizeof(list(ppToken*)));
        arg_arr = calloc(expected, sizeof(list(ppToken*)));
        if (expanded == NULL || arg_arr == NULL) {
            fprintf(stderr, "[preprocessor Fatal] at <paste_macro_body>: Cannot allocate memory\n");
            abort();
        }
    }
    size_t i = 0;
    foreach (list(ppToken*), arg, args)
        arg_arr[i++] = arg;

    list(ppToken*) result = create_list(ppToken*);
    ListNode* node = macro->body->head;
    while (node != NULL) {
        ppToken* t = (ppToken*)node->data;
        assert(t != NULL);
        if (t->type == PP_SYMBOL && t->value == SYMBOL_HASH && expected > 0) {
            bool space_before = t->space_before;
            node = node->next;
            assert(node != NULL);
            t = (ppToken*)node->data;
            int index = find_arg_index(macro->params, t, expected);
            if (index == -1) {
                preprocessor_error("Invalid parameter after # in macro body", t->line, t->column);
                free(expanded);
                free(arg_arr);
                return NULL;
            }
            string str = stringize_tokens(arg_arr[index]);
            ppToken* new = create_pp_token_in_macro(PP_STRING, str, name, space_before, NULL);
            append(result, new);
        } else if (t->type == PP_SYMBOL && t->value == SYMBOL_DOUBLE_HASH) {
            ppToken* next = NULL;
            if (node->next != NULL && node->next->data != NULL)
                next = (ppToken*)node->next->data;
            if (!is_eof(next) && next->type != PP_NEWLINE) {
                list(ppToken*) rhs = NULL;
                int index = find_arg_index(macro->params, next, expected);
                int rhs_stringize = -1;
                if (macro->params != NULL && next->type == PP_SYMBOL && next->value == SYMBOL_HASH && node->next->next != NULL)
                    rhs_stringize = find_arg_index(macro->params, (ppToken*)node->next->next->data, expected);
                if (rhs_stringize != -1) {
                    rhs = create_list(ppToken*);
                    append(rhs, create_pp_token_in_macro(PP_STRING, stringize_tokens(arg_arr[rhs_stringize]), name, next->space_before, NULL));
                    node = node->next;
                } else if (index != -1) {
                    rhs = arg_arr[index];
                } else {
                    rhs = create_list(ppToken*);
                    append(rhs, next);
                }
                node = node->next;

                ppToken* lhs = pop_back(result, ppToken*);
                assert(lhs != NULL);

                ListNode* r = (rhs == NULL) ? NULL : rhs->head;
                if (r == NULL) {
                    append(result, lhs);
                } else if (lhs->type == PP_PLACE_MARKER) {
                    bool first = true;
                    for (; r != NULL; r = r->next) {
                        ppToken* a = (ppToken*)r->data;
                        append(result, create_pp_token_in_macro(a->type, a->value, name, (first ? lhs : a)->space_before, a->hideset));
                        first = false;
                    }
                } else {
                    ppToken* first_rhs = (ppToken*)r->data;
                    ppToken* pasted = paste_two_tokens(ctx, lhs, first_rhs, name);
                    if (pasted != NULL) {
                        append(result, pasted);
                    } else {
                        append(result, lhs);
                        append(result, create_pp_token_in_macro(first_rhs->type, first_rhs->value, name, first_rhs->space_before, first_rhs->hideset));
                    }
                    for (r = r->next; r != NULL; r = r->next) {
                        ppToken* a = (ppToken*)r->data;
                        append(result, create_pp_token_in_macro(a->type, a->value, name, a->space_before, a->hideset));
                    }
                }
            }
        } else {
            int index = find_arg_index(macro->params, t, expected);
            if (index == -1) {
                append(result, create_pp_token_in_macro(t->type, t->value, name, t->space_before, t->hideset));
            } else {
                ppToken* next = NULL;
                if (node->next != NULL && node->next->data != NULL)
                    next = (ppToken*)node->next->data;
                if (next != NULL && next->type == PP_SYMBOL && next->value == SYMBOL_DOUBLE_HASH) {
                    if (list_empty(arg_arr[index]))
                        append(result, create_pp_token_in_macro(PP_PLACE_MARKER, NULL, name, t->space_before, NULL));
                    else {
                        bool first = true;
                        foreach (ppToken*, arg_t, arg_arr[index]) {
                            append(result, create_pp_token_in_macro(arg_t->type, arg_t->value, name, (first ? t : arg_t)->space_before, arg_t->hideset));
                            first = false;
                        }
                    }
                } else {
                    if (expanded[index] == NULL)
                        expanded[index] = expand_tokens(ctx, arg_arr[index]);
                    bool first = true;
                    foreach (ppToken*, arg_t, expanded[index]) {
                        append(result, create_pp_token_in_macro(arg_t->type, arg_t->value, name, (first ? t : arg_t)->space_before, arg_t->hideset));
                        first = false;
                    }
                }
            }
        }
        node = node->next;
    }

    free(expanded);
    free(arg_arr);

    ListNode* prev = NULL;
    bool first = true;
    foreach (ppToken*, t, result) {
        if (t->type == PP_PLACE_MARKER) {
            if (prev == NULL)
                result->head = t__n->next;
            else
                prev->next = t__n->next;
            if (t__n == result->tail)
                result->tail = prev;
        } else {
            t->hideset = hideset_union(t->hideset, hideset);
            if (first) {
                t->space_before = name->space_before;
                first = false;
            }
            prev = t__n;
        }
    }
    return result;
}

static bool expand_macro(ppContext* ctx, ppToken* name) {
    if (name->type != PP_IDENTIFIER)
        return false;
    ppMacro* macro = find_macro(ctx, name->value);
    if (macro == NULL)
        return false;
    if (hideset_contains(name->hideset, name->value))
        return false;

    ListNode* saved = ctx->current;
    list(string) hideset = NULL;
    list(list(ppToken*)) args = NULL;

    if (macro->params == NULL) {
        hideset = hideset_append(name->hideset, name->value);
    } else {
        if (!ctx->in_directive)
            while (pp_peek(ctx)->type == PP_NEWLINE)
                pp_get(ctx);
        ppToken* l_paren = pp_peek(ctx);
        if (is_eof(l_paren) || l_paren->type != PP_SYMBOL || l_paren->value != SYMBOL_L_PARENTHESIS) {
            ctx->current = saved;
            return false;
        }
        pp_get(ctx);  // consume '('

        args = handle_macro_args(ctx, macro, name);
        if (args == NULL) {
            ctx->current = saved;
            return false;
        }
        ppToken* r_paren = pp_get(ctx);  // consume ')'
        hideset = hideset_intersect(name->hideset, r_paren->hideset, name->value);
    }

    list(ppToken*) result = paste_macro_body(ctx, macro, args, name, hideset);
    if (list_empty(result))
        return true;
    result->tail->next = ctx->current;
    ctx->current = result->head;
    return true;
}

static void delete_macro(ppContext* ctx, string name) {
    if (!list_empty(ctx->macros)) {
        ListNode* prev = NULL;
        foreach (ppMacro*, macro, ctx->macros) {
            if (macro->name->value == name) {
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
}

static bool get_macro_params(ppContext* ctx, ppMacro* macro) {
    if (ctx == NULL || macro == NULL || macro->params == NULL)
        return false;
    ppToken* t = pp_peek(ctx);
    while (t->type != PP_SYMBOL || t->value != SYMBOL_R_PARENTHESIS) {
        if (is_eof(t) || t->type == PP_NEWLINE) {
            preprocessor_error("Expected parameter or ) in macro definition", (t == NULL ? macro->name : t)->line, (t == NULL ? macro->name : t)->column);
            return false;
        }
        if (t->type != PP_IDENTIFIER) {
            if (t->type == PP_SYMBOL && t->value == SYMBOL_ELLIPSIS) {
                pp_get(ctx);  // consume '...'
                macro->is_variadic = true;
                if (!expect_token(ctx, "Expected ) after ... in macro parameter list", t->line, t->column, PP_SYMBOL, SYMBOL_R_PARENTHESIS))
                    return false;
                return true;
            }
            preprocessor_error("Expected parameter name in macro definition", t->line, t->column);
            return false;
        }
        t = pp_get(ctx);  // consume parameter name
        if (t->value == P_VA_ARGS_) {
            preprocessor_error("Invalid parameter name __VA_ARGS__ in macro definition", t->line, t->column);
            return false;
        }
        foreach (ppToken*, param, macro->params) {
            if (param->value == t->value) {
                preprocessor_error("Duplicate parameter name in macro definition", t->line, t->column);
                return false;
            }
        }
        append(macro->params, t);
        t = pp_peek(ctx);
        if (is_eof(t) || t->type == PP_NEWLINE) {
            preprocessor_error("Expected , or ) in macro definition", (t == NULL ? macro->name : t)->line, (t == NULL ? macro->name : t)->column);
            return false;
        }
        if (t->type == PP_SYMBOL && t->value == SYMBOL_COMMA) {
            t = pp_get(ctx);  // consume ','
            t = pp_peek(ctx);
            if (is_eof(t) || t->type == PP_NEWLINE || (t->type == PP_SYMBOL && t->value == SYMBOL_R_PARENTHESIS)) {
                preprocessor_error("Expected parameter name after , in macro definition", (t == NULL ? macro->name : t)->line, (t == NULL ? macro->name : t)->column);
                return false;
            }
        } else if (t->type == PP_SYMBOL && t->value == SYMBOL_R_PARENTHESIS) {
            break;
        } else {
            preprocessor_error("Expected , or ) in macro definition", t->line, t->column);
            return false;
        }
        t = pp_peek(ctx);
    }
    if (t->type == PP_SYMBOL && t->value == SYMBOL_R_PARENTHESIS) {
        pp_get(ctx);  // consume ')'
        return true;
    } else {
        preprocessor_error("Expected ) in macro parameter list", t->line, t->column);
        return false;
    }
}

static bool macro_equal(ppMacro* a, ppMacro* b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (a->name->value != b->name->value) return false;
    if (a->is_variadic != b->is_variadic) return false;
    if ((a->params == NULL) != (b->params == NULL)) return false;
    if (list_empty(a->params) != list_empty(b->params)) return false;
    if (list_empty(a->body) != list_empty(b->body)) return false;
    if (!list_empty(a->params) && !list_empty(b->params)) {
        ListNode* old_node = a->params->head;
        ListNode* new_node = b->params->head;
        while (new_node != NULL && old_node != NULL) {
            if (((ppToken*)old_node->data)->value != ((ppToken*)new_node->data)->value)
                return false;
            old_node = old_node->next;
            new_node = new_node->next;
        }
        if ((old_node == NULL) != (new_node == NULL))
            return false;
    }
    if (!list_empty(a->body) && !list_empty(b->body)) {
        ListNode* old_node = a->body->head;
        ListNode* new_node = b->body->head;
        bool first = true;
        while (new_node != NULL && old_node != NULL) {
            ppToken* old_t = (ppToken*)old_node->data;
            ppToken* new_t = (ppToken*)new_node->data;
            if (old_t->type != new_t->type || old_t->value != new_t->value || (!first && old_t->space_before != new_t->space_before))
                return false;
            first = false;
            old_node = old_node->next;
            new_node = new_node->next;
        }
        if ((old_node == NULL) != (new_node == NULL))
            return false;
    }
    return true;
}

#define not_allow_macro_name(value) (value == P_DEFINED || value == P_VA_ARGS_ || value == P_DATE_ || value == P_TIME_ || value == P_STDC_ || value == P_STDC_VERSION_ || value == P_STDC_HOSTED_)

static void handle_define(ppContext* ctx) {
    ppToken* t = pp_peek(ctx);
    if (is_eof(t) || t->type != PP_IDENTIFIER) {
        preprocessor_error("Expected macro name after #define", t == NULL ? 0 : t->line, t == NULL ? 0 : t->column);
        return;
    }
    if (not_allow_macro_name(t->value)) {
        preprocessor_error("Invalid macro name after #define", t->line, t->column);
        return;
    }
    if (t->value == P_FILE_ || t->value == P_LINE_) {
        preprocessor_warn("Redefining predefined macro", t->line, t->column);
    }
    t = pp_get(ctx);  // consume macro name
    ppToken* name = t;
    t = pp_peek(ctx);
    ppMacro* macro = NULL;
    if (!is_eof(t) && t->type == PP_SYMBOL && t->value == SYMBOL_L_PARENTHESIS && !t->space_before) {
        pp_get(ctx);  // consume '('
        macro = create_pp_macro(name, true);
        if (!get_macro_params(ctx, macro))
            return;
    } else {
        if (!is_eof(t) && t->type != PP_NEWLINE && !t->space_before)
            preprocessor_warn("Missing space between macro name and replacement list", t->line, t->column);
        macro = create_pp_macro(name, false);
    }
    t = pp_peek(ctx);
    if (!is_eof(t) && t->type == PP_SYMBOL && t->value == SYMBOL_DOUBLE_HASH) {
        preprocessor_error("Macro body cannot start with ##", t->line, t->column);
        return;
    }
    int state = 0;  // 0: normal, 1: after #, 2: after ##
    while (!is_eof(t) && t->type != PP_NEWLINE) {
        t = pp_get(ctx);  // consume token
        if (t->type == PP_IDENTIFIER && t->value == P_VA_ARGS_ && !macro->is_variadic) {
            preprocessor_error("Invalid use of __VA_ARGS__ in macro body", t->line, t->column);
            return;
        }
        if (state == 1) {
            if (t->type != PP_IDENTIFIER) {
                preprocessor_error("Expected parameter after # in macro body", t->line, t->column);
                return;
            }
            bool find = false;
            if (t->value == P_VA_ARGS_ && macro->is_variadic)
                find = true;
            else if (!list_empty(macro->params)) {
                foreach (ppToken*, param, macro->params) {
                    if (param->value == t->value) {
                        find = true;
                        goto break_foreach_in_handle_define;
                    }
                }
            }
        break_foreach_in_handle_define:
            if (!find) {
                preprocessor_error("Invalid parameter after # in macro body", t->line, t->column);
                return;
            }
        }
        if (macro->params != NULL && t->type == PP_SYMBOL && t->value == SYMBOL_HASH)
            state = 1;
        else if (t->type == PP_SYMBOL && t->value == SYMBOL_DOUBLE_HASH)
            state = 2;
        else
            state = 0;
        append(macro->body, t);
        t = pp_peek(ctx);
    }
    if (state == 1) {
        preprocessor_error("Macro body cannot end with #", (t == NULL ? name : t)->line, (t == NULL ? name : t)->column);
        return;
    }
    if (state == 2) {
        preprocessor_error("Macro body cannot end with ##", (t == NULL ? name : t)->line, (t == NULL ? name : t)->column);
        return;
    }
    ppMacro* old = find_macro(ctx, name->value);
    if (old != NULL) {
        if (!macro_equal(old, macro))
            preprocessor_warn("Macro redefined", name->line, name->column);
        delete_macro(ctx, name->value);
    }
    append(ctx->macros, macro);
}

static void handle_include(ppContext* ctx, ppToken* header_name) {
    // TODO
}

static bool eval_conditional(ppContext* ctx) {
    // TODO
    return false;  // placeholder
}

static ppToken* build_include_name(ppContext* ctx, ppToken* directive, list(ppToken*) tokens) {
    if (list_empty(tokens)) {
        preprocessor_error("Expected header name in #include", directive->line, directive->column);
        return NULL;
    }
    int state = 0;  // 1: <, 2: header_name, 3: >
    ppToken* name = NULL;
    string header_name = NULL;
    ListNode* other = NULL;
    foreach (ppToken*, t, tokens) {
        if (is_eof(t)) {
            preprocessor_error("Unexpected end of tokens in #include", t->line, t->column);
            return NULL;
        } else if (state == 0 && t->type == PP_STRING) {
            name = create_pp_token(PP_HEADER_NAME, t->value, ctx->lexer, 0);
            name->line = t->line;
            name->column = t->column;
            name->expanded_from = t->expanded_from;
            other = t__n;
            goto skip_foreach_in_build_include_name;
        } else if (state == 0 && t->type == PP_SYMBOL && t->value == SYMBOL_LT) {
            state = 1;
            header_name = "<";
            continue;
        } else if ((state == 2 || state == 1) && t->type == PP_SYMBOL && t->value == SYMBOL_GT) {
            if (state == 1) {
                preprocessor_error("Expected header name after <", t->line, t->column);
                return NULL;
            }
            state = 3;
            header_name = string_splice("%s>", header_name);
            name = create_pp_token(PP_HEADER_NAME, header_name, ctx->lexer, 0);
            name->line = t->line;
            name->column = t->column;
            name->expanded_from = t->expanded_from;
            other = t__n;
            goto skip_foreach_in_build_include_name;
        } else if ((state == 1 || state == 2) && t->type != PP_EOF && t->type != PP_NEWLINE) {
            if (t->space_before && state == 2)  // don't add space after '<'
                header_name = string_splice("%s %s", header_name, t->value);
            else
                header_name = string_splice("%s%s", header_name, t->value);
            state = 2;
            continue;
        } else if (state == 0 && t->type == PP_HEADER_NAME) {
            name = t;
            other = t__n;
            goto skip_foreach_in_build_include_name;
        } else {
            preprocessor_error("Invalid token in #include header name", t->line, t->column);
            return NULL;
        }
    }
skip_foreach_in_build_include_name:
    if (other != NULL && other->next != NULL && (ppToken*)other->next->data != NULL) {
        ppToken* t = (ppToken*)other->next->data;
        if (!is_eof(t) && t->type != PP_NEWLINE) {
            preprocessor_error("Unexpected token after #include header name", t->line, t->column);
            return NULL;
        }
    }
    if (name == NULL) {
        if (state == 0)
            preprocessor_error("Expected header name in #include", directive->line, directive->column);
        else
            preprocessor_error("Expected closing > in #include", directive->line, directive->column);
        return NULL;
    }
    return name;
}

static void handle_directive(ppContext* ctx) {
    ppToken* directive = pp_peek(ctx);
    if (is_eof(directive) || directive->type != PP_IDENTIFIER) {
        if ((!is_eof(directive) && directive->type == PP_NEWLINE) || !cond_active(ctx))
            return;
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
        if (not_allow_macro_name(name->value)) {
            preprocessor_error("Invalid macro name after #undef", name->line, name->column);
            return;
        }
        pp_get(ctx);
        delete_macro(ctx, name->value);
    } else if (directive->value == P_IF || directive->value == P_IFDEF || directive->value == P_IFNDEF) {
        bool outer_active = cond_active(ctx);
        bool inner_active = false;
        ppCondFrame* frame = create_pp_cond_frame(directive);
        if (outer_active) {
            if (directive->value == P_IF) {
                inner_active = eval_conditional(ctx) != 0;
            } else {
                ppToken* name = pp_peek(ctx);
                if (is_eof(name) || name->type != PP_IDENTIFIER) {
                    preprocessor_error("Expected identifier after #if[n]def", directive->line, directive->column);
                    frame->active = false;
                    frame->taken = false;
                    append(ctx->cond_stack, frame);
                    return;
                }
                pp_get(ctx);
                inner_active = (directive->value == P_IFDEF) == (find_macro(ctx, name->value) != NULL);
            }
        }
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
        list(ppToken*) tokens = create_list(ppToken*);
        int expansions = 0;
        while (true) {
            ppToken* t = pp_peek(ctx);
            if (is_eof(t) || t->type == PP_NEWLINE) break;
            pp_get(ctx);
            if (t->type == PP_IDENTIFIER && expand_macro(ctx, t)) {
                if (++expansions > 64) {
                    preprocessor_error("Too many macro expansions in #include", t->line, t->column);
                    return;
                }
                continue;
            }
            append(tokens, t);
        }
        ppToken* name = build_include_name(ctx, directive, tokens);
        if (name == NULL)
            return;
        handle_include(ctx, name);
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
    has_error = pp_lexer(lexer);

    ppContext* ctx = create_pp_context(lexer);
    ctx->current = lexer->pp_tokens->head;

    while (true) {
        ppToken* token = pp_peek(ctx);
        if (is_eof(token)) break;

        if (token->at_line_start && token->type == PP_SYMBOL && token->value == SYMBOL_HASH) {
            pp_get(ctx);  // consume '#'
            ctx->in_directive = true;
            handle_directive(ctx);
            ctx->in_directive = false;
            skip_to_newline(ctx);
        } else {
            token = pp_get(ctx);
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
