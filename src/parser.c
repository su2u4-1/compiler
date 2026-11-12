#include "parser.h"

#include "ast.h"
#include "lexer.h"

#define is_eof(token) ((token)->type == TOKEN_EOF)
#define parser_error(msg, t) report_error(parser, (t), (msg))
#define parser_warn(msg, t) report_warning(parser, (t), (msg))
#define peek(parser) ((Token*)((parser)->next->data))

static void report_error(Parser* parser, Token* t, string msg) {
    if (parser->panic_mode) return;
    parser->panic_mode = true;
    parser->error_count++;
    if (t == NULL)
        fprintf(stderr, "[Parse Error] at unknown location: %s\n", msg);
    else
        fprintf(stderr, "[Parse Error] at %s:%zu:%zu: %s\n", t->filename, t->line, t->column, msg);
}

static void report_warning(Parser* parser, Token* t, string msg) {
    if (parser->panic_mode) return;
    if (t == NULL)
        fprintf(stderr, "[Parse Warning] at unknown location: %s\n", msg);
    else
        fprintf(stderr, "[Parse Warning] at %s:%zu:%zu: %s\n", t->filename, t->line, t->column, msg);
}

static Scope* create_scope(ScopeKind kind, Scope* parent) {
    Scope* scope = create_struct(Scope);
    scope->kind = kind;
    scope->parent = parent;
    scope->names = create_list(Symbol*);
    scope->tags = create_list(Symbol*);
    return scope;
}

Parser* create_parser(list(Token*) tokens) {
    Parser* parser = create_struct(Parser);
    parser->tokens = tokens;
    parser->next = tokens->head;
    parser->current = NULL;
    parser->current_scope = create_scope(SCOPE_FILE, NULL);
    parser->error_count = 0;
    parser->panic_mode = false;
    return parser;
}

static Token* get(Parser* parser) {
    parser->current = parser->next->data;
    if (!is_eof(parser->current))
        parser->next = parser->next->next;
    return parser->current;
}

static Token* peek2(Parser* parser) {
    assert(parser->next != NULL);
    Token* t = peek(parser);
    if (is_eof(t) || parser->next->next == NULL)
        return t;
    return (Token*)parser->next->next->data;
}

static bool check(Parser* parser, TokenType type, string value) {
    Token* t = peek(parser);
    assert(t != NULL);
    return t->type == type && (value == NULL || t->value == value);
}

static Token* expect(Parser* parser, TokenType type, string value, string msg) {
    if (!check(parser, type, value)) {
        parser_error(msg, peek(parser));
        return NULL;
    }
    return get(parser);
}

static bool match(Parser* parser, TokenType type, string value) {
    if (!check(parser, type, value))
        return false;
    get(parser);
    return true;
}

static void synchronize(Parser* parser) {
    if (!parser->panic_mode) return;
    size_t depth = 0;
    for (Token* t = peek(parser); !is_eof(t); t = peek(parser)) {
        if (t->type == TOKEN_SYMBOL && t->value == SYMBOL_R_BRACE && depth == 0)
            break;
        get(parser);
        if (t->type != TOKEN_SYMBOL) continue;
        if (t->value == SYMBOL_L_BRACE)
            depth++;
        else if (t->value == SYMBOL_R_BRACE && --depth == 0)
            break;
        else if (t->value == SYMBOL_SEMICOLON && depth == 0)
            break;
    }
    parser->panic_mode = false;
}

static bool is_typedef_name(Parser* parser, string name) {
    for (Scope* s = parser->current_scope; s != NULL; s = s->parent) {
        foreach (Symbol*, sym, s->names) {
            if (sym->name == name) return sym->kind == SYMBOL_KIND_TYPEDEF;
        }
    }
    return false;
}

