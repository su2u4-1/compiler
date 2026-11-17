typedef unsigned long long size_t;
typedef struct {
    long long a;
    long double b;
} max_align_t;
typedef unsigned long long uintmax_t;
typedef long long intmax_t;
typedef void *va_list;
void va_start(va_list ap, ...);
void va_end(va_list ap);
typedef struct {
    void *placeholder;
} FILE;
extern FILE *stderr;
FILE *fopen(const char *filename, const char *mode);
int fclose(FILE *stream);
int ferror(FILE *stream);
int fseek(FILE *stream, long offset, int origin);
long ftell(FILE *stream);
void rewind(FILE *stream);
size_t fread(void *buffer, size_t size, size_t count, FILE *stream);
int fputc(int c, FILE *stream);
int fputs(const char *str, FILE *stream);
int fprintf(FILE *stream, const char *format, ...);
int vsnprintf(char *buffer, size_t count, const char *format, va_list args);
void *malloc(size_t size);
void *calloc(size_t count, size_t size);
void free(void *p);
void abort(void);
double strtod(const char *str, char **end);
float strtof(const char *str, char **end);
long double strtold(const char *str, char **end);
size_t strlen(const char *str);
int strcmp(const char *a, const char *b);
int strncmp(const char *a, const char *b, size_t count);
int memcmp(const void *a, const void *b, size_t size);
void *memcpy(void *dst, const void *src, size_t size);
void *memmove(void *dst, const void *src, size_t size);
void *memset(void *dst, int value, size_t size);
typedef char *string;
typedef void *ptr;
void init(void);
string get_source(string path);
string string_splice(string format, ...);
typedef struct MemoryBlock MemoryBlock;
struct MemoryBlock {
    size_t size;
    size_t used;
    char *data;
    MemoryBlock *next;
};
typedef struct StringNode StringNode;
struct StringNode {
    size_t size;
    size_t hash;
    StringNode *next;
    string value;
};
typedef struct {
    StringNode **buckets;
    size_t capacity;
    size_t count;
} StringTable;
extern MemoryBlock *string_memory;
extern MemoryBlock *struct_memory;
void free_all_memory(void);
string create_string(const char *str, size_t len);
ptr alloc_memory(size_t size, _Bool is_struct);
typedef struct ListNode ListNode;
struct ListNode {
    void *data;
    ListNode *next;
};
typedef struct List {
    ListNode *head;
    ListNode *tail;
    int type_id;
} List;
List *list_create(int type_id);
int list_append(List *self, void *item, int type_id);
void *list_pop_front(List *self, int type_id);
void *list_pop_back(List *self, int type_id);
void *list_peek_front(List *self, int type_id);
void *list_peek_back(List *self, int type_id);
enum {
    LIST_TYPE_string,
    LIST_TYPE_ppToken,
    LIST_TYPE_ppMacro,
    LIST_TYPE_ppCondFrame,
    LIST_TYPE_List_ppToken,
    LIST_TYPE_Token,
    LIST_TYPE_AST_ExternDecl,
    LIST_TYPE_AST_DeclSpec,
    LIST_TYPE_AST_InitDecl,
    LIST_TYPE_AST_ParamDecl,
    LIST_TYPE_AST_StructDecl,
    LIST_TYPE_AST_Enumerator,
    LIST_TYPE_AST_InitializerItem,
    LIST_TYPE_AST_Designator,
    LIST_TYPE_AST_SpecifierQualifier,
    LIST_TYPE_AST_StructDeclarator,
    LIST_TYPE_AST_DeclStmt,
    LIST_TYPE_AST_AssignmentExpression,
    LIST_TYPE_AST_GenericAssociation,
    LIST_TYPE_AST_TypeName,
    LIST_TYPE_AST_Symbol,
};
typedef struct Token Token;
typedef struct ppToken ppToken;
typedef struct ppMacro ppMacro;
typedef struct ppCondFrame ppCondFrame;
typedef struct AST_ExternDecl AST_ExternDecl;
typedef struct AST_DeclSpec AST_DeclSpec;
typedef struct AST_InitDecl AST_InitDecl;
typedef struct AST_ParamDecl AST_ParamDecl;
typedef struct AST_StructDecl AST_StructDecl;
typedef struct AST_Enumerator AST_Enumerator;
typedef struct AST_InitializerItem AST_InitializerItem;
typedef struct AST_Designator AST_Designator;
typedef struct AST_SpecifierQualifier AST_SpecifierQualifier;
typedef struct AST_StructDeclarator AST_StructDeclarator;
typedef struct AST_DeclStmt AST_DeclStmt;
typedef struct AST_AssignmentExpression AST_AssignmentExpression;
typedef struct AST_GenericAssociation AST_GenericAssociation;
typedef struct AST_TypeName AST_TypeName;
typedef struct AST_Scope AST_Scope;
typedef struct AST_Symbol AST_Symbol;
typedef List *List_string;
typedef List List_ppToken;
typedef List List_ppMacro;
typedef List List_ppCondFrame;
typedef List List_List_ppToken;
typedef List List_Token;
typedef List List_AST_ExternDecl;
typedef List List_AST_DeclSpec;
typedef List List_AST_InitDecl;
typedef List List_AST_ParamDecl;
typedef List List_AST_StructDecl;
typedef List List_AST_Enumerator;
typedef List List_AST_InitializerItem;
typedef List List_AST_Designator;
typedef List List_AST_SpecifierQualifier;
typedef List List_AST_StructDeclarator;
typedef List List_AST_DeclStmt;
typedef List List_AST_AssignmentExpression;
typedef List List_AST_GenericAssociation;
typedef List List_AST_TypeName;
typedef List List_AST_Symbol;
typedef enum EscapeResult {
    ESC_OK,
    ESC_UNKNOWN,
    ESC_NO_HEX_DIGITS,
    ESC_HEX_OUT_OF_RANGE,
    ESC_OCT_OUT_OF_RANGE,
    ESC_UNSUPPORTED,
} EscapeResult;
typedef struct IntLiteral {
    uintmax_t value;
    unsigned int base;
    size_t digits_start;
    size_t digits_end;
    _Bool overflow;
} IntLiteral;
int hex_digit_value(char c);
IntLiteral parse_int_digits(const char *s);
EscapeResult decode_literal_char(const char *s, size_t *pos, unsigned int *value);
const char *escape_message(EscapeResult result);
extern string keywordList[44];
extern string KEYWORD_ALIGNAS;
extern string KEYWORD_ALIGNOF;
extern string KEYWORD_ATOMIC;
extern string KEYWORD_BOOL;
extern string KEYWORD_COMPLEX;
extern string KEYWORD_GENERIC;
extern string KEYWORD_IMAGINARY;
extern string KEYWORD_NORETURN;
extern string KEYWORD_STATIC_ASSERT;
extern string KEYWORD_THREAD_LOCAL;
extern string KEYWORD_AUTO;
extern string KEYWORD_BREAK;
extern string KEYWORD_CASE;
extern string KEYWORD_CHAR;
extern string KEYWORD_CONST;
extern string KEYWORD_CONTINUE;
extern string KEYWORD_DEFAULT;
extern string KEYWORD_DO;
extern string KEYWORD_DOUBLE;
extern string KEYWORD_ELSE;
extern string KEYWORD_ENUM;
extern string KEYWORD_EXTERN;
extern string KEYWORD_FLOAT;
extern string KEYWORD_FOR;
extern string KEYWORD_GOTO;
extern string KEYWORD_IF;
extern string KEYWORD_INLINE;
extern string KEYWORD_INT;
extern string KEYWORD_LONG;
extern string KEYWORD_REGISTER;
extern string KEYWORD_RESTRICT;
extern string KEYWORD_RETURN;
extern string KEYWORD_SHORT;
extern string KEYWORD_SIGNED;
extern string KEYWORD_SIZEOF;
extern string KEYWORD_STATIC;
extern string KEYWORD_STRUCT;
extern string KEYWORD_SWITCH;
extern string KEYWORD_TYPEDEF;
extern string KEYWORD_UNION;
extern string KEYWORD_UNSIGNED;
extern string KEYWORD_VOID;
extern string KEYWORD_VOLATILE;
extern string KEYWORD_WHILE;
extern string SYMBOL_SEMICOLON;
extern string SYMBOL_COMMA;
extern string SYMBOL_L_BRACE;
extern string SYMBOL_R_BRACE;
extern string SYMBOL_L_PARENTHESIS;
extern string SYMBOL_R_PARENTHESIS;
extern string SYMBOL_L_BRACKET;
extern string SYMBOL_R_BRACKET;
extern string SYMBOL_COLON;
extern string SYMBOL_QUESTION;
extern string SYMBOL_ELLIPSIS;
extern string SYMBOL_DOT;
extern string SYMBOL_ARROW;
extern string SYMBOL_MUL;
extern string SYMBOL_BITWISE_AND;
extern string SYMBOL_ASSIGN;
extern string SYMBOL_INCREMENT;
extern string SYMBOL_DECREMENT;
extern string SYMBOL_ADD;
extern string SYMBOL_SUB;
extern string SYMBOL_DIV;
extern string SYMBOL_MOD;
extern string SYMBOL_LOGICAL_NOT;
extern string SYMBOL_BITWISE_NOT;
extern string SYMBOL_XOR;
extern string SYMBOL_BITWISE_OR;
extern string SYMBOL_LT;
extern string SYMBOL_GT;
extern string SYMBOL_L_SHIFT;
extern string SYMBOL_R_SHIFT;
extern string SYMBOL_LE;
extern string SYMBOL_GE;
extern string SYMBOL_EQ;
extern string SYMBOL_NE;
extern string SYMBOL_LOGICAL_AND;
extern string SYMBOL_LOGICAL_OR;
extern string SYMBOL_ADD_ASSIGN;
extern string SYMBOL_SUB_ASSIGN;
extern string SYMBOL_MUL_ASSIGN;
extern string SYMBOL_DIV_ASSIGN;
extern string SYMBOL_MOD_ASSIGN;
extern string SYMBOL_L_SHIFT_ASSIGN;
extern string SYMBOL_R_SHIFT_ASSIGN;
extern string SYMBOL_AND_ASSIGN;
extern string SYMBOL_XOR_ASSIGN;
extern string SYMBOL_OR_ASSIGN;
extern string SYMBOL_HASH;
extern string SYMBOL_DOUBLE_HASH;
extern string P_DEFINED;
extern string P_DEFINE;
extern string P_UNDEF;
extern string P_IF;
extern string P_IFDEF;
extern string P_IFNDEF;
extern string P_ELIF;
extern string P_ELSE;
extern string P_ENDIF;
extern string P_INCLUDE;
extern string P_LINE;
extern string P_ERROR;
extern string P_PRAGMA;
extern string P_VA_ARGS_;
extern string P_FILE_;
extern string P_LINE_;
extern string P_DATE_;
extern string P_TIME_;
extern string P_STDC_;
extern string P_STDC_VERSION_;
extern string P_STDC_HOSTED_;
extern string P_PRAGMA_;
typedef enum ppTokenType {
    PP_IDENTIFIER,
    PP_NUMBER,
    PP_CHAR,
    PP_STRING,
    PP_SYMBOL,
    PP_OTHER,
    PP_NEWLINE,
    PP_EOF,
    PP_PLACE_MARKER,
    PP_HEADER_NAME,
} ppTokenType;
typedef struct ppToken ppToken;
struct ppToken {
    string value;
    size_t line;
    size_t column;
    string filename;
    List_string hideset;
    ppToken *expanded_from;
    ppTokenType type;
    _Bool space_before;
    _Bool at_line_start;
};
typedef struct ppLexer {
    string source_code;
    size_t length;
    size_t pos;
    string filename;
    List_ppToken *pp_tokens;
    size_t *line_map;
    size_t *column_map;
    int include_state;
    _Bool pending_space;
    _Bool line_start;
    _Bool output_error;
} ppLexer;
typedef struct ppCondFrame {
    ppToken *directive;
    _Bool active;
    _Bool taken;
    _Bool in_else;
} ppCondFrame;
typedef struct ppMacro {
    ppToken *name;
    List_ppToken *params;
    List_ppToken *body;
    _Bool is_variadic;
} ppMacro;
typedef struct ppContext {
    List_ppMacro *macros;
    List_ppCondFrame *cond_stack;
    List_ppToken *output;
    ListNode *current;
    ppLexer *lexer;
    int include_depth;
    _Bool in_directive;
} ppContext;
List_ppToken *preprocess(string filename, string source_code, _Bool *error_flag);
ppToken *create_pp_token(ppTokenType type, string value, ppLexer *lexer, size_t pos);
ppLexer *create_pp_lexer(string filename, string source_code);
_Bool pp_lexer(ppLexer *lexer);
_Bool expand_macro(ppContext *ctx, ppToken *name);
_Bool eval_conditional(ppContext *ctx, _Bool *eval_error);
ppToken *pp_peek(ppContext *ctx);
ppToken *pp_get(ppContext *ctx);
ppMacro *find_macro(ppContext *ctx, string name);
typedef struct Path {
    string root;
    string dir;
    string filename;
    string extension;
    string str;
    _Bool rooted;
    _Bool normalized;
} Path;
Path *create_path(string path);
Path *path_join(const Path *a, const Path *b);
Path *path_change_ext(const Path *p, string ext);
Path *path_change_filename(const Path *p, string name);
Path *path_absolute(const Path *p);
string path_str(const Path *p);
string path_dirname(const Path *p);
string path_root_str(const Path *p);
string path_filename(const Path *p);
string path_extension(const Path *p);
_Bool path_is_absolute(const Path *p);
_Bool path_equal(const Path *a, const Path *b);
_Bool path_exists(const Path *p);
_Bool path_is_dir(const Path *p);
void add_include_dir(string dir);
string find_file(string name, _Bool is_system, string current_file);
static _Bool has_error = 0;
ppMacro *find_macro(ppContext *ctx, string name) {
    ((void)(ctx != ((void *)0)));
    for (List *macro__l = (ctx->macros); macro__l != ((void *)0) && macro__l->head != ((void *)0); macro__l = ((void *)0))
        for (ListNode *macro__n = macro__l->head; macro__n != ((void *)0); macro__n = macro__n->next)
            for (ppMacro *macro = (ppMacro *)macro__n->data; macro != ((void *)0); macro = ((void *)0))
                if (macro->name->value == name)
                    return macro;
    return ((void *)0);
}
static ppCondFrame *create_pp_cond_frame(ppToken *directive) {
    ppCondFrame *frame = (ppCondFrame *)alloc_memory(sizeof(ppCondFrame), 1);
    frame->active = 0;
    frame->taken = 0;
    frame->in_else = 0;
    frame->directive = directive;
    return frame;
}
static ppMacro *create_pp_macro(ppToken *name, _Bool is_function) {
    ppMacro *macro = (ppMacro *)alloc_memory(sizeof(ppMacro), 1);
    macro->name = name;
    macro->params = ((void *)0);
    if (is_function)
        macro->params = list_create(_Generic((ppToken *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    macro->is_variadic = 0;
    macro->body = list_create(_Generic((ppToken *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    return macro;
}
static ppContext *create_pp_context(ppLexer *lexer) {
    ppContext *context = (ppContext *)alloc_memory(sizeof(ppContext), 1);
    context->macros = list_create(_Generic((ppMacro *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    context->cond_stack = list_create(_Generic((ppCondFrame *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    context->current = ((void *)0);
    context->output = list_create(_Generic((ppToken *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    context->lexer = lexer;
    context->include_depth = 0;
    context->in_directive = 0;
    return context;
}
static void skip_to_newline(ppContext *ctx) {
    ((void)(ctx != ((void *)0)));
    while (ctx->current != ((void *)0)) {
        if (ctx->current->data == ((void *)0))
            return;
        ppToken *t = (ppToken *)ctx->current->data;
        if (((t) == ((void *)0) || (t)->type == PP_EOF) || t->type == PP_NEWLINE)
            return;
        ctx->current = ctx->current->next;
    }
}
static _Bool cond_active(ppContext *ctx) {
    ((void)(ctx != ((void *)0)));
    if (((ctx->cond_stack) == ((void *)0) || (ctx->cond_stack)->head == ((void *)0)))
        return 1;
    return ((ppCondFrame *)ctx->cond_stack->tail->data)->active;
}
static _Bool expect_token(ppContext *ctx, char *message, size_t line, size_t column, ppTokenType type, string value) {
    ppToken *t = pp_peek(ctx);
    if (((t) == ((void *)0) || (t)->type == PP_EOF) || t->type != type || (value != ((void *)0) && t->value != value)) {
        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), line, column, message);
        return 0;
    }
    pp_get(ctx);
    return 1;
}
static List_List_ppToken *handle_macro_args(ppContext *ctx, ppMacro *macro, ppToken *name) {
    size_t expected = 0;
    for (List *param__l = (macro->params); param__l != ((void *)0) && param__l->head != ((void *)0); param__l = ((void *)0))
        for (ListNode *param__n = param__l->head; param__n != ((void *)0); param__n = param__n->next)
            for (ppToken *param = (ppToken *)param__n->data; param != ((void *)0); param = ((void *)0))
                expected++;
    size_t count = 0;
    List_List_ppToken *args = list_create(_Generic((List_ppToken *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    List_ppToken *cur = list_create(_Generic((ppToken *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    int depth = 0;
    _Bool space = 0;
    while (1) {
        ppToken *t = pp_peek(ctx);
        if (((t) == ((void *)0) || (t)->type == PP_EOF)) {
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), name->line, name->column, "Unterminated macro arguments");
            return ((void *)0);
        } else if (t->type == PP_NEWLINE) {
            if (ctx->in_directive) {
                fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Unterminated macro arguments");
                return ((void *)0);
            }
            space = 1;
            pp_get(ctx);
            continue;
        } else if (t->type == PP_SYMBOL && t->value == SYMBOL_L_PARENTHESIS) {
            depth++;
        } else if (t->type == PP_SYMBOL && t->value == SYMBOL_R_PARENTHESIS) {
            if (depth == 0)
                break;
            depth--;
        } else if (t->type == PP_SYMBOL && t->value == SYMBOL_COMMA && depth == 0) {
            if (!(macro->is_variadic && count >= expected)) {
                count++;
                list_append((args), (void *)(cur), _Generic((cur), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                cur = list_create(_Generic((ppToken *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                pp_get(ctx);
                space = 0;
                continue;
            }
        }
        pp_get(ctx);
        if (space) {
            ppToken *new = (ppToken *)alloc_memory(sizeof(ppToken), 1);
            memcpy(new, t, sizeof(ppToken));
            new->space_before = 1;
            list_append((cur), (void *)(new), _Generic((new), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
            space = 0;
        } else
            list_append((cur), (void *)(t), _Generic((t), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    }
    if (expected == 0 && ((cur) == ((void *)0) || (cur)->head == ((void *)0)) && ((args) == ((void *)0) || (args)->head == ((void *)0)) && !macro->is_variadic)
        return args;
    count++;
    list_append((args), (void *)(cur), _Generic((cur), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    if ((!macro->is_variadic && count != expected) || (macro->is_variadic && count < expected)) {
        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), name->line, name->column, "Incorrect number of macro arguments");
        return ((void *)0);
    }
    if (macro->is_variadic && count == expected)
        list_append((args), (void *)(list_create(_Generic((ppToken *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol))), _Generic((list_create(_Generic((ppToken *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol))), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    return args;
}
static int find_arg_index(List_ppToken *params, ppToken *param, size_t expected) {
    if (param == ((void *)0) || param->type != PP_IDENTIFIER)
        return -1;
    int index = 0;
    for (List *p__l = (params); p__l != ((void *)0) && p__l->head != ((void *)0); p__l = ((void *)0))
        for (ListNode *p__n = p__l->head; p__n != ((void *)0); p__n = p__n->next)
            for (ppToken *p = (ppToken *)p__n->data; p != ((void *)0); p = ((void *)0)) {
                if (p->value == param->value)
                    return index;
                index++;
            }
    if (param->value == P_VA_ARGS_ && expected > 0)
        return (int)expected - 1;
    return -1;
}
static string stringize_tokens(List_ppToken *tokens) {
    _Bool first = 1;
    size_t len = 2;
    for (List *t__l = (tokens); t__l != ((void *)0) && t__l->head != ((void *)0); t__l = ((void *)0))
        for (ListNode *t__n = t__l->head; t__n != ((void *)0); t__n = t__n->next)
            for (ppToken *t = (ppToken *)t__n->data; t != ((void *)0); t = ((void *)0)) {
                len += strlen(t->value) + ((t->space_before && !first) ? 1 : 0);
                if (t->type == PP_STRING || t->type == PP_CHAR) {
                    for (size_t i = 0; i < strlen(t->value); i++) {
                        char c = t->value[i];
                        if (c == '"' || c == '\\')
                            len++;
                    }
                }
                first = 0;
            }
    char *result = (char *)malloc(len + 1);
    if (result == ((void *)0)) {
        fprintf(stderr, "[preprocessor Fatal] at <stringize_tokens>: Cannot allocate memory\n");
        abort();
    }
    result[0] = '"';
    size_t pos = 1;
    first = 1;
    for (List *t__l = (tokens); t__l != ((void *)0) && t__l->head != ((void *)0); t__l = ((void *)0))
        for (ListNode *t__n = t__l->head; t__n != ((void *)0); t__n = t__n->next)
            for (ppToken *t = (ppToken *)t__n->data; t != ((void *)0); t = ((void *)0)) {
                if (t->space_before && !first)
                    result[pos++] = ' ';
                first = 0;
                size_t t_len = strlen(t->value);
                for (size_t i = 0; i < t_len; i++) {
                    char c = t->value[i];
                    if ((t->type == PP_STRING || t->type == PP_CHAR) && (c == '"' || c == '\\'))
                        result[pos++] = '\\';
                    result[pos++] = c;
                }
            }
    result[pos++] = '"';
    result[pos] = '\0';
    string str = create_string(result, pos);
    free(result);
    return str;
}
static ppToken *create_pp_token_in_macro(ppTokenType type, string value, ppToken *name, _Bool space_before, List_string hideset) {
    ppToken *new_token = (ppToken *)alloc_memory(sizeof(ppToken), 1);
    new_token->type = type;
    new_token->value = value;
    new_token->line = name->line;
    new_token->column = name->column;
    new_token->filename = name->filename;
    new_token->space_before = space_before;
    new_token->at_line_start = 0;
    new_token->hideset = hideset;
    new_token->expanded_from = name;
    while (new_token->expanded_from->expanded_from != ((void *)0))
        new_token->expanded_from = new_token->expanded_from->expanded_from;
    return new_token;
}
static List_ppToken *expand_tokens(ppContext *ctx, List_ppToken *tokens) {
    ppContext *sub_ctx = create_pp_context(ctx->lexer);
    sub_ctx->macros = ctx->macros;
    sub_ctx->in_directive = ctx->in_directive;
    sub_ctx->current = tokens->head;
    while (1) {
        ppToken *t = pp_peek(sub_ctx);
        if (((t) == ((void *)0) || (t)->type == PP_EOF))
            break;
        pp_get(sub_ctx);
        if (t->type == PP_IDENTIFIER && expand_macro(sub_ctx, t))
            continue;
        list_append((sub_ctx->output), (void *)(t), _Generic((t), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    }
    return sub_ctx->output;
}
static _Bool hideset_contains(List_string hideset, string name) {
    for (List *s__l = (hideset); s__l != ((void *)0) && s__l->head != ((void *)0); s__l = ((void *)0))
        for (ListNode *s__n = s__l->head; s__n != ((void *)0); s__n = s__n->next)
            for (string s = (string)s__n->data; s != ((void *)0); s = ((void *)0))
                if (s == name)
                    return 1;
    return 0;
}
static List_string hideset_union(List_string a, List_string b) {
    if (a == ((void *)0))
        return b;
    if (b == ((void *)0))
        return a;
    List_string result = list_create(_Generic((string)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    for (List *s__l = (a); s__l != ((void *)0) && s__l->head != ((void *)0); s__l = ((void *)0))
        for (ListNode *s__n = s__l->head; s__n != ((void *)0); s__n = s__n->next)
            for (string s = (string)s__n->data; s != ((void *)0); s = ((void *)0))
                list_append((result), (void *)(s), _Generic((s), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    for (List *t__l = (b); t__l != ((void *)0) && t__l->head != ((void *)0); t__l = ((void *)0))
        for (ListNode *t__n = t__l->head; t__n != ((void *)0); t__n = t__n->next)
            for (string t = (string)t__n->data; t != ((void *)0); t = ((void *)0))
                if (!hideset_contains(a, t))
                    list_append((result), (void *)(t), _Generic((t), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    return result;
}
static List_string hideset_append(List_string hideset, string name) {
    if (hideset_contains(hideset, name))
        return hideset;
    List_string new_hideset = list_create(_Generic((string)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    for (List *s__l = (hideset); s__l != ((void *)0) && s__l->head != ((void *)0); s__l = ((void *)0))
        for (ListNode *s__n = s__l->head; s__n != ((void *)0); s__n = s__n->next)
            for (string s = (string)s__n->data; s != ((void *)0); s = ((void *)0))
                list_append((new_hideset), (void *)(s), _Generic((s), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    list_append((new_hideset), (void *)(name), _Generic((name), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    return new_hideset;
}
static List_string hideset_intersect(List_string a, List_string b, string name) {
    List_string result = list_create(_Generic((string)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    for (List *s__l = (a); s__l != ((void *)0) && s__l->head != ((void *)0); s__l = ((void *)0))
        for (ListNode *s__n = s__l->head; s__n != ((void *)0); s__n = s__n->next)
            for (string s = (string)s__n->data; s != ((void *)0); s = ((void *)0))
                for (List *t__l = (b); t__l != ((void *)0) && t__l->head != ((void *)0); t__l = ((void *)0))
                    for (ListNode *t__n = t__l->head; t__n != ((void *)0); t__n = t__n->next)
                        for (string t = (string)t__n->data; t != ((void *)0); t = ((void *)0))
                            if (s == t)
                                list_append((result), (void *)(s), _Generic((s), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    if (name != ((void *)0) && !hideset_contains(result, name))
        list_append((result), (void *)(name), _Generic((name), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    return result;
}
static ppToken *paste_two_tokens(ppContext *ctx, ppToken *lhs, ppToken *rhs, ppToken *name) {
    string str = string_splice("%s%s", lhs->value, rhs->value);
    ppLexer *lexer = create_pp_lexer(name->filename, str);
    if (lexer == ((void *)0)) {
        fprintf(stderr, "[preprocessor Fatal] at <paste_two_tokens>: Cannot create lexer for token pasting\n");
        abort();
    }
    lexer->output_error = 0;
    _Bool lex_error = pp_lexer(lexer);
    ppToken *pasted = ((void *)0);
    size_t count = 0;
    for (List *token__l = (lexer->pp_tokens); token__l != ((void *)0) && token__l->head != ((void *)0); token__l = ((void *)0))
        for (ListNode *token__n = token__l->head; token__n != ((void *)0); token__n = token__n->next)
            for (ppToken *token = (ppToken *)token__n->data; token != ((void *)0); token = ((void *)0)) {
                if (token->type == PP_EOF || token->type == PP_NEWLINE)
                    continue;
                if (token->type == PP_OTHER) {
                    fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), name->line, name->column, string_splice("Pasting \"%s\" and \"%s\" does not give a valid preprocessing token", lhs->value, rhs->value));
                    return ((void *)0);
                }
                if (count++ == 0)
                    pasted = token;
            }
    if (lex_error || count != 1) {
        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), name->line, name->column, string_splice("Pasting \"%s\" and \"%s\" does not give a valid preprocessing token", lhs->value, rhs->value));
        return ((void *)0);
    }
    return create_pp_token_in_macro(pasted->type, pasted->value, name, lhs->space_before, hideset_intersect(lhs->hideset, rhs->hideset, ((void *)0)));
}
static List_ppToken *paste_macro_body(ppContext *ctx, ppMacro *macro, List_List_ppToken *args, ppToken *name, List_string hideset) {
    if (macro == ((void *)0) || name == ((void *)0))
        return ((void *)0);
    if (name->space_before && ctx->current != ((void *)0) && ctx->current->data != ((void *)0)) {
        ppToken *next = (ppToken *)alloc_memory(sizeof(ppToken), 1);
        memcpy(next, ctx->current->data, sizeof(ppToken));
        next->space_before = 1;
        ctx->current->data = next;
    }
    size_t expected = 0;
    if (macro->params != ((void *)0)) {
        ((void)(args != ((void *)0)));
        for (List *param__l = (macro->params); param__l != ((void *)0) && param__l->head != ((void *)0); param__l = ((void *)0))
            for (ListNode *param__n = param__l->head; param__n != ((void *)0); param__n = param__n->next)
                for (ppToken *param = (ppToken *)param__n->data; param != ((void *)0); param = ((void *)0))
                    expected++;
        if (macro->is_variadic)
            expected++;
    }
    List_ppToken **expanded = ((void *)0);
    List_ppToken **arg_arr = ((void *)0);
    if (expected > 0) {
        expanded = calloc(expected, sizeof(List_ppToken *));
        arg_arr = calloc(expected, sizeof(List_ppToken *));
        if (expanded == ((void *)0) || arg_arr == ((void *)0)) {
            fprintf(stderr, "[preprocessor Fatal] at <paste_macro_body>: Cannot allocate memory\n");
            abort();
        }
    }
    size_t i = 0;
    for (List *arg__l = (args); arg__l != ((void *)0) && arg__l->head != ((void *)0); arg__l = ((void *)0))
        for (ListNode *arg__n = arg__l->head; arg__n != ((void *)0); arg__n = arg__n->next)
            for (List_ppToken *arg = (List_ppToken *)arg__n->data; arg != ((void *)0); arg = ((void *)0))
                arg_arr[i++] = arg;
    List_ppToken *result = list_create(_Generic((ppToken *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    ListNode *node = macro->body->head;
    while (node != ((void *)0)) {
        ppToken *t = (ppToken *)node->data;
        ((void)(t != ((void *)0)));
        if (t->type == PP_SYMBOL && t->value == SYMBOL_HASH && expected > 0) {
            _Bool space_before = t->space_before;
            node = node->next;
            ((void)(node != ((void *)0)));
            t = (ppToken *)node->data;
            int index = find_arg_index(macro->params, t, expected);
            if (index == -1) {
                fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Invalid parameter after # in macro body");
                free(expanded);
                free(arg_arr);
                return ((void *)0);
            }
            string str = stringize_tokens(arg_arr[index]);
            ppToken *new = create_pp_token_in_macro(PP_STRING, str, name, space_before, ((void *)0));
            list_append((result), (void *)(new), _Generic((new), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
        } else if (t->type == PP_SYMBOL && t->value == SYMBOL_DOUBLE_HASH) {
            ppToken *next = ((void *)0);
            if (node->next != ((void *)0) && node->next->data != ((void *)0))
                next = (ppToken *)node->next->data;
            if (!((next) == ((void *)0) || (next)->type == PP_EOF) && next->type != PP_NEWLINE) {
                List_ppToken *rhs = ((void *)0);
                int index = find_arg_index(macro->params, next, expected);
                int rhs_stringize = -1;
                if (macro->params != ((void *)0) && next->type == PP_SYMBOL && next->value == SYMBOL_HASH && node->next->next != ((void *)0))
                    rhs_stringize = find_arg_index(macro->params, (ppToken *)node->next->next->data, expected);
                if (rhs_stringize != -1) {
                    rhs = list_create(_Generic((ppToken *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                    list_append((rhs), (void *)(create_pp_token_in_macro(PP_STRING, stringize_tokens(arg_arr[rhs_stringize]), name, next->space_before, ((void *)0))), _Generic((create_pp_token_in_macro(PP_STRING, stringize_tokens(arg_arr[rhs_stringize]), name, next->space_before, ((void *)0))), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                    node = node->next;
                } else if (index != -1) {
                    rhs = arg_arr[index];
                } else {
                    rhs = list_create(_Generic((ppToken *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                    list_append((rhs), (void *)(next), _Generic((next), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                }
                node = node->next;
                ppToken *lhs = ((ppToken *)list_pop_back((result), _Generic((ppToken *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol)));
                ((void)(lhs != ((void *)0)));
                ListNode *r = (rhs == ((void *)0)) ? ((void *)0) : rhs->head;
                if (r == ((void *)0)) {
                    list_append((result), (void *)(lhs), _Generic((lhs), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                } else if (lhs->type == PP_PLACE_MARKER) {
                    _Bool first = 1;
                    for (; r != ((void *)0); r = r->next) {
                        ppToken *a = (ppToken *)r->data;
                        list_append((result), (void *)(create_pp_token_in_macro(a->type, a->value, name, (first ? lhs : a)->space_before, a->hideset)), _Generic((create_pp_token_in_macro(a->type, a->value, name, (first ? lhs : a)->space_before, a->hideset)), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                        first = 0;
                    }
                } else {
                    ppToken *first_rhs = (ppToken *)r->data;
                    ppToken *pasted = paste_two_tokens(ctx, lhs, first_rhs, name);
                    if (pasted != ((void *)0)) {
                        list_append((result), (void *)(pasted), _Generic((pasted), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                    } else {
                        list_append((result), (void *)(lhs), _Generic((lhs), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                        list_append((result), (void *)(create_pp_token_in_macro(first_rhs->type, first_rhs->value, name, first_rhs->space_before, first_rhs->hideset)), _Generic((create_pp_token_in_macro(first_rhs->type, first_rhs->value, name, first_rhs->space_before, first_rhs->hideset)), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                    }
                    for (r = r->next; r != ((void *)0); r = r->next) {
                        ppToken *a = (ppToken *)r->data;
                        list_append((result), (void *)(create_pp_token_in_macro(a->type, a->value, name, a->space_before, a->hideset)), _Generic((create_pp_token_in_macro(a->type, a->value, name, a->space_before, a->hideset)), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                    }
                }
            }
        } else {
            int index = find_arg_index(macro->params, t, expected);
            if (index == -1) {
                list_append((result), (void *)(create_pp_token_in_macro(t->type, t->value, name, t->space_before, t->hideset)), _Generic((create_pp_token_in_macro(t->type, t->value, name, t->space_before, t->hideset)), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
            } else {
                ppToken *next = ((void *)0);
                if (node->next != ((void *)0) && node->next->data != ((void *)0))
                    next = (ppToken *)node->next->data;
                if (next != ((void *)0) && next->type == PP_SYMBOL && next->value == SYMBOL_DOUBLE_HASH) {
                    if (((arg_arr[index]) == ((void *)0) || (arg_arr[index])->head == ((void *)0)))
                        list_append((result), (void *)(create_pp_token_in_macro(PP_PLACE_MARKER, ((void *)0), name, t->space_before, ((void *)0))), _Generic((create_pp_token_in_macro(PP_PLACE_MARKER, ((void *)0), name, t->space_before, ((void *)0))), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                    else {
                        _Bool first = 1;
                        for (List *arg_t__l = (arg_arr[index]); arg_t__l != ((void *)0) && arg_t__l->head != ((void *)0); arg_t__l = ((void *)0))
                            for (ListNode *arg_t__n = arg_t__l->head; arg_t__n != ((void *)0); arg_t__n = arg_t__n->next)
                                for (ppToken *arg_t = (ppToken *)arg_t__n->data; arg_t != ((void *)0); arg_t = ((void *)0)) {
                                    list_append((result), (void *)(create_pp_token_in_macro(arg_t->type, arg_t->value, name, (first ? t : arg_t)->space_before, arg_t->hideset)), _Generic((create_pp_token_in_macro(arg_t->type, arg_t->value, name, (first ? t : arg_t)->space_before, arg_t->hideset)), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                                    first = 0;
                                }
                    }
                } else {
                    if (expanded[index] == ((void *)0))
                        expanded[index] = expand_tokens(ctx, arg_arr[index]);
                    _Bool first = 1;
                    for (List *arg_t__l = (expanded[index]); arg_t__l != ((void *)0) && arg_t__l->head != ((void *)0); arg_t__l = ((void *)0))
                        for (ListNode *arg_t__n = arg_t__l->head; arg_t__n != ((void *)0); arg_t__n = arg_t__n->next)
                            for (ppToken *arg_t = (ppToken *)arg_t__n->data; arg_t != ((void *)0); arg_t = ((void *)0)) {
                                list_append((result), (void *)(create_pp_token_in_macro(arg_t->type, arg_t->value, name, (first ? t : arg_t)->space_before, arg_t->hideset)), _Generic((create_pp_token_in_macro(arg_t->type, arg_t->value, name, (first ? t : arg_t)->space_before, arg_t->hideset)), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                                first = 0;
                            }
                }
            }
        }
        node = node->next;
    }
    free(expanded);
    free(arg_arr);
    ListNode *prev = ((void *)0);
    _Bool first = 1;
    for (List *t__l = (result); t__l != ((void *)0) && t__l->head != ((void *)0); t__l = ((void *)0))
        for (ListNode *t__n = t__l->head; t__n != ((void *)0); t__n = t__n->next)
            for (ppToken *t = (ppToken *)t__n->data; t != ((void *)0); t = ((void *)0)) {
                if (t->type == PP_PLACE_MARKER) {
                    if (prev == ((void *)0))
                        result->head = t__n->next;
                    else
                        prev->next = t__n->next;
                    if (t__n == result->tail)
                        result->tail = prev;
                } else {
                    t->hideset = hideset_union(t->hideset, hideset);
                    if (first) {
                        t->space_before = name->space_before;
                        first = 0;
                    }
                    prev = t__n;
                }
            }
    if (name->at_line_start && !((result) == ((void *)0) || (result)->head == ((void *)0)))
        ((ppToken *)result->head->data)->at_line_start = 1;
    return result;
}
static _Bool expand_builtin(ppContext *ctx, ppToken *name) {
    ppToken *origin = name;
    while (origin->expanded_from != ((void *)0))
        origin = origin->expanded_from;
    ppToken *t = ((void *)0);
    if (name->value == P_LINE_) {
        t = create_pp_token_in_macro(PP_NUMBER, string_splice("%zu", origin->line), name, name->space_before, ((void *)0));
    } else if (name->value == P_FILE_) {
        string f = origin->filename;
        size_t len = strlen(f);
        char *buf = malloc(len * 2 + 3);
        if (buf == ((void *)0)) {
            fprintf(stderr, "[preprocessor Fatal] at <expand_builtin>: Cannot allocate memory\n");
            abort();
        }
        size_t pos = 0;
        buf[pos++] = '"';
        for (size_t i = 0; i < len; i++) {
            if (f[i] == '\\' || f[i] == '"')
                buf[pos++] = '\\';
            buf[pos++] = f[i];
        }
        buf[pos++] = '"';
        buf[pos] = '\0';
        t = create_pp_token_in_macro(PP_STRING, create_string(buf, pos), name, name->space_before, ((void *)0));
        free(buf);
    } else {
        return 0;
    }
    ListNode *node = (ListNode *)alloc_memory(sizeof(ListNode), 1);
    node->data = t;
    node->next = ctx->current;
    ctx->current = node;
    return 1;
}
_Bool expand_macro(ppContext *ctx, ppToken *name) {
    if (name->type != PP_IDENTIFIER)
        return 0;
    ppMacro *macro = find_macro(ctx, name->value);
    if (macro == ((void *)0))
        return expand_builtin(ctx, name);
    if (hideset_contains(name->hideset, name->value))
        return 0;
    ListNode *saved = ctx->current;
    List_string hideset = ((void *)0);
    List_List_ppToken *args = ((void *)0);
    if (macro->params == ((void *)0)) {
        hideset = hideset_append(name->hideset, name->value);
    } else {
        if (!ctx->in_directive)
            while (pp_peek(ctx)->type == PP_NEWLINE)
                pp_get(ctx);
        ppToken *l_paren = pp_peek(ctx);
        if (((l_paren) == ((void *)0) || (l_paren)->type == PP_EOF) || l_paren->type != PP_SYMBOL || l_paren->value != SYMBOL_L_PARENTHESIS) {
            ctx->current = saved;
            return 0;
        }
        pp_get(ctx);
        args = handle_macro_args(ctx, macro, name);
        if (args == ((void *)0)) {
            ctx->current = saved;
            return 0;
        }
        ppToken *r_paren = pp_get(ctx);
        hideset = hideset_intersect(name->hideset, r_paren->hideset, name->value);
    }
    List_ppToken *result = paste_macro_body(ctx, macro, args, name, hideset);
    if (result == ((void *)0)) {
        ctx->current = saved;
        return 0;
    }
    if (((result) == ((void *)0) || (result)->head == ((void *)0)))
        return 1;
    result->tail->next = ctx->current;
    ctx->current = result->head;
    return 1;
}
static void delete_macro(ppContext *ctx, string name) {
    if (!((ctx->macros) == ((void *)0) || (ctx->macros)->head == ((void *)0))) {
        ListNode *prev = ((void *)0);
        for (List *macro__l = (ctx->macros); macro__l != ((void *)0) && macro__l->head != ((void *)0); macro__l = ((void *)0))
            for (ListNode *macro__n = macro__l->head; macro__n != ((void *)0); macro__n = macro__n->next)
                for (ppMacro *macro = (ppMacro *)macro__n->data; macro != ((void *)0); macro = ((void *)0)) {
                    if (macro->name->value == name) {
                        if (prev == ((void *)0))
                            ctx->macros->head = macro__n->next;
                        else
                            prev->next = macro__n->next;
                        if (macro__n == ctx->macros->tail)
                            ctx->macros->tail = prev;
                        return;
                    }
                    prev = macro__n;
                }
    }
}
static _Bool get_macro_params(ppContext *ctx, ppMacro *macro) {
    if (ctx == ((void *)0) || macro == ((void *)0) || macro->params == ((void *)0))
        return 0;
    ppToken *t = pp_peek(ctx);
    while (t->type != PP_SYMBOL || t->value != SYMBOL_R_PARENTHESIS) {
        if (((t) == ((void *)0) || (t)->type == PP_EOF) || t->type == PP_NEWLINE) {
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), (t == ((void *)0) ? macro->name : t)->line, (t == ((void *)0) ? macro->name : t)->column, "Expected parameter or ) in macro definition");
            return 0;
        }
        if (t->type != PP_IDENTIFIER) {
            if (t->type == PP_SYMBOL && t->value == SYMBOL_ELLIPSIS) {
                pp_get(ctx);
                macro->is_variadic = 1;
                if (!expect_token(ctx, "Expected ) after ... in macro parameter list", t->line, t->column, PP_SYMBOL, SYMBOL_R_PARENTHESIS))
                    return 0;
                return 1;
            }
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Expected parameter name in macro definition");
            return 0;
        }
        t = pp_get(ctx);
        if (t->value == P_VA_ARGS_) {
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Invalid parameter name __VA_ARGS__ in macro definition");
            return 0;
        }
        for (List *param__l = (macro->params); param__l != ((void *)0) && param__l->head != ((void *)0); param__l = ((void *)0))
            for (ListNode *param__n = param__l->head; param__n != ((void *)0); param__n = param__n->next)
                for (ppToken *param = (ppToken *)param__n->data; param != ((void *)0); param = ((void *)0)) {
                    if (param->value == t->value) {
                        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Duplicate parameter name in macro definition");
                        return 0;
                    }
                }
        list_append((macro->params), (void *)(t), _Generic((t), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
        t = pp_peek(ctx);
        if (((t) == ((void *)0) || (t)->type == PP_EOF) || t->type == PP_NEWLINE) {
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), (t == ((void *)0) ? macro->name : t)->line, (t == ((void *)0) ? macro->name : t)->column, "Expected , or ) in macro definition");
            return 0;
        }
        if (t->type == PP_SYMBOL && t->value == SYMBOL_COMMA) {
            t = pp_get(ctx);
            t = pp_peek(ctx);
            if (((t) == ((void *)0) || (t)->type == PP_EOF) || t->type == PP_NEWLINE || (t->type == PP_SYMBOL && t->value == SYMBOL_R_PARENTHESIS)) {
                fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), (t == ((void *)0) ? macro->name : t)->line, (t == ((void *)0) ? macro->name : t)->column, "Expected parameter name after , in macro definition");
                return 0;
            }
        } else if (t->type == PP_SYMBOL && t->value == SYMBOL_R_PARENTHESIS) {
            break;
        } else {
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Expected , or ) in macro definition");
            return 0;
        }
        t = pp_peek(ctx);
    }
    if (t->type == PP_SYMBOL && t->value == SYMBOL_R_PARENTHESIS) {
        pp_get(ctx);
        return 1;
    } else {
        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Expected ) in macro parameter list");
        return 0;
    }
}
static _Bool macro_equal(ppMacro *a, ppMacro *b) {
    if (a == ((void *)0) && b == ((void *)0))
        return 1;
    if (a == ((void *)0) || b == ((void *)0))
        return 0;
    if (a->name->value != b->name->value)
        return 0;
    if (a->is_variadic != b->is_variadic)
        return 0;
    if ((a->params == ((void *)0)) != (b->params == ((void *)0)))
        return 0;
    if (((a->params) == ((void *)0) || (a->params)->head == ((void *)0)) != ((b->params) == ((void *)0) || (b->params)->head == ((void *)0)))
        return 0;
    if (((a->body) == ((void *)0) || (a->body)->head == ((void *)0)) != ((b->body) == ((void *)0) || (b->body)->head == ((void *)0)))
        return 0;
    if (!((a->params) == ((void *)0) || (a->params)->head == ((void *)0)) && !((b->params) == ((void *)0) || (b->params)->head == ((void *)0))) {
        ListNode *old_node = a->params->head;
        ListNode *new_node = b->params->head;
        while (new_node != ((void *)0) && old_node != ((void *)0)) {
            if (((ppToken *)old_node->data)->value != ((ppToken *)new_node->data)->value)
                return 0;
            old_node = old_node->next;
            new_node = new_node->next;
        }
        if ((old_node == ((void *)0)) != (new_node == ((void *)0)))
            return 0;
    }
    if (!((a->body) == ((void *)0) || (a->body)->head == ((void *)0)) && !((b->body) == ((void *)0) || (b->body)->head == ((void *)0))) {
        ListNode *old_node = a->body->head;
        ListNode *new_node = b->body->head;
        _Bool first = 1;
        while (new_node != ((void *)0) && old_node != ((void *)0)) {
            ppToken *old_t = (ppToken *)old_node->data;
            ppToken *new_t = (ppToken *)new_node->data;
            if (old_t->type != new_t->type || old_t->value != new_t->value || (!first && old_t->space_before != new_t->space_before))
                return 0;
            first = 0;
            old_node = old_node->next;
            new_node = new_node->next;
        }
        if ((old_node == ((void *)0)) != (new_node == ((void *)0)))
            return 0;
    }
    return 1;
}
static void handle_define(ppContext *ctx) {
    ppToken *t = pp_peek(ctx);
    if (((t) == ((void *)0) || (t)->type == PP_EOF) || t->type != PP_IDENTIFIER) {
        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t == ((void *)0) ? 0 : t->line, t == ((void *)0) ? 0 : t->column, "Expected macro name after #define");
        return;
    }
    if ((t->value == P_DEFINED || t->value == P_VA_ARGS_ || t->value == P_DATE_ || t->value == P_TIME_ || t->value == P_STDC_ || t->value == P_STDC_VERSION_ || t->value == P_STDC_HOSTED_)) {
        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Invalid macro name after #define");
        return;
    }
    if (t->value == P_FILE_ || t->value == P_LINE_) {
        fprintf(stderr, "[Preprocess Warning] at %s:%zu:%zu: %s\n", ctx->lexer->filename, t->line, t->column, "Redefining predefined macro");
    }
    t = pp_get(ctx);
    ppToken *name = t;
    t = pp_peek(ctx);
    ppMacro *macro = ((void *)0);
    if (!((t) == ((void *)0) || (t)->type == PP_EOF) && t->type == PP_SYMBOL && t->value == SYMBOL_L_PARENTHESIS && !t->space_before) {
        pp_get(ctx);
        macro = create_pp_macro(name, 1);
        if (!get_macro_params(ctx, macro))
            return;
    } else {
        if (!((t) == ((void *)0) || (t)->type == PP_EOF) && t->type != PP_NEWLINE && !t->space_before)
            fprintf(stderr, "[Preprocess Warning] at %s:%zu:%zu: %s\n", ctx->lexer->filename, t->line, t->column, "Missing space between macro name and replacement list");
        macro = create_pp_macro(name, 0);
    }
    t = pp_peek(ctx);
    if (!((t) == ((void *)0) || (t)->type == PP_EOF) && t->type == PP_SYMBOL && t->value == SYMBOL_DOUBLE_HASH) {
        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Macro body cannot start with ##");
        return;
    }
    int state = 0;
    while (!((t) == ((void *)0) || (t)->type == PP_EOF) && t->type != PP_NEWLINE) {
        t = pp_get(ctx);
        if (t->type == PP_IDENTIFIER && t->value == P_VA_ARGS_ && !macro->is_variadic) {
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Invalid use of __VA_ARGS__ in macro body");
            return;
        }
        if (state == 1) {
            if (t->type != PP_IDENTIFIER) {
                fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Expected parameter after # in macro body");
                return;
            }
            _Bool find = 0;
            if (t->value == P_VA_ARGS_ && macro->is_variadic)
                find = 1;
            else if (!((macro->params) == ((void *)0) || (macro->params)->head == ((void *)0))) {
                for (List *param__l = (macro->params); param__l != ((void *)0) && param__l->head != ((void *)0); param__l = ((void *)0))
                    for (ListNode *param__n = param__l->head; param__n != ((void *)0); param__n = param__n->next)
                        for (ppToken *param = (ppToken *)param__n->data; param != ((void *)0); param = ((void *)0)) {
                            if (param->value == t->value) {
                                find = 1;
                                goto break_foreach_in_handle_define;
                            }
                        }
            }
        break_foreach_in_handle_define:
            if (!find) {
                fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Invalid parameter after # in macro body");
                return;
            }
        }
        if (macro->params != ((void *)0) && t->type == PP_SYMBOL && t->value == SYMBOL_HASH)
            state = 1;
        else if (t->type == PP_SYMBOL && t->value == SYMBOL_DOUBLE_HASH)
            state = 2;
        else
            state = 0;
        list_append((macro->body), (void *)(t), _Generic((t), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
        t = pp_peek(ctx);
    }
    if (state == 1) {
        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), (t == ((void *)0) ? name : t)->line, (t == ((void *)0) ? name : t)->column, "Macro body cannot end with #");
        return;
    }
    if (state == 2) {
        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), (t == ((void *)0) ? name : t)->line, (t == ((void *)0) ? name : t)->column, "Macro body cannot end with ##");
        return;
    }
    ppMacro *old = find_macro(ctx, name->value);
    if (old != ((void *)0)) {
        if (!macro_equal(old, macro))
            fprintf(stderr, "[Preprocess Warning] at %s:%zu:%zu: %s\n", ctx->lexer->filename, name->line, name->column, "Macro redefined");
        delete_macro(ctx, name->value);
    }
    list_append((ctx->macros), (void *)(macro), _Generic((macro), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
}
static void add_predefined(ppContext *ctx, string name, ppTokenType type, string value) {
    ppMacro *macro = create_pp_macro(create_pp_token(PP_IDENTIFIER, name, ctx->lexer, 0), 0);
    list_append((macro->body), (void *)(create_pp_token(type, value, ctx->lexer, 0)), _Generic((create_pp_token(type, value, ctx->lexer, 0)), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    list_append((ctx->macros), (void *)(macro), _Generic((macro), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
}
typedef long long time_t;
struct tm {
    int placeholder;
};
time_t time(time_t *t);
struct tm *localtime(const time_t *t);
size_t strftime(char *buffer, size_t size, const char *format, const struct tm *tm);
static void add_predefined_macros(ppContext *ctx) {
    time_t now = time(((void *)0));
    struct tm *tm = now == (time_t)-1 ? ((void *)0) : localtime(&now);
    if (tm == ((void *)0)) {
        add_predefined(ctx, P_DATE_, PP_STRING, create_string("\"??? ?? ????\"", 13));
        add_predefined(ctx, P_TIME_, PP_STRING, create_string("\"??:??:??\"", 10));
    } else {
        char buf[32];
        strftime(buf, sizeof buf, "\"%b %d %Y\"", tm);
        if (buf[5] == '0')
            buf[5] = ' ';
        add_predefined(ctx, P_DATE_, PP_STRING, create_string(buf, strlen(buf)));
        strftime(buf, sizeof buf, "\"%H:%M:%S\"", tm);
        add_predefined(ctx, P_TIME_, PP_STRING, create_string(buf, strlen(buf)));
    }
}
static void process_tokens(ppContext *ctx);
static void handle_include(ppContext *ctx, ppToken *header_name) {
    ((void)(ctx != ((void *)0) && header_name != ((void *)0)));
    ((void)(header_name->type == PP_HEADER_NAME));
    if (ctx->include_depth >= 200) {
        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), header_name->line, header_name->column, "Maximum include depth exceeded");
        return;
    }
    string name = header_name->value;
    size_t len = strlen(name);
    _Bool is_angle = 0;
    if (len > 2 && name[0] == '<' && name[len - 1] == '>') {
        name = create_string(name + 1, len - 2);
        is_angle = 1;
    } else if (len > 2 && name[0] == '"' && name[len - 1] == '"') {
        name = create_string(name + 1, len - 2);
    } else {
        if (len < 3)
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), header_name->line, header_name->column, "Empty header name in #include");
        else
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), header_name->line, header_name->column, "Invalid header name in #include");
        return;
    }
    string path = find_file(name, is_angle, ctx->lexer->filename);
    if (path == ((void *)0)) {
        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), header_name->line, header_name->column, string_splice("Cannot find header file: %s", name));
        return;
    }
    string source = get_source(path);
    if (source == ((void *)0)) {
        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), header_name->line, header_name->column, string_splice("Cannot read header file: %s", path));
        return;
    }
    ppLexer *lexer = create_pp_lexer(path, source);
    if (lexer == ((void *)0))
        return;
    if (pp_lexer(lexer))
        has_error = 1;
    ppContext *sub_ctx = create_pp_context(lexer);
    sub_ctx->macros = ctx->macros;
    sub_ctx->include_depth = ctx->include_depth + 1;
    sub_ctx->output = ctx->output;
    sub_ctx->current = lexer->pp_tokens->head;
    process_tokens(sub_ctx);
}
static ppToken *build_include_name(ppContext *ctx, ppToken *directive, List_ppToken *tokens) {
    if (((tokens) == ((void *)0) || (tokens)->head == ((void *)0))) {
        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), directive->line, directive->column, "Expected header name in #include");
        return ((void *)0);
    }
    int state = 0;
    ppToken *name = ((void *)0);
    string header_name = ((void *)0);
    ListNode *other = ((void *)0);
    for (List *t__l = (tokens); t__l != ((void *)0) && t__l->head != ((void *)0); t__l = ((void *)0))
        for (ListNode *t__n = t__l->head; t__n != ((void *)0); t__n = t__n->next)
            for (ppToken *t = (ppToken *)t__n->data; t != ((void *)0); t = ((void *)0)) {
                if (((t) == ((void *)0) || (t)->type == PP_EOF)) {
                    fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Unexpected end of tokens in #include");
                    return ((void *)0);
                } else if (state == 0 && t->type == PP_STRING) {
                    name = create_pp_token(PP_HEADER_NAME, t->value, ctx->lexer, 0);
                    name->line = t->line;
                    name->column = t->column;
                    name->expanded_from = t->expanded_from;
                    other = t__n;
                    goto skip_foreach_in_build_include_name;
                } else if (state == 0 && t->type == PP_SYMBOL && t->value == SYMBOL_LT) {
                    state = 1;
                    header_name = "<";
                    continue;
                } else if ((state == 2 || state == 1) && t->type == PP_SYMBOL && t->value == SYMBOL_GT) {
                    if (state == 1) {
                        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Expected header name after <");
                        return ((void *)0);
                    }
                    state = 3;
                    header_name = string_splice("%s>", header_name);
                    name = create_pp_token(PP_HEADER_NAME, header_name, ctx->lexer, 0);
                    name->line = t->line;
                    name->column = t->column;
                    name->expanded_from = t->expanded_from;
                    other = t__n;
                    goto skip_foreach_in_build_include_name;
                } else if ((state == 1 || state == 2) && t->type != PP_EOF && t->type != PP_NEWLINE) {
                    if (t->space_before && state == 2)
                        header_name = string_splice("%s %s", header_name, t->value);
                    else
                        header_name = string_splice("%s%s", header_name, t->value);
                    state = 2;
                    continue;
                } else if (state == 0 && t->type == PP_HEADER_NAME) {
                    name = t;
                    other = t__n;
                    goto skip_foreach_in_build_include_name;
                } else {
                    fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Invalid token in #include header name");
                    return ((void *)0);
                }
            }
skip_foreach_in_build_include_name:
    if (other != ((void *)0) && other->next != ((void *)0) && (ppToken *)other->next->data != ((void *)0)) {
        ppToken *t = (ppToken *)other->next->data;
        if (!((t) == ((void *)0) || (t)->type == PP_EOF) && t->type != PP_NEWLINE) {
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Unexpected token after #include header name");
            return ((void *)0);
        }
    }
    if (name == ((void *)0)) {
        if (state == 0)
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), directive->line, directive->column, "Expected header name in #include");
        else
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), directive->line, directive->column, "Expected closing > in #include");
        return ((void *)0);
    }
    return name;
}
static void handle_directive(ppContext *ctx) {
    ppToken *directive = pp_peek(ctx);
    if (((directive) == ((void *)0) || (directive)->type == PP_EOF) || directive->type != PP_IDENTIFIER) {
        if ((!((directive) == ((void *)0) || (directive)->type == PP_EOF) && directive->type == PP_NEWLINE) || !cond_active(ctx))
            return;
        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), directive == ((void *)0) ? 0 : directive->line, directive == ((void *)0) ? 0 : directive->column, "Expected directive after #");
        return;
    }
    pp_get(ctx);
    _Bool is_cond = directive->value == P_IF || directive->value == P_IFDEF || directive->value == P_IFNDEF || directive->value == P_ELIF || directive->value == P_ELSE || directive->value == P_ENDIF;
    if (!is_cond && !cond_active(ctx))
        return;
    if (directive->value == P_DEFINE) {
        handle_define(ctx);
    } else if (directive->value == P_UNDEF) {
        ppToken *name = pp_peek(ctx);
        if (((name) == ((void *)0) || (name)->type == PP_EOF) || name->type != PP_IDENTIFIER) {
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), directive->line, directive->column, "Expected macro name after #undef");
            return;
        }
        if ((name->value == P_DEFINED || name->value == P_VA_ARGS_ || name->value == P_DATE_ || name->value == P_TIME_ || name->value == P_STDC_ || name->value == P_STDC_VERSION_ || name->value == P_STDC_HOSTED_)) {
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), name->line, name->column, "Invalid macro name after #undef");
            return;
        }
        pp_get(ctx);
        delete_macro(ctx, name->value);
    } else if (directive->value == P_IF || directive->value == P_IFDEF || directive->value == P_IFNDEF) {
        _Bool outer_active = cond_active(ctx);
        _Bool inner_active = 0;
        ppCondFrame *frame = create_pp_cond_frame(directive);
        if (outer_active) {
            if (directive->value == P_IF) {
                _Bool eval_error = 0;
                inner_active = eval_conditional(ctx, &eval_error) != 0;
                if (eval_error)
                    has_error = 1;
            } else {
                ppToken *name = pp_peek(ctx);
                if (((name) == ((void *)0) || (name)->type == PP_EOF) || name->type != PP_IDENTIFIER) {
                    fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), directive->line, directive->column, "Expected identifier after #if[n]def");
                    frame->active = 0;
                    frame->taken = 0;
                    list_append((ctx->cond_stack), (void *)(frame), _Generic((frame), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                    return;
                }
                pp_get(ctx);
                inner_active = (directive->value == P_IFDEF) == (name->value == P_LINE_ || name->value == P_FILE_ || find_macro(ctx, name->value) != ((void *)0));
            }
        }
        frame->active = outer_active && inner_active;
        frame->taken = !outer_active || inner_active;
        list_append((ctx->cond_stack), (void *)(frame), _Generic((frame), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    } else if (directive->value == P_ELIF) {
        if (((ctx->cond_stack) == ((void *)0) || (ctx->cond_stack)->head == ((void *)0))) {
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), directive->line, directive->column, "#elif without #if");
            return;
        }
        ppCondFrame *frame = (ppCondFrame *)ctx->cond_stack->tail->data;
        if (frame->in_else) {
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), directive->line, directive->column, "#elif after #else");
            return;
        }
        if (frame->taken) {
            frame->active = 0;
        } else {
            _Bool eval_error = 0;
            _Bool cond = eval_conditional(ctx, &eval_error) != 0;
            if (eval_error)
                has_error = 1;
            frame->active = cond;
            frame->taken = frame->taken || cond;
        }
    } else if (directive->value == P_ELSE) {
        if (((ctx->cond_stack) == ((void *)0) || (ctx->cond_stack)->head == ((void *)0))) {
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), directive->line, directive->column, "#else without #if");
            return;
        }
        ppCondFrame *frame = (ppCondFrame *)ctx->cond_stack->tail->data;
        if (frame->in_else) {
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), directive->line, directive->column, "#else after #else");
            return;
        }
        frame->in_else = 1;
        frame->active = !frame->taken;
        frame->taken = 1;
    } else if (directive->value == P_ENDIF) {
        if (((ctx->cond_stack) == ((void *)0) || (ctx->cond_stack)->head == ((void *)0))) {
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), directive->line, directive->column, "#endif without #if");
            return;
        }
        if (ctx->cond_stack->head == ctx->cond_stack->tail) {
            ctx->cond_stack->head = ((void *)0);
            ctx->cond_stack->tail = ((void *)0);
        } else {
            ListNode *n = ctx->cond_stack->head;
            while (n->next != ctx->cond_stack->tail)
                n = n->next;
            n->next = ((void *)0);
            ctx->cond_stack->tail = n;
        }
    } else if (directive->value == P_INCLUDE) {
        List_ppToken *tokens = list_create(_Generic((ppToken *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
        int expansions = 0;
        while (1) {
            ppToken *t = pp_peek(ctx);
            if (((t) == ((void *)0) || (t)->type == PP_EOF) || t->type == PP_NEWLINE)
                break;
            pp_get(ctx);
            if (t->type == PP_IDENTIFIER && expand_macro(ctx, t)) {
                if (++expansions > 64) {
                    fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Too many macro expansions in #include");
                    return;
                }
                continue;
            }
            list_append((tokens), (void *)(t), _Generic((t), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
        }
        ppToken *name = build_include_name(ctx, directive, tokens);
        if (name == ((void *)0))
            return;
        handle_include(ctx, name);
    } else if (directive->value == P_LINE) {
        return;
    } else if (directive->value == P_ERROR) {
        string msg = "Encountered #error directive";
        ListNode *n = ctx->current;
        _Bool first = 1;
        while (n != ((void *)0)) {
            ppToken *t = (ppToken *)n->data;
            if (t == ((void *)0) || t->type == PP_NEWLINE || t->type == PP_EOF)
                break;
            msg = string_splice((first ? "%s: %s" : "%s %s"), msg, t->value);
            first = 0;
            n = n->next;
        }
        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), directive->line, directive->column, msg);
        return;
    } else if (directive->value == P_PRAGMA) {
        return;
    } else {
        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), directive->line, directive->column, "Unknown preprocessor directive");
        return;
    }
}
static void process_tokens(ppContext *ctx) {
    while (1) {
        ppToken *token = pp_peek(ctx);
        if (((token) == ((void *)0) || (token)->type == PP_EOF))
            break;
        if (token->at_line_start && token->expanded_from == ((void *)0) && token->type == PP_SYMBOL && token->value == SYMBOL_HASH) {
            pp_get(ctx);
            ctx->in_directive = 1;
            handle_directive(ctx);
            ctx->in_directive = 0;
            skip_to_newline(ctx);
        } else {
            token = pp_get(ctx);
            if (!cond_active(ctx))
                continue;
            if (token->type == PP_OTHER) {
                string msg = ((void *)0);
                if (token->value != ((void *)0) && token->value[0] == '"')
                    msg = "Unterminated string literal";
                else if (token->value != ((void *)0) && token->value[0] == '\'')
                    msg = "Unterminated char literal";
                else if (token->value != ((void *)0) && token->value[0] == '<')
                    msg = "Unterminated #include <...>";
                else
                    msg = string_splice("Unexpected token: %s", token->value == ((void *)0) ? "(null)" : token->value);
                fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), token->line, token->column, msg);
            } else if (token->type == PP_HEADER_NAME)
                fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), token->line, token->column, "Unexpected #include header name");
            if (token->type == PP_IDENTIFIER && expand_macro(ctx, token))
                continue;
            list_append((ctx->output), (void *)(token), _Generic((token), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
        }
    }
    if (!((ctx->cond_stack) == ((void *)0) || (ctx->cond_stack)->head == ((void *)0))) {
        size_t line = 0, column = 0;
        ppCondFrame *frame = ((ppCondFrame *)list_peek_back((ctx->cond_stack), _Generic((ppCondFrame *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol)));
        if (frame != ((void *)0) && frame->directive != ((void *)0)) {
            line = frame->directive->line;
            column = frame->directive->column;
        }
        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), line, column, "Unterminated conditional directive");
    }
}
List_ppToken *preprocess(string filename, string source_code, _Bool *error_flag) {
    has_error = 0;
    ppLexer *lexer = create_pp_lexer(filename, source_code);
    if (lexer == ((void *)0)) {
        *error_flag = 1;
        return ((void *)0);
    }
    has_error = pp_lexer(lexer);
    ppContext *ctx = create_pp_context(lexer);
    ctx->current = lexer->pp_tokens->head;
    add_predefined_macros(ctx);
    process_tokens(ctx);
    *error_flag = has_error;
    list_append((ctx->output), (void *)(create_pp_token(PP_EOF, ((void *)0), lexer, lexer->length)), _Generic((create_pp_token(PP_EOF, ((void *)0), lexer, lexer->length)), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    return ctx->output;
}
