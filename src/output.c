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

// all output_xxx(FILE* out, T* node, size_t indent) print `Name: {...}` without trailing newline

#define print_indent(indent) \
    for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out)

#define print(indent, str)    \
    do {                      \
        print_indent(indent); \
        fputs(str, out);      \
    } while (0)

#define start(name)                     \
    print(indent, name ": {\n");        \
    if (node == NULL) {                 \
        print(indent + 1, "(null)\n");  \
        print(indent, "}");             \
        return;                         \
    }                                   \
    print(indent + 1, "token: ");       \
    output_one_token(out, node->token); \
    fputs(",\n", out)

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

#define output_list(key, T, fn, lst, level)      \
    do {                                         \
        print(indent + (level), key ": [\n");    \
        foreach (T, item_, (lst))                \
            output_node(fn, item_, (level) + 1); \
        print(indent + (level), "],\n");         \
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
        foreach (string, s_, (lst)) {       \
            write_value(out, s_);           \
            fputs(", ", out);               \
        }                                   \
        fputs("],\n", out);                 \
    } while (0)

static void output_assignment_expression(FILE* out, AssignmentExpression* node, size_t indent);
static void output_conditional_expression(FILE* out, ConditionalExpression* node, size_t indent);
static void output_binary_expression(FILE* out, BinaryExpression* node, size_t indent);
static void output_cast_expression(FILE* out, CastExpression* node, size_t indent);
static void output_unary_expression(FILE* out, UnaryExpression* node, size_t indent);
static void output_postfix_expression(FILE* out, PostfixExpression* node, size_t indent);
static void output_primary_expression(FILE* out, PrimaryExpression* node, size_t indent);
static void output_generic_association(FILE* out, GenericAssociation* node, size_t indent);
static void output_decl_stmt(FILE* out, DeclStmt* node, size_t indent);
static void output_statement(FILE* out, Statement* node, size_t indent);
static void output_struct_decl(FILE* out, StructDecl* node, size_t indent);
static void output_specifier_qualifier(FILE* out, SpecifierQualifier* node, size_t indent);
static void output_type_name(FILE* out, TypeName* node, size_t indent);
static void output_param_decl(FILE* out, ParamDecl* node, size_t indent);
static void output_pointer(FILE* out, Pointer* node, size_t indent);
static void output_initializer_item(FILE* out, InitializerItem* node, size_t indent);
static void output_initializer(FILE* out, Initializer* node, size_t indent);
static void output_type_spec(FILE* out, TypeSpec* node, size_t indent);
static void output_declarator(FILE* out, Declarator* node, size_t indent);
static void output_decl_spec(FILE* out, DeclSpec* node, size_t indent);
static void output_static_assert_decl(FILE* out, StaticAssertDecl* node, size_t indent);
static void output_var_decl(FILE* out, VarDecl* node, size_t indent);

static void output_assignment_expression(FILE* out, AssignmentExpression* node, size_t indent) {
    start("AssignmentExpression");
    output_bool("is_conditional", node->is_conditional, 1);
    if (node->is_conditional) {
        output_node(output_conditional_expression, node->expr.cond_expr, 1);
    } else {
        print(indent + 1, "binary: {\n");
        output_str("op", node->expr.binary.op, 2);
        output_node(output_unary_expression, node->expr.binary.left, 2);
        output_node(output_assignment_expression, node->expr.binary.right, 2);
        print(indent + 1, "},\n");
    }
    print(indent, "}");
}

static void output_conditional_expression(FILE* out, ConditionalExpression* node, size_t indent) {
    start("ConditionalExpression");
    output_node(output_binary_expression, node->binary_expr, 1);
    output_list("true_expr", AssignmentExpression*, output_assignment_expression, node->true_expr, 1);
    output_keyed("false_expr", output_conditional_expression, node->false_expr, 1);
    print(indent, "}");
}

static void output_binary_expression(FILE* out, BinaryExpression* node, size_t indent) {
    start("BinaryExpression");
    output_bool("is_cast", node->is_cast, 1);
    if (node->is_cast) {
        output_node(output_cast_expression, node->expr.cast, 1);
    } else {
        print(indent + 1, "binary: {\n");
        output_str("op", node->expr.binary.op, 2);
        output_keyed("left", output_binary_expression, node->expr.binary.left, 2);
        output_keyed("right", output_binary_expression, node->expr.binary.right, 2);
        print(indent + 1, "},\n");
    }
    print(indent, "}");
}

