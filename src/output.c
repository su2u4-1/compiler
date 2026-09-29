#include "output.h"

#include "lexer.h"

void print_token(FILE* out, Token* token) {
    if (token == NULL) {
        fprintf(out, "[Error] Token is NULL\n");
        return;
    }
    switch (token->type) {
        case TOKEN_EOF: fprintf(out, "(EOF, %zu, %zu, '')\n", token->line + 1, token->column + 1); return;
        case TOKEN_IDENTIFIER: fputs("(identifier, ", out); break;
        case TOKEN_INT: fputs("(integer, ", out); break;
        case TOKEN_FLOAT: fputs("(float, ", out); break;
        case TOKEN_STRING: fputs("(string, ", out); break;
        case TOKEN_CHAR: fputs("(char, ", out); break;
        case TOKEN_SYMBOL: fputs("(symbol, ", out); break;
        case TOKEN_KEYWORD: fputs("(keyword, ", out); break;
        case TOKEN_COMMENT: fputs("(comment, ", out); break;
        case TOKEN_SYNTAX_ERROR_NUMBER: fputs("(error number, ", out); break;
        default: fprintf(out, "(unknown, %zu, %zu, '')\n", token->line + 1, token->column + 1); return;
    }
    fprintf(out, "%zu, %zu, `", token->line + 1, token->column + 1);
    if (token->value == NULL) {
        fprintf(out, "(null)`\n");
    } else {
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
    }
    fputs("`)\n", out);
}
