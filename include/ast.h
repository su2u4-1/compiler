#ifndef AST_H
#define AST_H

#include "lib.h"

typedef struct AST_StaticAssertDecl AST_StaticAssertDecl;
typedef struct AST_Declarator AST_Declarator;
typedef struct AST_DirectDeclarator AST_DirectDeclarator;
typedef struct AST_TypeSpec AST_TypeSpec;
typedef struct AST_Pointer AST_Pointer;
typedef struct AST_Initializer AST_Initializer;
typedef struct AST_InitializerItem AST_InitializerItem;
typedef struct AST_Statement AST_Statement;
typedef struct AST_Enumerator AST_Enumerator;
typedef struct AST_StructDeclarator AST_StructDeclarator;
typedef struct AST_StructDecl AST_StructDecl;
typedef struct AST_SpecifierQualifier AST_SpecifierQualifier;
typedef struct AST_TypeName AST_TypeName;
typedef struct AST_ParamDecl AST_ParamDecl;
typedef struct AST_Designator AST_Designator;
typedef struct AST_DeclSpec AST_DeclSpec;
typedef struct AST_FuncDecl AST_FuncDecl;
typedef struct AST_InitDecl AST_InitDecl;
typedef struct AST_VarDecl AST_VarDecl;
typedef struct AST_ExternDecl AST_ExternDecl;
typedef struct AST_TU AST_TU;

typedef struct AST_Declarator AST_AbsDeclarator;  // not use identifier

typedef struct AST_LabeledStatement AST_LabeledStatement;
typedef struct AST_SelectionStatement AST_SelectionStatement;
typedef struct AST_IterationStatement AST_IterationStatement;
typedef struct AST_JumpStatement AST_JumpStatement;
typedef struct AST_DeclStmt AST_DeclStmt;

typedef struct AST_AssignmentExpression AST_AssignmentExpression;
typedef struct AST_ConditionalExpression AST_ConditionalExpression;
typedef struct AST_BinaryExpression AST_BinaryExpression;
typedef struct AST_CastExpression AST_CastExpression;
typedef struct AST_UnaryExpression AST_UnaryExpression;
typedef struct AST_PostfixExpression AST_PostfixExpression;
typedef struct AST_PrimaryExpression AST_PrimaryExpression;
typedef struct AST_GenericAssociation AST_GenericAssociation;

struct AST_AssignmentExpression {
    Token* token;
    union {
        AST_ConditionalExpression* cond_expr;
        struct {
            AST_UnaryExpression* left;  // not allow cast expression
            AST_AssignmentExpression* right;
            string op;  // = | *= | /= | %= | += | -= | <<= | >>= | &= | ^= | |=
        } binary;
    } expr;
    bool is_conditional;
};

struct AST_ConditionalExpression {
    Token* token;
    AST_BinaryExpression* binary_expr;
    list(AST_AssignmentExpression*) true_expr;
    AST_ConditionalExpression* false_expr;
};

struct AST_BinaryExpression {
    Token* token;
    union {
        struct {
            string op;  // || | && | | | ^ | & | == | != | < | > | <= | >= | << | >> | + | - | * | / | %
            AST_BinaryExpression* left;
            AST_BinaryExpression* right;
        } binary;
        AST_CastExpression* cast;
    } expr;
    bool is_cast;
};

struct AST_CastExpression {
    Token* token;
    union {
        struct {
            AST_TypeName* type_name;
            AST_CastExpression* cast_expr;
        } cast;
        AST_UnaryExpression* unary_expr;
    } expr;
    bool is_cast;
};

struct AST_UnaryExpression {
    Token* token;
    union {
        struct {
            string op;  // ++ | -- | sizeof
            AST_UnaryExpression* unary_expr;
        } prefix;
        struct {
            string op;  // * | & | + | - | ~ | !
            AST_CastExpression* cast_expr;
        } unary_op;
        struct {
            AST_TypeName* type_name;
            bool is_sizeof;
        } function_like;  // sizeof(typename) | _Alignof(typename)
        AST_PostfixExpression* postfix;
    } expr;
    enum {
        UNARY_PREFIX,
        UNARY_UNARY_OP,
        UNARY_FUNCTION_LIKE,
        UNARY_POSTFIX,
    } expr_type;
};