static void output_cast_expression(FILE* out, CastExpression* node, size_t indent) {
    start("CastExpression");
    output_bool("is_cast", node->is_cast, 1);
    if (node->is_cast) {
        print(indent + 1, "cast: {\n");
        output_node(output_type_name, node->expr.cast.type_name, 2);
        output_node(output_cast_expression, node->expr.cast.cast_expr, 2);
        print(indent + 1, "},\n");
    } else {
        output_node(output_unary_expression, node->expr.unary_expr, 1);
    }
    print(indent, "}");
}

static void output_unary_expression(FILE* out, UnaryExpression* node, size_t indent) {
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
        print(indent + 1, "prefix: {\n");
        output_str("op", node->expr.prefix.op, 2);
        output_node(output_unary_expression, node->expr.prefix.unary_expr, 2);
        print(indent + 1, "},\n");
    } else if (node->expr_type == UNARY_UNARY_OP) {
        print(indent + 1, "unary_op: {\n");
        output_str("op", node->expr.unary_op.op, 2);
        output_node(output_cast_expression, node->expr.unary_op.cast_expr, 2);
        print(indent + 1, "},\n");
    } else if (node->expr_type == UNARY_FUNCTION_LIKE) {
        print(indent + 1, "function_like: {\n");
        output_bool("is_sizeof", node->expr.function_like.is_sizeof, 2);
        output_node(output_type_name, node->expr.function_like.type_name, 2);
        print(indent + 1, "},\n");
    } else if (node->expr_type == UNARY_POSTFIX) {
        output_node(output_postfix_expression, node->expr.postfix, 1);
    }
    print(indent, "}");
}

static void output_postfix_expression(FILE* out, PostfixExpression* node, size_t indent) {
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

    if (node->expr_type == POSTFIX_PRIMARY) {
        output_node(output_primary_expression, node->expr.primary_expr, 1);
    } else if (node->expr_type == POSTFIX_COMPOUND_LITERAL) {
        print(indent + 1, "compound_literal: {\n");
        output_node(output_type_name, node->expr.compound_literal.type_name, 2);
        output_list("initializer_list", InitializerItem*, output_initializer_item, node->expr.compound_literal.initializer_list, 2);
        print(indent + 1, "},\n");
    } else if (node->expr_type == POSTFIX_ARRAY_ACCESS) {
        print(indent + 1, "array_access: {\n");
        output_node(output_postfix_expression, node->expr.array_access.postfix_expr, 2);
        output_list("index_expr", AssignmentExpression*, output_assignment_expression, node->expr.array_access.index_expr, 2);
        print(indent + 1, "},\n");
    } else if (node->expr_type == POSTFIX_FUNC_CALL) {
        print(indent + 1, "func_call: {\n");
        output_node(output_postfix_expression, node->expr.func_call.postfix_expr, 2);
        output_list("args", AssignmentExpression*, output_assignment_expression, node->expr.func_call.args, 2);
        print(indent + 1, "},\n");
    } else if (node->expr_type == POSTFIX_OP) {
        print(indent + 1, "postfix_op: {\n");
        print(indent + 2, "op_type: ");
        switch (node->expr.postfix_op.op_type) {
            case POSTFIX_MEMBER_ACCESS: fputs("POSTFIX_MEMBER_ACCESS,\n", out); break;
            case POSTFIX_MEMBER_ACCESS_PTR: fputs("POSTFIX_MEMBER_ACCESS_PTR,\n", out); break;
            case POSTFIX_INCREMENT: fputs("POSTFIX_INCREMENT,\n", out); break;
            case POSTFIX_DECREMENT: fputs("POSTFIX_DECREMENT,\n", out); break;
            default: fputs("unknown,\n", out); break;
        }
        output_token("identifier", node->expr.postfix_op.identifier, 2);
        output_node(output_postfix_expression, node->expr.postfix_op.postfix_expr, 2);
        print(indent + 1, "},\n");
    }
    print(indent, "}");
}

static void output_primary_expression(FILE* out, PrimaryExpression* node, size_t indent) {
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
            output_list("expr", AssignmentExpression*, output_assignment_expression, node->primary.expr, 1);
            break;
        case PRIMARY_GENERIC_SELECTION:
            print(indent + 1, "generic_selection: {\n");
            output_node(output_assignment_expression, node->primary.generic_selection.expr, 2);
            output_list("generic_assoc_list", GenericAssociation*, output_generic_association, node->primary.generic_selection.generic_assoc_list, 2);
            print(indent + 1, "},\n");
            break;
        default: break;
    }
    print(indent, "}");
}

