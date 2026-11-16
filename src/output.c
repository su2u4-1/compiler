#include "output.h"

#include "lexer.h"
#include "preprocessor.h"

static FILE* open_file(string filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "[Error] at <output> Failed to open file: %s\n", filename);
        return NULL;
    }
    return file;
}

static void write_value(FILE* out, string value) {
    if (value == NULL) {
        fputs("(null)", out);
        return;
    }
    fputc('`', out);
    for (const char* p = value; *p != '\0'; ++p) {
        switch (*p) {
            case '\n': fputs("\\n", out); break;
            case '\t': fputs("\\t", out); break;
            case '\r': fputs("\\r", out); break;
            default: fputc(*p, out); break;
        }
    }
    fputc('`', out);
}

static void write_spacing(FILE* out, bool first, bool at_line_start, bool space_before, size_t column) {
    if (at_line_start) {
        if (!first) fputc('\n', out);
        for (size_t i = 1; i < column; ++i)
            fputc(' ', out);
    } else if (space_before && !first) {
        fputc(' ', out);
    }
}

void output_pp_tokens(string filename, list(ppToken*) tokens) {
    FILE* out = open_file(filename);
    if (out == NULL) return;
    foreach (ppToken*, token, tokens) {
        switch (token->type) {
            case PP_EOF: fputs("(EOF, ", out); break;
            case PP_IDENTIFIER: fputs("(identifier, ", out); break;
            case PP_NUMBER: fputs("(number, ", out); break;
            case PP_STRING: fputs("(string, ", out); break;
            case PP_CHAR: fputs("(char, ", out); break;
            case PP_SYMBOL: fputs("(symbol, ", out); break;
            case PP_NEWLINE: fputs("(newline, ", out); break;
            case PP_HEADER_NAME: fputs("(header_name, ", out); break;
            case PP_PLACE_MARKER: fputs("(place_marker, ", out); break;
            case PP_OTHER: fputs("(other, ", out); break;
            default: fputs("(unknown, ", out); break;
        }
        fprintf(out, "%zu, %zu, ", token->line, token->column);
        write_value(out, token->value);
        fputs(")\n", out);
    }
    fclose(out);
}

void print_pp_tokens(string filename, list(ppToken*) tokens) {
    FILE* out = open_file(filename);
    if (out == NULL) return;
    bool first = true;
    foreach (ppToken*, token, tokens) {
        if (token->type == PP_EOF) break;
        if (token->type == PP_NEWLINE || token->type == PP_PLACE_MARKER || token->value == NULL) continue;
        write_spacing(out, first, token->at_line_start, token->space_before, token->column);
        fputs(token->value, out);
        first = false;
    }
    fputc('\n', out);
    fclose(out);
}

void output_tokens(string filename, list(Token*) tokens) {
    FILE* out = open_file(filename);
    if (out == NULL) return;
    foreach (Token*, token, tokens) {
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
            case TOKEN_SYNTAX_ERROR_CHAR: fputs("(error char, ", out); break;
            case TOKEN_SYNTAX_ERROR_STRING: fputs("(error string, ", out); break;
            default: fputs("(unknown, ", out); break;
        }
        fprintf(out, "%zu, %zu, ", token->line, token->column);
        write_value(out, token->value);
        fputs(")\n", out);
    }
    fclose(out);
}

void print_tokens(string filename, list(Token*) tokens) {
    FILE* out = open_file(filename);
    if (out == NULL) return;
    bool first = true;
    foreach (Token*, token, tokens) {
        if (token->type == TOKEN_EOF) break;
        if (token->value == NULL) continue;
        write_spacing(out, first, token->at_line_start, token->space_before, token->column);
        fputs(token->value, out);
        first = false;
    }
    fputc('\n', out);
    fclose(out);
}

void output_ast(string filename, TU* tu) {
    FILE* out = open_file(filename);
    if (out == NULL) return;

    fputs("not complete implemented yet\n", out);
    fclose(out);
}

void print_ast(string filename, TU* tu) {
    FILE* out = open_file(filename);
    if (out == NULL) return;

    fputs("not complete implemented yet\n", out);
    fclose(out);
}
