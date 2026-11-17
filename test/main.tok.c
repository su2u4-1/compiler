typedef unsigned long long size_t;
typedef struct {
    long long a;
    long double b;
} max_align_t;
typedef unsigned long long uintmax_t;
typedef long long intmax_t;
typedef void* va_list;
void va_start(va_list ap, ...);
void va_end(va_list ap);
typedef struct {
    void* placeholder;
} FILE;
extern FILE* stderr;
FILE* fopen(const char* filename, const char* mode);
int fclose(FILE* stream);
int ferror(FILE* stream);
int fseek(FILE* stream, long offset, int origin);
long ftell(FILE* stream);
void rewind(FILE* stream);
size_t fread(void* buffer, size_t size, size_t count, FILE* stream);
int fputc(int c, FILE* stream);
int fputs(const char* str, FILE* stream);
int fprintf(FILE* stream, const char* format, ...);
int vsnprintf(char* buffer, size_t count, const char* format, va_list args);
void* malloc(size_t size);
void* calloc(size_t count, size_t size);
void free(void* p);
void abort(void);
double strtod(const char* str, char** end);
float strtof(const char* str, char** end);
long double strtold(const char* str, char** end);
size_t strlen(const char* str);
int strcmp(const char* a, const char* b);
int strncmp(const char* a, const char* b, size_t count);
int memcmp(const void* a, const void* b, size_t size);
void* memcpy(void* dst, const void* src, size_t size);
void* memmove(void* dst, const void* src, size_t size);
void* memset(void* dst, int value, size_t size);
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
typedef List* List_string;
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
    Token* token;
    union {
        AST_ConditionalExpression* cond_expr;
        struct {
            AST_UnaryExpression* left;
            AST_AssignmentExpression* right;
            string op;
        } binary;
    } expr;
    _Bool is_conditional;
};
struct AST_ConditionalExpression {
    Token* token;
    AST_BinaryExpression* binary_expr;
    List_AST_AssignmentExpression* true_expr;
    AST_ConditionalExpression* false_expr;
};
struct AST_BinaryExpression {
    Token* token;
    union {
        struct {
            string op;
            AST_BinaryExpression* left;
            AST_BinaryExpression* right;
        } binary;
        AST_CastExpression* cast;
    } expr;
    _Bool is_cast;
};
struct AST_CastExpression {
    Token* token;
    union {
        struct {
            AST_TypeName* type_name;
            AST_CastExpression* cast_expr;
        } cast;
        AST_UnaryExpression* unary_expr;
    } expr;
    _Bool is_cast;
};
struct AST_UnaryExpression {
    Token* token;
    union {
        struct {
            string op;
            AST_UnaryExpression* unary_expr;
        } prefix;
        struct {
            string op;
            AST_CastExpression* cast_expr;
        } unary_op;
        struct {
            AST_TypeName* type_name;
            _Bool is_sizeof;
        } function_like;
        AST_PostfixExpression* postfix;
    } expr;
    enum {
        UNARY_PREFIX,
        UNARY_UNARY_OP,
        UNARY_FUNCTION_LIKE,
        UNARY_POSTFIX,
    } expr_type;
};
struct AST_PostfixExpression {
    Token* token;
    union {
        AST_PrimaryExpression* primary_expr;
        struct {
            AST_TypeName* type_name;
            List_AST_InitializerItem* initializer_list;
        } compound_literal;
        struct {
            AST_PostfixExpression* postfix_expr;
            List_AST_AssignmentExpression* index_expr;
        } array_access;
        struct {
            AST_PostfixExpression* postfix_expr;
            List_AST_AssignmentExpression* args;
        } func_call;
        struct {
            AST_PostfixExpression* postfix_expr;
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
struct AST_PrimaryExpression {
    Token* token;
    union {
        Token* identifier;
        Token* integer_constant;
        Token* character_constant;
        Token* floating_constant;
        Token* string_literal;
        List_AST_AssignmentExpression* expr;
        struct {
            AST_AssignmentExpression* expr;
            List_AST_GenericAssociation* generic_assoc_list;
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
    Token* token;
    AST_TypeName* type_name;
    AST_AssignmentExpression* assignment_expr;
};
struct AST_DeclStmt {
    Token* token;
    union {
        AST_VarDecl* var_decl;
        AST_Statement* statement;
    } item;
    _Bool is_var_decl;
};
struct AST_LabeledStatement {
    Token* token;
    union {
        Token* identifier;
        AST_ConditionalExpression* case_stmt;
        void* none;
    } label;
    enum {
        LABEL_IDENTIFIER,
        LABEL_CASE,
        LABEL_DEFAULT,
    } label_type;
    AST_Statement* stmt;
};
struct AST_SelectionStatement {
    Token* token;
    union {
        struct {
            List_AST_AssignmentExpression* cond_expr;
            AST_Statement* then_stmt;
            AST_Statement* else_stmt;
        } if_stmt;
        struct {
            List_AST_AssignmentExpression* cond_expr;
            AST_Statement* stmt;
        } switch_stmt;
    } selection;
    _Bool is_switch;
};
struct AST_IterationStatement {
    Token* token;
    union {
        struct {
            List_AST_AssignmentExpression* expr;
            AST_Statement* stmt;
        } while_stmt;
        struct {
            union {
                List_AST_AssignmentExpression* init_expr;
                AST_VarDecl* init_decl;
            } init;
            _Bool is_init_decl;
            List_AST_AssignmentExpression* cond_expr;
            List_AST_AssignmentExpression* loop_expr;
            AST_Statement* stmt;
        } for_stmt;
    } loop;
    enum {
        LOOP_WHILE,
        LOOP_DO_WHILE,
        LOOP_FOR,
    } loop_type;
};
struct AST_JumpStatement {
    Token* token;
    union {
        Token* identifier;
        List_AST_AssignmentExpression* expr;
        void* none;
    } jump;
    enum {
        JUMP_GOTO,
        JUMP_CONTINUE,
        JUMP_BREAK,
        JUMP_RETURN,
    } jump_type;
};
struct AST_Statement {
    Token* token;
    union {
        AST_LabeledStatement* label;
        List_AST_DeclStmt* compound;
        List_AST_AssignmentExpression* expression;
        AST_SelectionStatement* selection;
        AST_IterationStatement* iteration;
        AST_JumpStatement* jump;
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
    Token* token;
    Token* identifier;
    AST_ConditionalExpression* constant_expr;
};
struct AST_StructDeclarator {
    Token* token;
    AST_Declarator* declarator;
    AST_ConditionalExpression* constant_expr;
};
struct AST_StructDecl {
    Token* token;
    union {
        struct {
            List_AST_SpecifierQualifier* spec_qual_list;
            List_AST_StructDeclarator* struct_declarators;
        } general_struct_decl;
        AST_StaticAssertDecl* static_assert_decl;
    } decl;
    _Bool is_static_assert_decl;
};
struct AST_SpecifierQualifier {
    Token* token;
    union {
        AST_TypeSpec* type_spec;
        string type_qualifier;
    } spec;
    _Bool is_type_spec;
};
struct AST_TypeName {
    Token* token;
    List_AST_SpecifierQualifier* spec_qual_list;
    AST_AbsDeclarator* abs_declarator;
};
struct AST_ParamDecl {
    Token* token;
    List_AST_DeclSpec* decl_specs;
    AST_Declarator* decl;
    _Bool is_abs;
};
struct AST_Pointer {
    Token* token;
    List_string type_qualifiers;
    AST_Pointer* pointer;
};
struct AST_Designator {
    Token* token;
    union {
        AST_ConditionalExpression* constant_expr;
        Token* identifier;
    } designator;
    _Bool is_constant_expr;
};
struct AST_InitializerItem {
    Token* token;
    List_AST_Designator* designation;
    AST_Initializer* initializer;
};
struct AST_Initializer {
    Token* token;
    union {
        AST_AssignmentExpression* assignment_expr;
        List_AST_InitializerItem* inits;
    } init;
    _Bool is_assignment_expr;
};
struct AST_TypeSpec {
    Token* token;
    union {
        string keyword_spec;
        AST_TypeName* atomic_spec;
        struct {
            _Bool is_struct;
            Token* identifier;
            List_AST_StructDecl* members;
        } struct_union_spec;
        struct {
            Token* identifier;
            List_AST_Enumerator* enumerators;
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
struct AST_DirectDeclarator {
    Token* token;
    union {
        Token* identifier;
        AST_Declarator* declarator;
        struct {
            AST_DirectDeclarator* direct_declarator;
            AST_AssignmentExpression* assignment_expression;
            List_string type_qualifiers;
            _Bool is_static;
        } array;
        struct {
            AST_DirectDeclarator* direct_declarator;
            List_AST_ParamDecl* param_decls;
            _Bool is_variadic;
        } func;
        struct {
            AST_DirectDeclarator* direct_declarator;
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
    AST_Scope* func_proto_scope;
};
struct AST_Declarator {
    Token* token;
    AST_Pointer* pointer;
    AST_DirectDeclarator* direct_declarator;
};
struct AST_DeclSpec {
    Token* token;
    union {
        string keyword;
        struct {
            union {
                AST_TypeName* type_name;
                AST_ConditionalExpression* constant_expression;
            } spec;
            _Bool is_type_name;
        } alignment;
        AST_TypeSpec* type;
    } specifier;
    enum {
        SPEC_KEYWORD,
        SPEC_ALIGNMENT,
        SPEC_TYPE_SPEC,
    } specifier_type;
};
struct AST_FuncDecl {
    Token* token;
    List_AST_DeclSpec* decl_specs;
    AST_Declarator* declarator;
    List_AST_DeclStmt* body;
};
struct AST_InitDecl {
    Token* token;
    AST_Declarator* declarator;
    AST_Initializer* initializer;
};
struct AST_StaticAssertDecl {
    Token* token;
    AST_ConditionalExpression* expr;
    Token* message;
};
struct AST_VarDecl {
    Token* token;
    union {
        struct {
            List_AST_DeclSpec* decl_specs;
            List_AST_InitDecl* init_decls;
        } general_decl;
        AST_StaticAssertDecl* static_assert_decl;
    } decl;
    _Bool is_static_assert_decl;
};
struct AST_ExternDecl {
    Token* token;
    union {
        AST_FuncDecl* func_decl;
        AST_VarDecl* var_decl;
    } decl;
    _Bool is_func_decl;
};
struct AST_TU {
    Token* token;
    string filename;
    List_AST_ExternDecl* extern_decls;
};
void output_pp_tokens(string filename, List_ppToken* tokens);
void print_pp_tokens(string filename, List_ppToken* tokens);
void output_tokens(string filename, List_Token* tokens);
void print_tokens(string filename, List_Token* tokens);
void output_ast(string filename, AST_TU* tu);
void print_ast(string filename, AST_TU* tu);
struct AST_Symbol {
    string name;
    _Bool is_typedef;
};
struct AST_Scope {
    AST_Scope* parent;
    List_AST_Symbol* names;
};
typedef struct Parser {
    List_Token* tokens;
    ListNode* next;
    Token* current;
    size_t brace_depth;
    size_t paren_depth;
    AST_Scope* current_scope;
    int error_count;
    _Bool panic_mode;
} Parser;
Parser* create_parser(List_Token* tokens);
AST_TU* parse_parser(Parser* parser);
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
            list_append((opt->source_path), (void*)(create_string(arg, strlen(arg))), _Generic((create_string(arg, strlen(arg))), string: LIST_TYPE_string, ppToken*: LIST_TYPE_ppToken, ppMacro*: LIST_TYPE_ppMacro, ppCondFrame*: LIST_TYPE_ppCondFrame, List_ppToken*: LIST_TYPE_List_ppToken, Token*: LIST_TYPE_Token, AST_ExternDecl*: LIST_TYPE_AST_ExternDecl, AST_DeclSpec*: LIST_TYPE_AST_DeclSpec, AST_InitDecl*: LIST_TYPE_AST_InitDecl, AST_ParamDecl*: LIST_TYPE_AST_ParamDecl, AST_StructDecl*: LIST_TYPE_AST_StructDecl, AST_Enumerator*: LIST_TYPE_AST_Enumerator, AST_InitializerItem*: LIST_TYPE_AST_InitializerItem, AST_Designator*: LIST_TYPE_AST_Designator, AST_SpecifierQualifier*: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator*: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt*: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression*: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation*: LIST_TYPE_AST_GenericAssociation, AST_TypeName*: LIST_TYPE_AST_TypeName, AST_Symbol*: LIST_TYPE_AST_Symbol )) ;
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
    AST_TU* tu = parse_parser(parser);
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
    *opt = (Options){.source_path = list_create(_Generic((string)0, string: LIST_TYPE_string, ppToken*: LIST_TYPE_ppToken, ppMacro*: LIST_TYPE_ppMacro, ppCondFrame*: LIST_TYPE_ppCondFrame, List_ppToken*: LIST_TYPE_List_ppToken, Token*: LIST_TYPE_Token, AST_ExternDecl*: LIST_TYPE_AST_ExternDecl, AST_DeclSpec*: LIST_TYPE_AST_DeclSpec, AST_InitDecl*: LIST_TYPE_AST_InitDecl, AST_ParamDecl*: LIST_TYPE_AST_ParamDecl, AST_StructDecl*: LIST_TYPE_AST_StructDecl, AST_Enumerator*: LIST_TYPE_AST_Enumerator, AST_InitializerItem*: LIST_TYPE_AST_InitializerItem, AST_Designator*: LIST_TYPE_AST_Designator, AST_SpecifierQualifier*: LIST_TYPE_AST_SpecifierQualifier, AST_StructDeclarator*: LIST_TYPE_AST_StructDeclarator, AST_DeclStmt*: LIST_TYPE_AST_DeclStmt, AST_AssignmentExpression*: LIST_TYPE_AST_AssignmentExpression, AST_GenericAssociation*: LIST_TYPE_AST_GenericAssociation, AST_TypeName*: LIST_TYPE_AST_TypeName, AST_Symbol*: LIST_TYPE_AST_Symbol )) , .output = ((void*)0) , .output_path = ((void*)0) , .p = 0 , .pc = 0 , .t = 0 , .tc = 0 , .a = 0 , .ac = 0 };
    if (!parse_args(argc, argv, opt)) {
        fprintf(stderr, "Usage: %s <source_files> [-o <output_file>] [-I<dir>...] [-p|-pc|-t|-tc|-a|-ac]...\n", argv[0]);
        free_all_memory();
        return 1;
    }
    int ret = run(opt);
    free_all_memory();
    return ret;
}
