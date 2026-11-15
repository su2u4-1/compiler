#include "parser.h"

#include "ast.h"
#include "lexer.h"

#define is_eof(token) ((token)->type == TOKEN_EOF)
#define parser_error(msg, t) report_error(parser, (t), (msg))
#define parser_warn(msg, t) report_warning(parser, (t), (msg))
#define peek(parser) ((Token*)((parser)->next->data))
#define pop_scope(parser) (parser->current_scope = parser->current_scope->parent)

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

static void push_new_scope(Parser* parser, ScopeKind kind) {
    Scope* scope = create_scope(kind, parser->current_scope);
    parser->current_scope = scope;
    append(parser->scopes, scope);
}

Parser* create_parser(list(Token*) tokens) {
    Parser* parser = create_struct(Parser);
    parser->tokens = tokens;
    parser->next = tokens->head;
    parser->current = NULL;
    parser->brace_depth = 0;
    parser->paren_depth = 0;
    parser->current_scope = NULL;
    parser->scopes = create_list(Scope*);
    parser->error_count = 0;
    parser->panic_mode = false;
    push_new_scope(parser, SCOPE_FILE);
    return parser;
}

static Token* get(Parser* parser) {
    Token* t = parser->next->data;
    parser->current = t;
    if (is_eof(t)) return t;
    parser->next = parser->next->next;
    if (t->type == TOKEN_SYMBOL) {
        if (t->value == SYMBOL_L_BRACE)
            parser->brace_depth++;
        else if (t->value == SYMBOL_R_BRACE && parser->brace_depth > 0)
            parser->brace_depth--;
        else if (t->value == SYMBOL_L_PARENTHESIS)
            parser->paren_depth++;
        else if (t->value == SYMBOL_R_PARENTHESIS && parser->paren_depth > 0)
            parser->paren_depth--;
    }
    return t;
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

static void synchronize(Parser* parser, Token* start, size_t start_depth, bool is_top_level) {
    if (!parser->panic_mode) return;
    parser->panic_mode = false;
    Token* last = parser->current;
    if (peek(parser) != start && parser->brace_depth == start_depth && last->type == TOKEN_SYMBOL && (last->value == SYMBOL_SEMICOLON || last->value == SYMBOL_R_BRACE))
        return;
    size_t parenthesis_depth = 0;
    for (Token* t = peek(parser); !is_eof(t); t = peek(parser)) {
        bool at_start_level = parser->brace_depth == start_depth;
        if (t->type == TOKEN_SYMBOL && t->value == SYMBOL_R_BRACE && at_start_level) {
            if (is_top_level)
                get(parser);
            return;
        }
        get(parser);
        if (t->type != TOKEN_SYMBOL) continue;
        if (t->value == SYMBOL_R_BRACE && parser->brace_depth == start_depth) {
            match(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON);
            return;
        }
        if (t->value == SYMBOL_SEMICOLON && at_start_level && parenthesis_depth == 0)
            return;
        if (t->value == SYMBOL_L_PARENTHESIS)
            parenthesis_depth++;
        else if (t->value == SYMBOL_R_PARENTHESIS && parenthesis_depth > 0)
            parenthesis_depth--;
        else if (t->value == SYMBOL_L_BRACE || t->value == SYMBOL_R_BRACE)
            parenthesis_depth = 0;
    }
}

static void synchronize_paren(Parser* parser, size_t start_depth) {
    if (!parser->panic_mode) return;
    parser->panic_mode = false;
    for (Token* t = peek(parser); !is_eof(t) && parser->paren_depth > start_depth; t = peek(parser)) {
        if (t->type == TOKEN_SYMBOL && (t->value == SYMBOL_L_BRACE || t->value == SYMBOL_R_BRACE))
            break;  // missing ')'
        get(parser);
    }
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

static bool is_type_start(Parser* parser, Token* t) {
    if (t->type == TOKEN_KEYWORD)
        return t->value == KEYWORD_ATOMIC ||
               t->value == KEYWORD_VOID ||
               t->value == KEYWORD_CHAR ||
               t->value == KEYWORD_SHORT ||
               t->value == KEYWORD_INT ||
               t->value == KEYWORD_LONG ||
               t->value == KEYWORD_FLOAT ||
               t->value == KEYWORD_DOUBLE ||
               t->value == KEYWORD_SIGNED ||
               t->value == KEYWORD_UNSIGNED ||
               t->value == KEYWORD_BOOL ||
               t->value == KEYWORD_IMAGINARY ||
               t->value == KEYWORD_COMPLEX ||
               t->value == KEYWORD_STRUCT ||
               t->value == KEYWORD_UNION ||
               t->value == KEYWORD_ENUM ||
               t->value == KEYWORD_CONST ||
               t->value == KEYWORD_RESTRICT ||
               t->value == KEYWORD_VOLATILE;
    if (t->type == TOKEN_IDENTIFIER)
        return is_typedef_name(parser, t->value);
    return false;
}

static DirectDeclarator* get_function_declarator(Declarator* decl, DirectDeclarator* outer) {
    DirectDeclarator* inner = decl->direct_declarator;
    DirectDeclarator* last = NULL;
    while (inner != NULL && inner->decl_type != DECLARATOR_ID && inner->decl_type != DECLARATOR_DECL) {
        last = inner;
        switch (inner->decl_type) {
            case DECLARATOR_ARRAY:
                inner = inner->decl.array.direct_declarator;
                break;
            case DECLARATOR_FUNC:
                inner = inner->decl.func.direct_declarator;
                break;
            case DECLARATOR_INCOMPLETE_ARRAY:
                inner = inner->decl.incomplete_array.direct_declarator;
                break;
            case DECLARATOR_ID:
            case DECLARATOR_DECL:
            default:
                break;
        }
    }
    DirectDeclarator* nearest = outer;
    if (last != NULL)
        nearest = last->decl_type == DECLARATOR_FUNC ? last : NULL;
    else if (decl->pointer != NULL)
        nearest = NULL;
    if (inner != NULL && inner->decl_type == DECLARATOR_DECL)
        return get_function_declarator(inner->decl.declarator, nearest);
    return nearest;
}

static void add_name(Parser* parser, Token* id, SymbolKind kind) {
    foreach (Symbol*, symbol, parser->current_scope->names) {
        if (symbol->name == id->value) {
            if ((kind == SYMBOL_KIND_TYPEDEF) != (symbol->kind == SYMBOL_KIND_TYPEDEF))
                parser_error("Redeclared as different kind of symbol", id);
            return;
        }
    }
    Symbol* symbol = create_struct(Symbol);
    *symbol = (Symbol){.name = id->value, .token = id, .kind = kind};
    append(parser->current_scope->names, symbol);
}

static Token* get_declarator_identifier(DirectDeclarator* decl) {
    if (decl == NULL) return NULL;
    switch (decl->decl_type) {
        case DECLARATOR_ID:
            return decl->decl.identifier;
        case DECLARATOR_DECL:
            return get_declarator_identifier(decl->decl.declarator->direct_declarator);
        case DECLARATOR_ARRAY:
            return get_declarator_identifier(decl->decl.array.direct_declarator);
        case DECLARATOR_FUNC:
            return get_declarator_identifier(decl->decl.func.direct_declarator);
        case DECLARATOR_INCOMPLETE_ARRAY:
            return get_declarator_identifier(decl->decl.incomplete_array.direct_declarator);
        default:
            assert(false);
    }
}

static bool has_typedef(list(DeclSpec*) decl_specs) {
    foreach (DeclSpec*, spec, decl_specs)
        if (spec->specifier_type == SPEC_KEYWORD && spec->specifier.keyword == KEYWORD_TYPEDEF)
            return true;
    return false;
}

static bool is_declaration_start(Parser* parser) {
    Token* t = peek(parser);
    if (is_type_start(parser, t))
        return true;
    if (t->type != TOKEN_KEYWORD)
        return false;
    return t->value == KEYWORD_TYPEDEF || t->value == KEYWORD_EXTERN || t->value == KEYWORD_STATIC || t->value == KEYWORD_THREAD_LOCAL || t->value == KEYWORD_AUTO || t->value == KEYWORD_REGISTER || t->value == KEYWORD_INLINE || t->value == KEYWORD_NORETURN || t->value == KEYWORD_ALIGNAS || t->value == KEYWORD_STATIC_ASSERT;
}

static int binary_operator_precedence(Token* t) {
    if (t->type != TOKEN_SYMBOL) return -1;
    else if (t->value == SYMBOL_LOGICAL_OR) return 1;
    else if (t->value == SYMBOL_LOGICAL_AND) return 2;
    else if (t->value == SYMBOL_BITWISE_OR) return 3;
    else if (t->value == SYMBOL_XOR) return 4;
    else if (t->value == SYMBOL_BITWISE_AND) return 5;
    else if (t->value == SYMBOL_EQ || t->value == SYMBOL_NE) return 6;
    else if (t->value == SYMBOL_LT || t->value == SYMBOL_GT || t->value == SYMBOL_LE || t->value == SYMBOL_GE) return 7;
    else if (t->value == SYMBOL_L_SHIFT || t->value == SYMBOL_R_SHIFT) return 8;
    else if (t->value == SYMBOL_ADD || t->value == SYMBOL_SUB) return 9;
    else if (t->value == SYMBOL_MUL || t->value == SYMBOL_DIV || t->value == SYMBOL_MOD) return 10;
    else return -1;
}

static AssignmentExpression* parse_assignment_expression(Parser* parser);
static TypeName* parse_type_name(Parser* parser);
static GenericAssociation* parse_generic_association(Parser* parser) {
    GenericAssociation* assoc = create_struct(GenericAssociation);
    assoc->type_name = NULL;
    if (!match(parser, TOKEN_KEYWORD, KEYWORD_DEFAULT))
        assoc->type_name = parse_type_name(parser);
    expect(parser, TOKEN_SYMBOL, SYMBOL_COLON, "Expected ':' in generic association");
    assoc->assignment_expr = parse_assignment_expression(parser);
    return NULL;  // placeholder
}

static list(AssignmentExpression*) parse_expression(Parser* parser);
static PrimaryExpression* parse_primary_expression(Parser* parser) {
    Token* t = peek(parser);
    PrimaryExpression* primary_expr = create_struct(PrimaryExpression);
    primary_expr->token = t;
    if (t->type == TOKEN_SYNTAX_ERROR_NUMBER)
        parser_error("Invalid number literal", t);
    else if (t->type == TOKEN_SYNTAX_ERROR_CHAR)
        parser_error("Invalid character literal", t);
    else if (t->type == TOKEN_SYNTAX_ERROR_STRING)
        parser_error("Invalid string literal", t);
    if (t->type == TOKEN_IDENTIFIER) {
        primary_expr->primary_type = PRIMARY_IDENTIFIER;
        primary_expr->primary.identifier = get(parser);
    } else if (t->type == TOKEN_INT || t->type == TOKEN_SYNTAX_ERROR_NUMBER) {
        primary_expr->primary_type = PRIMARY_INTEGER_CONSTANT;
        primary_expr->primary.integer_constant = get(parser);
    } else if (t->type == TOKEN_CHAR || t->type == TOKEN_SYNTAX_ERROR_CHAR) {
        primary_expr->primary_type = PRIMARY_CHARACTER_CONSTANT;
        primary_expr->primary.character_constant = get(parser);
    } else if (t->type == TOKEN_FLOAT) {
        primary_expr->primary_type = PRIMARY_FLOATING_CONSTANT;
        primary_expr->primary.floating_constant = get(parser);
    } else if (t->type == TOKEN_STRING || t->type == TOKEN_SYNTAX_ERROR_STRING) {
        primary_expr->primary_type = PRIMARY_STRING_LITERAL;
        primary_expr->primary.string_literal = get(parser);
    } else if (match(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS)) {
        primary_expr->primary_type = PRIMARY_EXPRESSION;
        primary_expr->primary.expr = parse_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after expression");
    } else if (match(parser, TOKEN_KEYWORD, KEYWORD_GENERIC)) {
        primary_expr->primary_type = PRIMARY_GENERIC_SELECTION;
        expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after '_Generic'");
        primary_expr->primary.generic_selection.expr = parse_assignment_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_COMMA, "Expected ',' after assignment expression in '_Generic'");
        primary_expr->primary.generic_selection.generic_assoc_list = create_list(GenericAssociation*);
        do {
            append(primary_expr->primary.generic_selection.generic_assoc_list, parse_generic_association(parser));
        } while (match(parser, TOKEN_SYMBOL, SYMBOL_COMMA));
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after generic association list in '_Generic'");
    } else {
        parser_error("Expected primary expression", t);
        return NULL;
    }
    return primary_expr;
}

static PostfixExpression* parse_postfix_suffix(Parser* parser, PostfixExpression* outer) {
    Token* t = peek(parser);
    while (t->type == TOKEN_SYMBOL && (t->value == SYMBOL_L_BRACKET || t->value == SYMBOL_L_PARENTHESIS || t->value == SYMBOL_DOT || t->value == SYMBOL_ARROW || t->value == SYMBOL_INCREMENT || t->value == SYMBOL_DECREMENT)) {
        PostfixExpression* postfix_expr = create_struct(PostfixExpression);
        postfix_expr->token = t;
        if (match(parser, TOKEN_SYMBOL, SYMBOL_L_BRACKET)) {
            postfix_expr->expr_type = POSTFIX_ARRAY_ACCESS;
            postfix_expr->expr.array_access.postfix_expr = outer;
            postfix_expr->expr.array_access.index_expr = parse_expression(parser);
            expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACKET, "Expected ']' after array index expression");
        } else if (match(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS)) {
            postfix_expr->expr_type = POSTFIX_FUNC_CALL;
            postfix_expr->expr.func_call.postfix_expr = outer;
            postfix_expr->expr.func_call.args = create_list(AssignmentExpression*);
            if (!check(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS)) {
                do {
                    append(postfix_expr->expr.func_call.args, parse_assignment_expression(parser));
                } while (match(parser, TOKEN_SYMBOL, SYMBOL_COMMA));
            }
            expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after function call arguments");
        } else if (match(parser, TOKEN_SYMBOL, SYMBOL_DOT) || match(parser, TOKEN_SYMBOL, SYMBOL_ARROW) || match(parser, TOKEN_SYMBOL, SYMBOL_INCREMENT) || match(parser, TOKEN_SYMBOL, SYMBOL_DECREMENT)) {
            postfix_expr->expr_type = POSTFIX_OP;
            postfix_expr->expr.postfix_op.postfix_expr = outer;
            if (t->value == SYMBOL_DOT)
                postfix_expr->expr.postfix_op.op_type = POSTFIX_MEMBER_ACCESS;
            else if (t->value == SYMBOL_ARROW)
                postfix_expr->expr.postfix_op.op_type = POSTFIX_MEMBER_ACCESS_PTR;
            else if (t->value == SYMBOL_INCREMENT)
                postfix_expr->expr.postfix_op.op_type = POSTFIX_INCREMENT;
            else if (t->value == SYMBOL_DECREMENT)
                postfix_expr->expr.postfix_op.op_type = POSTFIX_DECREMENT;
            postfix_expr->expr.postfix_op.identifier = NULL;
            if (t->value == SYMBOL_DOT || t->value == SYMBOL_ARROW) {
                t = expect(parser, TOKEN_IDENTIFIER, NULL, "Expected identifier after '.' or '->'");
                postfix_expr->expr.postfix_op.identifier = t;
            }
        } else break;
        outer = postfix_expr;
        t = peek(parser);
    }
    return outer;
}

