#include "semantic.h"

#include "lexer.h"

#define semantic_error(token, msg) report_error(ctx, (token), (msg), false)
#define semantic_warn(token, msg) report_error(ctx, (token), (msg), true)

typedef struct {
    IR_Type* type;
    string storage;
    bool is_inline;
    bool is_noreturn;
} DeclSpecInfo;

static void print_string_literal(FILE* out, StringLiteral str) {
    fputc('"', out);
    for (size_t i = 0; i < str.length; i++) {
        unsigned char c = (unsigned char)str.data[i];
        if (c == '"' || c == '\\') fprintf(out, "\\%c", c);
        else if (c >= 0x20 && c < 0x7F) fputc(c, out);
        else fprintf(out, "\\%03o", c);
    }
    fputc('"', out);
}

static void report_error(Semantic* ctx, Token* token, char* msg, bool is_warning) {
    if (is_warning)
        fprintf(stderr, "[Semantic warning] at %s:%zu:%zu: %s\n", token->filename, token->line, token->column, msg);
    else {
        fprintf(stderr, "[Semantic error] at %s:%zu:%zu: %s\n", token->filename, token->line, token->column, msg);
        ctx->error_count++;
    }
}

static void static_assert_report(Semantic* ctx, Token* token, StringLiteral str) {
    ctx->error_count++;
    fprintf(stderr, "[Static assertion failed] at %s:%zu:%zu: ", token->filename, token->line, token->column);
    print_string_literal(stderr, str);
    fputc('\n', stderr);
}

static IR_Scope* create_scope(IR_Scope* parent, IR_ScopeKind kind) {
    IR_Scope* scope = create_struct(IR_Scope);
    *scope = (IR_Scope){.parent = parent, .kind = kind, .names = create_list(IR_Symbol*), .tags = create_list(IR_Symbol*)};
    return scope;
}

static IR_Symbol* create_symbol(Token* token, string name, IR_Type* type, IR_SymbolKind kind) {
    IR_Symbol* symbol = create_struct(IR_Symbol);
    *symbol = (IR_Symbol){.token = token, .name = name, .type = type, .kind = kind, .linkage = LINKAGE_NONE};
    return symbol;
}

static IR_Symbol* declare_name(Semantic* ctx, Token* id, IR_Type* type, IR_SymbolKind kind, string storage) {
    return NULL;  // placeholder
}

static bool eval_const_int(IR_Expression* expr, intmax_t* out) {
    return false;  // placeholder
}

static bool is_complete_type(IR_Type* type) {
    if (type->type_kind == TYPE_VOID)
        return false;
    else if (type->type_kind == TYPE_STRUCT || type->type_kind == TYPE_UNION)
        return type->type.struct_union_type->members != NULL;
    else if (type->type_kind == TYPE_ENUM)
        return type->type.enum_type->items != NULL;
    else if (type->type_kind == TYPE_ARRAY)
        return type->type.array.length != 0;
    else
        return true;
}

static IR_Expression* analyze_conditional_expression(Semantic* ctx, AST_ConditionalExpression* node) {
    return NULL;  // placeholder
}

static IR_Expression* analyze_assignment_expression(Semantic* ctx, AST_AssignmentExpression* node) {
    return NULL;  // placeholder
}

static DeclSpecInfo analyze_decl_specs(Semantic* ctx, list(AST_DeclSpec*) decl_specs) {
    return (DeclSpecInfo){0};  // placeholder
}

