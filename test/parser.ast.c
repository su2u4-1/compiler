typedef unsigned long long size_t;
typedef struct {
    long long a;
    long double b;
} max_align_t;
typedef unsigned long long uintmax_t;
typedef long long intmax_t;
typedef struct {
    void *placeholder;
} FILE;
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
typedef enum SymbolKind {
    SYMBOL_KIND_VAR,
    SYMBOL_KIND_FUNC,
    SYMBOL_KIND_TYPEDEF,
    SYMBOL_KIND_ENUM_CONST,
    SYMBOL_KIND_STRUCT,
    SYMBOL_KIND_UNION,
    SYMBOL_KIND_ENUM,
} SymbolKind;
typedef enum ScopeKind {
    SCOPE_FILE,
    SCOPE_BLOCK,
    SCOPE_FUNC_PROTO,
    SCOPE_FUNC_BODY,
} ScopeKind;
typedef struct Symbol {
    string name;
    Token *token;
    SymbolKind kind;
    _Bool is_defined;
} Symbol;
typedef struct Scope {
    ScopeKind kind;
    struct Scope *parent;
    List_Symbol *names;
    List_Symbol *tags;
} Scope;
typedef struct Parser {
    List_Token *tokens;
    ListNode *next;
    Token *current;
    size_t brace_depth;
    size_t paren_depth;
    Scope *current_scope;
    List_Scope *scopes;
    int error_count;
    _Bool panic_mode;
} Parser;
Parser *create_parser(List_Token *tokens);
TU *parse_parser(Parser *parser);
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
static Scope *create_scope(ScopeKind kind, Scope *parent) {
    Scope *scope = (Scope *)alloc_memory(sizeof(Scope), 1);
    scope->kind = kind;
    scope->parent = parent;
    scope->names = list_create(_Generic((Symbol *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
    scope->tags = list_create(_Generic((Symbol *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
    return scope;
}
static void push_new_scope(Parser *parser, ScopeKind kind) {
    Scope *scope = create_scope(kind, parser->current_scope);
    parser->current_scope = scope;
    list_append((parser->scopes), (void *)(scope), _Generic((scope), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
}
Parser *create_parser(List_Token *tokens) {
    Parser *parser = (Parser *)alloc_memory(sizeof(Parser), 1);
    parser->tokens = tokens;
    parser->next = tokens->head;
    parser->current = ((void *)0);
    parser->brace_depth = 0;
    parser->paren_depth = 0;
    parser->current_scope = ((void *)0);
    parser->scopes = list_create(_Generic((Scope *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
    parser->error_count = 0;
    parser->panic_mode = 0;
    push_new_scope(parser, SCOPE_FILE);
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
    assert(parser->next != ((void *)0));
    Token *t = ((Token *)((parser)->next->data));
    if (((t)->type == TOKEN_EOF) || parser->next->next == ((void *)0))
        return t;
    return (Token *)parser->next->next->data;
}
static _Bool check(Parser *parser, TokenType type, string value) {
    Token *t = ((Token *)((parser)->next->data));
    assert(t != ((void *)0));
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
    for (Scope *s = parser->current_scope; s != ((void *)0); s = s->parent) {
        for (List *sym__l = (s->names); sym__l != ((void *)0) && sym__l->head != ((void *)0); sym__l = ((void *)0))
            for (ListNode *sym__n = sym__l->head; sym__n != ((void *)0); sym__n = sym__n->next)
                for (Symbol *sym = (Symbol *)sym__n->data; sym != ((void *)0); sym = ((void *)0)) {
                    if (sym->name == name)
                        return sym->kind == SYMBOL_KIND_TYPEDEF;
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
static DirectDeclarator *get_function_declarator(Declarator *decl, DirectDeclarator *outer) {
    DirectDeclarator *inner = decl->direct_declarator;
    DirectDeclarator *last = ((void *)0);
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
    DirectDeclarator *nearest = outer;
    if (last != ((void *)0))
        nearest = last->decl_type == DECLARATOR_FUNC ? last : ((void *)0);
    else if (decl->pointer != ((void *)0))
        nearest = ((void *)0);
    if (inner != ((void *)0) && inner->decl_type == DECLARATOR_DECL)
        return get_function_declarator(inner->decl.declarator, nearest);
    return nearest;
}
static void add_name(Parser *parser, Token *id, SymbolKind kind) {
    for (List *symbol__l = (parser->current_scope->names); symbol__l != ((void *)0) && symbol__l->head != ((void *)0); symbol__l = ((void *)0))
        for (ListNode *symbol__n = symbol__l->head; symbol__n != ((void *)0); symbol__n = symbol__n->next)
            for (Symbol *symbol = (Symbol *)symbol__n->data; symbol != ((void *)0); symbol = ((void *)0)) {
                if (symbol->name == id->value) {
                    if ((kind == SYMBOL_KIND_TYPEDEF) != (symbol->kind == SYMBOL_KIND_TYPEDEF))
                        report_error(parser, (id), ("Redeclared as different kind of symbol"));
                    return;
                }
            }
    Symbol *symbol = (Symbol *)alloc_memory(sizeof(Symbol), 1);
    *symbol = (Symbol){.name = id->value, .token = id, .kind = kind};
    list_append((parser->current_scope->names), (void *)(symbol), _Generic((symbol), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
}
static Token *get_declarator_identifier(DirectDeclarator *decl) {
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
        assert(0);
    }
}
static _Bool has_typedef(List_DeclSpec *decl_specs) {
    for (List *spec__l = (decl_specs); spec__l != ((void *)0) && spec__l->head != ((void *)0); spec__l = ((void *)0))
        for (ListNode *spec__n = spec__l->head; spec__n != ((void *)0); spec__n = spec__n->next)
            for (DeclSpec *spec = (DeclSpec *)spec__n->data; spec != ((void *)0); spec = ((void *)0))
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
static AssignmentExpression *parse_assignment_expression(Parser *parser);
static TypeName *parse_type_name(Parser *parser);
static GenericAssociation *parse_generic_association(Parser *parser) {
    GenericAssociation *assoc = (GenericAssociation *)alloc_memory(sizeof(GenericAssociation), 1);
    assoc->token = ((Token *)((parser)->next->data));
    assoc->type_name = ((void *)0);
    if (!match(parser, TOKEN_KEYWORD, KEYWORD_DEFAULT))
        assoc->type_name = parse_type_name(parser);
    expect(parser, TOKEN_SYMBOL, SYMBOL_COLON, "Expected ':' in generic association");
    assoc->assignment_expr = parse_assignment_expression(parser);
    return assoc;
}
static List_AssignmentExpression *parse_expression(Parser *parser);
static PrimaryExpression *parse_primary_expression(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    PrimaryExpression *primary_expr = (PrimaryExpression *)alloc_memory(sizeof(PrimaryExpression), 1);
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
        primary_expr->primary.generic_selection.generic_assoc_list = list_create(_Generic((GenericAssociation *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
        do {
            list_append((primary_expr->primary.generic_selection.generic_assoc_list), (void *)(parse_generic_association(parser)), _Generic((parse_generic_association(parser)), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
        } while (match(parser, TOKEN_SYMBOL, SYMBOL_COMMA));
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after generic association list in '_Generic'");
    } else {
        report_error(parser, (t), ("Expected primary expression"));
        return ((void *)0);
    }
    return primary_expr;
}
static PostfixExpression *parse_postfix_suffix(Parser *parser, PostfixExpression *outer) {
    Token *t = ((Token *)((parser)->next->data));
    while (t->type == TOKEN_SYMBOL && (t->value == SYMBOL_L_BRACKET || t->value == SYMBOL_L_PARENTHESIS || t->value == SYMBOL_DOT || t->value == SYMBOL_ARROW || t->value == SYMBOL_INCREMENT || t->value == SYMBOL_DECREMENT)) {
        PostfixExpression *postfix_expr = (PostfixExpression *)alloc_memory(sizeof(PostfixExpression), 1);
        postfix_expr->token = t;
        if (match(parser, TOKEN_SYMBOL, SYMBOL_L_BRACKET)) {
            postfix_expr->expr_type = POSTFIX_ARRAY_ACCESS;
            postfix_expr->expr.array_access.postfix_expr = outer;
            postfix_expr->expr.array_access.index_expr = parse_expression(parser);
            expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACKET, "Expected ']' after array index expression");
        } else if (match(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS)) {
            postfix_expr->expr_type = POSTFIX_FUNC_CALL;
            postfix_expr->expr.func_call.postfix_expr = outer;
            postfix_expr->expr.func_call.args = list_create(_Generic((AssignmentExpression *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
            if (!check(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS)) {
                do {
                    list_append((postfix_expr->expr.func_call.args), (void *)(parse_assignment_expression(parser)), _Generic((parse_assignment_expression(parser)), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
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
static InitializerItem *parse_initializer_item(Parser *parser);
static PostfixExpression *parse_compound_literal(Parser *parser, TypeName *type_name) {
    Token *t = get(parser);
    PostfixExpression *compound_literal = (PostfixExpression *)alloc_memory(sizeof(PostfixExpression), 1);
    *compound_literal = (PostfixExpression){.token = t, .expr_type = POSTFIX_COMPOUND_LITERAL, .expr.compound_literal = { .type_name = type_name, .initializer_list = list_create(_Generic((InitializerItem *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol)) }};
    do {
        if (check(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE))
            break;
        list_append((compound_literal->expr.compound_literal.initializer_list), (void *)(parse_initializer_item(parser)), _Generic((parse_initializer_item(parser)), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
    } while (match(parser, TOKEN_SYMBOL, SYMBOL_COMMA));
    expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE, "Expected ',' or '}' in initializer list");
    if (((compound_literal->expr.compound_literal.initializer_list) == ((void *)0) || (compound_literal->expr.compound_literal.initializer_list)->head == ((void *)0)))
        report_warning(parser, (t), ("ISO C forbids empty initializer braces"));
    return parse_postfix_suffix(parser, compound_literal);
}
static PostfixExpression *parse_postfix_expression(Parser *parser) {
    if (check(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS) && is_type_start(parser, peek2(parser))) {
        get(parser);
        TypeName *type_name = parse_type_name(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after type name");
        if (check(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
            return parse_compound_literal(parser, type_name);
        } else {
            report_error(parser, (((Token *)((parser)->next->data))), ("Expected '{' after type name for compound literal"));
            return ((void *)0);
        }
    } else {
        PostfixExpression *postfix_expr = (PostfixExpression *)alloc_memory(sizeof(PostfixExpression), 1);
        postfix_expr->token = ((Token *)((parser)->next->data));
        postfix_expr->expr_type = POSTFIX_PRIMARY;
        postfix_expr->expr.primary_expr = parse_primary_expression(parser);
        return parse_postfix_suffix(parser, postfix_expr);
    }
}
static CastExpression *parse_cast_expression(Parser *parser);
static UnaryExpression *parse_unary_expression(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    UnaryExpression *unary_expr = (UnaryExpression *)alloc_memory(sizeof(UnaryExpression), 1);
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
                TypeName *type_name = unary_expr->expr.function_like.type_name;
                unary_expr->expr_type = UNARY_PREFIX;
                unary_expr->expr.prefix.op = KEYWORD_SIZEOF;
                unary_expr->expr.prefix.unary_expr = (UnaryExpression *)alloc_memory(sizeof(UnaryExpression), 1);
                *unary_expr->expr.prefix.unary_expr = (UnaryExpression){.token = tt, .expr_type = UNARY_POSTFIX, .expr.postfix = parse_compound_literal(parser, type_name)};
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
static CastExpression *parse_cast_expression(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    CastExpression *cast_expr = (CastExpression *)alloc_memory(sizeof(CastExpression), 1);
    cast_expr->token = t;
    if (check(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS) && is_type_start(parser, peek2(parser))) {
        t = get(parser);
        TypeName *type_name = parse_type_name(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ')' after type name");
        if (check(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
            PostfixExpression *postfix_expr = parse_compound_literal(parser, type_name);
            UnaryExpression *unary_expr = (UnaryExpression *)alloc_memory(sizeof(UnaryExpression), 1);
            *unary_expr = (UnaryExpression){.token = t, .expr.postfix = postfix_expr, .expr_type = UNARY_POSTFIX};
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
static BinaryExpression *parse_binary_expression(Parser *parser, int min_precedence) {
    BinaryExpression *left = (BinaryExpression *)alloc_memory(sizeof(BinaryExpression), 1);
    *left = (BinaryExpression){.token = ((Token *)((parser)->next->data)), .is_cast = 1, .expr.cast = parse_cast_expression(parser)};
    while (1) {
        Token *op = ((Token *)((parser)->next->data));
        int precedence = binary_operator_precedence(op);
        if (precedence <= min_precedence)
            break;
        get(parser);
        BinaryExpression *right = parse_binary_expression(parser, precedence);
        BinaryExpression *node = (BinaryExpression *)alloc_memory(sizeof(BinaryExpression), 1);
        *node = (BinaryExpression){.token = op, .is_cast = 0, .expr.binary = { .op = op->value, .left = left, .right = right }};
        left = node;
    }
    return left;
}
static ConditionalExpression *parse_conditional_expression(Parser *parser) {
    ConditionalExpression *cond_expr = (ConditionalExpression *)alloc_memory(sizeof(ConditionalExpression), 1);
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
static AssignmentExpression *parse_assignment_expression(Parser *parser) {
    ConditionalExpression *cond_expr = parse_conditional_expression(parser);
    AssignmentExpression *assign_expr = (AssignmentExpression *)alloc_memory(sizeof(AssignmentExpression), 1);
    Token *t = ((Token *)((parser)->next->data));
    if (t->type == TOKEN_SYMBOL && (t->value == SYMBOL_ASSIGN || t->value == SYMBOL_MUL_ASSIGN || t->value == SYMBOL_DIV_ASSIGN || t->value == SYMBOL_MOD_ASSIGN || t->value == SYMBOL_ADD_ASSIGN || t->value == SYMBOL_SUB_ASSIGN || t->value == SYMBOL_L_SHIFT_ASSIGN || t->value == SYMBOL_R_SHIFT_ASSIGN || t->value == SYMBOL_AND_ASSIGN || t->value == SYMBOL_XOR_ASSIGN || t->value == SYMBOL_OR_ASSIGN)) {
        t = get(parser);
        if (cond_expr->false_expr != ((void *)0) || cond_expr->true_expr != ((void *)0)) {
            report_error(parser, (cond_expr->token), ("Not an assignable expression"));
            return ((void *)0);
        }
        BinaryExpression *binary_expr = cond_expr->binary_expr;
        if (!binary_expr->is_cast) {
            report_error(parser, (binary_expr->token), ("Not an assignable expression"));
            return ((void *)0);
        }
        CastExpression *cast_expr = binary_expr->expr.cast;
        if (cast_expr->is_cast) {
            report_error(parser, (cast_expr->token), ("Not an assignable expression"));
            return ((void *)0);
        }
        UnaryExpression *unary_expr = cast_expr->expr.unary_expr;
        *assign_expr = (AssignmentExpression){.token = t, .is_conditional = 0, .expr.binary = { .left = unary_expr, .right = parse_assignment_expression(parser), .op = t->value }};
    } else
        *assign_expr = (AssignmentExpression){.token = cond_expr->token, .is_conditional = 1, .expr.cond_expr = cond_expr};
    return assign_expr;
}
static List_AssignmentExpression *parse_expression(Parser *parser) {
    List_AssignmentExpression *expr_list = list_create(_Generic((AssignmentExpression *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
    do {
        list_append((expr_list), (void *)(parse_assignment_expression(parser)), _Generic((parse_assignment_expression(parser)), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
    } while (match(parser, TOKEN_SYMBOL, SYMBOL_COMMA));
    return expr_list;
}
static VarDecl *parse_declaration(Parser *parser, FuncDecl **func_def);
static Statement *parse_statement(Parser *parser);
static List_DeclStmt *parse_compound_stmt(Parser *parser) {
    List_DeclStmt *decl_stmts = list_create(_Generic((DeclStmt *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
    Token *t = ((Token *)((parser)->next->data));
    while (!((t)->type == TOKEN_EOF) && !check(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE)) {
        size_t start_depth = parser->brace_depth;
        DeclStmt *decl_stmt = (DeclStmt *)alloc_memory(sizeof(DeclStmt), 1);
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
        list_append((decl_stmts), (void *)(decl_stmt), _Generic((decl_stmt), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
        synchronize(parser, t, start_depth, 0);
        t = ((Token *)((parser)->next->data));
    }
    return decl_stmts;
}
static SelectionStatement *parse_selection_stmt(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    SelectionStatement *selection = (SelectionStatement *)alloc_memory(sizeof(SelectionStatement), 1);
    selection->token = t;
    size_t paren_depth = parser->paren_depth;
    push_new_scope(parser, SCOPE_BLOCK);
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
        assert(0);
    (parser->current_scope = parser->current_scope->parent);
    return selection;
}
static IterationStatement *parse_iteration_stmt(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    IterationStatement *iteration = (IterationStatement *)alloc_memory(sizeof(IterationStatement), 1);
    iteration->token = t;
    size_t paren_depth = parser->paren_depth;
    push_new_scope(parser, SCOPE_BLOCK);
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
        assert(0);
    (parser->current_scope = parser->current_scope->parent);
    return iteration;
}
static JumpStatement *parse_jump_stmt(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    JumpStatement *jump = (JumpStatement *)alloc_memory(sizeof(JumpStatement), 1);
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
        assert(0);
    expect(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON, "Expected ';' after jump statement");
    return jump;
}
static Statement *parse_statement(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    Token *p = peek2(parser);
    Statement *stmt = (Statement *)alloc_memory(sizeof(Statement), 1);
    stmt->token = t;
    if (match(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
        push_new_scope(parser, SCOPE_BLOCK);
        stmt->stmt_type = STMT_COMPOUND;
        stmt->stmt.compound = parse_compound_stmt(parser);
        expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE, "Expected '}' to close compound statement");
        (parser->current_scope = parser->current_scope->parent);
    } else if (t->type == TOKEN_KEYWORD && (t->value == KEYWORD_CASE || t->value == KEYWORD_DEFAULT)) {
        stmt->stmt_type = STMT_LABELED;
        t = get(parser);
        stmt->stmt.label = (LabeledStatement *)alloc_memory(sizeof(LabeledStatement), 1);
        if (t->value == KEYWORD_CASE) {
            *(stmt->stmt.label) = (LabeledStatement){.token = t, .label_type = LABEL_CASE, .label.case_stmt = parse_conditional_expression(parser), .stmt = ((void *)0)};
            expect(parser, TOKEN_SYMBOL, SYMBOL_COLON, "Expected ':' after case");
        } else {
            *(stmt->stmt.label) = (LabeledStatement){.token = t, .label_type = LABEL_DEFAULT, .label.none = ((void *)0), .stmt = ((void *)0)};
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
        stmt->stmt.label = (LabeledStatement *)alloc_memory(sizeof(LabeledStatement), 1);
        *(stmt->stmt.label) = (LabeledStatement){.token = t, .label_type = LABEL_IDENTIFIER, .label.identifier = t, .stmt = ((void *)0)};
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
static TypeSpec *parse_type_specifier(Parser *parser);
static List_SpecifierQualifier *parse_spec_qual_list(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    List_SpecifierQualifier *spec_qual_list = list_create(_Generic((SpecifierQualifier *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
    _Bool seen_type = 0;
    while (1) {
        t = ((Token *)((parser)->next->data));
        SpecifierQualifier *spec_qual = (SpecifierQualifier *)alloc_memory(sizeof(SpecifierQualifier), 1);
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
        list_append((spec_qual_list), (void *)(spec_qual), _Generic((spec_qual), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
    }
    if (((spec_qual_list) == ((void *)0) || (spec_qual_list)->head == ((void *)0))) {
        report_error(parser, (t), ("Expected type qualifier or specifier"));
        return ((void *)0);
    }
    return spec_qual_list;
}
static StaticAssertDecl *parse_static_assert(Parser *parser, Token *t) {
    StaticAssertDecl *decl = (StaticAssertDecl *)alloc_memory(sizeof(StaticAssertDecl), 1);
    *decl = (StaticAssertDecl){.token = t, .expr = ((void *)0), .message = ((void *)0)};
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
static Declarator *parse_declarator(Parser *parser, _Bool *is_abs);
static StructDecl *parse_struct_decl(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    StructDecl *struct_decl = (StructDecl *)alloc_memory(sizeof(StructDecl), 1);
    struct_decl->token = t;
    struct_decl->is_static_assert_decl = 0;
    if (match(parser, TOKEN_KEYWORD, KEYWORD_STATIC_ASSERT)) {
        struct_decl->is_static_assert_decl = 1;
        struct_decl->decl.static_assert_decl = parse_static_assert(parser, t);
    } else {
        List_SpecifierQualifier *spec_qual_list = parse_spec_qual_list(parser);
        List_StructDeclarator *struct_declarators = ((void *)0);
        if (!check(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON)) {
            struct_declarators = list_create(_Generic((StructDeclarator *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
            do {
                t = ((Token *)((parser)->next->data));
                StructDeclarator *struct_declarator = (StructDeclarator *)alloc_memory(sizeof(StructDeclarator), 1);
                *struct_declarator = (StructDeclarator){.token = t, .declarator = ((void *)0), .constant_expr = ((void *)0)};
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
                list_append((struct_declarators), (void *)(struct_declarator), _Generic((struct_declarator), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
            } while (match(parser, TOKEN_SYMBOL, SYMBOL_COMMA));
        } else {
            _Bool has_struct_or_union = 0;
            for (List *spec_qual__l = (spec_qual_list); spec_qual__l != ((void *)0) && spec_qual__l->head != ((void *)0); spec_qual__l = ((void *)0))
                for (ListNode *spec_qual__n = spec_qual__l->head; spec_qual__n != ((void *)0); spec_qual__n = spec_qual__n->next)
                    for (SpecifierQualifier *spec_qual = (SpecifierQualifier *)spec_qual__n->data; spec_qual != ((void *)0); spec_qual = ((void *)0)) {
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
static TypeName *parse_type_name(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    TypeName *type_name = (TypeName *)alloc_memory(sizeof(TypeName), 1);
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
static List_DeclSpec *parse_declaration_specifiers(Parser *parser);
static List_ParamDecl *parse_parameter_declarations(Parser *parser, _Bool *is_variadic) {
    Token *t = ((Token *)((parser)->next->data));
    *is_variadic = 0;
    List_ParamDecl *param_decls = list_create(_Generic((ParamDecl *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
    if (match(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS))
        return param_decls;
    do {
        if (match(parser, TOKEN_SYMBOL, SYMBOL_ELLIPSIS)) {
            if (((param_decls) == ((void *)0) || (param_decls)->head == ((void *)0)))
                report_warning(parser, (t), ("ISO C requires a named parameter before '...'"));
            *is_variadic = 1;
            break;
        }
        ParamDecl *param_decl = (ParamDecl *)alloc_memory(sizeof(ParamDecl), 1);
        t = ((Token *)((parser)->next->data));
        *param_decl = (ParamDecl){.token = t, .decl_specs = parse_declaration_specifiers(parser), .decl = ((void *)0), .is_abs = 1};
        t = ((Token *)((parser)->next->data));
        if (t->type == TOKEN_IDENTIFIER || (t->type == TOKEN_SYMBOL && (t->value == SYMBOL_MUL || t->value == SYMBOL_L_PARENTHESIS || t->value == SYMBOL_L_BRACKET))) {
            param_decl->is_abs = 1;
            param_decl->decl = parse_declarator(parser, &param_decl->is_abs);
            if (!param_decl->is_abs)
                add_name(parser, get_declarator_identifier(param_decl->decl->direct_declarator), SYMBOL_KIND_VAR);
        }
        list_append((param_decls), (void *)(param_decl), _Generic((param_decl), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
    } while (match(parser, TOKEN_SYMBOL, SYMBOL_COMMA));
    expect(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS, "Expected ',' or ')' in parameter list");
    return param_decls;
}
static Pointer *parse_pointer(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    Pointer *pointer = (Pointer *)alloc_memory(sizeof(Pointer), 1);
    expect(parser, TOKEN_SYMBOL, SYMBOL_MUL, "Expected '*' in pointer declarator");
    *pointer = (Pointer){.token = t, .type_qualifiers = ((void *)0), .pointer = ((void *)0)};
    if (is_type_qualifier_start(parser, 1)) {
        pointer->type_qualifiers = list_create(_Generic((string)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
        while (is_type_qualifier_start(parser, 1)) {
            t = get(parser);
            list_append((pointer->type_qualifiers), (void *)(t->value), _Generic((t->value), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
        }
    }
    if (check(parser, TOKEN_SYMBOL, SYMBOL_MUL))
        pointer->pointer = parse_pointer(parser);
    return pointer;
}
static Designator *parse_designator(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    Designator *designator = (Designator *)alloc_memory(sizeof(Designator), 1);
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
        assert(0);
    return designator;
}
static Initializer *parse_initializer(Parser *parser);
static InitializerItem *parse_initializer_item(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    InitializerItem *item = (InitializerItem *)alloc_memory(sizeof(InitializerItem), 1);
    item->token = t;
    item->designation = ((void *)0);
    if (check(parser, TOKEN_SYMBOL, SYMBOL_DOT) || check(parser, TOKEN_SYMBOL, SYMBOL_L_BRACKET)) {
        item->designation = list_create(_Generic((Designator *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
        while (check(parser, TOKEN_SYMBOL, SYMBOL_DOT) || check(parser, TOKEN_SYMBOL, SYMBOL_L_BRACKET))
            list_append((item->designation), (void *)(parse_designator(parser)), _Generic((parse_designator(parser)), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
        expect(parser, TOKEN_SYMBOL, SYMBOL_ASSIGN, "Expected '=' after designator");
    }
    item->initializer = parse_initializer(parser);
    return item;
}
static Initializer *parse_initializer(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    Initializer *init = (Initializer *)alloc_memory(sizeof(Initializer), 1);
    init->token = t;
    if (match(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
        init->is_assignment_expr = 0;
        init->init.inits = list_create(_Generic((InitializerItem *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
        do {
            if (check(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE))
                break;
            list_append((init->init.inits), (void *)(parse_initializer_item(parser)), _Generic((parse_initializer_item(parser)), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
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
static TypeSpec *parse_type_specifier(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    TypeSpec *type = (TypeSpec *)alloc_memory(sizeof(TypeSpec), 1);
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
            List_StructDecl *members = ((void *)0);
            if (match(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
                members = list_create(_Generic((StructDecl *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
                while (1) {
                    t = ((Token *)((parser)->next->data));
                    size_t start_depth = parser->brace_depth;
                    if (is_type_start(parser, t) || (t->type == TOKEN_KEYWORD && t->value == KEYWORD_STATIC_ASSERT)) {
                        StructDecl *decl = parse_struct_decl(parser);
                        list_append((members), (void *)(decl), _Generic((decl), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
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
            List_Enumerator *enumerators = ((void *)0);
            if (match(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
                enumerators = list_create(_Generic((Enumerator *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
                while (1) {
                    t = ((Token *)((parser)->next->data));
                    if (t->type == TOKEN_IDENTIFIER) {
                        t = get(parser);
                        Enumerator *enumerator = (Enumerator *)alloc_memory(sizeof(Enumerator), 1);
                        *enumerator = (Enumerator){.token = t, .identifier = t, .constant_expr = ((void *)0)};
                        if (match(parser, TOKEN_SYMBOL, SYMBOL_ASSIGN))
                            enumerator->constant_expr = parse_conditional_expression(parser);
                        add_name(parser, t, SYMBOL_KIND_ENUM_CONST);
                        list_append((enumerators), (void *)(enumerator), _Generic((enumerator), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
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
            assert(0);
    } else if (t->type == TOKEN_IDENTIFIER && is_typedef_name(parser, t->value)) {
        t = get(parser);
        type->spec_type = TYPE_SPEC_TYPEDEF_NAME;
        type->spec.typedef_name = t;
    }
    return type;
}
static DirectDeclarator *parse_function_suffix(Parser *parser, DirectDeclarator *inner, Token *t) {
    _Bool is_variadic = 0;
    Scope *scope = create_scope(SCOPE_FUNC_PROTO, parser->current_scope);
    parser->current_scope = scope;
    list_append((parser->scopes), (void *)(scope), _Generic((scope), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
    List_ParamDecl *params = parse_parameter_declarations(parser, &is_variadic);
    parser->current_scope = scope->parent;
    DirectDeclarator *new = (DirectDeclarator *)alloc_memory(sizeof(DirectDeclarator), 1);
    *new = (DirectDeclarator){.token = t, .decl_type = DECLARATOR_FUNC, .decl.func.direct_declarator = inner, .decl.func.param_decls = params, .decl.func.is_variadic = is_variadic, .func_proto_scope = scope};
    return new;
}
static DirectDeclarator *parse_direct_declarator(Parser *parser, _Bool *is_abs) {
    Token *t = ((Token *)((parser)->next->data));
    DirectDeclarator *direct_decl = ((void *)0);
    _Bool allow_abs = *is_abs;
    *is_abs = 1;
    if (match(parser, TOKEN_IDENTIFIER, ((void *)0))) {
        direct_decl = (DirectDeclarator *)alloc_memory(sizeof(DirectDeclarator), 1);
        *direct_decl = (DirectDeclarator){.token = t, .decl_type = DECLARATOR_ID, .decl.identifier = t};
        *is_abs = 0;
    } else if (match(parser, TOKEN_SYMBOL, SYMBOL_L_PARENTHESIS)) {
        if (allow_abs && (check(parser, TOKEN_SYMBOL, SYMBOL_R_PARENTHESIS) || is_declaration_start(parser))) {
            direct_decl = parse_function_suffix(parser, ((void *)0), t);
        } else {
            _Bool is_inner_abs = allow_abs;
            direct_decl = (DirectDeclarator *)alloc_memory(sizeof(DirectDeclarator), 1);
            *direct_decl = (DirectDeclarator){.token = t, .decl_type = DECLARATOR_DECL, .decl.declarator = parse_declarator(parser, &is_inner_abs)};
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
                type_qualifiers = list_create(_Generic((string)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
                while (is_type_qualifier_start(parser, 1)) {
                    Token *tt = get(parser);
                    list_append((type_qualifiers), (void *)(tt->value), _Generic((tt->value), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
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
                    type_qualifiers = list_create(_Generic((string)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
                    while (is_type_qualifier_start(parser, 1)) {
                        Token *tt = get(parser);
                        list_append((type_qualifiers), (void *)(tt->value), _Generic((tt->value), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
                    }
                }
            }
            AssignmentExpression *expr = ((void *)0);
            if (has_static || (!has_star && !check(parser, TOKEN_SYMBOL, SYMBOL_R_BRACKET)))
                expr = parse_assignment_expression(parser);
            expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACKET, "Expected ']' to close array declarator");
            DirectDeclarator *new = (DirectDeclarator *)alloc_memory(sizeof(DirectDeclarator), 1);
            if (has_static || expr != ((void *)0))
                *new = (DirectDeclarator){.token = t, .decl_type = DECLARATOR_ARRAY, .decl.array.direct_declarator = direct_decl, .decl.array.assignment_expression = expr, .decl.array.is_static = has_static, .decl.array.type_qualifiers = type_qualifiers};
            else
                *new = (DirectDeclarator){.token = t, .decl_type = DECLARATOR_INCOMPLETE_ARRAY, .decl.incomplete_array.direct_declarator = direct_decl, .decl.incomplete_array.has_star = has_star, .decl.incomplete_array.type_qualifiers = type_qualifiers};
            direct_decl = new;
        } else
            break;
    }
    return direct_decl;
}
static Declarator *parse_declarator(Parser *parser, _Bool *is_abs) {
    Declarator *decl = (Declarator *)alloc_memory(sizeof(Declarator), 1);
    *decl = (Declarator){.token = ((Token *)((parser)->next->data)), .pointer = ((void *)0), .direct_declarator = ((void *)0)};
    if (check(parser, TOKEN_SYMBOL, SYMBOL_MUL))
        decl->pointer = parse_pointer(parser);
    decl->direct_declarator = parse_direct_declarator(parser, is_abs);
    return decl;
}
static List_DeclSpec *parse_declaration_specifiers(Parser *parser) {
    List_DeclSpec *decl_specs = list_create(_Generic((DeclSpec *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
    _Bool seen_type = 0;
    for (Token *t = ((Token *)((parser)->next->data)); !((t)->type == TOKEN_EOF); t = ((Token *)((parser)->next->data))) {
        DeclSpec *decl_spec = (DeclSpec *)alloc_memory(sizeof(DeclSpec), 1);
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
        list_append((decl_specs), (void *)(decl_spec), _Generic((decl_spec), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
    }
    if (((decl_specs) == ((void *)0) || (decl_specs)->head == ((void *)0))) {
        report_error(parser, (((Token *)((parser)->next->data))), ("Expected type name or declaration specifier"));
        return ((void *)0);
    }
    return decl_specs;
}
static VarDecl *parse_var_decl(Parser *parser, List_DeclSpec *decl_specs, Declarator *first, Token *t) {
    VarDecl *var_decl = (VarDecl *)alloc_memory(sizeof(VarDecl), 1);
    *var_decl = (VarDecl){.token = t, .is_static_assert_decl = 0, .decl.general_decl.decl_specs = decl_specs, .decl.general_decl.init_decls = list_create(_Generic((InitDecl *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol))};
    if (first == ((void *)0) && match(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON)) {
        if (decl_specs != ((void *)0)) {
            TypeSpec *tag = ((void *)0);
            DeclSpec *redundant = ((void *)0);
            Token *tt = ((void *)0);
            for (List *spec__l = (decl_specs); spec__l != ((void *)0) && spec__l->head != ((void *)0); spec__l = ((void *)0))
                for (ListNode *spec__n = spec__l->head; spec__n != ((void *)0); spec__n = spec__n->next)
                    for (DeclSpec *spec = (DeclSpec *)spec__n->data; spec != ((void *)0); spec = ((void *)0)) {
                        if (tt == ((void *)0))
                            tt = spec->token;
                        if (spec->specifier_type == SPEC_TYPE_SPEC) {
                            TypeSpec *type = spec->specifier.type;
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
    Declarator *decl = first;
    while (1) {
        Token *decl_t = ((Token *)((parser)->next->data));
        if (decl != ((void *)0)) {
            decl_t = decl->token;
            SymbolKind kind = has_typedef(decl_specs) ? SYMBOL_KIND_TYPEDEF : (get_function_declarator(decl, ((void *)0)) != ((void *)0) ? SYMBOL_KIND_FUNC : SYMBOL_KIND_VAR);
            add_name(parser, get_declarator_identifier(decl->direct_declarator), kind);
        }
        Initializer *init = ((void *)0);
        if (match(parser, TOKEN_SYMBOL, SYMBOL_ASSIGN))
            init = parse_initializer(parser);
        InitDecl *init_decl = (InitDecl *)alloc_memory(sizeof(InitDecl), 1);
        *init_decl = (InitDecl){.token = decl_t, .declarator = decl, .initializer = init};
        list_append((var_decl->decl.general_decl.init_decls), (void *)(init_decl), _Generic((init_decl), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
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
static VarDecl *parse_declaration(Parser *parser, FuncDecl **func_def) {
    Token *t = ((Token *)((parser)->next->data));
    if (match(parser, TOKEN_KEYWORD, KEYWORD_STATIC_ASSERT)) {
        VarDecl *var_decl = (VarDecl *)alloc_memory(sizeof(VarDecl), 1);
        *var_decl = (VarDecl){.token = t, .is_static_assert_decl = 1, .decl.static_assert_decl = parse_static_assert(parser, t)};
        return var_decl;
    }
    List_DeclSpec *decl_specs = parse_declaration_specifiers(parser);
    if (check(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON))
        return parse_var_decl(parser, decl_specs, ((void *)0), t);
    _Bool is_abs = 0;
    Declarator *decl = parse_declarator(parser, &is_abs);
    if (is_abs) {
        report_error(parser, (decl->token), ("Expected identifier in declarator"));
        return ((void *)0);
    }
    if (check(parser, TOKEN_SYMBOL, SYMBOL_L_BRACE)) {
        DirectDeclarator *func_declarator = get_function_declarator(decl, ((void *)0));
        if (func_declarator == ((void *)0))
            report_error(parser, (((Token *)((parser)->next->data))), ("Expected ';' after declaration (only a function declarator can have a body)"));
        else if (func_def == ((void *)0))
            report_error(parser, (((Token *)((parser)->next->data))), ("Function definition is not allowed here"));
        else {
            get(parser);
            add_name(parser, get_declarator_identifier(decl->direct_declarator), SYMBOL_KIND_FUNC);
            Scope *body = func_declarator->func_proto_scope;
            body->kind = SCOPE_FUNC_BODY;
            parser->current_scope = body;
            List_DeclStmt *compound = parse_compound_stmt(parser);
            expect(parser, TOKEN_SYMBOL, SYMBOL_R_BRACE, "Expected '}' at end of function body");
            parser->current_scope = body->parent;
            FuncDecl *func_decl = (FuncDecl *)alloc_memory(sizeof(FuncDecl), 1);
            *func_decl = (FuncDecl){.token = t, .decl_specs = decl_specs, .declarator = decl, .body = compound};
            *func_def = func_decl;
        }
        return ((void *)0);
    }
    return parse_var_decl(parser, decl_specs, decl, t);
}
TU *parse_parser(Parser *parser) {
    Token *t = ((Token *)((parser)->next->data));
    TU *tu = (TU *)alloc_memory(sizeof(TU), 1);
    tu->token = t;
    tu->filename = t->filename;
    tu->extern_decls = list_create(_Generic((ExternDecl *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
    while (!((t)->type == TOKEN_EOF)) {
        size_t start_depth = parser->brace_depth;
        if (match(parser, TOKEN_SYMBOL, SYMBOL_SEMICOLON))
            report_warning(parser, (t), ("Extra ';' outside of a function"));
        else {
            FuncDecl *func_decl = ((void *)0);
            VarDecl *var_decl = parse_declaration(parser, &func_decl);
            ExternDecl *extern_decl = ((void *)0);
            extern_decl = (ExternDecl *)alloc_memory(sizeof(ExternDecl), 1);
            if (func_decl != ((void *)0))
                *extern_decl = (ExternDecl){.token = t, .decl.func_decl = func_decl, .is_func_decl = 1};
            else if (var_decl != ((void *)0))
                *extern_decl = (ExternDecl){.token = t, .decl.var_decl = var_decl, .is_func_decl = 0};
            if (func_decl != ((void *)0) || var_decl != ((void *)0))
                list_append((tu->extern_decls), (void *)(extern_decl), _Generic((extern_decl), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
        }
        synchronize(parser, t, start_depth, 1);
        if (((Token *)((parser)->next->data)) == t)
            get(parser);
        t = ((Token *)((parser)->next->data));
    }
    return tu;
}
