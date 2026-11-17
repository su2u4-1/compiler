#ifndef LIB_H
#define LIB_H

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// other

typedef char* string;
typedef void* ptr;
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

void init(void);
string get_source(string path);

#if defined(__clang__)
__attribute__((format(printf, 1, 2)))
#elif defined(__GNUC__)
__attribute__((format(gnu_printf, 1, 2)))
#endif
string string_splice(string format, ...);

#define MAX_INCLUDE_DEPTH 200

#ifdef _WIN32
#define WIN_PATH 1
#else
#define WIN_PATH 0
#endif

// memory

#define DEFAULT_MEMORY_SIZE 4096
#define ALIGN_SIZE _Alignof(max_align_t)

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

#define create_struct(T) (T*)alloc_memory(sizeof(T), true)
void free_all_memory(void);
string create_string(const char* str, size_t len);
ptr alloc_memory(size_t size, bool is_struct);

// list

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
// clang-format off
#define TYPE_TABLE string: LIST_TYPE_string,                   \
        ppToken*: LIST_TYPE_ppToken,                           \
        ppMacro*: LIST_TYPE_ppMacro,                           \
        ppCondFrame*: LIST_TYPE_ppCondFrame,                   \
        List_ppToken*: LIST_TYPE_List_ppToken,                 \
        Token*: LIST_TYPE_Token,                               \
        AST_ExternDecl*: LIST_TYPE_AST_ExternDecl,                     \
        AST_DeclSpec*: LIST_TYPE_AST_DeclSpec,                         \
        AST_InitDecl*: LIST_TYPE_AST_InitDecl,                         \
        AST_ParamDecl*: LIST_TYPE_AST_ParamDecl,                       \
        AST_StructDecl*: LIST_TYPE_AST_StructDecl,                     \
        AST_Enumerator*: LIST_TYPE_AST_Enumerator,                     \
        AST_InitializerItem*: LIST_TYPE_AST_InitializerItem,           \
        AST_Designator*: LIST_TYPE_AST_Designator,                     \
        AST_SpecifierQualifier*: LIST_TYPE_AST_SpecifierQualifier,     \
        AST_StructDeclarator*: LIST_TYPE_AST_StructDeclarator,         \
        AST_DeclStmt*: LIST_TYPE_AST_DeclStmt,                         \
        AST_AssignmentExpression*: LIST_TYPE_AST_AssignmentExpression, \
        AST_GenericAssociation*: LIST_TYPE_AST_GenericAssociation,     \
        AST_TypeName*: LIST_TYPE_AST_TypeName,                         \
        AST_Symbol*: LIST_TYPE_AST_Symbol
// clang-format on
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

