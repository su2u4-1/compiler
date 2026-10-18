#ifndef AST_H
#define AST_H

#include "lib.h"

typedef struct StaticAssertDecl StaticAssertDecl;
typedef struct Declarator Declarator;
typedef struct TypeSpec TypeSpec;
typedef struct Pointer Pointer;
typedef struct Initializer Initializer;
typedef struct InitializerItem InitializerItem;
typedef struct Statement Statement;
typedef struct Enumerator Enumerator;
typedef struct StructDeclarator StructDeclarator;
typedef struct StructDecl StructDecl;
typedef struct SpecifierQualifier SpecifierQualifier;
typedef struct TypeName TypeName;
typedef struct ParamDecl ParamDecl;
typedef struct Designator Designator;
typedef struct DeclSpec DeclSpec;
typedef struct FuncDecl FuncDecl;
typedef struct InitDecl InitDecl;
typedef struct VarDecl VarDecl;
typedef struct ExternDecl ExternDecl;
typedef struct TU TU;

typedef struct Declarator AbsDeclarator;  // not use identifier

typedef struct LabeledStatement LabeledStatement;
typedef struct SelectionStatement SelectionStatement;
typedef struct IterationStatement IterationStatement;
typedef struct JumpStatement JumpStatement;
typedef struct DeclStmt DeclStmt;

typedef struct AssignmentExpression AssignmentExpression;
typedef struct ConditionalExpression ConditionalExpression;
typedef struct BinaryExpression BinaryExpression;
typedef struct UnaryExpression UnaryExpression;
typedef struct PostfixExpression PostfixExpression;
typedef struct PrimaryExpression PrimaryExpression;
typedef struct GenericAssociation GenericAssociation;

struct AssignmentExpression {
    union {
        ConditionalExpression* cond_expr;
        struct {
            UnaryExpression* left;  // not allow cast expression
            AssignmentExpression* right;
            string op;  // = | *= | /= | %= | += | -= | <<= | >>= | &= | ^= | |=
        } binary;
    } expr;
    bool is_conditional;
};

struct ConditionalExpression {
    BinaryExpression* binary_expr;
    list(AssignmentExpression*) true_expr;
    ConditionalExpression* false_expr;
};

struct BinaryExpression {
    union {
        struct {
            string op;  // || | && | | | ^ | & | == | != | < | > | <= | >= | << | >> | + | - | * | / | %
            BinaryExpression* left;
            BinaryExpression* right;
        } binary;
        UnaryExpression* unary;
    } expr;
    bool is_unary;
};

struct UnaryExpression {
    union {
        struct {
            string op;  // ++ | -- | sizeof
            UnaryExpression* unary_expr;
        } prefix;
        struct {
            string op;  // * | & | + | - | ~ | !
            list(TypeName*) type_names;
            UnaryExpression* unary_expr;
        } cast;
        struct {
            TypeName* type_name;
            bool is_sizeof;
        } function_like;  // sizeof(typename) | _Alignof(typename)
        PostfixExpression* postfix;
    } expr;
    enum {
        UNARY_PREFIX,
        UNARY_CAST,
        UNARY_FUNCTION_LIKE,
        UNARY_POSTFIX,
    } expr_type;
};