static void output_generic_association(FILE* out, GenericAssociation* node, size_t indent) {
    start("GenericAssociation");
    if (node->type_name == NULL)
        print(indent + 1, "type_name: default,\n");
    else
        output_node(output_type_name, node->type_name, 1);
    output_node(output_assignment_expression, node->assignment_expr, 1);
    print(indent, "}");
}

static void output_decl_stmt(FILE* out, DeclStmt* node, size_t indent) {
    start("DeclStmt");
    output_bool("is_var_decl", node->is_var_decl, 1);
    if (node->is_var_decl)
        output_node(output_var_decl, node->item.var_decl, 1);
    else
        output_node(output_statement, node->item.statement, 1);
    print(indent, "}");
}

static void output_labeled_statement(FILE* out, LabeledStatement* node, size_t indent) {
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
    print(indent, "}");
}

static void output_selection_statement(FILE* out, SelectionStatement* node, size_t indent) {
    start("SelectionStatement");
    output_bool("is_switch", node->is_switch, 1);
    if (node->is_switch) {
        print(indent + 1, "switch_stmt: {\n");
        output_list("cond_expr", AssignmentExpression*, output_assignment_expression, node->selection.switch_stmt.cond_expr, 2);
        output_node(output_statement, node->selection.switch_stmt.stmt, 2);
        print(indent + 1, "},\n");
    } else {
        print(indent + 1, "if_stmt: {\n");
        output_list("cond_expr", AssignmentExpression*, output_assignment_expression, node->selection.if_stmt.cond_expr, 2);
        output_keyed("then_stmt", output_statement, node->selection.if_stmt.then_stmt, 2);
        output_keyed("else_stmt", output_statement, node->selection.if_stmt.else_stmt, 2);
        print(indent + 1, "},\n");
    }
    print(indent, "}");
}