static bool is_type_specifier_start(Parser* parser, bool seen_type) {
    Token* t = peek(parser);
    if (t->type == TOKEN_KEYWORD) {
        if (t->value == KEYWORD_ATOMIC) {
            // '_Atomic' '(' -> specifier
            Token* p = peek2(parser);
            return p->type == TOKEN_SYMBOL && p->value == SYMBOL_L_PARENTHESIS;
        }
        return t->value == KEYWORD_VOID || t->value == KEYWORD_CHAR || t->value == KEYWORD_SHORT || t->value == KEYWORD_INT || t->value == KEYWORD_LONG || t->value == KEYWORD_FLOAT || t->value == KEYWORD_DOUBLE || t->value == KEYWORD_SIGNED || t->value == KEYWORD_UNSIGNED || t->value == KEYWORD_BOOL || t->value == KEYWORD_IMAGINARY || t->value == KEYWORD_COMPLEX || t->value == KEYWORD_STRUCT || t->value == KEYWORD_UNION || t->value == KEYWORD_ENUM;
    }
    if (t->type == TOKEN_IDENTIFIER)
        return !seen_type && is_typedef_name(parser, t->value);
    return false;
}

static bool is_type_qualifier_start(Parser* parser, bool not_check_atomic) {
    Token* t = peek(parser);
    if (t->type == TOKEN_KEYWORD && (t->value == KEYWORD_CONST || t->value == KEYWORD_RESTRICT || t->value == KEYWORD_VOLATILE))
        return true;
    if (t->type == TOKEN_KEYWORD && t->value == KEYWORD_ATOMIC) {
        if (not_check_atomic) return true;
        // only '_Atomic' -> qualifier
        Token* p = peek2(parser);
        return p->type != TOKEN_SYMBOL || p->value != SYMBOL_L_PARENTHESIS;
    }
    return false;
}

static bool is_function_declarator(Declarator* d) {
    // TODO
    return false;  // placeholder
}

static ConditionalExpression* parse_conditional_expression(Parser* parser) {
    return NULL;  // placeholder
}
static list(DeclStmt*) parse_compound_statement(Parser* parser) {
    return NULL;  // placeholder
}
static TypeName* parse_type_name(Parser* parser) {
    return NULL;  // placeholder
}
static AssignmentExpression* parse_assignment_expression(Parser* parser) {
    return NULL;  // placeholder
}
static StructDecl* parse_struct_decl(Parser* parser) {
    return NULL;  // placeholder
}
static Enumerator* parse_enumerator(Parser* parser) {
    return NULL;  // placeholder
}

static Declarator* parse_declarator(Parser* parser, bool* is_abs);
static list(DeclSpec*) parse_declaration_specifiers(Parser* parser);
static list(ParamDecl*) parse_parameter_declarations(Parser* parser, bool* is_variadic) {
    Token* t = peek(parser);
    *is_variadic = false;
    list(ParamDecl*) param_decls = create_list(ParamDecl*);
    if (match(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS))
        return param_decls;
    do {
        if (match(parser, TOKEN_SYMBOL, SYMBOL_ELLIPSIS)) {
            if (list_empty(param_decls))
                parser_warn("ISO C requires a named parameter before '...'", t);
            *is_variadic = true;
            break;
        }
        ParamDecl* param_decl = create_struct(ParamDecl);
        t = peek(parser);
        *param_decl = (ParamDecl){.token = t, .decl_specs = parse_declaration_specifiers(parser), .decl = NULL, .is_abs = true};
        t = peek(parser);
        if (t->type == TOKEN_IDENTIFIER || (t->type == TOKEN_SYMBOL && (t->value == SYMBOL_MUL || t->value == SYMBOL_L_PARENTHESIS || t->value == SYMBOL_L_BRACKET))) {
            param_decl->is_abs = false;
            param_decl->decl = parse_declarator(parser, &param_decl->is_abs);
        }
        append(param_decls, param_decl);
    } while (match(parser, TOKEN_SYMBOL, SYMBOL_COMMA));
    expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ',' or ')' in parameter list");
    return param_decls;
}

