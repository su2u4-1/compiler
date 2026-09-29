#include "lexer.h"
#include "lib.h"
#include "output.h"

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

int main(int argc, char* argv[]) {
    init();
    handle_args(argc, argv);
    Lexer* lexer = create_lexer(source_path);
    if (lexer == NULL) {
        fprintf(stderr, "[lexer Fatal] at <main>: Failed to create lexer\n");
        return 1;
    }
    FILE* out = fopen(output_path, "w");
    if (out == NULL) {
        fprintf(stderr, "[Error] at <main>: Failed to open output file: %s\n", output_path);
        return 1;
    }
    print_tokens(out, lexer);
    return 0;
}
