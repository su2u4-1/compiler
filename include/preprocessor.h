#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "lib.h"

typedef enum ppTokenType {
    PP_IDENTIFIER,
    PP_NUMBER,
    PP_CHAR,
    PP_STRING,
    PP_SYMBOL,
    PP_OTHER,
    PP_NEWLINE,
    PP_EOF,
} ppTokenType;
typedef struct ppToken {
    ppTokenType type;
    string value;
    size_t line;
    size_t column;
} ppToken;
typedef struct ppLexer {
    string source_code;
    size_t length;
    size_t pos;
    size_t prev_line_column;
    size_t line;
    size_t column;
    ppToken* current_token;
    ppToken* next_token;
    string filename;
    list(ppToken*) pp_tokens;
    size_t* line_map;
    size_t* column_map;
} ppLexer;
#ifdef DEBUG_PP_LEXER
void pp_lexer(ppLexer* lexer);
ppLexer* create_pp_lexer(string filename, string source_code);
#endif

typedef struct ppCondFrame {
    bool active;
    bool taken;
    bool in_else;
} ppCondFrame;
typedef struct ppMacro {
    string name;
    list(string) params;
    bool is_variadic;
    list(ppToken*) body;
} ppMacro;
typedef struct ppContext {
    list(ppMacro*) macros;
    list(ppCondFrame*) cond_stack;
    list(ppToken*) output;
    ListNode* current;
    ppLexer* lexer;
} ppContext;

string preprocess(string filename, string source_code);

#endif  // PREPROCESSOR_H