static Pointer* parse_pointer(Parser* parser) {
    Token* t = peek(parser);
    Pointer* pointer = create_struct(Pointer);
    // always true, consume '*'
    expect(parser, TOKEN_SYMBOL, SYMBOL_MUL, "Expected '*' in pointer declarator");
    *pointer = (Pointer){.token = t, .type_qualifiers = NULL, .pointer = NULL};
    if (is_type_qualifier_start(parser, true)) {
        pointer->type_qualifiers = create_list(string);
        while (is_type_qualifier_start(parser, true)) {
            t = get(parser);
            append(pointer->type_qualifiers, t->value);
        }
    }
    if (check(parser, TOKEN_SYMBOL, SYMBOL_MUL))
        pointer->pointer = parse_pointer(parser);
    return pointer;
}

static Designator* parse_designator(Parser* parser) {
    Token* t = peek(parser);
    Designator* designator = create_struct(Designator);
    designator->token = t;
    if (match(parser, TOKEN_SYMBOL, SYMBOL_DOT)) {
        Token* id = expect(parser, TOKEN_IDENTIFIER, NULL, "Expected member name after '.' in designator");
        designator->is_constant_expr = false;
        designator->designator.identifier = id;
    } else if (match(parser, TOKEN_SYMBOL, SYMBOL_L_BRACKET)) {
        designator->is_constant_expr = true;
        designator->designator.constant_expr = parse_conditional_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACKET, "Expected ']' after array index in designator");
    } else
        assert(false);
    return designator;
}

static Initializer* parse_initializer(Parser* parser);
static InitializerItem* parse_initializer_item(Parser* parser) {
    Token* t = peek(parser);
    InitializerItem* item = create_struct(InitializerItem);
    item->token = t;
    item->designation = NULL;
    if (check(parser, TOKEN_SYMBOL, SYMBOL_DOT) || check(parser, TOKEN_SYMBOL, SYMBOL_L_BRACKET)) {
        item->designation = create_list(Designator*);
        while (check(parser, TOKEN_SYMBOL, SYMBOL_DOT) || check(parser, TOKEN_SYMBOL, SYMBOL_L_BRACKET))
            append(item->designation, parse_designator(parser));
        expect(parser, TOKEN_SYMBOL, SYMBOL_ASSIGN, "Expected '=' after designator");
    }
    item->initializer = parse_initializer(parser);
    return item;
}

static Initializer* parse_initializer(Parser* parser) {
    Token* t = peek(parser);
    Initializer* init = create_struct(Initializer);
    init->token = t;
    if (match(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
        init->is_assignment_expr = false;
        init->init.inits = create_list(InitializerItem*);
        do {
            if (check(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE))
                break;
            append(init->init.inits, parse_initializer_item(parser));
        } while (match(parser, TOKEN_SYMBOL, SYMBOL_COMMA));
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE, "Expected ',' or '}' in initializer list");
        if (list_empty(init->init.inits))
            parser_warn("ISO C forbids empty initializer braces", t);
    } else {
        init->is_assignment_expr = true;
        init->init.assignment_expr = parse_assignment_expression(parser);
    }
    return init;
}

