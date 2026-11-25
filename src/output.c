#include "output.h"

#include "lexer.h"
#include "preprocessor.h"

static FILE* open_file(string filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "[Error] at <output> Failed to open file: %s\n", filename);
        return NULL;
    }
    return file;
}

static void write_value(FILE* out, string value) {
    if (value == NULL) {
        fputs("(null)", out);
        return;
    }
    fputc('`', out);
    for (const char* p = value; *p != '\0'; ++p) {
        switch (*p) {
            case '\n': fputs("\\n", out); break;
            case '\t': fputs("\\t", out); break;
            case '\r': fputs("\\r", out); break;
            default: fputc(*p, out); break;
        }
    }
    fputc('`', out);
}

static void write_spacing(FILE* out, bool first, bool at_line_start, bool space_before, size_t column) {
    if (at_line_start) {
        if (!first) fputc('\n', out);
        for (size_t i = 1; i < column; ++i)
            fputc(' ', out);
    } else if (space_before && !first) {
        fputc(' ', out);
    }
}

void output_pp_tokens(string filename, list(ppToken*) tokens) {
    FILE* out = open_file(filename);
    if (out == NULL) return;
    foreach (ppToken*, token, tokens) {
        switch (token->type) {
            case PP_EOF: fputs("(EOF, ", out); break;
            case PP_IDENTIFIER: fputs("(identifier, ", out); break;
            case PP_NUMBER: fputs("(number, ", out); break;
            case PP_STRING: fputs("(string, ", out); break;
            case PP_CHAR: fputs("(char, ", out); break;
            case PP_SYMBOL: fputs("(symbol, ", out); break;
            case PP_NEWLINE: fputs("(newline, ", out); break;
            case PP_HEADER_NAME: fputs("(header_name, ", out); break;
            case PP_PLACE_MARKER: fputs("(place_marker, ", out); break;
            case PP_OTHER: fputs("(other, ", out); break;
            default: fputs("(unknown, ", out); break;
        }
        fprintf(out, "%zu, %zu, ", token->line, token->column);
        write_value(out, token->value);
        fputs(")\n", out);
    }
    fclose(out);
}

void print_pp_tokens(string filename, list(ppToken*) tokens) {
    FILE* out = open_file(filename);
    if (out == NULL) return;
    bool first = true;
    foreach (ppToken*, token, tokens) {
        if (token->type == PP_EOF) break;
        if (token->type == PP_NEWLINE || token->type == PP_PLACE_MARKER || token->value == NULL) continue;
        write_spacing(out, first, token->at_line_start, token->space_before, token->column);
        fputs(token->value, out);
        first = false;
    }
    fputc('\n', out);
    fclose(out);
}

static void output_one_token(FILE* out, Token* token) {
    if (token == NULL) {
        fputs("(null)", out);
        return;
    }
    switch (token->type) {
        case TOKEN_EOF: fputs("(EOF, ", out); break;
        case TOKEN_IDENTIFIER: fputs("(identifier, ", out); break;
        case TOKEN_INT: fputs("(integer, ", out); break;
        case TOKEN_FLOAT: fputs("(float, ", out); break;
        case TOKEN_STRING: fputs("(string, ", out); break;
        case TOKEN_CHAR: fputs("(char, ", out); break;
        case TOKEN_SYMBOL: fputs("(symbol, ", out); break;
        case TOKEN_KEYWORD: fputs("(keyword, ", out); break;
        case TOKEN_COMMENT: fputs("(comment, ", out); break;
        case TOKEN_SYNTAX_ERROR_NUMBER: fputs("(error number, ", out); break;
        case TOKEN_SYNTAX_ERROR_CHAR: fputs("(error char, ", out); break;
        case TOKEN_SYNTAX_ERROR_STRING: fputs("(error string, ", out); break;
        default: fputs("(unknown, ", out); break;
    }
    fprintf(out, "%zu, %zu, ", token->line, token->column);
    write_value(out, token->value);
    fputc(')', out);
}

void output_tokens(string filename, list(Token*) tokens) {
    FILE* out = open_file(filename);
    if (out == NULL) return;
    foreach (Token*, token, tokens) {
        output_one_token(out, token);
        fputc('\n', out);
    }
    fclose(out);
}

void print_tokens(string filename, list(Token*) tokens) {
    FILE* out = open_file(filename);
    if (out == NULL) return;
    bool first = true;
    foreach (Token*, token, tokens) {
        if (token->type == TOKEN_EOF) break;
        if (token->value == NULL) continue;
        write_spacing(out, first, token->at_line_start, token->space_before, token->column);
        fputs(token->value, out);
        first = false;
    }
    fputc('\n', out);
    fclose(out);
}

// output ast helpers

static Token* parent_token = NULL;

#define print_indent(indent) \
    for (size_t i = 0; i < (indent); ++i) fputc('\t', out)

#define print(indent, str)    \
    do {                      \
        print_indent(indent); \
        fputs(str, out);      \
    } while (0)

#define start(name)                         \
    if (node == NULL) {                     \
        print(indent, name ": null");       \
        return;                             \
    }                                       \
    print(indent, name ": {\n");            \
    Token* saved_token = parent_token;      \
    if (node->token != parent_token) {      \
        print(indent + 1, "token: ");       \
        output_one_token(out, node->token); \
        fputs(",\n", out);                  \
    }                                       \
    parent_token = node->token

#define end()                       \
    do {                            \
        parent_token = saved_token; \
        print(indent, "}");         \
    } while (0)

static bool open_ast_node(FILE* out, const char* name, Token* token, bool is_null, size_t indent) {
    print_indent(indent);
    fputs(name, out);
    if (is_null) {
        fputs(": null", out);
        return false;
    }
    fputs(": {\n", out);
    if (token != parent_token) {
        print(indent + 1, "token: ");
        output_one_token(out, token);
        fputs(",\n", out);
    }
    parent_token = token;
    return true;
}

#define open_node(name, n, level) open_ast_node(out, name, (n) == NULL ? NULL : (n)->token, (n) == NULL, indent + (level))

#define close_node(level)             \
    do {                              \
        parent_token = node->token;   \
        print(indent + (level), "}"); \
    } while (0)

#define pass_through(cond, fn, child) \
    do {                              \
        if (node != NULL && (cond)) { \
            fn(out, (child), indent); \
            return;                   \
        }                             \
    } while (0)

#define output_node(fn, child, level)       \
    do {                                    \
        fn(out, (child), indent + (level)); \
        fputs(",\n", out);                  \
    } while (0)

#define output_keyed(key, fn, child, level)   \
    do {                                      \
        print(indent + (level), key ": {\n"); \
        output_node(fn, child, (level) + 1);  \
        print(indent + (level), "},\n");      \
    } while (0)

#define output_list(key, T, fn, lst, level)     \
    do {                                        \
        print(indent + (level), key ": [\n");   \
        foreach (T, item, (lst))                \
            output_node(fn, item, (level) + 1); \
        print(indent + (level), "],\n");        \
    } while (0)

#define output_bool(key, value, level)                           \
    do {                                                         \
        print_indent(indent + (level));                          \
        fprintf(out, key ": %s,\n", (value) ? "true" : "false"); \
    } while (0)

#define output_str(key, value, level)      \
    do {                                   \
        print(indent + (level), key ": "); \
        write_value(out, (value));         \
        fputs(",\n", out);                 \
    } while (0)

#define output_token(key, tok, level)      \
    do {                                   \
        print(indent + (level), key ": "); \
        output_one_token(out, (tok));      \
        fputs(",\n", out);                 \
    } while (0)

