#include "file.h"
#include "lexer.h"
#include "lib.h"
#include "output.h"
#include "parser.h"
#include "preprocessor.h"
#include "target.h"

/*
<exe> <source_files> [-o <output_file>] [-I<dir>...] [output option...]
-I<dir> or -I <dir>: add include search directory (can be repeated)
output option (can be combined, each writes <output_file> with its own extension):
    -p : output pp-tokens         -> .pp
    -pc: render pp-tokens to code -> .pp.c
    -t : output tokens            -> .tok
    -tc: render tokens to code    -> .tok.c
    -a : output AST               -> .ast
    -ac: render AST to code       -> .ast.c
*/

typedef struct Options {
    list(string) source_path;
    string output;
    Path* output_path;
    bool p;
    bool pc;
    bool t;
    bool tc;
    bool a;
    bool ac;
} Options;

static bool parse_args(int argc, char* argv[], Options* opt) {
    for (int i = 1; i < argc; i++) {
        char* arg = argv[i];
        if (strcmp(arg, "-o") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "[Error] at <main>: Missing file name after '-o'\n");
                return false;
            }
            if (opt->output != NULL) {
                fprintf(stderr, "[Error] at <main>: Multiple '-o' options\n");
                return false;
            }
            i++;
            opt->output = create_string(argv[i], strlen(argv[i]));
        } else if (strncmp(arg, "-I", 2) == 0) {
            char* dir = arg + 2;
            if (dir[0] == '\0') {
                if (i + 1 >= argc) {
                    fprintf(stderr, "[Error] at <main>: Missing directory after '-I'\n");
                    return false;
                }
                dir = argv[++i];
            }
            add_include_dir(create_string(dir, strlen(dir)));
        } else if (arg[0] == '-') {
            if (strcmp(arg, "-p") == 0) opt->p = true;
            else if (strcmp(arg, "-pc") == 0) opt->pc = true;
            else if (strcmp(arg, "-t") == 0) opt->t = true;
            else if (strcmp(arg, "-tc") == 0) opt->tc = true;
            else if (strcmp(arg, "-a") == 0) opt->a = true;
            else if (strcmp(arg, "-ac") == 0) opt->ac = true;
            else {
                fprintf(stderr, "[Error] at <main>: Unknown option: %s\n", arg);
                return false;
            }
        } else {
            append(opt->source_path, create_string(arg, strlen(arg)));
        }
    }
    if (list_empty(opt->source_path)) {
        fprintf(stderr, "[Error] at <main>: No source file\n");
        return false;
    }
    if (opt->output == NULL)
        opt->output = create_string("a.out", 5);
    opt->output_path = create_path(opt->output);
    return true;
}

#define out_name(ext) path_str(path_change_ext(base, create_string(ext, strlen(ext))))

static bool compile(Options* opt, string source_path, bool multi) {
    Path* base = multi ? path_change_filename(opt->output_path, path_filename(create_path(source_path))) : opt->output_path;

    string source_code = get_source(source_path);
    if (source_code == NULL) {
        fprintf(stderr, "[Error] at <main>: Failed to read source file: %s\n", source_path);
        return false;
    }

    // preprocess
    bool error_flag = false;
    list(ppToken*) pp_tokens = preprocess(source_path, source_code, &error_flag);
    if (error_flag) {
        fprintf(stderr, "[Error] %s: Preprocessing failed due to errors.\n", source_path);
        return false;
    }
    if (opt->p) output_pp_tokens(out_name(".pp"), pp_tokens);
    if (opt->pc) print_pp_tokens(out_name(".pp.c"), pp_tokens);

    // tokens
    list(Token*) tokens = pp_to_tokens(pp_tokens);
    if (opt->t) output_tokens(out_name(".tok"), tokens);
    if (opt->tc) print_tokens(out_name(".tok.c"), tokens);

    // parse
    Parser* parser = create_parser(tokens, source_path);
    AST_TU* tu = parse_parser(parser);
    if (parser->error_count > 0) {
        fprintf(stderr, "[Error] %s: Parsing failed with %d error(s).\n", source_path, parser->error_count);
        return false;
    }
    if (opt->a) output_ast(out_name(".ast"), tu);
    if (opt->ac) print_ast(out_name(".ast.c"), tu);

    return true;
}

static int run(Options* opt) {
    bool multi = opt->source_path->head != opt->source_path->tail;
    bool ok = true;
    foreach (string, src, opt->source_path)
        ok &= compile(opt, src, multi);
    if (!ok)
        return 1;
    return 0;
}

int main(int argc, char* argv[]) {
    init();
    Options* opt = create_struct(Options);
    *opt = (Options){.source_path = create_list(string), .output = NULL, .output_path = NULL, .p = false, .pc = false, .t = false, .tc = false, .a = false, .ac = false};
    if (!parse_args(argc, argv, opt)) {
        fprintf(stderr, "Usage: %s <source_files> [-o <output_file>] [-I<dir>...] [-p|-pc|-t|-tc|-a|-ac]...\n", argv[0]);
        free_all_memory();
        return 1;
    }
    char* output_dirs[COUNT_OF_DEFAULT_INCLUDE_PATHS] = DEFAULT_INCLUDE_PATHS;
    for (int i = 0; i < COUNT_OF_DEFAULT_INCLUDE_PATHS; i++) {
        add_include_dir(output_dirs[i]);
    }

    int ret = run(opt);
    free_all_memory();
    return ret;
}
