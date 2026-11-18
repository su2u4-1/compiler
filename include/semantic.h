#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "lib.h"

typedef struct IR_Symbol IR_Symbol;
typedef struct IR_Scope IR_Scope;

typedef struct IR_TU IR_TU;
typedef struct IR_ExternDecl IR_ExternDecl;
typedef struct IR_FuncDef IR_FuncDef;
typedef struct IR_FuncProto IR_FuncProto;
typedef struct IR_Decl IR_Decl;
typedef struct IR_Initializer IR_Initializer;
typedef struct IR_Type IR_Type;
typedef struct IR_Param IR_Param;
typedef struct IR_Statement IR_Statement;
typedef struct IR_StructUnion IR_StructUnion;
typedef struct IR_Enum IR_Enum;
typedef struct IR_Expression IR_Expression;
typedef struct IR_EnumItem IR_EnumItem;
typedef struct IR_StructUnionDecl IR_StructUnionDecl;
typedef struct IR_CompoundStatement IR_CompoundStatement;

typedef enum {
    SYMBOL_VAR,
    SYMBOL_FUNC,
    SYMBOL_TYPEDEF,
    SYMBOL_ENUM_CONST,
    SYMBOL_TAG,  // struct / union / enum
    SYMBOL_LABEL,
} IR_SymbolKind;

typedef enum {
    LINKAGE_NONE,      // local var, arg, typedef, enum constant
    LINKAGE_INTERNAL,  // top-level static
    LINKAGE_EXTERNAL,  // global var, func, extern
} IR_Linkage;

struct IR_Symbol {
    Token* token;  // location of first declaration
    string name;
    IR_SymbolKind kind;
    IR_Type* type;
    IR_Linkage linkage;
    bool is_static_storage;
    bool is_register;  // not allow address-of `&`
    bool is_defined;
    bool is_tentative;  // top-level var and not initialized
    intmax_t enum_value;
};

typedef List List_IR_Symbol;

typedef enum {
    SCOPE_FILE,
    SCOPE_BLOCK,
    SCOPE_PROTO,
} IR_ScopeKind;

struct IR_Scope {
    IR_Scope* parent;
    IR_ScopeKind kind;
    list(IR_Symbol*) names;
    list(IR_Symbol*) tags;
};

typedef List List_IR_Initializer;
typedef List List_IR_Statement;
typedef List List_IR_Param;
typedef List List_IR_ExternDecl;
typedef List List_IR_EnumItem;
typedef List List_IR_StructUnionDecl;

struct IR_Expression {
    Token* token;
    // TODO
};

struct IR_Statement {
    Token* token;
    union {
        // compound
        // expression
        // id label
        // case label
        // default label
        // if
        // switch
        // while
        // do while
        // for
        IR_Symbol* goto_label;
        void* continue_;
        void* break_;
        IR_Expression* return_expr;
    } stmt;
    enum {
        IR_STMT_COMPOUND,
        IR_STMT_EXPRESSION,
        IR_STMT_ID_LABEL,
        IR_STMT_CASE_LABEL,
        IR_STMT_DEFAULT_LABEL,
        IR_STMT_IF,
        IR_STMT_SWITCH,
        IR_STMT_WHILE,
        IR_STMT_DO_WHILE,
        IR_STMT_FOR,
        IR_STMT_GOTO,
        IR_STMT_CONTINUE,
        IR_STMT_BREAK,
        IR_STMT_RETURN,
    } stmt_type;
};

struct IR_CompoundStatement {
    Token* token;
    list(IR_Statement*) statements;
    IR_Scope* scope;
};

struct IR_StructUnionDecl {
    Token* token;
    IR_Type* type;
    string name;
    size_t offset;
    intmax_t bitfield_size;
    int bit_offset;
};

struct IR_StructUnion {
    Token* token;
    string name;
    list(IR_StructUnionDecl*) members;
};

struct IR_EnumItem {
    Token* token;
    string name;
    intmax_t value;
};

struct IR_Enum {
    Token* token;
    string name;
    list(IR_EnumItem*) items;
};

struct IR_Param {
    Token* token;
    IR_Type* type;
    IR_Symbol* symbol;
};

struct IR_Initializer {
    Token* token;
    union {
        IR_Expression* expr;
        struct {
            list(IR_Initializer*) items;
            IR_StructUnionDecl* union_member;
        } list;
    } init;
    bool is_expr;
};

struct IR_Type {
    Token* token;
    union {
        void* basic_type;
        IR_Type* pointer_type;
        struct {
            IR_Type* element_type;
            uintmax_t length;
        } array;
        IR_FuncProto* func_type;
        IR_StructUnion* struct_union_type;
        IR_Enum* enum_type;
    } type;
    enum {
        TYPE_VOID,
        TYPE_BOOL,
        TYPE_CHAR,
        TYPE_U_CHAR,
        TYPE_S_CHAR,
        TYPE_SHORT,
        TYPE_U_SHORT,
        TYPE_INT,
        TYPE_U_INT,
        TYPE_LONG,
        TYPE_U_LONG,
        TYPE_LONG_LONG,
        TYPE_U_LONG_LONG,
        TYPE_FLOAT,
        TYPE_DOUBLE,
        TYPE_LONG_DOUBLE,
        TYPE_POINTER,
        TYPE_ARRAY,
        TYPE_FUNCTION,
        TYPE_STRUCT,
        TYPE_UNION,
        TYPE_ENUM,
    } type_kind;
    size_t size;
    size_t align;
    bool is_const;
    bool is_volatile;
    bool is_restrict;
    bool is_atomic;
};

struct IR_FuncDef {
    Token* token;
    IR_FuncProto* proto;
    IR_CompoundStatement* body;
    list(IR_Symbol*) locals;
    list(IR_Symbol*) labels;
};

struct IR_FuncProto {
    Token* token;
    string name;
    list(IR_Param*) params;
    IR_Type* return_type;
    bool is_variadic;
    IR_Scope* scope;
};

struct IR_Decl {
    Token* token;
    IR_Symbol* symbol;
    IR_Initializer* initializer;
};

struct IR_ExternDecl {
    Token* token;
    union {
        IR_FuncDef* func_def;
        IR_FuncProto* func_proto;
        IR_Decl* var_decl;
    } decl;
    bool is_func;
    bool is_func_def;
};

struct IR_TU {
    Token* token;
    list(IR_ExternDecl*) extern_decls;
    IR_Scope* global_scope;
    list(IR_Symbol*) static_vars;
};

#endif  // SEMANTIC_H