static TypeSpec* parse_type_specifier(Parser* parser) {
    Token* t = peek(parser);
    TypeSpec* type = create_struct(TypeSpec);
    type->token = t;
    if (t->type == TOKEN_KEYWORD) {
        if (t->value == KEYWORD_ATOMIC) {
            type->spec_type = TYPE_SPEC_ATOMIC;
            get(parser);  // consume '_Atomic'
            expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after '_Atomic'");
            type->spec.atomic_spec = parse_type_name(parser);
            expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after '_Atomic' type name");
        } else if (t->value == KEYWORD_VOID || t->value == KEYWORD_CHAR || t->value == KEYWORD_SHORT || t->value == KEYWORD_INT || t->value == KEYWORD_LONG || t->value == KEYWORD_FLOAT || t->value == KEYWORD_DOUBLE || t->value == KEYWORD_SIGNED || t->value == KEYWORD_UNSIGNED || t->value == KEYWORD_BOOL || t->value == KEYWORD_IMAGINARY || t->value == KEYWORD_COMPLEX) {
            t = get(parser);  // consume keyword
            type->spec_type = TYPE_SPEC_KEYWORD;
            type->spec.keyword_spec = t->value;
        } else if (t->value == KEYWORD_STRUCT || t->value == KEYWORD_UNION) {
            t = get(parser);  // consume 'struct' or 'union'
            type->spec_type = TYPE_SPEC_STRUCT_UNION;
            type->spec.struct_union_spec.is_struct = t->value == KEYWORD_STRUCT;
            t = peek(parser);
            if (match(parser, TOKEN_IDENTIFIER, NULL))
                type->spec.struct_union_spec.identifier = t;
            else
                type->spec.struct_union_spec.identifier = NULL;
            list(StructDecl*) members = NULL;
            if (match(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
                members = create_list(StructDecl*);
                while (true) {
                    t = peek(parser);
                    if (is_type_qualifier_start(parser, false) || is_type_specifier_start(parser, false) || (t->type == TOKEN_KEYWORD && t->value == KEYWORD_STATIC_ASSERT)) {
                        StructDecl* decl = parse_struct_decl(parser);
                        append(members, decl);
                    } else
                        break;
                }
                if (type->spec.struct_union_spec.is_struct)
                    expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE, "Expected member declaration or '}' in struct");
                else
                    expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE, "Expected member declaration or '}' in union");
            }
            type->spec.struct_union_spec.members = members;
            if (members != NULL && list_empty(members)) {
                if (type->spec.struct_union_spec.is_struct)
                    parser_warn("Struct has no members", t);
                else
                    parser_warn("Union has no members", t);
            } else if (type->spec.struct_union_spec.identifier == NULL && members == NULL) {
                if (type->spec.struct_union_spec.is_struct)
                    parser_error("Expected tag name or '{' after 'struct'", t);
                else
                    parser_error("Expected tag name or '{' after 'union'", t);
            }
        } else if (t->value == KEYWORD_ENUM) {
            t = get(parser);  // consume 'enum'
            type->spec_type = TYPE_SPEC_ENUM;
            t = peek(parser);
            if (match(parser, TOKEN_IDENTIFIER, NULL))
                type->spec.enum_spec.identifier = t;
            else
                type->spec.enum_spec.identifier = NULL;
            list(Enumerator*) enumerators = NULL;
            if (match(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
                enumerators = create_list(Enumerator*);
                while (true) {
                    t = peek(parser);
                    if (t->type == TOKEN_IDENTIFIER) {
                        Enumerator* decl = parse_enumerator(parser);
                        append(enumerators, decl);
                    } else
                        break;
                    if (!match(parser, TOKEN_SYMBOL, SYMBOL_COMMA))
                        break;
                }
                expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE, "Expected ',' or '}' in enumerator list");
            }
            type->spec.enum_spec.enumerators = enumerators;
            if (enumerators != NULL && list_empty(enumerators))
                parser_warn("Enum has no enumerators", t);
            else if (type->spec.enum_spec.identifier == NULL && enumerators == NULL)
                parser_error("Expected tag name or '{' after 'enum'", t);
        } else
            assert(false);
    } else if (t->type == TOKEN_IDENTIFIER && is_typedef_name(parser, t->value)) {
        t = get(parser);  // consume typedef_name
        type->spec_type = TYPE_SPEC_TYPEDEF_NAME;
        type->spec.typedef_name = t;
    }
    return type;
}