static IR_Type* analyze_pointer(Semantic* ctx, AST_Pointer* node, IR_Type* base) {
    if (node == NULL) return base;
    assert(node->token != NULL);

    IR_Type* type = create_struct(IR_Type);
    type->token = node->token;
    type->type_kind = TYPE_POINTER;
    type->type.pointer_type = base;
    foreach (string, qual, node->type_qualifiers) {
        if (qual == KEYWORD_CONST) {
            if (type->is_const) semantic_warn(node->token, "Duplicate 'const' qualifier");
            type->is_const = true;
        } else if (qual == KEYWORD_VOLATILE) {
            if (type->is_volatile) semantic_warn(node->token, "Duplicate 'volatile' qualifier");
            type->is_volatile = true;
        } else if (qual == KEYWORD_RESTRICT) {
            if (base != NULL && base->type_kind == TYPE_FUNCTION)
                semantic_error(node->token, "'restrict' qualifier is not allowed for function pointer");
            else if (type->is_restrict)
                semantic_warn(node->token, "Duplicate 'restrict' qualifier");
            type->is_restrict = true;
        } else if (qual == KEYWORD_ATOMIC) {
            if (type->is_atomic) semantic_warn(node->token, "Duplicate 'atomic' qualifier");
            type->is_atomic = true;
        } else assert(false);
    }

    return analyze_pointer(ctx, node->pointer, type);
}

static IR_Type* analyze_array_suffix(Semantic* ctx, AST_DirectDeclarator* node, IR_Type* base) {
    assert(node != NULL);
    assert(node->token != NULL);
    assert(node->decl_type == DECLARATOR_ARRAY || node->decl_type == DECLARATOR_INCOMPLETE_ARRAY);
    if (node->decl_type == DECLARATOR_ARRAY) {
        assert(node->decl.array.assignment_expression != NULL);
        assert(node->decl.array.assignment_expression->token != NULL);
    }

    if (base == NULL) return NULL;
    if (base->type_kind == TYPE_FUNCTION) {
        semantic_error(node->token, "Array of functions is not allowed");
        return NULL;
    }
    if (!is_complete_type(base)) {
        semantic_error(node->token, "Array has incomplete element type");
        return NULL;
    }

    IR_Type* type = create_struct(IR_Type);
    type->token = node->token;
    type->type_kind = TYPE_ARRAY;
    type->type.array.element_type = base;
    if (base->type_kind == TYPE_STRUCT || base->type_kind == TYPE_UNION)
        type->align = base->type.struct_union_type->align;
    else
        type->align = base->align;

    list(string) type_qualifiers = NULL;
    if (node->decl_type == DECLARATOR_ARRAY) {
        type_qualifiers = node->decl.array.type_qualifiers;
        AST_AssignmentExpression* length_expr = node->decl.array.assignment_expression;
        IR_Expression* expr = analyze_assignment_expression(ctx, length_expr);
        if (expr == NULL) return NULL;
        intmax_t length = 0;
        if (!eval_const_int(expr, &length)) {
            semantic_error(length_expr->token, "Array size is not an integer constant expression");
            return NULL;
        }
        if (length <= 0) {
            semantic_error(length_expr->token, "Array size must be greater than 0");
            return NULL;
        }
        type->type.array.length = (uintmax_t)length;
        if (base->type_kind == TYPE_STRUCT || base->type_kind == TYPE_UNION)
            type->size = (size_t)length * base->type.struct_union_type->size;
        else
            type->size = (size_t)length * base->size;
    } else
        type_qualifiers = node->decl.incomplete_array.type_qualifiers;

    foreach (string, qual, type_qualifiers) {
        if (qual == KEYWORD_CONST) {
            if (type->is_const) semantic_warn(node->token, "Duplicate 'const' qualifier");
            type->is_const = true;
        } else if (qual == KEYWORD_VOLATILE) {
            if (type->is_volatile) semantic_warn(node->token, "Duplicate 'volatile' qualifier");
            type->is_volatile = true;
        } else if (qual == KEYWORD_RESTRICT) {
            if (type->is_restrict) semantic_warn(node->token, "Duplicate 'restrict' qualifier");
            type->is_restrict = true;
        } else if (qual == KEYWORD_ATOMIC) {
            if (type->is_atomic) semantic_warn(node->token, "Duplicate 'atomic' qualifier");
            type->is_atomic = true;
        } else assert(false);
    }
    return type;
}

