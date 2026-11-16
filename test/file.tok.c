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
struct stat {
    unsigned short st_mode;
};
int stat(const char* path, struct stat* buf);
char* getcwd(char* buffer, size_t size);
static size_t root_length(string s, size_t n, _Bool * rooted) {
    *rooted = 0 ;
    if (n >= 1 && s[0] == '/') {
        *rooted = 1 ;
        return 1;
    }
    return 0;
}
static void path_normalize(Path* p, const char* raw) {
    ((void)(p != ((void*)0) && raw != ((void*)0))) ;
    size_t len = strlen(raw);
    char* out = (char*)malloc(len + 2);
    if (out == ((void*)0) ) {
        fprintf(stderr, "[path Fatal] at <path_normalize>: Cannot allocate memory\n");
        abort();
    }
    size_t pos = 0;
    size_t k = 0;
    for (; k < len; k++) {
        char c = raw[k];
        if (((c) == '/')) {
            if (pos == 0 || out[pos - 1] != '/')
                out[pos++] = '/';
        } else
            out[pos++] = c;
    }
    _Bool rooted;
    size_t base = root_length(out, pos, &rooted);
    if (rooted && base == pos && out[pos - 1] != '/') {
        out[pos++] = '/';
        base = pos;
    }
    if (pos > base && out[pos - 1] == '/')
        pos--;
    out[pos] = '\0';
    size_t r = base;
    size_t i = base;
    while (i <= pos) {
        size_t j = i;
        while (j < pos && out[j] != '/')
            j++;
        size_t seg_len = j - i;
        if (seg_len == 0) {
        } else if (seg_len == 1 && out[i] == '.') {
        } else if (seg_len == 2 && out[i] == '.' && out[i + 1] == '.') {
            _Bool top_is_dotdot = (r - base >= 2 && out[r - 1] == '.' && out[r - 2] == '.' && (r - base == 2 || out[r - 3] == '/'));
            if (r > base && !top_is_dotdot) {
                while (r > base && out[r - 1] != '/')
                    r--;
                if (r > base)
                    r--;
            } else if (!rooted) {
                if (r > base)
                    out[r++] = '/';
                out[r++] = '.';
                out[r++] = '.';
            }
        } else {
            if (r > base)
                out[r++] = '/';
            memmove(out + r, out + i, seg_len);
            r += seg_len;
        }
        i = j + 1;
    }
    if (r == 0)
        out[r++] = '.';
    out[r] = '\0';
    p->rooted = rooted;
    p->str = create_string(out, r);
    p->root = create_string(out, base);
    size_t file_start = base;
    size_t dir_len = 0;
    for (size_t m = r; m > base; m--) {
        if (out[m - 1] == '/') {
            dir_len = m - 1 - base;
            file_start = m;
            break;
        }
    }
    const char* f = out + file_start;
    size_t flen = r - file_start;
    size_t dot = flen;
    if (!(flen == 2 && f[0] == '.' && f[1] == '.')) {
        for (size_t m = flen; m > 1; m--) {
            if (f[m - 1] == '.') {
                dot = m - 1;
                break;
            }
        }
    }
    p->dir = create_string(out + base, dir_len);
    p->filename = create_string(f, dot);
    p->extension = create_string(f + dot, flen - dot);
    p->normalized = 1 ;
    free(out);
}
static string compose(const char* root, const char* dir, const char* filename, const char* extension) {
    _Bool has_name = (filename[0] != '\0' || extension[0] != '\0');
    if (root[0] == '\0' && dir[0] == '\0' && !has_name)
        return create_string(".", 1);
    if (dir[0] != '\0' && has_name)
        return string_splice("%s%s/%s%s", root, dir, filename, extension);
    if (root[0] == '\0' && dir[0] == '\0')
        return string_splice("%s%s", filename, extension);
    return string_splice("%s%s%s%s", root, dir, filename, extension);
}
Path* create_path(string raw) {
    ((void)(raw != ((void*)0))) ;
    Path* p = (Path*)alloc_memory(sizeof(Path), 1 ) ;
    path_normalize(p, raw);
    return p;
}
Path* path_join(const Path* a, const Path* b) {
    ((void)(a != ((void*)0) && b != ((void*)0))) ;
    if (b->rooted || a->str == SYMBOL_DOT)
        return create_path(b->str);
    size_t la = strlen(a->str);
    if (a->str[la - 1] == '/' || a->str == a->root)
        return create_path(string_splice("%s%s", a->str, b->str));
    else
        return create_path(string_splice("%s/%s", a->str, b->str));
}
Path* path_change_ext(const Path* p, string ext) {
    ((void)(p != ((void*)0) && ext != ((void*)0))) ;
    if (p->filename[0] == '\0' || p->filename == SYMBOL_DOT || strcmp(p->filename, "..") == 0)
        return create_path(p->str);
    string new_ext = (ext[0] == '\0' || ext[0] == '.') ? ext : string_splice(".%s", ext);
    return create_path(compose(p->root, p->dir, p->filename, new_ext));
}
Path* path_change_filename(const Path* p, string name) {
    ((void)(p != ((void*)0) && name != ((void*)0))) ;
    return create_path(compose(p->root, p->dir, name, p->extension));
}
Path* path_absolute(const Path* p) {
    ((void)(p != ((void*)0))) ;
    if (p->rooted)
        return create_path(p->str);
    char cwd[4096];
    if (getcwd(cwd, sizeof(cwd)) == ((void*)0) ) {
        fprintf(stderr, "[path Error] at <path_absolute>: Cannot get current working directory\n");
        return create_path(p->str);
    }
    return path_join(create_path(cwd), p);
}
string path_str(const Path* p) {
    ((void)(p != ((void*)0))) ;
    return p->str;
}
string path_dirname(const Path* p) {
    ((void)(p != ((void*)0))) ;
    return compose(p->root, p->dir, "", "");
}
string path_root_str(const Path* p) {
    ((void)(p != ((void*)0))) ;
    return p->root;
}
string path_filename(const Path* p) {
    ((void)(p != ((void*)0))) ;
    return p->filename;
}
string path_extension(const Path* p) {
    ((void)(p != ((void*)0))) ;
    return p->extension;
}
_Bool path_is_absolute(const Path* p) {
    ((void)(p != ((void*)0))) ;
    return p->rooted;
}
_Bool path_equal(const Path* a, const Path* b) {
    ((void)(a != ((void*)0) && b != ((void*)0))) ;
    return a->str == b->str;
}
_Bool path_exists(const Path* p) {
    ((void)(p != ((void*)0))) ;
    struct stat st;
    return stat(p->str, &st) == 0;
}
_Bool path_is_dir(const Path* p) {
    ((void)(p != ((void*)0))) ;
    struct stat st;
    return stat(p->str, &st) == 0 && (((st.st_mode) & 0170000) == 0040000) ;
}
static List_string include_dir = ((void*)0) ;
void add_include_dir(string dir) {
    if (include_dir == ((void*)0) )
        include_dir = list_create(_Generic((string)0, string: TYPE_string, ppToken*: TYPE_ppToken, ppMacro*: TYPE_ppMacro, ppCondFrame*: TYPE_ppCondFrame, List_ppToken*: TYPE_List_ppToken, Token*: TYPE_Token, ExternDecl*: TYPE_ExternDecl, DeclSpec*: TYPE_DeclSpec, InitDecl*: TYPE_InitDecl, ParamDecl*: TYPE_ParamDecl, StructDecl*: TYPE_StructDecl, Enumerator*: TYPE_Enumerator, InitializerItem*: TYPE_InitializerItem, Designator*: TYPE_Designator, SpecifierQualifier*: TYPE_SpecifierQualifier, StructDeclarator*: TYPE_StructDeclarator, DeclStmt*: TYPE_DeclStmt, AssignmentExpression*: TYPE_AssignmentExpression, GenericAssociation*: TYPE_GenericAssociation, TypeName*: TYPE_TypeName, Scope*: TYPE_Scope, Symbol*: TYPE_Symbol )) ;
    if (dir == ((void*)0) || dir[0] == '\0')
        return;
    string normalized_dir = create_path(dir)->str;
    for (List* d__l = (include_dir); d__l != ((void*)0) && d__l->head != ((void*)0) ; d__l = ((void*)0) ) for (ListNode* d__n = d__l->head; d__n != ((void*)0) ; d__n = d__n->next) for (string d = (string)d__n->data; d != ((void*)0) ; d = ((void*)0) )
        if (d == normalized_dir)
            return;
    list_append((include_dir), (void*)(normalized_dir), _Generic((normalized_dir), string: TYPE_string, ppToken*: TYPE_ppToken, ppMacro*: TYPE_ppMacro, ppCondFrame*: TYPE_ppCondFrame, List_ppToken*: TYPE_List_ppToken, Token*: TYPE_Token, ExternDecl*: TYPE_ExternDecl, DeclSpec*: TYPE_DeclSpec, InitDecl*: TYPE_InitDecl, ParamDecl*: TYPE_ParamDecl, StructDecl*: TYPE_StructDecl, Enumerator*: TYPE_Enumerator, InitializerItem*: TYPE_InitializerItem, Designator*: TYPE_Designator, SpecifierQualifier*: TYPE_SpecifierQualifier, StructDeclarator*: TYPE_StructDeclarator, DeclStmt*: TYPE_DeclStmt, AssignmentExpression*: TYPE_AssignmentExpression, GenericAssociation*: TYPE_GenericAssociation, TypeName*: TYPE_TypeName, Scope*: TYPE_Scope, Symbol*: TYPE_Symbol )) ;
}
string find_file(string name, _Bool is_system, string current_file) {
    if (include_dir == ((void*)0) )
        include_dir = list_create(_Generic((string)0, string: TYPE_string, ppToken*: TYPE_ppToken, ppMacro*: TYPE_ppMacro, ppCondFrame*: TYPE_ppCondFrame, List_ppToken*: TYPE_List_ppToken, Token*: TYPE_Token, ExternDecl*: TYPE_ExternDecl, DeclSpec*: TYPE_DeclSpec, InitDecl*: TYPE_InitDecl, ParamDecl*: TYPE_ParamDecl, StructDecl*: TYPE_StructDecl, Enumerator*: TYPE_Enumerator, InitializerItem*: TYPE_InitializerItem, Designator*: TYPE_Designator, SpecifierQualifier*: TYPE_SpecifierQualifier, StructDeclarator*: TYPE_StructDeclarator, DeclStmt*: TYPE_DeclStmt, AssignmentExpression*: TYPE_AssignmentExpression, GenericAssociation*: TYPE_GenericAssociation, TypeName*: TYPE_TypeName, Scope*: TYPE_Scope, Symbol*: TYPE_Symbol )) ;
    if (name == ((void*)0) || name[0] == '\0')
        return ((void*)0) ;
    Path* n = create_path(name);
    if (n->rooted) {
        if (path_exists(n) && !path_is_dir(n))
            return n->str;
        return ((void*)0) ;
    }
    if (!is_system && current_file != ((void*)0) ) {
        Path* dir = create_path(path_dirname(create_path(current_file)));
        Path* path = path_join(dir, n);
        if (path_exists(path) && !path_is_dir(path))
            return path->str;
    }
    for (List* d__l = (include_dir); d__l != ((void*)0) && d__l->head != ((void*)0) ; d__l = ((void*)0) ) for (ListNode* d__n = d__l->head; d__n != ((void*)0) ; d__n = d__n->next) for (string d = (string)d__n->data; d != ((void*)0) ; d = ((void*)0) ) {
        Path* path = path_join(create_path(d), n);
        if (path_exists(path) && !path_is_dir(path))
            return path->str;
    }
    return ((void*)0) ;
}
