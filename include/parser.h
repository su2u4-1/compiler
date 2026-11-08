#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lib.h"

typedef enum SymbolKind {
    SYMBOL_KIND_VAR,
    SYMBOL_KIND_FUNC,
    SYMBOL_KIND_TYPEDEF,
    SYMBOL_KIND_ENUM_CONST,
    SYMBOL_KIND_STRUCT,
    SYMBOL_KIND_UNION,
    SYMBOL_KIND_ENUM,
} SymbolKind;

typedef enum ScopeKind {
    SCOPE_FILE,
    SCOPE_BLOCK,
    SCOPE_FUNC_PROTO,
    SCOPE_FUNC_BODY,
} ScopeKind;

typedef struct Symbol {
    string name;
    Token* token;
    SymbolKind kind;
    bool is_defined;
} Symbol;

typedef struct Scope {
    ScopeKind kind;
    struct Scope* parent;
    // var, func, typedef, enum constant
    list(Symbol*) names;
    // struct name, union name, enum name
    list(Symbol*) tags;
} Scope;

typedef struct Parser {
    list(Token*) tokens;
    ListNode* next;
    Token* current;
    Scope* current_scope;
    int error_count;
    bool panic_mode;
} Parser;

Parser* create_parser(list(Token*) tokens);
TU* parse_parser(Parser* parser);

#endif  // PARSER_H
