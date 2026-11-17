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
typedef struct AST_StaticAssertDecl AST_StaticAssertDecl;
typedef struct AST_Declarator AST_Declarator;
typedef struct AST_DirectDeclarator AST_DirectDeclarator;
typedef struct AST_TypeSpec AST_TypeSpec;
typedef struct AST_Pointer AST_Pointer;
typedef struct AST_Initializer AST_Initializer;
typedef struct AST_InitializerItem AST_InitializerItem;
typedef struct AST_Statement AST_Statement;
typedef struct AST_Enumerator AST_Enumerator;
typedef struct AST_StructDeclarator AST_StructDeclarator;
typedef struct AST_StructDecl AST_StructDecl;
typedef struct AST_SpecifierQualifier AST_SpecifierQualifier;
typedef struct AST_TypeName AST_TypeName;
typedef struct AST_ParamDecl AST_ParamDecl;
typedef struct AST_Designator AST_Designator;
typedef struct AST_DeclSpec AST_DeclSpec;
typedef struct AST_FuncDecl AST_FuncDecl;
typedef struct AST_InitDecl AST_InitDecl;
typedef struct AST_VarDecl AST_VarDecl;
typedef struct AST_ExternDecl AST_ExternDecl;
typedef struct AST_TU AST_TU;
typedef struct AST_Declarator AST_AbsDeclarator;
typedef struct AST_LabeledStatement AST_LabeledStatement;
typedef struct AST_SelectionStatement AST_SelectionStatement;
typedef struct AST_IterationStatement AST_IterationStatement;
typedef struct AST_JumpStatement AST_JumpStatement;
typedef struct AST_DeclStmt AST_DeclStmt;
typedef struct AST_AssignmentExpression AST_AssignmentExpression;
typedef struct AST_ConditionalExpression AST_ConditionalExpression;
typedef struct AST_BinaryExpression AST_BinaryExpression;
typedef struct AST_CastExpression AST_CastExpression;
typedef struct AST_UnaryExpression AST_UnaryExpression;
typedef struct AST_PostfixExpression AST_PostfixExpression;
typedef struct AST_PrimaryExpression AST_PrimaryExpression;
typedef struct AST_GenericAssociation AST_GenericAssociation;
struct AST_AssignmentExpression {
    Token *token;
    union {
        AST_ConditionalExpression *cond_expr;
        struct {
            AST_UnaryExpression *left;
            AST_AssignmentExpression *right;
            string op;
        } binary;
    } expr;
    _Bool is_conditional;
};
struct AST_ConditionalExpression {
    Token *token;
    AST_BinaryExpression *binary_expr;
    List_AST_AssignmentExpression *true_expr;
    AST_ConditionalExpression *false_expr;
};
struct AST_BinaryExpression {
    Token *token;
    union {
        struct {
            string op;
            AST_BinaryExpression *left;
            AST_BinaryExpression *right;
        } binary;
        AST_CastExpression *cast;
    } expr;
    _Bool is_cast;
};
struct AST_CastExpression {
    Token *token;
    union {
        struct {
            AST_TypeName *type_name;
            AST_CastExpression *cast_expr;
        } cast;
        AST_UnaryExpression *unary_expr;
    } expr;
    _Bool is_cast;
};
struct AST_UnaryExpression {
    Token *token;
    union {
        struct {
            string op;
            AST_UnaryExpression *unary_expr;
        } prefix;
        struct {
            string op;
            AST_CastExpression *cast_expr;
        } unary_op;
        struct {
            AST_TypeName *type_name;
            _Bool is_sizeof;
        } function_like;
        AST_PostfixExpression *postfix;
    } expr;
    enum {
        UNARY_PREFIX,
        UNARY_UNARY_OP,
        UNARY_FUNCTION_LIKE,
        UNARY_POSTFIX,
    } expr_type;
};
struct AST_PostfixExpression {
    Token *token;
    union {
        AST_PrimaryExpression *primary_expr;
        struct {
            AST_TypeName *type_name;
            List_AST_InitializerItem *initializer_list;
        } compound_literal;
        struct {
            AST_PostfixExpression *postfix_expr;
            List_AST_AssignmentExpression *index_expr;
        } array_access;
        struct {
            AST_PostfixExpression *postfix_expr;
            List_AST_AssignmentExpression *args;
        } func_call;
        struct {
            AST_PostfixExpression *postfix_expr;
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
struct AST_PrimaryExpression {
    Token *token;
    union {
        Token *identifier;
        Token *integer_constant;
        Token *character_constant;
        Token *floating_constant;
        Token *string_literal;
        List_AST_AssignmentExpression *expr;
        struct {
            AST_AssignmentExpression *expr;
            List_AST_GenericAssociation *generic_assoc_list;
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
struct AST_GenericAssociation {
    Token *token;
    AST_TypeName *type_name;
    AST_AssignmentExpression *assignment_expr;
};
struct AST_DeclStmt {
    Token *token;
    union {
        AST_VarDecl *var_decl;
        AST_Statement *statement;
    } item;
    _Bool is_var_decl;
};
struct AST_LabeledStatement {
    Token *token;
    union {
        Token *identifier;
        AST_ConditionalExpression *case_stmt;
        void *none;
    } label;
    enum {
        LABEL_IDENTIFIER,
        LABEL_CASE,
        LABEL_DEFAULT,
    } label_type;
    AST_Statement *stmt;
};
struct AST_SelectionStatement {
    Token *token;
    union {
        struct {
            List_AST_AssignmentExpression *cond_expr;
            AST_Statement *then_stmt;
            AST_Statement *else_stmt;
        } if_stmt;
        struct {
            List_AST_AssignmentExpression *cond_expr;
            AST_Statement *stmt;
        } switch_stmt;
    } selection;
    _Bool is_switch;
};
struct AST_IterationStatement {
    Token *token;
    union {
        struct {
            List_AST_AssignmentExpression *expr;
            AST_Statement *stmt;
        } while_stmt;
        struct {
            union {
                List_AST_AssignmentExpression *init_expr;
                AST_VarDecl *init_decl;
            } init;
            _Bool is_init_decl;
            List_AST_AssignmentExpression *cond_expr;
            List_AST_AssignmentExpression *loop_expr;
            AST_Statement *stmt;
        } for_stmt;
    } loop;
    enum {
        LOOP_WHILE,
        LOOP_DO_WHILE,
        LOOP_FOR,
    } loop_type;
};
struct AST_JumpStatement {
    Token *token;
    union {
        Token *identifier;
        List_AST_AssignmentExpression *expr;
        void *none;
    } jump;
    enum {
        JUMP_GOTO,
        JUMP_CONTINUE,
        JUMP_BREAK,
        JUMP_RETURN,
    } jump_type;
};
struct AST_Statement {
    Token *token;
    union {
        AST_LabeledStatement *label;
        List_AST_DeclStmt *compound;
        List_AST_AssignmentExpression *expression;
        AST_SelectionStatement *selection;
        AST_IterationStatement *iteration;
        AST_JumpStatement *jump;
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
struct AST_Enumerator {
    Token *token;
    Token *identifier;
    AST_ConditionalExpression *constant_expr;
};
struct AST_StructDeclarator {
    Token *token;
    AST_Declarator *declarator;
    AST_ConditionalExpression *constant_expr;
};
struct AST_StructDecl {
    Token *token;
    union {
        struct {
            List_AST_SpecifierQualifier *spec_qual_list;
            List_AST_StructDeclarator *struct_declarators;
        } general_struct_decl;
        AST_StaticAssertDecl *static_assert_decl;
    } decl;
    _Bool is_static_assert_decl;
};
struct AST_SpecifierQualifier {
    Token *token;
    union {
        AST_TypeSpec *type_spec;
        string type_qualifier;
    } spec;
    _Bool is_type_spec;
};
struct AST_TypeName {
    Token *token;
    List_AST_SpecifierQualifier *spec_qual_list;
    AST_AbsDeclarator *abs_declarator;
};
struct AST_ParamDecl {
    Token *token;
    List_AST_DeclSpec *decl_specs;
    AST_Declarator *decl;
    _Bool is_abs;
};
struct AST_Pointer {
    Token *token;
    List_string type_qualifiers;
    AST_Pointer *pointer;
};
struct AST_Designator {
    Token *token;
    union {
        AST_ConditionalExpression *constant_expr;
        Token *identifier;
    } designator;
    _Bool is_constant_expr;
};
struct AST_InitializerItem {
    Token *token;
    List_AST_Designator *designation;
    AST_Initializer *initializer;
};
struct AST_Initializer {
    Token *token;
    union {
        AST_AssignmentExpression *assignment_expr;
        List_AST_InitializerItem *inits;
    } init;
    _Bool is_assignment_expr;
};
struct AST_TypeSpec {
    Token *token;
    union {
        string keyword_spec;
        AST_TypeName *atomic_spec;
        struct {
            _Bool is_struct;
            Token *identifier;
            List_AST_StructDecl *members;
        } struct_union_spec;
        struct {
            Token *identifier;
            List_AST_Enumerator *enumerators;
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
struct AST_DirectDeclarator {
    Token *token;
    union {
        Token *identifier;
        AST_Declarator *declarator;
        struct {
            AST_DirectDeclarator *direct_declarator;
            AST_AssignmentExpression *assignment_expression;
            List_string type_qualifiers;
            _Bool is_static;
        } array;
        struct {
            AST_DirectDeclarator *direct_declarator;
            List_AST_ParamDecl *param_decls;
            _Bool is_variadic;
        } func;
        struct {
            AST_DirectDeclarator *direct_declarator;
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
    AST_Scope *func_proto_scope;
};
struct AST_Declarator {
    Token *token;
    AST_Pointer *pointer;
    AST_DirectDeclarator *direct_declarator;
};
struct AST_DeclSpec {
    Token *token;
    union {
        string keyword;
        struct {
            union {
                AST_TypeName *type_name;
                AST_ConditionalExpression *constant_expression;
            } spec;
            _Bool is_type_name;
        } alignment;
        AST_TypeSpec *type;
    } specifier;
    enum {
        SPEC_KEYWORD,
        SPEC_ALIGNMENT,
        SPEC_TYPE_SPEC,
    } specifier_type;
};
struct AST_FuncDecl {
    Token *token;
    List_AST_DeclSpec *decl_specs;
    AST_Declarator *declarator;
    List_AST_DeclStmt *body;
};
struct AST_InitDecl {
    Token *token;
    AST_Declarator *declarator;
    AST_Initializer *initializer;
};
struct AST_StaticAssertDecl {
    Token *token;
    AST_ConditionalExpression *expr;
    Token *message;
};
struct AST_VarDecl {
    Token *token;
    union {
        struct {
            List_AST_DeclSpec *decl_specs;
            List_AST_InitDecl *init_decls;
        } general_decl;
        AST_StaticAssertDecl *static_assert_decl;
    } decl;
    _Bool is_static_assert_decl;
};
struct AST_ExternDecl {
    Token *token;
    union {
        AST_FuncDecl *func_decl;
        AST_VarDecl *var_decl;
    } decl;
    _Bool is_func_decl;
};
struct AST_TU {
    Token *token;
    string filename;
    List_AST_ExternDecl *extern_decls;
};
struct AST_Symbol {
    string name;
    _Bool is_typedef;
};
struct AST_Scope {
    AST_Scope *parent;
    List_AST_Symbol *names;
};
typedef struct Parser {
    List_Token *tokens;
    ListNode *next;
    Token *current;
    size_t brace_depth;
    size_t paren_depth;
    AST_Scope *current_scope;
    int error_count;
    _Bool panic_mode;
} Parser;
Parser *create_parser(List_Token *tokens);
AST_TU *parse_parser(Parser *parser);
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
static void report_error(Parser *parser, Token *t, string msg) {
    if (parser->panic_mode)
        return;
    parser->panic_mode = 1;
    parser->error_count++;
    if (t == ((void *)0)) {
        fprintf(stderr, "[Parse Error] at unknown location: %s\n", msg);
        return;
    }
    fprintf(stderr, "[Parse Error] at %s:%zu:%zu: %s\n", t->filename, t->line, t->column, msg);
    char *note = ((void *)0);
    if (t->type == TOKEN_SYNTAX_ERROR_NUMBER)
        note = "invalid number literal";
    else if (t->type == TOKEN_SYNTAX_ERROR_CHAR)
        note = "invalid character literal";
    else if (t->type == TOKEN_SYNTAX_ERROR_STRING)
        note = "invalid string literal";
    if (note != ((void *)0))
        fprintf(stderr, "    lexer report: '%s' is an %s\n", t->value, note);
}
static void report_warning(Parser *parser, Token *t, string msg) {
    if (parser->panic_mode)
        return;
    if (t == ((void *)0))
        fprintf(stderr, "[Parse Warning] at unknown location: %s\n", msg);
    else
        fprintf(stderr, "[Parse Warning] at %s:%zu:%zu: %s\n", t->filename, t->line, t->column, msg);
}
static AST_Scope *create_scope(AST_Scope *parent) {
    AST_Scope *scope = (AST_Scope *)alloc_memory(sizeof(AST_Scope), 1);
    scope->parent = parent;
    scope->names = list_create(_Generic((AST_Symbol *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    return scope;
}
static void push_new_scope(Parser *parser) {
    parser->current_scope = create_scope(parser->current_scope);
}
Parser *create_parser(List_Token *tokens) {
    Parser *parser = (Parser *)alloc_memory(sizeof(Parser), 1);
    parser->tokens = tokens;
    parser->next = tokens->head;
    parser->current = ((void *)0);
    parser->brace_depth = 0;
    parser->paren_depth = 0;
    parser->current_scope = ((void *)0);
    parser->error_count = 0;
    parser->panic_mode = 0;
    push_new_scope(parser);
    return parser;
}
static Token *get(Parser *parser) {
    Token *t = parser->next->data;
    parser->current = t;
    if (((t)->type == TOKEN_EOF))
        return t;
    parser->next = parser->next->next;
    if (t->type == TOKEN_SYMBOL) {
        if (t->value == SYMBOL_L_BRACE)
            parser->brace_depth++;
        else if (t->value == SYMBOL_R_BRACE && parser->brace_depth > 0)
            parser->brace_depth--;
        else if (t->value == SYMBOL_L_PARENTHESIS)
            parser->paren_depth++;
        else if (t->value == SYMBOL_R_PARENTHESIS && parser->paren_depth > 0)
            parser->paren_depth--;
    }
    return t;
}
static Token *peek2(Parser *parser) {
    ((void)(parser->next != ((void *)0)));
    Token *t = ((Token *)((parser)->next->data));
    if (((t)->type == TOKEN_EOF) || parser->next->next == ((void *)0))
        return t;
    return (Token *)parser->next->next->data;
}
static _Bool check(Parser *parser, TokenType type, string value) {
    Token *t = ((Token *)((parser)->next->data));
    ((void)(t != ((void *)0)));
    return t->type == type && (value == ((void *)0) || t->value == value);
}
static Token *expect(Parser *parser, TokenType type, string value, string msg) {
    if (!check(parser, type, value)) {
        report_error(parser, (((Token *)((parser)->next->data))), (msg));
        return ((void *)0);
    }
    return get(parser);
}
static _Bool match(Parser *parser, TokenType type, string value) {
    if (!check(parser, type, value))
        return 0;
    get(parser);
    return 1;
}
static void synchronize(Parser *parser, Token *start, size_t start_depth, _Bool is_top_level) {
    if (!parser->panic_mode)
        return;
    parser->panic_mode = 0;
    Token *last = parser->current;
    if (((Token *)((parser)->next->data)) != start && parser->brace_depth == start_depth && last->type == TOKEN_SYMBOL && (last->value == SYMBOL_SEMICOLON || last->value == SYMBOL_R_BRACE))
        return;
    size_t parenthesis_depth = 0;
    for (Token *t = ((Token *)((parser)->next->data)); !((t)->type == TOKEN_EOF); t = ((Token *)((parser)->next->data))) {
        _Bool at_start_level = parser->brace_depth == start_depth;
        if (t->type == TOKEN_SYMBOL && t->value == SYMBOL_R_BRACE && at_start_level) {
            if (is_top_level)
                get(parser);
            return;
        }
        get(parser);
        if (t->type != TOKEN_SYMBOL)
            continue;
        if (t->value == SYMBOL_R_BRACE && parser->brace_depth == start_depth) {
            match(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON);
            return;
        }
        if (t->value == SYMBOL_SEMICOLON && at_start_level && parenthesis_depth == 0)
            return;
        if (t->value == SYMBOL_L_PARENTHESIS)
            parenthesis_depth++;
        else if (t->value == SYMBOL_R_PARENTHESIS && parenthesis_depth > 0)
            parenthesis_depth--;
        else if (t->value == SYMBOL_L_BRACE || t->value == SYMBOL_R_BRACE)
            parenthesis_depth = 0;
    }
}
static void synchronize_paren(Parser *parser, size_t start_depth) {
    if (!parser->panic_mode)
        return;
    parser->panic_mode = 0;
    for (Token *t = ((Token *)((parser)->next->data)); !((t)->type == TOKEN_EOF) && parser->paren_depth > start_depth; t = ((Token *)((parser)->next->data))) {
        if (t->type == TOKEN_SYMBOL && (t->value == SYMBOL_L_BRACE || t->value == SYMBOL_R_BRACE))
            break;
        get(parser);
    }
}
static _Bool is_typedef_name(Parser *parser, string name) {
    for (AST_Scope *s = parser->current_scope; s != ((void *)0); s = s->parent) {
        for (List *sym__l = (s->names); sym__l != ((void *)0) && sym__l->head != ((void *)0); sym__l = ((void *)0))
            for (ListNode *sym__n = sym__l->head; sym__n != ((void *)0); sym__n = sym__n->next)
                for (AST_Symbol *sym = (AST_Symbol *)sym__n->data; sym != ((void *)0); sym = ((void *)0)) {
                    if (sym->name == name)
                        return sym->is_typedef;
                }
    }
    return 0;
}
static _Bool is_type_specifier_start(Parser *parser, _Bool seen_type) {
    Token *t = ((Token *)((parser)->next->data));
    if (t->type == TOKEN_KEYWORD) {
        if (t->value == KEYWORD_ATOMIC) {
            Token *p = peek2(parser);
            return p->type == TOKEN_SYMBOL && p->value == SYMBOL_L_PARENTHESIS;
        }
        return t->value == KEYWORD_VOID || t->value == KEYWORD_CHAR || t->value == KEYWORD_SHORT || t->value == KEYWORD_INT || t->value == KEYWORD_LONG || t->value == KEYWORD_FLOAT || t->value == KEYWORD_DOUBLE || t->value == KEYWORD_SIGNED || t->value == KEYWORD_UNSIGNED || t->value == KEYWORD_BOOL || t->value == KEYWORD_IMAGINARY || t->value == KEYWORD_COMPLEX || t->value == KEYWORD_STRUCT || t->value == KEYWORD_UNION || t->value == KEYWORD_ENUM;
    }
    if (t->type == TOKEN_IDENTIFIER)
        return !seen_type && is_typedef_name(parser, t->value);
    return 0;
}
static _Bool is_type_qualifier_start(Parser *parser, _Bool not_check_atomic) {
    Token *t = ((Token *)((parser)->next->data));
    if (t->type == TOKEN_KEYWORD && (t->value == KEYWORD_CONST || t->value == KEYWORD_RESTRICT || t->value == KEYWORD_VOLATILE))
        return 1;
    if (t->type == TOKEN_KEYWORD && t->value == KEYWORD_ATOMIC) {
        if (not_check_atomic)
            return 1;
        Token *p = peek2(parser);
        return p->type != TOKEN_SYMBOL || p->value != SYMBOL_L_PARENTHESIS;
    }
    return 0;
}
static _Bool is_type_start(Parser *parser, Token *t) {
    if (t->type == TOKEN_KEYWORD)
        return t->value == KEYWORD_ATOMIC || t->value == KEYWORD_VOID || t->value == KEYWORD_CHAR || t->value == KEYWORD_SHORT || t->value == KEYWORD_INT || t->value == KEYWORD_LONG || t->value == KEYWORD_FLOAT || t->value == KEYWORD_DOUBLE || t->value == KEYWORD_SIGNED || t->value == KEYWORD_UNSIGNED || t->value == KEYWORD_BOOL || t->value == KEYWORD_IMAGINARY || t->value == KEYWORD_COMPLEX || t->value == KEYWORD_STRUCT || t->value == KEYWORD_UNION || t->value == KEYWORD_ENUM || t->value == KEYWORD_CONST || t->value == KEYWORD_RESTRICT || t->value == KEYWORD_VOLATILE;
    if (t->type == TOKEN_IDENTIFIER)
        return is_typedef_name(parser, t->value);
    return 0;
}
static AST_DirectDeclarator *get_function_declarator(AST_Declarator *decl, AST_DirectDeclarator *outer) {
    AST_DirectDeclarator *inner = decl->direct_declarator;
    AST_DirectDeclarator *last = ((void *)0);
    while (inner != ((void *)0) && inner->decl_type != DECLARATOR_ID && inner->decl_type != DECLARATOR_DECL) {
        last = inner;
        switch (inner->decl_type) {
        case DECLARATOR_ARRAY:
            inner = inner->decl.array.direct_declarator;
            break;
        case DECLARATOR_FUNC:
            inner = inner->decl.func.direct_declarator;
            break;
        case DECLARATOR_INCOMPLETE_ARRAY:
            inner = inner->decl.incomplete_array.direct_declarator;
            break;
        case DECLARATOR_ID:
        case DECLARATOR_DECL:
        default:
            break;
        }
    }
    AST_DirectDeclarator *nearest = outer;
    if (last != ((void *)0))
        nearest = last->decl_type == DECLARATOR_FUNC ? last : ((void *)0);
    else if (decl->pointer != ((void *)0))
        nearest = ((void *)0);
    if (inner != ((void *)0) && inner->decl_type == DECLARATOR_DECL)
        return get_function_declarator(inner->decl.declarator, nearest);
    return nearest;
}
static void add_name(Parser *parser, Token *id, _Bool is_typedef) {
    for (List *symbol__l = (parser->current_scope->names); symbol__l != ((void *)0) && symbol__l->head != ((void *)0); symbol__l = ((void *)0))
        for (ListNode *symbol__n = symbol__l->head; symbol__n != ((void *)0); symbol__n = symbol__n->next)
            for (AST_Symbol *symbol = (AST_Symbol *)symbol__n->data; symbol != ((void *)0); symbol = ((void *)0))
                if (symbol->name == id->value)
                    return;
    AST_Symbol *symbol = (AST_Symbol *)alloc_memory(sizeof(AST_Symbol), 1);
    *symbol = (AST_Symbol){.name = id->value, .is_typedef = is_typedef};
    list_append((parser->current_scope->names), (void *)(symbol), _Generic((symbol), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
}
static Token *get_declarator_identifier(AST_DirectDeclarator *decl) {
    if (decl == ((void *)0))
        return ((void *)0);
    switch (decl->decl_type) {
    case DECLARATOR_ID:
        return decl->decl.identifier;
    case DECLARATOR_DECL:
        return get_declarator_identifier(decl->decl.declarator->direct_declarator);
    case DECLARATOR_ARRAY:
        return get_declarator_identifier(decl->decl.array.direct_declarator);
    case DECLARATOR_FUNC:
        return get_declarator_identifier(decl->decl.func.direct_declarator);
    case DECLARATOR_INCOMPLETE_ARRAY:
        return get_declarator_identifier(decl->decl.incomplete_array.direct_declarator);
    default:
        ((void)(0));
    }
}
static _Bool has_typedef(List_AST_DeclSpec *decl_specs) {
    for (List *spec__l = (decl_specs); spec__l != ((void *)0) && spec__l->head != ((void *)0); spec__l = ((void *)0))
        for (ListNode *spec__n = spec__l->head; spec__n != ((void *)0); spec__n = spec__n->next)
            for (AST_DeclSpec *spec = (AST_DeclSpec *)spec__n->data; spec != ((void *)0); spec = ((void *)0))
                if (spec->specifier_type == SPEC_KEYWORD && spec->specifier.keyword == KEYWORD_TYPEDEF)
                    return 1;
    return 0;
}
static _Bool is_declaration_start(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    if (is_type_start(parser, t))
        return 1;
    if (t->type != TOKEN_KEYWORD)
        return 0;
    return t->value == KEYWORD_TYPEDEF || t->value == KEYWORD_EXTERN || t->value == KEYWORD_STATIC || t->value == KEYWORD_THREAD_LOCAL || t->value == KEYWORD_AUTO || t->value == KEYWORD_REGISTER || t->value == KEYWORD_INLINE || t->value == KEYWORD_NORETURN || t->value == KEYWORD_ALIGNAS || t->value == KEYWORD_STATIC_ASSERT;
}
static int binary_operator_precedence(Token *t) {
    if (t->type != TOKEN_SYMBOL)
        return -1;
    else if (t->value == SYMBOL_LOGICAL_OR)
        return 1;
    else if (t->value == SYMBOL_LOGICAL_AND)
        return 2;
    else if (t->value == SYMBOL_BITWISE_OR)
        return 3;
    else if (t->value == SYMBOL_XOR)
        return 4;
    else if (t->value == SYMBOL_BITWISE_AND)
        return 5;
    else if (t->value == SYMBOL_EQ || t->value == SYMBOL_NE)
        return 6;
    else if (t->value == SYMBOL_LT || t->value == SYMBOL_GT || t->value == SYMBOL_LE || t->value == SYMBOL_GE)
        return 7;
    else if (t->value == SYMBOL_L_SHIFT || t->value == SYMBOL_R_SHIFT)
        return 8;
    else if (t->value == SYMBOL_ADD || t->value == SYMBOL_SUB)
        return 9;
    else if (t->value == SYMBOL_MUL || t->value == SYMBOL_DIV || t->value == SYMBOL_MOD)
        return 10;
    else
        return -1;
}
static AST_AssignmentExpression *parse_assignment_expression(Parser *parser);
static AST_TypeName *parse_type_name(Parser *parser);
static AST_GenericAssociation *parse_generic_association(Parser *parser) {
    AST_GenericAssociation *assoc = (AST_GenericAssociation *)alloc_memory(sizeof(AST_GenericAssociation), 1);
    assoc->token = ((Token *)((parser)->next->data));
    assoc->type_name = ((void *)0);
    if (!match(parser, TOKEN_KEYWORD, KEYWORD_DEFAULT))
        assoc->type_name = parse_type_name(parser);
    expect(parser, TOKEN_SYMBOL, SYMBOL_COLON, "Expected ':' in generic association");
    assoc->assignment_expr = parse_assignment_expression(parser);
    return assoc;
}
static List_AST_AssignmentExpression *parse_expression(Parser *parser);
static AST_PrimaryExpression *parse_primary_expression(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    AST_PrimaryExpression *primary_expr = (AST_PrimaryExpression *)alloc_memory(sizeof(AST_PrimaryExpression), 1);
    primary_expr->token = t;
    if (t->type == TOKEN_SYNTAX_ERROR_NUMBER)
        report_error(parser, (t), ("Invalid number literal"));
    else if (t->type == TOKEN_SYNTAX_ERROR_CHAR)
        report_error(parser, (t), ("Invalid character literal"));
    else if (t->type == TOKEN_SYNTAX_ERROR_STRING)
        report_error(parser, (t), ("Invalid string literal"));
    if (t->type == TOKEN_IDENTIFIER) {
        primary_expr->primary_type = PRIMARY_IDENTIFIER;
        primary_expr->primary.identifier = get(parser);
    } else if (t->type == TOKEN_INT || t->type == TOKEN_SYNTAX_ERROR_NUMBER) {
        primary_expr->primary_type = PRIMARY_INTEGER_CONSTANT;
        primary_expr->primary.integer_constant = get(parser);
    } else if (t->type == TOKEN_CHAR || t->type == TOKEN_SYNTAX_ERROR_CHAR) {
        primary_expr->primary_type = PRIMARY_CHARACTER_CONSTANT;
        primary_expr->primary.character_constant = get(parser);
    } else if (t->type == TOKEN_FLOAT) {
        primary_expr->primary_type = PRIMARY_FLOATING_CONSTANT;
        primary_expr->primary.floating_constant = get(parser);
    } else if (t->type == TOKEN_STRING || t->type == TOKEN_SYNTAX_ERROR_STRING) {
        primary_expr->primary_type = PRIMARY_STRING_LITERAL;
        primary_expr->primary.string_literal = get(parser);
    } else if (match(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS)) {
        primary_expr->primary_type = PRIMARY_EXPRESSION;
        primary_expr->primary.expr = parse_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after expression");
    } else if (match(parser, TOKEN_KEYWORD, KEYWORD_GENERIC)) {
        primary_expr->primary_type = PRIMARY_GENERIC_SELECTION;
        expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after '_Generic'");
        primary_expr->primary.generic_selection.expr = parse_assignment_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_COMMA, "Expected ',' after assignment expression in '_Generic'");
        primary_expr->primary.generic_selection.generic_assoc_list = list_create(_Generic((AST_GenericAssociation *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
        do {
            list_append((primary_expr->primary.generic_selection.generic_assoc_list), (void *)(parse_generic_association(parser)), _Generic((parse_generic_association(parser)), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
        } while (match(parser, TOKEN_SYMBOL, SYMBOL_COMMA));
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after generic association list in '_Generic'");
    } else {
        report_error(parser, (t), ("Expected primary expression"));
        return ((void *)0);
    }
    return primary_expr;
}
static AST_PostfixExpression *parse_postfix_suffix(Parser *parser, AST_PostfixExpression *outer) {
    Token *t = ((Token *)((parser)->next->data));
    while (t->type == TOKEN_SYMBOL && (t->value == SYMBOL_L_BRACKET || t->value == SYMBOL_L_PARENTHESIS || t->value == SYMBOL_DOT || t->value == SYMBOL_ARROW || t->value == SYMBOL_INCREMENT || t->value == SYMBOL_DECREMENT)) {
        AST_PostfixExpression *postfix_expr = (AST_PostfixExpression *)alloc_memory(sizeof(AST_PostfixExpression), 1);
        postfix_expr->token = t;
        if (match(parser, TOKEN_SYMBOL, SYMBOL_L_BRACKET)) {
            postfix_expr->expr_type = POSTFIX_ARRAY_ACCESS;
            postfix_expr->expr.array_access.postfix_expr = outer;
            postfix_expr->expr.array_access.index_expr = parse_expression(parser);
            expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACKET, "Expected ']' after array index expression");
        } else if (match(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS)) {
            postfix_expr->expr_type = POSTFIX_FUNC_CALL;
            postfix_expr->expr.func_call.postfix_expr = outer;
            postfix_expr->expr.func_call.args = list_create(_Generic((AST_AssignmentExpression *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
            if (!check(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS)) {
                do {
                    list_append((postfix_expr->expr.func_call.args), (void *)(parse_assignment_expression(parser)), _Generic((parse_assignment_expression(parser)), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                } while (match(parser, TOKEN_SYMBOL, SYMBOL_COMMA));
            }
            expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after function call arguments");
        } else if (match(parser, TOKEN_SYMBOL, SYMBOL_DOT) || match(parser, TOKEN_SYMBOL, SYMBOL_ARROW) || match(parser, TOKEN_SYMBOL, SYMBOL_INCREMENT) || match(parser, TOKEN_SYMBOL, SYMBOL_DECREMENT)) {
            postfix_expr->expr_type = POSTFIX_OP;
            postfix_expr->expr.postfix_op.postfix_expr = outer;
            if (t->value == SYMBOL_DOT)
                postfix_expr->expr.postfix_op.op_type = POSTFIX_MEMBER_ACCESS;
            else if (t->value == SYMBOL_ARROW)
                postfix_expr->expr.postfix_op.op_type = POSTFIX_MEMBER_ACCESS_PTR;
            else if (t->value == SYMBOL_INCREMENT)
                postfix_expr->expr.postfix_op.op_type = POSTFIX_INCREMENT;
            else if (t->value == SYMBOL_DECREMENT)
                postfix_expr->expr.postfix_op.op_type = POSTFIX_DECREMENT;
            postfix_expr->expr.postfix_op.identifier = ((void *)0);
            if (t->value == SYMBOL_DOT || t->value == SYMBOL_ARROW) {
                t = expect(parser, TOKEN_IDENTIFIER, ((void *)0), "Expected identifier after '.' or '->'");
                postfix_expr->expr.postfix_op.identifier = t;
            }
        } else
            break;
        outer = postfix_expr;
        t = ((Token *)((parser)->next->data));
    }
    return outer;
}
static AST_InitializerItem *parse_initializer_item(Parser *parser);
static AST_PostfixExpression *parse_compound_literal(Parser *parser, AST_TypeName *type_name) {
    Token *t = get(parser);
    AST_PostfixExpression *compound_literal = (AST_PostfixExpression *)alloc_memory(sizeof(AST_PostfixExpression), 1);
    *compound_literal = (AST_PostfixExpression){.token = t, .expr_type = POSTFIX_COMPOUND_LITERAL, .expr.compound_literal = { .type_name = type_name, .initializer_list = list_create(_Generic((AST_InitializerItem *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol)) }};
    do {
        if (check(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE))
            break;
        list_append((compound_literal->expr.compound_literal.initializer_list), (void *)(parse_initializer_item(parser)), _Generic((parse_initializer_item(parser)), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    } while (match(parser, TOKEN_SYMBOL, SYMBOL_COMMA));
    expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE, "Expected ',' or '}' in initializer list");
    if (((compound_literal->expr.compound_literal.initializer_list) == ((void *)0) || (compound_literal->expr.compound_literal.initializer_list)->head == ((void *)0)))
        report_warning(parser, (t), ("ISO C forbids empty initializer braces"));
    return parse_postfix_suffix(parser, compound_literal);
}
static AST_PostfixExpression *parse_postfix_expression(Parser *parser) {
    if (check(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS) && is_type_start(parser, peek2(parser))) {
        get(parser);
        AST_TypeName *type_name = parse_type_name(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after type name");
        if (check(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
            return parse_compound_literal(parser, type_name);
        } else {
            report_error(parser, (((Token *)((parser)->next->data))), ("Expected '{' after type name for compound literal"));
            return ((void *)0);
        }
    } else {
        AST_PostfixExpression *postfix_expr = (AST_PostfixExpression *)alloc_memory(sizeof(AST_PostfixExpression), 1);
        postfix_expr->token = ((Token *)((parser)->next->data));
        postfix_expr->expr_type = POSTFIX_PRIMARY;
        postfix_expr->expr.primary_expr = parse_primary_expression(parser);
        return parse_postfix_suffix(parser, postfix_expr);
    }
}
static AST_CastExpression *parse_cast_expression(Parser *parser);
static AST_UnaryExpression *parse_unary_expression(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    AST_UnaryExpression *unary_expr = (AST_UnaryExpression *)alloc_memory(sizeof(AST_UnaryExpression), 1);
    unary_expr->token = t;
    if (match(parser, TOKEN_SYMBOL, SYMBOL_INCREMENT) || match(parser, TOKEN_SYMBOL, SYMBOL_DECREMENT)) {
        unary_expr->expr_type = UNARY_PREFIX;
        unary_expr->expr.prefix.op = t->value;
        unary_expr->expr.prefix.unary_expr = parse_unary_expression(parser);
    } else if (t->type == TOKEN_SYMBOL && (t->value == SYMBOL_BITWISE_AND || t->value == SYMBOL_MUL || t->value == SYMBOL_ADD || t->value == SYMBOL_SUB || t->value == SYMBOL_BITWISE_NOT || t->value == SYMBOL_LOGICAL_NOT)) {
        unary_expr->expr_type = UNARY_UNARY_OP;
        unary_expr->expr.unary_op.op = get(parser)->value;
        unary_expr->expr.unary_op.cast_expr = parse_cast_expression(parser);
    } else if (match(parser, TOKEN_KEYWORD, KEYWORD_ALIGNOF)) {
        unary_expr->expr_type = UNARY_FUNCTION_LIKE;
        unary_expr->expr.function_like.is_sizeof = 0;
        expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after '_Alignof'");
        unary_expr->expr.function_like.type_name = parse_type_name(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after type name");
    } else if (match(parser, TOKEN_KEYWORD, KEYWORD_SIZEOF)) {
        if (check(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS) && is_type_start(parser, peek2(parser))) {
            unary_expr->expr_type = UNARY_FUNCTION_LIKE;
            unary_expr->expr.function_like.is_sizeof = 1;
            Token *tt = expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after 'sizeof'");
            unary_expr->expr.function_like.type_name = parse_type_name(parser);
            expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after type name");
            if (check(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
                AST_TypeName *type_name = unary_expr->expr.function_like.type_name;
                unary_expr->expr_type = UNARY_PREFIX;
                unary_expr->expr.prefix.op = KEYWORD_SIZEOF;
                unary_expr->expr.prefix.unary_expr = (AST_UnaryExpression *)alloc_memory(sizeof(AST_UnaryExpression), 1);
                *unary_expr->expr.prefix.unary_expr = (AST_UnaryExpression){.token = tt, .expr_type = UNARY_POSTFIX, .expr.postfix = parse_compound_literal(parser, type_name)};
            }
        } else {
            unary_expr->expr_type = UNARY_PREFIX;
            unary_expr->expr.prefix.op = KEYWORD_SIZEOF;
            unary_expr->expr.prefix.unary_expr = parse_unary_expression(parser);
        }
    } else {
        unary_expr->expr_type = UNARY_POSTFIX;
        unary_expr->expr.postfix = parse_postfix_expression(parser);
    }
    return unary_expr;
}
static AST_CastExpression *parse_cast_expression(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    AST_CastExpression *cast_expr = (AST_CastExpression *)alloc_memory(sizeof(AST_CastExpression), 1);
    cast_expr->token = t;
    if (check(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS) && is_type_start(parser, peek2(parser))) {
        t = get(parser);
        AST_TypeName *type_name = parse_type_name(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after type name");
        if (check(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
            AST_PostfixExpression *postfix_expr = parse_compound_literal(parser, type_name);
            AST_UnaryExpression *unary_expr = (AST_UnaryExpression *)alloc_memory(sizeof(AST_UnaryExpression), 1);
            *unary_expr = (AST_UnaryExpression){.token = t, .expr.postfix = postfix_expr, .expr_type = UNARY_POSTFIX};
            cast_expr->is_cast = 0;
            cast_expr->expr.unary_expr = unary_expr;
        } else {
            cast_expr->is_cast = 1;
            cast_expr->expr.cast.cast_expr = parse_cast_expression(parser);
            cast_expr->expr.cast.type_name = type_name;
        }
    } else {
        cast_expr->is_cast = 0;
        cast_expr->expr.unary_expr = parse_unary_expression(parser);
    }
    return cast_expr;
}
static AST_BinaryExpression *parse_binary_expression(Parser *parser, int min_precedence) {
    AST_BinaryExpression *left = (AST_BinaryExpression *)alloc_memory(sizeof(AST_BinaryExpression), 1);
    *left = (AST_BinaryExpression){.token = ((Token *)((parser)->next->data)), .is_cast = 1, .expr.cast = parse_cast_expression(parser)};
    while (1) {
        Token *op = ((Token *)((parser)->next->data));
        int precedence = binary_operator_precedence(op);
        if (precedence <= min_precedence)
            break;
        get(parser);
        AST_BinaryExpression *right = parse_binary_expression(parser, precedence);
        AST_BinaryExpression *node = (AST_BinaryExpression *)alloc_memory(sizeof(AST_BinaryExpression), 1);
        *node = (AST_BinaryExpression){.token = op, .is_cast = 0, .expr.binary = { .op = op->value, .left = left, .right = right }};
        left = node;
    }
    return left;
}
static AST_ConditionalExpression *parse_conditional_expression(Parser *parser) {
    AST_ConditionalExpression *cond_expr = (AST_ConditionalExpression *)alloc_memory(sizeof(AST_ConditionalExpression), 1);
    cond_expr->token = ((Token *)((parser)->next->data));
    cond_expr->true_expr = ((void *)0);
    cond_expr->false_expr = ((void *)0);
    cond_expr->binary_expr = parse_binary_expression(parser, 0);
    if (match(parser, TOKEN_SYMBOL, SYMBOL_QUESTION)) {
        cond_expr->true_expr = parse_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_COLON, "Expected ':' in conditional expression");
        cond_expr->false_expr = parse_conditional_expression(parser);
    }
    return cond_expr;
}
static AST_AssignmentExpression *parse_assignment_expression(Parser *parser) {
    AST_ConditionalExpression *cond_expr = parse_conditional_expression(parser);
    AST_AssignmentExpression *assign_expr = (AST_AssignmentExpression *)alloc_memory(sizeof(AST_AssignmentExpression), 1);
    Token *t = ((Token *)((parser)->next->data));
    if (t->type == TOKEN_SYMBOL && (t->value == SYMBOL_ASSIGN || t->value == SYMBOL_MUL_ASSIGN || t->value == SYMBOL_DIV_ASSIGN || t->value == SYMBOL_MOD_ASSIGN || t->value == SYMBOL_ADD_ASSIGN || t->value == SYMBOL_SUB_ASSIGN || t->value == SYMBOL_L_SHIFT_ASSIGN || t->value == SYMBOL_R_SHIFT_ASSIGN || t->value == SYMBOL_AND_ASSIGN || t->value == SYMBOL_XOR_ASSIGN || t->value == SYMBOL_OR_ASSIGN)) {
        t = get(parser);
        if (cond_expr->false_expr != ((void *)0) || cond_expr->true_expr != ((void *)0)) {
            report_error(parser, (cond_expr->token), ("Not an assignable expression"));
            return ((void *)0);
        }
        AST_BinaryExpression *binary_expr = cond_expr->binary_expr;
        if (!binary_expr->is_cast) {
            report_error(parser, (binary_expr->token), ("Not an assignable expression"));
            return ((void *)0);
        }
        AST_CastExpression *cast_expr = binary_expr->expr.cast;
        if (cast_expr->is_cast) {
            report_error(parser, (cast_expr->token), ("Not an assignable expression"));
            return ((void *)0);
        }
        AST_UnaryExpression *unary_expr = cast_expr->expr.unary_expr;
        *assign_expr = (AST_AssignmentExpression){.token = t, .is_conditional = 0, .expr.binary = { .left = unary_expr, .right = parse_assignment_expression(parser), .op = t->value }};
    } else
        *assign_expr = (AST_AssignmentExpression){.token = cond_expr->token, .is_conditional = 1, .expr.cond_expr = cond_expr};
    return assign_expr;
}
static List_AST_AssignmentExpression *parse_expression(Parser *parser) {
    List_AST_AssignmentExpression *expr_list = list_create(_Generic((AST_AssignmentExpression *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    do {
        list_append((expr_list), (void *)(parse_assignment_expression(parser)), _Generic((parse_assignment_expression(parser)), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    } while (match(parser, TOKEN_SYMBOL, SYMBOL_COMMA));
    return expr_list;
}
static AST_VarDecl *parse_declaration(Parser *parser, AST_FuncDecl **func_def);
static AST_Statement *parse_statement(Parser *parser);
static List_AST_DeclStmt *parse_compound_stmt(Parser *parser) {
    List_AST_DeclStmt *decl_stmts = list_create(_Generic((AST_DeclStmt *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    Token *t = ((Token *)((parser)->next->data));
    while (!((t)->type == TOKEN_EOF) && !check(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE)) {
        size_t start_depth = parser->brace_depth;
        AST_DeclStmt *decl_stmt = (AST_DeclStmt *)alloc_memory(sizeof(AST_DeclStmt), 1);
        decl_stmt->token = t;
        Token *p = peek2(parser);
        _Bool is_label = t->type == TOKEN_IDENTIFIER && p->type == TOKEN_SYMBOL && p->value == SYMBOL_COLON;
        if (!is_label && is_declaration_start(parser)) {
            decl_stmt->is_var_decl = 1;
            decl_stmt->item.var_decl = parse_declaration(parser, ((void *)0));
        } else {
            decl_stmt->is_var_decl = 0;
            decl_stmt->item.statement = parse_statement(parser);
        }
        list_append((decl_stmts), (void *)(decl_stmt), _Generic((decl_stmt), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
        synchronize(parser, t, start_depth, 0);
        t = ((Token *)((parser)->next->data));
    }
    return decl_stmts;
}
static AST_SelectionStatement *parse_selection_stmt(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    AST_SelectionStatement *selection = (AST_SelectionStatement *)alloc_memory(sizeof(AST_SelectionStatement), 1);
    selection->token = t;
    size_t paren_depth = parser->paren_depth;
    push_new_scope(parser);
    if (match(parser, TOKEN_KEYWORD, KEYWORD_IF)) {
        selection->is_switch = 0;
        expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after 'if'");
        selection->selection.if_stmt.cond_expr = parse_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after 'if' condition");
        synchronize_paren(parser, paren_depth);
        selection->selection.if_stmt.then_stmt = parse_statement(parser);
        if (match(parser, TOKEN_KEYWORD, KEYWORD_ELSE))
            selection->selection.if_stmt.else_stmt = parse_statement(parser);
        else
            selection->selection.if_stmt.else_stmt = ((void *)0);
    } else if (match(parser, TOKEN_KEYWORD, KEYWORD_SWITCH)) {
        selection->is_switch = 1;
        expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after 'switch'");
        selection->selection.switch_stmt.cond_expr = parse_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after 'switch' condition");
        synchronize_paren(parser, paren_depth);
        selection->selection.switch_stmt.stmt = parse_statement(parser);
    } else
        ((void)(0));
    (parser->current_scope = parser->current_scope->parent);
    return selection;
}
static AST_IterationStatement *parse_iteration_stmt(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    AST_IterationStatement *iteration = (AST_IterationStatement *)alloc_memory(sizeof(AST_IterationStatement), 1);
    iteration->token = t;
    size_t paren_depth = parser->paren_depth;
    push_new_scope(parser);
    if (match(parser, TOKEN_KEYWORD, KEYWORD_WHILE)) {
        iteration->loop_type = LOOP_WHILE;
        expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after 'while'");
        iteration->loop.while_stmt.expr = parse_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after 'while' condition");
        synchronize_paren(parser, paren_depth);
        iteration->loop.while_stmt.stmt = parse_statement(parser);
    } else if (match(parser, TOKEN_KEYWORD, KEYWORD_DO)) {
        iteration->loop_type = LOOP_DO_WHILE;
        iteration->loop.while_stmt.stmt = parse_statement(parser);
        expect(parser, TOKEN_KEYWORD, KEYWORD_WHILE, "Expected 'while' after 'do' statement");
        expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after 'while'");
        iteration->loop.while_stmt.expr = parse_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after 'while' condition");
        synchronize_paren(parser, paren_depth);
        expect(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON, "Expected ';' after 'do-while' statement");
    } else if (match(parser, TOKEN_KEYWORD, KEYWORD_FOR)) {
        iteration->loop_type = LOOP_FOR;
        expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after 'for'");
        if (is_declaration_start(parser)) {
            iteration->loop.for_stmt.is_init_decl = 1;
            iteration->loop.for_stmt.init.init_decl = parse_declaration(parser, ((void *)0));
        } else {
            iteration->loop.for_stmt.is_init_decl = 0;
            iteration->loop.for_stmt.init.init_expr = ((void *)0);
            if (!check(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON))
                iteration->loop.for_stmt.init.init_expr = parse_expression(parser);
            expect(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON, "Expected ';' after 'for' initializer");
        }
        iteration->loop.for_stmt.cond_expr = ((void *)0);
        if (!check(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON))
            iteration->loop.for_stmt.cond_expr = parse_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON, "Expected ';' after 'for' condition");
        iteration->loop.for_stmt.loop_expr = ((void *)0);
        if (!check(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS))
            iteration->loop.for_stmt.loop_expr = parse_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after 'for' increment");
        synchronize_paren(parser, paren_depth);
        iteration->loop.for_stmt.stmt = parse_statement(parser);
    } else
        ((void)(0));
    (parser->current_scope = parser->current_scope->parent);
    return iteration;
}
static AST_JumpStatement *parse_jump_stmt(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    AST_JumpStatement *jump = (AST_JumpStatement *)alloc_memory(sizeof(AST_JumpStatement), 1);
    jump->token = t;
    if (match(parser, TOKEN_KEYWORD, KEYWORD_GOTO)) {
        jump->jump_type = JUMP_GOTO;
        jump->jump.identifier = expect(parser, TOKEN_IDENTIFIER, ((void *)0), "Expected identifier after 'goto'");
    } else if (match(parser, TOKEN_KEYWORD, KEYWORD_CONTINUE)) {
        jump->jump_type = JUMP_CONTINUE;
        jump->jump.none = ((void *)0);
    } else if (match(parser, TOKEN_KEYWORD, KEYWORD_BREAK)) {
        jump->jump_type = JUMP_BREAK;
        jump->jump.none = ((void *)0);
    } else if (match(parser, TOKEN_KEYWORD, KEYWORD_RETURN)) {
        jump->jump_type = JUMP_RETURN;
        jump->jump.expr = ((void *)0);
        if (!check(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON))
            jump->jump.expr = parse_expression(parser);
    } else
        ((void)(0));
    expect(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON, "Expected ';' after jump statement");
    return jump;
}
static AST_Statement *parse_statement(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    Token *p = peek2(parser);
    AST_Statement *stmt = (AST_Statement *)alloc_memory(sizeof(AST_Statement), 1);
    stmt->token = t;
    if (match(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
        push_new_scope(parser);
        stmt->stmt_type = STMT_COMPOUND;
        stmt->stmt.compound = parse_compound_stmt(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE, "Expected '}' to close compound statement");
        (parser->current_scope = parser->current_scope->parent);
    } else if (t->type == TOKEN_KEYWORD && (t->value == KEYWORD_CASE || t->value == KEYWORD_DEFAULT)) {
        stmt->stmt_type = STMT_LABELED;
        t = get(parser);
        stmt->stmt.label = (AST_LabeledStatement *)alloc_memory(sizeof(AST_LabeledStatement), 1);
        if (t->value == KEYWORD_CASE) {
            *(stmt->stmt.label) = (AST_LabeledStatement){.token = t, .label_type = LABEL_CASE, .label.case_stmt = parse_conditional_expression(parser), .stmt = ((void *)0)};
            expect(parser, TOKEN_SYMBOL, SYMBOL_COLON, "Expected ':' after case");
        } else {
            *(stmt->stmt.label) = (AST_LabeledStatement){.token = t, .label_type = LABEL_DEFAULT, .label.none = ((void *)0), .stmt = ((void *)0)};
            expect(parser, TOKEN_SYMBOL, SYMBOL_COLON, "Expected ':' after default");
        }
        if (check(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE))
            report_warning(parser, (((Token *)((parser)->next->data))), ("Label at end of compound statement"));
        else
            stmt->stmt.label->stmt = parse_statement(parser);
    } else if (t->type == TOKEN_IDENTIFIER && p->type == TOKEN_SYMBOL && p->value == SYMBOL_COLON) {
        stmt->stmt_type = STMT_LABELED;
        t = get(parser);
        get(parser);
        stmt->stmt.label = (AST_LabeledStatement *)alloc_memory(sizeof(AST_LabeledStatement), 1);
        *(stmt->stmt.label) = (AST_LabeledStatement){.token = t, .label_type = LABEL_IDENTIFIER, .label.identifier = t, .stmt = ((void *)0)};
        if (check(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE))
            report_warning(parser, (((Token *)((parser)->next->data))), ("Label at end of compound statement"));
        else
            stmt->stmt.label->stmt = parse_statement(parser);
    } else if (t->type == TOKEN_KEYWORD && (t->value == KEYWORD_IF || t->value == KEYWORD_SWITCH)) {
        stmt->stmt_type = STMT_SELECTION;
        stmt->stmt.selection = parse_selection_stmt(parser);
    } else if (t->type == TOKEN_KEYWORD && (t->value == KEYWORD_FOR || t->value == KEYWORD_DO || t->value == KEYWORD_WHILE)) {
        stmt->stmt_type = STMT_ITERATION;
        stmt->stmt.iteration = parse_iteration_stmt(parser);
    } else if (t->type == TOKEN_KEYWORD && (t->value == KEYWORD_GOTO || t->value == KEYWORD_CONTINUE || t->value == KEYWORD_BREAK || t->value == KEYWORD_RETURN)) {
        stmt->stmt_type = STMT_JUMP;
        stmt->stmt.jump = parse_jump_stmt(parser);
    } else {
        stmt->stmt_type = STMT_EXPRESSION;
        stmt->stmt.expression = ((void *)0);
        if (!check(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON))
            stmt->stmt.expression = parse_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON, "Expected ';' after expression statement");
    }
    return stmt;
}
static AST_TypeSpec *parse_type_specifier(Parser *parser);
static List_AST_SpecifierQualifier *parse_spec_qual_list(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    List_AST_SpecifierQualifier *spec_qual_list = list_create(_Generic((AST_SpecifierQualifier *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    _Bool seen_type = 0;
    while (1) {
        t = ((Token *)((parser)->next->data));
        AST_SpecifierQualifier *spec_qual = (AST_SpecifierQualifier *)alloc_memory(sizeof(AST_SpecifierQualifier), 1);
        spec_qual->token = t;
        if (is_type_qualifier_start(parser, 0)) {
            spec_qual->is_type_spec = 0;
            t = get(parser);
            spec_qual->spec.type_qualifier = t->value;
        } else if (is_type_specifier_start(parser, seen_type)) {
            spec_qual->is_type_spec = 1;
            spec_qual->spec.type_spec = parse_type_specifier(parser);
            seen_type = 1;
        } else
            break;
        list_append((spec_qual_list), (void *)(spec_qual), _Generic((spec_qual), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    }
    if (((spec_qual_list) == ((void *)0) || (spec_qual_list)->head == ((void *)0))) {
        report_error(parser, (t), ("Expected type qualifier or specifier"));
        return ((void *)0);
    }
    return spec_qual_list;
}
static AST_StaticAssertDecl *parse_static_assert(Parser *parser, Token *t) {
    AST_StaticAssertDecl *decl = (AST_StaticAssertDecl *)alloc_memory(sizeof(AST_StaticAssertDecl), 1);
    *decl = (AST_StaticAssertDecl){.token = t, .expr = ((void *)0), .message = ((void *)0)};
    expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after '_Static_assert'");
    decl->expr = parse_conditional_expression(parser);
    expect(parser, TOKEN_SYMBOL, SYMBOL_COMMA, "Expected ',' after '_Static_assert' condition");
    Token *str = ((void *)0);
    if (((Token *)((parser)->next->data))->type == TOKEN_SYNTAX_ERROR_STRING)
        report_error(parser, (((Token *)((parser)->next->data))), ("Invalid string literal"));
    else
        str = expect(parser, TOKEN_STRING, ((void *)0), "Expected string literal as '_Static_assert' message");
    if (str != ((void *)0))
        decl->message = str;
    expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after '_Static_assert' message");
    expect(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON, "Expected ';' after '_Static_assert'");
    return decl;
}
static AST_Declarator *parse_declarator(Parser *parser, _Bool *is_abs);
static AST_StructDecl *parse_struct_decl(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    AST_StructDecl *struct_decl = (AST_StructDecl *)alloc_memory(sizeof(AST_StructDecl), 1);
    struct_decl->token = t;
    struct_decl->is_static_assert_decl = 0;
    if (match(parser, TOKEN_KEYWORD, KEYWORD_STATIC_ASSERT)) {
        struct_decl->is_static_assert_decl = 1;
        struct_decl->decl.static_assert_decl = parse_static_assert(parser, t);
    } else {
        List_AST_SpecifierQualifier *spec_qual_list = parse_spec_qual_list(parser);
        List_AST_StructDeclarator *struct_declarators = ((void *)0);
        if (!check(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON)) {
            struct_declarators = list_create(_Generic((AST_StructDeclarator *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
            do {
                t = ((Token *)((parser)->next->data));
                AST_StructDeclarator *struct_declarator = (AST_StructDeclarator *)alloc_memory(sizeof(AST_StructDeclarator), 1);
                *struct_declarator = (AST_StructDeclarator){.token = t, .declarator = ((void *)0), .constant_expr = ((void *)0)};
                if (!check(parser, TOKEN_SYMBOL, SYMBOL_COLON)) {
                    _Bool is_abs = 0;
                    struct_declarator->declarator = parse_declarator(parser, &is_abs);
                    if (is_abs) {
                        report_error(parser, (struct_declarator->token), ("Expected declarator in struct declaration"));
                        return ((void *)0);
                    }
                }
                if (match(parser, TOKEN_SYMBOL, SYMBOL_COLON))
                    struct_declarator->constant_expr = parse_conditional_expression(parser);
                if (struct_declarator->declarator == ((void *)0) && struct_declarator->constant_expr == ((void *)0)) {
                    report_error(parser, (struct_declarator->token), ("Expected declarator or bit-field in struct declaration"));
                    return ((void *)0);
                }
                list_append((struct_declarators), (void *)(struct_declarator), _Generic((struct_declarator), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
            } while (match(parser, TOKEN_SYMBOL, SYMBOL_COMMA));
        } else {
            _Bool has_struct_or_union = 0;
            for (List *spec_qual__l = (spec_qual_list); spec_qual__l != ((void *)0) && spec_qual__l->head != ((void *)0); spec_qual__l = ((void *)0))
                for (ListNode *spec_qual__n = spec_qual__l->head; spec_qual__n != ((void *)0); spec_qual__n = spec_qual__n->next)
                    for (AST_SpecifierQualifier *spec_qual = (AST_SpecifierQualifier *)spec_qual__n->data; spec_qual != ((void *)0); spec_qual = ((void *)0)) {
                        if (spec_qual->is_type_spec && spec_qual->spec.type_spec->spec_type == TYPE_SPEC_STRUCT_UNION) {
                            has_struct_or_union = 1;
                            goto skip_foreach_in_parse_struct_decl;
                        }
                    }
        skip_foreach_in_parse_struct_decl:
            if (!has_struct_or_union)
                report_warning(parser, (struct_decl->token), ("Declaration does not declare anything"));
        }
        expect(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON, "Expected ';' after struct declaration");
        struct_decl->decl.general_struct_decl.spec_qual_list = spec_qual_list;
        struct_decl->decl.general_struct_decl.struct_declarators = struct_declarators;
    }
    return struct_decl;
}
static AST_TypeName *parse_type_name(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    AST_TypeName *type_name = (AST_TypeName *)alloc_memory(sizeof(AST_TypeName), 1);
    type_name->token = t;
    type_name->spec_qual_list = parse_spec_qual_list(parser);
    t = ((Token *)((parser)->next->data));
    if (t->type == TOKEN_IDENTIFIER || (t->type == TOKEN_SYMBOL && (t->value == SYMBOL_MUL || t->value == SYMBOL_L_PARENTHESIS || t->value == SYMBOL_L_BRACKET))) {
        _Bool is_abs = 1;
        type_name->abs_declarator = parse_declarator(parser, &is_abs);
        if (!is_abs) {
            report_error(parser, (get_declarator_identifier(type_name->abs_declarator->direct_declarator)), ("Expected abstract declarator in type name"));
            return ((void *)0);
        }
    }
    return type_name;
}
static List_AST_DeclSpec *parse_declaration_specifiers(Parser *parser);
static List_AST_ParamDecl *parse_parameter_declarations(Parser *parser, _Bool *is_variadic) {
    Token *t = ((Token *)((parser)->next->data));
    *is_variadic = 0;
    List_AST_ParamDecl *param_decls = list_create(_Generic((AST_ParamDecl *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    if (match(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS))
        return param_decls;
    do {
        if (match(parser, TOKEN_SYMBOL, SYMBOL_ELLIPSIS)) {
            if (((param_decls) == ((void *)0) || (param_decls)->head == ((void *)0)))
                report_warning(parser, (t), ("ISO C requires a named parameter before '...'"));
            *is_variadic = 1;
            break;
        }
        AST_ParamDecl *param_decl = (AST_ParamDecl *)alloc_memory(sizeof(AST_ParamDecl), 1);
        t = ((Token *)((parser)->next->data));
        *param_decl = (AST_ParamDecl){.token = t, .decl_specs = parse_declaration_specifiers(parser), .decl = ((void *)0), .is_abs = 1};
        t = ((Token *)((parser)->next->data));
        if (t->type == TOKEN_IDENTIFIER || (t->type == TOKEN_SYMBOL && (t->value == SYMBOL_MUL || t->value == SYMBOL_L_PARENTHESIS || t->value == SYMBOL_L_BRACKET))) {
            param_decl->is_abs = 1;
            param_decl->decl = parse_declarator(parser, &param_decl->is_abs);
            if (!param_decl->is_abs)
                add_name(parser, get_declarator_identifier(param_decl->decl->direct_declarator), 0);
        }
        list_append((param_decls), (void *)(param_decl), _Generic((param_decl), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    } while (match(parser, TOKEN_SYMBOL, SYMBOL_COMMA));
    expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ',' or ')' in parameter list");
    return param_decls;
}
static AST_Pointer *parse_pointer(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    AST_Pointer *pointer = (AST_Pointer *)alloc_memory(sizeof(AST_Pointer), 1);
    expect(parser, TOKEN_SYMBOL, SYMBOL_MUL, "Expected '*' in pointer declarator");
    *pointer = (AST_Pointer){.token = t, .type_qualifiers = ((void *)0), .pointer = ((void *)0)};
    if (is_type_qualifier_start(parser, 1)) {
        pointer->type_qualifiers = list_create(_Generic((string)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
        while (is_type_qualifier_start(parser, 1)) {
            t = get(parser);
            list_append((pointer->type_qualifiers), (void *)(t->value), _Generic((t->value), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
        }
    }
    if (check(parser, TOKEN_SYMBOL, SYMBOL_MUL))
        pointer->pointer = parse_pointer(parser);
    return pointer;
}
static AST_Designator *parse_designator(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    AST_Designator *designator = (AST_Designator *)alloc_memory(sizeof(AST_Designator), 1);
    designator->token = t;
    if (match(parser, TOKEN_SYMBOL, SYMBOL_DOT)) {
        Token *id = expect(parser, TOKEN_IDENTIFIER, ((void *)0), "Expected member name after '.' in designator");
        designator->is_constant_expr = 0;
        designator->designator.identifier = id;
    } else if (match(parser, TOKEN_SYMBOL, SYMBOL_L_BRACKET)) {
        designator->is_constant_expr = 1;
        designator->designator.constant_expr = parse_conditional_expression(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACKET, "Expected ']' after array index in designator");
    } else
        ((void)(0));
    return designator;
}
static AST_Initializer *parse_initializer(Parser *parser);
static AST_InitializerItem *parse_initializer_item(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    AST_InitializerItem *item = (AST_InitializerItem *)alloc_memory(sizeof(AST_InitializerItem), 1);
    item->token = t;
    item->designation = ((void *)0);
    if (check(parser, TOKEN_SYMBOL, SYMBOL_DOT) || check(parser, TOKEN_SYMBOL, SYMBOL_L_BRACKET)) {
        item->designation = list_create(_Generic((AST_Designator *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
        while (check(parser, TOKEN_SYMBOL, SYMBOL_DOT) || check(parser, TOKEN_SYMBOL, SYMBOL_L_BRACKET))
            list_append((item->designation), (void *)(parse_designator(parser)), _Generic((parse_designator(parser)), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
        expect(parser, TOKEN_SYMBOL, SYMBOL_ASSIGN, "Expected '=' after designator");
    }
    item->initializer = parse_initializer(parser);
    return item;
}
static AST_Initializer *parse_initializer(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    AST_Initializer *init = (AST_Initializer *)alloc_memory(sizeof(AST_Initializer), 1);
    init->token = t;
    if (match(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
        init->is_assignment_expr = 0;
        init->init.inits = list_create(_Generic((AST_InitializerItem *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
        do {
            if (check(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE))
                break;
            list_append((init->init.inits), (void *)(parse_initializer_item(parser)), _Generic((parse_initializer_item(parser)), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
        } while (match(parser, TOKEN_SYMBOL, SYMBOL_COMMA));
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE, "Expected ',' or '}' in initializer list");
        if (((init->init.inits) == ((void *)0) || (init->init.inits)->head == ((void *)0)))
            report_warning(parser, (t), ("ISO C forbids empty initializer braces"));
    } else {
        init->is_assignment_expr = 1;
        init->init.assignment_expr = parse_assignment_expression(parser);
    }
    return init;
}
static AST_TypeSpec *parse_type_specifier(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    AST_TypeSpec *type = (AST_TypeSpec *)alloc_memory(sizeof(AST_TypeSpec), 1);
    type->token = t;
    if (t->type == TOKEN_KEYWORD) {
        if (t->value == KEYWORD_ATOMIC) {
            type->spec_type = TYPE_SPEC_ATOMIC;
            get(parser);
            expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after '_Atomic'");
            type->spec.atomic_spec = parse_type_name(parser);
            expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after '_Atomic' type name");
        } else if (t->value == KEYWORD_VOID || t->value == KEYWORD_CHAR || t->value == KEYWORD_SHORT || t->value == KEYWORD_INT || t->value == KEYWORD_LONG || t->value == KEYWORD_FLOAT || t->value == KEYWORD_DOUBLE || t->value == KEYWORD_SIGNED || t->value == KEYWORD_UNSIGNED || t->value == KEYWORD_BOOL || t->value == KEYWORD_IMAGINARY || t->value == KEYWORD_COMPLEX) {
            t = get(parser);
            type->spec_type = TYPE_SPEC_KEYWORD;
            type->spec.keyword_spec = t->value;
        } else if (t->value == KEYWORD_STRUCT || t->value == KEYWORD_UNION) {
            t = get(parser);
            type->spec_type = TYPE_SPEC_STRUCT_UNION;
            type->spec.struct_union_spec.is_struct = t->value == KEYWORD_STRUCT;
            t = ((Token *)((parser)->next->data));
            if (match(parser, TOKEN_IDENTIFIER, ((void *)0)))
                type->spec.struct_union_spec.identifier = t;
            else
                type->spec.struct_union_spec.identifier = ((void *)0);
            List_AST_StructDecl *members = ((void *)0);
            if (match(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
                members = list_create(_Generic((AST_StructDecl *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                while (1) {
                    t = ((Token *)((parser)->next->data));
                    size_t start_depth = parser->brace_depth;
                    if (is_type_start(parser, t) || (t->type == TOKEN_KEYWORD && t->value == KEYWORD_STATIC_ASSERT)) {
                        AST_StructDecl *decl = parse_struct_decl(parser);
                        list_append((members), (void *)(decl), _Generic((decl), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                        synchronize(parser, t, start_depth, 0);
                    } else if (check(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE) || ((t)->type == TOKEN_EOF))
                        break;
                    else {
                        report_error(parser, (t), ("Expected member declaration"));
                        synchronize(parser, t, start_depth, 0);
                    }
                }
                if (type->spec.struct_union_spec.is_struct)
                    expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE, "Expected member declaration or '}' in struct");
                else
                    expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE, "Expected member declaration or '}' in union");
            }
            type->spec.struct_union_spec.members = members;
            if (members != ((void *)0) && ((members) == ((void *)0) || (members)->head == ((void *)0))) {
                if (type->spec.struct_union_spec.is_struct)
                    report_warning(parser, (t), ("Struct has no members"));
                else
                    report_warning(parser, (t), ("Union has no members"));
            } else if (type->spec.struct_union_spec.identifier == ((void *)0) && members == ((void *)0)) {
                if (type->spec.struct_union_spec.is_struct)
                    report_error(parser, (t), ("Expected tag name or '{' after 'struct'"));
                else
                    report_error(parser, (t), ("Expected tag name or '{' after 'union'"));
            }
        } else if (t->value == KEYWORD_ENUM) {
            t = get(parser);
            type->spec_type = TYPE_SPEC_ENUM;
            t = ((Token *)((parser)->next->data));
            if (match(parser, TOKEN_IDENTIFIER, ((void *)0)))
                type->spec.enum_spec.identifier = t;
            else
                type->spec.enum_spec.identifier = ((void *)0);
            List_AST_Enumerator *enumerators = ((void *)0);
            if (match(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
                enumerators = list_create(_Generic((AST_Enumerator *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                while (1) {
                    t = ((Token *)((parser)->next->data));
                    if (t->type == TOKEN_IDENTIFIER) {
                        t = get(parser);
                        AST_Enumerator *enumerator = (AST_Enumerator *)alloc_memory(sizeof(AST_Enumerator), 1);
                        *enumerator = (AST_Enumerator){.token = t, .identifier = t, .constant_expr = ((void *)0)};
                        if (match(parser, TOKEN_SYMBOL, SYMBOL_ASSIGN))
                            enumerator->constant_expr = parse_conditional_expression(parser);
                        add_name(parser, t, 0);
                        list_append((enumerators), (void *)(enumerator), _Generic((enumerator), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                    } else
                        break;
                    if (!match(parser, TOKEN_SYMBOL, SYMBOL_COMMA))
                        break;
                }
                expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE, "Expected ',' or '}' in enumerator list");
            }
            type->spec.enum_spec.enumerators = enumerators;
            if (enumerators != ((void *)0) && ((enumerators) == ((void *)0) || (enumerators)->head == ((void *)0)))
                report_warning(parser, (t), ("Enum has no enumerators"));
            else if (type->spec.enum_spec.identifier == ((void *)0) && enumerators == ((void *)0))
                report_error(parser, (t), ("Expected tag name or '{' after 'enum'"));
        } else
            ((void)(0));
    } else if (t->type == TOKEN_IDENTIFIER && is_typedef_name(parser, t->value)) {
        t = get(parser);
        type->spec_type = TYPE_SPEC_TYPEDEF_NAME;
        type->spec.typedef_name = t;
    }
    return type;
}
static AST_DirectDeclarator *parse_function_suffix(Parser *parser, AST_DirectDeclarator *inner, Token *t) {
    _Bool is_variadic = 0;
    AST_Scope *scope = create_scope(parser->current_scope);
    parser->current_scope = scope;
    List_AST_ParamDecl *params = parse_parameter_declarations(parser, &is_variadic);
    parser->current_scope = scope->parent;
    AST_DirectDeclarator *new = (AST_DirectDeclarator *)alloc_memory(sizeof(AST_DirectDeclarator), 1);
    *new = (AST_DirectDeclarator){.token = t, .decl_type = DECLARATOR_FUNC, .decl.func.direct_declarator = inner, .decl.func.param_decls = params, .decl.func.is_variadic = is_variadic, .func_proto_scope = scope};
    return new;
}
static AST_DirectDeclarator *parse_direct_declarator(Parser *parser, _Bool *is_abs) {
    Token *t = ((Token *)((parser)->next->data));
    AST_DirectDeclarator *direct_decl = ((void *)0);
    _Bool allow_abs = *is_abs;
    *is_abs = 1;
    if (match(parser, TOKEN_IDENTIFIER, ((void *)0))) {
        direct_decl = (AST_DirectDeclarator *)alloc_memory(sizeof(AST_DirectDeclarator), 1);
        *direct_decl = (AST_DirectDeclarator){.token = t, .decl_type = DECLARATOR_ID, .decl.identifier = t};
        *is_abs = 0;
    } else if (match(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS)) {
        if (allow_abs && (check(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS) || is_declaration_start(parser))) {
            direct_decl = parse_function_suffix(parser, ((void *)0), t);
        } else {
            _Bool is_inner_abs = allow_abs;
            direct_decl = (AST_DirectDeclarator *)alloc_memory(sizeof(AST_DirectDeclarator), 1);
            *direct_decl = (AST_DirectDeclarator){.token = t, .decl_type = DECLARATOR_DECL, .decl.declarator = parse_declarator(parser, &is_inner_abs)};
            if (!is_inner_abs)
                *is_abs = 0;
            expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' to close parenthesized declarator");
        }
    }
    while (1) {
        if (match(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS)) {
            direct_decl = parse_function_suffix(parser, direct_decl, t);
        } else if (match(parser, TOKEN_SYMBOL, SYMBOL_L_BRACKET)) {
            _Bool has_static = 0;
            _Bool has_star = 0;
            List_string type_qualifiers = ((void *)0);
            Token *p = peek2(parser);
            if (is_type_qualifier_start(parser, 1)) {
                type_qualifiers = list_create(_Generic((string)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                while (is_type_qualifier_start(parser, 1)) {
                    Token *tt = get(parser);
                    list_append((type_qualifiers), (void *)(tt->value), _Generic((tt->value), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                }
                p = peek2(parser);
                if (check(parser, TOKEN_SYMBOL, SYMBOL_MUL) && p->type == TOKEN_SYMBOL && p->value == SYMBOL_R_BRACKET) {
                    get(parser);
                    has_star = 1;
                } else if (match(parser, TOKEN_KEYWORD, KEYWORD_STATIC))
                    has_static = 1;
            } else if (check(parser, TOKEN_SYMBOL, SYMBOL_MUL) && p->type == TOKEN_SYMBOL && p->value == SYMBOL_R_BRACKET) {
                get(parser);
                has_star = 1;
            } else if (match(parser, TOKEN_KEYWORD, KEYWORD_STATIC)) {
                has_static = 1;
                if (is_type_qualifier_start(parser, 1)) {
                    type_qualifiers = list_create(_Generic((string)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                    while (is_type_qualifier_start(parser, 1)) {
                        Token *tt = get(parser);
                        list_append((type_qualifiers), (void *)(tt->value), _Generic((tt->value), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
                    }
                }
            }
            AST_AssignmentExpression *expr = ((void *)0);
            if (has_static || (!has_star && !check(parser, TOKEN_SYMBOL, SYMBOL_R_BRACKET)))
                expr = parse_assignment_expression(parser);
            expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACKET, "Expected ']' to close array declarator");
            AST_DirectDeclarator *new = (AST_DirectDeclarator *)alloc_memory(sizeof(AST_DirectDeclarator), 1);
            if (has_static || expr != ((void *)0))
                *new = (AST_DirectDeclarator){.token = t, .decl_type = DECLARATOR_ARRAY, .decl.array.direct_declarator = direct_decl, .decl.array.assignment_expression = expr, .decl.array.is_static = has_static, .decl.array.type_qualifiers = type_qualifiers};
            else
                *new = (AST_DirectDeclarator){.token = t, .decl_type = DECLARATOR_INCOMPLETE_ARRAY, .decl.incomplete_array.direct_declarator = direct_decl, .decl.incomplete_array.has_star = has_star, .decl.incomplete_array.type_qualifiers = type_qualifiers};
            direct_decl = new;
        } else
            break;
    }
    return direct_decl;
}
static AST_Declarator *parse_declarator(Parser *parser, _Bool *is_abs) {
    AST_Declarator *decl = (AST_Declarator *)alloc_memory(sizeof(AST_Declarator), 1);
    *decl = (AST_Declarator){.token = ((Token *)((parser)->next->data)), .pointer = ((void *)0), .direct_declarator = ((void *)0)};
    if (check(parser, TOKEN_SYMBOL, SYMBOL_MUL))
        decl->pointer = parse_pointer(parser);
    decl->direct_declarator = parse_direct_declarator(parser, is_abs);
    return decl;
}
static List_AST_DeclSpec *parse_declaration_specifiers(Parser *parser) {
    List_AST_DeclSpec *decl_specs = list_create(_Generic((AST_DeclSpec *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    _Bool seen_type = 0;
    for (Token *t = ((Token *)((parser)->next->data)); !((t)->type == TOKEN_EOF); t = ((Token *)((parser)->next->data))) {
        AST_DeclSpec *decl_spec = (AST_DeclSpec *)alloc_memory(sizeof(AST_DeclSpec), 1);
        decl_spec->token = t;
        if (is_type_specifier_start(parser, seen_type)) {
            decl_spec->specifier_type = SPEC_TYPE_SPEC;
            decl_spec->specifier.type = parse_type_specifier(parser);
            seen_type = 1;
        } else if (is_type_qualifier_start(parser, 0)) {
            decl_spec->specifier_type = SPEC_KEYWORD;
            decl_spec->specifier.keyword = t->value;
            get(parser);
        } else if (t->type == TOKEN_KEYWORD) {
            if (t->value == KEYWORD_TYPEDEF || t->value == KEYWORD_EXTERN || t->value == KEYWORD_STATIC || t->value == KEYWORD_THREAD_LOCAL || t->value == KEYWORD_AUTO || t->value == KEYWORD_REGISTER || t->value == KEYWORD_INLINE || t->value == KEYWORD_NORETURN) {
                decl_spec->specifier_type = SPEC_KEYWORD;
                decl_spec->specifier.keyword = t->value;
                get(parser);
            } else if (t->value == KEYWORD_ALIGNAS) {
                decl_spec->specifier_type = SPEC_ALIGNMENT;
                get(parser);
                expect(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS, "Expected '(' after '_Alignas'");
                if (is_type_start(parser, ((Token *)((parser)->next->data)))) {
                    decl_spec->specifier.alignment.spec.type_name = parse_type_name(parser);
                    decl_spec->specifier.alignment.is_type_name = 1;
                } else {
                    decl_spec->specifier.alignment.spec.constant_expression = parse_conditional_expression(parser);
                    decl_spec->specifier.alignment.is_type_name = 0;
                }
                expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after '_Alignas' operand");
            } else
                break;
        } else
            break;
        list_append((decl_specs), (void *)(decl_spec), _Generic((decl_spec), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    }
    if (((decl_specs) == ((void *)0) || (decl_specs)->head == ((void *)0))) {
        report_error(parser, (((Token *)((parser)->next->data))), ("Expected type name or declaration specifier"));
        return ((void *)0);
    }
    return decl_specs;
}
static AST_VarDecl *parse_var_decl(Parser *parser, List_AST_DeclSpec *decl_specs, AST_Declarator *first, Token *t) {
    AST_VarDecl *var_decl = (AST_VarDecl *)alloc_memory(sizeof(AST_VarDecl), 1);
    *var_decl = (AST_VarDecl){.token = t, .is_static_assert_decl = 0, .decl.general_decl.decl_specs = decl_specs, .decl.general_decl.init_decls = list_create(_Generic((AST_InitDecl *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol))};
    if (first == ((void *)0) && match(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON)) {
        if (decl_specs != ((void *)0)) {
            AST_TypeSpec *tag = ((void *)0);
            AST_DeclSpec *redundant = ((void *)0);
            Token *tt = ((void *)0);
            for (List *spec__l = (decl_specs); spec__l != ((void *)0) && spec__l->head != ((void *)0); spec__l = ((void *)0))
                for (ListNode *spec__n = spec__l->head; spec__n != ((void *)0); spec__n = spec__n->next)
                    for (AST_DeclSpec *spec = (AST_DeclSpec *)spec__n->data; spec != ((void *)0); spec = ((void *)0)) {
                        if (tt == ((void *)0))
                            tt = spec->token;
                        if (spec->specifier_type == SPEC_TYPE_SPEC) {
                            AST_TypeSpec *type = spec->specifier.type;
                            if (type->spec_type == TYPE_SPEC_STRUCT_UNION || type->spec_type == TYPE_SPEC_ENUM)
                                tag = type;
                        } else if (redundant == ((void *)0))
                            redundant = spec;
                    }
            if (tag == ((void *)0))
                report_warning(parser, (tt), ("Declaration does not declare anything"));
            else if (tag->spec_type == TYPE_SPEC_STRUCT_UNION && tag->spec.struct_union_spec.identifier == ((void *)0))
                report_warning(parser, (tag->token), ("Unnamed struct/union that defines no instances"));
            else if (redundant != ((void *)0))
                report_warning(parser, (redundant->token), ("Useless specifier in empty declaration"));
        }
        return var_decl;
    }
    AST_Declarator *decl = first;
    while (1) {
        Token *decl_t = ((Token *)((parser)->next->data));
        if (decl != ((void *)0)) {
            decl_t = decl->token;
            _Bool is_typedef = has_typedef(decl_specs);
            add_name(parser, get_declarator_identifier(decl->direct_declarator), is_typedef);
        }
        AST_Initializer *init = ((void *)0);
        if (match(parser, TOKEN_SYMBOL, SYMBOL_ASSIGN))
            init = parse_initializer(parser);
        AST_InitDecl *init_decl = (AST_InitDecl *)alloc_memory(sizeof(AST_InitDecl), 1);
        *init_decl = (AST_InitDecl){.token = decl_t, .declarator = decl, .initializer = init};
        list_append((var_decl->decl.general_decl.init_decls), (void *)(init_decl), _Generic((init_decl), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
        if (!match(parser, TOKEN_SYMBOL, SYMBOL_COMMA))
            break;
        _Bool is_abs = 0;
        decl = parse_declarator(parser, &is_abs);
        if (is_abs) {
            report_error(parser, (decl->token), ("Expected identifier in declarator after ','"));
            break;
        }
    }
    expect(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON, "Expected ',' or ';' after declarator");
    return var_decl;
}
static AST_VarDecl *parse_declaration(Parser *parser, AST_FuncDecl **func_def) {
    Token *t = ((Token *)((parser)->next->data));
    if (match(parser, TOKEN_KEYWORD, KEYWORD_STATIC_ASSERT)) {
        AST_VarDecl *var_decl = (AST_VarDecl *)alloc_memory(sizeof(AST_VarDecl), 1);
        *var_decl = (AST_VarDecl){.token = t, .is_static_assert_decl = 1, .decl.static_assert_decl = parse_static_assert(parser, t)};
        return var_decl;
    }
    List_AST_DeclSpec *decl_specs = parse_declaration_specifiers(parser);
    if (check(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON))
        return parse_var_decl(parser, decl_specs, ((void *)0), t);
    _Bool is_abs = 0;
    AST_Declarator *decl = parse_declarator(parser, &is_abs);
    if (is_abs) {
        report_error(parser, (decl->token), ("Expected identifier in declarator"));
        return ((void *)0);
    }
    if (check(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
        AST_DirectDeclarator *func_declarator = get_function_declarator(decl, ((void *)0));
        if (func_declarator == ((void *)0))
            report_error(parser, (((Token *)((parser)->next->data))), ("Expected ';' after declaration (only a function declarator can have a body)"));
        else if (func_def == ((void *)0))
            report_error(parser, (((Token *)((parser)->next->data))), ("Function definition is not allowed here"));
        else {
            get(parser);
            add_name(parser, get_declarator_identifier(decl->direct_declarator), 0);
            AST_Scope *body = func_declarator->func_proto_scope;
            parser->current_scope = body;
            List_AST_DeclStmt *compound = parse_compound_stmt(parser);
            expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE, "Expected '}' at end of function body");
            parser->current_scope = body->parent;
            AST_FuncDecl *func_decl = (AST_FuncDecl *)alloc_memory(sizeof(AST_FuncDecl), 1);
            *func_decl = (AST_FuncDecl){.token = t, .decl_specs = decl_specs, .declarator = decl, .body = compound};
            *func_def = func_decl;
        }
        return ((void *)0);
    }
    return parse_var_decl(parser, decl_specs, decl, t);
}
AST_TU *parse_parser(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    AST_TU *tu = (AST_TU *)alloc_memory(sizeof(AST_TU), 1);
    tu->token = t;
    tu->filename = t->filename;
    tu->extern_decls = list_create(_Generic((AST_ExternDecl *)0, string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
    while (!((t)->type == TOKEN_EOF)) {
        size_t start_depth = parser->brace_depth;
        if (match(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON))
            report_warning(parser, (t), ("Extra ';' outside of a function"));
        else {
            AST_FuncDecl *func_decl = ((void *)0);
            AST_VarDecl *var_decl = parse_declaration(parser, &func_decl);
            AST_ExternDecl *extern_decl = ((void *)0);
            extern_decl = (AST_ExternDecl *)alloc_memory(sizeof(AST_ExternDecl), 1);
            if (func_decl != ((void *)0))
                *extern_decl = (AST_ExternDecl){.token = t, .decl.func_decl = func_decl, .is_func_decl = 1};
            else if (var_decl != ((void *)0))
                *extern_decl = (AST_ExternDecl){.token = t, .decl.var_decl = var_decl, .is_func_decl = 0};
            if (func_decl != ((void *)0) || var_decl != ((void *)0))
                list_append((tu->extern_decls), (void *)(extern_decl), _Generic((extern_decl), string: LIST_TYPE_string, ppToken *: LIST_TYPE_ppToken, ppMacro *: LIST_TYPE_ppMacro, ppCondFrame *: LIST_TYPE_ppCondFrame, List_ppToken *: LIST_TYPE_List_ppToken, Token *: LIST_TYPE_Token, AST_ExternDecl *: LIST_TYPE_AST_ExternDecl, AST_DeclSpec *: LIST_TYPE_AST_DeclSpec, AST_InitDecl *: LIST_TYPE_AST_InitDecl, AST_ParamDecl *: LIST_TYPE_AST_ParamDecl, AST_StructDecl *: LIST_TYPE_AST_StructDecl, AST_Enumerator *: LIST_TYPE_AST_Enumerator, AST_InitializerItem *: LIST_TYPE_AST_InitializerItem, AST_Designator *: LIST_TYPE_AST_Designator, AST_SpecifierQualifier *: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator *: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt *: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression *: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation *: LIST_TYPE_AST_GenericAssociation, AST_TypeName *: LIST_TYPE_AST_TypeName, AST_Symbol *: LIST_TYPE_AST_Symbol));
        }
        synchronize(parser, t, start_depth, 1);
        if (((Token *)((parser)->next->data)) == t)
            get(parser);
        t = ((Token *)((parser)->next->data));
    }
    return tu;
}
