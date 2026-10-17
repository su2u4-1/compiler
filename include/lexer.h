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
} TokenType;

typedef struct Token {
    TokenType type;
    string value;
    size_t line;
    size_t column;
} Token;

list(Token*) pp_to_tokens(list(ppToken*) pp_tokens);

#endif  // LEXER_H
