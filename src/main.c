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
        output_path = create_string(argv[2], strlen(argv[2]));
    } else {
        output_path = create_string("a.out", 5);
    }
}

int main(int argc, char* argv[]) {
    // init
    init();
    handle_args(argc, argv);
    string source_code = get_source(source_path);
    if (source_code == NULL) {
        fprintf(stderr, "[Error] at <main>: Failed to read source file: %s\n", source_path);
        return 1;
    }

    // preprocess
    bool error_flag = false;
    list(ppToken*) preprocessed_code = preprocess(source_path, source_code, &error_flag);
    if (error_flag) {
        fprintf(stderr, "[Error] Preprocessing failed due to errors.\n");
        return 1;
    }

    // convert preprocessed code to tokens
    list(Token*) tokens = pp_to_tokens(preprocessed_code);

    // output
    FILE* out = fopen(output_path, "w");
    if (out == NULL) {
        fprintf(stderr, "[Error] at <main>: Failed to open output file: %s\n", output_path);
        return 1;
    }
    // foreach (Token*, token, tokens)
    //     print_token(out, token);
    output_token_to_code(out, tokens);
    fclose(out);

    return 0;
}
