#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lib.h"

struct AST_Symbol {
    string name;
    bool is_typedef;
};

struct AST_Scope {
    AST_Scope* parent;
    list(AST_Symbol*) names;
};

typedef struct Parser {
    list(Token*) tokens;
    ListNode* next;
    Token* current;
    size_t brace_depth;
    size_t paren_depth;
    AST_Scope* current_scope;
    string filename;
    int error_count;
    bool panic_mode;
} Parser;

Parser* create_parser(list(Token*) tokens, string filename);
AST_TU* parse_parser(Parser* parser);

#endif  // PARSER_H