#define output_strs(key, lst, level)        \
    do {                                    \
        print(indent + (level), key ": ["); \
        foreach (string, str, (lst)) {      \
            write_value(out, str);          \
            fputs(", ", out);               \
        }                                   \
        fputs("],\n", out);                 \
    } while (0)

static void output_assignment_expression(FILE* out, AST_AssignmentExpression* node, size_t indent);
static void output_conditional_expression(FILE* out, AST_ConditionalExpression* node, size_t indent);
static void output_binary_expression(FILE* out, AST_BinaryExpression* node, size_t indent);
static void output_cast_expression(FILE* out, AST_CastExpression* node, size_t indent);
static void output_unary_expression(FILE* out, AST_UnaryExpression* node, size_t indent);
static void output_postfix_expression(FILE* out, AST_PostfixExpression* node, size_t indent);
static void output_primary_expression(FILE* out, AST_PrimaryExpression* node, size_t indent);
static void output_decl_stmt(FILE* out, AST_DeclStmt* node, size_t indent);
static void output_statement(FILE* out, AST_Statement* node, size_t indent);
static void output_struct_decl(FILE* out, AST_StructDecl* node, size_t indent);
static void output_specifier_qualifier(FILE* out, AST_SpecifierQualifier* node, size_t indent);
static void output_type_name(FILE* out, AST_TypeName* node, size_t indent);
static void output_pointer(FILE* out, AST_Pointer* node, size_t indent);
static void output_initializer_item(FILE* out, AST_InitializerItem* node, size_t indent);
static void output_initializer(FILE* out, AST_Initializer* node, size_t indent);
static void output_type_spec(FILE* out, AST_TypeSpec* node, size_t indent);
static void output_declarator(FILE* out, AST_Declarator* node, size_t indent);
static void output_decl_spec(FILE* out, AST_DeclSpec* node, size_t indent);
static void output_static_assert_decl(FILE* out, AST_StaticAssertDecl* node, size_t indent);
static void output_var_decl(FILE* out, AST_VarDecl* node, size_t indent);

// output ast functions

static void output_assignment_expression(FILE* out, AST_AssignmentExpression* node, size_t indent) {
    pass_through(node->is_conditional, output_conditional_expression, node->expr.cond_expr);
    start("AssignmentExpression");
    output_str("op", node->expr.binary.op, 1);
    output_keyed("left", output_unary_expression, node->expr.binary.left, 1);
    output_keyed("right", output_assignment_expression, node->expr.binary.right, 1);
    end();
}

static void output_conditional_expression(FILE* out, AST_ConditionalExpression* node, size_t indent) {
    pass_through(node->false_expr == NULL, output_binary_expression, node->binary_expr);
    start("ConditionalExpression");
    output_keyed("cond", output_binary_expression, node->binary_expr, 1);
    output_list("true_expr", AST_AssignmentExpression*, output_assignment_expression, node->true_expr, 1);
    output_keyed("false_expr", output_conditional_expression, node->false_expr, 1);
    end();
}

static void output_binary_expression(FILE* out, AST_BinaryExpression* node, size_t indent) {
    pass_through(node->is_cast, output_cast_expression, node->expr.cast);
    start("BinaryExpression");
    output_str("op", node->expr.binary.op, 1);
    output_keyed("left", output_binary_expression, node->expr.binary.left, 1);
    output_keyed("right", output_binary_expression, node->expr.binary.right, 1);
    end();
}

static void output_cast_expression(FILE* out, AST_CastExpression* node, size_t indent) {
    pass_through(!node->is_cast, output_unary_expression, node->expr.unary_expr);
    start("CastExpression");
    output_node(output_type_name, node->expr.cast.type_name, 1);
    output_node(output_cast_expression, node->expr.cast.cast_expr, 1);
    end();
}

