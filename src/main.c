#include "lexer.h"
#include "lib.h"

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

int main(int argc, char* argv[]) {
    handle_args(argc, argv);
    Lexer* lexer = create_lexer(source_path);
    return 0;
}