static Token* analyze_declarator(Semantic* ctx, AST_Declarator* node, IR_Type* base, IR_Type** out_type);
static IR_Type* analyze_func_suffix(Semantic* ctx, AST_DirectDeclarator* node, IR_Type* base) {
    assert(node != NULL);
    assert(node->token != NULL);
    assert(node->decl_type == DECLARATOR_FUNC);
    assert(node->decl.func.param_decls != NULL);

    if (base == NULL) return NULL;

    bool has_error = false;
    if (base->type_kind == TYPE_ARRAY) {
        semantic_error(node->token, "Function cannot return an array");
        has_error = true;
    } else if (base->type_kind == TYPE_FUNCTION) {
        semantic_error(node->token, "Function cannot return a function");
        has_error = true;
    }

    IR_FuncProto* proto = create_struct(IR_FuncProto);
    *proto = (IR_FuncProto){.token = node->token, .params = create_list(IR_Param*), .return_type = base, .is_variadic = node->decl.func.is_variadic, .scope = create_scope(ctx->scope, SCOPE_PROTO)};
    bool is_only_param = node->decl.func.param_decls->head != NULL && node->decl.func.param_decls->head->next == NULL && !proto->is_variadic;

    ctx->scope = proto->scope;
    foreach (AST_ParamDecl*, param, node->decl.func.param_decls) {
        assert(param->token != NULL);
        assert(param->decl_specs != NULL);
        assert(param->decl != NULL || param->is_abs);
        DeclSpecInfo info = analyze_decl_specs(ctx, param->decl_specs);
        IR_Type* type = info.type;
        Token* id = NULL;
        if (param->decl != NULL) {
            id = analyze_declarator(ctx, param->decl, info.type, &type);
            if (type == NULL) {
                has_error = true;
                continue;
            }
        }
        assert(param->is_abs == (id == NULL));

        if (info.storage != NULL && info.storage != KEYWORD_REGISTER) {
            semantic_error(param->token, "Invalid storage class for parameter");
            has_error = true;
            continue;
        }
        if (info.is_inline || info.is_noreturn) {
            semantic_error(param->token, "Function specifier is not allowed for parameter");
            has_error = true;
            continue;
        }
        if (type->type_kind == TYPE_VOID) {
            bool is_unqualified = !type->is_const && !type->is_volatile && !type->is_restrict && !type->is_atomic;
            if (!is_only_param || id != NULL || !is_unqualified) {
                semantic_error(param->token, "'void' must be the only parameter, unnamed and unqualified");
                has_error = true;
            }
            continue;
        }

        if (type->type_kind == TYPE_ARRAY) {
            IR_Type* ptr = create_struct(IR_Type);
            *ptr = (IR_Type){.token = type->token, .type.pointer_type = type->type.array.element_type, .type_kind = TYPE_POINTER, .size = 8, .align = 8, .is_const = type->is_const, .is_volatile = type->is_volatile, .is_restrict = type->is_restrict, .is_atomic = type->is_atomic};
            type = ptr;
        } else if (type->type_kind == TYPE_FUNCTION) {
            IR_Type* ptr = create_struct(IR_Type);
            *ptr = (IR_Type){.token = type->token, .type.pointer_type = type, .type_kind = TYPE_POINTER, .size = 8, .align = 8};
            type = ptr;
        }

        IR_Param* ir_param = create_struct(IR_Param);
        *ir_param = (IR_Param){.token = param->token, .type = type};
        if (id != NULL) {
            ir_param->symbol = declare_name(ctx, id, type, SYMBOL_VAR, info.storage);
            if (ir_param->symbol == NULL) has_error = true;
        }
        append(proto->params, ir_param);
    }
    ctx->scope = proto->scope->parent;

    if (has_error) return NULL;
    IR_Type* type = create_struct(IR_Type);
    type->token = node->token;
    type->type_kind = TYPE_FUNCTION;
    type->type.func_type = proto;
    return type;
}