static void output_unary_expression(FILE* out, AST_UnaryExpression* node, size_t indent) {
    pass_through(node->expr_type == UNARY_POSTFIX, output_postfix_expression, node->expr.postfix);
    start("UnaryExpression");
    print(indent + 1, "expr_type: ");
    switch (node->expr_type) {
        case UNARY_PREFIX: fputs("UNARY_PREFIX,\n", out); break;
        case UNARY_UNARY_OP: fputs("UNARY_UNARY_OP,\n", out); break;
        case UNARY_FUNCTION_LIKE: fputs("UNARY_FUNCTION_LIKE,\n", out); break;
        case UNARY_POSTFIX: fputs("UNARY_POSTFIX,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }

    if (node->expr_type == UNARY_PREFIX) {
        output_str("op", node->expr.prefix.op, 1);
        output_node(output_unary_expression, node->expr.prefix.unary_expr, 1);
    } else if (node->expr_type == UNARY_UNARY_OP) {
        output_str("op", node->expr.unary_op.op, 1);
        output_node(output_cast_expression, node->expr.unary_op.cast_expr, 1);
    } else if (node->expr_type == UNARY_FUNCTION_LIKE) {
        output_bool("is_sizeof", node->expr.function_like.is_sizeof, 1);
        output_node(output_type_name, node->expr.function_like.type_name, 1);
    }
    end();
}

static void output_postfix_expression(FILE* out, AST_PostfixExpression* node, size_t indent) {
    pass_through(node->expr_type == POSTFIX_PRIMARY, output_primary_expression, node->expr.primary_expr);
    start("PostfixExpression");
    print(indent + 1, "expr_type: ");
    switch (node->expr_type) {
        case POSTFIX_PRIMARY: fputs("POSTFIX_PRIMARY,\n", out); break;
        case POSTFIX_COMPOUND_LITERAL: fputs("POSTFIX_COMPOUND_LITERAL,\n", out); break;
        case POSTFIX_ARRAY_ACCESS: fputs("POSTFIX_ARRAY_ACCESS,\n", out); break;
        case POSTFIX_FUNC_CALL: fputs("POSTFIX_FUNC_CALL,\n", out); break;
        case POSTFIX_OP: fputs("POSTFIX_OP,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }

    if (node->expr_type == POSTFIX_COMPOUND_LITERAL) {
        output_node(output_type_name, node->expr.compound_literal.type_name, 1);
        output_list("initializer_list", AST_InitializerItem*, output_initializer_item, node->expr.compound_literal.initializer_list, 1);
    } else if (node->expr_type == POSTFIX_ARRAY_ACCESS) {
        output_node(output_postfix_expression, node->expr.array_access.postfix_expr, 1);
        output_list("index_expr", AST_AssignmentExpression*, output_assignment_expression, node->expr.array_access.index_expr, 1);
    } else if (node->expr_type == POSTFIX_FUNC_CALL) {
        output_node(output_postfix_expression, node->expr.func_call.postfix_expr, 1);
        output_list("args", AST_AssignmentExpression*, output_assignment_expression, node->expr.func_call.args, 1);
    } else if (node->expr_type == POSTFIX_OP) {
        print(indent + 1, "op_type: ");
        switch (node->expr.postfix_op.op_type) {
            case POSTFIX_MEMBER_ACCESS: fputs("POSTFIX_MEMBER_ACCESS,\n", out); break;
            case POSTFIX_MEMBER_ACCESS_PTR: fputs("POSTFIX_MEMBER_ACCESS_PTR,\n", out); break;
            case POSTFIX_INCREMENT: fputs("POSTFIX_INCREMENT,\n", out); break;
            case POSTFIX_DECREMENT: fputs("POSTFIX_DECREMENT,\n", out); break;
            default: fputs("unknown,\n", out); break;
        }
        if (node->expr.postfix_op.identifier != NULL)
            output_token("identifier", node->expr.postfix_op.identifier, 1);
        output_node(output_postfix_expression, node->expr.postfix_op.postfix_expr, 1);
    }
    end();
}

static void output_primary_expression(FILE* out, AST_PrimaryExpression* node, size_t indent) {
    start("PrimaryExpression");
    print(indent + 1, "primary_type: ");
    switch (node->primary_type) {
        case PRIMARY_IDENTIFIER: fputs("PRIMARY_IDENTIFIER,\n", out); break;
        case PRIMARY_INTEGER_CONSTANT: fputs("PRIMARY_INTEGER_CONSTANT,\n", out); break;
        case PRIMARY_CHARACTER_CONSTANT: fputs("PRIMARY_CHARACTER_CONSTANT,\n", out); break;
        case PRIMARY_FLOATING_CONSTANT: fputs("PRIMARY_FLOATING_CONSTANT,\n", out); break;
        case PRIMARY_STRING_LITERAL: fputs("PRIMARY_STRING_LITERAL,\n", out); break;
        case PRIMARY_EXPRESSION: fputs("PRIMARY_EXPRESSION,\n", out); break;
        case PRIMARY_GENERIC_SELECTION: fputs("PRIMARY_GENERIC_SELECTION,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }

    switch (node->primary_type) {
        case PRIMARY_IDENTIFIER: output_token("identifier", node->primary.identifier, 1); break;
        case PRIMARY_INTEGER_CONSTANT: output_token("integer_constant", node->primary.integer_constant, 1); break;
        case PRIMARY_CHARACTER_CONSTANT: output_token("character_constant", node->primary.character_constant, 1); break;
        case PRIMARY_FLOATING_CONSTANT: output_token("floating_constant", node->primary.floating_constant, 1); break;
        case PRIMARY_STRING_LITERAL: output_token("string_literal", node->primary.string_literal, 1); break;
        case PRIMARY_EXPRESSION:
            output_list("expr", AST_AssignmentExpression*, output_assignment_expression, node->primary.expr, 1);
            break;
        case PRIMARY_GENERIC_SELECTION:
            output_node(output_assignment_expression, node->primary.generic_selection.expr, 1);
            print(indent + 1, "generic_assoc_list: [\n");
            foreach (AST_GenericAssociation*, assoc, node->primary.generic_selection.generic_assoc_list) {
                if (open_node("GenericAssociation", assoc, 2)) {
                    if (assoc->type_name == NULL)
                        print(indent + 3, "type_name: default,\n");
                    else
                        output_node(output_type_name, assoc->type_name, 3);
                    output_node(output_assignment_expression, assoc->assignment_expr, 3);
                    close_node(2);
                }
                fputs(",\n", out);
            }
            print(indent + 1, "],\n");
            break;
        default: break;
    }
    end();
}

static void output_decl_stmt(FILE* out, AST_DeclStmt* node, size_t indent) {
    pass_through(node->is_var_decl, output_var_decl, node->item.var_decl);
    pass_through(!node->is_var_decl, output_statement, node->item.statement);
    print(indent, "DeclStmt: null");
}

static void output_labeled_statement(FILE* out, AST_LabeledStatement* node, size_t indent) {
    start("LabeledStatement");
    print(indent + 1, "label_type: ");
    switch (node->label_type) {
        case LABEL_IDENTIFIER: fputs("LABEL_IDENTIFIER,\n", out); break;
        case LABEL_CASE: fputs("LABEL_CASE,\n", out); break;
        case LABEL_DEFAULT: fputs("LABEL_DEFAULT,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }

    if (node->label_type == LABEL_IDENTIFIER)
        output_token("identifier", node->label.identifier, 1);
    else if (node->label_type == LABEL_CASE)
        output_node(output_conditional_expression, node->label.case_stmt, 1);
    output_node(output_statement, node->stmt, 1);
    end();
}

static void output_selection_statement(FILE* out, AST_SelectionStatement* node, size_t indent) {
    start("SelectionStatement");
    output_bool("is_switch", node->is_switch, 1);
    if (node->is_switch) {
        output_list("cond_expr", AST_AssignmentExpression*, output_assignment_expression, node->selection.switch_stmt.cond_expr, 1);
        output_node(output_statement, node->selection.switch_stmt.stmt, 1);
    } else {
        output_list("cond_expr", AST_AssignmentExpression*, output_assignment_expression, node->selection.if_stmt.cond_expr, 1);
        output_keyed("then_stmt", output_statement, node->selection.if_stmt.then_stmt, 1);
        output_keyed("else_stmt", output_statement, node->selection.if_stmt.else_stmt, 1);
    }
    end();
}

static void output_iteration_statement(FILE* out, AST_IterationStatement* node, size_t indent) {
    start("IterationStatement");
    print(indent + 1, "loop_type: ");
    switch (node->loop_type) {
        case LOOP_WHILE: fputs("LOOP_WHILE,\n", out); break;
        case LOOP_DO_WHILE: fputs("LOOP_DO_WHILE,\n", out); break;
        case LOOP_FOR: fputs("LOOP_FOR,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }

    if (node->loop_type == LOOP_WHILE || node->loop_type == LOOP_DO_WHILE) {
        output_list("expr", AST_AssignmentExpression*, output_assignment_expression, node->loop.while_stmt.expr, 1);
        output_node(output_statement, node->loop.while_stmt.stmt, 1);
    } else if (node->loop_type == LOOP_FOR) {
        if (node->loop.for_stmt.is_init_decl)
            output_node(output_var_decl, node->loop.for_stmt.init.init_decl, 1);
        else
            output_list("init_expr", AST_AssignmentExpression*, output_assignment_expression, node->loop.for_stmt.init.init_expr, 1);
        output_list("cond_expr", AST_AssignmentExpression*, output_assignment_expression, node->loop.for_stmt.cond_expr, 1);
        output_list("loop_expr", AST_AssignmentExpression*, output_assignment_expression, node->loop.for_stmt.loop_expr, 1);
        output_node(output_statement, node->loop.for_stmt.stmt, 1);
    }
    end();
}

static void output_jump_statement(FILE* out, AST_JumpStatement* node, size_t indent) {
    start("JumpStatement");
    print(indent + 1, "jump_type: ");
    switch (node->jump_type) {
        case JUMP_GOTO: fputs("JUMP_GOTO,\n", out); break;
        case JUMP_CONTINUE: fputs("JUMP_CONTINUE,\n", out); break;
        case JUMP_BREAK: fputs("JUMP_BREAK,\n", out); break;
        case JUMP_RETURN: fputs("JUMP_RETURN,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }

    if (node->jump_type == JUMP_GOTO)
        output_token("identifier", node->jump.identifier, 1);
    else if (node->jump_type == JUMP_RETURN)
        output_list("expr", AST_AssignmentExpression*, output_assignment_expression, node->jump.expr, 1);
    end();
}

static void output_statement(FILE* out, AST_Statement* node, size_t indent) {
    pass_through(node->stmt_type == STMT_LABELED, output_labeled_statement, node->stmt.label);
    pass_through(node->stmt_type == STMT_SELECTION, output_selection_statement, node->stmt.selection);
    pass_through(node->stmt_type == STMT_ITERATION, output_iteration_statement, node->stmt.iteration);
    pass_through(node->stmt_type == STMT_JUMP, output_jump_statement, node->stmt.jump);
    start("Statement");
    print(indent + 1, "stmt_type: ");
    switch (node->stmt_type) {
        case STMT_LABELED: fputs("STMT_LABELED,\n", out); break;
        case STMT_COMPOUND: fputs("STMT_COMPOUND,\n", out); break;
        case STMT_EXPRESSION: fputs("STMT_EXPRESSION,\n", out); break;
        case STMT_SELECTION: fputs("STMT_SELECTION,\n", out); break;
        case STMT_ITERATION: fputs("STMT_ITERATION,\n", out); break;
        case STMT_JUMP: fputs("STMT_JUMP,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }

    if (node->stmt_type == STMT_COMPOUND)
        output_list("compound", AST_DeclStmt*, output_decl_stmt, node->stmt.compound, 1);
    else if (node->stmt_type == STMT_EXPRESSION)
        output_list("expression", AST_AssignmentExpression*, output_assignment_expression, node->stmt.expression, 1);
    end();
}

static void output_struct_decl(FILE* out, AST_StructDecl* node, size_t indent) {
    pass_through(node->is_static_assert_decl, output_static_assert_decl, node->decl.static_assert_decl);
    start("StructDecl");
    output_list("spec_qual_list", AST_SpecifierQualifier*, output_specifier_qualifier, node->decl.general_struct_decl.spec_qual_list, 1);
    print(indent + 1, "struct_declarators: [\n");
    foreach (AST_StructDeclarator*, decl, node->decl.general_struct_decl.struct_declarators) {
        if (open_node("StructDeclarator", decl, 2)) {
            output_node(output_declarator, decl->declarator, 3);
            output_node(output_conditional_expression, decl->constant_expr, 3);
            close_node(2);
        }
        fputs(",\n", out);
    }
    print(indent + 1, "],\n");
    end();
}

static void output_specifier_qualifier(FILE* out, AST_SpecifierQualifier* node, size_t indent) {
    pass_through(node->is_type_spec, output_type_spec, node->spec.type_spec);
    start("SpecifierQualifier");
    output_str("type_qualifier", node->spec.type_qualifier, 1);
    end();
}

static void output_type_name(FILE* out, AST_TypeName* node, size_t indent) {
    start("TypeName");
    output_list("spec_qual_list", AST_SpecifierQualifier*, output_specifier_qualifier, node->spec_qual_list, 1);
    output_node(output_declarator, node->abs_declarator, 1);
    end();
}

static void output_type_spec(FILE* out, AST_TypeSpec* node, size_t indent) {
    start("TypeSpec");
    print(indent + 1, "spec_type: ");
    switch (node->spec_type) {
        case TYPE_SPEC_KEYWORD: fputs("TYPE_SPEC_KEYWORD,\n", out); break;
        case TYPE_SPEC_ATOMIC: fputs("TYPE_SPEC_ATOMIC,\n", out); break;
        case TYPE_SPEC_STRUCT_UNION: fputs("TYPE_SPEC_STRUCT_UNION,\n", out); break;
        case TYPE_SPEC_ENUM: fputs("TYPE_SPEC_ENUM,\n", out); break;
        case TYPE_SPEC_TYPEDEF_NAME: fputs("TYPE_SPEC_TYPEDEF_NAME,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }

    if (node->spec_type == TYPE_SPEC_KEYWORD) {
        output_str("keyword_spec", node->spec.keyword_spec, 1);
    } else if (node->spec_type == TYPE_SPEC_ATOMIC) {
        output_node(output_type_name, node->spec.atomic_spec, 1);
    } else if (node->spec_type == TYPE_SPEC_STRUCT_UNION) {
        output_bool("is_struct", node->spec.struct_union_spec.is_struct, 1);
        output_token("identifier", node->spec.struct_union_spec.identifier, 1);
        output_list("members", AST_StructDecl*, output_struct_decl, node->spec.struct_union_spec.members, 1);
    } else if (node->spec_type == TYPE_SPEC_ENUM) {
        output_token("identifier", node->spec.enum_spec.identifier, 1);
        print(indent + 1, "enumerators: [\n");
        foreach (AST_Enumerator*, enumerator, node->spec.enum_spec.enumerators) {
            if (open_node("Enumerator", enumerator, 2)) {
                output_token("identifier", enumerator->identifier, 3);
                output_node(output_conditional_expression, enumerator->constant_expr, 3);
                close_node(2);
            }
            fputs(",\n", out);
        }
        print(indent + 1, "],\n");
    } else if (node->spec_type == TYPE_SPEC_TYPEDEF_NAME) {
        output_token("typedef_name", node->spec.typedef_name, 1);
    }
    end();
}

static void output_pointer(FILE* out, AST_Pointer* node, size_t indent) {
    start("Pointer");
    output_strs("type_qualifiers", node->type_qualifiers, 1);
    output_node(output_pointer, node->pointer, 1);
    end();
}

static void output_direct_declarator(FILE* out, AST_DirectDeclarator* node, size_t indent) {
    start("DirectDeclarator");
    print(indent + 1, "decl_type: ");
    switch (node->decl_type) {
        case DECLARATOR_ID: fputs("DECLARATOR_ID,\n", out); break;
        case DECLARATOR_DECL: fputs("DECLARATOR_DECL,\n", out); break;
        case DECLARATOR_ARRAY: fputs("DECLARATOR_ARRAY,\n", out); break;
        case DECLARATOR_FUNC: fputs("DECLARATOR_FUNC,\n", out); break;
        case DECLARATOR_INCOMPLETE_ARRAY: fputs("DECLARATOR_INCOMPLETE_ARRAY,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }

    if (node->decl_type == DECLARATOR_ID) {
        output_token("identifier", node->decl.identifier, 1);
    } else if (node->decl_type == DECLARATOR_DECL) {
        output_node(output_declarator, node->decl.declarator, 1);
    } else if (node->decl_type == DECLARATOR_ARRAY) {
        output_bool("is_static", node->decl.array.is_static, 1);
        output_strs("type_qualifiers", node->decl.array.type_qualifiers, 1);
        output_node(output_assignment_expression, node->decl.array.assignment_expression, 1);
        output_node(output_direct_declarator, node->decl.array.direct_declarator, 1);
    } else if (node->decl_type == DECLARATOR_FUNC) {
        output_bool("is_variadic", node->decl.func.is_variadic, 1);
        print(indent + 1, "param_decls: [\n");
        foreach (AST_ParamDecl*, param, node->decl.func.param_decls) {
            if (open_node("ParamDecl", param, 2)) {
                output_bool("is_abs", param->is_abs, 3);
                output_list("decl_specs", AST_DeclSpec*, output_decl_spec, param->decl_specs, 3);
                output_node(output_declarator, param->decl, 3);
                close_node(2);
            }
            fputs(",\n", out);
        }
        print(indent + 1, "],\n");
        output_node(output_direct_declarator, node->decl.func.direct_declarator, 1);
    } else if (node->decl_type == DECLARATOR_INCOMPLETE_ARRAY) {
        output_bool("has_star", node->decl.incomplete_array.has_star, 1);
        output_strs("type_qualifiers", node->decl.incomplete_array.type_qualifiers, 1);
        output_node(output_direct_declarator, node->decl.incomplete_array.direct_declarator, 1);
    }
    end();
}

static void output_declarator(FILE* out, AST_Declarator* node, size_t indent) {
    pass_through(node->pointer == NULL, output_direct_declarator, node->direct_declarator);
    start("Declarator");
    output_node(output_pointer, node->pointer, 1);
    output_node(output_direct_declarator, node->direct_declarator, 1);
    end();
}

static void output_initializer_item(FILE* out, AST_InitializerItem* node, size_t indent) {
    start("InitializerItem");
    print(indent + 1, "designation: [\n");
    foreach (AST_Designator*, designator, node->designation) {
        if (open_node("Designator", designator, 2)) {
            if (designator->is_index)
                output_node(output_conditional_expression, designator->designator.index_expr, 3);
            else
                output_token("identifier", designator->designator.member, 3);
            close_node(2);
        }
        fputs(",\n", out);
    }
    print(indent + 1, "],\n");
    output_node(output_initializer, node->initializer, 1);
    end();
}

static void output_initializer(FILE* out, AST_Initializer* node, size_t indent) {
    pass_through(node->is_assignment_expr, output_assignment_expression, node->init.assignment_expr);
    start("Initializer");
    output_list("inits", AST_InitializerItem*, output_initializer_item, node->init.inits, 1);
    end();
}

static void output_decl_spec(FILE* out, AST_DeclSpec* node, size_t indent) {
    pass_through(node->specifier_type == SPEC_TYPE_SPEC, output_type_spec, node->specifier.type);
    start("DeclSpec");
    print(indent + 1, "specifier_type: ");
    switch (node->specifier_type) {
        case SPEC_KEYWORD: fputs("SPEC_KEYWORD,\n", out); break;
        case SPEC_ALIGNMENT: fputs("SPEC_ALIGNMENT,\n", out); break;
        case SPEC_TYPE_SPEC: fputs("SPEC_TYPE_SPEC,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }

    if (node->specifier_type == SPEC_KEYWORD) {
        output_str("keyword", node->specifier.keyword, 1);
    } else if (node->specifier_type == SPEC_ALIGNMENT) {
        if (node->specifier.alignment.is_type_name)
            output_node(output_type_name, node->specifier.alignment.spec.type_name, 1);
        else
            output_node(output_conditional_expression, node->specifier.alignment.spec.constant_expression, 1);
    }
    end();
}

static void output_static_assert_decl(FILE* out, AST_StaticAssertDecl* node, size_t indent) {
    start("StaticAssertDecl");
    output_node(output_conditional_expression, node->expr, 1);
    output_token("message", node->message, 1);
    end();
}

static void output_var_decl(FILE* out, AST_VarDecl* node, size_t indent) {
    pass_through(node->is_static_assert_decl, output_static_assert_decl, node->decl.static_assert_decl);
    start("VarDecl");
    output_list("decl_specs", AST_DeclSpec*, output_decl_spec, node->decl.general_decl.decl_specs, 1);
    print(indent + 1, "init_decls: [\n");
    foreach (AST_InitDecl*, init_decl, node->decl.general_decl.init_decls) {
        if (open_node("InitDecl", init_decl, 2)) {
            output_node(output_declarator, init_decl->declarator, 3);
            output_node(output_initializer, init_decl->initializer, 3);
            close_node(2);
        }
        fputs(",\n", out);
    }
    print(indent + 1, "],\n");
    end();
}

static void output_tu(FILE* out, AST_TU* node, size_t indent) {
    start("TU");
    output_str("filename", node->filename, 1);
    print(indent + 1, "extern_decls: [\n");
    foreach (AST_ExternDecl*, ext, node->extern_decls) {
        if (ext == NULL) {
            print(indent + 2, "ExternDecl: null");
        } else if (!ext->is_func_decl) {
            output_var_decl(out, ext->decl.var_decl, indent + 2);
        } else {
            AST_FuncDecl* func = ext->decl.func_decl;
            if (open_node("FuncDecl", func, 2)) {
                output_list("decl_specs", AST_DeclSpec*, output_decl_spec, func->decl_specs, 3);
                output_node(output_declarator, func->declarator, 3);
                output_list("body", AST_DeclStmt*, output_decl_stmt, func->body, 3);
                close_node(2);
            }
        }
        fputs(",\n", out);
    }
    print(indent + 1, "],\n");
    end();
}

void output_ast(string filename, AST_TU* tu) {
    FILE* out = open_file(filename);
    if (out == NULL) return;
    output_tu(out, tu, 0);
    fputc('\n', out);
    fclose(out);
}

// print ast helpers

#undef print_indent
#define print_indent(indent) \
    for (size_t i = 0; i < (indent); ++i) fputs("    ", out)

#define check_null(name)                             \
    do {                                             \
        if (node == NULL) {                          \
            fputs("// error " name ": NULL\n", out); \
            return;                                  \
        }                                            \
    } while (0)

#define print_join(T, fn, lst, sep)                        \
    do {                                                   \
        foreach (T, item, (lst)) {                         \
            if (item__n != item__l->head) fputs(sep, out); \
            fn(out, item);                                 \
        }                                                  \
    } while (0)

static void print_assignment_expression(FILE* out, AST_AssignmentExpression* node);
static void print_conditional_expression(FILE* out, AST_ConditionalExpression* node);
static void print_cast_expression(FILE* out, AST_CastExpression* node);
static void print_unary_expression(FILE* out, AST_UnaryExpression* node);
static void print_type_name(FILE* out, AST_TypeName* node);
static void print_type_spec(FILE* out, AST_TypeSpec* node, size_t indent);
static void print_initializer_item(FILE* out, AST_InitializerItem* node);
static void print_initializer(FILE* out, AST_Initializer* node);
static void print_declarator(FILE* out, AST_Declarator* node);
static void print_decl_spec(FILE* out, AST_DeclSpec* node, size_t indent);
static void print_static_assert_decl(FILE* out, AST_StaticAssertDecl* node);
static void print_var_decl(FILE* out, AST_VarDecl* node, size_t indent);
static void print_statement(FILE* out, AST_Statement* node, size_t indent);

// print ast functions

static void print_primary_expression(FILE* out, AST_PrimaryExpression* node) {
    check_null("PrimaryExpression");
    switch (node->primary_type) {
        case PRIMARY_IDENTIFIER: fputs(node->primary.identifier->value, out); break;
        case PRIMARY_INTEGER_CONSTANT: fputs(node->primary.integer_constant->value, out); break;
        case PRIMARY_CHARACTER_CONSTANT: fputs(node->primary.character_constant->value, out); break;
        case PRIMARY_FLOATING_CONSTANT: fputs(node->primary.floating_constant->value, out); break;
        case PRIMARY_STRING_LITERAL: fputs(node->primary.string_literal->value, out); break;
        case PRIMARY_EXPRESSION:
            fputc('(', out);
            print_join(AST_AssignmentExpression*, print_assignment_expression, node->primary.expr, ", ");
            fputc(')', out);
            break;
        case PRIMARY_GENERIC_SELECTION:
            fputs("_Generic(", out);
            print_assignment_expression(out, node->primary.generic_selection.expr);
            fputs(", ", out);
            foreach (AST_GenericAssociation*, assoc, node->primary.generic_selection.generic_assoc_list) {
                if (assoc__n != assoc__l->head) fputs(", ", out);
                if (assoc->type_name == NULL)
                    fputs("default", out);
                else
                    print_type_name(out, assoc->type_name);
                fputs(": ", out);
                print_assignment_expression(out, assoc->assignment_expr);
            }
            fputc(')', out);
            break;
        default: fputs("// error PrimaryExpression: unknown type\n", out); break;
    }
}

static void print_postfix_expression(FILE* out, AST_PostfixExpression* node) {
    check_null("PostfixExpression");
    switch (node->expr_type) {
        case POSTFIX_PRIMARY: print_primary_expression(out, node->expr.primary_expr); break;
        case POSTFIX_COMPOUND_LITERAL:
            fputc('(', out);
            print_type_name(out, node->expr.compound_literal.type_name);
            fputs("){", out);
            print_join(AST_InitializerItem*, print_initializer_item, node->expr.compound_literal.initializer_list, ", ");
            fputc('}', out);
            break;
        case POSTFIX_ARRAY_ACCESS:
            print_postfix_expression(out, node->expr.array_access.postfix_expr);
            fputc('[', out);
            print_join(AST_AssignmentExpression*, print_assignment_expression, node->expr.array_access.index_expr, ", ");
            fputc(']', out);
            break;
        case POSTFIX_FUNC_CALL:
            print_postfix_expression(out, node->expr.func_call.postfix_expr);
            fputc('(', out);
            print_join(AST_AssignmentExpression*, print_assignment_expression, node->expr.func_call.args, ", ");
            fputc(')', out);
            break;
        case POSTFIX_OP:
            print_postfix_expression(out, node->expr.postfix_op.postfix_expr);
            switch (node->expr.postfix_op.op_type) {
                case POSTFIX_MEMBER_ACCESS:
                    fputc('.', out);
                    fputs(node->expr.postfix_op.identifier->value, out);
                    break;
                case POSTFIX_MEMBER_ACCESS_PTR:
                    fputs("->", out);
                    fputs(node->expr.postfix_op.identifier->value, out);
                    break;
                case POSTFIX_INCREMENT: fputs("++", out); break;
                case POSTFIX_DECREMENT: fputs("--", out); break;
                default: fputs("// error PostfixExpression: unknown op\n", out); break;
            }
            break;
        default: fputs("// error PostfixExpression: unknown type\n", out); break;
    }
}

static string unary_leading_op(AST_UnaryExpression* node) {
    if (node == NULL) return NULL;
    if (node->expr_type == UNARY_PREFIX) return node->expr.prefix.op;
    if (node->expr_type == UNARY_UNARY_OP) return node->expr.unary_op.op;
    return NULL;
}

static void print_unary_op(FILE* out, string op, string next_op) {
    fputs(op, out);
    if (strcmp(op, "sizeof") == 0 || (next_op != NULL && next_op[0] == op[0]))
        fputc(' ', out);
}

static void print_unary_expression(FILE* out, AST_UnaryExpression* node) {
    check_null("UnaryExpression");
    switch (node->expr_type) {
        case UNARY_PREFIX:
            print_unary_op(out, node->expr.prefix.op, unary_leading_op(node->expr.prefix.unary_expr));
            print_unary_expression(out, node->expr.prefix.unary_expr);
            break;
        case UNARY_UNARY_OP: {
            AST_CastExpression* cast = node->expr.unary_op.cast_expr;
            print_unary_op(out, node->expr.unary_op.op, (cast != NULL && !cast->is_cast) ? unary_leading_op(cast->expr.unary_expr) : NULL);
            print_cast_expression(out, cast);
            break;
        }
        case UNARY_FUNCTION_LIKE:
            fputs(node->expr.function_like.is_sizeof ? "sizeof(" : "_Alignof(", out);
            print_type_name(out, node->expr.function_like.type_name);
            fputc(')', out);
            break;
        case UNARY_POSTFIX: print_postfix_expression(out, node->expr.postfix); break;
        default: fputs("// error UnaryExpression: unknown type\n", out); break;
    }
}

static void print_cast_expression(FILE* out, AST_CastExpression* node) {
    check_null("CastExpression");
    if (node->is_cast) {
        fputc('(', out);
        print_type_name(out, node->expr.cast.type_name);
        fputc(')', out);
        print_cast_expression(out, node->expr.cast.cast_expr);
    } else {
        print_unary_expression(out, node->expr.unary_expr);
    }
}

static void print_binary_expression(FILE* out, AST_BinaryExpression* node) {
    check_null("BinaryExpression");
    if (node->is_cast) {
        print_cast_expression(out, node->expr.cast);
    } else {
        print_binary_expression(out, node->expr.binary.left);
        fprintf(out, " %s ", node->expr.binary.op);
        print_binary_expression(out, node->expr.binary.right);
    }
}

static void print_conditional_expression(FILE* out, AST_ConditionalExpression* node) {
    check_null("ConditionalExpression");
    print_binary_expression(out, node->binary_expr);
    if (node->false_expr != NULL) {
        fputs(" ? ", out);
        print_join(AST_AssignmentExpression*, print_assignment_expression, node->true_expr, ", ");
        fputs(" : ", out);
        print_conditional_expression(out, node->false_expr);
    }
}

static void print_assignment_expression(FILE* out, AST_AssignmentExpression* node) {
    check_null("AssignmentExpression");
    if (node->is_conditional) {
        print_conditional_expression(out, node->expr.cond_expr);
    } else {
        print_unary_expression(out, node->expr.binary.left);
        fprintf(out, " %s ", node->expr.binary.op);
        print_assignment_expression(out, node->expr.binary.right);
    }
}

static void print_specifier_qualifier(FILE* out, AST_SpecifierQualifier* node, size_t indent) {
    check_null("SpecifierQualifier");
    if (node->is_type_spec)
        print_type_spec(out, node->spec.type_spec, indent);
    else
        fputs(node->spec.type_qualifier, out);
}

static void print_struct_decl(FILE* out, AST_StructDecl* node, size_t indent) {
    check_null("StructDecl");
    if (node->is_static_assert_decl) {
        print_static_assert_decl(out, node->decl.static_assert_decl);
    } else {
        foreach (AST_SpecifierQualifier*, spec, node->decl.general_struct_decl.spec_qual_list) {
            if (spec__n != spec__l->head) fputs(" ", out);
            print_specifier_qualifier(out, spec, indent);
        }
        if (!list_empty(node->decl.general_struct_decl.struct_declarators)) {
            fputc(' ', out);
            foreach (AST_StructDeclarator*, decl, node->decl.general_struct_decl.struct_declarators) {
                if (decl__n != decl__l->head) fputs(", ", out);
                if (decl->declarator != NULL)
                    print_declarator(out, decl->declarator);
                if (decl->constant_expr != NULL) {
                    fputs(decl->declarator != NULL ? " : " : ": ", out);
                    print_conditional_expression(out, decl->constant_expr);
                }
            }
        }
    }
    fputc(';', out);
}

static void print_type_spec(FILE* out, AST_TypeSpec* node, size_t indent) {
    check_null("TypeSpec");
    switch (node->spec_type) {
        case TYPE_SPEC_KEYWORD: fputs(node->spec.keyword_spec, out); break;
        case TYPE_SPEC_ATOMIC:
            fputs("_Atomic(", out);
            print_type_name(out, node->spec.atomic_spec);
            fputc(')', out);
            break;
        case TYPE_SPEC_STRUCT_UNION:
            fputs(node->spec.struct_union_spec.is_struct ? "struct" : "union", out);
            if (node->spec.struct_union_spec.identifier != NULL)
                fprintf(out, " %s", node->spec.struct_union_spec.identifier->value);
            if (node->spec.struct_union_spec.members != NULL) {
                fputs(" {\n", out);
                foreach (AST_StructDecl*, member, node->spec.struct_union_spec.members) {
                    print_indent(indent + 1);
                    print_struct_decl(out, member, indent + 1);
                    fputc('\n', out);
                }
                print(indent, "}");
            }
            break;
        case TYPE_SPEC_ENUM:
            fputs("enum", out);
            if (node->spec.enum_spec.identifier != NULL)
                fprintf(out, " %s", node->spec.enum_spec.identifier->value);
            if (node->spec.enum_spec.enumerators != NULL) {
                fputs(" {\n", out);
                foreach (AST_Enumerator*, enumerator, node->spec.enum_spec.enumerators) {
                    print_indent(indent + 1);
                    fputs(enumerator->identifier->value, out);
                    if (enumerator->constant_expr != NULL) {
                        fputs(" = ", out);
                        print_conditional_expression(out, enumerator->constant_expr);
                    }
                    fputs(",\n", out);
                }
                print(indent, "}");
            }
            break;
        case TYPE_SPEC_TYPEDEF_NAME: fputs(node->spec.typedef_name->value, out); break;
        default: fputs("// error TypeSpec: unknown type\n", out); break;
    }
}

static void print_type_name(FILE* out, AST_TypeName* node) {
    check_null("TypeName");
    foreach (AST_SpecifierQualifier*, spec, node->spec_qual_list) {
        if (spec__n != spec__l->head) fputs(" ", out);
        print_specifier_qualifier(out, spec, 0);
    }
    AST_Declarator* decl = node->abs_declarator;
    if (decl != NULL && (decl->pointer != NULL || decl->direct_declarator != NULL)) {
        fputc(' ', out);
        print_declarator(out, decl);
    }
}

static void print_pointer(FILE* out, AST_Pointer* node) {
    check_null("Pointer");
    fputc('*', out);
    foreach (string, qualifier, node->type_qualifiers)
        fprintf(out, " %s", qualifier);
    if (!list_empty(node->type_qualifiers))
        fputc(' ', out);
    if (node->pointer != NULL)
        print_pointer(out, node->pointer);
}

static void print_array_qualifiers(FILE* out, list(string) qualifiers, bool* need_space) {
    foreach (string, qualifier, qualifiers) {
        if (*need_space) fputc(' ', out);
        fputs(qualifier, out);
        *need_space = true;
    }
}

static void print_direct_declarator(FILE* out, AST_DirectDeclarator* node) {
    check_null("DirectDeclarator");
    bool need_space = false;
    switch (node->decl_type) {
        case DECLARATOR_ID: fputs(node->decl.identifier->value, out); break;
        case DECLARATOR_DECL:
            fputc('(', out);
            print_declarator(out, node->decl.declarator);
            fputc(')', out);
            break;
        case DECLARATOR_ARRAY:
            if (node->decl.array.direct_declarator != NULL)
                print_direct_declarator(out, node->decl.array.direct_declarator);
            fputc('[', out);
            if (node->decl.array.is_static) {
                fputs("static", out);
                need_space = true;
            }
            print_array_qualifiers(out, node->decl.array.type_qualifiers, &need_space);
            if (node->decl.array.assignment_expression != NULL) {
                if (need_space) fputc(' ', out);
                print_assignment_expression(out, node->decl.array.assignment_expression);
            }
            fputc(']', out);
            break;
        case DECLARATOR_FUNC:
            if (node->decl.func.direct_declarator != NULL)
                print_direct_declarator(out, node->decl.func.direct_declarator);
            fputc('(', out);
            foreach (AST_ParamDecl*, param, node->decl.func.param_decls) {
                if (param__n != param__l->head) fputs(", ", out);
                foreach (AST_DeclSpec*, spec, param->decl_specs) {
                    if (spec__n != spec__l->head) fputs(" ", out);
                    print_decl_spec(out, spec, 0);
                }
                if (param->decl != NULL && (param->decl->pointer != NULL || param->decl->direct_declarator != NULL)) {
                    fputc(' ', out);
                    print_declarator(out, param->decl);
                }
            }
            if (node->decl.func.is_variadic)
                fputs(list_empty(node->decl.func.param_decls) ? "..." : ", ...", out);
            fputc(')', out);
            break;
        case DECLARATOR_INCOMPLETE_ARRAY:
            if (node->decl.incomplete_array.direct_declarator != NULL)
                print_direct_declarator(out, node->decl.incomplete_array.direct_declarator);
            fputc('[', out);
            print_array_qualifiers(out, node->decl.incomplete_array.type_qualifiers, &need_space);
            if (node->decl.incomplete_array.has_star)
                fputs(need_space ? " *" : "*", out);
            fputc(']', out);
            break;
        default: fputs("// error DirectDeclarator: unknown type\n", out); break;
    }
}

static void print_declarator(FILE* out, AST_Declarator* node) {
    check_null("Declarator");
    if (node->pointer != NULL)
        print_pointer(out, node->pointer);
    if (node->direct_declarator != NULL)
        print_direct_declarator(out, node->direct_declarator);
}

static void print_initializer_item(FILE* out, AST_InitializerItem* node) {
    check_null("InitializerItem");
    if (!list_empty(node->designation)) {
        foreach (AST_Designator*, designator, node->designation) {
            if (designator->is_index) {
                fputc('[', out);
                print_conditional_expression(out, designator->designator.index_expr);
                fputc(']', out);
            } else {
                fprintf(out, ".%s", designator->designator.member->value);
            }
        }
        fputs(" = ", out);
    }
    print_initializer(out, node->initializer);
}

static void print_initializer(FILE* out, AST_Initializer* node) {
    check_null("Initializer");
    if (node->is_assignment_expr) {
        print_assignment_expression(out, node->init.assignment_expr);
    } else if (list_empty(node->init.inits)) {
        fputs("{}", out);
    } else {
        fputs("{ ", out);
        print_join(AST_InitializerItem*, print_initializer_item, node->init.inits, ", ");
        fputs(" }", out);
    }
}

static void print_decl_spec(FILE* out, AST_DeclSpec* node, size_t indent) {
    check_null("DeclSpec");
    switch (node->specifier_type) {
        case SPEC_KEYWORD: fputs(node->specifier.keyword, out); break;
        case SPEC_ALIGNMENT:
            fputs("_Alignas(", out);
            if (node->specifier.alignment.is_type_name)
                print_type_name(out, node->specifier.alignment.spec.type_name);
            else
                print_conditional_expression(out, node->specifier.alignment.spec.constant_expression);
            fputc(')', out);
            break;
        case SPEC_TYPE_SPEC: print_type_spec(out, node->specifier.type, indent); break;
        default: fputs("// error DeclSpec: unknown type\n", out); break;
    }
}

static void print_static_assert_decl(FILE* out, AST_StaticAssertDecl* node) {
    check_null("StaticAssertDecl");
    fputs("_Static_assert(", out);
    print_conditional_expression(out, node->expr);
    if (node->message != NULL)
        fprintf(out, ", %s", node->message->value);
    fputc(')', out);
}

static void print_var_decl(FILE* out, AST_VarDecl* node, size_t indent) {
    check_null("VarDecl");
    if (node->is_static_assert_decl) {
        print_static_assert_decl(out, node->decl.static_assert_decl);
    } else {
        foreach (AST_DeclSpec*, spec, node->decl.general_decl.decl_specs) {
            if (spec__n != spec__l->head) fputs(" ", out);
            print_decl_spec(out, spec, indent);
        }
        if (!list_empty(node->decl.general_decl.init_decls)) {
            fputc(' ', out);
            foreach (AST_InitDecl*, init_decl, node->decl.general_decl.init_decls) {
                if (init_decl__n != init_decl__l->head) fputs(", ", out);
                print_declarator(out, init_decl->declarator);
                if (init_decl->initializer != NULL) {
                    fputs(" = ", out);
                    print_initializer(out, init_decl->initializer);
                }
            }
        }
    }
    fputc(';', out);
}

static void print_statement_line(FILE* out, AST_Statement* node, size_t indent) {
    if (node != NULL && node->stmt_type == STMT_LABELED && indent > 0)
        print_indent(indent - 1);
    else
        print_indent(indent);
    print_statement(out, node, indent);
}

static void print_decl_stmt(FILE* out, AST_DeclStmt* node, size_t indent) {
    check_null("DeclStmt");
    if (node->is_var_decl) {
        print_indent(indent);
        print_var_decl(out, node->item.var_decl, indent);
    } else {
        print_statement_line(out, node->item.statement, indent);
    }
}

static void print_body(FILE* out, AST_Statement* node, size_t indent) {
    if (node != NULL && node->stmt_type == STMT_COMPOUND) {
        fputc(' ', out);
        print_statement(out, node, indent);
    } else {
        fputc('\n', out);
        print_statement_line(out, node, indent + 1);
    }
}

static void print_statement(FILE* out, AST_Statement* node, size_t indent) {
    check_null("Statement");
    switch (node->stmt_type) {
        case STMT_LABELED: {
            AST_LabeledStatement* label = node->stmt.label;
            if (label->label_type == LABEL_IDENTIFIER) {
                fprintf(out, "%s:", label->label.identifier->value);
            } else if (label->label_type == LABEL_CASE) {
                fputs("case ", out);
                print_conditional_expression(out, label->label.case_stmt);
                fputc(':', out);
            } else {
                fputs("default:", out);
            }
            fputc('\n', out);
            print_statement_line(out, label->stmt, indent);
            break;
        }
        case STMT_COMPOUND:
            fputs("{\n", out);
            foreach (AST_DeclStmt*, item, node->stmt.compound) {
                print_decl_stmt(out, item, indent + 1);
                fputc('\n', out);
            }
            print(indent, "}");
            break;
        case STMT_EXPRESSION:
            print_join(AST_AssignmentExpression*, print_assignment_expression, node->stmt.expression, ", ");
            fputc(';', out);
            break;
        case STMT_SELECTION: {
            AST_SelectionStatement* sel = node->stmt.selection;
            if (sel->is_switch) {
                fputs("switch (", out);
                print_join(AST_AssignmentExpression*, print_assignment_expression, sel->selection.switch_stmt.cond_expr, ", ");
                fputc(')', out);
                print_body(out, sel->selection.switch_stmt.stmt, indent);
                break;
            }
            AST_Statement* then_stmt = sel->selection.if_stmt.then_stmt;
            AST_Statement* else_stmt = sel->selection.if_stmt.else_stmt;
            fputs("if (", out);
            print_join(AST_AssignmentExpression*, print_assignment_expression, sel->selection.if_stmt.cond_expr, ", ");
            fputc(')', out);
            print_body(out, then_stmt, indent);
            if (else_stmt != NULL) {
                if (then_stmt != NULL && then_stmt->stmt_type == STMT_COMPOUND) {
                    fputs(" else", out);
                } else {
                    fputc('\n', out);
                    print(indent, "else");
                }
                if (else_stmt->stmt_type == STMT_SELECTION && !else_stmt->stmt.selection->is_switch) {
                    fputc(' ', out);
                    print_statement(out, else_stmt, indent);
                } else {
                    print_body(out, else_stmt, indent);
                }
            }
            break;
        }
        case STMT_ITERATION: {
            AST_IterationStatement* loop = node->stmt.iteration;
            if (loop->loop_type == LOOP_WHILE) {
                fputs("while (", out);
                print_join(AST_AssignmentExpression*, print_assignment_expression, loop->loop.while_stmt.expr, ", ");
                fputc(')', out);
                print_body(out, loop->loop.while_stmt.stmt, indent);
            } else if (loop->loop_type == LOOP_DO_WHILE) {
                AST_Statement* body = loop->loop.while_stmt.stmt;
                fputs("do", out);
                print_body(out, body, indent);
                if (body != NULL && body->stmt_type == STMT_COMPOUND) {
                    fputc(' ', out);
                } else {
                    fputc('\n', out);
                    print_indent(indent);
                }
                fputs("while (", out);
                print_join(AST_AssignmentExpression*, print_assignment_expression, loop->loop.while_stmt.expr, ", ");
                fputs(");", out);
            } else {
                fputs("for (", out);
                if (loop->loop.for_stmt.is_init_decl) {
                    print_var_decl(out, loop->loop.for_stmt.init.init_decl, indent);
                } else {
                    print_join(AST_AssignmentExpression*, print_assignment_expression, loop->loop.for_stmt.init.init_expr, ", ");
                    fputc(';', out);
                }
                if (!list_empty(loop->loop.for_stmt.cond_expr)) {
                    fputc(' ', out);
                    print_join(AST_AssignmentExpression*, print_assignment_expression, loop->loop.for_stmt.cond_expr, ", ");
                }
                fputc(';', out);
                if (!list_empty(loop->loop.for_stmt.loop_expr)) {
                    fputc(' ', out);
                    print_join(AST_AssignmentExpression*, print_assignment_expression, loop->loop.for_stmt.loop_expr, ", ");
                }
                fputc(')', out);
                print_body(out, loop->loop.for_stmt.stmt, indent);
            }
            break;
        }
        case STMT_JUMP: {
            AST_JumpStatement* jump = node->stmt.jump;
            switch (jump->jump_type) {
                case JUMP_GOTO: fprintf(out, "goto %s;", jump->jump.identifier->value); break;
                case JUMP_CONTINUE: fputs("continue;", out); break;
                case JUMP_BREAK: fputs("break;", out); break;
                case JUMP_RETURN:
                    fputs("return", out);
                    if (!list_empty(jump->jump.expr)) {
                        fputc(' ', out);
                        print_join(AST_AssignmentExpression*, print_assignment_expression, jump->jump.expr, ", ");
                    }
                    fputc(';', out);
                    break;
                default: fputs("// error JumpStatement: unknown type\n", out); break;
            }
            break;
        }
        default: fputs("// error Statement: unknown type\n", out); break;
    }
}

void print_ast(string filename, AST_TU* tu) {
    FILE* out = open_file(filename);
    if (out == NULL) return;
    if (tu == NULL) fputs("// error TU: NULL\n", out);
    foreach (AST_ExternDecl*, decl, tu == NULL ? NULL : tu->extern_decls) {
        if (!decl->is_func_decl) {
            print_var_decl(out, decl->decl.var_decl, 0);
        } else if (decl->decl.func_decl == NULL) {
            fputs("// error FuncDecl: NULL\n", out);
        } else {
            AST_FuncDecl* func = decl->decl.func_decl;
            foreach (AST_DeclSpec*, spec, func->decl_specs) {
                if (spec__n != spec__l->head) fputs(" ", out);
                print_decl_spec(out, spec, 0);
            }
            fputc(' ', out);
            print_declarator(out, func->declarator);
            fputs(" {\n", out);
            foreach (AST_DeclStmt*, stmt, func->body) {
                print_decl_stmt(out, stmt, 1);
                fputc('\n', out);
            }
            fputc('}', out);
        }
        fputc('\n', out);
    }
    fclose(out);
}
