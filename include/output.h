#ifndef OUTPUT_H
#define OUTPUT_H

#include "ast.h"

void output_pp_tokens(string filename, list(ppToken*) tokens);
void print_pp_tokens(string filename, list(ppToken*) tokens);
void output_tokens(string filename, list(Token*) tokens);
void print_tokens(string filename, list(Token*) tokens);
void output_ast(string filename, AST_TU* tu);
void print_ast(string filename, AST_TU* tu);

#endif  // OUTPUT_H