static DirectDeclarator* parse_direct_declarator(Parser* parser, bool* is_abs) {
    Token* t = peek(parser);
    DirectDeclarator* direct_decl = NULL;
    *is_abs = true;
    if (match(parser, TOKEN_IDENTIFIER, NULL)) {
        direct_decl = create_struct(DirectDeclarator);
        *direct_decl = (DirectDeclarator){.token = t, .decl_type = DECLARATOR_ID, .decl.identifier = t};
        *is_abs = false;
    } else if (match(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS)) {
        // TODO: check is function pointer declarator or declarator with parentheses
        bool is_inner_abs = true;
        direct_decl = create_struct(DirectDeclarator);
        *direct_decl = (DirectDeclarator){.token = t, .decl_type = DECLARATOR_DECL, .decl.declarator = parse_declarator(parser, &is_inner_abs)};
        if (!is_inner_abs) *is_abs = false;
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' to close parenthesized declarator");
    }
    while (true) {
        if (match(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS)) {
            bool is_variadic = false;
            list(ParamDecl*) params = parse_parameter_declarations(parser, &is_variadic);
            DirectDeclarator* new = create_struct(DirectDeclarator);
            *new = (DirectDeclarator){.token = t, .decl_type = DECLARATOR_FUNC, .decl.func.direct_declarator = direct_decl, .decl.func.param_decls = params, .decl.func.is_variadic = is_variadic};
            direct_decl = new;
        } else if (match(parser, TOKEN_SYMBOL, SYMBOL_L_BRACKET)) {
            bool has_static = false;
            bool has_star = false;
            list(string) type_qualifiers = NULL;
            Token* p = peek2(parser);
            if (is_type_qualifier_start(parser, true)) {
                type_qualifiers = create_list(string);
                while (is_type_qualifier_start(parser, true)) {
                    Token* tt = get(parser);
                    append(type_qualifiers, tt->value);
                }
                p = peek2(parser);
                if (check(parser, TOKEN_SYMBOL, SYMBOL_MUL) && p->type == TOKEN_SYMBOL && p->value == SYMBOL_R_BRACKET) {
                    get(parser);  // consume '*'
                    has_star = true;
                } else if (match(parser, TOKEN_KEYWORD, KEYWORD_STATIC))
                    has_static = true;
            } else if (check(parser, TOKEN_SYMBOL, SYMBOL_MUL) && p->type == TOKEN_SYMBOL && p->value == SYMBOL_R_BRACKET) {
                get(parser);  // consume '*'
                has_star = true;
            } else if (match(parser, TOKEN_KEYWORD, KEYWORD_STATIC)) {
                has_static = true;
                if (is_type_qualifier_start(parser, true)) {
                    type_qualifiers = create_list(string);
                    while (is_type_qualifier_start(parser, true)) {
                        Token* tt = get(parser);
                        append(type_qualifiers, tt->value);
                    }
                }
            }
            AssignmentExpression* expr = NULL;
            if (has_static || (!has_star && !check(parser, TOKEN_SYMBOL, SYMBOL_R_BRACKET)))
                expr = parse_assignment_expression(parser);
            expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACKET, "Expected ']' to close array declarator");
            DirectDeclarator* new = create_struct(DirectDeclarator);
            if (has_static || expr != NULL)
                *new = (DirectDeclarator){.token = t, .decl_type = DECLARATOR_ARRAY, .decl.array.direct_declarator = direct_decl, .decl.array.assignment_expression = expr, .decl.array.is_static = has_static, .decl.array.type_qualifiers = type_qualifiers};
            else
                *new = (DirectDeclarator){.token = t, .decl_type = DECLARATOR_INCOMPLETE_ARRAY, .decl.incomplete_array.direct_declarator = direct_decl, .decl.incomplete_array.has_star = has_star, .decl.incomplete_array.type_qualifiers = type_qualifiers};
            direct_decl = new;
        } else
            break;
    }
    return direct_decl;
}

static Declarator* parse_declarator(Parser* parser, bool* is_abs) {
    Declarator* decl = create_struct(Declarator);
    *decl = (Declarator){.token = peek(parser), .pointer = NULL, .direct_declarator = NULL};
    if (check(parser, TOKEN_SYMBOL, SYMBOL_MUL))
        decl->pointer = parse_pointer(parser);
    decl->direct_declarator = parse_direct_declarator(parser, is_abs);
    return decl;
}