static Token* analyze_direct_declarator(Semantic* ctx, AST_DirectDeclarator* node, IR_Type* base, IR_Type** out_type) {
    if (node == NULL) {
        *out_type = base;
        return NULL;
    }
    assert(node->token != NULL);

    if (node->decl_type == DECLARATOR_ID) {
        assert(node->decl.identifier != NULL);
        *out_type = base;
        return node->decl.identifier;
    } else if (node->decl_type == DECLARATOR_DECL) {
        assert(node->decl.declarator != NULL);
        return analyze_declarator(ctx, node->decl.declarator, base, out_type);
    } else {
        IR_Type* type = NULL;
        AST_DirectDeclarator* direct_decl = NULL;
        if (node->decl_type == DECLARATOR_ARRAY) {
            type = analyze_array_suffix(ctx, node, base);
            direct_decl = node->decl.array.direct_declarator;
        } else if (node->decl_type == DECLARATOR_INCOMPLETE_ARRAY) {
            type = analyze_array_suffix(ctx, node, base);
            direct_decl = node->decl.incomplete_array.direct_declarator;
        } else if (node->decl_type == DECLARATOR_FUNC) {
            type = analyze_func_suffix(ctx, node, base);
            direct_decl = node->decl.func.direct_declarator;
        } else
            assert(false);
        return analyze_direct_declarator(ctx, direct_decl, type, out_type);
    }
}

static Token* analyze_declarator(Semantic* ctx, AST_Declarator* node, IR_Type* base, IR_Type** out_type) {
    assert(node != NULL);
    assert(node->token != NULL);
    assert(node->pointer != NULL || node->direct_declarator != NULL);

    IR_Type* type = analyze_pointer(ctx, node->pointer, base);
    return analyze_direct_declarator(ctx, node->direct_declarator, type, out_type);
}

static IR_Initializer* analyze_initializer(Semantic* ctx, AST_Initializer* node, IR_Type* type) {
    return NULL;  // placeholder
}

static void analyze_static_assert_decl(Semantic* ctx, AST_StaticAssertDecl* node) {
    assert(node != NULL);
    assert(node->token != NULL);
    assert(node->expr != NULL);
    assert(node->expr->token != NULL);
    assert(node->message != NULL);
    assert(node->message->type == TOKEN_STRING);

    IR_Expression* expr = analyze_conditional_expression(ctx, node->expr);
    if (expr == NULL) return;
    intmax_t value = 0;
    if (!eval_const_int(expr, &value))
        semantic_error(node->expr->token, "This expression is not a constant expression.");
    else if (value == 0)
        static_assert_report(ctx, node->token, node->message->literal.str);
}

static IR_Decl* analyze_init_decl(Semantic* ctx, AST_InitDecl* node, DeclSpecInfo info) {
    assert(node != NULL);
    assert(node->token != NULL);
    assert(node->declarator != NULL);

    IR_Type* type = NULL;
    Token* id = analyze_declarator(ctx, node->declarator, info.type, &type);
    assert(id != NULL);
    if (type == NULL) return NULL;

    IR_SymbolKind kind = SYMBOL_VAR;
    if (info.storage == KEYWORD_TYPEDEF) kind = SYMBOL_TYPEDEF;
    else if (type->type_kind == TYPE_FUNCTION) kind = SYMBOL_FUNC;

    IR_Symbol* symbol = declare_name(ctx, id, type, kind, info.storage);
    if (symbol == NULL) return NULL;

    if (kind == SYMBOL_TYPEDEF) {
        if (node->initializer != NULL)
            semantic_error(node->token, "typedef is initialized");
        return NULL;
    }

    IR_Decl* decl = create_struct(IR_Decl);
    *decl = (IR_Decl){.token = node->token, .symbol = symbol};
    if (kind == SYMBOL_FUNC) {
        if (node->initializer != NULL)
            semantic_error(node->token, "Function is initialized like a variable");
        decl->is_func_proto = true;
        decl->decl.func_proto = type->type.func_type;
    } else if (node->initializer != NULL) {
        decl->decl.initializer = analyze_initializer(ctx, node->initializer, symbol->type);
        symbol->is_defined = true;
    }
    return decl;
}

