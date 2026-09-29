#include "lexer.h"
#include "lib.h"
#include "output.h"
#include "preprocessor.h"

static string source_path = NULL;
static string output_path = NULL;

static void handle_args(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source_file> [output_file]\n", argv[0]);
        exit(1);
    }
    source_path = argv[1];
    if (argc >= 3) {
        output_path = argv[2];
    } else {
        output_path = "a.out";
    }
}

static void print_tokens(FILE* out, Lexer* lexer) {
    lexer->skip_comment = false;
    Token* token = NULL;
    do {
        token = next(lexer);
        print_token(out, token);
    } while (token != NULL && token->type != TOKEN_EOF);
}

#ifdef DEBUG_PP_LEXER
static void print_pp_tokens(FILE* out, list(ppToken*) pp_tokens) {
    foreach (ppToken*, token, pp_tokens)
        print_pp_token(out, token);
}
#endif

int main(int argc, char* argv[]) {
    init();
    handle_args(argc, argv);
    string source_code = get_source(source_path);
#ifdef DEBUG_LEXER
    Lexer* lexer = create_lexer(source_path, source_code);
    if (lexer == NULL) {
        fprintf(stderr, "[lexer Fatal] at <main>: Failed to create lexer\n");
        return 1;
    }
#elif defined(DEBUG_PP_LEXER)
    ppLexer* pplexer = create_pp_lexer(source_path, source_code);
    pp_lexer(pplexer);
#endif
    string preprocessed_code = preprocess(source_path, source_code);
    FILE* out = fopen(output_path, "w");
    if (out == NULL) {
        fprintf(stderr, "[Error] at <main>: Failed to open output file: %s\n", output_path);
        return 1;
    }
#ifdef DEBUG_LEXER
    print_tokens(out, lexer);
#elif defined(DEBUG_PP_LEXER)
    print_pp_tokens(out, pplexer->pp_tokens);
#endif
    fputs(preprocessed_code, out);
    fclose(out);
    return 0;
}