static list(DeclSpec*) parse_declaration_specifiers(Parser* parser) {
    list(DeclSpec*) decl_specs = create_list(DeclSpec*);
    bool seen_type = false;
    for (Token* t = peek(parser); !is_eof(t); t = peek(parser)) {
        DeclSpec* decl_spec = create_struct(DeclSpec);
        decl_spec->token = t;
        if (is_type_specifier_start(parser, seen_type)) {
            // type_specifier
            decl_spec->specifier_type = SPEC_TYPE_SPEC;
            decl_spec->specifier.type = parse_type_specifier(parser);
            seen_type = true;
        } else if (is_type_qualifier_start(parser, false)) {
            // type_qualifier
            decl_spec->specifier_type = SPEC_KEYWORD;
            decl_spec->specifier.keyword = t->value;
            get(parser);  // consume type_qualifier
        } else if (t->type == TOKEN_KEYWORD) {
            if (t->value == KEYWORD_TYPEDEF || t->value == KEYWORD_EXTERN || t->value == KEYWORD_STATIC || t->value == KEYWORD_THREAD_LOCAL || t->value == KEYWORD_AUTO || t->value == KEYWORD_REGISTER || t->value == KEYWORD_INLINE || t->value == KEYWORD_NORETURN) {
                // storage_class_specifier & function_specifier
                decl_spec->specifier_type = SPEC_KEYWORD;
                decl_spec->specifier.keyword = t->value;
                get(parser);  // consume storage_class_specifier or function_specifier
            } else if (t->value == KEYWORD_ALIGNAS) {
                // alignment_specifier
                decl_spec->specifier_type = SPEC_ALIGNMENT;
                get(parser);  // consume '_Alignas'
                expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after '_Alignas'");
                if (is_type_qualifier_start(parser, false) || is_type_specifier_start(parser, false)) {
                    decl_spec->specifier.alignment.spec.type_name = parse_type_name(parser);
                    decl_spec->specifier.alignment.is_type_name = true;
                } else {
                    decl_spec->specifier.alignment.spec.constant_expression = parse_conditional_expression(parser);
                    decl_spec->specifier.alignment.is_type_name = false;
                }
                expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after '_Alignas' operand");
            } else
                break;
        } else
            break;
        append(decl_specs, decl_spec);
    }
    if (list_empty(decl_specs)) {
        parser_error("Expected type name or declaration specifier", peek(parser));
        return NULL;
    }
    return decl_specs;
}

static StaticAssertDecl* parse_static_assert(Parser* parser, Token* t) {
    StaticAssertDecl* decl = create_struct(StaticAssertDecl);
    *decl = (StaticAssertDecl){.token = t, .expr = NULL, .message = NULL};

    expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after '_Static_assert'");
    decl->expr = parse_conditional_expression(parser);
    expect(parser, TOKEN_SYMBOL, SYMBOL_COMMA, "Expected ',' after '_Static_assert' condition");
    Token* str = expect(parser, TOKEN_STRING, NULL, "Expected string literal as '_Static_assert' message");
    if (str != NULL)
        decl->message = str->literal.str.data;
    expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after '_Static_assert' message");
    expect(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON, "Expected ';' after '_Static_assert'");
    return decl;
}