static void output_iteration_statement(FILE* out, IterationStatement* node, size_t indent) {
    start("IterationStatement");
    print(indent + 1, "loop_type: ");
    switch (node->loop_type) {
        case LOOP_WHILE: fputs("LOOP_WHILE,\n", out); break;
        case LOOP_DO_WHILE: fputs("LOOP_DO_WHILE,\n", out); break;
        case LOOP_FOR: fputs("LOOP_FOR,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }

    if (node->loop_type == LOOP_WHILE || node->loop_type == LOOP_DO_WHILE) {
        print(indent + 1, "while_stmt: {\n");
        output_list("expr", AssignmentExpression*, output_assignment_expression, node->loop.while_stmt.expr, 2);
        output_node(output_statement, node->loop.while_stmt.stmt, 2);
        print(indent + 1, "},\n");
    } else if (node->loop_type == LOOP_FOR) {
        print(indent + 1, "for_stmt: {\n");
        output_bool("is_init_decl", node->loop.for_stmt.is_init_decl, 2);
        if (node->loop.for_stmt.is_init_decl)
            output_node(output_var_decl, node->loop.for_stmt.init.init_decl, 2);
        else
            output_list("init_expr", AssignmentExpression*, output_assignment_expression, node->loop.for_stmt.init.init_expr, 2);
        output_list("cond_expr", AssignmentExpression*, output_assignment_expression, node->loop.for_stmt.cond_expr, 2);
        output_list("loop_expr", AssignmentExpression*, output_assignment_expression, node->loop.for_stmt.loop_expr, 2);
        output_node(output_statement, node->loop.for_stmt.stmt, 2);
        print(indent + 1, "},\n");
    }
    print(indent, "}");
}

static void output_jump_statement(FILE* out, JumpStatement* node, size_t indent) {
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
        output_list("expr", AssignmentExpression*, output_assignment_expression, node->jump.expr, 1);
    print(indent, "}");
}

static void output_statement(FILE* out, Statement* node, size_t indent) {
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

    switch (node->stmt_type) {
        case STMT_LABELED: output_node(output_labeled_statement, node->stmt.label, 1); break;
        case STMT_COMPOUND: output_list("compound", DeclStmt*, output_decl_stmt, node->stmt.compound, 1); break;
        case STMT_EXPRESSION:
            output_list("expression", AssignmentExpression*, output_assignment_expression, node->stmt.expression, 1);
            break;
        case STMT_SELECTION: output_node(output_selection_statement, node->stmt.selection, 1); break;
        case STMT_ITERATION: output_node(output_iteration_statement, node->stmt.iteration, 1); break;
        case STMT_JUMP: output_node(output_jump_statement, node->stmt.jump, 1); break;
        default: break;
    }
    print(indent, "}");
}

static void output_enumerator(FILE* out, Enumerator* node, size_t indent) {
    start("Enumerator");
    output_token("identifier", node->identifier, 1);
    output_node(output_conditional_expression, node->constant_expr, 1);
    print(indent, "}");
}

static void output_struct_declarator(FILE* out, StructDeclarator* node, size_t indent) {
    start("StructDeclarator");
    output_node(output_declarator, node->declarator, 1);
    output_node(output_conditional_expression, node->constant_expr, 1);
    print(indent, "}");
}

static void output_struct_decl(FILE* out, StructDecl* node, size_t indent) {
    start("StructDecl");
    output_bool("is_static_assert_decl", node->is_static_assert_decl, 1);
    if (node->is_static_assert_decl) {
        output_node(output_static_assert_decl, node->decl.static_assert_decl, 1);
    } else {
        print(indent + 1, "general_struct_decl: {\n");
        output_list("spec_qual_list", SpecifierQualifier*, output_specifier_qualifier, node->decl.general_struct_decl.spec_qual_list, 2);
        output_list("struct_declarators", StructDeclarator*, output_struct_declarator, node->decl.general_struct_decl.struct_declarators, 2);
        print(indent + 1, "},\n");
    }
    print(indent, "}");
}

static void output_specifier_qualifier(FILE* out, SpecifierQualifier* node, size_t indent) {
    start("SpecifierQualifier");
    output_bool("is_type_spec", node->is_type_spec, 1);
    if (node->is_type_spec)
        output_node(output_type_spec, node->spec.type_spec, 1);
    else
        output_str("type_qualifier", node->spec.type_qualifier, 1);
    print(indent, "}");
}

static void output_type_name(FILE* out, TypeName* node, size_t indent) {
    start("TypeName");
    output_list("spec_qual_list", SpecifierQualifier*, output_specifier_qualifier, node->spec_qual_list, 1);
    output_node(output_declarator, node->abs_declarator, 1);
    print(indent, "}");
}

static void output_type_spec(FILE* out, TypeSpec* node, size_t indent) {
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
        print(indent + 1, "struct_union_spec: {\n");
        output_bool("is_struct", node->spec.struct_union_spec.is_struct, 2);
        output_token("identifier", node->spec.struct_union_spec.identifier, 2);
        output_list("members", StructDecl*, output_struct_decl, node->spec.struct_union_spec.members, 2);
        print(indent + 1, "},\n");
    } else if (node->spec_type == TYPE_SPEC_ENUM) {
        print(indent + 1, "enum_spec: {\n");
        output_token("identifier", node->spec.enum_spec.identifier, 2);
        output_list("enumerators", Enumerator*, output_enumerator, node->spec.enum_spec.enumerators, 2);
        print(indent + 1, "},\n");
    } else if (node->spec_type == TYPE_SPEC_TYPEDEF_NAME) {
        output_token("typedef_name", node->spec.typedef_name, 1);
    }
    print(indent, "}");
}

static void output_param_decl(FILE* out, ParamDecl* node, size_t indent) {
    start("ParamDecl");
    output_bool("is_abs", node->is_abs, 1);
    output_list("decl_specs", DeclSpec*, output_decl_spec, node->decl_specs, 1);
    output_node(output_declarator, node->decl, 1);
    print(indent, "}");
}

static void output_pointer(FILE* out, Pointer* node, size_t indent) {
    start("Pointer");
    output_strs("type_qualifiers", node->type_qualifiers, 1);
    output_node(output_pointer, node->pointer, 1);
    print(indent, "}");
}

static void output_direct_declarator(FILE* out, DirectDeclarator* node, size_t indent) {
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
        print(indent + 1, "array: {\n");
        output_bool("is_static", node->decl.array.is_static, 2);
        output_strs("type_qualifiers", node->decl.array.type_qualifiers, 2);
        output_node(output_assignment_expression, node->decl.array.assignment_expression, 2);
        output_node(output_direct_declarator, node->decl.array.direct_declarator, 2);
        print(indent + 1, "},\n");
    } else if (node->decl_type == DECLARATOR_FUNC) {
        print(indent + 1, "func: {\n");
        output_bool("is_variadic", node->decl.func.is_variadic, 2);
        output_list("param_decls", ParamDecl*, output_param_decl, node->decl.func.param_decls, 2);
        output_node(output_direct_declarator, node->decl.func.direct_declarator, 2);
        print(indent + 1, "},\n");
    } else if (node->decl_type == DECLARATOR_INCOMPLETE_ARRAY) {
        print(indent + 1, "incomplete_array: {\n");
        output_bool("has_star", node->decl.incomplete_array.has_star, 2);
        output_strs("type_qualifiers", node->decl.incomplete_array.type_qualifiers, 2);
        output_node(output_direct_declarator, node->decl.incomplete_array.direct_declarator, 2);
        print(indent + 1, "},\n");
    }
    print(indent, "}");
}