static InitializerItem* parse_initializer_item(Parser* parser);
static PostfixExpression* parse_compound_literal(Parser* parser, TypeName* type_name) {
    Token* t = get(parser);  // consume '{'
    PostfixExpression* compound_literal = create_struct(PostfixExpression);
    *compound_literal = (PostfixExpression){.token = t, .expr_type = POSTFIX_COMPOUND_LITERAL, .expr.compound_literal = {.type_name = type_name, .initializer_list = create_list(InitializerItem*)}};
    do {
        if (check(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE))
            break;
        append(compound_literal->expr.compound_literal.initializer_list, parse_initializer_item(parser));
    } while (match(parser, TOKEN_SYMBOL, SYMBOL_COMMA));
    expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE, "Expected ',' or '}' in initializer list");
    if (list_empty(compound_literal->expr.compound_literal.initializer_list))
        parser_warn("ISO C forbids empty initializer braces", t);
    return parse_postfix_suffix(parser, compound_literal);
}

static PostfixExpression* parse_postfix_expression(Parser* parser) {
    if (check(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS) && is_type_start(parser, peek2(parser))) {
        get(parser);  // consume '('
        TypeName* type_name = parse_type_name(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after type name");
        if (check(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
            return parse_compound_literal(parser, type_name);
        } else {
            parser_error("Expected '{' after type name for compound literal", peek(parser));
            return NULL;
        }
    } else {
        PostfixExpression* postfix_expr = create_struct(PostfixExpression);
        postfix_expr->token = peek(parser);
        postfix_expr->expr_type = POSTFIX_PRIMARY;
        postfix_expr->expr.primary_expr = parse_primary_expression(parser);
        return parse_postfix_suffix(parser, postfix_expr);
    }
}

static CastExpression* parse_cast_expression(Parser* parser);
static UnaryExpression* parse_unary_expression(Parser* parser) {
    Token* t = peek(parser);
    UnaryExpression* unary_expr = create_struct(UnaryExpression);
    unary_expr->token = t;
    if (match(parser, TOKEN_SYMBOL, SYMBOL_INCREMENT) || match(parser, TOKEN_SYMBOL, SYMBOL_DECREMENT)) {
        unary_expr->expr_type = UNARY_PREFIX;
        unary_expr->expr.prefix.op = t->value;
        unary_expr->expr.prefix.unary_expr = parse_unary_expression(parser);
    } else if (t->type == TOKEN_SYMBOL && (t->value == SYMBOL_BITWISE_AND || t->value == SYMBOL_MUL || t->value == SYMBOL_ADD || t->value == SYMBOL_SUB || t->value == SYMBOL_BITWISE_NOT || t->value == SYMBOL_LOGICAL_NOT)) {
        unary_expr->expr_type = UNARY_UNARY_OP;
        unary_expr->expr.unary_op.op = get(parser)->value;
        unary_expr->expr.unary_op.cast_expr = parse_cast_expression(parser);
    } else if (match(parser, TOKEN_KEYWORD, KEYWORD_ALIGNOF)) {
        unary_expr->expr_type = UNARY_FUNCTION_LIKE;
        unary_expr->expr.function_like.is_sizeof = false;
        expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after '_Alignof'");
        unary_expr->expr.function_like.type_name = parse_type_name(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after type name");
    } else if (match(parser, TOKEN_KEYWORD, KEYWORD_SIZEOF)) {
        if (check(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS) && is_type_start(parser, peek2(parser))) {
            unary_expr->expr_type = UNARY_FUNCTION_LIKE;
            unary_expr->expr.function_like.is_sizeof = true;
            Token* tt = expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after 'sizeof'");
            unary_expr->expr.function_like.type_name = parse_type_name(parser);
            expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after type name");
            if (check(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
                TypeName* type_name = unary_expr->expr.function_like.type_name;
                unary_expr->expr_type = UNARY_PREFIX;
                unary_expr->expr.prefix.op = KEYWORD_SIZEOF;
                unary_expr->expr.prefix.unary_expr = create_struct(UnaryExpression);
                *unary_expr->expr.prefix.unary_expr = (UnaryExpression){.token = tt, .expr_type = UNARY_POSTFIX, .expr.postfix = parse_compound_literal(parser, type_name)};
            }
        } else {
            unary_expr->expr_type = UNARY_PREFIX;
            unary_expr->expr.prefix.op = KEYWORD_SIZEOF;
            unary_expr->expr.prefix.unary_expr = parse_unary_expression(parser);
        }
    } else {
        unary_expr->expr_type = UNARY_POSTFIX;
        unary_expr->expr.postfix = parse_postfix_expression(parser);
    }
    return unary_expr;
}

static CastExpression* parse_cast_expression(Parser* parser) {
    Token* t = peek(parser);
    CastExpression* cast_expr = create_struct(CastExpression);
    cast_expr->token = t;
    if (check(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS) && is_type_start(parser, peek2(parser))) {
        t = get(parser);  // consume '('
        TypeName* type_name = parse_type_name(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after type name");
        if (check(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
            PostfixExpression* postfix_expr = parse_compound_literal(parser, type_name);
            UnaryExpression* unary_expr = create_struct(UnaryExpression);
            *unary_expr = (UnaryExpression){.token = t, .expr.postfix = postfix_expr, .expr_type = UNARY_POSTFIX};
            cast_expr->is_cast = false;
            cast_expr->expr.unary_expr = unary_expr;
        } else {
            cast_expr->is_cast = true;
            cast_expr->expr.cast.cast_expr = parse_cast_expression(parser);
            cast_expr->expr.cast.type_name = type_name;
        }
    } else {
        cast_expr->is_cast = false;
        cast_expr->expr.unary_expr = parse_unary_expression(parser);
    }
    return cast_expr;
}

static BinaryExpression* parse_binary_expression(Parser* parser, int min_precedence) {
    BinaryExpression* left = create_struct(BinaryExpression);
    *left = (BinaryExpression){.token = peek(parser), .is_cast = true, .expr.cast = parse_cast_expression(parser)};
    while (true) {
        Token* op = peek(parser);
        int precedence = binary_operator_precedence(op);
        if (precedence <= min_precedence) break;
        get(parser);  // consume operator
        BinaryExpression* right = parse_binary_expression(parser, precedence);
        BinaryExpression* node = create_struct(BinaryExpression);
        *node = (BinaryExpression){.token = op, .is_cast = false, .expr.binary = {.op = op->value, .left = left, .right = right}};
        left = node;
    }
    return left;
}

static ConditionalExpression* parse_conditional_expression(Parser* parser) {
    ConditionalExpression* cond_expr = create_struct(ConditionalExpression);
    cond_expr->token = peek(parser);
    cond_expr->true_expr = NULL;
    cond_expr->false_expr = NULL;
    cond_expr->binary_expr = parse_binary_expression(parser, 0);
    if (match(parser, TOKEN_SYMBOL, SYMBOL_QUESTION)) {
        cond_expr->true_expr = parse_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_COLON, "Expected ':' in conditional expression");
        cond_expr->false_expr = parse_conditional_expression(parser);
    }
    return cond_expr;
}

static AssignmentExpression* parse_assignment_expression(Parser* parser) {
    ConditionalExpression* cond_expr = parse_conditional_expression(parser);
    AssignmentExpression* assign_expr = create_struct(AssignmentExpression);
    Token* t = peek(parser);
    if (t->type == TOKEN_SYMBOL && (t->value == SYMBOL_ASSIGN || t->value == SYMBOL_MUL_ASSIGN || t->value == SYMBOL_DIV_ASSIGN || t->value == SYMBOL_MOD_ASSIGN || t->value == SYMBOL_ADD_ASSIGN || t->value == SYMBOL_SUB_ASSIGN || t->value == SYMBOL_L_SHIFT_ASSIGN || t->value == SYMBOL_R_SHIFT_ASSIGN || t->value == SYMBOL_AND_ASSIGN || t->value == SYMBOL_XOR_ASSIGN || t->value == SYMBOL_OR_ASSIGN)) {
        t = get(parser);  // consume assignment operator
        if (cond_expr->false_expr != NULL || cond_expr->true_expr != NULL) {
            parser_error("Not an assignable expression", cond_expr->token);
            return NULL;
        }
        BinaryExpression* binary_expr = cond_expr->binary_expr;
        if (!binary_expr->is_cast) {
            parser_error("Not an assignable expression", binary_expr->token);
            return NULL;
        }
        CastExpression* cast_expr = binary_expr->expr.cast;
        if (cast_expr->is_cast) {
            parser_error("Not an assignable expression", cast_expr->token);
            return NULL;
        }
        UnaryExpression* unary_expr = cast_expr->expr.unary_expr;
        *assign_expr = (AssignmentExpression){.token = t, .is_conditional = false, .expr.binary = {.left = unary_expr, .right = parse_assignment_expression(parser), .op = t->value}};
    } else
        *assign_expr = (AssignmentExpression){.token = cond_expr->token, .is_conditional = true, .expr.cond_expr = cond_expr};
    return assign_expr;
}

static list(AssignmentExpression*) parse_expression(Parser* parser) {
    list(AssignmentExpression*) expr_list = create_list(AssignmentExpression*);
    do {
        append(expr_list, parse_assignment_expression(parser));
    } while (match(parser, TOKEN_SYMBOL, SYMBOL_COMMA));
    return expr_list;
}

static VarDecl* parse_declaration(Parser* parser, FuncDecl** func_def);
static Statement* parse_statement(Parser* parser);
static list(DeclStmt*) parse_compound_stmt(Parser* parser) {
    list(DeclStmt*) decl_stmts = create_list(DeclStmt*);
    Token* t = peek(parser);
    while (!is_eof(t) && !check(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE)) {
        size_t start_depth = parser->brace_depth;
        DeclStmt* decl_stmt = create_struct(DeclStmt);
        decl_stmt->token = t;
        Token* p = peek2(parser);
        bool is_label = t->type == TOKEN_IDENTIFIER && p->type == TOKEN_SYMBOL && p->value == SYMBOL_COLON;
        if (!is_label && is_declaration_start(parser)) {
            decl_stmt->is_var_decl = true;
            decl_stmt->item.var_decl = parse_declaration(parser, NULL);
        } else {
            decl_stmt->is_var_decl = false;
            decl_stmt->item.statement = parse_statement(parser);
        }
        append(decl_stmts, decl_stmt);
        synchronize(parser, t, start_depth, false);
        t = peek(parser);
    }
    return decl_stmts;
}

static SelectionStatement* parse_selection_stmt(Parser* parser) {
    Token* t = peek(parser);
    SelectionStatement* selection = create_struct(SelectionStatement);
    selection->token = t;
    size_t paren_depth = parser->paren_depth;
    push_new_scope(parser, SCOPE_BLOCK);
    if (match(parser, TOKEN_KEYWORD, KEYWORD_IF)) {
        selection->is_switch = false;
        expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after 'if'");
        selection->selection.if_stmt.cond_expr = parse_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after 'if' condition");
        synchronize_paren(parser, paren_depth);
        selection->selection.if_stmt.then_stmt = parse_statement(parser);
        if (match(parser, TOKEN_KEYWORD, KEYWORD_ELSE))
            selection->selection.if_stmt.else_stmt = parse_statement(parser);
        else
            selection->selection.if_stmt.else_stmt = NULL;
    } else if (match(parser, TOKEN_KEYWORD, KEYWORD_SWITCH)) {
        selection->is_switch = true;
        expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after 'switch'");
        selection->selection.switch_stmt.cond_expr = parse_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after 'switch' condition");
        synchronize_paren(parser, paren_depth);
        selection->selection.switch_stmt.stmt = parse_statement(parser);
    } else assert(false);
    pop_scope(parser);
    return selection;
}

static IterationStatement* parse_iteration_stmt(Parser* parser) {
    Token* t = peek(parser);
    IterationStatement* iteration = create_struct(IterationStatement);
    iteration->token = t;
    size_t paren_depth = parser->paren_depth;
    push_new_scope(parser, SCOPE_BLOCK);
    if (match(parser, TOKEN_KEYWORD, KEYWORD_WHILE)) {
        iteration->loop_type = LOOP_WHILE;
        expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after 'while'");
        iteration->loop.while_stmt.expr = parse_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after 'while' condition");
        synchronize_paren(parser, paren_depth);
        iteration->loop.while_stmt.stmt = parse_statement(parser);
    } else if (match(parser, TOKEN_KEYWORD, KEYWORD_DO)) {
        iteration->loop_type = LOOP_DO_WHILE;
        iteration->loop.while_stmt.stmt = parse_statement(parser);
        expect(parser, TOKEN_KEYWORD, KEYWORD_WHILE, "Expected 'while' after 'do' statement");
        expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after 'while'");
        iteration->loop.while_stmt.expr = parse_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after 'while' condition");
        synchronize_paren(parser, paren_depth);
        expect(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON, "Expected ';' after 'do-while' statement");
    } else if (match(parser, TOKEN_KEYWORD, KEYWORD_FOR)) {
        iteration->loop_type = LOOP_FOR;
        expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after 'for'");
        if (is_declaration_start(parser)) {
            iteration->loop.for_stmt.is_init_decl = true;
            iteration->loop.for_stmt.init.init_decl = parse_declaration(parser, NULL);
        } else {
            iteration->loop.for_stmt.is_init_decl = false;
            iteration->loop.for_stmt.init.init_expr = NULL;
            if (!check(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON))
                iteration->loop.for_stmt.init.init_expr = parse_expression(parser);
            expect(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON, "Expected ';' after 'for' initializer");
        }
        iteration->loop.for_stmt.cond_expr = NULL;
        if (!check(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON))
            iteration->loop.for_stmt.cond_expr = parse_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON, "Expected ';' after 'for' condition");
        iteration->loop.for_stmt.loop_expr = NULL;
        if (!check(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS))
            iteration->loop.for_stmt.loop_expr = parse_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after 'for' increment");
        synchronize_paren(parser, paren_depth);
        iteration->loop.for_stmt.stmt = parse_statement(parser);
    } else assert(false);
    pop_scope(parser);
    return iteration;
}

static JumpStatement* parse_jump_stmt(Parser* parser) {
    Token* t = peek(parser);
    JumpStatement* jump = create_struct(JumpStatement);
    jump->token = t;
    if (match(parser, TOKEN_KEYWORD, KEYWORD_GOTO)) {
        jump->jump_type = JUMP_GOTO;
        jump->jump.identifier = expect(parser, TOKEN_IDENTIFIER, NULL, "Expected identifier after 'goto'");
    } else if (match(parser, TOKEN_KEYWORD, KEYWORD_CONTINUE)) {
        jump->jump_type = JUMP_CONTINUE;
        jump->jump.none = NULL;
    } else if (match(parser, TOKEN_KEYWORD, KEYWORD_BREAK)) {
        jump->jump_type = JUMP_BREAK;
        jump->jump.none = NULL;
    } else if (match(parser, TOKEN_KEYWORD, KEYWORD_RETURN)) {
        jump->jump_type = JUMP_RETURN;
        jump->jump.expr = NULL;
        if (!check(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON))
            jump->jump.expr = parse_expression(parser);
    } else assert(false);
    expect(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON, "Expected ';' after jump statement");
    return jump;
}

static Statement* parse_statement(Parser* parser) {
    Token* t = peek(parser);
    Token* p = peek2(parser);
    Statement* stmt = create_struct(Statement);
    stmt->token = t;
    if (match(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
        // compound
        push_new_scope(parser, SCOPE_BLOCK);
        stmt->stmt_type = STMT_COMPOUND;
        stmt->stmt.compound = parse_compound_stmt(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE, "Expected '}' to close compound statement");
        pop_scope(parser);
    } else if (t->type == TOKEN_KEYWORD && (t->value == KEYWORD_CASE || t->value == KEYWORD_DEFAULT)) {
        // case label or default label
        stmt->stmt_type = STMT_LABELED;
        t = get(parser);  // consume 'case' or 'default'
        stmt->stmt.label = create_struct(LabeledStatement);
        if (t->value == KEYWORD_CASE) {
            *(stmt->stmt.label) = (LabeledStatement){.token = t, .label_type = LABEL_CASE, .label.case_stmt = parse_conditional_expression(parser), .stmt = NULL};
            expect(parser, TOKEN_SYMBOL, SYMBOL_COLON, "Expected ':' after case");
        } else {
            *(stmt->stmt.label) = (LabeledStatement){.token = t, .label_type = LABEL_DEFAULT, .label.none = NULL, .stmt = NULL};
            expect(parser, TOKEN_SYMBOL, SYMBOL_COLON, "Expected ':' after default");
        }
        if (check(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE))
            parser_warn("Label at end of compound statement", peek(parser));
        else
            stmt->stmt.label->stmt = parse_statement(parser);
    } else if (t->type == TOKEN_IDENTIFIER && p->type == TOKEN_SYMBOL && p->value == SYMBOL_COLON) {
        // identifier label
        stmt->stmt_type = STMT_LABELED;
        t = get(parser);  // consume identifier
        get(parser);      // consume ':'
        stmt->stmt.label = create_struct(LabeledStatement);
        *(stmt->stmt.label) = (LabeledStatement){.token = t, .label_type = LABEL_IDENTIFIER, .label.identifier = t, .stmt = NULL};
        if (check(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE))
            parser_warn("Label at end of compound statement", peek(parser));
        else
            stmt->stmt.label->stmt = parse_statement(parser);
    } else if (t->type == TOKEN_KEYWORD && (t->value == KEYWORD_IF || t->value == KEYWORD_SWITCH)) {
        // selection
        stmt->stmt_type = STMT_SELECTION;
        stmt->stmt.selection = parse_selection_stmt(parser);
    } else if (t->type == TOKEN_KEYWORD && (t->value == KEYWORD_FOR || t->value == KEYWORD_DO || t->value == KEYWORD_WHILE)) {
        // iteration
        stmt->stmt_type = STMT_ITERATION;
        stmt->stmt.iteration = parse_iteration_stmt(parser);
    } else if (t->type == TOKEN_KEYWORD && (t->value == KEYWORD_GOTO || t->value == KEYWORD_CONTINUE || t->value == KEYWORD_BREAK || t->value == KEYWORD_RETURN)) {
        // jump
        stmt->stmt_type = STMT_JUMP;
        stmt->stmt.jump = parse_jump_stmt(parser);
    } else {
        // expression
        stmt->stmt_type = STMT_EXPRESSION;
        stmt->stmt.expression = NULL;
        if (!check(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON))
            stmt->stmt.expression = parse_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON, "Expected ';' after expression statement");
    }
    return stmt;
}

static TypeSpec* parse_type_specifier(Parser* parser);
static list(SpecifierQualifier*) parse_spec_qual_list(Parser* parser) {
    Token* t = peek(parser);
    list(SpecifierQualifier*) spec_qual_list = create_list(SpecifierQualifier*);
    bool seen_type = false;
    while (true) {
        t = peek(parser);
        SpecifierQualifier* spec_qual = create_struct(SpecifierQualifier);
        spec_qual->token = t;
        if (is_type_qualifier_start(parser, false)) {
            spec_qual->is_type_spec = false;
            t = get(parser);  // consume type_qualifier
            spec_qual->spec.type_qualifier = t->value;
        } else if (is_type_specifier_start(parser, seen_type)) {
            spec_qual->is_type_spec = true;
            spec_qual->spec.type_spec = parse_type_specifier(parser);
            seen_type = true;
        } else
            break;
        append(spec_qual_list, spec_qual);
    }
    if (list_empty(spec_qual_list)) {
        parser_error("Expected type qualifier or specifier", t);
        return NULL;
    }
    return spec_qual_list;
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

static Declarator* parse_declarator(Parser* parser, bool* is_abs);
static StructDecl* parse_struct_decl(Parser* parser) {
    Token* t = peek(parser);
    StructDecl* struct_decl = create_struct(StructDecl);
    struct_decl->token = t;
    struct_decl->is_static_assert_decl = false;
    if (match(parser, TOKEN_KEYWORD, KEYWORD_STATIC_ASSERT)) {
        struct_decl->is_static_assert_decl = true;
        struct_decl->decl.static_assert_decl = parse_static_assert(parser, t);
    } else {
        list(SpecifierQualifier*) spec_qual_list = parse_spec_qual_list(parser);
        list(StructDeclarator*) struct_declarators = NULL;
        if (!check(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON)) {
            struct_declarators = create_list(StructDeclarator*);
            do {
                t = peek(parser);
                StructDeclarator* struct_declarator = create_struct(StructDeclarator);
                *struct_declarator = (StructDeclarator){.token = t, .declarator = NULL, .constant_expr = NULL};
                if (!check(parser, TOKEN_SYMBOL, SYMBOL_COLON)) {
                    bool is_abs = false;
                    struct_declarator->declarator = parse_declarator(parser, &is_abs);
                    if (is_abs) {
                        parser_error("Expected declarator in struct declaration", struct_declarator->token);
                        return NULL;
                    }
                }
                if (match(parser, TOKEN_SYMBOL, SYMBOL_COLON))
                    struct_declarator->constant_expr = parse_conditional_expression(parser);
                if (struct_declarator->declarator == NULL && struct_declarator->constant_expr == NULL) {
                    parser_error("Expected declarator or bit-field in struct declaration", struct_declarator->token);
                    return NULL;
                }
                append(struct_declarators, struct_declarator);
            } while (match(parser, TOKEN_SYMBOL, SYMBOL_COMMA));
        } else {
            bool has_struct_or_union = false;
            foreach (SpecifierQualifier*, spec_qual, spec_qual_list) {
                if (spec_qual->is_type_spec && spec_qual->spec.type_spec->spec_type == TYPE_SPEC_STRUCT_UNION) {
                    has_struct_or_union = true;
                    goto skip_foreach_in_parse_struct_decl;
                }
            }
        skip_foreach_in_parse_struct_decl:
            if (!has_struct_or_union)
                parser_warn("Declaration does not declare anything", struct_decl->token);
        }
        expect(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON, "Expected ';' after struct declaration");
        struct_decl->decl.general_struct_decl.spec_qual_list = spec_qual_list;
        struct_decl->decl.general_struct_decl.struct_declarators = struct_declarators;
    }
    return struct_decl;
}

static TypeName* parse_type_name(Parser* parser) {
    Token* t = peek(parser);
    TypeName* type_name = create_struct(TypeName);
    type_name->token = t;
    type_name->spec_qual_list = parse_spec_qual_list(parser);
    t = peek(parser);
    if (t->type == TOKEN_IDENTIFIER || (t->type == TOKEN_SYMBOL && (t->value == SYMBOL_MUL || t->value == SYMBOL_L_PARENTHESIS || t->value == SYMBOL_L_BRACKET))) {
        bool is_abs = true;  // allow abstract
        type_name->abs_declarator = parse_declarator(parser, &is_abs);
        if (!is_abs) {
            parser_error("Expected abstract declarator in type name", get_declarator_identifier(type_name->abs_declarator->direct_declarator));
            return NULL;
        }
    }
    return type_name;
}

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
            param_decl->is_abs = true;  // allow abstract
            param_decl->decl = parse_declarator(parser, &param_decl->is_abs);
            if (!param_decl->is_abs)
                add_name(parser, get_declarator_identifier(param_decl->decl->direct_declarator), SYMBOL_KIND_VAR);
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
                    size_t start_depth = parser->brace_depth;
                    if (is_type_start(parser, t) || (t->type == TOKEN_KEYWORD && t->value == KEYWORD_STATIC_ASSERT)) {
                        StructDecl* decl = parse_struct_decl(parser);
                        append(members, decl);
                        synchronize(parser, t, start_depth, false);
                    } else if (check(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE) || is_eof(t))
                        break;
                    else {
                        parser_error("Expected member declaration", t);
                        synchronize(parser, t, start_depth, false);
                    }
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
                        t = get(parser);  // consume identifier
                        Enumerator* enumerator = create_struct(Enumerator);
                        *enumerator = (Enumerator){.token = t, .identifier = t, .constant_expr = NULL};
                        if (match(parser, TOKEN_SYMBOL, SYMBOL_ASSIGN))
                            enumerator->constant_expr = parse_conditional_expression(parser);
                        add_name(parser, t, SYMBOL_KIND_ENUM_CONST);
                        append(enumerators, enumerator);
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

static DirectDeclarator* parse_function_suffix(Parser* parser, DirectDeclarator* inner, Token* t) {
    bool is_variadic = false;
    Scope* scope = create_scope(SCOPE_FUNC_PROTO, parser->current_scope);
    parser->current_scope = scope;
    append(parser->scopes, scope);
    list(ParamDecl*) params = parse_parameter_declarations(parser, &is_variadic);
    parser->current_scope = scope->parent;
    DirectDeclarator* new = create_struct(DirectDeclarator);
    *new = (DirectDeclarator){.token = t, .decl_type = DECLARATOR_FUNC, .decl.func.direct_declarator = inner, .decl.func.param_decls = params, .decl.func.is_variadic = is_variadic, .func_proto_scope = scope};
    return new;
}

// is_abs: in = allow abs, out = result is abs
static DirectDeclarator* parse_direct_declarator(Parser* parser, bool* is_abs) {
    Token* t = peek(parser);
    DirectDeclarator* direct_decl = NULL;
    bool allow_abs = *is_abs;
    *is_abs = true;
    if (match(parser, TOKEN_IDENTIFIER, NULL)) {
        direct_decl = create_struct(DirectDeclarator);
        *direct_decl = (DirectDeclarator){.token = t, .decl_type = DECLARATOR_ID, .decl.identifier = t};
        *is_abs = false;
    } else if (match(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS)) {
        if (allow_abs && (check(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS) || is_declaration_start(parser))) {
            // abs func declarator, e.g. int (int)
            direct_decl = parse_function_suffix(parser, NULL, t);
        } else {
            // parenthesized declarator, e.g. int (*fp)(int)
            bool is_inner_abs = allow_abs;
            direct_decl = create_struct(DirectDeclarator);
            *direct_decl = (DirectDeclarator){.token = t, .decl_type = DECLARATOR_DECL, .decl.declarator = parse_declarator(parser, &is_inner_abs)};
            if (!is_inner_abs) *is_abs = false;
            expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' to close parenthesized declarator");
        }
    }
    while (true) {
        if (match(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS)) {
            direct_decl = parse_function_suffix(parser, direct_decl, t);
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

// is_abs: in = allow abs, out = result is abs
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
                if (is_type_start(parser, peek(parser))) {
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
        Token* decl_t = peek(parser);
        if (decl != NULL) {
            decl_t = decl->token;
            SymbolKind kind = has_typedef(decl_specs) ? SYMBOL_KIND_TYPEDEF : (get_function_declarator(decl, NULL) != NULL ? SYMBOL_KIND_FUNC : SYMBOL_KIND_VAR);
            add_name(parser, get_declarator_identifier(decl->direct_declarator), kind);
        }
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

static VarDecl* parse_declaration(Parser* parser, FuncDecl** func_def) {
    Token* t = peek(parser);
    if (match(parser, TOKEN_KEYWORD, KEYWORD_STATIC_ASSERT)) {
        VarDecl* var_decl = create_struct(VarDecl);
        *var_decl = (VarDecl){.token = t, .is_static_assert_decl = true, .decl.static_assert_decl = parse_static_assert(parser, t)};
        return var_decl;
    }
    list(DeclSpec*) decl_specs = parse_declaration_specifiers(parser);
    if (check(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON))
        return parse_var_decl(parser, decl_specs, NULL, t);

    bool is_abs = false;
    Declarator* decl = parse_declarator(parser, &is_abs);
    if (is_abs) {
        parser_error("Expected identifier in declarator", decl->token);
        return NULL;
    }
    if (check(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
        DirectDeclarator* func_declarator = get_function_declarator(decl, NULL);
        if (func_declarator == NULL)
            parser_error("Expected ';' after declaration (only a function declarator can have a body)", peek(parser));
        else if (func_def == NULL)
            parser_error("Function definition is not allowed here", peek(parser));
        else {
            get(parser);  // consume '{'
            add_name(parser, get_declarator_identifier(decl->direct_declarator), SYMBOL_KIND_FUNC);
            Scope* body = func_declarator->func_proto_scope;
            body->kind = SCOPE_FUNC_BODY;
            parser->current_scope = body;
            list(DeclStmt*) compound = parse_compound_stmt(parser);
            expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE, "Expected '}' at end of function body");
            parser->current_scope = body->parent;
            FuncDecl* func_decl = create_struct(FuncDecl);
            *func_decl = (FuncDecl){.token = t, .decl_specs = decl_specs, .declarator = decl, .body = compound};
            *func_def = func_decl;
        }
        return NULL;
    }
    return parse_var_decl(parser, decl_specs, decl, t);
}

TU* parse_parser(Parser* parser) {
    Token* t = peek(parser);
    TU* tu = create_struct(TU);
    tu->token = t;
    tu->filename = t->filename;
    tu->extern_decls = create_list(ExternDecl*);
    while (!is_eof(t)) {
        size_t start_depth = parser->brace_depth;
        if (match(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON))
            parser_warn("Extra ';' outside of a function", t);
        else {
            FuncDecl* func_decl = NULL;
            VarDecl* var_decl = parse_declaration(parser, &func_decl);
            ExternDecl* extern_decl = NULL;
            extern_decl = create_struct(ExternDecl);
            if (func_decl != NULL)
                *extern_decl = (ExternDecl){.token = t, .decl.func_decl = func_decl, .is_func_decl = true};
            else if (var_decl != NULL)
                *extern_decl = (ExternDecl){.token = t, .decl.var_decl = var_decl, .is_func_decl = false};
            if (func_decl != NULL || var_decl != NULL)
                append(tu->extern_decls, extern_decl);
        }
        synchronize(parser, t, start_depth, true);
        if (peek(parser) == t)
            get(parser);
        t = peek(parser);
    }
    return tu;
}
