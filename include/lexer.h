#ifndef LEXER_H
#define LEXER_H

#include "lib.h"

typedef enum TokenType {
    TOKEN_IDENTIFIER,
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_STRING,
    TOKEN_KEYWORD,
    TOKEN_SYMBOL,
    TOKEN_COMMENT,
    TOKEN_EOF,
} TokenType;

typedef struct Token {
    TokenType type;
    string value;
    size_t line;
    size_t column;
} Token;

typedef struct Lexer {
    string source_code;
    size_t length;
    size_t pos;
    size_t line;
    size_t column;
    Token* current_token;
    Token* next_token;
    string filename;
    bool skip_comment;
} Lexer;

Lexer* create_lexer(string filename);
Token* next(Lexer* lexer);
Token* peek(Lexer* lexer);

#endif  // LEXER_H