static void output_declarator(FILE* out, Declarator* node, size_t indent) {
    start("Declarator");
    output_node(output_pointer, node->pointer, 1);
    output_node(output_direct_declarator, node->direct_declarator, 1);
    print(indent, "}");
}

static void output_designator(FILE* out, Designator* node, size_t indent) {
    start("Designator");
    output_bool("is_constant_expr", node->is_constant_expr, 1);
    if (node->is_constant_expr)
        output_node(output_conditional_expression, node->designator.constant_expr, 1);
    else
        output_token("identifier", node->designator.identifier, 1);
    print(indent, "}");
}

static void output_initializer_item(FILE* out, InitializerItem* node, size_t indent) {
    start("InitializerItem");
    output_list("designation", Designator*, output_designator, node->designation, 1);
    output_node(output_initializer, node->initializer, 1);
    print(indent, "}");
}

static void output_initializer(FILE* out, Initializer* node, size_t indent) {
    start("Initializer");
    output_bool("is_assignment_expr", node->is_assignment_expr, 1);
    if (node->is_assignment_expr)
        output_node(output_assignment_expression, node->init.assignment_expr, 1);
    else
        output_list("inits", InitializerItem*, output_initializer_item, node->init.inits, 1);
    print(indent, "}");
}

static void output_decl_spec(FILE* out, DeclSpec* node, size_t indent) {
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
        print(indent + 1, "alignment: {\n");
        output_bool("is_type_name", node->specifier.alignment.is_type_name, 2);
        if (node->specifier.alignment.is_type_name)
            output_node(output_type_name, node->specifier.alignment.spec.type_name, 2);
        else
            output_node(output_conditional_expression, node->specifier.alignment.spec.constant_expression, 2);
        print(indent + 1, "},\n");
    } else if (node->specifier_type == SPEC_TYPE_SPEC) {
        output_node(output_type_spec, node->specifier.type, 1);
    }
    print(indent, "}");
}

static void output_func(FILE* out, FuncDecl* node, size_t indent) {
    start("FuncDecl");
    output_list("decl_specs", DeclSpec*, output_decl_spec, node->decl_specs, 1);
    output_node(output_declarator, node->declarator, 1);
    output_list("body", DeclStmt*, output_decl_stmt, node->body, 1);
    print(indent, "}");
}

static void output_init_decl(FILE* out, InitDecl* node, size_t indent) {
    start("InitDecl");
    output_node(output_declarator, node->declarator, 1);
    output_node(output_initializer, node->initializer, 1);
    print(indent, "}");
}

static void output_static_assert_decl(FILE* out, StaticAssertDecl* node, size_t indent) {
    start("StaticAssertDecl");
    output_node(output_conditional_expression, node->expr, 1);
    output_str("message", node->message, 1);
    print(indent, "}");
}

static void output_var_decl(FILE* out, VarDecl* node, size_t indent) {
    start("VarDecl");
    output_bool("is_static_assert_decl", node->is_static_assert_decl, 1);
    if (node->is_static_assert_decl) {
        output_node(output_static_assert_decl, node->decl.static_assert_decl, 1);
    } else {
        print(indent + 1, "general_decl: {\n");
        output_list("decl_specs", DeclSpec*, output_decl_spec, node->decl.general_decl.decl_specs, 2);
        output_list("init_decls", InitDecl*, output_init_decl, node->decl.general_decl.init_decls, 2);
        print(indent + 1, "},\n");
    }
    print(indent, "}");
}

static void output_extern_decl(FILE* out, ExternDecl* node, size_t indent) {
    start("ExternDecl");
    output_bool("is_func_decl", node->is_func_decl, 1);
    if (node->is_func_decl)
        output_node(output_func, node->decl.func_decl, 1);
    else
        output_node(output_var_decl, node->decl.var_decl, 1);
    print(indent, "}");
}

static void output_tu(FILE* out, TU* node, size_t indent) {
    start("TU");
    output_str("filename", node->filename, 1);
    output_list("extern_decls", ExternDecl*, output_extern_decl, node->extern_decls, 1);
    print(indent, "}");
}

void output_ast(string filename, TU* tu) {
    FILE* out = open_file(filename);
    if (out == NULL) return;
    output_tu(out, tu, 0);
    fputc('\n', out);
    fclose(out);
}

void print_ast(string filename, TU* tu) {
    FILE* out = open_file(filename);
    if (out == NULL) return;

    fputs("not complete implemented yet\n", out);
    fclose(out);
}
