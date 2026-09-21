#include "lexer.h"

static string is_keyword(string str) {
    for (size_t i = 0; i < keyword_count; ++i) {
        if (str == keywordList[i]) {
            return keywordList[i];
        }
    }
    return NULL;
}

static Token* create_token(TokenType type, string value, size_t line, size_t column) {
    Token* token = create_struct(Token);
    token->line = line;
    token->column = column;
    if (type == TOKEN_IDENTIFIER) {
        string keyword = is_keyword(value);
        if (keyword != NULL) {
            token->type = TOKEN_KEYWORD;
            token->value = keyword;
            return token;
        }
    }
    token->type = type;
    token->value = value;
    return token;
}

#define is_digit(c) ((c) >= '0' && (c) <= '9')
#define is_alphabet(c) ((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z')
#define lexer_error(message, line, column) fprintf(stderr, "[lexer Error] at %s:%zu:%zu: %s\n", lexer->filename, line + 1, column + 1, message)

static Token* get_next_token(Lexer* lexer) {
    if (lexer->pos >= lexer->length)
        return create_token(TOKEN_EOF, NULL, lexer->line, lexer->column);
    while (true) {
        char c = lexer->source_code[lexer->pos++];
        lexer->column++;
        if (c == '\0') {
            return create_token(TOKEN_EOF, NULL, lexer->line, lexer->column);
        } else if (c == ' ' || c == '\t' || c == '\r') {
            continue;
        } else if (c == '\n') {
            lexer->line++;
            lexer->column = 1;
            continue;
        } else if (is_alphabet(c) || c == '_') {
            size_t start = lexer->pos - 1;
            size_t column_start = lexer->column - 1;
            do {
                c = lexer->source_code[lexer->pos++];
                lexer->column++;
            } while (is_alphabet(c) || is_digit(c) || c == '_');
            lexer->pos -= 1;
            lexer->column -= 1;
            string content = create_string(&lexer->source_code[start], lexer->pos - start);
            return create_token(TOKEN_IDENTIFIER, content, lexer->line, column_start);
        } else if (is_digit(c)) {
            size_t start = lexer->pos - 1;
            size_t column_start = lexer->column - 1;
            while (is_digit(c)) {
                c = lexer->source_code[lexer->pos++];
                lexer->column++;
            }
            TokenType type = TOKEN_INT;
            char p = lexer->source_code[lexer->pos];
            if (c == '.' && (is_digit(p))) {
                c = lexer->source_code[lexer->pos++];
                lexer->column++;
                while (is_digit(c)) {
                    c = lexer->source_code[lexer->pos++];
                    lexer->column++;
                }
                type = TOKEN_FLOAT;
            }
            lexer->pos -= 1;
            lexer->column -= 1;
            return create_token(type, create_string(&lexer->source_code[start], lexer->pos - start), lexer->line, column_start);
        }
    }
    lexer_error("Unrecognized token", lexer->line, lexer->column);
    return NULL;
}

static Token* get(Lexer* lexer) {
    Token* token;
    do {
        token = get_next_token(lexer);
        if (token == NULL) {
            fprintf(stderr, "[lexer Error] at <get>: Failed to get next token\n");
            return NULL;
        }
    } while (lexer->skip_comment && token->type == TOKEN_COMMENT);
    return token;
}

Lexer* create_lexer(string filename) {
    Lexer* lexer = create_struct(Lexer);
    lexer->source_code = get_source(filename);
    lexer->length = strlen(lexer->source_code);
    lexer->pos = 0;
    lexer->line = 1;
    lexer->column = 1;
    lexer->current_token = NULL;
    lexer->next_token = NULL;
    lexer->filename = filename;
    lexer->skip_comment = true;
    return lexer;
}

Token* next(Lexer* lexer) {
    lexer->current_token = lexer->next_token ? lexer->next_token : get(lexer);
    lexer->next_token = get(lexer);
    return lexer->current_token;
}

Token* peek(Lexer* lexer) {
    if (lexer->next_token == NULL)
        lexer->next_token = get(lexer);
    return lexer->next_token;
}
