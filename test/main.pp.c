typedef unsigned long long size_t;
typedef struct {
    long long a;
    long double b;
} max_align_t;
typedef unsigned long long uintmax_t;
typedef long long intmax_t;
typedef struct {
    void* placeholder;
} FILE;
typedef char* string;
typedef void* ptr;
void init(void);
string get_source(string path);
string string_splice(string format, ...);
typedef struct MemoryBlock MemoryBlock;
struct MemoryBlock {
    size_t size;
    size_t used;
    char* data;
    MemoryBlock* next;
};
typedef struct StringNode StringNode;
struct StringNode {
    size_t size;
    size_t hash;
    StringNode* next;
    string value;
};
typedef struct {
    StringNode** buckets;
    size_t capacity;
    size_t count;
} StringTable;
extern MemoryBlock* string_memory;
extern MemoryBlock* struct_memory;
void free_all_memory(void);
string create_string(const char* str, size_t len);
ptr alloc_memory(size_t size, _Bool is_struct);
typedef struct ListNode ListNode;
struct ListNode {
    void* data;
    ListNode* next;
};
typedef struct List {
    ListNode* head;
    ListNode* tail;
    int type_id;
} List;
List* list_create(int type_id);
int list_append(List* self, void* item, int type_id);
void* list_pop_front(List* self, int type_id);
void* list_pop_back(List* self, int type_id);
void* list_peek_front(List* self, int type_id);
void* list_peek_back(List* self, int type_id);
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
typedef List* List_string;
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
IntLiteral parse_int_digits(const char* s);
EscapeResult decode_literal_char(const char* s, size_t* pos, unsigned int* value);
const char* escape_message(EscapeResult result);
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
typedef struct Path {
    string root;
    string dir;
    string filename;
    string extension;
    string str;
    _Bool rooted;
    _Bool normalized;
} Path;
Path* create_path(string path);
Path* path_join(const Path* a, const Path* b);
Path* path_change_ext(const Path* p, string ext);
Path* path_change_filename(const Path* p, string name);
Path* path_absolute(const Path* p);
string path_str(const Path* p);
string path_dirname(const Path* p);
string path_root_str(const Path* p);
string path_filename(const Path* p);
string path_extension(const Path* p);
_Bool path_is_absolute(const Path* p);
_Bool path_equal(const Path* a, const Path* b);
_Bool path_exists(const Path* p);
_Bool path_is_dir(const Path* p);
void add_include_dir(string dir);
string find_file(string name, _Bool is_system, string current_file);
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
            char* data;
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
List_Token* pp_to_tokens(List_ppToken* pp_tokens);
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
    Token* token;
    union {
        ConditionalExpression* cond_expr;
        struct {
            UnaryExpression* left;
            AssignmentExpression* right;
            string op;
        } binary;
    } expr;
    _Bool is_conditional;
};
struct ConditionalExpression {
    Token* token;
    BinaryExpression* binary_expr;
    List_AssignmentExpression* true_expr;
    ConditionalExpression* false_expr;
};
struct BinaryExpression {
    Token* token;
    union {
        struct {
            string op;
            BinaryExpression* left;
            BinaryExpression* right;
        } binary;
        CastExpression* cast;
    } expr;
    _Bool is_cast;
};
struct CastExpression {
    Token* token;
    union {
        struct {
            TypeName* type_name;
            CastExpression* cast_expr;
        } cast;
        UnaryExpression* unary_expr;
    } expr;
    _Bool is_cast;
};
struct UnaryExpression {
    Token* token;
    union {
        struct {
            string op;
            UnaryExpression* unary_expr;
        } prefix;
        struct {
            string op;
            CastExpression* cast_expr;
        } unary_op;
        struct {
            TypeName* type_name;
            _Bool is_sizeof;
        } function_like;
        PostfixExpression* postfix;
    } expr;
    enum {
        UNARY_PREFIX,
        UNARY_UNARY_OP,
        UNARY_FUNCTION_LIKE,
        UNARY_POSTFIX,
    } expr_type;
};
struct PostfixExpression {
    Token* token;
    union {
        PrimaryExpression* primary_expr;
        struct {
            TypeName* type_name;
            List_InitializerItem* initializer_list;
        } compound_literal;
        struct {
            PostfixExpression* postfix_expr;
            List_AssignmentExpression* index_expr;
        } array_access;
        struct {
            PostfixExpression* postfix_expr;
            List_AssignmentExpression* args;
        } func_call;
        struct {
            PostfixExpression* postfix_expr;
            Token* identifier;
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
    Token* token;
    union {
        Token* identifier;
        Token* integer_constant;
        Token* character_constant;
        Token* floating_constant;
        Token* string_literal;
        List_AssignmentExpression* expr;
        struct {
            AssignmentExpression* expr;
            List_GenericAssociation* generic_assoc_list;
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
    Token* token;
    TypeName* type_name;
    AssignmentExpression* assignment_expr;
};
struct DeclStmt {
    Token* token;
    union {
        VarDecl* var_decl;
        Statement* statement;
    } item;
    _Bool is_var_decl;
};
struct LabeledStatement {
    Token* token;
    union {
        Token* identifier;
        ConditionalExpression* case_stmt;
        void* none;
    } label;
    enum {
        LABEL_IDENTIFIER,
        LABEL_CASE,
        LABEL_DEFAULT,
    } label_type;
    Statement* stmt;
};
struct SelectionStatement {
    Token* token;
    union {
        struct {
            List_AssignmentExpression* cond_expr;
            Statement* then_stmt;
            Statement* else_stmt;
        } if_stmt;
        struct {
            List_AssignmentExpression* cond_expr;
            Statement* stmt;
        } switch_stmt;
    } selection;
    _Bool is_switch;
};
struct IterationStatement {
    Token* token;
    union {
        struct {
            List_AssignmentExpression* expr;
            Statement* stmt;
        } while_stmt;
        struct {
            union {
                List_AssignmentExpression* init_expr;
                VarDecl* init_decl;
            } init;
            _Bool is_init_decl;
            List_AssignmentExpression* cond_expr;
            List_AssignmentExpression* loop_expr;
            Statement* stmt;
        } for_stmt;
    } loop;
    enum {
        LOOP_WHILE,
        LOOP_DO_WHILE,
        LOOP_FOR,
    } loop_type;
};
struct JumpStatement {
    Token* token;
    union {
        Token* identifier;
        List_AssignmentExpression* expr;
        void* none;
    } jump;
    enum {
        JUMP_GOTO,
        JUMP_CONTINUE,
        JUMP_BREAK,
        JUMP_RETURN,
    } jump_type;
};
struct Statement {
    Token* token;
    union {
        LabeledStatement* label;
        List_DeclStmt* compound;
        List_AssignmentExpression* expression;
        SelectionStatement* selection;
        IterationStatement* iteration;
        JumpStatement* jump;
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
    Token* token;
    Token* identifier;
    ConditionalExpression* constant_expr;
};
struct StructDeclarator {
    Token* token;
    Declarator* declarator;
    ConditionalExpression* constant_expr;
};
struct StructDecl {
    Token* token;
    union {
        struct {
            List_SpecifierQualifier* spec_qual_list;
            List_StructDeclarator* struct_declarators;
        } general_struct_decl;
        StaticAssertDecl* static_assert_decl;
    } decl;
    _Bool is_static_assert_decl;
};
struct SpecifierQualifier {
    Token* token;
    union {
        TypeSpec* type_spec;
        string type_qualifier;
    } spec;
    _Bool is_type_spec;
};
struct TypeName {
    Token* token;
    List_SpecifierQualifier* spec_qual_list;
    AbsDeclarator* abs_declarator;
};
struct ParamDecl {
    Token* token;
    List_DeclSpec* decl_specs;
    Declarator* decl;
    _Bool is_abs;
};
struct Pointer {
    Token* token;
    List_string type_qualifiers;
    Pointer* pointer;
};
struct Designator {
    Token* token;
    union {
        ConditionalExpression* constant_expr;
        Token* identifier;
    } designator;
    _Bool is_constant_expr;
};
struct InitializerItem {
    Token* token;
    List_Designator* designation;
    Initializer* initializer;
};
struct Initializer {
    Token* token;
    union {
        AssignmentExpression* assignment_expr;
        List_InitializerItem* inits;
    } init;
    _Bool is_assignment_expr;
};
struct TypeSpec {
    Token* token;
    union {
        string keyword_spec;
        TypeName* atomic_spec;
        struct {
            _Bool is_struct;
            Token* identifier;
            List_StructDecl* members;
        } struct_union_spec;
        struct {
            Token* identifier;
            List_Enumerator* enumerators;
        } enum_spec;
        Token* typedef_name;
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
    Token* token;
    union {
        Token* identifier;
        Declarator* declarator;
        struct {
            DirectDeclarator* direct_declarator;
            AssignmentExpression* assignment_expression;
            List_string type_qualifiers;
            _Bool is_static;
        } array;
        struct {
            DirectDeclarator* direct_declarator;
            List_ParamDecl* param_decls;
            _Bool is_variadic;
        } func;
        struct {
            DirectDeclarator* direct_declarator;
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
    Scope* func_proto_scope;
};
struct Declarator {
    Token* token;
    Pointer* pointer;
    DirectDeclarator* direct_declarator;
};
struct DeclSpec {
    Token* token;
    union {
        string keyword;
        struct {
            union {
                TypeName* type_name;
                ConditionalExpression* constant_expression;
            } spec;
            _Bool is_type_name;
        } alignment;
        TypeSpec* type;
    } specifier;
    enum {
        SPEC_KEYWORD,
        SPEC_ALIGNMENT,
        SPEC_TYPE_SPEC,
    } specifier_type;
};
struct FuncDecl {
    Token* token;
    List_DeclSpec* decl_specs;
    Declarator* declarator;
    List_DeclStmt* body;
};
struct InitDecl {
    Token* token;
    Declarator* declarator;
    Initializer* initializer;
};
struct StaticAssertDecl {
    Token* token;
    ConditionalExpression* expr;
    Token* message;
};
struct VarDecl {
    Token* token;
    union {
        struct {
            List_DeclSpec* decl_specs;
            List_InitDecl* init_decls;
        } general_decl;
        StaticAssertDecl* static_assert_decl;
    } decl;
    _Bool is_static_assert_decl;
};
struct ExternDecl {
    Token* token;
    union {
        FuncDecl* func_decl;
        VarDecl* var_decl;
    } decl;
    _Bool is_func_decl;
};
struct TU {
    Token* token;
    string filename;
    List_ExternDecl* extern_decls;
};
void output_pp_tokens(string filename, List_ppToken* tokens);
void print_pp_tokens(string filename, List_ppToken* tokens);
void output_tokens(string filename, List_Token* tokens);
void print_tokens(string filename, List_Token* tokens);
void output_ast(string filename, TU* tu);
void print_ast(string filename, TU* tu);
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
    Token* token;
    SymbolKind kind;
    _Bool is_defined;
} Symbol;
typedef struct Scope {
    ScopeKind kind;
    struct Scope* parent;
    List_Symbol* names;
    List_Symbol* tags;
} Scope;
typedef struct Parser {
    List_Token* tokens;
    ListNode* next;
    Token* current;
    size_t brace_depth;
    size_t paren_depth;
    Scope* current_scope;
    List_Scope* scopes;
    int error_count;
    _Bool panic_mode;
} Parser;
Parser* create_parser(List_Token* tokens);
TU* parse_parser(Parser* parser);
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
    ppToken* expanded_from;
    ppTokenType type;
    _Bool space_before;
    _Bool at_line_start;
};
typedef struct ppLexer {
    string source_code;
    size_t length;
    size_t pos;
    string filename;
    List_ppToken* pp_tokens;
    size_t* line_map;
    size_t* column_map;
    int include_state;
    _Bool pending_space;
    _Bool line_start;
    _Bool output_error;
} ppLexer;
typedef struct ppCondFrame {
    ppToken* directive;
    _Bool active;
    _Bool taken;
    _Bool in_else;
} ppCondFrame;
typedef struct ppMacro {
    ppToken* name;
    List_ppToken* params;
    List_ppToken* body;
    _Bool is_variadic;
} ppMacro;
typedef struct ppContext {
    List_ppMacro* macros;
    List_ppCondFrame* cond_stack;
    List_ppToken* output;
    ListNode* current;
    ppLexer* lexer;
    int include_depth;
    _Bool in_directive;
} ppContext;
List_ppToken* preprocess(string filename, string source_code, _Bool * error_flag);
ppToken* create_pp_token(ppTokenType type, string value, ppLexer* lexer, size_t pos);
ppLexer* create_pp_lexer(string filename, string source_code);
_Bool pp_lexer(ppLexer* lexer);
_Bool expand_macro(ppContext* ctx, ppToken* name);
_Bool eval_conditional(ppContext* ctx, _Bool * eval_error);
ppToken* pp_peek(ppContext* ctx);
ppToken* pp_get(ppContext* ctx);
ppMacro* find_macro(ppContext* ctx, string name);
typedef struct Options {
    List_string source_path;
    string output;
    Path* output_path;
    _Bool p;
    _Bool pc;
    _Bool t;
    _Bool tc;
    _Bool a;
    _Bool ac;
} Options;
static _Bool parse_args(int argc, char* argv[], Options* opt) {
    for (int i = 1; i < argc; i++) {
        char* arg = argv[i];
        if (strcmp(arg, "-o") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "[Error] at <main>: Missing file name after '-o'\n");
                return 0 ;
            }
            if (opt->output != ((void*)0) ) {
                fprintf(stderr, "[Error] at <main>: Multiple '-o' options\n");
                return 0 ;
            }
            i++;
            opt->output = create_string(argv[i], strlen(argv[i]));
        } else if (strncmp(arg, "-I", 2) == 0) {
            char* dir = arg + 2;
            if (dir[0] == '\0') {
                if (i + 1 >= argc) {
                    fprintf(stderr, "[Error] at <main>: Missing directory after '-I'\n");
                    return 0 ;
                }
                dir = argv[++i];
            }
            add_include_dir(create_string(dir, strlen(dir)));
        } else if (arg[0] == '-') {
            if (strcmp(arg, "-p") == 0) opt->p = 1 ;
            else if (strcmp(arg, "-pc") == 0) opt->pc = 1 ;
            else if (strcmp(arg, "-t") == 0) opt->t = 1 ;
            else if (strcmp(arg, "-tc") == 0) opt->tc = 1 ;
            else if (strcmp(arg, "-a") == 0) opt->a = 1 ;
            else if (strcmp(arg, "-ac") == 0) opt->ac = 1 ;
            else {
                fprintf(stderr, "[Error] at <main>: Unknown option: %s\n", arg);
                return 0 ;
            }
        } else {
            list_append((opt->source_path), (void*)(create_string(arg, strlen(arg))), _Generic((create_string(arg, strlen(arg))), string: TYPE_string, ppToken*: TYPE_ppToken, ppMacro*: TYPE_ppMacro, ppCondFrame*: TYPE_ppCondFrame, List_ppToken*: TYPE_List_ppToken, Token*: TYPE_Token, ExternDecl*: TYPE_ExternDecl, DeclSpec*: TYPE_DeclSpec, InitDecl*: TYPE_InitDecl, ParamDecl*: TYPE_ParamDecl, StructDecl*: TYPE_StructDecl, Enumerator*: TYPE_Enumerator, InitializerItem*: TYPE_InitializerItem, Designator*: TYPE_Designator, SpecifierQualifier*: TYPE_SpecifierQualifier, StructDeclarator*: TYPE_StructDeclarator, DeclStmt*: TYPE_DeclStmt, AssignmentExpression*: TYPE_AssignmentExpression, GenericAssociation*: TYPE_GenericAssociation, TypeName*: TYPE_TypeName, Scope*: TYPE_Scope, Symbol*: TYPE_Symbol )) ;
        }
    }
    if (((opt->source_path) == ((void*)0) || (opt->source_path)->head == ((void*)0) )) {
        fprintf(stderr, "[Error] at <main>: No source file\n");
        return 0 ;
    }
    if (opt->output == ((void*)0) )
        opt->output = create_string("a.out", 5);
    opt->output_path = create_path(opt->output);
    return 1 ;
}
static _Bool compile(Options* opt, string source_path, _Bool multi) {
    Path* base = multi ? path_change_filename(opt->output_path, path_filename(create_path(source_path))) : opt->output_path;
    string source_code = get_source(source_path);
    if (source_code == ((void*)0) ) {
        fprintf(stderr, "[Error] at <main>: Failed to read source file: %s\n", source_path);
        return 0 ;
    }
    _Bool error_flag = 0 ;
    List_ppToken* pp_tokens = preprocess(source_path, source_code, &error_flag);
    if (error_flag) {
        fprintf(stderr, "[Error] %s: Preprocessing failed due to errors.\n", source_path);
        return 0 ;
    }
    if (opt->p) output_pp_tokens(path_str(path_change_ext(base, create_string(".pp", strlen(".pp")))), pp_tokens);
    if (opt->pc) print_pp_tokens(path_str(path_change_ext(base, create_string(".pp.c", strlen(".pp.c")))), pp_tokens);
    List_Token* tokens = pp_to_tokens(pp_tokens);
    if (opt->t) output_tokens(path_str(path_change_ext(base, create_string(".tok", strlen(".tok")))), tokens);
    if (opt->tc) print_tokens(path_str(path_change_ext(base, create_string(".tok.c", strlen(".tok.c")))), tokens);
    Parser* parser = create_parser(tokens);
    TU* tu = parse_parser(parser);
    if (parser->error_count > 0) {
        fprintf(stderr, "[Error] %s: Parsing failed with %d error(s).\n", source_path, parser->error_count);
        return 0 ;
    }
    if (opt->a) output_ast(path_str(path_change_ext(base, create_string(".ast", strlen(".ast")))), tu);
    if (opt->ac) print_ast(path_str(path_change_ext(base, create_string(".ast.c", strlen(".ast.c")))), tu);
    return 1 ;
}
static int run(Options* opt) {
    _Bool multi = opt->source_path->head != opt->source_path->tail;
    _Bool ok = 1 ;
    for (List* src__l = (opt->source_path); src__l != ((void*)0) && src__l->head != ((void*)0) ; src__l = ((void*)0) ) for (ListNode* src__n = src__l->head; src__n != ((void*)0) ; src__n = src__n->next) for (string src = (string)src__n->data; src != ((void*)0) ; src = ((void*)0) )
        ok &= compile(opt, src, multi);
    if (!ok)
        return 1;
    return 0;
}
int main(int argc, char* argv[]) {
    init();
    Options* opt = (Options*)alloc_memory(sizeof(Options), 1 ) ;
    *opt = (Options){.source_path = list_create(_Generic((string)0, string: TYPE_string, ppToken*: TYPE_ppToken, ppMacro*: TYPE_ppMacro, ppCondFrame*: TYPE_ppCondFrame, List_ppToken*: TYPE_List_ppToken, Token*: TYPE_Token, ExternDecl*: TYPE_ExternDecl, DeclSpec*: TYPE_DeclSpec, InitDecl*: TYPE_InitDecl, ParamDecl*: TYPE_ParamDecl, StructDecl*: TYPE_StructDecl, Enumerator*: TYPE_Enumerator, InitializerItem*: TYPE_InitializerItem, Designator*: TYPE_Designator, SpecifierQualifier*: TYPE_SpecifierQualifier, StructDeclarator*: TYPE_StructDeclarator, DeclStmt*: TYPE_DeclStmt, AssignmentExpression*: TYPE_AssignmentExpression, GenericAssociation*: TYPE_GenericAssociation, TypeName*: TYPE_TypeName, Scope*: TYPE_Scope, Symbol*: TYPE_Symbol )) , .output = ((void*)0) , .output_path = ((void*)0) , .p = 0 , .pc = 0 , .t = 0 , .tc = 0 , .a = 0 , .ac = 0 };
    if (!parse_args(argc, argv, opt)) {
        fprintf(stderr, "Usage: %s <source_files> [-o <output_file>] [-I<dir>...] [-p|-pc|-t|-tc|-a|-ac]...\n", argv[0]);
        free_all_memory();
        return 1;
    }
    int ret = run(opt);
    free_all_memory();
    return ret;
}