struct PostfixExpression {
    union {
        PrimaryExpression* primary_expr;
        struct {
            TypeName* type_name;
            list(InitializerItem*) initializer_list;
        } compound_literal;
        struct {
            PostfixExpression* postfix_expr;
            list(AssignmentExpression*) index_expr;
        } array_access;
        struct {
            PostfixExpression* postfix_expr;
            list(AssignmentExpression*) args;
        } func_call;
        struct {
            PostfixExpression* postfix_expr;
            string identifier;
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

struct PrimaryExpression {
    union {
        string identifier;
        string integer_constant;
        string character_constant;
        string floating_constant;
        string string_literal;
        list(AssignmentExpression*) expr;
        struct {
            AssignmentExpression* expr;
            list(GenericAssociation*) generic_assoc_list;
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
struct GenericAssociation {
    TypeName* type_name;  // if type_name == NULL, type_name = "default"
    AssignmentExpression* assignment_expr;
};

struct DeclStmt {
    union {
        VarDecl* var_decl;
        Statement* statement;
    } item;
    bool is_var_decl;
};

struct LabeledStatement {
    union {
        string identifier;                 // identifier
        ConditionalExpression* case_stmt;  // case constant_expression
        void* none;                        // default
    } label;
    enum {
        LABEL_IDENTIFIER,
        LABEL_CASE,
        LABEL_DEFAULT,
    } label_type;
    Statement* stmt;
};

struct SelectionStatement {
    union {
        struct {
            list(AssignmentExpression*) cond_expr;
            Statement* then_stmt;
            Statement* else_stmt;
        } if_stmt;
        struct {
            list(AssignmentExpression*) cond_expr;
            Statement* stmt;
        } switch_stmt;
    } selection;
    bool is_switch;
};

struct IterationStatement {
    union {
        struct {
            list(AssignmentExpression*) expr;
            Statement* stmt;
        } while_stmt;  // while and do-while
        struct {
            union {
                list(AssignmentExpression*) init_expr;
                VarDecl* init_decl;
            } init;
            bool is_init_decl;
            list(AssignmentExpression*) cond_expr;
            list(AssignmentExpression*) loop_expr;
            Statement* stmt;
        } for_stmt;  // for
    } loop;
    enum {
        LOOP_WHILE,
        LOOP_DO_WHILE,
        LOOP_FOR,
    } loop_type;
};

struct JumpStatement {
    union {
        string identifier;                 // goto identifier
        list(AssignmentExpression*) expr;  // return [ expression ]
        void* none;                        // continue | break
    } jump;
    enum {
        JUMP_GOTO,
        JUMP_CONTINUE,
        JUMP_BREAK,
        JUMP_RETURN,
    } jump_type;
};

struct Statement {
    union {
        LabeledStatement* label;
        list(DeclStmt*) compound;
        list(AssignmentExpression*) expression;
        SelectionStatement* selection;
        IterationStatement* iteration;
        JumpStatement* jump;
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

struct Enumerator {
    string identifier;
    ConditionalExpression* constant_expr;
};

struct StructDeclarator {
    Declarator* declarator;
    ConditionalExpression* constant_expr;
};
struct StructDecl {
    union {
        struct {
            list(SpecifierQualifier*) spec_qual_list;
            list(StructDeclarator*) struct_declarators;
        } general_struct_decl;
        StaticAssertDecl* static_assert_decl;
    } decl;
    bool is_static_assert_decl;
};

struct SpecifierQualifier {
    union {
        TypeSpec* type_spec;
        string type_qualifier;
    } spec;
    bool is_type_spec;
};

struct TypeName {
    list(SpecifierQualifier*) spec_qual_list;
    AbsDeclarator* abs_declarator;
};

struct ParamDecl {
    list(DeclSpec*) decl_specs;
    Declarator* decl;
    bool is_abs;
};

struct Pointer {
    list(string) type_qualifiers;
    Pointer* pointer;
};

struct Designator {
    union {
        ConditionalExpression* constant_expr;
        string identifier;
    } designator;
    bool is_constant_expr;
};
struct InitializerItem {
    list(Designator*) designation;
    Initializer* initializer;
};
struct Initializer {
    union {
        AssignmentExpression* assignment_expr;
        list(InitializerItem*) inits;
    } init;
    bool is_assignment_expr;
};

struct TypeSpec {
    union {
        string keyword_spec;    // "void" | "char" | "short" | "int" | "long" | "float" | "double" | "signed" | "unsigned" | "_Bool" | "_Imaginary" | "_Complex"
        TypeName* atomic_spec;  // atomic_type_specifier
        struct {
            bool is_struct;
            string identifier;
            list(StructDecl*) members;
        } struct_union_spec;  // struct_or_union_specifier
        struct {
            string identifier;
            list(Enumerator*) enumerators;
        } enum_spec;          // enum_specifier
        string typedef_name;  // typedef_name
    } spec;
    enum {
        TYPE_SPEC_KEYWORD,
        TYPE_SPEC_ATOMIC,
        TYPE_SPEC_STRUCT_UNION,
        TYPE_SPEC_ENUM,
        TYPE_SPEC_TYPEDEF_NAME,
    } spec_type;
};

typedef struct DirectDeclarator DirectDeclarator;
struct DirectDeclarator {
    union {
        string identifier;
        Declarator* declarator;
        struct {
            DirectDeclarator* direct_declarator;
            AssignmentExpression* assignment_expression;
            list(string) type_qualifiers;
            bool is_static;
        } array;
        struct {
            DirectDeclarator* direct_declarator;
            list(ParamDecl*) param_decls;
            bool is_variadic;
        } func;
        struct {
            DirectDeclarator* direct_declarator;
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
};
struct Declarator {
    Pointer* pointer;
    DirectDeclarator* direct_declarator;
};

struct DeclSpec {
    union {
        string keyword_specifier;  // storage_class_specifier | type_qualifier | function_specifier
        struct {
            union {
                TypeName* type_name;
                ConditionalExpression* constant_expression;
            } spec;
            bool is_type_name;
        } alignment_specifier;     // alignment_specifier
        TypeSpec* type_specifier;  // type_specifier
    } specifier;
    enum {
        SPEC_KEYWORD,
        SPEC_ALIGNMENT,
        SPEC_TYPE_SPEC,
    } specifier_type;
};

struct FuncDecl {
    list(DeclSpec*) decl_specs;
    Declarator* declarator;
    list(DeclStmt*) body;
};

struct InitDecl {
    Declarator* declarator;
    Initializer* initializer;
};

struct StaticAssertDecl {
    ConditionalExpression* expr;
    string message;
};

struct VarDecl {
    union {
        struct {
            list(DeclSpec*) decl_specs;
            list(InitDecl*) init_decls;
        } general_decl;
        StaticAssertDecl* static_assert_decl;
    } decl;
    bool is_static_assert_decl;
};

struct ExternDecl {
    union {
        FuncDecl* func_decl;
        VarDecl* var_decl;
    } decl;
    bool is_func_decl;
};

struct TU {
    string filename;
    list(ExternDecl*) extern_decls;
};

#endif  // AST_H
