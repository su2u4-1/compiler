#include "lib.h"

// memory

MemoryBlock* string_memory = NULL;
MemoryBlock* struct_memory = NULL;

static size_t malloc_allocated = 0;
static size_t string_count = 0;
static StringTable* string_table = NULL;

static void free_all_memory(void) {
    MemoryBlock* block = string_memory;
    while (block != NULL) {
        MemoryBlock* next = block->next;
        free(block->data);
        free(block);
        block = next;
    }
    string_memory = NULL;
    block = struct_memory;
    while (block != NULL) {
        MemoryBlock* next = block->next;
        free(block->data);
        free(block);
        block = next;
    }
    struct_memory = NULL;
}

static MemoryBlock* create_memory_block(size_t size) {
    MemoryBlock* block = malloc(sizeof(MemoryBlock));
    if (block == NULL) {
        fprintf(stderr, "[lib Fatal] at <create_memory_block>: Cannot allocate memory\n");
        free_all_memory();
        abort();
    }
    malloc_allocated += sizeof(MemoryBlock);
    block->size = size;
    block->used = 0;
    block->data = malloc(size);
    if (block->data == NULL) {
        fprintf(stderr, "[lib Fatal] at <create_memory_block>: Cannot allocate memory\n");
        free(block);
        free_all_memory();
        abort();
    }
    malloc_allocated += size;
    block->next = NULL;
    return block;
}

static void increase_memory(MemoryBlock** block, size_t additional_size) {
    MemoryBlock* new_block = create_memory_block((*block)->size + additional_size);
    new_block->next = *block;
    *block = new_block;
}

static StringTable* create_string_table(size_t capacity) {
    StringTable* table = create_struct(StringTable);
    table->capacity = capacity;
    table->count = 0;
    table->buckets = calloc(capacity, sizeof(StringNode*));
    return table;
}
pointer alloc_memory(size_t size, bool is_struct) {
    if (size >= DEFAULT_MEMORY_SIZE) {
        pointer ptr = malloc(size);
        if (ptr == NULL) {
            fprintf(stderr, "[lib Fatal] at <alloc_memory>: Cannot allocate memory\n");
            free(ptr);
            free_all_memory();
            abort();
        }
        malloc_allocated += size;
        return ptr;
    }
    MemoryBlock* block = string_memory;
    if (is_struct) {
        block = struct_memory;
        size = (size + ALIGN_SIZE - 1) & ~(ALIGN_SIZE - 1);
    }
    while (block != NULL) {
        if (block->size - block->used >= size) {
            pointer ptr = (void*)(block->data + block->used);
            if (is_struct)
                assert((size_t)ptr % ALIGN_SIZE == 0);
            block->used += size;
            return ptr;
        }
        block = block->next;
    }
    if (is_struct)
        increase_memory(&struct_memory, size);
    else
        increase_memory(&string_memory, size);
    return alloc_memory(size, is_struct);
}

// other

// FNV-1a hash function
static size_t hash(const char* str, size_t len) {
    size_t hash_value = 2166136261;
    for (size_t i = 0; i < len; i++) {
        hash_value ^= (unsigned char)str[i];
        hash_value *= 16777619;
    }
    return hash_value;
}

static string create_string_check(const char* str, size_t len, bool check) {
    size_t hash_value = hash(str, len);
    size_t index = hash_value % string_table->capacity;
    if (check) {
        StringNode* current = string_table->buckets[index];
        while (current != NULL) {
            if (current->size == len && current->hash == hash_value && strncmp(current->value, str, len) == 0)
                return current->value;
            current = current->next;
        }
    }
    StringNode* node = create_struct(StringNode);
    node->size = len;
    node->hash = hash_value;
    node->next = string_table->buckets[index];
    node->value = (string)alloc_memory(len + 1, false);
    memcpy(node->value, str, len);
    node->value[len] = '\0';
    string_table->buckets[index] = node;
    string_table->count++;
    string_count++;
    return node->value;
}

string create_string(const char* str, size_t len) {
    return create_string_check(str, len, true);
}

string get_source(string path) {
    FILE* file = fopen(path, "rb");
    if (file == NULL)
        return NULL;
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return NULL;
    }
    long n = ftell(file);
    if (n < 0 || n > (1L << 30)) {  // 1 GiB limit
        fclose(file);
        return NULL;
    }
    rewind(file);
    size_t size = (size_t)n;
    string source_code = (string)alloc_memory(size + 1, false);
    size_t got = fread(source_code, 1, size, file);
    bool failed = ferror(file);
    fclose(file);
    if (failed)
        return NULL;
    source_code[got] = '\0';
    return source_code;
}

