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
MemoryBlock *string_memory = ((void *)0);
MemoryBlock *struct_memory = ((void *)0);
static size_t malloc_allocated = 0;
static size_t string_count = 0;
static StringTable *string_table = ((void *)0);
void free_all_memory(void) {
    MemoryBlock *block = string_memory;
    while (block != ((void *)0)) {
        MemoryBlock *next = block->next;
        free(block->data);
        free(block);
        block = next;
    }
    string_memory = ((void *)0);
    block = struct_memory;
    while (block != ((void *)0)) {
        MemoryBlock *next = block->next;
        free(block->data);
        free(block);
        block = next;
    }
    struct_memory = ((void *)0);
}
static MemoryBlock *create_memory_block(size_t size) {
    MemoryBlock *block = malloc(sizeof(MemoryBlock));
    if (block == ((void *)0)) {
        fprintf(stderr, "[lib Fatal] at <create_memory_block>: Cannot allocate memory\n");
        free_all_memory();
        abort();
    }
    malloc_allocated += sizeof(MemoryBlock);
    block->size = size;
    block->used = 0;
    block->data = calloc(1, size);
    if (block->data == ((void *)0)) {
        fprintf(stderr, "[lib Fatal] at <create_memory_block>: Cannot allocate memory\n");
        free(block);
        free_all_memory();
        abort();
    }
    malloc_allocated += size;
    block->next = ((void *)0);
    return block;
}
static void add_memory_block(MemoryBlock **block, size_t size) {
    MemoryBlock *new_block = ((void *)0);
    if (size >= 4096) {
        if (size % 4096 != 0)
            size = (size / 4096 + 1) * 4096;
        new_block = create_memory_block(size);
    } else
        new_block = create_memory_block(4096);
    new_block->next = *block;
    *block = new_block;
}
static StringTable *create_string_table(size_t capacity) {
    StringTable *table = (StringTable *)alloc_memory(sizeof(StringTable), 1);
    table->capacity = capacity;
    table->count = 0;
    table->buckets = calloc(capacity, sizeof(StringNode *));
    return table;
}
ptr alloc_memory(size_t size, _Bool is_struct) {
    if (size >= 4096)
        add_memory_block(is_struct ? &struct_memory : &string_memory, size);
    MemoryBlock *block = string_memory;
    if (is_struct) {
        block = struct_memory;
        size = (size + _Alignof(max_align_t) - 1) & ~(_Alignof(max_align_t) - 1);
    }
    while (block != ((void *)0)) {
        if (block->size - block->used >= size) {
            ptr ptr = (void *)(block->data + block->used);
            if (is_struct)
                assert((size_t)ptr % _Alignof(max_align_t) == 0);
            block->used += size;
            return ptr;
        }
        block = block->next;
    }
    if (is_struct)
        add_memory_block(&struct_memory, size);
    else
        add_memory_block(&string_memory, size);
    return alloc_memory(size, is_struct);
}
static size_t hash(const char *str, size_t len) {
    size_t hash_value = 2166136261;
    for (size_t i = 0; i < len; i++) {
        hash_value ^= (unsigned char)str[i];
        hash_value *= 16777619;
    }
    return hash_value;
}
static string create_string_check(const char *str, size_t len, _Bool check) {
    size_t hash_value = hash(str, len);
    size_t index = hash_value % string_table->capacity;
    if (check) {
        StringNode *current = string_table->buckets[index];
        while (current != ((void *)0)) {
            if (current->size == len && current->hash == hash_value && memcmp(current->value, str, len) == 0)
                return current->value;
            current = current->next;
        }
    }
    StringNode *node = (StringNode *)alloc_memory(sizeof(StringNode), 1);
    node->size = len;
    node->hash = hash_value;
    node->next = string_table->buckets[index];
    node->value = (string)alloc_memory(len + 1, 0);
    memcpy(node->value, str, len);
    node->value[len] = '\0';
    string_table->buckets[index] = node;
    string_table->count++;
    string_count++;
    return node->value;
}
string create_string(const char *str, size_t len) {
    return create_string_check(str, len, 1);
}
string get_source(string path) {
    FILE *file = fopen(path, "rb");
    if (file == ((void *)0))
        return ((void *)0);
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return ((void *)0);
    }
    long n = ftell(file);
    if (n < 0 || n > (1L << 30)) {
        fclose(file);
        return ((void *)0);
    }
    rewind(file);
    size_t size = (size_t)n;
    string source_code = (string)alloc_memory(size + 1, 0);
    size_t got = fread(source_code, 1, size, file);
    _Bool failed = ferror(file);
    fclose(file);
    if (failed)
        return ((void *)0);
    source_code[got] = '\0';
    return source_code;
}
typedef void *va_list;
string string_splice(string format, ...) {
    va_list args;
    va_start(args, format);
    int length = vsnprintf(((void *)0), 0, format, args);
    va_end(args);
    if (length <= 0) {
        fprintf(stderr, "[lib Error] at <string_splice>: Failed to format string\n");
        return ((void *)0);
    }
    char *name = malloc((size_t)length + 1);
    if (name == ((void *)0)) {
        fprintf(stderr, "[lib Fatal] at <string_splice>: Cannot allocate memory\n");
        free_all_memory();
        abort();
    }
    va_start(args, format);
    vsnprintf(name, (size_t)length + 1, format, args);
    va_end(args);
    string result = create_string(name, (size_t)length);
    free(name);
    return result;
}
static void init_constant(void);
void init(void) {
    if (string_memory == ((void *)0))
        string_memory = create_memory_block(4096);
    if (struct_memory == ((void *)0))
        struct_memory = create_memory_block(4096);
    if (string_table == ((void *)0))
        string_table = create_string_table(4096);
    init_constant();
}
List *list_create(int type_id) {
    List *self = (List *)alloc_memory(sizeof(List), 1);
    if (self == ((void *)0))
        return ((void *)0);
    self->head = ((void *)0);
    self->tail = ((void *)0);
    self->type_id = type_id;
    return self;
}
int list_append(List *self, void *item, int type_id) {
    if (self == ((void *)0))
        return 1;
    if (self->type_id != type_id) {
        fprintf(stderr, "[lib Error] at <list_append>: type mismatch: list has %d, got %d\n", self->type_id, type_id);
        return 1;
    }
    ListNode *node = (ListNode *)alloc_memory(sizeof(ListNode), 1);
    if (node == ((void *)0))
        return 1;
    node->data = item;
    node->next = ((void *)0);
    if (self->tail != ((void *)0))
        self->tail->next = node;
    else
        self->head = node;
    self->tail = node;
    return 0;
}
void *list_pop_front(List *self, int type_id) {
    if (((self) == ((void *)0) || (self)->head == ((void *)0)))
        return ((void *)0);
    if (self->type_id != type_id) {
        fprintf(stderr, "[lib Error at <list_pop>: type mismatch: list has %d, got %d\n", self->type_id, type_id);
        return ((void *)0);
    }
    void *data = self->head->data;
    self->head = self->head->next;
    if (self->head == ((void *)0))
        self->tail = ((void *)0);
    return data;
}
void *list_pop_back(List *self, int type_id) {
    if (((self) == ((void *)0) || (self)->head == ((void *)0)))
        return ((void *)0);
    if (self->type_id != type_id) {
        fprintf(stderr, "[lib Error at <list_pop_back>: type mismatch: list has %d, got %d\n", self->type_id, type_id);
        return ((void *)0);
    }
    void *data = self->tail->data;
    if (self->head == self->tail) {
        self->head = ((void *)0);
        self->tail = ((void *)0);
    } else {
        ListNode *current = self->head;
        while (current->next != self->tail) {
            current = current->next;
        }
        current->next = ((void *)0);
        self->tail = current;
    }
    return data;
}
void *list_peek_front(List *self, int type_id) {
    if (((self) == ((void *)0) || (self)->head == ((void *)0)))
        return ((void *)0);
    if (self->type_id != type_id) {
        fprintf(stderr, "[lib Error at <list_peek_front>: type mismatch: list has %d, got %d\n", self->type_id, type_id);
        return ((void *)0);
    }
    return self->head->data;
}
void *list_peek_back(List *self, int type_id) {
    if (((self) == ((void *)0) || (self)->head == ((void *)0)))
        return ((void *)0);
    if (self->type_id != type_id) {
        fprintf(stderr, "[lib Error at <list_peek_back>: type mismatch: list has %d, got %d\n", self->type_id, type_id);
        return ((void *)0);
    }
    return self->tail->data;
}
int hex_digit_value(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return -1;
}
IntLiteral parse_int_digits(const char *s) {
    IntLiteral result = { .base = 10 };
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        result.base = 16;
        result.digits_start = 2;
    } else if (s[0] == '0' && (s[1] == 'b' || s[1] == 'B')) {
        result.base = 2;
        result.digits_start = 2;
    } else if (s[0] == '0') {
        result.base = 8;
    }
    size_t i = result.digits_start;
    for (;; ++i) {
        int d = hex_digit_value(s[i]);
        if (d < 0 || (unsigned int)d >= result.base)
            break;
        if (result.value > (UINTMAX_MAX - (uintmax_t)d) / result.base)
            result.overflow = 1;
        result.value = result.value * result.base + (uintmax_t)d;
    }
    result.digits_end = i;
    return result;
}
EscapeResult decode_literal_char(const char *s, size_t *pos, unsigned int *value) {
    if (s[*pos] != '\\') {
        *value = (unsigned char)s[(*pos)++];
        return ESC_OK;
    }
    ++*pos;
    *value = 0;
    char c = s[*pos];
    if (c == '\0')
        return ESC_UNKNOWN;
    ++*pos;
    switch (c) {
    case 'a':
        *value = 7;
        return ESC_OK;
    case 'b':
        *value = 8;
        return ESC_OK;
    case 'f':
        *value = 12;
        return ESC_OK;
    case 'n':
        *value = 10;
        return ESC_OK;
    case 'r':
        *value = 13;
        return ESC_OK;
    case 't':
        *value = 9;
        return ESC_OK;
    case 'v':
        *value = 11;
        return ESC_OK;
    case 'e':
    case 'E':
        *value = 27;
        return ESC_OK;
    case '(':
    case '{':
    case '[':
    case '%':
    case '\\':
    case '\'':
    case '"':
    case '?':
        *value = (unsigned char)c;
        return ESC_OK;
    case 'u':
    case 'U':
        return ESC_UNSUPPORTED;
    case 'x':
        {
            if (hex_digit_value(s[*pos]) < 0)
                return ESC_NO_HEX_DIGITS;
            _Bool out_of_range = 0;
            unsigned int v = 0;
            while (hex_digit_value(s[*pos]) >= 0) {
                v = v * 16 + (unsigned int)hex_digit_value(s[*pos]);
                if (v > UCHAR_MAX) {
                    out_of_range = 1;
                    v &= UCHAR_MAX;
                }
                ++*pos;
            }
            *value = v;
            return out_of_range ? ESC_HEX_OUT_OF_RANGE : ESC_OK;
        }
    default:
        {
            if (c < '0' || c > '7') {
                *value = (unsigned char)c;
                return ESC_UNKNOWN;
            }
            unsigned int v = (unsigned int)(c - '0');
            for (int i = 0; i < 2 && s[*pos] >= '0' && s[*pos] <= '7'; ++i) {
                v = v * 8 + (unsigned int)(s[*pos] - '0');
                ++*pos;
            }
            *value = v & UCHAR_MAX;
            return v > UCHAR_MAX ? ESC_OCT_OUT_OF_RANGE : ESC_OK;
        }
    }
}
const char *escape_message(EscapeResult result) {
    switch (result) {
    case ESC_UNKNOWN:
        return "Unknown escape sequence";
    case ESC_NO_HEX_DIGITS:
        return "\\x used with no following hex digits";
    case ESC_HEX_OUT_OF_RANGE:
        return "Hex escape sequence out of range";
    case ESC_OCT_OUT_OF_RANGE:
        return "Octal escape sequence out of range";
    case ESC_UNSUPPORTED:
        return "Universal character name is not supported";
    case ESC_OK:
    default:
        return ((void *)0);
    }
}
static const char *keywordStrings[44] = { "_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary", "_Noreturn", "_Static_assert", "_Thread_local", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while" };
string keywordList[44] = { 0 };
string KEYWORD_ALIGNAS = ((void *)0);
string KEYWORD_ALIGNOF = ((void *)0);
string KEYWORD_ATOMIC = ((void *)0);
string KEYWORD_BOOL = ((void *)0);
string KEYWORD_COMPLEX = ((void *)0);
string KEYWORD_GENERIC = ((void *)0);
string KEYWORD_IMAGINARY = ((void *)0);
string KEYWORD_NORETURN = ((void *)0);
string KEYWORD_STATIC_ASSERT = ((void *)0);
string KEYWORD_THREAD_LOCAL = ((void *)0);
string KEYWORD_AUTO = ((void *)0);
string KEYWORD_BREAK = ((void *)0);
string KEYWORD_CASE = ((void *)0);
string KEYWORD_CHAR = ((void *)0);
string KEYWORD_CONST = ((void *)0);
string KEYWORD_CONTINUE = ((void *)0);
string KEYWORD_DEFAULT = ((void *)0);
string KEYWORD_DO = ((void *)0);
string KEYWORD_DOUBLE = ((void *)0);
string KEYWORD_ELSE = ((void *)0);
string KEYWORD_ENUM = ((void *)0);
string KEYWORD_EXTERN = ((void *)0);
string KEYWORD_FLOAT = ((void *)0);
string KEYWORD_FOR = ((void *)0);
string KEYWORD_GOTO = ((void *)0);
string KEYWORD_IF = ((void *)0);
string KEYWORD_INLINE = ((void *)0);
string KEYWORD_INT = ((void *)0);
string KEYWORD_LONG = ((void *)0);
string KEYWORD_REGISTER = ((void *)0);
string KEYWORD_RESTRICT = ((void *)0);
string KEYWORD_RETURN = ((void *)0);
string KEYWORD_SHORT = ((void *)0);
string KEYWORD_SIGNED = ((void *)0);
string KEYWORD_SIZEOF = ((void *)0);
string KEYWORD_STATIC = ((void *)0);
string KEYWORD_STRUCT = ((void *)0);
string KEYWORD_SWITCH = ((void *)0);
string KEYWORD_TYPEDEF = ((void *)0);
string KEYWORD_UNION = ((void *)0);
string KEYWORD_UNSIGNED = ((void *)0);
string KEYWORD_VOID = ((void *)0);
string KEYWORD_VOLATILE = ((void *)0);
string KEYWORD_WHILE = ((void *)0);
string SYMBOL_SEMICOLON = ((void *)0);
string SYMBOL_COMMA = ((void *)0);
string SYMBOL_L_BRACE = ((void *)0);
string SYMBOL_R_BRACE = ((void *)0);
string SYMBOL_L_PARENTHESIS = ((void *)0);
string SYMBOL_R_PARENTHESIS = ((void *)0);
string SYMBOL_L_BRACKET = ((void *)0);
string SYMBOL_R_BRACKET = ((void *)0);
string SYMBOL_COLON = ((void *)0);
string SYMBOL_QUESTION = ((void *)0);
string SYMBOL_ELLIPSIS = ((void *)0);
string SYMBOL_DOT = ((void *)0);
string SYMBOL_ARROW = ((void *)0);
string SYMBOL_MUL = ((void *)0);
string SYMBOL_BITWISE_AND = ((void *)0);
string SYMBOL_ASSIGN = ((void *)0);
string SYMBOL_INCREMENT = ((void *)0);
string SYMBOL_DECREMENT = ((void *)0);
string SYMBOL_ADD = ((void *)0);
string SYMBOL_SUB = ((void *)0);
string SYMBOL_DIV = ((void *)0);
string SYMBOL_MOD = ((void *)0);
string SYMBOL_LOGICAL_NOT = ((void *)0);
string SYMBOL_BITWISE_NOT = ((void *)0);
string SYMBOL_XOR = ((void *)0);
string SYMBOL_BITWISE_OR = ((void *)0);
string SYMBOL_LT = ((void *)0);
string SYMBOL_GT = ((void *)0);
string SYMBOL_L_SHIFT = ((void *)0);
string SYMBOL_R_SHIFT = ((void *)0);
string SYMBOL_LE = ((void *)0);
string SYMBOL_GE = ((void *)0);
string SYMBOL_EQ = ((void *)0);
string SYMBOL_NE = ((void *)0);
string SYMBOL_LOGICAL_AND = ((void *)0);
string SYMBOL_LOGICAL_OR = ((void *)0);
string SYMBOL_ADD_ASSIGN = ((void *)0);
string SYMBOL_SUB_ASSIGN = ((void *)0);
string SYMBOL_MUL_ASSIGN = ((void *)0);
string SYMBOL_DIV_ASSIGN = ((void *)0);
string SYMBOL_MOD_ASSIGN = ((void *)0);
string SYMBOL_L_SHIFT_ASSIGN = ((void *)0);
string SYMBOL_R_SHIFT_ASSIGN = ((void *)0);
string SYMBOL_AND_ASSIGN = ((void *)0);
string SYMBOL_XOR_ASSIGN = ((void *)0);
string SYMBOL_OR_ASSIGN = ((void *)0);
string SYMBOL_HASH = ((void *)0);
string SYMBOL_DOUBLE_HASH = ((void *)0);
string P_DEFINE = ((void *)0);
string P_DEFINED = ((void *)0);
string P_UNDEF = ((void *)0);
string P_IF = ((void *)0);
string P_IFDEF = ((void *)0);
string P_IFNDEF = ((void *)0);
string P_ELIF = ((void *)0);
string P_ELSE = ((void *)0);
string P_ENDIF = ((void *)0);
string P_INCLUDE = ((void *)0);
string P_LINE = ((void *)0);
string P_ERROR = ((void *)0);
string P_PRAGMA = ((void *)0);
string P_VA_ARGS_ = ((void *)0);
string P_FILE_ = ((void *)0);
string P_LINE_ = ((void *)0);
string P_DATE_ = ((void *)0);
string P_TIME_ = ((void *)0);
string P_STDC_ = ((void *)0);
string P_STDC_VERSION_ = ((void *)0);
string P_STDC_HOSTED_ = ((void *)0);
string P_PRAGMA_ = ((void *)0);
void init_constant(void) {
    for (size_t i = 0; i < 44; ++i) {
        keywordList[i] = create_string_check(keywordStrings[i], strlen(keywordStrings[i]), 0);
    }
    KEYWORD_ALIGNAS = keywordList[0];
    KEYWORD_ALIGNOF = keywordList[1];
    KEYWORD_ATOMIC = keywordList[2];
    KEYWORD_BOOL = keywordList[3];
    KEYWORD_COMPLEX = keywordList[4];
    KEYWORD_GENERIC = keywordList[5];
    KEYWORD_IMAGINARY = keywordList[6];
    KEYWORD_NORETURN = keywordList[7];
    KEYWORD_STATIC_ASSERT = keywordList[8];
    KEYWORD_THREAD_LOCAL = keywordList[9];
    KEYWORD_AUTO = keywordList[10];
    KEYWORD_BREAK = keywordList[11];
    KEYWORD_CASE = keywordList[12];
    KEYWORD_CHAR = keywordList[13];
    KEYWORD_CONST = keywordList[14];
    KEYWORD_CONTINUE = keywordList[15];
    KEYWORD_DEFAULT = keywordList[16];
    KEYWORD_DO = keywordList[17];
    KEYWORD_DOUBLE = keywordList[18];
    KEYWORD_ELSE = keywordList[19];
    KEYWORD_ENUM = keywordList[20];
    KEYWORD_EXTERN = keywordList[21];
    KEYWORD_FLOAT = keywordList[22];
    KEYWORD_FOR = keywordList[23];
    KEYWORD_GOTO = keywordList[24];
    KEYWORD_IF = keywordList[25];
    KEYWORD_INLINE = keywordList[26];
    KEYWORD_INT = keywordList[27];
    KEYWORD_LONG = keywordList[28];
    KEYWORD_REGISTER = keywordList[29];
    KEYWORD_RESTRICT = keywordList[30];
    KEYWORD_RETURN = keywordList[31];
    KEYWORD_SHORT = keywordList[32];
    KEYWORD_SIGNED = keywordList[33];
    KEYWORD_SIZEOF = keywordList[34];
    KEYWORD_STATIC = keywordList[35];
    KEYWORD_STRUCT = keywordList[36];
    KEYWORD_SWITCH = keywordList[37];
    KEYWORD_TYPEDEF = keywordList[38];
    KEYWORD_UNION = keywordList[39];
    KEYWORD_UNSIGNED = keywordList[40];
    KEYWORD_VOID = keywordList[41];
    KEYWORD_VOLATILE = keywordList[42];
    KEYWORD_WHILE = keywordList[43];
    SYMBOL_SEMICOLON = create_string_check(";", 1, 0);
    SYMBOL_COMMA = create_string_check(",", 1, 0);
    SYMBOL_L_BRACE = create_string_check("{", 1, 0);
    SYMBOL_R_BRACE = create_string_check("}", 1, 0);
    SYMBOL_L_PARENTHESIS = create_string_check("(", 1, 0);
    SYMBOL_R_PARENTHESIS = create_string_check(")", 1, 0);
    SYMBOL_L_BRACKET = create_string_check("[", 1, 0);
    SYMBOL_R_BRACKET = create_string_check("]", 1, 0);
    SYMBOL_COLON = create_string_check(":", 1, 0);
    SYMBOL_QUESTION = create_string_check("?", 1, 0);
    SYMBOL_ELLIPSIS = create_string_check("...", 3, 0);
    SYMBOL_DOT = create_string_check(".", 1, 0);
    SYMBOL_ARROW = create_string_check("->", 2, 0);
    SYMBOL_MUL = create_string_check("*", 1, 0);
    SYMBOL_BITWISE_AND = create_string_check("&", 1, 0);
    SYMBOL_ASSIGN = create_string_check("=", 1, 0);
    SYMBOL_INCREMENT = create_string_check("++", 2, 0);
    SYMBOL_DECREMENT = create_string_check("--", 2, 0);
    SYMBOL_ADD = create_string_check("+", 1, 0);
    SYMBOL_SUB = create_string_check("-", 1, 0);
    SYMBOL_DIV = create_string_check("/", 1, 0);
    SYMBOL_MOD = create_string_check("%", 1, 0);
    SYMBOL_LOGICAL_NOT = create_string_check("!", 1, 0);
    SYMBOL_BITWISE_NOT = create_string_check("~", 1, 0);
    SYMBOL_XOR = create_string_check("^", 1, 0);
    SYMBOL_BITWISE_OR = create_string_check("|", 1, 0);
    SYMBOL_LT = create_string_check("<", 1, 0);
    SYMBOL_GT = create_string_check(">", 1, 0);
    SYMBOL_L_SHIFT = create_string_check("<<", 2, 0);
    SYMBOL_R_SHIFT = create_string_check(">>", 2, 0);
    SYMBOL_LE = create_string_check("<=", 2, 0);
    SYMBOL_GE = create_string_check(">=", 2, 0);
    SYMBOL_EQ = create_string_check("==", 2, 0);
    SYMBOL_NE = create_string_check("!=", 2, 0);
    SYMBOL_LOGICAL_AND = create_string_check("&&", 2, 0);
    SYMBOL_LOGICAL_OR = create_string_check("||", 2, 0);
    SYMBOL_ADD_ASSIGN = create_string_check("+=", 2, 0);
    SYMBOL_SUB_ASSIGN = create_string_check("-=", 2, 0);
    SYMBOL_MUL_ASSIGN = create_string_check("*=", 2, 0);
    SYMBOL_DIV_ASSIGN = create_string_check("/=", 2, 0);
    SYMBOL_MOD_ASSIGN = create_string_check("%=", 2, 0);
    SYMBOL_L_SHIFT_ASSIGN = create_string_check("<<=", 3, 0);
    SYMBOL_R_SHIFT_ASSIGN = create_string_check(">>=", 3, 0);
    SYMBOL_AND_ASSIGN = create_string_check("&=", 2, 0);
    SYMBOL_XOR_ASSIGN = create_string_check("^=", 2, 0);
    SYMBOL_OR_ASSIGN = create_string_check("|=", 2, 0);
    SYMBOL_HASH = create_string_check("#", 1, 0);
    SYMBOL_DOUBLE_HASH = create_string_check("##", 2, 0);
    P_DEFINE = create_string_check("define", 6, 0);
    P_DEFINED = create_string_check("defined", 7, 0);
    P_UNDEF = create_string_check("undef", 5, 0);
    P_IF = KEYWORD_IF;
    P_IFDEF = create_string_check("ifdef", 5, 0);
    P_IFNDEF = create_string_check("ifndef", 6, 0);
    P_ELIF = create_string_check("elif", 4, 0);
    P_ELSE = KEYWORD_ELSE;
    P_ENDIF = create_string_check("endif", 5, 0);
    P_INCLUDE = create_string_check("include", 7, 0);
    P_LINE = create_string_check("line", 4, 0);
    P_ERROR = create_string_check("error", 5, 0);
    P_PRAGMA = create_string_check("pragma", 6, 0);
    P_VA_ARGS_ = create_string_check("__VA_ARGS__", 11, 0);
    P_FILE_ = create_string_check("__FILE__", 8, 0);
    P_LINE_ = create_string_check("__LINE__", 8, 0);
    P_DATE_ = create_string_check("__DATE__", 8, 0);
    P_TIME_ = create_string_check("__TIME__", 8, 0);
    P_STDC_ = create_string_check("__STDC__", 8, 0);
    P_STDC_VERSION_ = create_string_check("__STDC_VERSION__", 16, 0);
    P_STDC_HOSTED_ = create_string_check("__STDC_HOSTED__", 15, 0);
    P_PRAGMA_ = create_string_check("_Pragma", 7, 0);
}