struct AST_PostfixExpression {
    Token* token;
    union {
        AST_PrimaryExpression* primary_expr;
        struct {
            AST_TypeName* type_name;
            list(AST_InitializerItem*) initializer_list;
        } compound_literal;
        struct {
            AST_PostfixExpression* postfix_expr;
            list(AST_AssignmentExpression*) index_expr;
        } array_access;
        struct {
            AST_PostfixExpression* postfix_expr;
            list(AST_AssignmentExpression*) args;
        } func_call;
        struct {
            AST_PostfixExpression* postfix_expr;
            Token* identifier;
            enum {  // . | -> | ++ | --
                POSTFIX_MEMBER_ACCESS,
                POSTFIX_MEMBER_ACCESS_PTR,
                POSTFIX_INCREMENT,
                POSTFIX_DECREMENT,
            } op_type;
        } postfix_op;
    } expr;
    enum {
        POSTFIX_PRIMARY,
        POSTFIX_COMPOUND_LITERAL,
        POSTFIX_ARRAY_ACCESS,
        POSTFIX_FUNC_CALL,
        POSTFIX_OP,
    } expr_type;
};

struct AST_PrimaryExpression {
    Token* token;
    union {
        Token* identifier;
        Token* integer_constant;
        Token* character_constant;
        Token* floating_constant;
        Token* string_literal;
        list(AST_AssignmentExpression*) expr;
        struct {
            AST_AssignmentExpression* expr;
            list(AST_GenericAssociation*) generic_assoc_list;
        } generic_selection;
    } primary;
    enum {
        PRIMARY_IDENTIFIER,
        PRIMARY_INTEGER_CONSTANT,
        PRIMARY_CHARACTER_CONSTANT,
        PRIMARY_FLOATING_CONSTANT,
        PRIMARY_STRING_LITERAL,
        PRIMARY_EXPRESSION,
        PRIMARY_GENERIC_SELECTION,
    } primary_type;
};
struct AST_GenericAssociation {
    Token* token;
    AST_TypeName* type_name;  // if type_name == NULL, type_name = "default"
    AST_AssignmentExpression* assignment_expr;
};

struct AST_DeclStmt {
    Token* token;
    union {
        AST_VarDecl* var_decl;
        AST_Statement* statement;
    } item;
    bool is_var_decl;
};

struct AST_LabeledStatement {
    Token* token;
    union {
        Token* identifier;                 // identifier
        AST_ConditionalExpression* case_stmt;  // case constant_expression
        void* none;                        // default
    } label;
    enum {
        LABEL_IDENTIFIER,
        LABEL_CASE,
        LABEL_DEFAULT,
    } label_type;
    AST_Statement* stmt;
};

struct AST_SelectionStatement {
    Token* token;
    union {
        struct {
            list(AST_AssignmentExpression*) cond_expr;
            AST_Statement* then_stmt;
            AST_Statement* else_stmt;
        } if_stmt;
        struct {
            list(AST_AssignmentExpression*) cond_expr;
            AST_Statement* stmt;
        } switch_stmt;
    } selection;
    bool is_switch;
};

struct AST_IterationStatement {
    Token* token;
    union {
        struct {
            list(AST_AssignmentExpression*) expr;
            AST_Statement* stmt;
        } while_stmt;  // while and do-while
        struct {
            union {
                list(AST_AssignmentExpression*) init_expr;
                AST_VarDecl* init_decl;
            } init;
            bool is_init_decl;
            list(AST_AssignmentExpression*) cond_expr;
            list(AST_AssignmentExpression*) loop_expr;
            AST_Statement* stmt;
        } for_stmt;  // for
    } loop;
    enum {
        LOOP_WHILE,
        LOOP_DO_WHILE,
        LOOP_FOR,
    } loop_type;
};

struct AST_JumpStatement {
    Token* token;
    union {
        Token* identifier;                 // goto identifier
        list(AST_AssignmentExpression*) expr;  // return [ expression ]
        void* none;                        // continue | break
    } jump;
    enum {
        JUMP_GOTO,
        JUMP_CONTINUE,
        JUMP_BREAK,
        JUMP_RETURN,
    } jump_type;
};

struct AST_Statement {
    Token* token;
    union {
        AST_LabeledStatement* label;
        list(AST_DeclStmt*) compound;
        list(AST_AssignmentExpression*) expression;
        AST_SelectionStatement* selection;
        AST_IterationStatement* iteration;
        AST_JumpStatement* jump;
    } stmt;
    enum {
        STMT_LABELED,
        STMT_COMPOUND,
        STMT_EXPRESSION,
        STMT_SELECTION,
        STMT_ITERATION,
        STMT_JUMP,
    } stmt_type;
};

struct AST_Enumerator {
    Token* token;
    Token* identifier;
    AST_ConditionalExpression* constant_expr;
};

struct AST_StructDeclarator {
    Token* token;
    AST_Declarator* declarator;
    AST_ConditionalExpression* constant_expr;
};

struct AST_StructDecl {
    Token* token;
    union {
        struct {
            list(AST_SpecifierQualifier*) spec_qual_list;
            list(AST_StructDeclarator*) struct_declarators;
        } general_struct_decl;
        AST_StaticAssertDecl* static_assert_decl;
    } decl;
    bool is_static_assert_decl;
};

