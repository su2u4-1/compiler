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
            if (block->size - block->used >= size) {
                block->used += size;
                return ptr;
            }
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
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "[lib Error] at <get_source>: could not open source file '%s'\n", path);
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    size_t end = (size_t)ftell(file);
    fseek(file, 0, SEEK_SET);
    string source_code = malloc(end + 1);
    if (source_code == NULL) {
        fprintf(stderr, "[lib Error] at <get_source>: could not allocate memory for source code\n");
        exit(1);
    }
    fread(source_code, 1, end, file);
    source_code[end] = '\0';
    fclose(file);
    return source_code;
}

string string_splice(string format, ...) {
#include <stdarg.h>
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

void* list_pop(List* self, int type_id) {
    if (self == NULL)
        return NULL;
    if (self->type_id != type_id) {
        fprintf(stderr, "[lib Error at <list_pop>: type mismatch: list has %d, got %d\n", self->type_id, type_id);
        return NULL;
    }
    if (list_empty(self))
        return NULL;
    void* data = self->head->data;
    self->head = self->head->next;
    if (self->head == NULL)
        self->tail = NULL;
    return data;
}

// constants

static const char* keywordStrings[keyword_count] = {"_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary", "_Noreturn", "_Static_assert", "_Thread_local", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
string keywordList[keyword_count] = {0};
static const char* symbolStrings[symbol_count] = {";", ",", "{", "}", "(", ")", "[", "]", ":", "?", "...", ".", "->", "*", "&", "=", "++", "--", "+", "-", "/", "%", "!", "~", "^", "|", "<", ">", "<<", ">>", "<=", ">=", "==", "!=", "&&", "||", "+=", "-=", "*=", "/=", "%=", "<<=", ">>=", "&=", "^=", "|="};
string symbolList[symbol_count] = {0};

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
string KEYWORD_SINGED = NULL;
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
    KEYWORD_SINGED = keywordList[33];
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
    for (size_t i = 0; i < symbol_count; ++i) {
        symbolList[i] = create_string_check(symbolStrings[i], strlen(symbolStrings[i]), false);
    }
    SYMBOL_SEMICOLON = symbolList[0];
    SYMBOL_COMMA = symbolList[1];
    SYMBOL_L_BRACE = symbolList[2];
    SYMBOL_R_BRACE = symbolList[3];
    SYMBOL_L_PARENTHESIS = symbolList[4];
    SYMBOL_R_PARENTHESIS = symbolList[5];
    SYMBOL_L_BRACKET = symbolList[6];
    SYMBOL_R_BRACKET = symbolList[7];
    SYMBOL_COLON = symbolList[8];
    SYMBOL_QUESTION = symbolList[9];
    SYMBOL_ELLIPSIS = symbolList[10];
    SYMBOL_DOT = symbolList[11];
    SYMBOL_ARROW = symbolList[12];
    SYMBOL_MUL = symbolList[13];
    SYMBOL_BITWISE_AND = symbolList[14];
    SYMBOL_ASSIGN = symbolList[15];
    SYMBOL_INCREMENT = symbolList[16];
    SYMBOL_DECREMENT = symbolList[17];
    SYMBOL_ADD = symbolList[18];
    SYMBOL_SUB = symbolList[19];
    SYMBOL_DIV = symbolList[20];
    SYMBOL_MOD = symbolList[21];
    SYMBOL_LOGICAL_NOT = symbolList[22];
    SYMBOL_BITWISE_NOT = symbolList[23];
    SYMBOL_XOR = symbolList[24];
    SYMBOL_BITWISE_OR = symbolList[25];
    SYMBOL_LT = symbolList[26];
    SYMBOL_GT = symbolList[27];
    SYMBOL_L_SHIFT = symbolList[28];
    SYMBOL_R_SHIFT = symbolList[29];
    SYMBOL_LE = symbolList[30];
    SYMBOL_GE = symbolList[31];
    SYMBOL_EQ = symbolList[32];
    SYMBOL_NE = symbolList[33];
    SYMBOL_LOGICAL_AND = symbolList[34];
    SYMBOL_LOGICAL_OR = symbolList[35];
    SYMBOL_ADD_ASSIGN = symbolList[36];
    SYMBOL_SUB_ASSIGN = symbolList[37];
    SYMBOL_MUL_ASSIGN = symbolList[38];
    SYMBOL_DIV_ASSIGN = symbolList[39];
    SYMBOL_MOD_ASSIGN = symbolList[40];
    SYMBOL_L_SHIFT_ASSIGN = symbolList[41];
    SYMBOL_R_SHIFT_ASSIGN = symbolList[42];
    SYMBOL_AND_ASSIGN = symbolList[43];
    SYMBOL_XOR_ASSIGN = symbolList[44];
    SYMBOL_OR_ASSIGN = symbolList[45];
}
