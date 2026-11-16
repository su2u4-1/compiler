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
    string message;
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
static FILE* open_file(string filename) {
    FILE* file = fopen(filename, "w");
    if (file == ((void*)0) ) {
        fprintf(stderr, "[Error] at <output> Failed to open file: %s\n", filename);
        return ((void*)0) ;
    }
    return file;
}
static void write_value(FILE* out, string value) {
    if (value == ((void*)0) ) {
        fputs("(null)", out);
        return;
    }
    fputc('`', out);
    for (const char* p = value; *p != '\0'; ++p) {
        switch (*p) {
            case '\n': fputs("\\n", out); break;
            case '\t': fputs("\\t", out); break;
            case '\r': fputs("\\r", out); break;
            default: fputc(*p, out); break;
        }
    }
    fputc('`', out);
}
static void write_spacing(FILE* out, _Bool first, _Bool at_line_start, _Bool space_before, size_t column) {
    if (at_line_start) {
        if (!first) fputc('\n', out);
        for (size_t i = 1; i < column; ++i)
            fputc(' ', out);
    } else if (space_before && !first) {
        fputc(' ', out);
    }
}
void output_pp_tokens(string filename, List_ppToken* tokens) {
    FILE* out = open_file(filename);
    if (out == ((void*)0) ) return;
    for (List* token__l = (tokens); token__l != ((void*)0) && token__l->head != ((void*)0) ; token__l = ((void*)0) ) for (ListNode* token__n = token__l->head; token__n != ((void*)0) ; token__n = token__n->next) for (ppToken* token = (ppToken*)token__n->data; token != ((void*)0) ; token = ((void*)0) ) {
        switch (token->type) {
            case PP_EOF: fputs("(EOF, ", out); break;
            case PP_IDENTIFIER: fputs("(identifier, ", out); break;
            case PP_NUMBER: fputs("(number, ", out); break;
            case PP_STRING: fputs("(string, ", out); break;
            case PP_CHAR: fputs("(char, ", out); break;
            case PP_SYMBOL: fputs("(symbol, ", out); break;
            case PP_NEWLINE: fputs("(newline, ", out); break;
            case PP_HEADER_NAME: fputs("(header_name, ", out); break;
            case PP_PLACE_MARKER: fputs("(place_marker, ", out); break;
            case PP_OTHER: fputs("(other, ", out); break;
            default: fputs("(unknown, ", out); break;
        }
        fprintf(out, "%zu, %zu, ", token->line, token->column);
        write_value(out, token->value);
        fputs(")\n", out);
    }
    fclose(out);
}
void print_pp_tokens(string filename, List_ppToken* tokens) {
    FILE* out = open_file(filename);
    if (out == ((void*)0) ) return;
    _Bool first = 1 ;
    for (List* token__l = (tokens); token__l != ((void*)0) && token__l->head != ((void*)0) ; token__l = ((void*)0) ) for (ListNode* token__n = token__l->head; token__n != ((void*)0) ; token__n = token__n->next) for (ppToken* token = (ppToken*)token__n->data; token != ((void*)0) ; token = ((void*)0) ) {
        if (token->type == PP_EOF) break;
        if (token->type == PP_NEWLINE || token->type == PP_PLACE_MARKER || token->value == ((void*)0) ) continue;
        write_spacing(out, first, token->at_line_start, token->space_before, token->column);
        fputs(token->value, out);
        first = 0 ;
    }
    fputc('\n', out);
    fclose(out);
}
static void output_one_token(FILE* out, Token* token) {
    if (token == ((void*)0) ) {
        fputs("(null)", out);
        return;
    }
    switch (token->type) {
        case TOKEN_EOF: fputs("(EOF, ", out); break;
        case TOKEN_IDENTIFIER: fputs("(identifier, ", out); break;
        case TOKEN_INT: fputs("(integer, ", out); break;
        case TOKEN_FLOAT: fputs("(float, ", out); break;
        case TOKEN_STRING: fputs("(string, ", out); break;
        case TOKEN_CHAR: fputs("(char, ", out); break;
        case TOKEN_SYMBOL: fputs("(symbol, ", out); break;
        case TOKEN_KEYWORD: fputs("(keyword, ", out); break;
        case TOKEN_COMMENT: fputs("(comment, ", out); break;
        case TOKEN_SYNTAX_ERROR_NUMBER: fputs("(error number, ", out); break;
        case TOKEN_SYNTAX_ERROR_CHAR: fputs("(error char, ", out); break;
        case TOKEN_SYNTAX_ERROR_STRING: fputs("(error string, ", out); break;
        default: fputs("(unknown, ", out); break;
    }
    fprintf(out, "%zu, %zu, ", token->line, token->column);
    write_value(out, token->value);
    fputc(')', out);
}
void output_tokens(string filename, List_Token* tokens) {
    FILE* out = open_file(filename);
    if (out == ((void*)0) ) return;
    for (List* token__l = (tokens); token__l != ((void*)0) && token__l->head != ((void*)0) ; token__l = ((void*)0) ) for (ListNode* token__n = token__l->head; token__n != ((void*)0) ; token__n = token__n->next) for (Token* token = (Token*)token__n->data; token != ((void*)0) ; token = ((void*)0) ) {
        output_one_token(out, token);
        fputc('\n', out);
    }
    fclose(out);
}
void print_tokens(string filename, List_Token* tokens) {
    FILE* out = open_file(filename);
    if (out == ((void*)0) ) return;
    _Bool first = 1 ;
    for (List* token__l = (tokens); token__l != ((void*)0) && token__l->head != ((void*)0) ; token__l = ((void*)0) ) for (ListNode* token__n = token__l->head; token__n != ((void*)0) ; token__n = token__n->next) for (Token* token = (Token*)token__n->data; token != ((void*)0) ; token = ((void*)0) ) {
        if (token->type == TOKEN_EOF) break;
        if (token->value == ((void*)0) ) continue;
        write_spacing(out, first, token->at_line_start, token->space_before, token->column);
        fputs(token->value, out);
        first = 0 ;
    }
    fputc('\n', out);
    fclose(out);
}
static void output_assignment_expression(FILE* out, AssignmentExpression* node, size_t indent);
static void output_conditional_expression(FILE* out, ConditionalExpression* node, size_t indent);
static void output_binary_expression(FILE* out, BinaryExpression* node, size_t indent);
static void output_cast_expression(FILE* out, CastExpression* node, size_t indent);
static void output_unary_expression(FILE* out, UnaryExpression* node, size_t indent);
static void output_postfix_expression(FILE* out, PostfixExpression* node, size_t indent);
static void output_primary_expression(FILE* out, PrimaryExpression* node, size_t indent);
static void output_generic_association(FILE* out, GenericAssociation* node, size_t indent);
static void output_decl_stmt(FILE* out, DeclStmt* node, size_t indent);
static void output_statement(FILE* out, Statement* node, size_t indent);
static void output_struct_decl(FILE* out, StructDecl* node, size_t indent);
static void output_specifier_qualifier(FILE* out, SpecifierQualifier* node, size_t indent);
static void output_type_name(FILE* out, TypeName* node, size_t indent);
static void output_param_decl(FILE* out, ParamDecl* node, size_t indent);
static void output_pointer(FILE* out, Pointer* node, size_t indent);
static void output_initializer_item(FILE* out, InitializerItem* node, size_t indent);
static void output_initializer(FILE* out, Initializer* node, size_t indent);
static void output_type_spec(FILE* out, TypeSpec* node, size_t indent);
static void output_declarator(FILE* out, Declarator* node, size_t indent);
static void output_decl_spec(FILE* out, DeclSpec* node, size_t indent);
static void output_static_assert_decl(FILE* out, StaticAssertDecl* node, size_t indent);
static void output_var_decl(FILE* out, VarDecl* node, size_t indent);
static void output_assignment_expression(FILE* out, AssignmentExpression* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("AssignmentExpression"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fprintf(out, "is_conditional"": %s,\n", (node->is_conditional) ? "true" : "false"); } while (0) ;
    if (node->is_conditional) {
        do { output_conditional_expression(out, (node->expr.cond_expr), indent + (1)); fputs(",\n", out); } while (0) ;
    } else {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("binary: {\n", out); } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("op"": ", out); } while (0) ; write_value(out, (node->expr.binary.op)); fputs(",\n", out); } while (0) ;
        do { output_unary_expression(out, (node->expr.binary.left), indent + (2)); fputs(",\n", out); } while (0) ;
        do { output_assignment_expression(out, (node->expr.binary.right), indent + (2)); fputs(",\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    }
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_conditional_expression(FILE* out, ConditionalExpression* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("ConditionalExpression"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { output_binary_expression(out, (node->binary_expr), indent + (1)); fputs(",\n", out); } while (0) ;
    do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("true_expr"": [\n", out); } while (0) ; for (List* item___l = ((node->true_expr)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (AssignmentExpression* item_ = (AssignmentExpression*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_assignment_expression(out, (item_), indent + ((1) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
    do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("false_expr"": {\n", out); } while (0) ; do { output_conditional_expression(out, (node->false_expr), indent + ((1) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ; } while (0) ;
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_binary_expression(FILE* out, BinaryExpression* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("BinaryExpression"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fprintf(out, "is_cast"": %s,\n", (node->is_cast) ? "true" : "false"); } while (0) ;
    if (node->is_cast) {
        do { output_cast_expression(out, (node->expr.cast), indent + (1)); fputs(",\n", out); } while (0) ;
    } else {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("binary: {\n", out); } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("op"": ", out); } while (0) ; write_value(out, (node->expr.binary.op)); fputs(",\n", out); } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("left"": {\n", out); } while (0) ; do { output_binary_expression(out, (node->expr.binary.left), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ; } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("right"": {\n", out); } while (0) ; do { output_binary_expression(out, (node->expr.binary.right), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ; } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    }
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_cast_expression(FILE* out, CastExpression* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("CastExpression"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fprintf(out, "is_cast"": %s,\n", (node->is_cast) ? "true" : "false"); } while (0) ;
    if (node->is_cast) {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("cast: {\n", out); } while (0) ;
        do { output_type_name(out, (node->expr.cast.type_name), indent + (2)); fputs(",\n", out); } while (0) ;
        do { output_cast_expression(out, (node->expr.cast.cast_expr), indent + (2)); fputs(",\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    } else {
        do { output_unary_expression(out, (node->expr.unary_expr), indent + (1)); fputs(",\n", out); } while (0) ;
    }
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_unary_expression(FILE* out, UnaryExpression* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("UnaryExpression"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("expr_type: ", out); } while (0) ;
    switch (node->expr_type) {
        case UNARY_PREFIX: fputs("UNARY_PREFIX,\n", out); break;
        case UNARY_UNARY_OP: fputs("UNARY_UNARY_OP,\n", out); break;
        case UNARY_FUNCTION_LIKE: fputs("UNARY_FUNCTION_LIKE,\n", out); break;
        case UNARY_POSTFIX: fputs("UNARY_POSTFIX,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }
    if (node->expr_type == UNARY_PREFIX) {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("prefix: {\n", out); } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("op"": ", out); } while (0) ; write_value(out, (node->expr.prefix.op)); fputs(",\n", out); } while (0) ;
        do { output_unary_expression(out, (node->expr.prefix.unary_expr), indent + (2)); fputs(",\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    } else if (node->expr_type == UNARY_UNARY_OP) {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("unary_op: {\n", out); } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("op"": ", out); } while (0) ; write_value(out, (node->expr.unary_op.op)); fputs(",\n", out); } while (0) ;
        do { output_cast_expression(out, (node->expr.unary_op.cast_expr), indent + (2)); fputs(",\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    } else if (node->expr_type == UNARY_FUNCTION_LIKE) {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("function_like: {\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fprintf(out, "is_sizeof"": %s,\n", (node->expr.function_like.is_sizeof) ? "true" : "false"); } while (0) ;
        do { output_type_name(out, (node->expr.function_like.type_name), indent + (2)); fputs(",\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    } else if (node->expr_type == UNARY_POSTFIX) {
        do { output_postfix_expression(out, (node->expr.postfix), indent + (1)); fputs(",\n", out); } while (0) ;
    }
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_postfix_expression(FILE* out, PostfixExpression* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("PostfixExpression"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("expr_type: ", out); } while (0) ;
    switch (node->expr_type) {
        case POSTFIX_PRIMARY: fputs("POSTFIX_PRIMARY,\n", out); break;
        case POSTFIX_COMPOUND_LITERAL: fputs("POSTFIX_COMPOUND_LITERAL,\n", out); break;
        case POSTFIX_ARRAY_ACCESS: fputs("POSTFIX_ARRAY_ACCESS,\n", out); break;
        case POSTFIX_FUNC_CALL: fputs("POSTFIX_FUNC_CALL,\n", out); break;
        case POSTFIX_OP: fputs("POSTFIX_OP,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }
    if (node->expr_type == POSTFIX_PRIMARY) {
        do { output_primary_expression(out, (node->expr.primary_expr), indent + (1)); fputs(",\n", out); } while (0) ;
    } else if (node->expr_type == POSTFIX_COMPOUND_LITERAL) {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("compound_literal: {\n", out); } while (0) ;
        do { output_type_name(out, (node->expr.compound_literal.type_name), indent + (2)); fputs(",\n", out); } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("initializer_list"": [\n", out); } while (0) ; for (List* item___l = ((node->expr.compound_literal.initializer_list)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (InitializerItem* item_ = (InitializerItem*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_initializer_item(out, (item_), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    } else if (node->expr_type == POSTFIX_ARRAY_ACCESS) {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("array_access: {\n", out); } while (0) ;
        do { output_postfix_expression(out, (node->expr.array_access.postfix_expr), indent + (2)); fputs(",\n", out); } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("index_expr"": [\n", out); } while (0) ; for (List* item___l = ((node->expr.array_access.index_expr)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (AssignmentExpression* item_ = (AssignmentExpression*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_assignment_expression(out, (item_), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    } else if (node->expr_type == POSTFIX_FUNC_CALL) {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("func_call: {\n", out); } while (0) ;
        do { output_postfix_expression(out, (node->expr.func_call.postfix_expr), indent + (2)); fputs(",\n", out); } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("args"": [\n", out); } while (0) ; for (List* item___l = ((node->expr.func_call.args)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (AssignmentExpression* item_ = (AssignmentExpression*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_assignment_expression(out, (item_), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    } else if (node->expr_type == POSTFIX_OP) {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("postfix_op: {\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 2); ++i_) fputs("    ", out) ; fputs("op_type: ", out); } while (0) ;
        switch (node->expr.postfix_op.op_type) {
            case POSTFIX_MEMBER_ACCESS: fputs("POSTFIX_MEMBER_ACCESS,\n", out); break;
            case POSTFIX_MEMBER_ACCESS_PTR: fputs("POSTFIX_MEMBER_ACCESS_PTR,\n", out); break;
            case POSTFIX_INCREMENT: fputs("POSTFIX_INCREMENT,\n", out); break;
            case POSTFIX_DECREMENT: fputs("POSTFIX_DECREMENT,\n", out); break;
            default: fputs("unknown,\n", out); break;
        }
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("identifier"": ", out); } while (0) ; output_one_token(out, (node->expr.postfix_op.identifier)); fputs(",\n", out); } while (0) ;
        do { output_postfix_expression(out, (node->expr.postfix_op.postfix_expr), indent + (2)); fputs(",\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    }
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_primary_expression(FILE* out, PrimaryExpression* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("PrimaryExpression"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("primary_type: ", out); } while (0) ;
    switch (node->primary_type) {
        case PRIMARY_IDENTIFIER: fputs("PRIMARY_IDENTIFIER,\n", out); break;
        case PRIMARY_INTEGER_CONSTANT: fputs("PRIMARY_INTEGER_CONSTANT,\n", out); break;
        case PRIMARY_CHARACTER_CONSTANT: fputs("PRIMARY_CHARACTER_CONSTANT,\n", out); break;
        case PRIMARY_FLOATING_CONSTANT: fputs("PRIMARY_FLOATING_CONSTANT,\n", out); break;
        case PRIMARY_STRING_LITERAL: fputs("PRIMARY_STRING_LITERAL,\n", out); break;
        case PRIMARY_EXPRESSION: fputs("PRIMARY_EXPRESSION,\n", out); break;
        case PRIMARY_GENERIC_SELECTION: fputs("PRIMARY_GENERIC_SELECTION,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }
    switch (node->primary_type) {
        case PRIMARY_IDENTIFIER: do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("identifier"": ", out); } while (0) ; output_one_token(out, (node->primary.identifier)); fputs(",\n", out); } while (0) ; break;
        case PRIMARY_INTEGER_CONSTANT: do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("integer_constant"": ", out); } while (0) ; output_one_token(out, (node->primary.integer_constant)); fputs(",\n", out); } while (0) ; break;
        case PRIMARY_CHARACTER_CONSTANT: do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("character_constant"": ", out); } while (0) ; output_one_token(out, (node->primary.character_constant)); fputs(",\n", out); } while (0) ; break;
        case PRIMARY_FLOATING_CONSTANT: do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("floating_constant"": ", out); } while (0) ; output_one_token(out, (node->primary.floating_constant)); fputs(",\n", out); } while (0) ; break;
        case PRIMARY_STRING_LITERAL: do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("string_literal"": ", out); } while (0) ; output_one_token(out, (node->primary.string_literal)); fputs(",\n", out); } while (0) ; break;
        case PRIMARY_EXPRESSION:
            do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("expr"": [\n", out); } while (0) ; for (List* item___l = ((node->primary.expr)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (AssignmentExpression* item_ = (AssignmentExpression*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_assignment_expression(out, (item_), indent + ((1) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
            break;
        case PRIMARY_GENERIC_SELECTION:
            do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("generic_selection: {\n", out); } while (0) ;
            do { output_assignment_expression(out, (node->primary.generic_selection.expr), indent + (2)); fputs(",\n", out); } while (0) ;
            do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("generic_assoc_list"": [\n", out); } while (0) ; for (List* item___l = ((node->primary.generic_selection.generic_assoc_list)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (GenericAssociation* item_ = (GenericAssociation*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_generic_association(out, (item_), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
            do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
            break;
        default: break;
    }
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_generic_association(FILE* out, GenericAssociation* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("GenericAssociation"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    if (node->type_name == ((void*)0) )
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("type_name: default,\n", out); } while (0) ;
    else
        do { output_type_name(out, (node->type_name), indent + (1)); fputs(",\n", out); } while (0) ;
    do { output_assignment_expression(out, (node->assignment_expr), indent + (1)); fputs(",\n", out); } while (0) ;
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_decl_stmt(FILE* out, DeclStmt* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("DeclStmt"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fprintf(out, "is_var_decl"": %s,\n", (node->is_var_decl) ? "true" : "false"); } while (0) ;
    if (node->is_var_decl)
        do { output_var_decl(out, (node->item.var_decl), indent + (1)); fputs(",\n", out); } while (0) ;
    else
        do { output_statement(out, (node->item.statement), indent + (1)); fputs(",\n", out); } while (0) ;
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_labeled_statement(FILE* out, LabeledStatement* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("LabeledStatement"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("label_type: ", out); } while (0) ;
    switch (node->label_type) {
        case LABEL_IDENTIFIER: fputs("LABEL_IDENTIFIER,\n", out); break;
        case LABEL_CASE: fputs("LABEL_CASE,\n", out); break;
        case LABEL_DEFAULT: fputs("LABEL_DEFAULT,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }
    if (node->label_type == LABEL_IDENTIFIER)
        do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("identifier"": ", out); } while (0) ; output_one_token(out, (node->label.identifier)); fputs(",\n", out); } while (0) ;
    else if (node->label_type == LABEL_CASE)
        do { output_conditional_expression(out, (node->label.case_stmt), indent + (1)); fputs(",\n", out); } while (0) ;
    do { output_statement(out, (node->stmt), indent + (1)); fputs(",\n", out); } while (0) ;
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_selection_statement(FILE* out, SelectionStatement* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("SelectionStatement"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fprintf(out, "is_switch"": %s,\n", (node->is_switch) ? "true" : "false"); } while (0) ;
    if (node->is_switch) {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("switch_stmt: {\n", out); } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("cond_expr"": [\n", out); } while (0) ; for (List* item___l = ((node->selection.switch_stmt.cond_expr)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (AssignmentExpression* item_ = (AssignmentExpression*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_assignment_expression(out, (item_), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
        do { output_statement(out, (node->selection.switch_stmt.stmt), indent + (2)); fputs(",\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    } else {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("if_stmt: {\n", out); } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("cond_expr"": [\n", out); } while (0) ; for (List* item___l = ((node->selection.if_stmt.cond_expr)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (AssignmentExpression* item_ = (AssignmentExpression*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_assignment_expression(out, (item_), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("then_stmt"": {\n", out); } while (0) ; do { output_statement(out, (node->selection.if_stmt.then_stmt), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ; } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("else_stmt"": {\n", out); } while (0) ; do { output_statement(out, (node->selection.if_stmt.else_stmt), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ; } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    }
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_iteration_statement(FILE* out, IterationStatement* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("IterationStatement"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("loop_type: ", out); } while (0) ;
    switch (node->loop_type) {
        case LOOP_WHILE: fputs("LOOP_WHILE,\n", out); break;
        case LOOP_DO_WHILE: fputs("LOOP_DO_WHILE,\n", out); break;
        case LOOP_FOR: fputs("LOOP_FOR,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }
    if (node->loop_type == LOOP_WHILE || node->loop_type == LOOP_DO_WHILE) {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("while_stmt: {\n", out); } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("expr"": [\n", out); } while (0) ; for (List* item___l = ((node->loop.while_stmt.expr)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (AssignmentExpression* item_ = (AssignmentExpression*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_assignment_expression(out, (item_), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
        do { output_statement(out, (node->loop.while_stmt.stmt), indent + (2)); fputs(",\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    } else if (node->loop_type == LOOP_FOR) {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("for_stmt: {\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fprintf(out, "is_init_decl"": %s,\n", (node->loop.for_stmt.is_init_decl) ? "true" : "false"); } while (0) ;
        if (node->loop.for_stmt.is_init_decl)
            do { output_var_decl(out, (node->loop.for_stmt.init.init_decl), indent + (2)); fputs(",\n", out); } while (0) ;
        else
            do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("init_expr"": [\n", out); } while (0) ; for (List* item___l = ((node->loop.for_stmt.init.init_expr)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (AssignmentExpression* item_ = (AssignmentExpression*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_assignment_expression(out, (item_), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("cond_expr"": [\n", out); } while (0) ; for (List* item___l = ((node->loop.for_stmt.cond_expr)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (AssignmentExpression* item_ = (AssignmentExpression*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_assignment_expression(out, (item_), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("loop_expr"": [\n", out); } while (0) ; for (List* item___l = ((node->loop.for_stmt.loop_expr)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (AssignmentExpression* item_ = (AssignmentExpression*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_assignment_expression(out, (item_), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
        do { output_statement(out, (node->loop.for_stmt.stmt), indent + (2)); fputs(",\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    }
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_jump_statement(FILE* out, JumpStatement* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("JumpStatement"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("jump_type: ", out); } while (0) ;
    switch (node->jump_type) {
        case JUMP_GOTO: fputs("JUMP_GOTO,\n", out); break;
        case JUMP_CONTINUE: fputs("JUMP_CONTINUE,\n", out); break;
        case JUMP_BREAK: fputs("JUMP_BREAK,\n", out); break;
        case JUMP_RETURN: fputs("JUMP_RETURN,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }
    if (node->jump_type == JUMP_GOTO)
        do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("identifier"": ", out); } while (0) ; output_one_token(out, (node->jump.identifier)); fputs(",\n", out); } while (0) ;
    else if (node->jump_type == JUMP_RETURN)
        do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("expr"": [\n", out); } while (0) ; for (List* item___l = ((node->jump.expr)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (AssignmentExpression* item_ = (AssignmentExpression*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_assignment_expression(out, (item_), indent + ((1) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_statement(FILE* out, Statement* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("Statement"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("stmt_type: ", out); } while (0) ;
    switch (node->stmt_type) {
        case STMT_LABELED: fputs("STMT_LABELED,\n", out); break;
        case STMT_COMPOUND: fputs("STMT_COMPOUND,\n", out); break;
        case STMT_EXPRESSION: fputs("STMT_EXPRESSION,\n", out); break;
        case STMT_SELECTION: fputs("STMT_SELECTION,\n", out); break;
        case STMT_ITERATION: fputs("STMT_ITERATION,\n", out); break;
        case STMT_JUMP: fputs("STMT_JUMP,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }
    switch (node->stmt_type) {
        case STMT_LABELED: do { output_labeled_statement(out, (node->stmt.label), indent + (1)); fputs(",\n", out); } while (0) ; break;
        case STMT_COMPOUND: do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("compound"": [\n", out); } while (0) ; for (List* item___l = ((node->stmt.compound)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (DeclStmt* item_ = (DeclStmt*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_decl_stmt(out, (item_), indent + ((1) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ; break;
        case STMT_EXPRESSION:
            do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("expression"": [\n", out); } while (0) ; for (List* item___l = ((node->stmt.expression)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (AssignmentExpression* item_ = (AssignmentExpression*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_assignment_expression(out, (item_), indent + ((1) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
            break;
        case STMT_SELECTION: do { output_selection_statement(out, (node->stmt.selection), indent + (1)); fputs(",\n", out); } while (0) ; break;
        case STMT_ITERATION: do { output_iteration_statement(out, (node->stmt.iteration), indent + (1)); fputs(",\n", out); } while (0) ; break;
        case STMT_JUMP: do { output_jump_statement(out, (node->stmt.jump), indent + (1)); fputs(",\n", out); } while (0) ; break;
        default: break;
    }
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_enumerator(FILE* out, Enumerator* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("Enumerator"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("identifier"": ", out); } while (0) ; output_one_token(out, (node->identifier)); fputs(",\n", out); } while (0) ;
    do { output_conditional_expression(out, (node->constant_expr), indent + (1)); fputs(",\n", out); } while (0) ;
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_struct_declarator(FILE* out, StructDeclarator* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("StructDeclarator"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { output_declarator(out, (node->declarator), indent + (1)); fputs(",\n", out); } while (0) ;
    do { output_conditional_expression(out, (node->constant_expr), indent + (1)); fputs(",\n", out); } while (0) ;
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_struct_decl(FILE* out, StructDecl* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("StructDecl"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fprintf(out, "is_static_assert_decl"": %s,\n", (node->is_static_assert_decl) ? "true" : "false"); } while (0) ;
    if (node->is_static_assert_decl) {
        do { output_static_assert_decl(out, (node->decl.static_assert_decl), indent + (1)); fputs(",\n", out); } while (0) ;
    } else {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("general_struct_decl: {\n", out); } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("spec_qual_list"": [\n", out); } while (0) ; for (List* item___l = ((node->decl.general_struct_decl.spec_qual_list)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (SpecifierQualifier* item_ = (SpecifierQualifier*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_specifier_qualifier(out, (item_), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("struct_declarators"": [\n", out); } while (0) ; for (List* item___l = ((node->decl.general_struct_decl.struct_declarators)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (StructDeclarator* item_ = (StructDeclarator*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_struct_declarator(out, (item_), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    }
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_specifier_qualifier(FILE* out, SpecifierQualifier* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("SpecifierQualifier"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fprintf(out, "is_type_spec"": %s,\n", (node->is_type_spec) ? "true" : "false"); } while (0) ;
    if (node->is_type_spec)
        do { output_type_spec(out, (node->spec.type_spec), indent + (1)); fputs(",\n", out); } while (0) ;
    else
        do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("type_qualifier"": ", out); } while (0) ; write_value(out, (node->spec.type_qualifier)); fputs(",\n", out); } while (0) ;
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_type_name(FILE* out, TypeName* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("TypeName"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("spec_qual_list"": [\n", out); } while (0) ; for (List* item___l = ((node->spec_qual_list)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (SpecifierQualifier* item_ = (SpecifierQualifier*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_specifier_qualifier(out, (item_), indent + ((1) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
    do { output_declarator(out, (node->abs_declarator), indent + (1)); fputs(",\n", out); } while (0) ;
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_type_spec(FILE* out, TypeSpec* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("TypeSpec"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("spec_type: ", out); } while (0) ;
    switch (node->spec_type) {
        case TYPE_SPEC_KEYWORD: fputs("TYPE_SPEC_KEYWORD,\n", out); break;
        case TYPE_SPEC_ATOMIC: fputs("TYPE_SPEC_ATOMIC,\n", out); break;
        case TYPE_SPEC_STRUCT_UNION: fputs("TYPE_SPEC_STRUCT_UNION,\n", out); break;
        case TYPE_SPEC_ENUM: fputs("TYPE_SPEC_ENUM,\n", out); break;
        case TYPE_SPEC_TYPEDEF_NAME: fputs("TYPE_SPEC_TYPEDEF_NAME,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }
    if (node->spec_type == TYPE_SPEC_KEYWORD) {
        do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("keyword_spec"": ", out); } while (0) ; write_value(out, (node->spec.keyword_spec)); fputs(",\n", out); } while (0) ;
    } else if (node->spec_type == TYPE_SPEC_ATOMIC) {
        do { output_type_name(out, (node->spec.atomic_spec), indent + (1)); fputs(",\n", out); } while (0) ;
    } else if (node->spec_type == TYPE_SPEC_STRUCT_UNION) {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("struct_union_spec: {\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fprintf(out, "is_struct"": %s,\n", (node->spec.struct_union_spec.is_struct) ? "true" : "false"); } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("identifier"": ", out); } while (0) ; output_one_token(out, (node->spec.struct_union_spec.identifier)); fputs(",\n", out); } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("members"": [\n", out); } while (0) ; for (List* item___l = ((node->spec.struct_union_spec.members)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (StructDecl* item_ = (StructDecl*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_struct_decl(out, (item_), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    } else if (node->spec_type == TYPE_SPEC_ENUM) {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("enum_spec: {\n", out); } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("identifier"": ", out); } while (0) ; output_one_token(out, (node->spec.enum_spec.identifier)); fputs(",\n", out); } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("enumerators"": [\n", out); } while (0) ; for (List* item___l = ((node->spec.enum_spec.enumerators)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (Enumerator* item_ = (Enumerator*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_enumerator(out, (item_), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    } else if (node->spec_type == TYPE_SPEC_TYPEDEF_NAME) {
        do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("typedef_name"": ", out); } while (0) ; output_one_token(out, (node->spec.typedef_name)); fputs(",\n", out); } while (0) ;
    }
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_param_decl(FILE* out, ParamDecl* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("ParamDecl"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fprintf(out, "is_abs"": %s,\n", (node->is_abs) ? "true" : "false"); } while (0) ;
    do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("decl_specs"": [\n", out); } while (0) ; for (List* item___l = ((node->decl_specs)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (DeclSpec* item_ = (DeclSpec*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_decl_spec(out, (item_), indent + ((1) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
    do { output_declarator(out, (node->decl), indent + (1)); fputs(",\n", out); } while (0) ;
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_pointer(FILE* out, Pointer* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("Pointer"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("type_qualifiers"": [", out); } while (0) ; for (List* s___l = ((node->type_qualifiers)); s___l != ((void*)0) && s___l->head != ((void*)0) ; s___l = ((void*)0) ) for (ListNode* s___n = s___l->head; s___n != ((void*)0) ; s___n = s___n->next) for (string s_ = (string)s___n->data; s_ != ((void*)0) ; s_ = ((void*)0) ) { write_value(out, s_); fputs(", ", out); } fputs("],\n", out); } while (0) ;
    do { output_pointer(out, (node->pointer), indent + (1)); fputs(",\n", out); } while (0) ;
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_direct_declarator(FILE* out, DirectDeclarator* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("DirectDeclarator"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("decl_type: ", out); } while (0) ;
    switch (node->decl_type) {
        case DECLARATOR_ID: fputs("DECLARATOR_ID,\n", out); break;
        case DECLARATOR_DECL: fputs("DECLARATOR_DECL,\n", out); break;
        case DECLARATOR_ARRAY: fputs("DECLARATOR_ARRAY,\n", out); break;
        case DECLARATOR_FUNC: fputs("DECLARATOR_FUNC,\n", out); break;
        case DECLARATOR_INCOMPLETE_ARRAY: fputs("DECLARATOR_INCOMPLETE_ARRAY,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }
    if (node->decl_type == DECLARATOR_ID) {
        do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("identifier"": ", out); } while (0) ; output_one_token(out, (node->decl.identifier)); fputs(",\n", out); } while (0) ;
    } else if (node->decl_type == DECLARATOR_DECL) {
        do { output_declarator(out, (node->decl.declarator), indent + (1)); fputs(",\n", out); } while (0) ;
    } else if (node->decl_type == DECLARATOR_ARRAY) {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("array: {\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fprintf(out, "is_static"": %s,\n", (node->decl.array.is_static) ? "true" : "false"); } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("type_qualifiers"": [", out); } while (0) ; for (List* s___l = ((node->decl.array.type_qualifiers)); s___l != ((void*)0) && s___l->head != ((void*)0) ; s___l = ((void*)0) ) for (ListNode* s___n = s___l->head; s___n != ((void*)0) ; s___n = s___n->next) for (string s_ = (string)s___n->data; s_ != ((void*)0) ; s_ = ((void*)0) ) { write_value(out, s_); fputs(", ", out); } fputs("],\n", out); } while (0) ;
        do { output_assignment_expression(out, (node->decl.array.assignment_expression), indent + (2)); fputs(",\n", out); } while (0) ;
        do { output_direct_declarator(out, (node->decl.array.direct_declarator), indent + (2)); fputs(",\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    } else if (node->decl_type == DECLARATOR_FUNC) {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("func: {\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fprintf(out, "is_variadic"": %s,\n", (node->decl.func.is_variadic) ? "true" : "false"); } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("param_decls"": [\n", out); } while (0) ; for (List* item___l = ((node->decl.func.param_decls)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (ParamDecl* item_ = (ParamDecl*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_param_decl(out, (item_), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
        do { output_direct_declarator(out, (node->decl.func.direct_declarator), indent + (2)); fputs(",\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    } else if (node->decl_type == DECLARATOR_INCOMPLETE_ARRAY) {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("incomplete_array: {\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fprintf(out, "has_star"": %s,\n", (node->decl.incomplete_array.has_star) ? "true" : "false"); } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("type_qualifiers"": [", out); } while (0) ; for (List* s___l = ((node->decl.incomplete_array.type_qualifiers)); s___l != ((void*)0) && s___l->head != ((void*)0) ; s___l = ((void*)0) ) for (ListNode* s___n = s___l->head; s___n != ((void*)0) ; s___n = s___n->next) for (string s_ = (string)s___n->data; s_ != ((void*)0) ; s_ = ((void*)0) ) { write_value(out, s_); fputs(", ", out); } fputs("],\n", out); } while (0) ;
        do { output_direct_declarator(out, (node->decl.incomplete_array.direct_declarator), indent + (2)); fputs(",\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    }
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_declarator(FILE* out, Declarator* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("Declarator"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { output_pointer(out, (node->pointer), indent + (1)); fputs(",\n", out); } while (0) ;
    do { output_direct_declarator(out, (node->direct_declarator), indent + (1)); fputs(",\n", out); } while (0) ;
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_designator(FILE* out, Designator* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("Designator"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fprintf(out, "is_constant_expr"": %s,\n", (node->is_constant_expr) ? "true" : "false"); } while (0) ;
    if (node->is_constant_expr)
        do { output_conditional_expression(out, (node->designator.constant_expr), indent + (1)); fputs(",\n", out); } while (0) ;
    else
        do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("identifier"": ", out); } while (0) ; output_one_token(out, (node->designator.identifier)); fputs(",\n", out); } while (0) ;
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_initializer_item(FILE* out, InitializerItem* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("InitializerItem"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("designation"": [\n", out); } while (0) ; for (List* item___l = ((node->designation)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (Designator* item_ = (Designator*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_designator(out, (item_), indent + ((1) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
    do { output_initializer(out, (node->initializer), indent + (1)); fputs(",\n", out); } while (0) ;
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_initializer(FILE* out, Initializer* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("Initializer"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fprintf(out, "is_assignment_expr"": %s,\n", (node->is_assignment_expr) ? "true" : "false"); } while (0) ;
    if (node->is_assignment_expr)
        do { output_assignment_expression(out, (node->init.assignment_expr), indent + (1)); fputs(",\n", out); } while (0) ;
    else
        do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("inits"": [\n", out); } while (0) ; for (List* item___l = ((node->init.inits)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (InitializerItem* item_ = (InitializerItem*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_initializer_item(out, (item_), indent + ((1) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_decl_spec(FILE* out, DeclSpec* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("DeclSpec"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("specifier_type: ", out); } while (0) ;
    switch (node->specifier_type) {
        case SPEC_KEYWORD: fputs("SPEC_KEYWORD,\n", out); break;
        case SPEC_ALIGNMENT: fputs("SPEC_ALIGNMENT,\n", out); break;
        case SPEC_TYPE_SPEC: fputs("SPEC_TYPE_SPEC,\n", out); break;
        default: fputs("unknown,\n", out); break;
    }
    if (node->specifier_type == SPEC_KEYWORD) {
        do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("keyword"": ", out); } while (0) ; write_value(out, (node->specifier.keyword)); fputs(",\n", out); } while (0) ;
    } else if (node->specifier_type == SPEC_ALIGNMENT) {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("alignment: {\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fprintf(out, "is_type_name"": %s,\n", (node->specifier.alignment.is_type_name) ? "true" : "false"); } while (0) ;
        if (node->specifier.alignment.is_type_name)
            do { output_type_name(out, (node->specifier.alignment.spec.type_name), indent + (2)); fputs(",\n", out); } while (0) ;
        else
            do { output_conditional_expression(out, (node->specifier.alignment.spec.constant_expression), indent + (2)); fputs(",\n", out); } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    } else if (node->specifier_type == SPEC_TYPE_SPEC) {
        do { output_type_spec(out, (node->specifier.type), indent + (1)); fputs(",\n", out); } while (0) ;
    }
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_func(FILE* out, FuncDecl* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("FuncDecl"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("decl_specs"": [\n", out); } while (0) ; for (List* item___l = ((node->decl_specs)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (DeclSpec* item_ = (DeclSpec*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_decl_spec(out, (item_), indent + ((1) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
    do { output_declarator(out, (node->declarator), indent + (1)); fputs(",\n", out); } while (0) ;
    do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("body"": [\n", out); } while (0) ; for (List* item___l = ((node->body)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (DeclStmt* item_ = (DeclStmt*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_decl_stmt(out, (item_), indent + ((1) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_init_decl(FILE* out, InitDecl* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("InitDecl"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { output_declarator(out, (node->declarator), indent + (1)); fputs(",\n", out); } while (0) ;
    do { output_initializer(out, (node->initializer), indent + (1)); fputs(",\n", out); } while (0) ;
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_static_assert_decl(FILE* out, StaticAssertDecl* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("StaticAssertDecl"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { output_conditional_expression(out, (node->expr), indent + (1)); fputs(",\n", out); } while (0) ;
    do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("message"": ", out); } while (0) ; write_value(out, (node->message)); fputs(",\n", out); } while (0) ;
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_var_decl(FILE* out, VarDecl* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("VarDecl"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fprintf(out, "is_static_assert_decl"": %s,\n", (node->is_static_assert_decl) ? "true" : "false"); } while (0) ;
    if (node->is_static_assert_decl) {
        do { output_static_assert_decl(out, (node->decl.static_assert_decl), indent + (1)); fputs(",\n", out); } while (0) ;
    } else {
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("general_decl: {\n", out); } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("decl_specs"": [\n", out); } while (0) ; for (List* item___l = ((node->decl.general_decl.decl_specs)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (DeclSpec* item_ = (DeclSpec*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_decl_spec(out, (item_), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
        do { do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("init_decls"": [\n", out); } while (0) ; for (List* item___l = ((node->decl.general_decl.init_decls)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (InitDecl* item_ = (InitDecl*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_init_decl(out, (item_), indent + ((2) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (2)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
        do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("},\n", out); } while (0) ;
    }
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_extern_decl(FILE* out, ExternDecl* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("ExternDecl"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fprintf(out, "is_func_decl"": %s,\n", (node->is_func_decl) ? "true" : "false"); } while (0) ;
    if (node->is_func_decl)
        do { output_func(out, (node->decl.func_decl), indent + (1)); fputs(",\n", out); } while (0) ;
    else
        do { output_var_decl(out, (node->decl.var_decl), indent + (1)); fputs(",\n", out); } while (0) ;
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
static void output_tu(FILE* out, TU* node, size_t indent) {
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("TU"": {\n", out); } while (0) ; if (node == ((void*)0) ) { do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("(null)\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ; return; } do { for (size_t i_ = 0; i_ < (indent + 1); ++i_) fputs("    ", out) ; fputs("token: ", out); } while (0) ; output_one_token(out, node->token); fputs(",\n", out) ;
    do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("filename"": ", out); } while (0) ; write_value(out, (node->filename)); fputs(",\n", out); } while (0) ;
    do { do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("extern_decls"": [\n", out); } while (0) ; for (List* item___l = ((node->extern_decls)); item___l != ((void*)0) && item___l->head != ((void*)0) ; item___l = ((void*)0) ) for (ListNode* item___n = item___l->head; item___n != ((void*)0) ; item___n = item___n->next) for (ExternDecl* item_ = (ExternDecl*)item___n->data; item_ != ((void*)0) ; item_ = ((void*)0) ) do { output_extern_decl(out, (item_), indent + ((1) + 1)); fputs(",\n", out); } while (0) ; do { for (size_t i_ = 0; i_ < (indent + (1)); ++i_) fputs("    ", out) ; fputs("],\n", out); } while (0) ; } while (0) ;
    do { for (size_t i_ = 0; i_ < (indent); ++i_) fputs("    ", out) ; fputs("}", out); } while (0) ;
}
void output_ast(string filename, TU* tu) {
    FILE* out = open_file(filename);
    if (out == ((void*)0) ) return;
    output_tu(out, tu, 0);
    fputc('\n', out);
    fclose(out);
}
void print_ast(string filename, TU* tu) {
    FILE* out = open_file(filename);
    if (out == ((void*)0) ) return;
    fputs("not complete implemented yet\n", out);
    fclose(out);
}