struct AST_SpecifierQualifier {
    Token* token;
    union {
        AST_TypeSpec* type_spec;
        string type_qualifier;
    } spec;
    bool is_type_spec;
};

struct AST_TypeName {
    Token* token;
    list(AST_SpecifierQualifier*) spec_qual_list;
    AST_AbsDeclarator* abs_declarator;
};

struct AST_ParamDecl {
    Token* token;
    list(AST_DeclSpec*) decl_specs;
    AST_Declarator* decl;
    bool is_abs;
};

struct AST_Pointer {
    Token* token;
    list(string) type_qualifiers;
    AST_Pointer* pointer;
};

struct AST_Designator {
    Token* token;
    union {
        AST_ConditionalExpression* constant_expr;
        Token* identifier;
    } designator;
    bool is_constant_expr;
};

struct AST_InitializerItem {
    Token* token;
    list(AST_Designator*) designation;
    AST_Initializer* initializer;
};
struct AST_Initializer {
    Token* token;
    union {
        AST_AssignmentExpression* assignment_expr;
        list(AST_InitializerItem*) inits;
    } init;
    bool is_assignment_expr;
};

struct AST_TypeSpec {
    Token* token;
    union {
        string keyword_spec;    // "void" | "char" | "short" | "int" | "long" | "float" | "double" | "signed" | "unsigned" | "_Bool" | "_Imaginary" | "_Complex"
        AST_TypeName* atomic_spec;  // atomic_type_specifier
        struct {
            bool is_struct;
            Token* identifier;
            list(AST_StructDecl*) members;
        } struct_union_spec;  // struct_or_union_specifier
        struct {
            Token* identifier;
            list(AST_Enumerator*) enumerators;
        } enum_spec;          // enum_specifier
        Token* typedef_name;  // typedef_name
    } spec;
    enum {
        TYPE_SPEC_KEYWORD,
        TYPE_SPEC_ATOMIC,
        TYPE_SPEC_STRUCT_UNION,
        TYPE_SPEC_ENUM,
        TYPE_SPEC_TYPEDEF_NAME,
    } spec_type;
};

struct AST_DirectDeclarator {
    Token* token;
    union {
        Token* identifier;
        AST_Declarator* declarator;
        struct {
            AST_DirectDeclarator* direct_declarator;
            AST_AssignmentExpression* assignment_expression;
            list(string) type_qualifiers;
            bool is_static;
        } array;
        struct {
            AST_DirectDeclarator* direct_declarator;
            list(AST_ParamDecl*) param_decls;
            bool is_variadic;
        } func;
        struct {
            AST_DirectDeclarator* direct_declarator;
            list(string) type_qualifiers;
            bool has_star;
        } incomplete_array;
    } decl;
    enum {
        DECLARATOR_ID,
        DECLARATOR_DECL,
        DECLARATOR_ARRAY,
        DECLARATOR_FUNC,
        DECLARATOR_INCOMPLETE_ARRAY,
    } decl_type;
    AST_Scope* func_proto_scope;
};
struct AST_Declarator {
    Token* token;
    AST_Pointer* pointer;
    AST_DirectDeclarator* direct_declarator;
};

struct AST_DeclSpec {
    Token* token;
    union {
        string keyword;  // storage_class_specifier | type_qualifier | function_specifier
        struct {
            union {
                AST_TypeName* type_name;
                AST_ConditionalExpression* constant_expression;
            } spec;
            bool is_type_name;
        } alignment;     // alignment_specifier
        AST_TypeSpec* type;  // type_specifier
    } specifier;
    enum {
        SPEC_KEYWORD,
        SPEC_ALIGNMENT,
        SPEC_TYPE_SPEC,
    } specifier_type;
};

struct AST_FuncDecl {
    Token* token;
    list(AST_DeclSpec*) decl_specs;
    AST_Declarator* declarator;
    list(AST_DeclStmt*) body;
};

struct AST_InitDecl {
    Token* token;
    AST_Declarator* declarator;
    AST_Initializer* initializer;
};

struct AST_StaticAssertDecl {
    Token* token;
    AST_ConditionalExpression* expr;
    Token* message;
};

struct AST_VarDecl {
    Token* token;
    union {
        struct {
            list(AST_DeclSpec*) decl_specs;
            list(AST_InitDecl*) init_decls;
        } general_decl;
        AST_StaticAssertDecl* static_assert_decl;
    } decl;
    bool is_static_assert_decl;
};

struct AST_ExternDecl {
    Token* token;
    union {
        AST_FuncDecl* func_decl;
        AST_VarDecl* var_decl;
    } decl;
    bool is_func_decl;
};

struct AST_TU {
    Token* token;
    string filename;
    list(AST_ExternDecl*) extern_decls;
};

#endif  // AST_H