static VarDecl* parse_var_decl(Parser* parser, list(DeclSpec*) decl_specs, Declarator* first, Token* t) {
    VarDecl* var_decl = create_struct(VarDecl);
    *var_decl = (VarDecl){.token = t, .is_static_assert_decl = false, .decl.general_decl.decl_specs = decl_specs, .decl.general_decl.init_decls = create_list(InitDecl*)};
    if (first == NULL && match(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON)) {
        if (decl_specs != NULL) {
            TypeSpec* tag = NULL;
            DeclSpec* redundant = NULL;
            Token* tt = NULL;
            foreach (DeclSpec*, spec, decl_specs) {
                if (tt == NULL) tt = spec->token;
                if (spec->specifier_type == SPEC_TYPE_SPEC) {
                    TypeSpec* type = spec->specifier.type;
                    if (type->spec_type == TYPE_SPEC_STRUCT_UNION || type->spec_type == TYPE_SPEC_ENUM)
                        tag = type;
                } else if (redundant == NULL)
                    redundant = spec;
            }
            if (tag == NULL)
                parser_warn("Declaration does not declare anything", tt);
            else if (tag->spec_type == TYPE_SPEC_STRUCT_UNION && tag->spec.struct_union_spec.identifier == NULL)
                parser_warn("Unnamed struct/union that defines no instances", tag->token);
            else if (redundant != NULL)
                parser_warn("Useless specifier in empty declaration", redundant->token);
        }
        return var_decl;
    }
    Declarator* decl = first;
    while (true) {
        Token* decl_t = decl != NULL ? decl->token : peek(parser);
        Initializer* init = NULL;
        if (match(parser, TOKEN_SYMBOL, SYMBOL_ASSIGN))
            init = parse_initializer(parser);
        InitDecl* init_decl = create_struct(InitDecl);
        *init_decl = (InitDecl){.token = decl_t, .declarator = decl, .initializer = init};
        append(var_decl->decl.general_decl.init_decls, init_decl);
        if (!match(parser, TOKEN_SYMBOL, SYMBOL_COMMA)) break;
        bool is_abs = false;
        decl = parse_declarator(parser, &is_abs);
        if (is_abs) {
            parser_error("Expected identifier in declarator after ','", decl->token);
            break;
        }
    }
    expect(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON, "Expected ',' or ';' after declarator");
    return var_decl;
}

TU* parse_parser(Parser* parser) {
    Token* t = peek(parser);
    TU* tu = create_struct(TU);
    tu->token = t;
    tu->filename = t->filename;
    tu->extern_decls = create_list(ExternDecl*);
    while (!is_eof(t)) {
        VarDecl* var_decl = NULL;
        if (match(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON))
            parser_warn("Extra ';' outside of a function", t);
        else if (match(parser, TOKEN_KEYWORD, KEYWORD_STATIC_ASSERT)) {
            StaticAssertDecl* static_assert_decl = parse_static_assert(parser, t);
            var_decl = create_struct(VarDecl);
            *var_decl = (VarDecl){.token = t, .is_static_assert_decl = true, .decl.static_assert_decl = static_assert_decl};
        } else {
            list(DeclSpec*) decl_specs = parse_declaration_specifiers(parser);
            if (check(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON))
                var_decl = parse_var_decl(parser, decl_specs, NULL, t);
            else {
                bool is_abs = false;
                Declarator* decl = parse_declarator(parser, &is_abs);
                if (is_abs)
                    parser_error("Expected identifier in declarator", decl->token);
                else if (check(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE) && !is_function_declarator(decl))
                    parser_error("Expected ';' after declaration (only a function declarator can have a body)", peek(parser));
                else if (match(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
                    list(DeclStmt*) compound = parse_compound_statement(parser);
                    expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE, "Expected '}' at end of function body");
                    FuncDecl* func_decl = create_struct(FuncDecl);
                    *func_decl = (FuncDecl){.token = t, .decl_specs = decl_specs, .declarator = decl, .body = compound};
                    ExternDecl* extern_decl = create_struct(ExternDecl);
                    *extern_decl = (ExternDecl){.token = t, .decl.func_decl = func_decl, .is_func_decl = true};
                    append(tu->extern_decls, extern_decl);
                } else
                    var_decl = parse_var_decl(parser, decl_specs, decl, t);
            }
        }
        if (var_decl != NULL) {
            ExternDecl* extern_decl = create_struct(ExternDecl);
            *extern_decl = (ExternDecl){.token = t, .decl.var_decl = var_decl, .is_func_decl = false};
            append(tu->extern_decls, extern_decl);
        }
        synchronize(parser);
        if (peek(parser) == t)
            get(parser);
        t = peek(parser);
    }
    return tu;
}
// TODO: add name into scope