#include <stdarg.h>
string string_splice(string format, ...) {
    va_list args;
    va_start(args, format);
    int length = vsnprintf(NULL, 0, format, args);
    va_end(args);
    if (length <= 0) {
        fprintf(stderr, "[lib Error] at <string_splice>: Failed to format string\n");
        return NULL;
    }
    char* name = malloc((size_t)length + 1);
    if (name == NULL) {
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
    if (string_memory == NULL)
        string_memory = create_memory_block(DEFAULT_MEMORY_SIZE);
    if (struct_memory == NULL)
        struct_memory = create_memory_block(DEFAULT_MEMORY_SIZE);
    if (string_table == NULL)
        string_table = create_string_table(1024);
    init_constant();
}

// list

List* list_create(int type_id) {
    List* self = create_struct(List);
    if (self == NULL)
        return NULL;
    self->head = NULL;
    self->tail = NULL;
    self->type_id = type_id;
    return self;
}

int list_append(List* self, void* item, int type_id) {
    if (self == NULL)
        return 1;
    if (self->type_id != type_id) {
        fprintf(stderr, "[lib Error] at <list_append>: type mismatch: list has %d, got %d\n", self->type_id, type_id);
        return 1;
    }
    ListNode* node = create_struct(ListNode);
    if (node == NULL)
        return 1;
    node->data = item;
    node->next = NULL;
    if (self->tail != NULL)
        self->tail->next = node;
    else
        self->head = node;
    self->tail = node;
    return 0;
}

void* list_pop_front(List* self, int type_id) {
    if (list_empty(self))
        return NULL;
    if (self->type_id != type_id) {
        fprintf(stderr, "[lib Error at <list_pop>: type mismatch: list has %d, got %d\n", self->type_id, type_id);
        return NULL;
    }
    void* data = self->head->data;
    self->head = self->head->next;
    if (self->head == NULL)
        self->tail = NULL;
    return data;
}

void* list_pop_back(List* self, int type_id) {
    if (list_empty(self))
        return NULL;
    if (self->type_id != type_id) {
        fprintf(stderr, "[lib Error at <list_pop_back>: type mismatch: list has %d, got %d\n", self->type_id, type_id);
        return NULL;
    }
    void* data = self->tail->data;
    if (self->head == self->tail) {
        self->head = NULL;
        self->tail = NULL;
    } else {
        ListNode* current = self->head;
        while (current->next != self->tail) {
            current = current->next;
        }
        current->next = NULL;
        self->tail = current;
    }
    return data;
}

void* list_peek_front(List* self, int type_id) {
    if (list_empty(self))
        return NULL;
    if (self->type_id != type_id) {
        fprintf(stderr, "[lib Error at <list_peek_front>: type mismatch: list has %d, got %d\n", self->type_id, type_id);
        return NULL;
    }
    return self->head->data;
}

void* list_peek_back(List* self, int type_id) {
    if (list_empty(self))
        return NULL;
    if (self->type_id != type_id) {
        fprintf(stderr, "[lib Error at <list_peek_back>: type mismatch: list has %d, got %d\n", self->type_id, type_id);
        return NULL;
    }
    return self->tail->data;
}

// constants

static const char* keywordStrings[keyword_count] = {"_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary", "_Noreturn", "_Static_assert", "_Thread_local", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
string keywordList[keyword_count] = {0};

string KEYWORD_ALIGNAS = NULL;
string KEYWORD_ALIGNOF = NULL;
string KEYWORD_ATOMIC = NULL;
string KEYWORD_BOOL = NULL;
string KEYWORD_COMPLEX = NULL;
string KEYWORD_GENERIC = NULL;
string KEYWORD_IMAGINARY = NULL;
string KEYWORD_NORETURN = NULL;
string KEYWORD_STATIC_ASSERT = NULL;
string KEYWORD_THREAD_LOCAL = NULL;
string KEYWORD_AUTO = NULL;
string KEYWORD_BREAK = NULL;
string KEYWORD_CASE = NULL;
string KEYWORD_CHAR = NULL;
string KEYWORD_CONST = NULL;
string KEYWORD_CONTINUE = NULL;
string KEYWORD_DEFAULT = NULL;
string KEYWORD_DO = NULL;
string KEYWORD_DOUBLE = NULL;
string KEYWORD_ELSE = NULL;
string KEYWORD_ENUM = NULL;
string KEYWORD_EXTERN = NULL;
string KEYWORD_FLOAT = NULL;
string KEYWORD_FOR = NULL;
string KEYWORD_GOTO = NULL;
string KEYWORD_IF = NULL;
string KEYWORD_INLINE = NULL;
string KEYWORD_INT = NULL;
string KEYWORD_LONG = NULL;
string KEYWORD_REGISTER = NULL;
string KEYWORD_RESTRICT = NULL;
string KEYWORD_RETURN = NULL;
string KEYWORD_SHORT = NULL;
string KEYWORD_SIGNED = NULL;
string KEYWORD_SIZEOF = NULL;
string KEYWORD_STATIC = NULL;
string KEYWORD_STRUCT = NULL;
string KEYWORD_SWITCH = NULL;
string KEYWORD_TYPEDEF = NULL;
string KEYWORD_UNION = NULL;
string KEYWORD_UNSIGNED = NULL;
string KEYWORD_VOID = NULL;
string KEYWORD_VOLATILE = NULL;
string KEYWORD_WHILE = NULL;
string SYMBOL_SEMICOLON = NULL;
string SYMBOL_COMMA = NULL;
string SYMBOL_L_BRACE = NULL;
string SYMBOL_R_BRACE = NULL;
string SYMBOL_L_PARENTHESIS = NULL;
string SYMBOL_R_PARENTHESIS = NULL;
string SYMBOL_L_BRACKET = NULL;
string SYMBOL_R_BRACKET = NULL;
string SYMBOL_COLON = NULL;
string SYMBOL_QUESTION = NULL;
string SYMBOL_ELLIPSIS = NULL;
string SYMBOL_DOT = NULL;
string SYMBOL_ARROW = NULL;
string SYMBOL_MUL = NULL;
string SYMBOL_BITWISE_AND = NULL;
string SYMBOL_ASSIGN = NULL;
string SYMBOL_INCREMENT = NULL;
string SYMBOL_DECREMENT = NULL;
string SYMBOL_ADD = NULL;
string SYMBOL_SUB = NULL;
string SYMBOL_DIV = NULL;
string SYMBOL_MOD = NULL;
string SYMBOL_LOGICAL_NOT = NULL;
string SYMBOL_BITWISE_NOT = NULL;
string SYMBOL_XOR = NULL;
string SYMBOL_BITWISE_OR = NULL;
string SYMBOL_LT = NULL;
string SYMBOL_GT = NULL;
string SYMBOL_L_SHIFT = NULL;
string SYMBOL_R_SHIFT = NULL;
string SYMBOL_LE = NULL;
string SYMBOL_GE = NULL;
string SYMBOL_EQ = NULL;
string SYMBOL_NE = NULL;
string SYMBOL_LOGICAL_AND = NULL;
string SYMBOL_LOGICAL_OR = NULL;
string SYMBOL_ADD_ASSIGN = NULL;
string SYMBOL_SUB_ASSIGN = NULL;
string SYMBOL_MUL_ASSIGN = NULL;
string SYMBOL_DIV_ASSIGN = NULL;
string SYMBOL_MOD_ASSIGN = NULL;
string SYMBOL_L_SHIFT_ASSIGN = NULL;
string SYMBOL_R_SHIFT_ASSIGN = NULL;
string SYMBOL_AND_ASSIGN = NULL;
string SYMBOL_XOR_ASSIGN = NULL;
string SYMBOL_OR_ASSIGN = NULL;
string SYMBOL_HASH = NULL;
string SYMBOL_DOUBLE_HASH = NULL;
string P_DEFINE = NULL;
string P_DEFINED = NULL;
string P_UNDEF = NULL;
string P_IF = NULL;
string P_IFDEF = NULL;
string P_IFNDEF = NULL;
string P_ELIF = NULL;
string P_ELSE = NULL;
string P_ENDIF = NULL;
string P_INCLUDE = NULL;
string P_LINE = NULL;
string P_ERROR = NULL;
string P_PRAGMA = NULL;
string P_VA_ARGS_ = NULL;
string P_FILE_ = NULL;
string P_LINE_ = NULL;
string P_DATE_ = NULL;
string P_TIME_ = NULL;
string P_STDC_ = NULL;
string P_STDC_VERSION_ = NULL;
string P_STDC_HOSTED_ = NULL;

void init_constant(void) {
    for (size_t i = 0; i < keyword_count; ++i) {
        keywordList[i] = create_string_check(keywordStrings[i], strlen(keywordStrings[i]), false);
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

    SYMBOL_SEMICOLON = create_string_check(";", 1, false);
    SYMBOL_COMMA = create_string_check(",", 1, false);
    SYMBOL_L_BRACE = create_string_check("{", 1, false);
    SYMBOL_R_BRACE = create_string_check("}", 1, false);
    SYMBOL_L_PARENTHESIS = create_string_check("(", 1, false);
    SYMBOL_R_PARENTHESIS = create_string_check(")", 1, false);
    SYMBOL_L_BRACKET = create_string_check("[", 1, false);
    SYMBOL_R_BRACKET = create_string_check("]", 1, false);
    SYMBOL_COLON = create_string_check(":", 1, false);
    SYMBOL_QUESTION = create_string_check("?", 1, false);
    SYMBOL_ELLIPSIS = create_string_check("...", 3, false);
    SYMBOL_DOT = create_string_check(".", 1, false);
    SYMBOL_ARROW = create_string_check("->", 2, false);
    SYMBOL_MUL = create_string_check("*", 1, false);
    SYMBOL_BITWISE_AND = create_string_check("&", 1, false);
    SYMBOL_ASSIGN = create_string_check("=", 1, false);
    SYMBOL_INCREMENT = create_string_check("++", 2, false);
    SYMBOL_DECREMENT = create_string_check("--", 2, false);
    SYMBOL_ADD = create_string_check("+", 1, false);
    SYMBOL_SUB = create_string_check("-", 1, false);
    SYMBOL_DIV = create_string_check("/", 1, false);
    SYMBOL_MOD = create_string_check("%", 1, false);
    SYMBOL_LOGICAL_NOT = create_string_check("!", 1, false);
    SYMBOL_BITWISE_NOT = create_string_check("~", 1, false);
    SYMBOL_XOR = create_string_check("^", 1, false);
    SYMBOL_BITWISE_OR = create_string_check("|", 1, false);
    SYMBOL_LT = create_string_check("<", 1, false);
    SYMBOL_GT = create_string_check(">", 1, false);
    SYMBOL_L_SHIFT = create_string_check("<<", 2, false);
    SYMBOL_R_SHIFT = create_string_check(">>", 2, false);
    SYMBOL_LE = create_string_check("<=", 2, false);
    SYMBOL_GE = create_string_check(">=", 2, false);
    SYMBOL_EQ = create_string_check("==", 2, false);
    SYMBOL_NE = create_string_check("!=", 2, false);
    SYMBOL_LOGICAL_AND = create_string_check("&&", 2, false);
    SYMBOL_LOGICAL_OR = create_string_check("||", 2, false);
    SYMBOL_ADD_ASSIGN = create_string_check("+=", 2, false);
    SYMBOL_SUB_ASSIGN = create_string_check("-=", 2, false);
    SYMBOL_MUL_ASSIGN = create_string_check("*=", 2, false);
    SYMBOL_DIV_ASSIGN = create_string_check("/=", 2, false);
    SYMBOL_MOD_ASSIGN = create_string_check("%=", 2, false);
    SYMBOL_L_SHIFT_ASSIGN = create_string_check("<<=", 3, false);
    SYMBOL_R_SHIFT_ASSIGN = create_string_check(">>=", 3, false);
    SYMBOL_AND_ASSIGN = create_string_check("&=", 2, false);
    SYMBOL_XOR_ASSIGN = create_string_check("^=", 2, false);
    SYMBOL_OR_ASSIGN = create_string_check("|=", 2, false);
    SYMBOL_HASH = create_string_check("#", 1, false);
    SYMBOL_DOUBLE_HASH = create_string_check("##", 2, false);

    P_DEFINE = create_string_check("define", 6, false);
    P_DEFINED = create_string_check("defined", 7, false);
    P_UNDEF = create_string_check("undef", 5, false);
    P_IF = KEYWORD_IF;
    P_IFDEF = create_string_check("ifdef", 5, false);
    P_IFNDEF = create_string_check("ifndef", 6, false);
    P_ELIF = create_string_check("elif", 4, false);
    P_ELSE = KEYWORD_ELSE;
    P_ENDIF = create_string_check("endif", 5, false);
    P_INCLUDE = create_string_check("include", 7, false);
    P_LINE = create_string_check("line", 4, false);
    P_ERROR = create_string_check("error", 5, false);
    P_PRAGMA = create_string_check("pragma", 6, false);
    P_VA_ARGS_ = create_string_check("__VA_ARGS__", 11, false);
    P_FILE_ = create_string_check("__FILE__", 8, false);
    P_LINE_ = create_string_check("__LINE__", 8, false);
    P_DATE_ = create_string_check("__DATE__", 8, false);
    P_TIME_ = create_string_check("__TIME__", 8, false);
    P_STDC_ = create_string_check("__STDC__", 8, false);
    P_STDC_VERSION_ = create_string_check("__STDC_VERSION__", 16, false);
    P_STDC_HOSTED_ = create_string_check("__STDC_HOSTED__", 15, false);
}
