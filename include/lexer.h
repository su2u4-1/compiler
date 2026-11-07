#ifndef LEXER_H
#define LEXER_H

#include "lib.h"

typedef enum TokenType {
    TOKEN_IDENTIFIER,
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_STRING,
    TOKEN_CHAR,
    TOKEN_KEYWORD,
    TOKEN_SYMBOL,
    TOKEN_COMMENT,
    TOKEN_EOF,
    TOKEN_SYNTAX_ERROR_NUMBER,
    TOKEN_SYNTAX_ERROR_CHAR,
    TOKEN_SYNTAX_ERROR_STRING,
} TokenType;

typedef enum NumberSuffix {
    SUFFIX_NONE,
    SUFFIX_U,
    SUFFIX_UL,
    SUFFIX_ULL,
    SUFFIX_L,
    SUFFIX_LL,
    SUFFIX_F,
    SUFFIX_LD,
} NumberSuffix;

typedef struct Token {
    TokenType type;
    string value;
    union {
        struct {
            char* data;
            size_t length;
        } str;          // TOKEN_STRING
        int character;  // TOKEN_CHAR
        struct {
            uintmax_t data;
            NumberSuffix suffix;
        } integer;  // TOKEN_INT
        struct {
            long double data;
            NumberSuffix suffix;
        } floating;  // TOKEN_FLOAT
    } literal;
    size_t line;
    size_t column;
    string filename;
    bool space_before;
    bool at_line_start;
} Token;

list(Token*) pp_to_tokens(list(ppToken*) pp_tokens);

#endif  // LEXER_H
