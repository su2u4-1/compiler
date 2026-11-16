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
    TYPE_string,
    TYPE_ppToken,
    TYPE_ppMacro,
    TYPE_ppCondFrame,
    TYPE_List_ppToken,
    TYPE_Token,
    TYPE_ExternDecl,
    TYPE_DeclSpec,
    TYPE_InitDecl,
    TYPE_ParamDecl,
    TYPE_StructDecl,
    TYPE_Enumerator,
    TYPE_InitializerItem,
    TYPE_Designator,
    TYPE_SpecifierQualifier,
    TYPE_StructDeclarator,
    TYPE_DeclStmt,
    TYPE_AssignmentExpression,
    TYPE_GenericAssociation,
    TYPE_TypeName,
    TYPE_Scope,
    TYPE_Symbol,
};
typedef struct Token Token;
typedef struct ppToken ppToken;
typedef struct ppMacro ppMacro;
typedef struct ppCondFrame ppCondFrame;
typedef struct ExternDecl ExternDecl;
typedef struct DeclSpec DeclSpec;
typedef struct InitDecl InitDecl;
typedef struct ParamDecl ParamDecl;
typedef struct StructDecl StructDecl;
typedef struct Enumerator Enumerator;
typedef struct InitializerItem InitializerItem;
typedef struct Designator Designator;
typedef struct SpecifierQualifier SpecifierQualifier;
typedef struct StructDeclarator StructDeclarator;
typedef struct DeclStmt DeclStmt;
typedef struct AssignmentExpression AssignmentExpression;
typedef struct GenericAssociation GenericAssociation;
typedef struct TypeName TypeName;
typedef struct Scope Scope;
typedef struct Symbol Symbol;
typedef List *List_string;
typedef List List_ppToken;
typedef List List_ppMacro;
typedef List List_ppCondFrame;
typedef List List_List_ppToken;
typedef List List_Token;
typedef List List_ExternDecl;
typedef List List_DeclSpec;
typedef List List_InitDecl;
typedef List List_ParamDecl;
typedef List List_StructDecl;
typedef List List_Enumerator;
typedef List List_InitializerItem;
typedef List List_Designator;
typedef List List_SpecifierQualifier;
typedef List List_StructDeclarator;
typedef List List_DeclStmt;
typedef List List_AssignmentExpression;
typedef List List_GenericAssociation;
typedef List List_TypeName;
typedef List List_Scope;
typedef List List_Symbol;
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
typedef struct StaticAssertDecl StaticAssertDecl;
typedef struct Declarator Declarator;
typedef struct DirectDeclarator DirectDeclarator;
typedef struct TypeSpec TypeSpec;
typedef struct Pointer Pointer;
typedef struct Initializer Initializer;
typedef struct InitializerItem InitializerItem;
typedef struct Statement Statement;
typedef struct Enumerator Enumerator;
typedef struct StructDeclarator StructDeclarator;
typedef struct StructDecl StructDecl;
typedef struct SpecifierQualifier SpecifierQualifier;
typedef struct TypeName TypeName;
typedef struct ParamDecl ParamDecl;
typedef struct Designator Designator;
typedef struct DeclSpec DeclSpec;
typedef struct FuncDecl FuncDecl;
typedef struct InitDecl InitDecl;
typedef struct VarDecl VarDecl;
typedef struct ExternDecl ExternDecl;
typedef struct TU TU;
typedef struct Declarator AbsDeclarator;
typedef struct LabeledStatement LabeledStatement;
typedef struct SelectionStatement SelectionStatement;
typedef struct IterationStatement IterationStatement;
typedef struct JumpStatement JumpStatement;
typedef struct DeclStmt DeclStmt;
typedef struct AssignmentExpression AssignmentExpression;
typedef struct ConditionalExpression ConditionalExpression;
typedef struct BinaryExpression BinaryExpression;
typedef struct CastExpression CastExpression;
typedef struct UnaryExpression UnaryExpression;
typedef struct PostfixExpression PostfixExpression;
typedef struct PrimaryExpression PrimaryExpression;
typedef struct GenericAssociation GenericAssociation;
struct AssignmentExpression {
    Token *token;
    union {
        ConditionalExpression *cond_expr;
        struct {
            UnaryExpression *left;
            AssignmentExpression *right;
            string op;
        } binary;
    } expr;
    _Bool is_conditional;
};
struct ConditionalExpression {
    Token *token;
    BinaryExpression *binary_expr;
    List_AssignmentExpression *true_expr;
    ConditionalExpression *false_expr;
};
struct BinaryExpression {
    Token *token;
    union {
        struct {
            string op;
            BinaryExpression *left;
            BinaryExpression *right;
        } binary;
        CastExpression *cast;
    } expr;
    _Bool is_cast;
};
struct CastExpression {
    Token *token;
    union {
        struct {
            TypeName *type_name;
            CastExpression *cast_expr;
        } cast;
        UnaryExpression *unary_expr;
    } expr;
    _Bool is_cast;
};
struct UnaryExpression {
    Token *token;
    union {
        struct {
            string op;
            UnaryExpression *unary_expr;
        } prefix;
        struct {
            string op;
            CastExpression *cast_expr;
        } unary_op;
        struct {
            TypeName *type_name;
            _Bool is_sizeof;
        } function_like;
        PostfixExpression *postfix;
    } expr;
    enum {
        UNARY_PREFIX,
        UNARY_UNARY_OP,
        UNARY_FUNCTION_LIKE,
        UNARY_POSTFIX,
    } expr_type;
};
struct PostfixExpression {
    Token *token;
    union {
        PrimaryExpression *primary_expr;
        struct {
            TypeName *type_name;
            List_InitializerItem *initializer_list;
        } compound_literal;
        struct {
            PostfixExpression *postfix_expr;
            List_AssignmentExpression *index_expr;
        } array_access;
        struct {
            PostfixExpression *postfix_expr;
            List_AssignmentExpression *args;
        } func_call;
        struct {
            PostfixExpression *postfix_expr;
            Token *identifier;
            enum {
                POSTFIX_MEMBER_ACCESS,
                POSTFIX_MEMBER_ACCESS_PTR,
                POSTFIX_INCREMENT,
                POSTFIX_DECREMENT,
            } op_type;
        } postfix_op;
    } expr;
    enum {
        POSTFIX_PRIMARY,
        POSTFIX_COMPOUND_LITERAL,
        POSTFIX_ARRAY_ACCESS,
        POSTFIX_FUNC_CALL,
        POSTFIX_OP,
    } expr_type;
};
struct PrimaryExpression {
    Token *token;
    union {
        Token *identifier;
        Token *integer_constant;
        Token *character_constant;
        Token *floating_constant;
        Token *string_literal;
        List_AssignmentExpression *expr;
        struct {
            AssignmentExpression *expr;
            List_GenericAssociation *generic_assoc_list;
        } generic_selection;
    } primary;
    enum {
        PRIMARY_IDENTIFIER,
        PRIMARY_INTEGER_CONSTANT,
        PRIMARY_CHARACTER_CONSTANT,
        PRIMARY_FLOATING_CONSTANT,
        PRIMARY_STRING_LITERAL,
        PRIMARY_EXPRESSION,
        PRIMARY_GENERIC_SELECTION,
    } primary_type;
};
struct GenericAssociation {
    Token *token;
    TypeName *type_name;
    AssignmentExpression *assignment_expr;
};
struct DeclStmt {
    Token *token;
    union {
        VarDecl *var_decl;
        Statement *statement;
    } item;
    _Bool is_var_decl;
};
struct LabeledStatement {
    Token *token;
    union {
        Token *identifier;
        ConditionalExpression *case_stmt;
        void *none;
    } label;
    enum {
        LABEL_IDENTIFIER,
        LABEL_CASE,
        LABEL_DEFAULT,
    } label_type;
    Statement *stmt;
};
struct SelectionStatement {
    Token *token;
    union {
        struct {
            List_AssignmentExpression *cond_expr;
            Statement *then_stmt;
            Statement *else_stmt;
        } if_stmt;
        struct {
            List_AssignmentExpression *cond_expr;
            Statement *stmt;
        } switch_stmt;
    } selection;
    _Bool is_switch;
};
struct IterationStatement {
    Token *token;
    union {
        struct {
            List_AssignmentExpression *expr;
            Statement *stmt;
        } while_stmt;
        struct {
            union {
                List_AssignmentExpression *init_expr;
                VarDecl *init_decl;
            } init;
            _Bool is_init_decl;
            List_AssignmentExpression *cond_expr;
            List_AssignmentExpression *loop_expr;
            Statement *stmt;
        } for_stmt;
    } loop;
    enum {
        LOOP_WHILE,
        LOOP_DO_WHILE,
        LOOP_FOR,
    } loop_type;
};
struct JumpStatement {
    Token *token;
    union {
        Token *identifier;
        List_AssignmentExpression *expr;
        void *none;
    } jump;
    enum {
        JUMP_GOTO,
        JUMP_CONTINUE,
        JUMP_BREAK,
        JUMP_RETURN,
    } jump_type;
};
struct Statement {
    Token *token;
    union {
        LabeledStatement *label;
        List_DeclStmt *compound;
        List_AssignmentExpression *expression;
        SelectionStatement *selection;
        IterationStatement *iteration;
        JumpStatement *jump;
    } stmt;
    enum {
        STMT_LABELED,
        STMT_COMPOUND,
        STMT_EXPRESSION,
        STMT_SELECTION,
        STMT_ITERATION,
        STMT_JUMP,
    } stmt_type;
};
struct Enumerator {
    Token *token;
    Token *identifier;
    ConditionalExpression *constant_expr;
};
struct StructDeclarator {
    Token *token;
    Declarator *declarator;
    ConditionalExpression *constant_expr;
};
struct StructDecl {
    Token *token;
    union {
        struct {
            List_SpecifierQualifier *spec_qual_list;
            List_StructDeclarator *struct_declarators;
        } general_struct_decl;
        StaticAssertDecl *static_assert_decl;
    } decl;
    _Bool is_static_assert_decl;
};
struct SpecifierQualifier {
    Token *token;
    union {
        TypeSpec *type_spec;
        string type_qualifier;
    } spec;
    _Bool is_type_spec;
};
struct TypeName {
    Token *token;
    List_SpecifierQualifier *spec_qual_list;
    AbsDeclarator *abs_declarator;
};
struct ParamDecl {
    Token *token;
    List_DeclSpec *decl_specs;
    Declarator *decl;
    _Bool is_abs;
};
struct Pointer {
    Token *token;
    List_string type_qualifiers;
    Pointer *pointer;
};
struct Designator {
    Token *token;
    union {
        ConditionalExpression *constant_expr;
        Token *identifier;
    } designator;
    _Bool is_constant_expr;
};
struct InitializerItem {
    Token *token;
    List_Designator *designation;
    Initializer *initializer;
};
struct Initializer {
    Token *token;
    union {
        AssignmentExpression *assignment_expr;
        List_InitializerItem *inits;
    } init;
    _Bool is_assignment_expr;
};
struct TypeSpec {
    Token *token;
    union {
        string keyword_spec;
        TypeName *atomic_spec;
        struct {
            _Bool is_struct;
            Token *identifier;
            List_StructDecl *members;
        } struct_union_spec;
        struct {
            Token *identifier;
            List_Enumerator *enumerators;
        } enum_spec;
        Token *typedef_name;
    } spec;
    enum {
        TYPE_SPEC_KEYWORD,
        TYPE_SPEC_ATOMIC,
        TYPE_SPEC_STRUCT_UNION,
        TYPE_SPEC_ENUM,
        TYPE_SPEC_TYPEDEF_NAME,
    } spec_type;
};
struct DirectDeclarator {
    Token *token;
    union {
        Token *identifier;
        Declarator *declarator;
        struct {
            DirectDeclarator *direct_declarator;
            AssignmentExpression *assignment_expression;
            List_string type_qualifiers;
            _Bool is_static;
        } array;
        struct {
            DirectDeclarator *direct_declarator;
            List_ParamDecl *param_decls;
            _Bool is_variadic;
        } func;
        struct {
            DirectDeclarator *direct_declarator;
            List_string type_qualifiers;
            _Bool has_star;
        } incomplete_array;
    } decl;
    enum {
        DECLARATOR_ID,
        DECLARATOR_DECL,
        DECLARATOR_ARRAY,
        DECLARATOR_FUNC,
        DECLARATOR_INCOMPLETE_ARRAY,
    } decl_type;
    Scope *func_proto_scope;
};
struct Declarator {
    Token *token;
    Pointer *pointer;
    DirectDeclarator *direct_declarator;
};
struct DeclSpec {
    Token *token;
    union {
        string keyword;
        struct {
            union {
                TypeName *type_name;
                ConditionalExpression *constant_expression;
            } spec;
            _Bool is_type_name;
        } alignment;
        TypeSpec *type;
    } specifier;
    enum {
        SPEC_KEYWORD,
        SPEC_ALIGNMENT,
        SPEC_TYPE_SPEC,
    } specifier_type;
};
struct FuncDecl {
    Token *token;
    List_DeclSpec *decl_specs;
    Declarator *declarator;
    List_DeclStmt *body;
};
struct InitDecl {
    Token *token;
    Declarator *declarator;
    Initializer *initializer;
};
struct StaticAssertDecl {
    Token *token;
    ConditionalExpression *expr;
    Token *message;
};
struct VarDecl {
    Token *token;
    union {
        struct {
            List_DeclSpec *decl_specs;
            List_InitDecl *init_decls;
        } general_decl;
        StaticAssertDecl *static_assert_decl;
    } decl;
    _Bool is_static_assert_decl;
};
struct ExternDecl {
    Token *token;
    union {
        FuncDecl *func_decl;
        VarDecl *var_decl;
    } decl;
    _Bool is_func_decl;
};
struct TU {
    Token *token;
    string filename;
    List_ExternDecl *extern_decls;
};
void output_pp_tokens(string filename, List_ppToken *tokens);
void print_pp_tokens(string filename, List_ppToken *tokens);
void output_tokens(string filename, List_Token *tokens);
void print_tokens(string filename, List_Token *tokens);
void output_ast(string filename, TU *tu);
void print_ast(string filename, TU *tu);
typedef enum TokenType {
    TOKEN_IDENTIFIER,
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_STRING,
    TOKEN_CHAR,
    TOKEN_KEYWORD,
    TOKEN_SYMBOL,
    TOKEN_COMMENT,
    TOKEN_EOF,
    TOKEN_SYNTAX_ERROR_NUMBER,
    TOKEN_SYNTAX_ERROR_CHAR,
    TOKEN_SYNTAX_ERROR_STRING,
} TokenType;
typedef enum NumberSuffix {
    SUFFIX_NONE,
    SUFFIX_U,
    SUFFIX_UL,
    SUFFIX_ULL,
    SUFFIX_L,
    SUFFIX_LL,
    SUFFIX_F,
    SUFFIX_LD,
} NumberSuffix;
typedef struct Token {
    TokenType type;
    string value;
    union {
        struct {
            char *data;
            size_t length;
        } str;
        int character;
        struct {
            uintmax_t data;
            NumberSuffix suffix;
            _Bool is_decimal;
        } integer;
        struct {
            long double data;
            NumberSuffix suffix;
        } floating;
    } literal;
    size_t line;
    size_t column;
    string filename;
    _Bool space_before;
    _Bool at_line_start;
} Token;
List_Token *pp_to_tokens(List_ppToken *pp_tokens);
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
static FILE *open_file(string filename) {
    FILE *file = fopen(filename, "w");
    if (file == ((void *)0)) {
        fprintf(stderr, "[Error] at <output> Failed to open file: %s\n", filename);
        return ((void *)0);
    }
    return file;
}
static void write_value(FILE *out, string value) {
    if (value == ((void *)0)) {
        fputs("(null)", out);
        return;
    }
    fputc('`', out);
    for (const char *p = value; *p != '\0'; ++p) {
        switch (*p) {
        case '\n':
            fputs("\\n", out);
            break;
        case '\t':
            fputs("\\t", out);
            break;
        case '\r':
            fputs("\\r", out);
            break;
        default:
            fputc(*p, out);
            break;
        }
    }
    fputc('`', out);
}
static void write_spacing(FILE *out, _Bool first, _Bool at_line_start, _Bool space_before, size_t column) {
    if (at_line_start) {
        if (!first)
            fputc('\n', out);
        for (size_t i = 1; i < column; ++i)
            fputc(' ', out);
    } else if (space_before && !first) {
        fputc(' ', out);
    }
}
void output_pp_tokens(string filename, List_ppToken *tokens) {
    FILE *out = open_file(filename);
    if (out == ((void *)0))
        return;
    for (List *token__l = (tokens); token__l != ((void *)0) && token__l->head != ((void *)0); token__l = ((void *)0))
        for (ListNode *token__n = token__l->head; token__n != ((void *)0); token__n = token__n->next)
            for (ppToken *token = (ppToken *)token__n->data; token != ((void *)0); token = ((void *)0)) {
                switch (token->type) {
                case PP_EOF:
                    fputs("(EOF, ", out);
                    break;
                case PP_IDENTIFIER:
                    fputs("(identifier, ", out);
                    break;
                case PP_NUMBER:
                    fputs("(number, ", out);
                    break;
                case PP_STRING:
                    fputs("(string, ", out);
                    break;
                case PP_CHAR:
                    fputs("(char, ", out);
                    break;
                case PP_SYMBOL:
                    fputs("(symbol, ", out);
                    break;
                case PP_NEWLINE:
                    fputs("(newline, ", out);
                    break;
                case PP_HEADER_NAME:
                    fputs("(header_name, ", out);
                    break;
                case PP_PLACE_MARKER:
                    fputs("(place_marker, ", out);
                    break;
                case PP_OTHER:
                    fputs("(other, ", out);
                    break;
                default:
                    fputs("(unknown, ", out);
                    break;
                }
                fprintf(out, "%zu, %zu, ", token->line, token->column);
                write_value(out, token->value);
                fputs(")\n", out);
            }
    fclose(out);
}
void print_pp_tokens(string filename, List_ppToken *tokens) {
    FILE *out = open_file(filename);
    if (out == ((void *)0))
        return;
    _Bool first = 1;
    for (List *token__l = (tokens); token__l != ((void *)0) && token__l->head != ((void *)0); token__l = ((void *)0))
        for (ListNode *token__n = token__l->head; token__n != ((void *)0); token__n = token__n->next)
            for (ppToken *token = (ppToken *)token__n->data; token != ((void *)0); token = ((void *)0)) {
                if (token->type == PP_EOF)
                    break;
                if (token->type == PP_NEWLINE || token->type == PP_PLACE_MARKER || token->value == ((void *)0))
                    continue;
                write_spacing(out, first, token->at_line_start, token->space_before, token->column);
                fputs(token->value, out);
                first = 0;
            }
    fputc('\n', out);
    fclose(out);
}
static void output_one_token(FILE *out, Token *token) {
    if (token == ((void *)0)) {
        fputs("(null)", out);
        return;
    }
    switch (token->type) {
    case TOKEN_EOF:
        fputs("(EOF, ", out);
        break;
    case TOKEN_IDENTIFIER:
        fputs("(identifier, ", out);
        break;
    case TOKEN_INT:
        fputs("(integer, ", out);
        break;
    case TOKEN_FLOAT:
        fputs("(float, ", out);
        break;
    case TOKEN_STRING:
        fputs("(string, ", out);
        break;
    case TOKEN_CHAR:
        fputs("(char, ", out);
        break;
    case TOKEN_SYMBOL:
        fputs("(symbol, ", out);
        break;
    case TOKEN_KEYWORD:
        fputs("(keyword, ", out);
        break;
    case TOKEN_COMMENT:
        fputs("(comment, ", out);
        break;
    case TOKEN_SYNTAX_ERROR_NUMBER:
        fputs("(error number, ", out);
        break;
    case TOKEN_SYNTAX_ERROR_CHAR:
        fputs("(error char, ", out);
        break;
    case TOKEN_SYNTAX_ERROR_STRING:
        fputs("(error string, ", out);
        break;
    default:
        fputs("(unknown, ", out);
        break;
    }
    fprintf(out, "%zu, %zu, ", token->line, token->column);
    write_value(out, token->value);
    fputc(')', out);
}
void output_tokens(string filename, List_Token *tokens) {
    FILE *out = open_file(filename);
    if (out == ((void *)0))
        return;
    for (List *token__l = (tokens); token__l != ((void *)0) && token__l->head != ((void *)0); token__l = ((void *)0))
        for (ListNode *token__n = token__l->head; token__n != ((void *)0); token__n = token__n->next)
            for (Token *token = (Token *)token__n->data; token != ((void *)0); token = ((void *)0)) {
                output_one_token(out, token);
                fputc('\n', out);
            }
    fclose(out);
}
void print_tokens(string filename, List_Token *tokens) {
    FILE *out = open_file(filename);
    if (out == ((void *)0))
        return;
    _Bool first = 1;
    for (List *token__l = (tokens); token__l != ((void *)0) && token__l->head != ((void *)0); token__l = ((void *)0))
        for (ListNode *token__n = token__l->head; token__n != ((void *)0); token__n = token__n->next)
            for (Token *token = (Token *)token__n->data; token != ((void *)0); token = ((void *)0)) {
                if (token->type == TOKEN_EOF)
                    break;
                if (token->value == ((void *)0))
                    continue;
                write_spacing(out, first, token->at_line_start, token->space_before, token->column);
                fputs(token->value, out);
                first = 0;
            }
    fputc('\n', out);
    fclose(out);
}
static Token *parent_token = ((void *)0);
static _Bool open_ast_node(FILE *out, const char *name, Token *token, _Bool is_null, size_t indent) {
    for (size_t i = 0; i < (indent); ++i)
        fputc('\t', out);
    fputs(name, out);
    if (is_null) {
        fputs(": null", out);
        return 0;
    }
    fputs(": {\n", out);
    if (token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, token);
        fputs(",\n", out);
    }
    parent_token = token;
    return 1;
}
static void output_assignment_expression(FILE *out, AssignmentExpression *node, size_t indent);
static void output_conditional_expression(FILE *out, ConditionalExpression *node, size_t indent);
static void output_binary_expression(FILE *out, BinaryExpression *node, size_t indent);
static void output_cast_expression(FILE *out, CastExpression *node, size_t indent);
static void output_unary_expression(FILE *out, UnaryExpression *node, size_t indent);
static void output_postfix_expression(FILE *out, PostfixExpression *node, size_t indent);
static void output_primary_expression(FILE *out, PrimaryExpression *node, size_t indent);
static void output_decl_stmt(FILE *out, DeclStmt *node, size_t indent);
static void output_statement(FILE *out, Statement *node, size_t indent);
static void output_struct_decl(FILE *out, StructDecl *node, size_t indent);
static void output_specifier_qualifier(FILE *out, SpecifierQualifier *node, size_t indent);
static void output_type_name(FILE *out, TypeName *node, size_t indent);
static void output_pointer(FILE *out, Pointer *node, size_t indent);
static void output_initializer_item(FILE *out, InitializerItem *node, size_t indent);
static void output_initializer(FILE *out, Initializer *node, size_t indent);
static void output_type_spec(FILE *out, TypeSpec *node, size_t indent);
static void output_declarator(FILE *out, Declarator *node, size_t indent);
static void output_decl_spec(FILE *out, DeclSpec *node, size_t indent);
static void output_static_assert_decl(FILE *out, StaticAssertDecl *node, size_t indent);
static void output_var_decl(FILE *out, VarDecl *node, size_t indent);
static void output_assignment_expression(FILE *out, AssignmentExpression *node, size_t indent) {
    do {
        if (node != ((void *)0) && (node->is_conditional)) {
            output_conditional_expression(out, (node->expr.cond_expr), indent);
            return;
        }
    } while (0);
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("AssignmentExpression"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("AssignmentExpression"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("op"": ", out);
        } while (0);
        write_value(out, (node->expr.binary.op));
        fputs(",\n", out);
    } while (0);
    do {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("left"": {\n", out);
        } while (0);
        do {
            output_unary_expression(out, (node->expr.binary.left), indent + ((1) + 1));
            fputs(",\n", out);
        } while (0);
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("},\n", out);
        } while (0);
    } while (0);
    do {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("right"": {\n", out);
        } while (0);
        do {
            output_assignment_expression(out, (node->expr.binary.right), indent + ((1) + 1));
            fputs(",\n", out);
        } while (0);
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("},\n", out);
        } while (0);
    } while (0);
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_conditional_expression(FILE *out, ConditionalExpression *node, size_t indent) {
    do {
        if (node != ((void *)0) && (node->false_expr == ((void *)0))) {
            output_binary_expression(out, (node->binary_expr), indent);
            return;
        }
    } while (0);
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("ConditionalExpression"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("ConditionalExpression"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("cond"": {\n", out);
        } while (0);
        do {
            output_binary_expression(out, (node->binary_expr), indent + ((1) + 1));
            fputs(",\n", out);
        } while (0);
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("},\n", out);
        } while (0);
    } while (0);
    do {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("true_expr"": [\n", out);
        } while (0);
        for (List *item__l = ((node->true_expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
            for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0))
                    do {
                        output_assignment_expression(out, (item), indent + ((1) + 1));
                        fputs(",\n", out);
                    } while (0);
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("],\n", out);
        } while (0);
    } while (0);
    do {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("false_expr"": {\n", out);
        } while (0);
        do {
            output_conditional_expression(out, (node->false_expr), indent + ((1) + 1));
            fputs(",\n", out);
        } while (0);
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("},\n", out);
        } while (0);
    } while (0);
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_binary_expression(FILE *out, BinaryExpression *node, size_t indent) {
    do {
        if (node != ((void *)0) && (node->is_cast)) {
            output_cast_expression(out, (node->expr.cast), indent);
            return;
        }
    } while (0);
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("BinaryExpression"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("BinaryExpression"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("op"": ", out);
        } while (0);
        write_value(out, (node->expr.binary.op));
        fputs(",\n", out);
    } while (0);
    do {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("left"": {\n", out);
        } while (0);
        do {
            output_binary_expression(out, (node->expr.binary.left), indent + ((1) + 1));
            fputs(",\n", out);
        } while (0);
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("},\n", out);
        } while (0);
    } while (0);
    do {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("right"": {\n", out);
        } while (0);
        do {
            output_binary_expression(out, (node->expr.binary.right), indent + ((1) + 1));
            fputs(",\n", out);
        } while (0);
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("},\n", out);
        } while (0);
    } while (0);
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_cast_expression(FILE *out, CastExpression *node, size_t indent) {
    do {
        if (node != ((void *)0) && (!node->is_cast)) {
            output_unary_expression(out, (node->expr.unary_expr), indent);
            return;
        }
    } while (0);
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("CastExpression"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("CastExpression"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        output_type_name(out, (node->expr.cast.type_name), indent + (1));
        fputs(",\n", out);
    } while (0);
    do {
        output_cast_expression(out, (node->expr.cast.cast_expr), indent + (1));
        fputs(",\n", out);
    } while (0);
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_unary_expression(FILE *out, UnaryExpression *node, size_t indent) {
    do {
        if (node != ((void *)0) && (node->expr_type == UNARY_POSTFIX)) {
            output_postfix_expression(out, (node->expr.postfix), indent);
            return;
        }
    } while (0);
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("UnaryExpression"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("UnaryExpression"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        for (size_t i = 0; i < (indent + 1); ++i)
            fputc('\t', out);
        fputs("expr_type: ", out);
    } while (0);
    switch (node->expr_type) {
    case UNARY_PREFIX:
        fputs("UNARY_PREFIX,\n", out);
        break;
    case UNARY_UNARY_OP:
        fputs("UNARY_UNARY_OP,\n", out);
        break;
    case UNARY_FUNCTION_LIKE:
        fputs("UNARY_FUNCTION_LIKE,\n", out);
        break;
    case UNARY_POSTFIX:
        fputs("UNARY_POSTFIX,\n", out);
        break;
    default:
        fputs("unknown,\n", out);
        break;
    }
    if (node->expr_type == UNARY_PREFIX) {
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("op"": ", out);
            } while (0);
            write_value(out, (node->expr.prefix.op));
            fputs(",\n", out);
        } while (0);
        do {
            output_unary_expression(out, (node->expr.prefix.unary_expr), indent + (1));
            fputs(",\n", out);
        } while (0);
    } else if (node->expr_type == UNARY_UNARY_OP) {
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("op"": ", out);
            } while (0);
            write_value(out, (node->expr.unary_op.op));
            fputs(",\n", out);
        } while (0);
        do {
            output_cast_expression(out, (node->expr.unary_op.cast_expr), indent + (1));
            fputs(",\n", out);
        } while (0);
    } else if (node->expr_type == UNARY_FUNCTION_LIKE) {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fprintf(out, "is_sizeof"": %s,\n", (node->expr.function_like.is_sizeof) ? "true" : "false");
        } while (0);
        do {
            output_type_name(out, (node->expr.function_like.type_name), indent + (1));
            fputs(",\n", out);
        } while (0);
    }
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_postfix_expression(FILE *out, PostfixExpression *node, size_t indent) {
    do {
        if (node != ((void *)0) && (node->expr_type == POSTFIX_PRIMARY)) {
            output_primary_expression(out, (node->expr.primary_expr), indent);
            return;
        }
    } while (0);
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("PostfixExpression"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("PostfixExpression"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        for (size_t i = 0; i < (indent + 1); ++i)
            fputc('\t', out);
        fputs("expr_type: ", out);
    } while (0);
    switch (node->expr_type) {
    case POSTFIX_PRIMARY:
        fputs("POSTFIX_PRIMARY,\n", out);
        break;
    case POSTFIX_COMPOUND_LITERAL:
        fputs("POSTFIX_COMPOUND_LITERAL,\n", out);
        break;
    case POSTFIX_ARRAY_ACCESS:
        fputs("POSTFIX_ARRAY_ACCESS,\n", out);
        break;
    case POSTFIX_FUNC_CALL:
        fputs("POSTFIX_FUNC_CALL,\n", out);
        break;
    case POSTFIX_OP:
        fputs("POSTFIX_OP,\n", out);
        break;
    default:
        fputs("unknown,\n", out);
        break;
    }
    if (node->expr_type == POSTFIX_COMPOUND_LITERAL) {
        do {
            output_type_name(out, (node->expr.compound_literal.type_name), indent + (1));
            fputs(",\n", out);
        } while (0);
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("initializer_list"": [\n", out);
            } while (0);
            for (List *item__l = ((node->expr.compound_literal.initializer_list)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                    for (InitializerItem *item = (InitializerItem *)item__n->data; item != ((void *)0); item = ((void *)0))
                        do {
                            output_initializer_item(out, (item), indent + ((1) + 1));
                            fputs(",\n", out);
                        } while (0);
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("],\n", out);
            } while (0);
        } while (0);
    } else if (node->expr_type == POSTFIX_ARRAY_ACCESS) {
        do {
            output_postfix_expression(out, (node->expr.array_access.postfix_expr), indent + (1));
            fputs(",\n", out);
        } while (0);
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("index_expr"": [\n", out);
            } while (0);
            for (List *item__l = ((node->expr.array_access.index_expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                    for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0))
                        do {
                            output_assignment_expression(out, (item), indent + ((1) + 1));
                            fputs(",\n", out);
                        } while (0);
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("],\n", out);
            } while (0);
        } while (0);
    } else if (node->expr_type == POSTFIX_FUNC_CALL) {
        do {
            output_postfix_expression(out, (node->expr.func_call.postfix_expr), indent + (1));
            fputs(",\n", out);
        } while (0);
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("args"": [\n", out);
            } while (0);
            for (List *item__l = ((node->expr.func_call.args)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                    for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0))
                        do {
                            output_assignment_expression(out, (item), indent + ((1) + 1));
                            fputs(",\n", out);
                        } while (0);
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("],\n", out);
            } while (0);
        } while (0);
    } else if (node->expr_type == POSTFIX_OP) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("op_type: ", out);
        } while (0);
        switch (node->expr.postfix_op.op_type) {
        case POSTFIX_MEMBER_ACCESS:
            fputs("POSTFIX_MEMBER_ACCESS,\n", out);
            break;
        case POSTFIX_MEMBER_ACCESS_PTR:
            fputs("POSTFIX_MEMBER_ACCESS_PTR,\n", out);
            break;
        case POSTFIX_INCREMENT:
            fputs("POSTFIX_INCREMENT,\n", out);
            break;
        case POSTFIX_DECREMENT:
            fputs("POSTFIX_DECREMENT,\n", out);
            break;
        default:
            fputs("unknown,\n", out);
            break;
        }
        if (node->expr.postfix_op.identifier != ((void *)0))
            do {
                do {
                    for (size_t i = 0; i < (indent + (1)); ++i)
                        fputc('\t', out);
                    fputs("identifier"": ", out);
                } while (0);
                output_one_token(out, (node->expr.postfix_op.identifier));
                fputs(",\n", out);
            } while (0);
        do {
            output_postfix_expression(out, (node->expr.postfix_op.postfix_expr), indent + (1));
            fputs(",\n", out);
        } while (0);
    }
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_primary_expression(FILE *out, PrimaryExpression *node, size_t indent) {
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("PrimaryExpression"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("PrimaryExpression"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        for (size_t i = 0; i < (indent + 1); ++i)
            fputc('\t', out);
        fputs("primary_type: ", out);
    } while (0);
    switch (node->primary_type) {
    case PRIMARY_IDENTIFIER:
        fputs("PRIMARY_IDENTIFIER,\n", out);
        break;
    case PRIMARY_INTEGER_CONSTANT:
        fputs("PRIMARY_INTEGER_CONSTANT,\n", out);
        break;
    case PRIMARY_CHARACTER_CONSTANT:
        fputs("PRIMARY_CHARACTER_CONSTANT,\n", out);
        break;
    case PRIMARY_FLOATING_CONSTANT:
        fputs("PRIMARY_FLOATING_CONSTANT,\n", out);
        break;
    case PRIMARY_STRING_LITERAL:
        fputs("PRIMARY_STRING_LITERAL,\n", out);
        break;
    case PRIMARY_EXPRESSION:
        fputs("PRIMARY_EXPRESSION,\n", out);
        break;
    case PRIMARY_GENERIC_SELECTION:
        fputs("PRIMARY_GENERIC_SELECTION,\n", out);
        break;
    default:
        fputs("unknown,\n", out);
        break;
    }
    switch (node->primary_type) {
    case PRIMARY_IDENTIFIER:
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("identifier"": ", out);
            } while (0);
            output_one_token(out, (node->primary.identifier));
            fputs(",\n", out);
        } while (0);
        break;
    case PRIMARY_INTEGER_CONSTANT:
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("integer_constant"": ", out);
            } while (0);
            output_one_token(out, (node->primary.integer_constant));
            fputs(",\n", out);
        } while (0);
        break;
    case PRIMARY_CHARACTER_CONSTANT:
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("character_constant"": ", out);
            } while (0);
            output_one_token(out, (node->primary.character_constant));
            fputs(",\n", out);
        } while (0);
        break;
    case PRIMARY_FLOATING_CONSTANT:
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("floating_constant"": ", out);
            } while (0);
            output_one_token(out, (node->primary.floating_constant));
            fputs(",\n", out);
        } while (0);
        break;
    case PRIMARY_STRING_LITERAL:
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("string_literal"": ", out);
            } while (0);
            output_one_token(out, (node->primary.string_literal));
            fputs(",\n", out);
        } while (0);
        break;
    case PRIMARY_EXPRESSION:
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("expr"": [\n", out);
            } while (0);
            for (List *item__l = ((node->primary.expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                    for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0))
                        do {
                            output_assignment_expression(out, (item), indent + ((1) + 1));
                            fputs(",\n", out);
                        } while (0);
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("],\n", out);
            } while (0);
        } while (0);
        break;
    case PRIMARY_GENERIC_SELECTION:
        do {
            output_assignment_expression(out, (node->primary.generic_selection.expr), indent + (1));
            fputs(",\n", out);
        } while (0);
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("generic_assoc_list: [\n", out);
        } while (0);
        for (List *assoc__l = (node->primary.generic_selection.generic_assoc_list); assoc__l != ((void *)0) && assoc__l->head != ((void *)0); assoc__l = ((void *)0))
            for (ListNode *assoc__n = assoc__l->head; assoc__n != ((void *)0); assoc__n = assoc__n->next)
                for (GenericAssociation *assoc = (GenericAssociation *)assoc__n->data; assoc != ((void *)0); assoc = ((void *)0)) {
                    if (open_ast_node(out, "GenericAssociation", (assoc) == ((void *)0) ? ((void *)0) : (assoc)->token, (assoc) == ((void *)0), indent + (2))) {
                        if (assoc->type_name == ((void *)0))
                            do {
                                for (size_t i = 0; i < (indent + 3); ++i)
                                    fputc('\t', out);
                                fputs("type_name: default,\n", out);
                            } while (0);
                        else
                            do {
                                output_type_name(out, (assoc->type_name), indent + (3));
                                fputs(",\n", out);
                            } while (0);
                        do {
                            output_assignment_expression(out, (assoc->assignment_expr), indent + (3));
                            fputs(",\n", out);
                        } while (0);
                        do {
                            parent_token = node->token;
                            do {
                                for (size_t i = 0; i < (indent + (2)); ++i)
                                    fputc('\t', out);
                                fputs("}", out);
                            } while (0);
                        } while (0);
                    }
                    fputs(",\n", out);
                }
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("],\n", out);
        } while (0);
        break;
    default:
        break;
    }
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_decl_stmt(FILE *out, DeclStmt *node, size_t indent) {
    do {
        if (node != ((void *)0) && (node->is_var_decl)) {
            output_var_decl(out, (node->item.var_decl), indent);
            return;
        }
    } while (0);
    do {
        if (node != ((void *)0) && (!node->is_var_decl)) {
            output_statement(out, (node->item.statement), indent);
            return;
        }
    } while (0);
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("DeclStmt: null", out);
    } while (0);
}
static void output_labeled_statement(FILE *out, LabeledStatement *node, size_t indent) {
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("LabeledStatement"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("LabeledStatement"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        for (size_t i = 0; i < (indent + 1); ++i)
            fputc('\t', out);
        fputs("label_type: ", out);
    } while (0);
    switch (node->label_type) {
    case LABEL_IDENTIFIER:
        fputs("LABEL_IDENTIFIER,\n", out);
        break;
    case LABEL_CASE:
        fputs("LABEL_CASE,\n", out);
        break;
    case LABEL_DEFAULT:
        fputs("LABEL_DEFAULT,\n", out);
        break;
    default:
        fputs("unknown,\n", out);
        break;
    }
    if (node->label_type == LABEL_IDENTIFIER)
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("identifier"": ", out);
            } while (0);
            output_one_token(out, (node->label.identifier));
            fputs(",\n", out);
        } while (0);
    else if (node->label_type == LABEL_CASE)
        do {
            output_conditional_expression(out, (node->label.case_stmt), indent + (1));
            fputs(",\n", out);
        } while (0);
    do {
        output_statement(out, (node->stmt), indent + (1));
        fputs(",\n", out);
    } while (0);
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_selection_statement(FILE *out, SelectionStatement *node, size_t indent) {
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("SelectionStatement"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("SelectionStatement"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        for (size_t i = 0; i < (indent + (1)); ++i)
            fputc('\t', out);
        fprintf(out, "is_switch"": %s,\n", (node->is_switch) ? "true" : "false");
    } while (0);
    if (node->is_switch) {
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("cond_expr"": [\n", out);
            } while (0);
            for (List *item__l = ((node->selection.switch_stmt.cond_expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                    for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0))
                        do {
                            output_assignment_expression(out, (item), indent + ((1) + 1));
                            fputs(",\n", out);
                        } while (0);
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("],\n", out);
            } while (0);
        } while (0);
        do {
            output_statement(out, (node->selection.switch_stmt.stmt), indent + (1));
            fputs(",\n", out);
        } while (0);
    } else {
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("cond_expr"": [\n", out);
            } while (0);
            for (List *item__l = ((node->selection.if_stmt.cond_expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                    for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0))
                        do {
                            output_assignment_expression(out, (item), indent + ((1) + 1));
                            fputs(",\n", out);
                        } while (0);
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("],\n", out);
            } while (0);
        } while (0);
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("then_stmt"": {\n", out);
            } while (0);
            do {
                output_statement(out, (node->selection.if_stmt.then_stmt), indent + ((1) + 1));
                fputs(",\n", out);
            } while (0);
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("},\n", out);
            } while (0);
        } while (0);
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("else_stmt"": {\n", out);
            } while (0);
            do {
                output_statement(out, (node->selection.if_stmt.else_stmt), indent + ((1) + 1));
                fputs(",\n", out);
            } while (0);
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("},\n", out);
            } while (0);
        } while (0);
    }
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_iteration_statement(FILE *out, IterationStatement *node, size_t indent) {
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("IterationStatement"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("IterationStatement"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        for (size_t i = 0; i < (indent + 1); ++i)
            fputc('\t', out);
        fputs("loop_type: ", out);
    } while (0);
    switch (node->loop_type) {
    case LOOP_WHILE:
        fputs("LOOP_WHILE,\n", out);
        break;
    case LOOP_DO_WHILE:
        fputs("LOOP_DO_WHILE,\n", out);
        break;
    case LOOP_FOR:
        fputs("LOOP_FOR,\n", out);
        break;
    default:
        fputs("unknown,\n", out);
        break;
    }
    if (node->loop_type == LOOP_WHILE || node->loop_type == LOOP_DO_WHILE) {
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("expr"": [\n", out);
            } while (0);
            for (List *item__l = ((node->loop.while_stmt.expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                    for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0))
                        do {
                            output_assignment_expression(out, (item), indent + ((1) + 1));
                            fputs(",\n", out);
                        } while (0);
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("],\n", out);
            } while (0);
        } while (0);
        do {
            output_statement(out, (node->loop.while_stmt.stmt), indent + (1));
            fputs(",\n", out);
        } while (0);
    } else if (node->loop_type == LOOP_FOR) {
        if (node->loop.for_stmt.is_init_decl)
            do {
                output_var_decl(out, (node->loop.for_stmt.init.init_decl), indent + (1));
                fputs(",\n", out);
            } while (0);
        else
            do {
                do {
                    for (size_t i = 0; i < (indent + (1)); ++i)
                        fputc('\t', out);
                    fputs("init_expr"": [\n", out);
                } while (0);
                for (List *item__l = ((node->loop.for_stmt.init.init_expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                    for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                        for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0))
                            do {
                                output_assignment_expression(out, (item), indent + ((1) + 1));
                                fputs(",\n", out);
                            } while (0);
                do {
                    for (size_t i = 0; i < (indent + (1)); ++i)
                        fputc('\t', out);
                    fputs("],\n", out);
                } while (0);
            } while (0);
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("cond_expr"": [\n", out);
            } while (0);
            for (List *item__l = ((node->loop.for_stmt.cond_expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                    for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0))
                        do {
                            output_assignment_expression(out, (item), indent + ((1) + 1));
                            fputs(",\n", out);
                        } while (0);
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("],\n", out);
            } while (0);
        } while (0);
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("loop_expr"": [\n", out);
            } while (0);
            for (List *item__l = ((node->loop.for_stmt.loop_expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                    for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0))
                        do {
                            output_assignment_expression(out, (item), indent + ((1) + 1));
                            fputs(",\n", out);
                        } while (0);
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("],\n", out);
            } while (0);
        } while (0);
        do {
            output_statement(out, (node->loop.for_stmt.stmt), indent + (1));
            fputs(",\n", out);
        } while (0);
    }
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_jump_statement(FILE *out, JumpStatement *node, size_t indent) {
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("JumpStatement"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("JumpStatement"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        for (size_t i = 0; i < (indent + 1); ++i)
            fputc('\t', out);
        fputs("jump_type: ", out);
    } while (0);
    switch (node->jump_type) {
    case JUMP_GOTO:
        fputs("JUMP_GOTO,\n", out);
        break;
    case JUMP_CONTINUE:
        fputs("JUMP_CONTINUE,\n", out);
        break;
    case JUMP_BREAK:
        fputs("JUMP_BREAK,\n", out);
        break;
    case JUMP_RETURN:
        fputs("JUMP_RETURN,\n", out);
        break;
    default:
        fputs("unknown,\n", out);
        break;
    }
    if (node->jump_type == JUMP_GOTO)
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("identifier"": ", out);
            } while (0);
            output_one_token(out, (node->jump.identifier));
            fputs(",\n", out);
        } while (0);
    else if (node->jump_type == JUMP_RETURN)
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("expr"": [\n", out);
            } while (0);
            for (List *item__l = ((node->jump.expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                    for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0))
                        do {
                            output_assignment_expression(out, (item), indent + ((1) + 1));
                            fputs(",\n", out);
                        } while (0);
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("],\n", out);
            } while (0);
        } while (0);
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_statement(FILE *out, Statement *node, size_t indent) {
    do {
        if (node != ((void *)0) && (node->stmt_type == STMT_LABELED)) {
            output_labeled_statement(out, (node->stmt.label), indent);
            return;
        }
    } while (0);
    do {
        if (node != ((void *)0) && (node->stmt_type == STMT_SELECTION)) {
            output_selection_statement(out, (node->stmt.selection), indent);
            return;
        }
    } while (0);
    do {
        if (node != ((void *)0) && (node->stmt_type == STMT_ITERATION)) {
            output_iteration_statement(out, (node->stmt.iteration), indent);
            return;
        }
    } while (0);
    do {
        if (node != ((void *)0) && (node->stmt_type == STMT_JUMP)) {
            output_jump_statement(out, (node->stmt.jump), indent);
            return;
        }
    } while (0);
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("Statement"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("Statement"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        for (size_t i = 0; i < (indent + 1); ++i)
            fputc('\t', out);
        fputs("stmt_type: ", out);
    } while (0);
    switch (node->stmt_type) {
    case STMT_LABELED:
        fputs("STMT_LABELED,\n", out);
        break;
    case STMT_COMPOUND:
        fputs("STMT_COMPOUND,\n", out);
        break;
    case STMT_EXPRESSION:
        fputs("STMT_EXPRESSION,\n", out);
        break;
    case STMT_SELECTION:
        fputs("STMT_SELECTION,\n", out);
        break;
    case STMT_ITERATION:
        fputs("STMT_ITERATION,\n", out);
        break;
    case STMT_JUMP:
        fputs("STMT_JUMP,\n", out);
        break;
    default:
        fputs("unknown,\n", out);
        break;
    }
    if (node->stmt_type == STMT_COMPOUND)
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("compound"": [\n", out);
            } while (0);
            for (List *item__l = ((node->stmt.compound)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                    for (DeclStmt *item = (DeclStmt *)item__n->data; item != ((void *)0); item = ((void *)0))
                        do {
                            output_decl_stmt(out, (item), indent + ((1) + 1));
                            fputs(",\n", out);
                        } while (0);
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("],\n", out);
            } while (0);
        } while (0);
    else if (node->stmt_type == STMT_EXPRESSION)
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("expression"": [\n", out);
            } while (0);
            for (List *item__l = ((node->stmt.expression)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                    for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0))
                        do {
                            output_assignment_expression(out, (item), indent + ((1) + 1));
                            fputs(",\n", out);
                        } while (0);
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("],\n", out);
            } while (0);
        } while (0);
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_struct_decl(FILE *out, StructDecl *node, size_t indent) {
    do {
        if (node != ((void *)0) && (node->is_static_assert_decl)) {
            output_static_assert_decl(out, (node->decl.static_assert_decl), indent);
            return;
        }
    } while (0);
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("StructDecl"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("StructDecl"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("spec_qual_list"": [\n", out);
        } while (0);
        for (List *item__l = ((node->decl.general_struct_decl.spec_qual_list)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
            for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                for (SpecifierQualifier *item = (SpecifierQualifier *)item__n->data; item != ((void *)0); item = ((void *)0))
                    do {
                        output_specifier_qualifier(out, (item), indent + ((1) + 1));
                        fputs(",\n", out);
                    } while (0);
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("],\n", out);
        } while (0);
    } while (0);
    do {
        for (size_t i = 0; i < (indent + 1); ++i)
            fputc('\t', out);
        fputs("struct_declarators: [\n", out);
    } while (0);
    for (List *decl__l = (node->decl.general_struct_decl.struct_declarators); decl__l != ((void *)0) && decl__l->head != ((void *)0); decl__l = ((void *)0))
        for (ListNode *decl__n = decl__l->head; decl__n != ((void *)0); decl__n = decl__n->next)
            for (StructDeclarator *decl = (StructDeclarator *)decl__n->data; decl != ((void *)0); decl = ((void *)0)) {
                if (open_ast_node(out, "StructDeclarator", (decl) == ((void *)0) ? ((void *)0) : (decl)->token, (decl) == ((void *)0), indent + (2))) {
                    do {
                        output_declarator(out, (decl->declarator), indent + (3));
                        fputs(",\n", out);
                    } while (0);
                    do {
                        output_conditional_expression(out, (decl->constant_expr), indent + (3));
                        fputs(",\n", out);
                    } while (0);
                    do {
                        parent_token = node->token;
                        do {
                            for (size_t i = 0; i < (indent + (2)); ++i)
                                fputc('\t', out);
                            fputs("}", out);
                        } while (0);
                    } while (0);
                }
                fputs(",\n", out);
            }
    do {
        for (size_t i = 0; i < (indent + 1); ++i)
            fputc('\t', out);
        fputs("],\n", out);
    } while (0);
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_specifier_qualifier(FILE *out, SpecifierQualifier *node, size_t indent) {
    do {
        if (node != ((void *)0) && (node->is_type_spec)) {
            output_type_spec(out, (node->spec.type_spec), indent);
            return;
        }
    } while (0);
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("SpecifierQualifier"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("SpecifierQualifier"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("type_qualifier"": ", out);
        } while (0);
        write_value(out, (node->spec.type_qualifier));
        fputs(",\n", out);
    } while (0);
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_type_name(FILE *out, TypeName *node, size_t indent) {
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("TypeName"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("TypeName"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("spec_qual_list"": [\n", out);
        } while (0);
        for (List *item__l = ((node->spec_qual_list)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
            for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                for (SpecifierQualifier *item = (SpecifierQualifier *)item__n->data; item != ((void *)0); item = ((void *)0))
                    do {
                        output_specifier_qualifier(out, (item), indent + ((1) + 1));
                        fputs(",\n", out);
                    } while (0);
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("],\n", out);
        } while (0);
    } while (0);
    do {
        output_declarator(out, (node->abs_declarator), indent + (1));
        fputs(",\n", out);
    } while (0);
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_type_spec(FILE *out, TypeSpec *node, size_t indent) {
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("TypeSpec"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("TypeSpec"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        for (size_t i = 0; i < (indent + 1); ++i)
            fputc('\t', out);
        fputs("spec_type: ", out);
    } while (0);
    switch (node->spec_type) {
    case TYPE_SPEC_KEYWORD:
        fputs("TYPE_SPEC_KEYWORD,\n", out);
        break;
    case TYPE_SPEC_ATOMIC:
        fputs("TYPE_SPEC_ATOMIC,\n", out);
        break;
    case TYPE_SPEC_STRUCT_UNION:
        fputs("TYPE_SPEC_STRUCT_UNION,\n", out);
        break;
    case TYPE_SPEC_ENUM:
        fputs("TYPE_SPEC_ENUM,\n", out);
        break;
    case TYPE_SPEC_TYPEDEF_NAME:
        fputs("TYPE_SPEC_TYPEDEF_NAME,\n", out);
        break;
    default:
        fputs("unknown,\n", out);
        break;
    }
    if (node->spec_type == TYPE_SPEC_KEYWORD) {
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("keyword_spec"": ", out);
            } while (0);
            write_value(out, (node->spec.keyword_spec));
            fputs(",\n", out);
        } while (0);
    } else if (node->spec_type == TYPE_SPEC_ATOMIC) {
        do {
            output_type_name(out, (node->spec.atomic_spec), indent + (1));
            fputs(",\n", out);
        } while (0);
    } else if (node->spec_type == TYPE_SPEC_STRUCT_UNION) {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fprintf(out, "is_struct"": %s,\n", (node->spec.struct_union_spec.is_struct) ? "true" : "false");
        } while (0);
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("identifier"": ", out);
            } while (0);
            output_one_token(out, (node->spec.struct_union_spec.identifier));
            fputs(",\n", out);
        } while (0);
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("members"": [\n", out);
            } while (0);
            for (List *item__l = ((node->spec.struct_union_spec.members)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                    for (StructDecl *item = (StructDecl *)item__n->data; item != ((void *)0); item = ((void *)0))
                        do {
                            output_struct_decl(out, (item), indent + ((1) + 1));
                            fputs(",\n", out);
                        } while (0);
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("],\n", out);
            } while (0);
        } while (0);
    } else if (node->spec_type == TYPE_SPEC_ENUM) {
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("identifier"": ", out);
            } while (0);
            output_one_token(out, (node->spec.enum_spec.identifier));
            fputs(",\n", out);
        } while (0);
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("enumerators: [\n", out);
        } while (0);
        for (List *enumerator__l = (node->spec.enum_spec.enumerators); enumerator__l != ((void *)0) && enumerator__l->head != ((void *)0); enumerator__l = ((void *)0))
            for (ListNode *enumerator__n = enumerator__l->head; enumerator__n != ((void *)0); enumerator__n = enumerator__n->next)
                for (Enumerator *enumerator = (Enumerator *)enumerator__n->data; enumerator != ((void *)0); enumerator = ((void *)0)) {
                    if (open_ast_node(out, "Enumerator", (enumerator) == ((void *)0) ? ((void *)0) : (enumerator)->token, (enumerator) == ((void *)0), indent + (2))) {
                        do {
                            do {
                                for (size_t i = 0; i < (indent + (3)); ++i)
                                    fputc('\t', out);
                                fputs("identifier"": ", out);
                            } while (0);
                            output_one_token(out, (enumerator->identifier));
                            fputs(",\n", out);
                        } while (0);
                        do {
                            output_conditional_expression(out, (enumerator->constant_expr), indent + (3));
                            fputs(",\n", out);
                        } while (0);
                        do {
                            parent_token = node->token;
                            do {
                                for (size_t i = 0; i < (indent + (2)); ++i)
                                    fputc('\t', out);
                                fputs("}", out);
                            } while (0);
                        } while (0);
                    }
                    fputs(",\n", out);
                }
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("],\n", out);
        } while (0);
    } else if (node->spec_type == TYPE_SPEC_TYPEDEF_NAME) {
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("typedef_name"": ", out);
            } while (0);
            output_one_token(out, (node->spec.typedef_name));
            fputs(",\n", out);
        } while (0);
    }
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_pointer(FILE *out, Pointer *node, size_t indent) {
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("Pointer"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("Pointer"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("type_qualifiers"": [", out);
        } while (0);
        for (List *str__l = ((node->type_qualifiers)); str__l != ((void *)0) && str__l->head != ((void *)0); str__l = ((void *)0))
            for (ListNode *str__n = str__l->head; str__n != ((void *)0); str__n = str__n->next)
                for (string str = (string)str__n->data; str != ((void *)0); str = ((void *)0)) {
                    write_value(out, str);
                    fputs(", ", out);
                }
        fputs("],\n", out);
    } while (0);
    do {
        output_pointer(out, (node->pointer), indent + (1));
        fputs(",\n", out);
    } while (0);
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_direct_declarator(FILE *out, DirectDeclarator *node, size_t indent) {
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("DirectDeclarator"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("DirectDeclarator"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        for (size_t i = 0; i < (indent + 1); ++i)
            fputc('\t', out);
        fputs("decl_type: ", out);
    } while (0);
    switch (node->decl_type) {
    case DECLARATOR_ID:
        fputs("DECLARATOR_ID,\n", out);
        break;
    case DECLARATOR_DECL:
        fputs("DECLARATOR_DECL,\n", out);
        break;
    case DECLARATOR_ARRAY:
        fputs("DECLARATOR_ARRAY,\n", out);
        break;
    case DECLARATOR_FUNC:
        fputs("DECLARATOR_FUNC,\n", out);
        break;
    case DECLARATOR_INCOMPLETE_ARRAY:
        fputs("DECLARATOR_INCOMPLETE_ARRAY,\n", out);
        break;
    default:
        fputs("unknown,\n", out);
        break;
    }
    if (node->decl_type == DECLARATOR_ID) {
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("identifier"": ", out);
            } while (0);
            output_one_token(out, (node->decl.identifier));
            fputs(",\n", out);
        } while (0);
    } else if (node->decl_type == DECLARATOR_DECL) {
        do {
            output_declarator(out, (node->decl.declarator), indent + (1));
            fputs(",\n", out);
        } while (0);
    } else if (node->decl_type == DECLARATOR_ARRAY) {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fprintf(out, "is_static"": %s,\n", (node->decl.array.is_static) ? "true" : "false");
        } while (0);
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("type_qualifiers"": [", out);
            } while (0);
            for (List *str__l = ((node->decl.array.type_qualifiers)); str__l != ((void *)0) && str__l->head != ((void *)0); str__l = ((void *)0))
                for (ListNode *str__n = str__l->head; str__n != ((void *)0); str__n = str__n->next)
                    for (string str = (string)str__n->data; str != ((void *)0); str = ((void *)0)) {
                        write_value(out, str);
                        fputs(", ", out);
                    }
            fputs("],\n", out);
        } while (0);
        do {
            output_assignment_expression(out, (node->decl.array.assignment_expression), indent + (1));
            fputs(",\n", out);
        } while (0);
        do {
            output_direct_declarator(out, (node->decl.array.direct_declarator), indent + (1));
            fputs(",\n", out);
        } while (0);
    } else if (node->decl_type == DECLARATOR_FUNC) {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fprintf(out, "is_variadic"": %s,\n", (node->decl.func.is_variadic) ? "true" : "false");
        } while (0);
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("param_decls: [\n", out);
        } while (0);
        for (List *param__l = (node->decl.func.param_decls); param__l != ((void *)0) && param__l->head != ((void *)0); param__l = ((void *)0))
            for (ListNode *param__n = param__l->head; param__n != ((void *)0); param__n = param__n->next)
                for (ParamDecl *param = (ParamDecl *)param__n->data; param != ((void *)0); param = ((void *)0)) {
                    if (open_ast_node(out, "ParamDecl", (param) == ((void *)0) ? ((void *)0) : (param)->token, (param) == ((void *)0), indent + (2))) {
                        do {
                            for (size_t i = 0; i < (indent + (3)); ++i)
                                fputc('\t', out);
                            fprintf(out, "is_abs"": %s,\n", (param->is_abs) ? "true" : "false");
                        } while (0);
                        do {
                            do {
                                for (size_t i = 0; i < (indent + (3)); ++i)
                                    fputc('\t', out);
                                fputs("decl_specs"": [\n", out);
                            } while (0);
                            for (List *item__l = ((param->decl_specs)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                                    for (DeclSpec *item = (DeclSpec *)item__n->data; item != ((void *)0); item = ((void *)0))
                                        do {
                                            output_decl_spec(out, (item), indent + ((3) + 1));
                                            fputs(",\n", out);
                                        } while (0);
                            do {
                                for (size_t i = 0; i < (indent + (3)); ++i)
                                    fputc('\t', out);
                                fputs("],\n", out);
                            } while (0);
                        } while (0);
                        do {
                            output_declarator(out, (param->decl), indent + (3));
                            fputs(",\n", out);
                        } while (0);
                        do {
                            parent_token = node->token;
                            do {
                                for (size_t i = 0; i < (indent + (2)); ++i)
                                    fputc('\t', out);
                                fputs("}", out);
                            } while (0);
                        } while (0);
                    }
                    fputs(",\n", out);
                }
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("],\n", out);
        } while (0);
        do {
            output_direct_declarator(out, (node->decl.func.direct_declarator), indent + (1));
            fputs(",\n", out);
        } while (0);
    } else if (node->decl_type == DECLARATOR_INCOMPLETE_ARRAY) {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fprintf(out, "has_star"": %s,\n", (node->decl.incomplete_array.has_star) ? "true" : "false");
        } while (0);
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("type_qualifiers"": [", out);
            } while (0);
            for (List *str__l = ((node->decl.incomplete_array.type_qualifiers)); str__l != ((void *)0) && str__l->head != ((void *)0); str__l = ((void *)0))
                for (ListNode *str__n = str__l->head; str__n != ((void *)0); str__n = str__n->next)
                    for (string str = (string)str__n->data; str != ((void *)0); str = ((void *)0)) {
                        write_value(out, str);
                        fputs(", ", out);
                    }
            fputs("],\n", out);
        } while (0);
        do {
            output_direct_declarator(out, (node->decl.incomplete_array.direct_declarator), indent + (1));
            fputs(",\n", out);
        } while (0);
    }
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_declarator(FILE *out, Declarator *node, size_t indent) {
    do {
        if (node != ((void *)0) && (node->pointer == ((void *)0))) {
            output_direct_declarator(out, (node->direct_declarator), indent);
            return;
        }
    } while (0);
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("Declarator"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("Declarator"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        output_pointer(out, (node->pointer), indent + (1));
        fputs(",\n", out);
    } while (0);
    do {
        output_direct_declarator(out, (node->direct_declarator), indent + (1));
        fputs(",\n", out);
    } while (0);
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_initializer_item(FILE *out, InitializerItem *node, size_t indent) {
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("InitializerItem"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("InitializerItem"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        for (size_t i = 0; i < (indent + 1); ++i)
            fputc('\t', out);
        fputs("designation: [\n", out);
    } while (0);
    for (List *designator__l = (node->designation); designator__l != ((void *)0) && designator__l->head != ((void *)0); designator__l = ((void *)0))
        for (ListNode *designator__n = designator__l->head; designator__n != ((void *)0); designator__n = designator__n->next)
            for (Designator *designator = (Designator *)designator__n->data; designator != ((void *)0); designator = ((void *)0)) {
                if (open_ast_node(out, "Designator", (designator) == ((void *)0) ? ((void *)0) : (designator)->token, (designator) == ((void *)0), indent + (2))) {
                    if (designator->is_constant_expr)
                        do {
                            output_conditional_expression(out, (designator->designator.constant_expr), indent + (3));
                            fputs(",\n", out);
                        } while (0);
                    else
                        do {
                            do {
                                for (size_t i = 0; i < (indent + (3)); ++i)
                                    fputc('\t', out);
                                fputs("identifier"": ", out);
                            } while (0);
                            output_one_token(out, (designator->designator.identifier));
                            fputs(",\n", out);
                        } while (0);
                    do {
                        parent_token = node->token;
                        do {
                            for (size_t i = 0; i < (indent + (2)); ++i)
                                fputc('\t', out);
                            fputs("}", out);
                        } while (0);
                    } while (0);
                }
                fputs(",\n", out);
            }
    do {
        for (size_t i = 0; i < (indent + 1); ++i)
            fputc('\t', out);
        fputs("],\n", out);
    } while (0);
    do {
        output_initializer(out, (node->initializer), indent + (1));
        fputs(",\n", out);
    } while (0);
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_initializer(FILE *out, Initializer *node, size_t indent) {
    do {
        if (node != ((void *)0) && (node->is_assignment_expr)) {
            output_assignment_expression(out, (node->init.assignment_expr), indent);
            return;
        }
    } while (0);
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("Initializer"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("Initializer"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("inits"": [\n", out);
        } while (0);
        for (List *item__l = ((node->init.inits)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
            for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                for (InitializerItem *item = (InitializerItem *)item__n->data; item != ((void *)0); item = ((void *)0))
                    do {
                        output_initializer_item(out, (item), indent + ((1) + 1));
                        fputs(",\n", out);
                    } while (0);
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("],\n", out);
        } while (0);
    } while (0);
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_decl_spec(FILE *out, DeclSpec *node, size_t indent) {
    do {
        if (node != ((void *)0) && (node->specifier_type == SPEC_TYPE_SPEC)) {
            output_type_spec(out, (node->specifier.type), indent);
            return;
        }
    } while (0);
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("DeclSpec"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("DeclSpec"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        for (size_t i = 0; i < (indent + 1); ++i)
            fputc('\t', out);
        fputs("specifier_type: ", out);
    } while (0);
    switch (node->specifier_type) {
    case SPEC_KEYWORD:
        fputs("SPEC_KEYWORD,\n", out);
        break;
    case SPEC_ALIGNMENT:
        fputs("SPEC_ALIGNMENT,\n", out);
        break;
    case SPEC_TYPE_SPEC:
        fputs("SPEC_TYPE_SPEC,\n", out);
        break;
    default:
        fputs("unknown,\n", out);
        break;
    }
    if (node->specifier_type == SPEC_KEYWORD) {
        do {
            do {
                for (size_t i = 0; i < (indent + (1)); ++i)
                    fputc('\t', out);
                fputs("keyword"": ", out);
            } while (0);
            write_value(out, (node->specifier.keyword));
            fputs(",\n", out);
        } while (0);
    } else if (node->specifier_type == SPEC_ALIGNMENT) {
        if (node->specifier.alignment.is_type_name)
            do {
                output_type_name(out, (node->specifier.alignment.spec.type_name), indent + (1));
                fputs(",\n", out);
            } while (0);
        else
            do {
                output_conditional_expression(out, (node->specifier.alignment.spec.constant_expression), indent + (1));
                fputs(",\n", out);
            } while (0);
    }
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_static_assert_decl(FILE *out, StaticAssertDecl *node, size_t indent) {
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("StaticAssertDecl"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("StaticAssertDecl"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        output_conditional_expression(out, (node->expr), indent + (1));
        fputs(",\n", out);
    } while (0);
    do {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("message"": ", out);
        } while (0);
        output_one_token(out, (node->message));
        fputs(",\n", out);
    } while (0);
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_var_decl(FILE *out, VarDecl *node, size_t indent) {
    do {
        if (node != ((void *)0) && (node->is_static_assert_decl)) {
            output_static_assert_decl(out, (node->decl.static_assert_decl), indent);
            return;
        }
    } while (0);
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("VarDecl"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("VarDecl"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("decl_specs"": [\n", out);
        } while (0);
        for (List *item__l = ((node->decl.general_decl.decl_specs)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
            for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                for (DeclSpec *item = (DeclSpec *)item__n->data; item != ((void *)0); item = ((void *)0))
                    do {
                        output_decl_spec(out, (item), indent + ((1) + 1));
                        fputs(",\n", out);
                    } while (0);
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("],\n", out);
        } while (0);
    } while (0);
    do {
        for (size_t i = 0; i < (indent + 1); ++i)
            fputc('\t', out);
        fputs("init_decls: [\n", out);
    } while (0);
    for (List *init_decl__l = (node->decl.general_decl.init_decls); init_decl__l != ((void *)0) && init_decl__l->head != ((void *)0); init_decl__l = ((void *)0))
        for (ListNode *init_decl__n = init_decl__l->head; init_decl__n != ((void *)0); init_decl__n = init_decl__n->next)
            for (InitDecl *init_decl = (InitDecl *)init_decl__n->data; init_decl != ((void *)0); init_decl = ((void *)0)) {
                if (open_ast_node(out, "InitDecl", (init_decl) == ((void *)0) ? ((void *)0) : (init_decl)->token, (init_decl) == ((void *)0), indent + (2))) {
                    do {
                        output_declarator(out, (init_decl->declarator), indent + (3));
                        fputs(",\n", out);
                    } while (0);
                    do {
                        output_initializer(out, (init_decl->initializer), indent + (3));
                        fputs(",\n", out);
                    } while (0);
                    do {
                        parent_token = node->token;
                        do {
                            for (size_t i = 0; i < (indent + (2)); ++i)
                                fputc('\t', out);
                            fputs("}", out);
                        } while (0);
                    } while (0);
                }
                fputs(",\n", out);
            }
    do {
        for (size_t i = 0; i < (indent + 1); ++i)
            fputc('\t', out);
        fputs("],\n", out);
    } while (0);
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
static void output_tu(FILE *out, TU *node, size_t indent) {
    if (node == ((void *)0)) {
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("TU"": null", out);
        } while (0);
        return;
    }
    do {
        for (size_t i = 0; i < (indent); ++i)
            fputc('\t', out);
        fputs("TU"": {\n", out);
    } while (0);
    Token *saved_token = parent_token;
    if (node->token != parent_token) {
        do {
            for (size_t i = 0; i < (indent + 1); ++i)
                fputc('\t', out);
            fputs("token: ", out);
        } while (0);
        output_one_token(out, node->token);
        fputs(",\n", out);
    }
    parent_token = node->token;
    do {
        do {
            for (size_t i = 0; i < (indent + (1)); ++i)
                fputc('\t', out);
            fputs("filename"": ", out);
        } while (0);
        write_value(out, (node->filename));
        fputs(",\n", out);
    } while (0);
    do {
        for (size_t i = 0; i < (indent + 1); ++i)
            fputc('\t', out);
        fputs("extern_decls: [\n", out);
    } while (0);
    for (List *ext__l = (node->extern_decls); ext__l != ((void *)0) && ext__l->head != ((void *)0); ext__l = ((void *)0))
        for (ListNode *ext__n = ext__l->head; ext__n != ((void *)0); ext__n = ext__n->next)
            for (ExternDecl *ext = (ExternDecl *)ext__n->data; ext != ((void *)0); ext = ((void *)0)) {
                if (ext == ((void *)0)) {
                    do {
                        for (size_t i = 0; i < (indent + 2); ++i)
                            fputc('\t', out);
                        fputs("ExternDecl: null", out);
                    } while (0);
                } else if (!ext->is_func_decl) {
                    output_var_decl(out, ext->decl.var_decl, indent + 2);
                } else {
                    FuncDecl *func = ext->decl.func_decl;
                    if (open_ast_node(out, "FuncDecl", (func) == ((void *)0) ? ((void *)0) : (func)->token, (func) == ((void *)0), indent + (2))) {
                        do {
                            do {
                                for (size_t i = 0; i < (indent + (3)); ++i)
                                    fputc('\t', out);
                                fputs("decl_specs"": [\n", out);
                            } while (0);
                            for (List *item__l = ((func->decl_specs)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                                    for (DeclSpec *item = (DeclSpec *)item__n->data; item != ((void *)0); item = ((void *)0))
                                        do {
                                            output_decl_spec(out, (item), indent + ((3) + 1));
                                            fputs(",\n", out);
                                        } while (0);
                            do {
                                for (size_t i = 0; i < (indent + (3)); ++i)
                                    fputc('\t', out);
                                fputs("],\n", out);
                            } while (0);
                        } while (0);
                        do {
                            output_declarator(out, (func->declarator), indent + (3));
                            fputs(",\n", out);
                        } while (0);
                        do {
                            do {
                                for (size_t i = 0; i < (indent + (3)); ++i)
                                    fputc('\t', out);
                                fputs("body"": [\n", out);
                            } while (0);
                            for (List *item__l = ((func->body)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                                    for (DeclStmt *item = (DeclStmt *)item__n->data; item != ((void *)0); item = ((void *)0))
                                        do {
                                            output_decl_stmt(out, (item), indent + ((3) + 1));
                                            fputs(",\n", out);
                                        } while (0);
                            do {
                                for (size_t i = 0; i < (indent + (3)); ++i)
                                    fputc('\t', out);
                                fputs("],\n", out);
                            } while (0);
                        } while (0);
                        do {
                            parent_token = node->token;
                            do {
                                for (size_t i = 0; i < (indent + (2)); ++i)
                                    fputc('\t', out);
                                fputs("}", out);
                            } while (0);
                        } while (0);
                    }
                }
                fputs(",\n", out);
            }
    do {
        for (size_t i = 0; i < (indent + 1); ++i)
            fputc('\t', out);
        fputs("],\n", out);
    } while (0);
    do {
        parent_token = saved_token;
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputc('\t', out);
            fputs("}", out);
        } while (0);
    } while (0);
}
void output_ast(string filename, TU *tu) {
    FILE *out = open_file(filename);
    if (out == ((void *)0))
        return;
    output_tu(out, tu, 0);
    fputc('\n', out);
    fclose(out);
}
static void print_assignment_expression(FILE *out, AssignmentExpression *node);
static void print_conditional_expression(FILE *out, ConditionalExpression *node);
static void print_cast_expression(FILE *out, CastExpression *node);
static void print_unary_expression(FILE *out, UnaryExpression *node);
static void print_type_name(FILE *out, TypeName *node);
static void print_type_spec(FILE *out, TypeSpec *node, size_t indent);
static void print_initializer_item(FILE *out, InitializerItem *node);
static void print_initializer(FILE *out, Initializer *node);
static void print_declarator(FILE *out, Declarator *node);
static void print_decl_spec(FILE *out, DeclSpec *node, size_t indent);
static void print_static_assert_decl(FILE *out, StaticAssertDecl *node);
static void print_var_decl(FILE *out, VarDecl *node, size_t indent);
static void print_statement(FILE *out, Statement *node, size_t indent);
static void print_primary_expression(FILE *out, PrimaryExpression *node) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""PrimaryExpression"": NULL\n", out);
            return;
        }
    } while (0);
    switch (node->primary_type) {
    case PRIMARY_IDENTIFIER:
        fputs(node->primary.identifier->value, out);
        break;
    case PRIMARY_INTEGER_CONSTANT:
        fputs(node->primary.integer_constant->value, out);
        break;
    case PRIMARY_CHARACTER_CONSTANT:
        fputs(node->primary.character_constant->value, out);
        break;
    case PRIMARY_FLOATING_CONSTANT:
        fputs(node->primary.floating_constant->value, out);
        break;
    case PRIMARY_STRING_LITERAL:
        fputs(node->primary.string_literal->value, out);
        break;
    case PRIMARY_EXPRESSION:
        fputc('(', out);
        do {
            for (List *item__l = ((node->primary.expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                    for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0)) {
                        if (item__n != item__l->head)
                            fputs(", ", out);
                        print_assignment_expression(out, item);
                    }
        } while (0);
        fputc(')', out);
        break;
    case PRIMARY_GENERIC_SELECTION:
        fputs("_Generic(", out);
        print_assignment_expression(out, node->primary.generic_selection.expr);
        fputs(", ", out);
        for (List *assoc__l = (node->primary.generic_selection.generic_assoc_list); assoc__l != ((void *)0) && assoc__l->head != ((void *)0); assoc__l = ((void *)0))
            for (ListNode *assoc__n = assoc__l->head; assoc__n != ((void *)0); assoc__n = assoc__n->next)
                for (GenericAssociation *assoc = (GenericAssociation *)assoc__n->data; assoc != ((void *)0); assoc = ((void *)0)) {
                    if (assoc__n != assoc__l->head)
                        fputs(", ", out);
                    if (assoc->type_name == ((void *)0))
                        fputs("default", out);
                    else
                        print_type_name(out, assoc->type_name);
                    fputs(": ", out);
                    print_assignment_expression(out, assoc->assignment_expr);
                }
        fputc(')', out);
        break;
    default:
        fputs("// error PrimaryExpression: unknown type\n", out);
        break;
    }
}
static void print_postfix_expression(FILE *out, PostfixExpression *node) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""PostfixExpression"": NULL\n", out);
            return;
        }
    } while (0);
    switch (node->expr_type) {
    case POSTFIX_PRIMARY:
        print_primary_expression(out, node->expr.primary_expr);
        break;
    case POSTFIX_COMPOUND_LITERAL:
        fputc('(', out);
        print_type_name(out, node->expr.compound_literal.type_name);
        fputs("){", out);
        do {
            for (List *item__l = ((node->expr.compound_literal.initializer_list)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                    for (InitializerItem *item = (InitializerItem *)item__n->data; item != ((void *)0); item = ((void *)0)) {
                        if (item__n != item__l->head)
                            fputs(", ", out);
                        print_initializer_item(out, item);
                    }
        } while (0);
        fputc('}', out);
        break;
    case POSTFIX_ARRAY_ACCESS:
        print_postfix_expression(out, node->expr.array_access.postfix_expr);
        fputc('[', out);
        do {
            for (List *item__l = ((node->expr.array_access.index_expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                    for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0)) {
                        if (item__n != item__l->head)
                            fputs(", ", out);
                        print_assignment_expression(out, item);
                    }
        } while (0);
        fputc(']', out);
        break;
    case POSTFIX_FUNC_CALL:
        print_postfix_expression(out, node->expr.func_call.postfix_expr);
        fputc('(', out);
        do {
            for (List *item__l = ((node->expr.func_call.args)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                    for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0)) {
                        if (item__n != item__l->head)
                            fputs(", ", out);
                        print_assignment_expression(out, item);
                    }
        } while (0);
        fputc(')', out);
        break;
    case POSTFIX_OP:
        print_postfix_expression(out, node->expr.postfix_op.postfix_expr);
        switch (node->expr.postfix_op.op_type) {
        case POSTFIX_MEMBER_ACCESS:
            fputc('.', out);
            fputs(node->expr.postfix_op.identifier->value, out);
            break;
        case POSTFIX_MEMBER_ACCESS_PTR:
            fputs("->", out);
            fputs(node->expr.postfix_op.identifier->value, out);
            break;
        case POSTFIX_INCREMENT:
            fputs("++", out);
            break;
        case POSTFIX_DECREMENT:
            fputs("--", out);
            break;
        default:
            fputs("// error PostfixExpression: unknown op\n", out);
            break;
        }
        break;
    default:
        fputs("// error PostfixExpression: unknown type\n", out);
        break;
    }
}
static string unary_leading_op(UnaryExpression *node) {
    if (node == ((void *)0))
        return ((void *)0);
    if (node->expr_type == UNARY_PREFIX)
        return node->expr.prefix.op;
    if (node->expr_type == UNARY_UNARY_OP)
        return node->expr.unary_op.op;
    return ((void *)0);
}
static void print_unary_op(FILE *out, string op, string next_op) {
    fputs(op, out);
    if (strcmp(op, "sizeof") == 0 || (next_op != ((void *)0) && next_op[0] == op[0]))
        fputc(' ', out);
}
static void print_unary_expression(FILE *out, UnaryExpression *node) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""UnaryExpression"": NULL\n", out);
            return;
        }
    } while (0);
    switch (node->expr_type) {
    case UNARY_PREFIX:
        print_unary_op(out, node->expr.prefix.op, unary_leading_op(node->expr.prefix.unary_expr));
        print_unary_expression(out, node->expr.prefix.unary_expr);
        break;
    case UNARY_UNARY_OP:
        {
            CastExpression *cast = node->expr.unary_op.cast_expr;
            print_unary_op(out, node->expr.unary_op.op, (cast != ((void *)0) && !cast->is_cast) ? unary_leading_op(cast->expr.unary_expr) : ((void *)0));
            print_cast_expression(out, cast);
            break;
        }
    case UNARY_FUNCTION_LIKE:
        fputs(node->expr.function_like.is_sizeof ? "sizeof(" : "_Alignof(", out);
        print_type_name(out, node->expr.function_like.type_name);
        fputc(')', out);
        break;
    case UNARY_POSTFIX:
        print_postfix_expression(out, node->expr.postfix);
        break;
    default:
        fputs("// error UnaryExpression: unknown type\n", out);
        break;
    }
}
static void print_cast_expression(FILE *out, CastExpression *node) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""CastExpression"": NULL\n", out);
            return;
        }
    } while (0);
    if (node->is_cast) {
        fputc('(', out);
        print_type_name(out, node->expr.cast.type_name);
        fputc(')', out);
        print_cast_expression(out, node->expr.cast.cast_expr);
    } else {
        print_unary_expression(out, node->expr.unary_expr);
    }
}
static void print_binary_expression(FILE *out, BinaryExpression *node) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""BinaryExpression"": NULL\n", out);
            return;
        }
    } while (0);
    if (node->is_cast) {
        print_cast_expression(out, node->expr.cast);
    } else {
        print_binary_expression(out, node->expr.binary.left);
        fprintf(out, " %s ", node->expr.binary.op);
        print_binary_expression(out, node->expr.binary.right);
    }
}
static void print_conditional_expression(FILE *out, ConditionalExpression *node) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""ConditionalExpression"": NULL\n", out);
            return;
        }
    } while (0);
    print_binary_expression(out, node->binary_expr);
    if (node->false_expr != ((void *)0)) {
        fputs(" ? ", out);
        do {
            for (List *item__l = ((node->true_expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                    for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0)) {
                        if (item__n != item__l->head)
                            fputs(", ", out);
                        print_assignment_expression(out, item);
                    }
        } while (0);
        fputs(" : ", out);
        print_conditional_expression(out, node->false_expr);
    }
}
static void print_assignment_expression(FILE *out, AssignmentExpression *node) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""AssignmentExpression"": NULL\n", out);
            return;
        }
    } while (0);
    if (node->is_conditional) {
        print_conditional_expression(out, node->expr.cond_expr);
    } else {
        print_unary_expression(out, node->expr.binary.left);
        fprintf(out, " %s ", node->expr.binary.op);
        print_assignment_expression(out, node->expr.binary.right);
    }
}
static void print_specifier_qualifier(FILE *out, SpecifierQualifier *node, size_t indent) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""SpecifierQualifier"": NULL\n", out);
            return;
        }
    } while (0);
    if (node->is_type_spec)
        print_type_spec(out, node->spec.type_spec, indent);
    else
        fputs(node->spec.type_qualifier, out);
}
static void print_struct_decl(FILE *out, StructDecl *node, size_t indent) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""StructDecl"": NULL\n", out);
            return;
        }
    } while (0);
    if (node->is_static_assert_decl) {
        print_static_assert_decl(out, node->decl.static_assert_decl);
    } else {
        for (List *spec__l = (node->decl.general_struct_decl.spec_qual_list); spec__l != ((void *)0) && spec__l->head != ((void *)0); spec__l = ((void *)0))
            for (ListNode *spec__n = spec__l->head; spec__n != ((void *)0); spec__n = spec__n->next)
                for (SpecifierQualifier *spec = (SpecifierQualifier *)spec__n->data; spec != ((void *)0); spec = ((void *)0)) {
                    if (spec__n != spec__l->head)
                        fputs(" ", out);
                    print_specifier_qualifier(out, spec, indent);
                }
        if (!((node->decl.general_struct_decl.struct_declarators) == ((void *)0) || (node->decl.general_struct_decl.struct_declarators)->head == ((void *)0))) {
            fputc(' ', out);
            for (List *decl__l = (node->decl.general_struct_decl.struct_declarators); decl__l != ((void *)0) && decl__l->head != ((void *)0); decl__l = ((void *)0))
                for (ListNode *decl__n = decl__l->head; decl__n != ((void *)0); decl__n = decl__n->next)
                    for (StructDeclarator *decl = (StructDeclarator *)decl__n->data; decl != ((void *)0); decl = ((void *)0)) {
                        if (decl__n != decl__l->head)
                            fputs(", ", out);
                        if (decl->declarator != ((void *)0))
                            print_declarator(out, decl->declarator);
                        if (decl->constant_expr != ((void *)0)) {
                            fputs(decl->declarator != ((void *)0) ? " : " : ": ", out);
                            print_conditional_expression(out, decl->constant_expr);
                        }
                    }
        }
    }
    fputc(';', out);
}
static void print_type_spec(FILE *out, TypeSpec *node, size_t indent) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""TypeSpec"": NULL\n", out);
            return;
        }
    } while (0);
    switch (node->spec_type) {
    case TYPE_SPEC_KEYWORD:
        fputs(node->spec.keyword_spec, out);
        break;
    case TYPE_SPEC_ATOMIC:
        fputs("_Atomic(", out);
        print_type_name(out, node->spec.atomic_spec);
        fputc(')', out);
        break;
    case TYPE_SPEC_STRUCT_UNION:
        fputs(node->spec.struct_union_spec.is_struct ? "struct" : "union", out);
        if (node->spec.struct_union_spec.identifier != ((void *)0))
            fprintf(out, " %s", node->spec.struct_union_spec.identifier->value);
        if (node->spec.struct_union_spec.members != ((void *)0)) {
            fputs(" {\n", out);
            for (List *member__l = (node->spec.struct_union_spec.members); member__l != ((void *)0) && member__l->head != ((void *)0); member__l = ((void *)0))
                for (ListNode *member__n = member__l->head; member__n != ((void *)0); member__n = member__n->next)
                    for (StructDecl *member = (StructDecl *)member__n->data; member != ((void *)0); member = ((void *)0)) {
                        for (size_t i = 0; i < (indent + 1); ++i)
                            fputs("    ", out);
                        print_struct_decl(out, member, indent + 1);
                        fputc('\n', out);
                    }
            do {
                for (size_t i = 0; i < (indent); ++i)
                    fputs("    ", out);
                fputs("}", out);
            } while (0);
        }
        break;
    case TYPE_SPEC_ENUM:
        fputs("enum", out);
        if (node->spec.enum_spec.identifier != ((void *)0))
            fprintf(out, " %s", node->spec.enum_spec.identifier->value);
        if (node->spec.enum_spec.enumerators != ((void *)0)) {
            fputs(" {\n", out);
            for (List *enumerator__l = (node->spec.enum_spec.enumerators); enumerator__l != ((void *)0) && enumerator__l->head != ((void *)0); enumerator__l = ((void *)0))
                for (ListNode *enumerator__n = enumerator__l->head; enumerator__n != ((void *)0); enumerator__n = enumerator__n->next)
                    for (Enumerator *enumerator = (Enumerator *)enumerator__n->data; enumerator != ((void *)0); enumerator = ((void *)0)) {
                        for (size_t i = 0; i < (indent + 1); ++i)
                            fputs("    ", out);
                        fputs(enumerator->identifier->value, out);
                        if (enumerator->constant_expr != ((void *)0)) {
                            fputs(" = ", out);
                            print_conditional_expression(out, enumerator->constant_expr);
                        }
                        fputs(",\n", out);
                    }
            do {
                for (size_t i = 0; i < (indent); ++i)
                    fputs("    ", out);
                fputs("}", out);
            } while (0);
        }
        break;
    case TYPE_SPEC_TYPEDEF_NAME:
        fputs(node->spec.typedef_name->value, out);
        break;
    default:
        fputs("// error TypeSpec: unknown type\n", out);
        break;
    }
}
static void print_type_name(FILE *out, TypeName *node) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""TypeName"": NULL\n", out);
            return;
        }
    } while (0);
    for (List *spec__l = (node->spec_qual_list); spec__l != ((void *)0) && spec__l->head != ((void *)0); spec__l = ((void *)0))
        for (ListNode *spec__n = spec__l->head; spec__n != ((void *)0); spec__n = spec__n->next)
            for (SpecifierQualifier *spec = (SpecifierQualifier *)spec__n->data; spec != ((void *)0); spec = ((void *)0)) {
                if (spec__n != spec__l->head)
                    fputs(" ", out);
                print_specifier_qualifier(out, spec, 0);
            }
    Declarator *decl = node->abs_declarator;
    if (decl != ((void *)0) && (decl->pointer != ((void *)0) || decl->direct_declarator != ((void *)0))) {
        fputc(' ', out);
        print_declarator(out, decl);
    }
}
static void print_pointer(FILE *out, Pointer *node) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""Pointer"": NULL\n", out);
            return;
        }
    } while (0);
    fputc('*', out);
    for (List *qualifier__l = (node->type_qualifiers); qualifier__l != ((void *)0) && qualifier__l->head != ((void *)0); qualifier__l = ((void *)0))
        for (ListNode *qualifier__n = qualifier__l->head; qualifier__n != ((void *)0); qualifier__n = qualifier__n->next)
            for (string qualifier = (string)qualifier__n->data; qualifier != ((void *)0); qualifier = ((void *)0))
                fprintf(out, " %s", qualifier);
    if (!((node->type_qualifiers) == ((void *)0) || (node->type_qualifiers)->head == ((void *)0)))
        fputc(' ', out);
    if (node->pointer != ((void *)0))
        print_pointer(out, node->pointer);
}
static void print_array_qualifiers(FILE *out, List_string qualifiers, _Bool *need_space) {
    for (List *qualifier__l = (qualifiers); qualifier__l != ((void *)0) && qualifier__l->head != ((void *)0); qualifier__l = ((void *)0))
        for (ListNode *qualifier__n = qualifier__l->head; qualifier__n != ((void *)0); qualifier__n = qualifier__n->next)
            for (string qualifier = (string)qualifier__n->data; qualifier != ((void *)0); qualifier = ((void *)0)) {
                if (*need_space)
                    fputc(' ', out);
                fputs(qualifier, out);
                *need_space = 1;
            }
}
static void print_direct_declarator(FILE *out, DirectDeclarator *node) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""DirectDeclarator"": NULL\n", out);
            return;
        }
    } while (0);
    _Bool need_space = 0;
    switch (node->decl_type) {
    case DECLARATOR_ID:
        fputs(node->decl.identifier->value, out);
        break;
    case DECLARATOR_DECL:
        fputc('(', out);
        print_declarator(out, node->decl.declarator);
        fputc(')', out);
        break;
    case DECLARATOR_ARRAY:
        if (node->decl.array.direct_declarator != ((void *)0))
            print_direct_declarator(out, node->decl.array.direct_declarator);
        fputc('[', out);
        if (node->decl.array.is_static) {
            fputs("static", out);
            need_space = 1;
        }
        print_array_qualifiers(out, node->decl.array.type_qualifiers, &need_space);
        if (node->decl.array.assignment_expression != ((void *)0)) {
            if (need_space)
                fputc(' ', out);
            print_assignment_expression(out, node->decl.array.assignment_expression);
        }
        fputc(']', out);
        break;
    case DECLARATOR_FUNC:
        if (node->decl.func.direct_declarator != ((void *)0))
            print_direct_declarator(out, node->decl.func.direct_declarator);
        fputc('(', out);
        for (List *param__l = (node->decl.func.param_decls); param__l != ((void *)0) && param__l->head != ((void *)0); param__l = ((void *)0))
            for (ListNode *param__n = param__l->head; param__n != ((void *)0); param__n = param__n->next)
                for (ParamDecl *param = (ParamDecl *)param__n->data; param != ((void *)0); param = ((void *)0)) {
                    if (param__n != param__l->head)
                        fputs(", ", out);
                    for (List *spec__l = (param->decl_specs); spec__l != ((void *)0) && spec__l->head != ((void *)0); spec__l = ((void *)0))
                        for (ListNode *spec__n = spec__l->head; spec__n != ((void *)0); spec__n = spec__n->next)
                            for (DeclSpec *spec = (DeclSpec *)spec__n->data; spec != ((void *)0); spec = ((void *)0)) {
                                if (spec__n != spec__l->head)
                                    fputs(" ", out);
                                print_decl_spec(out, spec, 0);
                            }
                    if (param->decl != ((void *)0) && (param->decl->pointer != ((void *)0) || param->decl->direct_declarator != ((void *)0))) {
                        fputc(' ', out);
                        print_declarator(out, param->decl);
                    }
                }
        if (node->decl.func.is_variadic)
            fputs(((node->decl.func.param_decls) == ((void *)0) || (node->decl.func.param_decls)->head == ((void *)0)) ? "..." : ", ...", out);
        fputc(')', out);
        break;
    case DECLARATOR_INCOMPLETE_ARRAY:
        if (node->decl.incomplete_array.direct_declarator != ((void *)0))
            print_direct_declarator(out, node->decl.incomplete_array.direct_declarator);
        fputc('[', out);
        print_array_qualifiers(out, node->decl.incomplete_array.type_qualifiers, &need_space);
        if (node->decl.incomplete_array.has_star)
            fputs(need_space ? " *" : "*", out);
        fputc(']', out);
        break;
    default:
        fputs("// error DirectDeclarator: unknown type\n", out);
        break;
    }
}
static void print_declarator(FILE *out, Declarator *node) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""Declarator"": NULL\n", out);
            return;
        }
    } while (0);
    if (node->pointer != ((void *)0))
        print_pointer(out, node->pointer);
    if (node->direct_declarator != ((void *)0))
        print_direct_declarator(out, node->direct_declarator);
}
static void print_initializer_item(FILE *out, InitializerItem *node) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""InitializerItem"": NULL\n", out);
            return;
        }
    } while (0);
    if (!((node->designation) == ((void *)0) || (node->designation)->head == ((void *)0))) {
        for (List *designator__l = (node->designation); designator__l != ((void *)0) && designator__l->head != ((void *)0); designator__l = ((void *)0))
            for (ListNode *designator__n = designator__l->head; designator__n != ((void *)0); designator__n = designator__n->next)
                for (Designator *designator = (Designator *)designator__n->data; designator != ((void *)0); designator = ((void *)0)) {
                    if (designator->is_constant_expr) {
                        fputc('[', out);
                        print_conditional_expression(out, designator->designator.constant_expr);
                        fputc(']', out);
                    } else {
                        fprintf(out, ".%s", designator->designator.identifier->value);
                    }
                }
        fputs(" = ", out);
    }
    print_initializer(out, node->initializer);
}
static void print_initializer(FILE *out, Initializer *node) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""Initializer"": NULL\n", out);
            return;
        }
    } while (0);
    if (node->is_assignment_expr) {
        print_assignment_expression(out, node->init.assignment_expr);
    } else if (((node->init.inits) == ((void *)0) || (node->init.inits)->head == ((void *)0))) {
        fputs("{}", out);
    } else {
        fputs("{ ", out);
        do {
            for (List *item__l = ((node->init.inits)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                    for (InitializerItem *item = (InitializerItem *)item__n->data; item != ((void *)0); item = ((void *)0)) {
                        if (item__n != item__l->head)
                            fputs(", ", out);
                        print_initializer_item(out, item);
                    }
        } while (0);
        fputs(" }", out);
    }
}
static void print_decl_spec(FILE *out, DeclSpec *node, size_t indent) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""DeclSpec"": NULL\n", out);
            return;
        }
    } while (0);
    switch (node->specifier_type) {
    case SPEC_KEYWORD:
        fputs(node->specifier.keyword, out);
        break;
    case SPEC_ALIGNMENT:
        fputs("_Alignas(", out);
        if (node->specifier.alignment.is_type_name)
            print_type_name(out, node->specifier.alignment.spec.type_name);
        else
            print_conditional_expression(out, node->specifier.alignment.spec.constant_expression);
        fputc(')', out);
        break;
    case SPEC_TYPE_SPEC:
        print_type_spec(out, node->specifier.type, indent);
        break;
    default:
        fputs("// error DeclSpec: unknown type\n", out);
        break;
    }
}
static void print_static_assert_decl(FILE *out, StaticAssertDecl *node) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""StaticAssertDecl"": NULL\n", out);
            return;
        }
    } while (0);
    fputs("_Static_assert(", out);
    print_conditional_expression(out, node->expr);
    if (node->message != ((void *)0))
        fprintf(out, ", %s", node->message->value);
    fputc(')', out);
}
static void print_var_decl(FILE *out, VarDecl *node, size_t indent) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""VarDecl"": NULL\n", out);
            return;
        }
    } while (0);
    if (node->is_static_assert_decl) {
        print_static_assert_decl(out, node->decl.static_assert_decl);
    } else {
        for (List *spec__l = (node->decl.general_decl.decl_specs); spec__l != ((void *)0) && spec__l->head != ((void *)0); spec__l = ((void *)0))
            for (ListNode *spec__n = spec__l->head; spec__n != ((void *)0); spec__n = spec__n->next)
                for (DeclSpec *spec = (DeclSpec *)spec__n->data; spec != ((void *)0); spec = ((void *)0)) {
                    if (spec__n != spec__l->head)
                        fputs(" ", out);
                    print_decl_spec(out, spec, indent);
                }
        if (!((node->decl.general_decl.init_decls) == ((void *)0) || (node->decl.general_decl.init_decls)->head == ((void *)0))) {
            fputc(' ', out);
            for (List *init_decl__l = (node->decl.general_decl.init_decls); init_decl__l != ((void *)0) && init_decl__l->head != ((void *)0); init_decl__l = ((void *)0))
                for (ListNode *init_decl__n = init_decl__l->head; init_decl__n != ((void *)0); init_decl__n = init_decl__n->next)
                    for (InitDecl *init_decl = (InitDecl *)init_decl__n->data; init_decl != ((void *)0); init_decl = ((void *)0)) {
                        if (init_decl__n != init_decl__l->head)
                            fputs(", ", out);
                        print_declarator(out, init_decl->declarator);
                        if (init_decl->initializer != ((void *)0)) {
                            fputs(" = ", out);
                            print_initializer(out, init_decl->initializer);
                        }
                    }
        }
    }
    fputc(';', out);
}
static void print_statement_line(FILE *out, Statement *node, size_t indent) {
    if (node != ((void *)0) && node->stmt_type == STMT_LABELED && indent > 0)
        for (size_t i = 0; i < (indent - 1); ++i)
            fputs("    ", out);
    else
        for (size_t i = 0; i < (indent); ++i)
            fputs("    ", out);
    print_statement(out, node, indent);
}
static void print_decl_stmt(FILE *out, DeclStmt *node, size_t indent) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""DeclStmt"": NULL\n", out);
            return;
        }
    } while (0);
    if (node->is_var_decl) {
        for (size_t i = 0; i < (indent); ++i)
            fputs("    ", out);
        print_var_decl(out, node->item.var_decl, indent);
    } else {
        print_statement_line(out, node->item.statement, indent);
    }
}
static void print_body(FILE *out, Statement *node, size_t indent) {
    if (node != ((void *)0) && node->stmt_type == STMT_COMPOUND) {
        fputc(' ', out);
        print_statement(out, node, indent);
    } else {
        fputc('\n', out);
        print_statement_line(out, node, indent + 1);
    }
}
static void print_statement(FILE *out, Statement *node, size_t indent) {
    do {
        if (node == ((void *)0)) {
            fputs("// error ""Statement"": NULL\n", out);
            return;
        }
    } while (0);
    switch (node->stmt_type) {
    case STMT_LABELED:
        {
            LabeledStatement *label = node->stmt.label;
            if (label->label_type == LABEL_IDENTIFIER) {
                fprintf(out, "%s:", label->label.identifier->value);
            } else if (label->label_type == LABEL_CASE) {
                fputs("case ", out);
                print_conditional_expression(out, label->label.case_stmt);
                fputc(':', out);
            } else {
                fputs("default:", out);
            }
            fputc('\n', out);
            print_statement_line(out, label->stmt, indent);
            break;
        }
    case STMT_COMPOUND:
        fputs("{\n", out);
        for (List *item__l = (node->stmt.compound); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
            for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                for (DeclStmt *item = (DeclStmt *)item__n->data; item != ((void *)0); item = ((void *)0)) {
                    print_decl_stmt(out, item, indent + 1);
                    fputc('\n', out);
                }
        do {
            for (size_t i = 0; i < (indent); ++i)
                fputs("    ", out);
            fputs("}", out);
        } while (0);
        break;
    case STMT_EXPRESSION:
        do {
            for (List *item__l = ((node->stmt.expression)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                    for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0)) {
                        if (item__n != item__l->head)
                            fputs(", ", out);
                        print_assignment_expression(out, item);
                    }
        } while (0);
        fputc(';', out);
        break;
    case STMT_SELECTION:
        {
            SelectionStatement *sel = node->stmt.selection;
            if (sel->is_switch) {
                fputs("switch (", out);
                do {
                    for (List *item__l = ((sel->selection.switch_stmt.cond_expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                        for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                            for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0)) {
                                if (item__n != item__l->head)
                                    fputs(", ", out);
                                print_assignment_expression(out, item);
                            }
                } while (0);
                fputc(')', out);
                print_body(out, sel->selection.switch_stmt.stmt, indent);
                break;
            }
            Statement *then_stmt = sel->selection.if_stmt.then_stmt;
            Statement *else_stmt = sel->selection.if_stmt.else_stmt;
            fputs("if (", out);
            do {
                for (List *item__l = ((sel->selection.if_stmt.cond_expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                    for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                        for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0)) {
                            if (item__n != item__l->head)
                                fputs(", ", out);
                            print_assignment_expression(out, item);
                        }
            } while (0);
            fputc(')', out);
            print_body(out, then_stmt, indent);
            if (else_stmt != ((void *)0)) {
                if (then_stmt != ((void *)0) && then_stmt->stmt_type == STMT_COMPOUND) {
                    fputs(" else", out);
                } else {
                    fputc('\n', out);
                    do {
                        for (size_t i = 0; i < (indent); ++i)
                            fputs("    ", out);
                        fputs("else", out);
                    } while (0);
                }
                if (else_stmt->stmt_type == STMT_SELECTION && !else_stmt->stmt.selection->is_switch) {
                    fputc(' ', out);
                    print_statement(out, else_stmt, indent);
                } else {
                    print_body(out, else_stmt, indent);
                }
            }
            break;
        }
    case STMT_ITERATION:
        {
            IterationStatement *loop = node->stmt.iteration;
            if (loop->loop_type == LOOP_WHILE) {
                fputs("while (", out);
                do {
                    for (List *item__l = ((loop->loop.while_stmt.expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                        for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                            for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0)) {
                                if (item__n != item__l->head)
                                    fputs(", ", out);
                                print_assignment_expression(out, item);
                            }
                } while (0);
                fputc(')', out);
                print_body(out, loop->loop.while_stmt.stmt, indent);
            } else if (loop->loop_type == LOOP_DO_WHILE) {
                Statement *body = loop->loop.while_stmt.stmt;
                fputs("do", out);
                print_body(out, body, indent);
                if (body != ((void *)0) && body->stmt_type == STMT_COMPOUND) {
                    fputc(' ', out);
                } else {
                    fputc('\n', out);
                    for (size_t i = 0; i < (indent); ++i)
                        fputs("    ", out);
                }
                fputs("while (", out);
                do {
                    for (List *item__l = ((loop->loop.while_stmt.expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                        for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                            for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0)) {
                                if (item__n != item__l->head)
                                    fputs(", ", out);
                                print_assignment_expression(out, item);
                            }
                } while (0);
                fputs(");", out);
            } else {
                fputs("for (", out);
                if (loop->loop.for_stmt.is_init_decl) {
                    print_var_decl(out, loop->loop.for_stmt.init.init_decl, indent);
                } else {
                    do {
                        for (List *item__l = ((loop->loop.for_stmt.init.init_expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                            for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                                for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0)) {
                                    if (item__n != item__l->head)
                                        fputs(", ", out);
                                    print_assignment_expression(out, item);
                                }
                    } while (0);
                    fputc(';', out);
                }
                if (!((loop->loop.for_stmt.cond_expr) == ((void *)0) || (loop->loop.for_stmt.cond_expr)->head == ((void *)0))) {
                    fputc(' ', out);
                    do {
                        for (List *item__l = ((loop->loop.for_stmt.cond_expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                            for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                                for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0)) {
                                    if (item__n != item__l->head)
                                        fputs(", ", out);
                                    print_assignment_expression(out, item);
                                }
                    } while (0);
                }
                fputc(';', out);
                if (!((loop->loop.for_stmt.loop_expr) == ((void *)0) || (loop->loop.for_stmt.loop_expr)->head == ((void *)0))) {
                    fputc(' ', out);
                    do {
                        for (List *item__l = ((loop->loop.for_stmt.loop_expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                            for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                                for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0)) {
                                    if (item__n != item__l->head)
                                        fputs(", ", out);
                                    print_assignment_expression(out, item);
                                }
                    } while (0);
                }
                fputc(')', out);
                print_body(out, loop->loop.for_stmt.stmt, indent);
            }
            break;
        }
    case STMT_JUMP:
        {
            JumpStatement *jump = node->stmt.jump;
            switch (jump->jump_type) {
            case JUMP_GOTO:
                fprintf(out, "goto %s;", jump->jump.identifier->value);
                break;
            case JUMP_CONTINUE:
                fputs("continue;", out);
                break;
            case JUMP_BREAK:
                fputs("break;", out);
                break;
            case JUMP_RETURN:
                fputs("return", out);
                if (!((jump->jump.expr) == ((void *)0) || (jump->jump.expr)->head == ((void *)0))) {
                    fputc(' ', out);
                    do {
                        for (List *item__l = ((jump->jump.expr)); item__l != ((void *)0) && item__l->head != ((void *)0); item__l = ((void *)0))
                            for (ListNode *item__n = item__l->head; item__n != ((void *)0); item__n = item__n->next)
                                for (AssignmentExpression *item = (AssignmentExpression *)item__n->data; item != ((void *)0); item = ((void *)0)) {
                                    if (item__n != item__l->head)
                                        fputs(", ", out);
                                    print_assignment_expression(out, item);
                                }
                    } while (0);
                }
                fputc(';', out);
                break;
            default:
                fputs("// error JumpStatement: unknown type\n", out);
                break;
            }
            break;
        }
    default:
        fputs("// error Statement: unknown type\n", out);
        break;
    }
}
void print_ast(string filename, TU *tu) {
    FILE *out = open_file(filename);
    if (out == ((void *)0))
        return;
    if (tu == ((void *)0))
        fputs("// error TU: NULL\n", out);
    for (List *decl__l = (tu == ((void *)0) ? ((void *)0) : tu->extern_decls); decl__l != ((void *)0) && decl__l->head != ((void *)0); decl__l = ((void *)0))
        for (ListNode *decl__n = decl__l->head; decl__n != ((void *)0); decl__n = decl__n->next)
            for (ExternDecl *decl = (ExternDecl *)decl__n->data; decl != ((void *)0); decl = ((void *)0)) {
                if (!decl->is_func_decl) {
                    print_var_decl(out, decl->decl.var_decl, 0);
                } else if (decl->decl.func_decl == ((void *)0)) {
                    fputs("// error FuncDecl: NULL\n", out);
                } else {
                    FuncDecl *func = decl->decl.func_decl;
                    for (List *spec__l = (func->decl_specs); spec__l != ((void *)0) && spec__l->head != ((void *)0); spec__l = ((void *)0))
                        for (ListNode *spec__n = spec__l->head; spec__n != ((void *)0); spec__n = spec__n->next)
                            for (DeclSpec *spec = (DeclSpec *)spec__n->data; spec != ((void *)0); spec = ((void *)0)) {
                                if (spec__n != spec__l->head)
                                    fputs(" ", out);
                                print_decl_spec(out, spec, 0);
                            }
                    fputc(' ', out);
                    print_declarator(out, func->declarator);
                    fputs(" {\n", out);
                    for (List *stmt__l = (func->body); stmt__l != ((void *)0) && stmt__l->head != ((void *)0); stmt__l = ((void *)0))
                        for (ListNode *stmt__n = stmt__l->head; stmt__n != ((void *)0); stmt__n = stmt__n->next)
                            for (DeclStmt *stmt = (DeclStmt *)stmt__n->data; stmt != ((void *)0); stmt = ((void *)0)) {
                                print_decl_stmt(out, stmt, 1);
                                fputc('\n', out);
                            }
                    fputc('}', out);
                }
                fputc('\n', out);
            }
    fclose(out);
}
