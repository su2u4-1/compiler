#include "output.h"

#include "lexer.h"
#include "preprocessor.h"

void print_token(FILE* out, Token* token) {
    if (token == NULL) {
        fprintf(out, "[Error] Token is NULL\n");
        return;
    }
    switch (token->type) {
        case TOKEN_EOF: fputs("(EOF, ", out); break;
        case TOKEN_IDENTIFIER: fputs("(identifier, ", out); break;
        case TOKEN_INT: fputs("(integer, ", out); break;
        case TOKEN_FLOAT: fputs("(float, ", out); break;
        case TOKEN_STRING: fputs("(string, ", out); break;
        case TOKEN_CHAR: fputs("(char, ", out); break;
        case TOKEN_SYMBOL: fputs("(symbol, ", out); break;
        case TOKEN_KEYWORD: fputs("(keyword, ", out); break;
        case TOKEN_COMMENT: fputs("(comment, ", out); break;
        case TOKEN_SYNTAX_ERROR_NUMBER: fputs("(error number, ", out); break;
        default: fputs("(unknown, \n", out); break;
    }
    fprintf(out, "%zu, %zu, ", token->line, token->column);
    if (token->value == NULL) {
        fputs("(null))\n", out);
    } else {
        fputs("`", out);
        for (size_t i = 0; i < strlen(token->value); ++i) {
            char c = token->value[i];
            if (c == '\0')
                fputs("\\0", out);
            else if (c == '\n')
                fputs("\\n", out);
            else if (c == '\t')
                fputs("\\t", out);
            else if (c == '\r')
                fputs("\\r", out);
            else
                fputc(c, out);
        }
        fputs("`)\n", out);
    }
}

void print_pp_token(FILE* out, ppToken* token) {
    if (token == NULL) {
        fprintf(out, "[Error] Token is NULL\n");
        return;
    }
    switch (token->type) {
        case PP_EOF: fputs("(EOF, ", out); break;
        case PP_IDENTIFIER: fputs("(identifier, ", out); break;
        case PP_NUMBER: fputs("(number, ", out); break;
        case PP_STRING: fputs("(string, ", out); break;
        case PP_CHAR: fputs("(char, ", out); break;
        case PP_SYMBOL: fputs("(symbol, ", out); break;
        case PP_NEWLINE: fputs("(newline, ", out); break;
        case PP_OTHER: fputs("(other, ", out); break;
        default: fputs("(unknown, ", out); break;
    }
    fprintf(out, "%zu, %zu, ", token->line, token->column);
    if (token->value == NULL) {
        fputs("(null))\n", out);
    } else {
        fputs("`", out);
        for (size_t i = 0; i < strlen(token->value); ++i) {
            char c = token->value[i];
            if (c == '\0')
                fputs("\\0", out);
            else if (c == '\n')
                fputs("\\n", out);
            else if (c == '\t')
                fputs("\\t", out);
            else if (c == '\r')
                fputs("\\r", out);
            else
                fputc(c, out);
        }
        fputs("`)\n", out);
    }
}
