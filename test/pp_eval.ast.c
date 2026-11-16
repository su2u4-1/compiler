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
ppToken *pp_peek(ppContext *ctx) {
    if (ctx == ((void *)0))
        return ((void *)0);
    if (ctx->current == ((void *)0) || ctx->current->data == ((void *)0))
        return create_pp_token(PP_EOF, ((void *)0), ctx->lexer, ctx->lexer->length);
    return (ppToken *)ctx->current->data;
}
ppToken *pp_get(ppContext *ctx) {
    if (ctx == ((void *)0))
        return ((void *)0);
    if (ctx->current == ((void *)0) || ctx->current->data == ((void *)0))
        return create_pp_token(PP_EOF, ((void *)0), ctx->lexer, ctx->lexer->length);
    ppToken *t = (ppToken *)ctx->current->data;
    ctx->current = ctx->current->next;
    return t;
}
static _Bool has_error = 0;
static _Bool expect_token(ppContext *ctx, char *message, size_t line, size_t column, ppTokenType type, string value) {
    ppToken *t = pp_peek(ctx);
    if (((t) == ((void *)0) || (t)->type == PP_EOF) || t->type != type || (value != ((void *)0) && t->value != value)) {
        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), line, column, message);
        return 0;
    }
    pp_get(ctx);
    return 1;
}
typedef struct {
    union {
        intmax_t sign;
        uintmax_t unsign;
    } value;
    _Bool is_unsigned;
} ppIntValue;
static inline _Bool is_true(ppIntValue v) {
    return v.is_unsigned ? v.value.unsign != 0 : v.value.sign != 0;
}
static inline intmax_t get_sign(ppIntValue v) {
    return v.is_unsigned ? (intmax_t)v.value.unsign : v.value.sign;
}
static inline uintmax_t get_unsign(ppIntValue v) {
    return v.is_unsigned ? v.value.unsign : (uintmax_t)v.value.sign;
}
static inline ppIntValue pp_bool(ppIntValue b) {
    return ((ppIntValue){.value.sign = (is_true(b) ? 1 : 0), .is_unsigned = 0});
}
static ppIntValue eval_number_literal(ppContext *ctx, ppToken *t, _Bool skip) {
    assert(t != ((void *)0) && t->type == PP_NUMBER);
    string s = t->value;
    IntLiteral literal = parse_int_digits(s);
    unsigned base = literal.base;
    uintmax_t v = literal.value;
    size_t i = literal.digits_end;
    char e = s[i];
    if (e == '.' || (base == 16 ? (e == 'p' || e == 'P') : (e == 'e' || e == 'E'))) {
        if (!skip)
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Floating constant in preprocessor expression");
        return ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
    }
    if (i == literal.digits_start && base != 8) {
        if (!skip)
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Integer constant has no digits");
        return ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
    }
    if (hex_digit_value(s[i]) >= 0) {
        if (!skip)
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Invalid digit in integer constant");
        return ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
    }
    _Bool u = 0;
    int l = 0;
    while (s[i]) {
        if ((s[i] == 'u' || s[i] == 'U') && !u) {
            u = 1;
            i++;
        } else if ((s[i] == 'l' || s[i] == 'L') && l == 0) {
            l = 1;
            i++;
            if (s[i] == s[i - 1]) {
                l = 2;
                i++;
            }
        } else
            break;
    }
    if (s[i] != '\0') {
        if (!skip)
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Invalid suffix on integer constant");
        return ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
    }
    if (literal.overflow) {
        if (!skip)
            fprintf(stderr, "[Preprocess Warning] at %s:%zu:%zu: %s\n", ctx->lexer->filename, t->line, t->column, "Integer constant is too large");
        return u ? ((ppIntValue){.value.unsign = (v), .is_unsigned = 1}) : ((ppIntValue){.value.sign = ((intmax_t)v), .is_unsigned = 0});
    }
    if (u)
        return ((ppIntValue){.value.unsign = (v), .is_unsigned = 1});
    if (v > (uintmax_t)INTMAX_MAX) {
        if (base == 10 && !skip)
            fprintf(stderr, "[Preprocess Warning] at %s:%zu:%zu: %s\n", ctx->lexer->filename, t->line, t->column, "Integer constant is so large that it is unsigned");
        return ((ppIntValue){.value.unsign = (v), .is_unsigned = 1});
    }
    return ((ppIntValue){.value.sign = ((intmax_t)v), .is_unsigned = 0});
}
static int eval_char_literal(ppContext *ctx, ppToken *t, _Bool skip) {
    assert(t != ((void *)0) && t->type == PP_CHAR);
    string s = t->value;
    size_t end = strlen(s) - 1;
    size_t i = 1;
    size_t count = 0;
    unsigned int acc = 0;
    while (i < end) {
        unsigned int c;
        EscapeResult result = decode_literal_char(s, &i, &c);
        if (result != ESC_OK && !skip) {
            if (result == ESC_NO_HEX_DIGITS)
                fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, escape_message(result));
            else
                fprintf(stderr, "[Preprocess Warning] at %s:%zu:%zu: %s\n", ctx->lexer->filename, t->line, t->column, escape_message(result));
        }
        if (result == ESC_NO_HEX_DIGITS || result == ESC_UNSUPPORTED)
            return 0;
        acc = (acc << 8) | c;
        count++;
    }
    if (count == 0) {
        if (!skip)
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Empty character constant");
        return 0;
    }
    if (count > 1 && !skip) {
        fprintf(stderr, "[Preprocess Warning] at %s:%zu:%zu: %s\n", ctx->lexer->filename, t->line, t->column, "Multi-character character constant");
        if (count > 4)
            fprintf(stderr, "[Preprocess Warning] at %s:%zu:%zu: %s\n", ctx->lexer->filename, t->line, t->column, "character constant too long");
    }
    return count == 1 ? (int)(char)acc : (int)acc;
}
static ppIntValue eval_conditional_expr(ppContext *ctx, _Bool skip);
static ppIntValue eval_unary_expr(ppContext *ctx, _Bool skip) {
    ppToken *t = pp_peek(ctx);
    if (((t) == ((void *)0) || (t)->type == PP_EOF) || t->type == PP_NEWLINE) {
        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t == ((void *)0) ? 0 : t->line, t == ((void *)0) ? 0 : t->column, "Expected primary expression");
        return ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
    } else if (t->type == PP_IDENTIFIER && t->value == P_DEFINED) {
        pp_get(ctx);
        t = pp_peek(ctx);
        _Bool has_parens = 0;
        if (!((t) == ((void *)0) || (t)->type == PP_EOF) && t->type == PP_SYMBOL && t->value == SYMBOL_L_PARENTHESIS) {
            has_parens = 1;
            pp_get(ctx);
        }
        ppToken *name_token = pp_peek(ctx);
        if (!expect_token(ctx, "Expected identifier after defined", name_token->line, name_token->column, PP_IDENTIFIER, ((void *)0)))
            return ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
        if (has_parens) {
            if (!expect_token(ctx, "Expected ) after defined(identifier)", name_token->line, name_token->column, PP_SYMBOL, SYMBOL_R_PARENTHESIS))
                return ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
        }
        if (name_token->value == P_LINE_ || name_token->value == P_FILE_ || find_macro(ctx, name_token->value) != ((void *)0))
            return ((ppIntValue){.value.sign = (1), .is_unsigned = 0});
        return ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
    } else if (t->type == PP_SYMBOL && (t->value == SYMBOL_ADD || t->value == SYMBOL_SUB || t->value == SYMBOL_BITWISE_NOT || t->value == SYMBOL_LOGICAL_NOT)) {
        pp_get(ctx);
        ppIntValue operand = eval_unary_expr(ctx, skip);
        if (t->value == SYMBOL_ADD)
            return operand;
        else if (t->value == SYMBOL_SUB) {
            if (operand.is_unsigned)
                return ((ppIntValue){.value.unsign = (0U - operand.value.unsign), .is_unsigned = 1});
            else
                return ((ppIntValue){.value.sign = ((intmax_t)(0 - (uintmax_t)get_sign(operand))), .is_unsigned = 0});
        } else if (t->value == SYMBOL_BITWISE_NOT) {
            if (operand.is_unsigned)
                return ((ppIntValue){.value.unsign = (~operand.value.unsign), .is_unsigned = 1});
            else
                return ((ppIntValue){.value.sign = (~operand.value.sign), .is_unsigned = 0});
        } else
            return is_true(operand) ? ((ppIntValue){.value.sign = (0), .is_unsigned = 0}) : ((ppIntValue){.value.sign = (1), .is_unsigned = 0});
    } else if (t->type == PP_IDENTIFIER && t->value == P_PRAGMA_) {
        pp_get(ctx);
        if (expect_token(ctx, "Expected ( after _Pragma", t->line, t->column, PP_SYMBOL, SYMBOL_L_PARENTHESIS))
            if (expect_token(ctx, "Expected string literal after _Pragma(", t->line, t->column, PP_STRING, ((void *)0)))
                expect_token(ctx, "Expected ) after _Pragma(string)", t->line, t->column, PP_SYMBOL, SYMBOL_R_PARENTHESIS);
        return ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
    } else if (t->type == PP_IDENTIFIER) {
        pp_get(ctx);
        if (expand_macro(ctx, t))
            return eval_unary_expr(ctx, skip);
        return ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
    } else if (t->type == PP_NUMBER) {
        t = pp_get(ctx);
        return eval_number_literal(ctx, t, skip);
    } else if (t->type == PP_CHAR) {
        t = pp_get(ctx);
        return ((ppIntValue){.value.sign = ((intmax_t)eval_char_literal(ctx, t, skip)), .is_unsigned = 0});
    } else if (t->type == PP_SYMBOL && t->value == SYMBOL_L_PARENTHESIS) {
        t = pp_get(ctx);
        ppIntValue result = eval_conditional_expr(ctx, skip);
        t = pp_peek(ctx);
        if (!expect_token(ctx, "Expected ) after expression", t->line, t->column, PP_SYMBOL, SYMBOL_R_PARENTHESIS))
            return ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
        return result;
    } else {
        if (!skip)
            fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Expected primary expression");
        return ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
    }
}
static ppIntValue eval_multiplicative_expr(ppContext *ctx, _Bool skip) {
    ppIntValue result = eval_unary_expr(ctx, skip);
    ppToken *t = pp_peek(ctx);
    while (!((t) == ((void *)0) || (t)->type == PP_EOF) && t->type == PP_SYMBOL && (t->value == SYMBOL_MUL || t->value == SYMBOL_DIV || t->value == SYMBOL_MOD)) {
        t = pp_get(ctx);
        ppIntValue right = eval_unary_expr(ctx, skip);
        if (t->value == SYMBOL_MUL) {
            if (!result.is_unsigned && !right.is_unsigned)
                result = ((ppIntValue){.value.sign = ((intmax_t)((uintmax_t)get_sign(result) * (uintmax_t)get_sign(right))), .is_unsigned = 0});
            else
                result = ((ppIntValue){.value.unsign = (get_unsign(result) * get_unsign(right)), .is_unsigned = 1});
        } else if (t->value == SYMBOL_DIV) {
            if (!is_true(right)) {
                if (!skip)
                    fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Division by zero");
                result = ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
                break;
            } else if (!result.is_unsigned && !right.is_unsigned) {
                if (!right.is_unsigned && get_sign(result) == INTMAX_MIN && get_sign(right) == -1) {
                    if (!skip)
                        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Integer constant expression overflow");
                    result = ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
                } else
                    result = ((ppIntValue){.value.sign = (get_sign(result) / get_sign(right)), .is_unsigned = 0});
            } else
                result = ((ppIntValue){.value.unsign = (get_unsign(result) / get_unsign(right)), .is_unsigned = 1});
        } else {
            if (!is_true(right)) {
                if (!skip)
                    fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Modulo by zero");
                result = ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
                break;
            } else if (!result.is_unsigned && !right.is_unsigned) {
                if (!right.is_unsigned && get_sign(result) == INTMAX_MIN && get_sign(right) == -1) {
                    if (!skip)
                        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Integer constant expression overflow");
                    result = ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
                } else
                    result = ((ppIntValue){.value.sign = (get_sign(result) % get_sign(right)), .is_unsigned = 0});
            } else
                result = ((ppIntValue){.value.unsign = (get_unsign(result) % get_unsign(right)), .is_unsigned = 1});
        }
        t = pp_peek(ctx);
    }
    return result;
}
static ppIntValue eval_additive_expr(ppContext *ctx, _Bool skip) {
    ppIntValue result = eval_multiplicative_expr(ctx, skip);
    ppToken *t = pp_peek(ctx);
    while (!((t) == ((void *)0) || (t)->type == PP_EOF) && t->type == PP_SYMBOL && (t->value == SYMBOL_ADD || t->value == SYMBOL_SUB)) {
        t = pp_get(ctx);
        ppIntValue right = eval_multiplicative_expr(ctx, skip);
        if (t->value == SYMBOL_ADD) {
            if (!result.is_unsigned && !right.is_unsigned)
                result = ((ppIntValue){.value.sign = ((intmax_t)((uintmax_t)get_sign(result) + (uintmax_t)get_sign(right))), .is_unsigned = 0});
            else
                result = ((ppIntValue){.value.unsign = (get_unsign(result) + get_unsign(right)), .is_unsigned = 1});
        } else {
            if (!result.is_unsigned && !right.is_unsigned)
                result = ((ppIntValue){.value.sign = ((intmax_t)((uintmax_t)get_sign(result) - (uintmax_t)get_sign(right))), .is_unsigned = 0});
            else
                result = ((ppIntValue){.value.unsign = (get_unsign(result) - get_unsign(right)), .is_unsigned = 1});
        }
        t = pp_peek(ctx);
    }
    return result;
}
static ppIntValue eval_shift_expr(ppContext *ctx, _Bool skip) {
    ppIntValue result = eval_additive_expr(ctx, skip);
    ppToken *t = pp_peek(ctx);
    while (!((t) == ((void *)0) || (t)->type == PP_EOF) && t->type == PP_SYMBOL && (t->value == SYMBOL_L_SHIFT || t->value == SYMBOL_R_SHIFT)) {
        t = pp_get(ctx);
        ppIntValue right = eval_additive_expr(ctx, skip);
        uintmax_t n = 0;
        if (right.is_unsigned)
            n = get_unsign(right);
        else if (get_sign(right) < 0) {
            if (!skip) {
                fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Negative shift count");
                result = ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
                break;
            }
        } else
            n = (uintmax_t)get_sign(right);
        if (n >= sizeof(intmax_t) * CHAR_BIT) {
            if (!skip) {
                fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Shift count too large");
                result = ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
                break;
            }
            n = 0;
        }
        if (t->value == SYMBOL_L_SHIFT) {
            uintmax_t shifted = get_unsign(result) << n;
            if (!result.is_unsigned && shifted > (uintmax_t)INTMAX_MAX) {
                if (!skip)
                    fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Integer constant expression overflow");
                result = ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
                break;
            }
            result = result.is_unsigned ? ((ppIntValue){.value.unsign = (shifted), .is_unsigned = 1}) : ((ppIntValue){.value.sign = ((intmax_t)shifted), .is_unsigned = 0});
        } else {
            if (result.is_unsigned)
                result = ((ppIntValue){.value.unsign = (get_unsign(result) >> n), .is_unsigned = 1});
            else {
                intmax_t value = get_sign(result);
                if (value >= 0)
                    value >>= n;
                else {
                    uintmax_t magnitude = (uintmax_t)(-(value + 1)) + 1;
                    uintmax_t shifted = magnitude >> n;
                    if ((magnitude & ((((uintmax_t)1) << n) - 1)) != 0)
                        shifted++;
                    value = -(intmax_t)shifted;
                }
                result = ((ppIntValue){.value.sign = (value), .is_unsigned = 0});
            }
        }
        t = pp_peek(ctx);
    }
    return result;
}
static ppIntValue eval_relational_expr(ppContext *ctx, _Bool skip) {
    ppIntValue result = eval_shift_expr(ctx, skip);
    ppToken *t = pp_peek(ctx);
    while (!((t) == ((void *)0) || (t)->type == PP_EOF) && t->type == PP_SYMBOL && (t->value == SYMBOL_LT || t->value == SYMBOL_GT || t->value == SYMBOL_LE || t->value == SYMBOL_GE)) {
        t = pp_get(ctx);
        ppIntValue right = eval_shift_expr(ctx, skip);
        _Bool cmp;
        if (!result.is_unsigned && !right.is_unsigned) {
            intmax_t left_val = get_sign(result);
            intmax_t right_val = get_sign(right);
            if (t->value == SYMBOL_LT)
                cmp = left_val < right_val;
            else if (t->value == SYMBOL_GT)
                cmp = left_val > right_val;
            else if (t->value == SYMBOL_LE)
                cmp = left_val <= right_val;
            else
                cmp = left_val >= right_val;
        } else {
            uintmax_t left_val = get_unsign(result);
            uintmax_t right_val = get_unsign(right);
            if (t->value == SYMBOL_LT)
                cmp = left_val < right_val;
            else if (t->value == SYMBOL_GT)
                cmp = left_val > right_val;
            else if (t->value == SYMBOL_LE)
                cmp = left_val <= right_val;
            else
                cmp = left_val >= right_val;
        }
        result = cmp ? ((ppIntValue){.value.sign = (1), .is_unsigned = 0}) : ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
        t = pp_peek(ctx);
    }
    return result;
}
static ppIntValue eval_equality_expr(ppContext *ctx, _Bool skip) {
    ppIntValue result = eval_relational_expr(ctx, skip);
    ppToken *t = pp_peek(ctx);
    while (!((t) == ((void *)0) || (t)->type == PP_EOF) && t->type == PP_SYMBOL && (t->value == SYMBOL_EQ || t->value == SYMBOL_NE)) {
        t = pp_get(ctx);
        ppIntValue right = eval_relational_expr(ctx, skip);
        _Bool eq;
        if (!result.is_unsigned && !right.is_unsigned)
            eq = get_sign(result) == get_sign(right);
        else
            eq = get_unsign(result) == get_unsign(right);
        result = ((t->value == SYMBOL_EQ) == eq) ? ((ppIntValue){.value.sign = (1), .is_unsigned = 0}) : ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
        t = pp_peek(ctx);
    }
    return result;
}
static ppIntValue eval_and_expr(ppContext *ctx, _Bool skip) {
    ppIntValue result = eval_equality_expr(ctx, skip);
    ppToken *t = pp_peek(ctx);
    while (!((t) == ((void *)0) || (t)->type == PP_EOF) && t->type == PP_SYMBOL && t->value == SYMBOL_BITWISE_AND) {
        pp_get(ctx);
        ppIntValue right = eval_equality_expr(ctx, skip);
        if (!result.is_unsigned && !right.is_unsigned)
            result = ((ppIntValue){.value.sign = (get_sign(result) & get_sign(right)), .is_unsigned = 0});
        else
            result = ((ppIntValue){.value.unsign = (get_unsign(result) & get_unsign(right)), .is_unsigned = 1});
        t = pp_peek(ctx);
    }
    return result;
}
static ppIntValue eval_exclusive_or_expr(ppContext *ctx, _Bool skip) {
    ppIntValue result = eval_and_expr(ctx, skip);
    ppToken *t = pp_peek(ctx);
    while (!((t) == ((void *)0) || (t)->type == PP_EOF) && t->type == PP_SYMBOL && t->value == SYMBOL_XOR) {
        pp_get(ctx);
        ppIntValue right = eval_and_expr(ctx, skip);
        if (!result.is_unsigned && !right.is_unsigned)
            result = ((ppIntValue){.value.sign = (get_sign(result) ^ get_sign(right)), .is_unsigned = 0});
        else
            result = ((ppIntValue){.value.unsign = (get_unsign(result) ^ get_unsign(right)), .is_unsigned = 1});
        t = pp_peek(ctx);
    }
    return result;
}
static ppIntValue eval_inclusive_or_expr(ppContext *ctx, _Bool skip) {
    ppIntValue result = eval_exclusive_or_expr(ctx, skip);
    ppToken *t = pp_peek(ctx);
    while (!((t) == ((void *)0) || (t)->type == PP_EOF) && t->type == PP_SYMBOL && t->value == SYMBOL_BITWISE_OR) {
        pp_get(ctx);
        ppIntValue right = eval_exclusive_or_expr(ctx, skip);
        if (!result.is_unsigned && !right.is_unsigned)
            result = ((ppIntValue){.value.sign = (get_sign(result) | get_sign(right)), .is_unsigned = 0});
        else
            result = ((ppIntValue){.value.unsign = (get_unsign(result) | get_unsign(right)), .is_unsigned = 1});
        t = pp_peek(ctx);
    }
    return result;
}
static ppIntValue eval_logic_and_expr(ppContext *ctx, _Bool skip) {
    ppIntValue result = eval_inclusive_or_expr(ctx, skip);
    ppToken *t = pp_peek(ctx);
    while (!((t) == ((void *)0) || (t)->type == PP_EOF) && t->type == PP_SYMBOL && t->value == SYMBOL_LOGICAL_AND) {
        pp_get(ctx);
        if (is_true(result))
            result = pp_bool(eval_inclusive_or_expr(ctx, skip));
        else {
            eval_inclusive_or_expr(ctx, 1);
            result = ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
        }
        t = pp_peek(ctx);
    }
    return result;
}
static ppIntValue eval_logic_or_expr(ppContext *ctx, _Bool skip) {
    ppIntValue result = eval_logic_and_expr(ctx, skip);
    ppToken *t = pp_peek(ctx);
    while (!((t) == ((void *)0) || (t)->type == PP_EOF) && t->type == PP_SYMBOL && t->value == SYMBOL_LOGICAL_OR) {
        pp_get(ctx);
        if (!is_true(result))
            result = pp_bool(eval_logic_and_expr(ctx, skip));
        else {
            eval_logic_and_expr(ctx, 1);
            result = ((ppIntValue){.value.sign = (1), .is_unsigned = 0});
        }
        t = pp_peek(ctx);
    }
    return result;
}
static ppIntValue eval_conditional_expr(ppContext *ctx, _Bool skip) {
    ppIntValue result = eval_logic_or_expr(ctx, skip);
    ppToken *t = pp_peek(ctx);
    if (!((t) == ((void *)0) || (t)->type == PP_EOF) && t->type == PP_SYMBOL && t->value == SYMBOL_QUESTION) {
        pp_get(ctx);
        ppIntValue skipped = result.is_unsigned ? ((ppIntValue){.value.unsign = (0), .is_unsigned = 1}) : ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
        if (is_true(result)) {
            result = eval_conditional_expr(ctx, skip);
            t = pp_peek(ctx);
            if (!expect_token(ctx, "Expected : in conditional expression", t->line, t->column, PP_SYMBOL, SYMBOL_COLON))
                result = ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
            else
                skipped = eval_conditional_expr(ctx, 1);
        } else {
            skipped = eval_conditional_expr(ctx, 1);
            t = pp_peek(ctx);
            if (!expect_token(ctx, "Expected : in conditional expression", t->line, t->column, PP_SYMBOL, SYMBOL_COLON))
                result = ((ppIntValue){.value.sign = (0), .is_unsigned = 0});
            else
                result = eval_conditional_expr(ctx, skip);
        }
        if (skipped.is_unsigned && !result.is_unsigned)
            result = ((ppIntValue){.value.unsign = ((uintmax_t)get_sign(result)), .is_unsigned = 1});
    }
    return result;
}
_Bool eval_conditional(ppContext *ctx, _Bool *eval_error) {
    has_error = 0;
    _Bool result = is_true(eval_conditional_expr(ctx, 0));
    ppToken *t = pp_peek(ctx);
    if (!((t) == ((void *)0) || (t)->type == PP_EOF) && t->type != PP_NEWLINE)
        fprintf(stderr, "[Preprocess Error] at %s:%zu:%zu: %s\n", (has_error = 1, ctx->lexer->filename), t->line, t->column, "Unexpected token after conditional expression");
    if (has_error) {
        *eval_error = 1;
        return 0;
    }
    return result;
}