#define list_concat(T) List_##T
#define list(T) list_concat(T)
#define create_list(T) list_create(_Generic((T)0, TYPE_TABLE))
#define list_empty(self) ((self) == NULL || (self)->head == NULL)
#define append(lst, item) list_append((lst), (void*)(item), _Generic((item), TYPE_TABLE))
#define pop_front(lst, T) ((T)list_pop_front((lst), _Generic((T)0, TYPE_TABLE)))
#define pop_back(lst, T) ((T)list_pop_back((lst), _Generic((T)0, TYPE_TABLE)))
#define peek_front(lst, T) ((T)list_peek_front((lst), _Generic((T)0, TYPE_TABLE)))
#define peek_back(lst, T) ((T)list_peek_back((lst), _Generic((T)0, TYPE_TABLE)))
#define foreach(type, item, lst)                                                                    \
    for (List* item##__l = (lst); item##__l != NULL && item##__l->head != NULL; item##__l = NULL)   \
        for (ListNode* item##__n = item##__l->head; item##__n != NULL; item##__n = item##__n->next) \
            for (type item = (type)item##__n->data; item != NULL; item = NULL)

// literal

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
    bool overflow;
} IntLiteral;

int hex_digit_value(char c);
IntLiteral parse_int_digits(const char* s);
EscapeResult decode_literal_char(const char* s, size_t* pos, unsigned int* value);
const char* escape_message(EscapeResult result);

// constants

#define keyword_count 44
extern string keywordList[keyword_count];

extern string KEYWORD_ALIGNAS;        // keyword `_Alignas`
extern string KEYWORD_ALIGNOF;        // keyword `_Alignof`
extern string KEYWORD_ATOMIC;         // keyword `_Atomic`
extern string KEYWORD_BOOL;           // keyword `_Bool`
extern string KEYWORD_COMPLEX;        // keyword `_Complex`
extern string KEYWORD_GENERIC;        // keyword `_Generic`
extern string KEYWORD_IMAGINARY;      // keyword `_Imaginary`
extern string KEYWORD_NORETURN;       // keyword `_Noreturn`
extern string KEYWORD_STATIC_ASSERT;  // keyword `_Static_assert`
extern string KEYWORD_THREAD_LOCAL;   // keyword `_Thread_local`
extern string KEYWORD_AUTO;           // keyword `auto`
extern string KEYWORD_BREAK;          // keyword `break`
extern string KEYWORD_CASE;           // keyword `case`
extern string KEYWORD_CHAR;           // keyword `char`
extern string KEYWORD_CONST;          // keyword `const`
extern string KEYWORD_CONTINUE;       // keyword `continue`
extern string KEYWORD_DEFAULT;        // keyword `default`
extern string KEYWORD_DO;             // keyword `do`
extern string KEYWORD_DOUBLE;         // keyword `double`
extern string KEYWORD_ELSE;           // keyword `else`
extern string KEYWORD_ENUM;           // keyword `enum`
extern string KEYWORD_EXTERN;         // keyword `extern`
extern string KEYWORD_FLOAT;          // keyword `float`
extern string KEYWORD_FOR;            // keyword `for`
extern string KEYWORD_GOTO;           // keyword `goto`
extern string KEYWORD_IF;             // keyword `if`
extern string KEYWORD_INLINE;         // keyword `inline`
extern string KEYWORD_INT;            // keyword `int`
extern string KEYWORD_LONG;           // keyword `long`
extern string KEYWORD_REGISTER;       // keyword `register`
extern string KEYWORD_RESTRICT;       // keyword `restrict`
extern string KEYWORD_RETURN;         // keyword `return`
extern string KEYWORD_SHORT;          // keyword `short`
extern string KEYWORD_SIGNED;         // keyword `signed`
extern string KEYWORD_SIZEOF;         // keyword `sizeof`
extern string KEYWORD_STATIC;         // keyword `static`
extern string KEYWORD_STRUCT;         // keyword `struct`
extern string KEYWORD_SWITCH;         // keyword `switch`
extern string KEYWORD_TYPEDEF;        // keyword `typedef`
extern string KEYWORD_UNION;          // keyword `union`
extern string KEYWORD_UNSIGNED;       // keyword `unsigned`
extern string KEYWORD_VOID;           // keyword `void`
extern string KEYWORD_VOLATILE;       // keyword `volatile`
extern string KEYWORD_WHILE;          // keyword `while`
extern string SYMBOL_SEMICOLON;       // symbol `;`
extern string SYMBOL_COMMA;           // symbol `,`
extern string SYMBOL_L_BRACE;         // symbol `{`
extern string SYMBOL_R_BRACE;         // symbol `}`
extern string SYMBOL_L_PARENTHESIS;   // symbol `(`
extern string SYMBOL_R_PARENTHESIS;   // symbol `)`
extern string SYMBOL_L_BRACKET;       // symbol `[`
extern string SYMBOL_R_BRACKET;       // symbol `]`
extern string SYMBOL_COLON;           // symbol `:`
extern string SYMBOL_QUESTION;        // symbol `?`
extern string SYMBOL_ELLIPSIS;        // symbol `...`
extern string SYMBOL_DOT;             // symbol `.`
extern string SYMBOL_ARROW;           // symbol `->`
extern string SYMBOL_MUL;             // symbol `*`
extern string SYMBOL_BITWISE_AND;     // symbol `&`
extern string SYMBOL_ASSIGN;          // symbol `=`
extern string SYMBOL_INCREMENT;       // symbol `++`
extern string SYMBOL_DECREMENT;       // symbol `--`
extern string SYMBOL_ADD;             // symbol `+`
extern string SYMBOL_SUB;             // symbol `-`
extern string SYMBOL_DIV;             // symbol `/`
extern string SYMBOL_MOD;             // symbol `%`
extern string SYMBOL_LOGICAL_NOT;     // symbol `!`
extern string SYMBOL_BITWISE_NOT;     // symbol `~`
extern string SYMBOL_XOR;             // symbol `^`
extern string SYMBOL_BITWISE_OR;      // symbol `|`
extern string SYMBOL_LT;              // symbol `<`
extern string SYMBOL_GT;              // symbol `>`
extern string SYMBOL_L_SHIFT;         // symbol `<<`
extern string SYMBOL_R_SHIFT;         // symbol `>>`
extern string SYMBOL_LE;              // symbol `<=`
extern string SYMBOL_GE;              // symbol `>=`
extern string SYMBOL_EQ;              // symbol `==`
extern string SYMBOL_NE;              // symbol `!=`
extern string SYMBOL_LOGICAL_AND;     // symbol `&&`
extern string SYMBOL_LOGICAL_OR;      // symbol `||`
extern string SYMBOL_ADD_ASSIGN;      // symbol `+=`
extern string SYMBOL_SUB_ASSIGN;      // symbol `-=`
extern string SYMBOL_MUL_ASSIGN;      // symbol `*=`
extern string SYMBOL_DIV_ASSIGN;      // symbol `/=`
extern string SYMBOL_MOD_ASSIGN;      // symbol `%=`
extern string SYMBOL_L_SHIFT_ASSIGN;  // symbol `<<=`
extern string SYMBOL_R_SHIFT_ASSIGN;  // symbol `>>=`
extern string SYMBOL_AND_ASSIGN;      // symbol `&=`
extern string SYMBOL_XOR_ASSIGN;      // symbol `^=`
extern string SYMBOL_OR_ASSIGN;       // symbol `|=`
extern string SYMBOL_HASH;            // symbol `#`
extern string SYMBOL_DOUBLE_HASH;     // symbol `##`
extern string P_DEFINED;              // preprocessor `defined`
extern string P_DEFINE;               // preprocessor `define`
extern string P_UNDEF;                // preprocessor `undef`
extern string P_IF;                   // preprocessor `if`
extern string P_IFDEF;                // preprocessor `ifdef`
extern string P_IFNDEF;               // preprocessor `ifndef`
extern string P_ELIF;                 // preprocessor `elif`
extern string P_ELSE;                 // preprocessor `else`
extern string P_ENDIF;                // preprocessor `endif`
extern string P_INCLUDE;              // preprocessor `include`
extern string P_LINE;                 // preprocessor `line`
extern string P_ERROR;                // preprocessor `error`
extern string P_PRAGMA;               // preprocessor `pragma`
extern string P_VA_ARGS_;             // preprocessor `__VA_ARGS__`
extern string P_FILE_;                // preprocessor `__FILE__`
extern string P_LINE_;                // preprocessor `__LINE__`
extern string P_DATE_;                // preprocessor `__DATE__`
extern string P_TIME_;                // preprocessor `__TIME__`
extern string P_STDC_;                // preprocessor `__STDC__`
extern string P_STDC_VERSION_;        // preprocessor `__STDC_VERSION__`
extern string P_STDC_HOSTED_;         // preprocessor `__STDC_HOSTED__`
extern string P_PRAGMA_;              // preprocessor `_Pragma`

#endif  // LIB_H
