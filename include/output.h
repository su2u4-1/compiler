#ifndef OUTPUT_H
#define OUTPUT_H

#include "lexer.h"
#include "preprocessor.h"

void print_token(FILE* out, Token* token);
void print_pp_token(FILE* out, ppToken* token);
void output_token_to_code(FILE* out, list(Token*) tokens);

#endif  // OUTPUT_H