static list(IR_Decl*) analyze_var_decl(Semantic* ctx, AST_VarDecl* node) {
    assert(node != NULL);
    assert(node->token != NULL);
    if (!node->is_static_assert_decl) {
        assert(node->decl.general_decl.decl_specs != NULL);
        assert(node->decl.general_decl.init_decls != NULL);
    } else
        assert(node->decl.static_assert_decl != NULL);

    list(IR_Decl*) result = create_list(IR_Decl*);
    if (node->is_static_assert_decl) {
        analyze_static_assert_decl(ctx, node->decl.static_assert_decl);
        return result;
    }
    DeclSpecInfo info = analyze_decl_specs(ctx, node->decl.general_decl.decl_specs);

    foreach (AST_InitDecl*, init_decl, node->decl.general_decl.init_decls) {
        IR_Decl* decl = analyze_init_decl(ctx, init_decl, info);
        if (decl != NULL)
            append(result, decl);
    }
    return result;
}

static IR_FuncDef* analyze_func_decl(Semantic* ctx, AST_FuncDecl* node) {
    assert(node != NULL);
    assert(node->token != NULL);
    assert(node->decl_specs != NULL);
    assert(node->declarator != NULL);
    assert(node->body != NULL);

    DeclSpecInfo info = analyze_decl_specs(ctx, node->decl_specs);
    if (info.storage == KEYWORD_TYPEDEF || info.storage == KEYWORD_REGISTER || info.storage == KEYWORD_AUTO) {
        semantic_error(node->token, "Invalid storage class for function");
        return NULL;
    }

    IR_Type* type = NULL;
    Token* id = analyze_declarator(ctx, node->declarator, info.type, &type);
    assert(id != NULL);
    if (type == NULL) return NULL;

    if (type->type_kind != TYPE_FUNCTION || type == info.type) {
        semantic_error(node->token, "Function declarator must have function type");
        return NULL;
    }

    IR_FuncProto* proto = type->type.func_type;
    proto->name = id->value;

    // TODO

    return NULL;  // placeholder
}

static list(IR_ExternDecl*) analyze_extern_decl(Semantic* ctx, AST_ExternDecl* node) {
    assert(node != NULL);
    assert(node->token != NULL);
    if (node->is_func_decl)
        assert(node->decl.func_decl != NULL);
    else
        assert(node->decl.var_decl != NULL);

    list(IR_ExternDecl*) result = create_list(IR_ExternDecl*);
    if (node->is_func_decl) {
        IR_FuncDef* func_def = analyze_func_decl(ctx, node->decl.func_decl);
        if (func_def == NULL) return result;
        IR_ExternDecl* extern_decl = create_struct(IR_ExternDecl);
        *extern_decl = (IR_ExternDecl){.token = node->token, .decl.func_def = func_def, .is_func = true, .is_func_def = true};
        append(result, extern_decl);
        return result;
    }
    foreach (IR_Decl*, decl, analyze_var_decl(ctx, node->decl.var_decl)) {
        IR_ExternDecl* extern_decl = create_struct(IR_ExternDecl);
        if (decl->is_func_proto)
            *extern_decl = (IR_ExternDecl){.token = node->token, .decl.func_proto = decl->decl.func_proto, .is_func = true};
        else
            *extern_decl = (IR_ExternDecl){.token = node->token, .decl.var_decl = decl};
        append(result, extern_decl);
    }
    return result;
}

IR_TU* semantic_analyze(AST_TU* ast) {
    assert(ast != NULL);
    assert(ast->token != NULL);
    assert(ast->filename != NULL);
    assert(ast->extern_decls != NULL);

    IR_TU* tu = create_struct(IR_TU);
    *tu = (IR_TU){.token = ast->token, .extern_decls = create_list(IR_ExternDecl*), .global_scope = create_scope(NULL, SCOPE_FILE), .static_vars = create_list(IR_Symbol*), .filename = ast->filename};
    Semantic ctx = {.tu = tu, .func = NULL, .scope = tu->global_scope, .error_count = 0};
    foreach (AST_ExternDecl*, extern_decl, ast->extern_decls)
        foreach (IR_ExternDecl*, decl, analyze_extern_decl(&ctx, extern_decl))
            append(tu->extern_decls, decl);
    return tu;
}
