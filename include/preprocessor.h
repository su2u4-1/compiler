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
    PP_PLACE_MARKER,
    PP_HEADER_NAME,
} ppTokenType;
typedef struct ppToken ppToken;
struct ppToken {
    string value;
    size_t line;
    size_t column;
    string filename;
    list(string) hideset;
    ppToken* expanded_from;
    ppTokenType type;
    bool space_before;
    bool at_line_start;
};
typedef struct ppLexer {
    string source_code;
    size_t length;
    size_t pos;
    string filename;
    list(ppToken*) pp_tokens;
    size_t* line_map;
    size_t* column_map;
    int include_state;
    bool pending_space;
    bool line_start;
    bool output_error;
} ppLexer;

typedef struct ppCondFrame {
    ppToken* directive;
    bool active;
    bool taken;
    bool in_else;
} ppCondFrame;
typedef struct ppMacro {
    ppToken* name;
    list(ppToken*) params;
    list(ppToken*) body;
    bool is_variadic;
} ppMacro;
typedef struct ppContext {
    list(ppMacro*) macros;
    list(ppCondFrame*) cond_stack;
    list(ppToken*) output;
    ListNode* current;
    ppLexer* lexer;
    int include_depth;
    bool in_directive;
} ppContext;

#define is_digit(c) ((c) >= '0' && (c) <= '9')
#define is_alphabet(c) (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))

list(ppToken*) preprocess(string filename, string source_code, bool* error_flag);
ppToken* create_pp_token(ppTokenType type, string value, ppLexer* lexer, size_t pos);
ppLexer* create_pp_lexer(string filename, string source_code);
bool pp_lexer(ppLexer* lexer);

#endif  // PREPROCESSOR_H
