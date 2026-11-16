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
static string is_keyword(string str) {
    for (size_t i = 0; i < 44; ++i)
        if (str == keywordList[i])
            return keywordList[i];
    return ((void *)0);
}
static Token *create_token(TokenType type, ppToken *t) {
    Token *token = (Token *)alloc_memory(sizeof(Token), 1);
    token->line = t->line;
    token->column = t->column;
    token->type = type;
    token->value = t->value;
    memset(&token->literal, 0, sizeof (token->literal));
    token->filename = t->filename;
    token->space_before = t->space_before;
    token->at_line_start = t->at_line_start;
    if (type == TOKEN_IDENTIFIER) {
        string keyword = is_keyword(t->value);
        if (keyword != ((void *)0)) {
            token->type = TOKEN_KEYWORD;
            token->value = keyword;
        }
    }
    return token;
}
static Token *int_token(ppToken *t) {
    string s = t->value;
    IntLiteral literal = parse_int_digits(s);
    size_t i = literal.digits_end;
    _Bool is_unsigned = 0;
    size_t long_count = 0;
    for (; s[i] != '\0'; ++i) {
        if (s[i] == 'u' || s[i] == 'U')
            is_unsigned = 1;
        else
            long_count++;
    }
    if (literal.overflow)
        fprintf(stderr, "[Syntax Warning] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + 0, "Integer constant is too large");
    else if (literal.base == 10 && !is_unsigned && literal.value > (uintmax_t)INTMAX_MAX)
        fprintf(stderr, "[Syntax Warning] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + 0, "Integer constant is so large that it is unsigned");
    Token *token = create_token(TOKEN_INT, t);
    token->literal.integer.data = literal.value;
    if (is_unsigned)
        token->literal.integer.suffix = long_count == 0 ? SUFFIX_U : (long_count == 1 ? SUFFIX_UL : SUFFIX_ULL);
    else
        token->literal.integer.suffix = long_count == 0 ? SUFFIX_NONE : (long_count == 1 ? SUFFIX_L : SUFFIX_LL);
    token->literal.integer.is_decimal = literal.base == 10;
    return token;
}
static _Bool has_nonzero_digit(string s) {
    _Bool is_hex = s[0] == '0' && (s[1] == 'x' || s[1] == 'X');
    for (size_t i = is_hex ? 2 : 0; s[i] != '\0'; ++i) {
        if (is_hex ? (s[i] == 'p' || s[i] == 'P') : (s[i] == 'e' || s[i] == 'E'))
            break;
        if (is_hex ? hex_digit_value(s[i]) > 0 : (s[i] >= '1' && s[i] <= '9'))
            return 1;
    }
    return 0;
}
static Token *float_token(ppToken *t) {
    string s = t->value;
    char last = s[strlen(s) - 1];
    NumberSuffix suffix = SUFFIX_NONE;
    long double value;
    if (last == 'f' || last == 'F') {
        suffix = SUFFIX_F;
        value = (long double)strtof(s, ((void *)0));
    } else if (last == 'l' || last == 'L') {
        suffix = SUFFIX_LD;
        value = strtold(s, ((void *)0));
    } else {
        value = (long double)strtod(s, ((void *)0));
    }
    if (isinf(value))
        fprintf(stderr, "[Syntax Warning] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + 0, "Floating constant exceeds the range of its type");
    else if (value <= 0 && has_nonzero_digit(s))
        fprintf(stderr, "[Syntax Warning] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + 0, "Floating constant truncated to zero");
    Token *token = create_token(TOKEN_FLOAT, t);
    token->literal.floating.data = value;
    token->literal.floating.suffix = suffix;
    return token;
}
static Token *number_token(ppToken *t) {
    _Bool is_float = 0;
    _Bool is_hex = 0;
    _Bool error = 0;
    size_t i = 0;
    string C = t->value;
    if (((C[0]) >= '0' && (C[0]) <= '9') && C[0] != '0') {
        i = 1;
        while (((C[i]) >= '0' && (C[i]) <= '9'))
            i++;
        if (C[i] == '.') {
            is_float = 1;
            i++;
            while (((C[i]) >= '0' && (C[i]) <= '9'))
                i++;
        }
    } else if (C[0] == '0') {
        if (C[1] == 'x' || C[1] == 'X') {
            is_hex = 1;
            i = 2;
            size_t t0 = 0;
            while (hex_digit_value(C[i]) >= 0) {
                i++;
                t0++;
            }
            if (C[i] == '.') {
                is_float = 1;
                i++;
                size_t t1 = 0;
                while (hex_digit_value(C[i]) >= 0) {
                    i++;
                    t1++;
                }
                if (t0 == 0 && t1 == 0) {
                    if (!error)
                        fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + 0, "Invalid number format, hex number must have at least one digit");
                    error = 1;
                }
            } else if (t0 == 0) {
                if (!error)
                    fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + 0, "Invalid number format, hex number must have at least one digit");
                error = 1;
            }
        } else if (C[1] == 'b' || C[1] == 'B') {
            i = 2;
            size_t t0 = 0;
            while (C[i] == '0' || C[i] == '1') {
                i++;
                t0++;
            }
            if ((((C[i]) >= '0' && (C[i]) <= '9') && C[i] != '0' && C[i] != '1') || C[i] == '.' || C[i] == 'e' || C[i] == 'E' || C[i] == 'p' || C[i] == 'P') {
                if (!error)
                    fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + 0, "Invalid number format, binary number can only contain 0 and 1");
                error = 1;
            }
            if (t0 == 0) {
                if (!error)
                    fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + 0, "Invalid number format, binary number must have at least one digit");
                error = 1;
            }
        } else if (C[1] == '.') {
            is_float = 1;
            i = 2;
            while (((C[i]) >= '0' && (C[i]) <= '9'))
                i++;
        } else {
            i = 1;
            while (((C[i]) >= '0' && (C[i]) <= '9'))
                i++;
            if (C[i] == '.') {
                is_float = 1;
                i++;
                while (((C[i]) >= '0' && (C[i]) <= '9'))
                    i++;
            } else if (C[i] == 'e' || C[i] == 'E') {
                is_float = 1;
            } else {
                for (size_t k = 0; k < i; k++) {
                    if (C[k] == '8' || C[k] == '9') {
                        if (!error)
                            fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + 0, "Invalid number format, octal number can only contain digits 0-7");
                        error = 1;
                        break;
                    }
                }
            }
        }
    } else if (C[0] == '.') {
        is_float = 1;
        i = 1;
        size_t t1 = 0;
        while (((C[i]) >= '0' && (C[i]) <= '9')) {
            i++;
            t1++;
        }
        if (t1 == 0) {
            if (!error)
                fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + 0, "Invalid number format, float number must have at least one digit after decimal point");
            error = 1;
        }
    }
    if (is_float && is_hex && C[i] != 'p' && C[i] != 'P') {
        if (!error)
            fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + 0, "Invalid number format, hex float number must have 'p' or 'P' exponent");
        error = 1;
    }
    if (C[i] == 'p' || C[i] == 'P' || C[i] == 'e' || C[i] == 'E') {
        char ec = C[i];
        if (is_hex && ec != 'p' && ec != 'P') {
            if (!error)
                fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + 0, "Invalid number format, hex float number must have 'p' or 'P' exponent");
            error = 1;
        }
        if (!is_hex && (ec == 'p' || ec == 'P')) {
            if (!error)
                fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + 0, "Invalid number format, decimal float number must have 'e' or 'E' exponent");
            error = 1;
        }
        is_float = 1;
        i++;
        if (C[i] == '+' || C[i] == '-')
            i++;
        size_t t1 = 0;
        while (((C[i]) >= '0' && (C[i]) <= '9')) {
            i++;
            t1++;
        }
        if (t1 == 0) {
            if (!error)
                fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + 0, "Invalid number format, exponent must have at least one digit");
            error = 1;
        }
    }
    if (is_float) {
        if (C[i] == 'f' || C[i] == 'F')
            i++;
        else if (C[i] == 'l' || C[i] == 'L')
            i++;
    } else {
        if (C[i] == 'u' || C[i] == 'U') {
            i++;
            if (C[i] == 'l' || C[i] == 'L') {
                i++;
                if (C[i - 1] == C[i])
                    i++;
            }
        } else if (C[i] == 'l' || C[i] == 'L') {
            i++;
            if (C[i - 1] == C[i])
                i++;
            if (C[i] == 'u' || C[i] == 'U')
                i++;
        }
    }
    if (C[i] != '\0') {
        if (!error)
            fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + 0, "Invalid number format");
        error = 1;
    }
    if (error)
        return create_token(TOKEN_SYNTAX_ERROR_NUMBER, t);
    else if (is_float)
        return float_token(t);
    else
        return int_token(t);
}
static _Bool report_escape(ppToken *t, EscapeResult result, size_t offset) {
    if (result == ESC_OK)
        return 1;
    if (result == ESC_NO_HEX_DIGITS || result == ESC_UNSUPPORTED) {
        fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + offset, escape_message(result));
        return 0;
    }
    fprintf(stderr, "[Syntax Warning] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + offset, escape_message(result));
    return 1;
}
static Token *char_token(ppToken *t) {
    size_t end = strlen(t->value) - 1;
    assert(end >= 1 && t->value[0] == '\'' && t->value[end] == '\'');
    size_t i = 1;
    size_t count = 0;
    unsigned int acc = 0;
    while (i < end) {
        size_t start = i;
        unsigned int c;
        if (!report_escape(t, decode_literal_char(t->value, &i, &c), start))
            return create_token(TOKEN_SYNTAX_ERROR_CHAR, t);
        acc = (acc << 8) | c;
        count++;
    }
    if (count == 0) {
        fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + 0, "Empty character constant");
        return create_token(TOKEN_SYNTAX_ERROR_CHAR, t);
    }
    if (count > 1) {
        fprintf(stderr, "[Syntax Warning] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + 0, "Multi-character character constant");
        if (count > 4)
            fprintf(stderr, "[Syntax Warning] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + 0, "character constant too long");
    }
    Token *token = create_token(TOKEN_CHAR, t);
    token->literal.character = count == 1 ? (int)(char)acc : (int)acc;
    return token;
}
static Token *string_token(ppToken *t) {
    size_t end = strlen(t->value) - 1;
    assert(end >= 1 && t->value[0] == '"' && t->value[end] == '"');
    char *data = (char *)alloc_memory(end - 1, 0);
    size_t length = 0;
    size_t i = 1;
    while (i < end) {
        if (t->value[i] == '\\' && i + 1 == end) {
            fprintf(stderr, "[Syntax Error] at %s:%zu:%zu: %s\n", t->filename, t->line + 0, t->column + i, "Invalid string literal, ends with a lone '\\'");
            return create_token(TOKEN_SYNTAX_ERROR_STRING, t);
        }
        size_t start = i;
        unsigned int c;
        if (!report_escape(t, decode_literal_char(t->value, &i, &c), start))
            return create_token(TOKEN_SYNTAX_ERROR_STRING, t);
        data[length++] = (char)c;
    }
    Token *token = create_token(TOKEN_STRING, t);
    token->literal.str.data = data;
    token->literal.str.length = length;
    return token;
}
static List_Token *splice_adjacent_string(List_Token *tokens) {
    List_Token *result = list_create(_Generic((Token *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
    ListNode *n = tokens->head;
    while (n != ((void *)0)) {
        Token *first = (Token *)n->data;
        list_append((result), (void *)(first), _Generic((first), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
        ListNode *end = n;
        size_t value_len = 0;
        size_t data_len = 0;
        for (; end != ((void *)0) && end->data != ((void *)0) && ((Token *)end->data)->type == TOKEN_STRING; end = end->next) {
            value_len += strlen(((Token *)end->data)->value);
            data_len += ((Token *)end->data)->literal.str.length;
        }
        if (end == n || end == n->next) {
            n = n->next;
            continue;
        }
        char *value = (char *)malloc(value_len);
        char *data = (char *)malloc(data_len + 1);
        if (value == ((void *)0) || data == ((void *)0)) {
            fprintf(stderr, "[lexer Fatal] at <splice_adjacent_string>: Cannot allocate memory\n");
            abort();
        }
        value_len = 0;
        data_len = 0;
        for (; n != end; n = n->next) {
            Token *t = (Token *)n->data;
            size_t len = strlen(t->value);
            memcpy(value + value_len, t->value, len);
            memcpy(data + data_len, t->literal.str.data, t->literal.str.length);
            value_len += len;
            data_len += t->literal.str.length;
        }
        first->value = create_string(value, value_len);
        first->literal.str.data = create_string(data, data_len);
        first->literal.str.length = data_len;
        free(value);
        free(data);
    }
    return result;
}
List_Token *pp_to_tokens(List_ppToken *pp_tokens) {
    List_Token *tokens = list_create(_Generic((Token *)0, string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
    for (List *t__l = (pp_tokens); t__l != ((void *)0) && t__l->head != ((void *)0); t__l = ((void *)0))
        for (ListNode *t__n = t__l->head; t__n != ((void *)0); t__n = t__n->next)
            for (ppToken *t = (ppToken *)t__n->data; t != ((void *)0); t = ((void *)0)) {
                switch (t->type) {
                case PP_IDENTIFIER:
                    list_append((tokens), (void *)(create_token(TOKEN_IDENTIFIER, t)), _Generic((create_token(TOKEN_IDENTIFIER, t)), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
                    break;
                case PP_NUMBER:
                    list_append((tokens), (void *)(number_token(t)), _Generic((number_token(t)), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
                    break;
                case PP_CHAR:
                    list_append((tokens), (void *)(char_token(t)), _Generic((char_token(t)), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
                    break;
                case PP_STRING:
                    list_append((tokens), (void *)(string_token(t)), _Generic((string_token(t)), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
                    break;
                case PP_SYMBOL:
                    list_append((tokens), (void *)(create_token(TOKEN_SYMBOL, t)), _Generic((create_token(TOKEN_SYMBOL, t)), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
                    break;
                case PP_EOF:
                    list_append((tokens), (void *)(create_token(TOKEN_EOF, t)), _Generic((create_token(TOKEN_EOF, t)), string: TYPE_string, ppToken *: TYPE_ppToken, ppMacro *: TYPE_ppMacro, ppCondFrame *: TYPE_ppCondFrame, List_ppToken *: TYPE_List_ppToken, Token *: TYPE_Token, ExternDecl *: TYPE_ExternDecl, DeclSpec *: TYPE_DeclSpec, InitDecl *: TYPE_InitDecl, ParamDecl *: TYPE_ParamDecl, StructDecl *: TYPE_StructDecl, Enumerator *: TYPE_Enumerator, InitializerItem *: TYPE_InitializerItem, Designator *: TYPE_Designator, SpecifierQualifier *: TYPE_SpecifierQualifier, StructDeclarator *: TYPE_StructDeclarator, DeclStmt *: TYPE_DeclStmt, AssignmentExpression *: TYPE_AssignmentExpression, GenericAssociation *: TYPE_GenericAssociation, TypeName *: TYPE_TypeName, Scope *: TYPE_Scope, Symbol *: TYPE_Symbol));
                    return splice_adjacent_string(tokens);
                case PP_OTHER:
                case PP_PLACE_MARKER:
                case PP_HEADER_NAME:
                    assert(0);
                case PP_NEWLINE:
                default:
                    break;
                }
            }
    return splice_adjacent_string(tokens);
}
