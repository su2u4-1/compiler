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
static _Bool has_error = 0;
static void track_include(ppLexer *lx, ppToken *t) {
    if (t->type == PP_SYMBOL && t->value == SYMBOL_HASH && t->at_line_start)
        lx->include_state = 1;
    else if (lx->include_state == 1 && t->type == PP_IDENTIFIER && t->value == P_INCLUDE)
        lx->include_state = 2;
    else
        lx->include_state = 0;
}
static void add_pp_token(ppLexer *lexer, ppTokenType type, string value, size_t pos) {
    ppToken *t = create_pp_token(type, value, lexer, pos);
    t->space_before = lexer->pending_space;
    t->at_line_start = lexer->line_start;
    track_include(lexer, t);
    list_append((lexer->pp_tokens), (void *)(t), _Generic((t), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
    lexer->pending_space = 0;
    lexer->line_start = (type == PP_NEWLINE);
}
ppToken *create_pp_token(ppTokenType type, string value, ppLexer *lexer, size_t pos) {
    ppToken *t = (ppToken *)alloc_memory(sizeof(ppToken), 1);
    t->type = type;
    t->value = value;
    t->line = ((pos >= lexer->length) ? lexer->line_map[lexer->length] : lexer->line_map[pos]);
    t->column = ((pos >= lexer->length) ? lexer->column_map[lexer->length] : lexer->column_map[pos]);
    t->filename = lexer->filename;
    t->space_before = 0;
    t->at_line_start = 0;
    t->hideset = ((void *)0);
    t->expanded_from = ((void *)0);
    return t;
}
static void normalize(ppLexer *lexer, string source_code) {
    const string src = source_code;
    size_t source_len = strlen(source_code);
    string buffer = (string)alloc_memory(source_len + 2, 0);
    lexer->line_map = alloc_memory(sizeof(size_t) * (source_len + 2), 1);
    lexer->column_map = alloc_memory(sizeof(size_t) * (source_len + 2), 1);
    size_t size = 0;
    size_t line = 1, column = 1;
    for (size_t i = 0; i < source_len;) {
        char c = src[i];
        if (c == '\r') {
            if (i + 1 < source_len && src[i + 1] == '\n')
                i++;
            c = '\n';
        }
        if (c == '\\') {
            size_t j = i + 1;
            _Bool has_space = 0;
            while (j < source_len && (src[j] == ' ' || src[j] == '\t')) {
                j++;
                has_space = 1;
            }
            char n = (j < source_len) ? src[j] : '\0';
            _Bool newline = 0;
            if (n == '\n') {
                j++;
                newline = 1;
            } else if (n == '\r') {
                j++;
                if (j < source_len && src[j] == '\n')
                    j++;
                newline = 1;
            }
            if (newline) {
                if (has_space)
                    fprintf(stderr, "[Syntax Warning] at %s:%zu:%zu: Backslash and newline separated by space\n", lexer->filename, line, column);
                line++;
                column = 1;
                i = j;
                continue;
            }
        }
        buffer[size] = c;
        lexer->line_map[size] = line;
        lexer->column_map[size] = column;
        size++;
        if (c == '\n') {
            line++;
            column = 1;
        } else
            column++;
        i++;
    }
    if (size == 0 || buffer[size - 1] != '\n') {
        lexer->line_map[size] = line;
        lexer->column_map[size] = column;
        buffer[size++] = '\n';
        column = 1;
        line++;
    }
    buffer[size] = '\0';
    lexer->line_map[size] = line;
    lexer->column_map[size] = column;
    lexer->source_code = buffer;
    lexer->length = size;
}
ppLexer *create_pp_lexer(string filename, string source_code) {
    ppLexer *lexer = (ppLexer *)alloc_memory(sizeof(ppLexer), 1);
    if (source_code == ((void *)0)) {
        fprintf(stderr, "[Preprocessor Error] at <create_pp_lexer>: Failed to create ppLexer, source_code is NULL\n");
        has_error = 1;
        return ((void *)0);
    }
    lexer->source_code = ((void *)0);
    lexer->length = 0;
    lexer->pos = 0;
    lexer->filename = filename;
    lexer->pp_tokens = list_create(_Generic((ppToken *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
    lexer->line_map = ((void *)0);
    lexer->column_map = ((void *)0);
    lexer->include_state = 0;
    lexer->pending_space = 0;
    lexer->line_start = 1;
    lexer->output_error = 1;
    normalize(lexer, source_code);
    return lexer;
}
_Bool pp_lexer(ppLexer *lexer) {
    has_error = 0;
    while (1) {
        char c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
        if (c == '\0') {
            add_pp_token(lexer, PP_EOF, ((void *)0), lexer->length);
            return has_error;
        } else if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f') {
            if (c == '\n')
                add_pp_token(lexer, PP_NEWLINE, ((void *)0), lexer->pos - 1);
            else
                lexer->pending_space = 1;
        } else if ((((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z')) || c == '_') {
            size_t start = lexer->pos - 1;
            do {
                c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
            } while ((((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z')) || ((c) >= '0' && (c) <= '9') || c == '_');
            if (lexer->pos > 0)
                lexer->pos -= 1;
            add_pp_token(lexer, PP_IDENTIFIER, create_string(&lexer->source_code[start], ((lexer->pos) < (lexer->length) ? (lexer->pos) : (lexer->length)) - start), start);
        } else if (((c) >= '0' && (c) <= '9') || (((((lexer->pos >= lexer->length) ? '\0' : lexer->source_code[lexer->pos])) >= '0' && (((lexer->pos >= lexer->length) ? '\0' : lexer->source_code[lexer->pos])) <= '9') && (c == '.'))) {
            size_t start = lexer->pos - 1;
            char p = '\0';
            c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
            while (((c) >= '0' && (c) <= '9') || (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z')) || c == '_' || c == '.') {
                p = c;
                c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
                if (p == 'e' || p == 'E' || p == 'p' || p == 'P') {
                    if (c == '+' || c == '-') {
                        p = c;
                        c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
                    }
                }
            }
            if (lexer->pos > 0)
                lexer->pos -= 1;
            add_pp_token(lexer, PP_NUMBER, create_string(&lexer->source_code[start], ((lexer->pos) < (lexer->length) ? (lexer->pos) : (lexer->length)) - start), start);
        } else if (c == '"') {
            _Bool is_header_name = (lexer->include_state == 2);
            size_t start = lexer->pos - 1;
            _Bool error = 0;
            do {
                c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
                if (c == '\\' && !is_header_name && ((lexer->pos >= lexer->length) ? '\0' : lexer->source_code[lexer->pos]) != '\0' && ((lexer->pos >= lexer->length) ? '\0' : lexer->source_code[lexer->pos]) != '\n')
                    ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
                if (c == '\0' || c == '\n') {
                    error = 1;
                    if (c == '\n')
                        if (lexer->pos > 0)
                            lexer->pos -= 1;
                    break;
                }
            } while (c != '"');
            add_pp_token(lexer, error ? PP_OTHER : (is_header_name ? PP_HEADER_NAME : PP_STRING), create_string(&lexer->source_code[start], ((lexer->pos) < (lexer->length) ? (lexer->pos) : (lexer->length)) - start), start);
        } else if (c == '\'') {
            size_t start = lexer->pos - 1;
            _Bool error = 0;
            do {
                c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
                if (c == '\\' && ((lexer->pos >= lexer->length) ? '\0' : lexer->source_code[lexer->pos]) != '\0' && ((lexer->pos >= lexer->length) ? '\0' : lexer->source_code[lexer->pos]) != '\n')
                    ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
                if (c == '\0' || c == '\n') {
                    error = 1;
                    if (c == '\n')
                        if (lexer->pos > 0)
                            lexer->pos -= 1;
                    break;
                }
            } while (c != '\'');
            add_pp_token(lexer, error ? PP_OTHER : PP_CHAR, create_string(&lexer->source_code[start], ((lexer->pos) < (lexer->length) ? (lexer->pos) : (lexer->length)) - start), start);
        } else if (c == '/') {
            size_t start = lexer->pos - 1;
            c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
            if (c == '/') {
                do {
                    c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
                } while (c != '\n' && c != '\0');
                lexer->pending_space = 1;
                if (lexer->pos > 0)
                    lexer->pos -= 1;
            } else if (c == '*') {
                while (1) {
                    c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
                    if (c == '\0') {
                        if (lexer->output_error)
                            fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: Unterminated comment\n", lexer->filename, ((start >= lexer->length) ? lexer->line_map[lexer->length] : lexer->line_map[start]), ((start >= lexer->length) ? lexer->column_map[lexer->length] : lexer->column_map[start]));
                        has_error = 1;
                        break;
                    } else if (c == '*') {
                        c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
                        if (c == '/')
                            break;
                        if (lexer->pos > 0)
                            lexer->pos -= 1;
                    }
                }
                lexer->pending_space = 1;
            } else if (c == '=')
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_DIV_ASSIGN, start);
            else {
                if (lexer->pos > 0)
                    lexer->pos -= 1;
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_DIV, start);
            }
        } else if (c == '-') {
            c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
            if (c == '-')
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_DECREMENT, lexer->pos - 2);
            else if (c == '=')
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_SUB_ASSIGN, lexer->pos - 2);
            else if (c == '>')
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_ARROW, lexer->pos - 2);
            else {
                if (lexer->pos > 0)
                    lexer->pos -= 1;
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_SUB, lexer->pos - 1);
            }
        } else if (c == '!') {
            if (((lexer->pos >= lexer->length) ? '\0' : lexer->source_code[lexer->pos]) == '=') {
                c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_NE, lexer->pos - 2);
            } else
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_LOGICAL_NOT, lexer->pos - 1);
        } else if (c == '*') {
            if (((lexer->pos >= lexer->length) ? '\0' : lexer->source_code[lexer->pos]) == '=') {
                c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_MUL_ASSIGN, lexer->pos - 2);
            } else
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_MUL, lexer->pos - 1);
        } else if (c == '.') {
            c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
            if (c == '.' && ((lexer->pos >= lexer->length) ? '\0' : lexer->source_code[lexer->pos]) == '.') {
                ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_ELLIPSIS, lexer->pos - 3);
            } else {
                if (lexer->pos > 0)
                    lexer->pos -= 1;
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_DOT, lexer->pos - 1);
            }
        } else if (c == '&') {
            c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
            if (c == '&')
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_LOGICAL_AND, lexer->pos - 2);
            else if (c == '=')
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_AND_ASSIGN, lexer->pos - 2);
            else {
                if (lexer->pos > 0)
                    lexer->pos -= 1;
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_BITWISE_AND, lexer->pos - 1);
            }
        } else if (c == '%') {
            if (((lexer->pos >= lexer->length) ? '\0' : lexer->source_code[lexer->pos]) == '=') {
                ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_MOD_ASSIGN, lexer->pos - 2);
            } else
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_MOD, lexer->pos - 1);
        } else if (c == '^') {
            if (((lexer->pos >= lexer->length) ? '\0' : lexer->source_code[lexer->pos]) == '=') {
                ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_XOR_ASSIGN, lexer->pos - 2);
            } else
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_XOR, lexer->pos - 1);
        } else if (c == '=') {
            if (((lexer->pos >= lexer->length) ? '\0' : lexer->source_code[lexer->pos]) == '=') {
                ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_EQ, lexer->pos - 2);
            } else
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_ASSIGN, lexer->pos - 1);
        } else if (c == '+') {
            c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
            if (c == '+')
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_INCREMENT, lexer->pos - 2);
            else if (c == '=')
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_ADD_ASSIGN, lexer->pos - 2);
            else {
                if (lexer->pos > 0)
                    lexer->pos -= 1;
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_ADD, lexer->pos - 1);
            }
        } else if (c == '<') {
            if (lexer->include_state == 2) {
                size_t start = lexer->pos - 1;
                while (1) {
                    c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
                    if (c == '\0' || c == '\n') {
                        if (c == '\n')
                            if (lexer->pos > 0)
                                lexer->pos -= 1;
                        add_pp_token(lexer, PP_OTHER, create_string(&lexer->source_code[start], ((lexer->pos) < (lexer->length) ? (lexer->pos) : (lexer->length)) - start), start);
                        break;
                    } else if (c == '>') {
                        add_pp_token(lexer, PP_HEADER_NAME, create_string(&lexer->source_code[start], ((lexer->pos) < (lexer->length) ? (lexer->pos) : (lexer->length)) - start), start);
                        break;
                    }
                }
                continue;
            }
            c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
            if (c == '=')
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_LE, lexer->pos - 2);
            else if (c == '<') {
                if (((lexer->pos >= lexer->length) ? '\0' : lexer->source_code[lexer->pos]) == '=') {
                    c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
                    add_pp_token(lexer, PP_SYMBOL, SYMBOL_L_SHIFT_ASSIGN, lexer->pos - 3);
                } else
                    add_pp_token(lexer, PP_SYMBOL, SYMBOL_L_SHIFT, lexer->pos - 2);
            } else {
                if (lexer->pos > 0)
                    lexer->pos -= 1;
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_LT, lexer->pos - 1);
            }
        } else if (c == '>') {
            c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
            if (c == '=')
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_GE, lexer->pos - 2);
            else if (c == '>') {
                if (((lexer->pos >= lexer->length) ? '\0' : lexer->source_code[lexer->pos]) == '=') {
                    c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
                    add_pp_token(lexer, PP_SYMBOL, SYMBOL_R_SHIFT_ASSIGN, lexer->pos - 3);
                } else
                    add_pp_token(lexer, PP_SYMBOL, SYMBOL_R_SHIFT, lexer->pos - 2);
            } else {
                if (lexer->pos > 0)
                    lexer->pos -= 1;
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_GT, lexer->pos - 1);
            }
        } else if (c == '|') {
            c = ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
            if (c == '|')
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_LOGICAL_OR, lexer->pos - 2);
            else if (c == '=')
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_OR_ASSIGN, lexer->pos - 2);
            else {
                if (lexer->pos > 0)
                    lexer->pos -= 1;
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_BITWISE_OR, lexer->pos - 1);
            }
        } else if (c == ',')
            add_pp_token(lexer, PP_SYMBOL, SYMBOL_COMMA, lexer->pos - 1);
        else if (c == ';')
            add_pp_token(lexer, PP_SYMBOL, SYMBOL_SEMICOLON, lexer->pos - 1);
        else if (c == ':')
            add_pp_token(lexer, PP_SYMBOL, SYMBOL_COLON, lexer->pos - 1);
        else if (c == '?')
            add_pp_token(lexer, PP_SYMBOL, SYMBOL_QUESTION, lexer->pos - 1);
        else if (c == '(')
            add_pp_token(lexer, PP_SYMBOL, SYMBOL_L_PARENTHESIS, lexer->pos - 1);
        else if (c == ')')
            add_pp_token(lexer, PP_SYMBOL, SYMBOL_R_PARENTHESIS, lexer->pos - 1);
        else if (c == '[')
            add_pp_token(lexer, PP_SYMBOL, SYMBOL_L_BRACKET, lexer->pos - 1);
        else if (c == ']')
            add_pp_token(lexer, PP_SYMBOL, SYMBOL_R_BRACKET, lexer->pos - 1);
        else if (c == '{')
            add_pp_token(lexer, PP_SYMBOL, SYMBOL_L_BRACE, lexer->pos - 1);
        else if (c == '}')
            add_pp_token(lexer, PP_SYMBOL, SYMBOL_R_BRACE, lexer->pos - 1);
        else if (c == '~')
            add_pp_token(lexer, PP_SYMBOL, SYMBOL_BITWISE_NOT, lexer->pos - 1);
        else if (c == '#') {
            if (((lexer->pos >= lexer->length) ? '\0' : lexer->source_code[lexer->pos]) == '#') {
                ((lexer->pos++ >= lexer->length) ? '\0' : lexer->source_code[lexer->pos - 1]);
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_DOUBLE_HASH, lexer->pos - 2);
            } else
                add_pp_token(lexer, PP_SYMBOL, SYMBOL_HASH, lexer->pos - 1);
        } else
            add_pp_token(lexer, PP_OTHER, create_string(&lexer->source_code[lexer->pos - 1], 1), lexer->pos - 1);
    }
}
