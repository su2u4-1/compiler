#include "semantic.h"

#include <complex.h>

#include "lexer.h"
#include "target.h"

#define semantic_error(token, msg) report_error(ctx, (token), (msg), false)
#define semantic_warn(token, msg) report_error(ctx, (token), (msg), true)
#define is_char_type(type_) ((type_)->type_kind == TYPE_CHAR || (type_)->type_kind == TYPE_S_CHAR || (type_)->type_kind == TYPE_U_CHAR)
#define type_size(type_) (((type_)->type_kind == TYPE_STRUCT || (type_)->type_kind == TYPE_UNION) ? (type_)->type.struct_union_type->size : (type_)->size)

typedef struct {
    IR_Type* type;
    string storage;
    uintmax_t align;
    Token* align_keyword;
    bool is_inline;
    bool is_noreturn;
    bool is_thread_local;
} DeclSpecInfo;

typedef struct {
    ListNode* node;
    ListNode* designator;
    IR_Expression* expr;
} InitCursor;

typedef struct InitNode InitNode;
struct InitNode {
    Token* token;
    IR_Type* type;
    size_t offset;
    IR_Expression* expr;
    IR_StructUnionDecl* member;
    uintmax_t index;
    bool is_set;
    InitNode *head, *tail, *next;
};

static void print_string_literal(FILE* out, StringLiteral str) {
    fputc('"', out);
    for (size_t i = 0; i < str.length; i++) {
        unsigned char c = (unsigned char)str.data[i];
        if (c == '"' || c == '\\') fprintf(out, "\\%c", c);
        else if (c >= 0x20 && c < 0x7F) fputc(c, out);
        else fprintf(out, "\\%03o", c);
    }
    fputc('"', out);
}

static void report_error(Semantic* ctx, Token* token, char* msg, bool is_warning) {
    if (is_warning)
        fprintf(stderr, "[Semantic warning] at %s:%zu:%zu: %s\n", token->filename, token->line, token->column, msg);
    else {
        fprintf(stderr, "[Semantic error] at %s:%zu:%zu: %s\n", token->filename, token->line, token->column, msg);
        ctx->error_count++;
    }
}

static void static_assert_report(Semantic* ctx, Token* token, StringLiteral str) {
    ctx->error_count++;
    fprintf(stderr, "[Static assertion failed] at %s:%zu:%zu: ", token->filename, token->line, token->column);
    print_string_literal(stderr, str);
    fputc('\n', stderr);
}

static IR_Scope* create_scope(IR_Scope* parent, IR_ScopeKind kind) {
    IR_Scope* scope = create_struct(IR_Scope);
    *scope = (IR_Scope){.parent = parent, .kind = kind, .names = create_list(IR_Symbol*), .tags = create_list(IR_Symbol*)};
    return scope;
}

static IR_Symbol* create_symbol(Token* token, string name, IR_Type* type, IR_SymbolKind kind) {
    IR_Symbol* symbol = create_struct(IR_Symbol);
    *symbol = (IR_Symbol){.token = token, .name = name, .type = type, .kind = kind, .linkage = LINKAGE_NONE};
    return symbol;
}

static IR_Symbol* find_symbol(IR_Scope* scope, string name, bool search_names) {
    assert(scope != NULL);
    assert(name != NULL);
    IR_Scope* s = scope;
    while (s != NULL) {
        foreach (IR_Symbol*, symbol, (search_names ? s->names : s->tags)) {
            if (symbol->name == name)
                return symbol;
        }
        s = s->parent;
    }
    return NULL;
}

static IR_Symbol* declare_name(Semantic* ctx, Token* id, IR_Type* type, IR_SymbolKind kind, string storage) {
    return NULL;  // placeholder
}

static bool eval_const_int(IR_Expression* expr, intmax_t* out) {
    return false;  // placeholder
}

static bool is_complete_type(IR_Type* type) {
    if (type->type_kind == TYPE_VOID)
        return false;
    else if (type->type_kind == TYPE_STRUCT || type->type_kind == TYPE_UNION)
        return type->type.struct_union_type->members != NULL;
    else if (type->type_kind == TYPE_ENUM)
        return type->type.enum_type->items != NULL;
    else if (type->type_kind == TYPE_ARRAY)
        return type->type.array.length != 0;
    else
        return true;
}

static IR_Type* compatible_type(IR_Type* a, IR_Type* b, bool a_is_lvalue) {
    return NULL;  // placeholder
}

static IR_Expression* convert_for_assignment(Semantic* ctx, IR_Expression* expr, IR_Type* target_type, Token* token) {
    return NULL;  // placeholder
}

static void update_cursor(InitCursor* cursor) {
    assert(cursor != NULL);
    *cursor = (InitCursor){.node = cursor->node->next, .designator = NULL, .expr = NULL};
    if (cursor->node == NULL)
        return;
    assert(cursor->node->data != NULL);
    list(AST_Designator*) designation = ((AST_InitializerItem*)cursor->node->data)->designation;
    if (!list_empty(designation))
        cursor->designator = designation->head;
}

static ListNode* find_member(IR_Type* type, string name) {
    assert(type != NULL);
    assert(name != NULL);
    assert(type->type_kind == TYPE_STRUCT || type->type_kind == TYPE_UNION);

    foreach (IR_StructUnionDecl*, decl, type->type.struct_union_type->members) {
        if (decl->name == name)
            return decl__n;
        if (decl->name == NULL && (decl->type->type_kind == TYPE_STRUCT || decl->type->type_kind == TYPE_UNION)) {
            ListNode* node = find_member(decl->type, name);
            if (node != NULL)
                return decl__n;
        }
    }
    return NULL;
}

static InitNode* create_init_tree(IR_Type* type) {
    InitNode* node = create_struct(InitNode);
    *node = (InitNode){.token = NULL, .type = type, .offset = 0, .expr = NULL, .member = NULL, .index = 0, .is_set = false, .head = NULL, .tail = NULL, .next = NULL};
    return node;
}

static InitNode* get_child(InitNode* parent, uintmax_t index, IR_StructUnionDecl* member, IR_Type* type, size_t offset, Token* token) {
    assert(parent != NULL);
    assert(type != NULL);
    assert((parent->type->type_kind == TYPE_ARRAY) == (member == NULL));

    if (parent->head == NULL || parent->tail == NULL) {
        InitNode* child = create_struct(InitNode);
        *child = (InitNode){.token = token, .type = type, .offset = offset, .expr = NULL, .member = member, .index = index, .is_set = false, .head = NULL, .tail = NULL, .next = NULL};
        parent->head = child;
        parent->tail = child;
        return child;
    }

    InitNode *l = NULL, *r = NULL;
    if (parent->type->type_kind == TYPE_ARRAY && parent->tail != NULL && index > parent->tail->index)
        l = parent->tail;
    else {
        for (InitNode* child = parent->head; child != NULL; child = child->next) {
            if (parent->type->type_kind == TYPE_ARRAY) {
                if (child->index > index && r == NULL) {
                    r = child;
                    break;
                } else if (child->index < index)
                    l = child;
                else
                    return child;
            } else if (child->member == member)
                return child;
        }
    }
    InitNode* child = create_struct(InitNode);
    *child = (InitNode){.token = token, .type = type, .offset = offset, .expr = NULL, .member = NULL, .index = 0, .is_set = false, .head = NULL, .tail = NULL, .next = NULL};
    if (parent->type->type_kind == TYPE_ARRAY) {
        child->index = index;
        child->next = r;
        if (l != NULL)
            l->next = child;
        else
            parent->head = child;
        if (r == NULL)
            parent->tail = child;
    } else {
        child->member = member;
        if (parent->type->type_kind == TYPE_UNION)
            parent->tail = NULL;
        if (parent->tail == NULL) {
            parent->tail = child;
            parent->head = child;
        } else {
            parent->tail->next = child;
            parent->tail = child;
        }
    }
    return child;
}

static void convert_init_tree(InitNode* tree, bool has_base, list(IR_Initializer*) result) {
    assert(tree != NULL);
    assert(result != NULL);

    if (tree->expr != NULL || (tree->is_set && has_base)) {
        IR_Initializer* init = create_struct(IR_Initializer);
        *init = (IR_Initializer){.token = tree->token, .offset = tree->offset, .size = type_size(tree->type), .expr = tree->expr, .bitfield_size = 0, .bit_offset = 0};
        if (tree->member != NULL) {
            init->bitfield_size = tree->member->bitfield_size;
            init->bit_offset = tree->member->bit_offset;
        }
        append(result, init);
        has_base = tree->expr != NULL;
    }
    for (InitNode* child = tree->head; child != NULL; child = child->next)
        convert_init_tree(child, has_base, result);
}

static size_t get_type_size(IR_Type* type) {
    switch (type->type_kind) {
        case TYPE_VOID: return VOID_SIZE;
        case TYPE_CHAR: return CHAR_SIZE;
        case TYPE_S_CHAR: return SIGNED_CHAR_SIZE;
        case TYPE_U_CHAR: return UNSIGNED_CHAR_SIZE;
        case TYPE_SHORT: return SHORT_SIZE;
        case TYPE_U_SHORT: return UNSIGNED_SHORT_SIZE;
        case TYPE_INT: return INT_SIZE;
        case TYPE_U_INT: return UNSIGNED_INT_SIZE;
        case TYPE_LONG: return LONG_SIZE;
        case TYPE_U_LONG: return UNSIGNED_LONG_SIZE;
        case TYPE_LONG_LONG: return LONG_LONG_SIZE;
        case TYPE_U_LONG_LONG: return UNSIGNED_LONG_LONG_SIZE;
        case TYPE_FLOAT: return FLOAT_SIZE;
        case TYPE_DOUBLE: return DOUBLE_SIZE;
        case TYPE_LONG_DOUBLE: return LONG_DOUBLE_SIZE;
        case TYPE_BOOL: return BOOL_SIZE;
        case TYPE_FLOAT_COMPLEX: return FLOAT_COMPLEX_SIZE;
        case TYPE_DOUBLE_COMPLEX: return DOUBLE_COMPLEX_SIZE;
        case TYPE_LONG_DOUBLE_COMPLEX: return LONG_DOUBLE_COMPLEX_SIZE;
        case TYPE_FLOAT_IMAGINARY: return FLOAT_IMAGINARY_SIZE;
        case TYPE_DOUBLE_IMAGINARY: return DOUBLE_IMAGINARY_SIZE;
        case TYPE_LONG_DOUBLE_IMAGINARY: return LONG_DOUBLE_IMAGINARY_SIZE;
        case TYPE_POINTER: return POINTER_SIZE;
        case TYPE_ARRAY: return get_type_size(type->type.array.element_type) * type->type.array.length;
        case TYPE_FUNCTION: return 0;  // functions do not have a size
        case TYPE_STRUCT: return type->type.struct_union_type->size;
        case TYPE_UNION: return type->type.struct_union_type->size;
        case TYPE_ENUM: return ENUM_SIZE;
        default: assert(false);
    }
}

static size_t get_type_align(IR_Type* type) {
    switch (type->type_kind) {
        case TYPE_VOID: return VOID_ALIGN;
        case TYPE_CHAR: return CHAR_ALIGN;
        case TYPE_S_CHAR: return SIGNED_CHAR_ALIGN;
        case TYPE_U_CHAR: return UNSIGNED_CHAR_ALIGN;
        case TYPE_SHORT: return SHORT_ALIGN;
        case TYPE_U_SHORT: return UNSIGNED_SHORT_ALIGN;
        case TYPE_INT: return INT_ALIGN;
        case TYPE_U_INT: return UNSIGNED_INT_ALIGN;
        case TYPE_LONG: return LONG_ALIGN;
        case TYPE_U_LONG: return UNSIGNED_LONG_ALIGN;
        case TYPE_LONG_LONG: return LONG_LONG_ALIGN;
        case TYPE_U_LONG_LONG: return UNSIGNED_LONG_LONG_ALIGN;
        case TYPE_FLOAT: return FLOAT_ALIGN;
        case TYPE_DOUBLE: return DOUBLE_ALIGN;
        case TYPE_LONG_DOUBLE: return LONG_DOUBLE_ALIGN;
        case TYPE_BOOL: return BOOL_ALIGN;
        case TYPE_FLOAT_COMPLEX: return FLOAT_COMPLEX_ALIGN;
        case TYPE_DOUBLE_COMPLEX: return DOUBLE_COMPLEX_ALIGN;
        case TYPE_LONG_DOUBLE_COMPLEX: return LONG_DOUBLE_COMPLEX_ALIGN;
        case TYPE_FLOAT_IMAGINARY: return FLOAT_IMAGINARY_ALIGN;
        case TYPE_DOUBLE_IMAGINARY: return DOUBLE_IMAGINARY_ALIGN;
        case TYPE_LONG_DOUBLE_IMAGINARY: return LONG_DOUBLE_IMAGINARY_ALIGN;
        case TYPE_POINTER: return POINTER_ALIGN;
        case TYPE_ARRAY: return get_type_align(type->type.array.element_type);
        case TYPE_FUNCTION: return 0;  // functions do not have a size
        case TYPE_STRUCT: return type->type.struct_union_type->align;
        case TYPE_UNION: return type->type.struct_union_type->align;
        case TYPE_ENUM: return ENUM_ALIGN;
        default: assert(false);
    }
}

static IR_Expression* analyze_conditional_expression(Semantic* ctx, AST_ConditionalExpression* node) {
    return NULL;  // placeholder
}

static IR_Expression* analyze_assignment_expression(Semantic* ctx, AST_AssignmentExpression* node) {
    return NULL;  // placeholder
}

static IR_Statement* analyze_statement(Semantic* ctx, AST_Statement* node) {
    return NULL;  // placeholder
}

static IR_StructUnion* analyze_struct_union(Semantic* ctx, list(AST_StructDecl*) struct_decls, bool is_struct, Token* name) {
    return NULL;  // placeholder
}

static IR_Enum* analyze_enum(Semantic* ctx, list(AST_Enumerator*) enumerators, Token* name) {
    return NULL;  // placeholder
}

static IR_Type* analyze_type_name(Semantic* ctx, AST_TypeName* node) {
    return NULL;  // placeholder
}

static DeclSpecInfo* analyze_decl_specs(Semantic* ctx, list(AST_DeclSpec*) decl_specs) {
    DeclSpecInfo* decl_spec_info = create_struct(DeclSpecInfo);
    decl_spec_info->type = NULL;
    decl_spec_info->storage = NULL;
    decl_spec_info->align = 0;
    decl_spec_info->align_keyword = NULL;
    decl_spec_info->is_inline = false;
    decl_spec_info->is_noreturn = false;
    decl_spec_info->is_thread_local = false;
    bool is_const = false;
    bool is_restrict = false;
    bool is_volatile = false;
    bool is_atomic = false;
    /*
    complex imaginary bool unsigned signed double float long long int short char void
    4096    2048      1024 512      256    128    64    32   16   8   4     2    1
    */
    int type_bits = 0;

    IR_Type* other = NULL;
    bool has_type_specifier = false;
    bool has_error = false;
    foreach (AST_DeclSpec*, decl, decl_specs) {
        if (decl->specifier_type == SPEC_TYPE_SPEC) {
            has_type_specifier = true;
            AST_TypeSpec* type = decl->specifier.type;
            if (type->spec_type == TYPE_SPEC_KEYWORD) {
                if (type->spec.keyword_spec == KEYWORD_VOID) {
                    if (type_bits & 1) semantic_error(type->token, "Duplicate 'void' type specifier");
                    else type_bits |= 1;
                } else if (type->spec.keyword_spec == KEYWORD_CHAR) {
                    if (type_bits & 2) semantic_error(type->token, "Duplicate 'char' type specifier");
                    else type_bits |= 2;
                } else if (type->spec.keyword_spec == KEYWORD_SHORT) {
                    if (type_bits & 4) semantic_error(type->token, "Duplicate 'short' type specifier");
                    else type_bits |= 4;
                } else if (type->spec.keyword_spec == KEYWORD_INT) {
                    if (type_bits & 8) semantic_error(type->token, "Duplicate 'int' type specifier");
                    else type_bits |= 8;
                } else if (type->spec.keyword_spec == KEYWORD_LONG) {
                    if (type_bits & 32) semantic_error(type->token, "Too many 'long' type specifiers");
                    else if (type_bits & 16) type_bits |= 32;
                    else type_bits |= 16;
                } else if (type->spec.keyword_spec == KEYWORD_FLOAT) {
                    if (type_bits & 64) semantic_error(type->token, "Duplicate 'float' type specifier");
                    else type_bits |= 64;
                } else if (type->spec.keyword_spec == KEYWORD_DOUBLE) {
                    if (type_bits & 128) semantic_error(type->token, "Duplicate 'double' type specifier");
                    else type_bits |= 128;
                } else if (type->spec.keyword_spec == KEYWORD_SIGNED) {
                    if (type_bits & 256) semantic_error(type->token, "Duplicate 'signed' type specifier");
                    else type_bits |= 256;
                } else if (type->spec.keyword_spec == KEYWORD_UNSIGNED) {
                    if (type_bits & 512) semantic_error(type->token, "Duplicate 'unsigned' type specifier");
                    else type_bits |= 512;
                } else if (type->spec.keyword_spec == KEYWORD_BOOL) {
                    if (type_bits & 1024) semantic_error(type->token, "Duplicate '_Bool' type specifier");
                    else type_bits |= 1024;
                } else if (type->spec.keyword_spec == KEYWORD_IMAGINARY) {
                    if (type_bits & 2048) semantic_error(type->token, "Duplicate '_Imaginary' type specifier");
                    else type_bits |= 2048;
                } else if (type->spec.keyword_spec == KEYWORD_COMPLEX) {
                    if (type_bits & 4096) semantic_error(type->token, "Duplicate '_Complex' type specifier");
                    else type_bits |= 4096;
                } else assert(false);
            } else if (type->spec_type == TYPE_SPEC_ATOMIC) {
                IR_Type* t = analyze_type_name(ctx, type->spec.atomic_spec);
                if (t == NULL) {
                    has_error = true;
                    continue;
                }
                if (t->type_kind == TYPE_FUNCTION || t->type_kind == TYPE_ARRAY) {
                    semantic_error(type->token, "Atomic specifier cannot be applied to function or array types");
                    has_error = true;
                    continue;
                }
                if (t->is_atomic || t->is_const || t->is_volatile || t->is_restrict) {
                    semantic_error(type->token, "Atomic specifier cannot be combined with atomic, const, volatile, or restrict qualifiers");
                    has_error = true;
                    continue;
                }
                if (other != NULL) {
                    semantic_error(type->token, "Cannot combine atomic specifier with other type specifiers");
                    continue;
                }
                other = create_struct(IR_Type);
                memcpy(other, t, sizeof(IR_Type));
                other->token = type->token;
                other->is_atomic = true;
                // TODO: in Atomic, size and align depend on the target
            } else if (type->spec_type == TYPE_SPEC_STRUCT_UNION) {
                IR_StructUnion* struct_union = analyze_struct_union(ctx, type->spec.struct_union_spec.members, type->spec.struct_union_spec.is_struct, type->spec.struct_union_spec.identifier);
                if (struct_union == NULL) {
                    has_error = true;
                    continue;
                }
                if (other != NULL) {
                    semantic_error(type->token, "Cannot combine struct/union specifier with other type specifiers");
                    continue;
                }
                other = create_struct(IR_Type);
                other->type.struct_union_type = struct_union;
                other->token = type->token;
                other->type_kind = type->spec.struct_union_spec.is_struct ? TYPE_STRUCT : TYPE_UNION;
            } else if (type->spec_type == TYPE_SPEC_ENUM) {
                IR_Enum* enum_type = analyze_enum(ctx, type->spec.enum_spec.enumerators, type->spec.enum_spec.identifier);
                if (enum_type == NULL) {
                    has_error = true;
                    continue;
                }
                if (other != NULL) {
                    semantic_error(type->token, "Cannot combine enum specifier with other type specifiers");
                    continue;
                }
                other = create_struct(IR_Type);
                other->type.enum_type = enum_type;
                other->token = type->token;
                other->type_kind = TYPE_ENUM;
            } else if (type->spec_type == TYPE_SPEC_TYPEDEF_NAME) {
                IR_Symbol* symbol = find_symbol(ctx->scope, type->spec.typedef_name->value, true);
                if (symbol == NULL || symbol->kind != SYMBOL_TYPEDEF) {
                    semantic_error(type->spec.typedef_name, "Unknown typedef name");
                    has_error = true;
                    continue;
                }
                if (other != NULL) {
                    semantic_error(type->spec.typedef_name, "Cannot combine typedef name with other type specifiers");
                    continue;
                }
                other = create_struct(IR_Type);
                memcpy(other, symbol->type, sizeof(IR_Type));
                other->token = type->spec.typedef_name;
            } else assert(false);
        } else if (decl->specifier_type == SPEC_ALIGNMENT) {
            intmax_t value = 0;
            if (decl->specifier.alignment.is_type_name) {
                IR_Type* type = analyze_type_name(ctx, decl->specifier.alignment.spec.type_name);
                if (type == NULL) continue;
                value = (intmax_t)type->align;
            } else {
                IR_Expression* expr = analyze_conditional_expression(ctx, decl->specifier.alignment.spec.constant_expression);
                if (expr == NULL)
                    continue;
                if (!eval_const_int(expr, &value)) {
                    semantic_error(decl->token, "Alignment specifier is not a constant expression");
                    continue;
                }
            }
            if (value == 0) continue;
            if (value < 0 || (value & (value - 1)) != 0) {
                semantic_error(decl->token, "Alignment specifier must be a positive power of two");
                continue;
            }
            if (decl_spec_info->align <= (uintmax_t)value) {
                decl_spec_info->align = (uintmax_t)value;
                decl_spec_info->align_keyword = decl->token;
            }
        } else if (decl->specifier_type == SPEC_KEYWORD) {
            if (decl->specifier.keyword == KEYWORD_TYPEDEF || decl->specifier.keyword == KEYWORD_EXTERN || decl->specifier.keyword == KEYWORD_STATIC || decl->specifier.keyword == KEYWORD_AUTO || decl->specifier.keyword == KEYWORD_REGISTER) {
                if (decl_spec_info->storage != NULL)
                    semantic_error(decl->token, "Multiple storage class specifiers");
                else
                    decl_spec_info->storage = decl->specifier.keyword;
            } else if (decl->specifier.keyword == KEYWORD_THREAD_LOCAL) decl_spec_info->is_thread_local = true;
            else if (decl->specifier.keyword == KEYWORD_CONST) is_const = true;
            else if (decl->specifier.keyword == KEYWORD_RESTRICT) is_restrict = true;
            else if (decl->specifier.keyword == KEYWORD_VOLATILE) is_volatile = true;
            else if (decl->specifier.keyword == KEYWORD_ATOMIC) is_atomic = true;
            else if (decl->specifier.keyword == KEYWORD_INLINE) decl_spec_info->is_inline = true;
            else if (decl->specifier.keyword == KEYWORD_NORETURN) decl_spec_info->is_noreturn = true;
            else assert(false);
        } else assert(false);
    }
    if (other == NULL) {
        if (has_error) return NULL;
        other = create_struct(IR_Type);
        other->type.basic_type = NULL;
        other->token = peek_front(decl_specs, AST_DeclSpec*)->token;
        // clang-format off
        switch (type_bits) {
            case 0: other->type_kind = TYPE_INT;  // default to int
                if (!has_type_specifier)
                    semantic_warn(other->token, "No type specifier, defaulting to 'int'");
                break;
            case 1: other->type_kind = TYPE_VOID; break;
            case 2: other->type_kind = TYPE_CHAR; break;
            case 258: other->type_kind = TYPE_S_CHAR; break;
            case 514: other->type_kind = TYPE_U_CHAR; break;
            case 4: case 12: case 260: case 268: other->type_kind = TYPE_SHORT; break;
            case 516: case 524: other->type_kind = TYPE_U_SHORT; break;
            case 8: case 256: case 264: other->type_kind = TYPE_INT; break;
            case 512: case 520: other->type_kind = TYPE_U_INT; break;
            case 16: case 24: case 272: case 280: other->type_kind = TYPE_LONG; break;
            case 528: case 536: other->type_kind = TYPE_U_LONG; break;
            case 48: case 56: case 304: case 312: other->type_kind = TYPE_LONG_LONG; break;
            case 560: case 568: other->type_kind = TYPE_U_LONG_LONG; break;
            case 64: other->type_kind = TYPE_FLOAT; break;
            case 128: other->type_kind = TYPE_DOUBLE; break;
            case 144: other->type_kind = TYPE_LONG_DOUBLE; break;
            case 1024: other->type_kind = TYPE_BOOL; break;
            case 4160: other->type_kind = TYPE_FLOAT_COMPLEX; break;
            case 4096: case 4224: other->type_kind = TYPE_DOUBLE_COMPLEX; break;
            case 4240: other->type_kind = TYPE_LONG_DOUBLE_COMPLEX; break;
            case 2112: other->type_kind = TYPE_FLOAT_IMAGINARY; break;
            case 2048: case 2176: other->type_kind = TYPE_DOUBLE_IMAGINARY; break;
            case 2192: other->type_kind = TYPE_LONG_DOUBLE_IMAGINARY; break;
            default:
                semantic_error(other->token, "Invalid combination of type specifiers");
                return NULL;
        }
        // clang-format on
    } else if (type_bits > 0) {
        semantic_error(other->token, "Cannot combine type specifiers with struct/union/enum/typedef");
        return NULL;
    }
    if (other->type_kind == TYPE_ARRAY && (is_const || is_volatile || is_restrict || is_atomic)) {
        IR_Type* t = other;
        while (true) {
            if (t->type_kind != TYPE_ARRAY) break;
            IR_Type* element_type = create_struct(IR_Type);
            memcpy(element_type, t->type.array.element_type, sizeof(IR_Type));
            t->type.array.element_type = element_type;
            t = element_type;
        }
    } else {
        other->is_const |= is_const;
        other->is_volatile |= is_volatile;
    }
    other->size = get_type_size(other);
    other->align = get_type_align(other);
    decl_spec_info->type = other;
    if (decl_spec_info->is_thread_local && decl_spec_info->storage != NULL && decl_spec_info->storage != KEYWORD_EXTERN && decl_spec_info->storage != KEYWORD_STATIC)
        semantic_error(other->token, "Thread-local storage class is only allowed with 'extern' or 'static'");
    if (is_restrict && other->type_kind != TYPE_POINTER)
        semantic_error(other->token, "'restrict' qualifier is not allowed for function type");
    else
        other->is_restrict |= is_restrict;
    if (is_atomic && (other->type_kind == TYPE_FUNCTION || other->type_kind == TYPE_ARRAY))
        semantic_error(other->token, "'atomic' qualifier is not allowed for function or array types");
    else
        other->is_atomic |= is_atomic;
    return decl_spec_info;
}

static IR_Type* analyze_pointer(Semantic* ctx, AST_Pointer* node, IR_Type* base) {
    if (node == NULL) return base;
    assert(node->token != NULL);
    if (base == NULL) return NULL;

    IR_Type* type = create_struct(IR_Type);
    type->token = node->token;
    type->type_kind = TYPE_POINTER;
    type->type.pointer_type = base;
    type->size = POINTER_SIZE;
    type->align = POINTER_ALIGN;
    foreach (string, qual, node->type_qualifiers) {
        if (qual == KEYWORD_CONST) {
            if (type->is_const) semantic_warn(node->token, "Duplicate 'const' qualifier");
            type->is_const = true;
        } else if (qual == KEYWORD_VOLATILE) {
            if (type->is_volatile) semantic_warn(node->token, "Duplicate 'volatile' qualifier");
            type->is_volatile = true;
        } else if (qual == KEYWORD_RESTRICT) {
            if (base != NULL && base->type_kind == TYPE_FUNCTION)
                semantic_error(node->token, "'restrict' qualifier is not allowed for function pointer");
            else if (type->is_restrict)
                semantic_warn(node->token, "Duplicate 'restrict' qualifier");
            type->is_restrict = true;
        } else if (qual == KEYWORD_ATOMIC) {
            if (type->is_atomic) semantic_warn(node->token, "Duplicate 'atomic' qualifier");
            type->is_atomic = true;
        } else assert(false);
    }

    return analyze_pointer(ctx, node->pointer, type);
}

static IR_Type* analyze_array_suffix(Semantic* ctx, AST_DirectDeclarator* node, IR_Type* base) {
    assert(node != NULL);
    assert(node->token != NULL);
    assert(node->decl_type == DECLARATOR_ARRAY || node->decl_type == DECLARATOR_INCOMPLETE_ARRAY);
    if (node->decl_type == DECLARATOR_ARRAY) {
        assert(node->decl.array.assignment_expression != NULL);
        assert(node->decl.array.assignment_expression->token != NULL);
    }

    if (base == NULL) return NULL;
    if (base->type_kind == TYPE_FUNCTION) {
        semantic_error(node->token, "Array of functions is not allowed");
        return NULL;
    }
    if (!is_complete_type(base)) {
        semantic_error(node->token, "Array has incomplete element type");
        return NULL;
    }

    IR_Type* type = create_struct(IR_Type);
    type->token = node->token;
    type->type_kind = TYPE_ARRAY;
    type->type.array.element_type = base;
    if (base->type_kind == TYPE_STRUCT || base->type_kind == TYPE_UNION)
        type->align = base->type.struct_union_type->align;
    else
        type->align = base->align;

    list(string) type_qualifiers = NULL;
    if (node->decl_type == DECLARATOR_ARRAY) {
        type_qualifiers = node->decl.array.type_qualifiers;
        AST_AssignmentExpression* length_expr = node->decl.array.assignment_expression;
        IR_Expression* expr = analyze_assignment_expression(ctx, length_expr);
        if (expr == NULL) return NULL;
        intmax_t length = 0;
        if (!eval_const_int(expr, &length)) {
            semantic_error(length_expr->token, "Array size is not an integer constant expression");
            return NULL;
        }
        if (length <= 0) {
            semantic_error(length_expr->token, "Array size must be greater than 0");
            return NULL;
        }
        size_t element_size = type_size(base);
        if (element_size > 0 && (uintmax_t)length > INTMAX_MAX / element_size / 2) {
            semantic_error(length_expr->token, "Array is too large");
            return NULL;
        }
        type->type.array.length = (uintmax_t)length;
        type->size = (size_t)length * element_size;
    } else
        type_qualifiers = node->decl.incomplete_array.type_qualifiers;

    foreach (string, qual, type_qualifiers) {
        if (qual == KEYWORD_CONST) {
            if (type->is_const) semantic_warn(node->token, "Duplicate 'const' qualifier");
            type->is_const = true;
        } else if (qual == KEYWORD_VOLATILE) {
            if (type->is_volatile) semantic_warn(node->token, "Duplicate 'volatile' qualifier");
            type->is_volatile = true;
        } else if (qual == KEYWORD_RESTRICT) {
            if (type->is_restrict) semantic_warn(node->token, "Duplicate 'restrict' qualifier");
            type->is_restrict = true;
        } else if (qual == KEYWORD_ATOMIC) {
            if (type->is_atomic) semantic_warn(node->token, "Duplicate 'atomic' qualifier");
            type->is_atomic = true;
        } else assert(false);
    }
    return type;
}

static Token* analyze_declarator(Semantic* ctx, AST_Declarator* node, IR_Type* base, IR_Type** out_type);
static IR_Type* analyze_func_suffix(Semantic* ctx, AST_DirectDeclarator* node, IR_Type* base) {
    assert(node != NULL);
    assert(node->token != NULL);
    assert(node->decl_type == DECLARATOR_FUNC);
    assert(node->decl.func.param_decls != NULL);

    if (base == NULL) return NULL;

    bool has_error = false;
    if (base->type_kind == TYPE_ARRAY) {
        semantic_error(node->token, "Function cannot return an array");
        has_error = true;
    } else if (base->type_kind == TYPE_FUNCTION) {
        semantic_error(node->token, "Function cannot return a function");
        has_error = true;
    }

    IR_FuncProto* proto = create_struct(IR_FuncProto);
    *proto = (IR_FuncProto){.token = node->token, .params = create_list(IR_Param*), .return_type = base, .is_variadic = node->decl.func.is_variadic, .scope = create_scope(ctx->scope, SCOPE_PROTO)};
    bool is_only_param = node->decl.func.param_decls->head != NULL && node->decl.func.param_decls->head->next == NULL && !proto->is_variadic;

    ctx->scope = proto->scope;
    foreach (AST_ParamDecl*, param, node->decl.func.param_decls) {
        assert(param->token != NULL);
        assert(param->decl_specs != NULL);
        assert(param->decl != NULL || param->is_abs);
        DeclSpecInfo* info = analyze_decl_specs(ctx, param->decl_specs);
        if (info == NULL) {
            has_error = true;
            continue;
        }
        IR_Type* type = info->type;
        Token* id = NULL;
        if (param->decl != NULL) {
            id = analyze_declarator(ctx, param->decl, info->type, &type);
            if (type == NULL) {
                has_error = true;
                continue;
            }
        }
        assert(param->is_abs == (id == NULL));

        if (info->storage != NULL && info->storage != KEYWORD_REGISTER) {
            semantic_error(param->token, "Invalid storage class for parameter");
            has_error = true;
            continue;
        }
        if (info->is_inline || info->is_noreturn) {
            semantic_error(param->token, "Function specifier is not allowed for parameter");
            has_error = true;
            continue;
        }
        if (type->type_kind == TYPE_VOID) {
            bool is_unqualified = !type->is_const && !type->is_volatile && !type->is_restrict && !type->is_atomic;
            if (!is_only_param || id != NULL || !is_unqualified) {
                semantic_error(param->token, "'void' must be the only parameter, unnamed and unqualified");
                has_error = true;
            }
            continue;
        }

        if (type->type_kind == TYPE_ARRAY) {
            IR_Type* ptr = create_struct(IR_Type);
            *ptr = (IR_Type){.token = type->token, .type.pointer_type = type->type.array.element_type, .type_kind = TYPE_POINTER, .size = POINTER_SIZE, .align = POINTER_ALIGN, .is_const = type->is_const, .is_volatile = type->is_volatile, .is_restrict = type->is_restrict, .is_atomic = type->is_atomic};
            type = ptr;
        } else if (type->type_kind == TYPE_FUNCTION) {
            IR_Type* ptr = create_struct(IR_Type);
            *ptr = (IR_Type){.token = type->token, .type.pointer_type = type, .type_kind = TYPE_POINTER, .size = POINTER_SIZE, .align = POINTER_ALIGN};
            type = ptr;
        }

        IR_Param* ir_param = create_struct(IR_Param);
        *ir_param = (IR_Param){.token = param->token, .type = type};
        if (id != NULL) {
            ir_param->symbol = declare_name(ctx, id, type, SYMBOL_VAR, info->storage);
            if (ir_param->symbol == NULL) has_error = true;
        }
        append(proto->params, ir_param);
    }
    ctx->scope = proto->scope->parent;

    if (has_error) return NULL;
    IR_Type* type = create_struct(IR_Type);
    type->token = node->token;
    type->type_kind = TYPE_FUNCTION;
    type->type.func_type = proto;
    return type;
}

static Token* analyze_direct_declarator(Semantic* ctx, AST_DirectDeclarator* node, IR_Type* base, IR_Type** out_type) {
    if (node == NULL) {
        *out_type = base;
        return NULL;
    }
    assert(node->token != NULL);

    if (node->decl_type == DECLARATOR_ID) {
        assert(node->decl.identifier != NULL);
        *out_type = base;
        return node->decl.identifier;
    } else if (node->decl_type == DECLARATOR_DECL) {
        assert(node->decl.declarator != NULL);
        return analyze_declarator(ctx, node->decl.declarator, base, out_type);
    } else {
        IR_Type* type = NULL;
        AST_DirectDeclarator* direct_decl = NULL;
        if (node->decl_type == DECLARATOR_ARRAY) {
            type = analyze_array_suffix(ctx, node, base);
            direct_decl = node->decl.array.direct_declarator;
        } else if (node->decl_type == DECLARATOR_INCOMPLETE_ARRAY) {
            type = analyze_array_suffix(ctx, node, base);
            direct_decl = node->decl.incomplete_array.direct_declarator;
        } else if (node->decl_type == DECLARATOR_FUNC) {
            type = analyze_func_suffix(ctx, node, base);
            direct_decl = node->decl.func.direct_declarator;
        } else
            assert(false);
        return analyze_direct_declarator(ctx, direct_decl, type, out_type);
    }
}

static Token* analyze_declarator(Semantic* ctx, AST_Declarator* node, IR_Type* base, IR_Type** out_type) {
    assert(node != NULL);
    assert(node->token != NULL);
    assert(node->pointer != NULL || node->direct_declarator != NULL);

    IR_Type* type = analyze_pointer(ctx, node->pointer, base);
    return analyze_direct_declarator(ctx, node->direct_declarator, type, out_type);
}

static IR_Expression* analyze_initializer_scalar(Semantic* ctx, Token* token, IR_Expression* expr, IR_Type* type) {
    assert(token != NULL);
    assert(type != NULL);
    assert(expr != NULL);

    if (type->type_kind == TYPE_ARRAY) {
        if (expr->expr_type != EXPR_STRING || !is_char_type(type->type.array.element_type)) {
            semantic_error(token, "Array must be initialized with a brace-enclosed initializer or string literal");
            return NULL;
        }
        size_t length = expr->expr.string_literal.length;
        if (type->type.array.length == 0) {
            type->type.array.length = length + 1;
            type->size = (length + 1) * type->type.array.element_type->size;
        } else if (length > type->type.array.length)
            semantic_warn(token, "Initializer string for char array is too long");
    } else
        expr = convert_for_assignment(ctx, expr, type, token);
    return expr;
}

static void analyze_error_initializer(Semantic* ctx, AST_Initializer* node) {
    assert(node != NULL);
    if (!node->is_assignment_expr) {
        foreach (AST_InitializerItem*, item, node->init.inits) {
            foreach (AST_Designator*, designator, item->designation) {
                if (designator->is_index)
                    analyze_conditional_expression(ctx, designator->designator.index_expr);
            }
            analyze_error_initializer(ctx, item->initializer);
        }
    } else
        analyze_assignment_expression(ctx, node->init.assignment_expr);
}

static void analyze_initializer(Semantic* ctx, AST_Initializer* node, IR_Type** type, InitNode* tree);
static void analyze_initializer_items(Semantic* ctx, IR_Type* type, InitCursor* cursor, bool is_braced, InitNode* tree) {
    assert(cursor != NULL);
    assert(cursor->node != NULL);
    assert(cursor->node->data != NULL);
    assert(type != NULL);
    assert(type->type_kind == TYPE_ARRAY || type->type_kind == TYPE_STRUCT || type->type_kind == TYPE_UNION);
    assert(tree != NULL);

    uintmax_t index = 0;
    uintmax_t max_index = 0;
    ListNode* member_node = NULL;
    if (type->type_kind != TYPE_ARRAY && !list_empty(type->type.struct_union_type->members))
        member_node = type->type.struct_union_type->members->head;
    ListNode* start = cursor->node;
    while (cursor->node != NULL) {
        assert(cursor->node->data != NULL);

        bool is_first = cursor->node == start;
        if (cursor->designator != NULL && !is_braced && !is_first)
            return;
        AST_InitializerItem* item = cursor->node->data;
        IR_Type* placement_type = NULL;
        uintmax_t placement_offset = 0;
        IR_StructUnionDecl* decl = NULL;

        if (type->type_kind == TYPE_ARRAY) {
            if (cursor->designator != NULL) {
                AST_Designator* designator = cursor->designator->data;
                if (!designator->is_index) {
                    semantic_error(designator->token, "Member designator is not allowed for array type");
                    analyze_error_initializer(ctx, item->initializer);
                    update_cursor(cursor);
                    continue;
                }
                IR_Expression* expr = analyze_conditional_expression(ctx, designator->designator.index_expr);
                if (expr == NULL) {
                    analyze_error_initializer(ctx, item->initializer);
                    update_cursor(cursor);
                    continue;
                }
                intmax_t v = 0;
                char* msg = NULL;
                size_t element_size = type_size(type->type.array.element_type);
                if (!eval_const_int(expr, &v))
                    msg = "Array index is not a constant expression";
                else if (v < 0)
                    msg = "Array index is negative";
                else if (type->type.array.length > 0 && (uintmax_t)v >= type->type.array.length)
                    msg = "Array index is out of bounds";
                else if (type->type.array.length == 0 && element_size > 0 && (uintmax_t)v >= INTMAX_MAX / element_size / 2)
                    msg = "Array is too large";
                if (msg != NULL) {
                    semantic_error(designator->token, msg);
                    analyze_error_initializer(ctx, item->initializer);
                    update_cursor(cursor);
                    continue;
                }
                index = (uintmax_t)v;
                cursor->designator = cursor->designator->next;
            }
            if (type->type.array.length > 0 && index >= type->type.array.length) {
                if (!is_braced) return;
                semantic_warn(item->token, "Excess elements in array initializer");
                analyze_error_initializer(ctx, item->initializer);
                update_cursor(cursor);
                continue;
            }
            placement_type = type->type.array.element_type;
            placement_offset = tree->offset + index * type_size(placement_type);
        } else {
            if (cursor->designator != NULL) {
                AST_Designator* designator = cursor->designator->data;
                if (designator->is_index) {
                    semantic_error(designator->token, "Array index designator is not allowed for struct/union type");
                    analyze_error_initializer(ctx, item->initializer);
                    update_cursor(cursor);
                    continue;
                }
                assert(designator->designator.member->type == TOKEN_IDENTIFIER);
                ListNode* member = find_member(type, designator->designator.member->value);
                if (member == NULL) {
                    semantic_error(designator->token, "Member designator does not match any member of struct/union");
                    analyze_error_initializer(ctx, item->initializer);
                    update_cursor(cursor);
                    continue;
                }
                decl = member->data;
                if (decl->type->type_kind == TYPE_ARRAY && decl->type->type.array.length == 0) {
                    semantic_error(designator->token, "Initialization of flexible array member is not supported");
                    analyze_error_initializer(ctx, item->initializer);
                    update_cursor(cursor);
                    continue;
                }
                if (decl->name != NULL)
                    cursor->designator = cursor->designator->next;
                member_node = member;
            }
            for (; member_node != NULL; member_node = member_node->next) {
                decl = member_node->data;
                if (decl->type->type_kind == TYPE_ARRAY && decl->type->type.array.length == 0)
                    continue;
                if (decl->name != NULL || decl->type->type_kind == TYPE_STRUCT || decl->type->type_kind == TYPE_UNION)
                    break;
            }
            if (member_node == NULL) {
                if (!is_braced && !is_first) return;
                semantic_warn(item->token, "Excess elements in struct/union initializer");
                if (cursor->expr == NULL)
                    analyze_error_initializer(ctx, item->initializer);
                update_cursor(cursor);
                continue;
            }
            assert(decl != NULL);
            placement_type = decl->type;
            placement_offset = tree->offset + decl->offset;
        }

        InitNode* child = get_child(tree, index, decl, placement_type, placement_offset, item->token);
        if (cursor->designator != NULL) {
            AST_Designator* designator = cursor->designator->data;
            if (placement_type->type_kind == TYPE_ARRAY || placement_type->type_kind == TYPE_STRUCT || placement_type->type_kind == TYPE_UNION) {
                analyze_initializer_items(ctx, placement_type, cursor, false, child);
            } else {
                semantic_error(designator->token, "Designator is not allowed for scalar type");
                analyze_error_initializer(ctx, item->initializer);
                update_cursor(cursor);
            }
        } else if (!item->initializer->is_assignment_expr) {
            analyze_initializer(ctx, item->initializer, &placement_type, child);
            update_cursor(cursor);
        } else {
            if (cursor->expr == NULL)
                cursor->expr = analyze_assignment_expression(ctx, item->initializer->init.assignment_expr);
            bool is_recursive = false;
            if (cursor->expr != NULL) {
                IR_Expression* init = NULL;
                bool is_direct = (placement_type->type_kind != TYPE_ARRAY && placement_type->type_kind != TYPE_STRUCT && placement_type->type_kind != TYPE_UNION) ||
                                 (placement_type->type_kind == TYPE_ARRAY && is_char_type(placement_type->type.array.element_type) && cursor->expr->expr_type == EXPR_STRING) ||
                                 (placement_type->type_kind != TYPE_ARRAY && cursor->expr->type->type_kind == placement_type->type_kind && cursor->expr->type->type.struct_union_type == placement_type->type.struct_union_type);
                if (is_direct)
                    init = analyze_initializer_scalar(ctx, item->token, cursor->expr, placement_type);
                else
                    analyze_initializer_items(ctx, placement_type, cursor, false, child);
                if (init != NULL) {
                    child->expr = init;
                    child->token = init->token;
                    child->is_set = true;
                    child->head = NULL;
                    child->tail = NULL;
                }
            }
            if (!is_recursive)
                update_cursor(cursor);
        }
        if (type->type_kind == TYPE_ARRAY) {
            index++;
            if (index > max_index)
                max_index = index;
        } else
            member_node = type->type_kind == TYPE_STRUCT ? member_node->next : NULL;
    }
    if (type->type_kind == TYPE_ARRAY && type->type.array.length == 0) {
        type->type.array.length = max_index;
        type->size = max_index * type_size(type->type.array.element_type);
    }
}

static void analyze_initializer(Semantic* ctx, AST_Initializer* node, IR_Type** target_type, InitNode* tree) {
    assert(node != NULL);
    assert(node->token != NULL);
    assert(target_type != NULL);
    assert(*target_type != NULL);
    assert(tree != NULL);

    tree->token = node->token;
    tree->expr = NULL;
    tree->head = NULL;
    tree->tail = NULL;
    tree->is_set = true;
    IR_Type* type = *target_type;
    if (type->type_kind == TYPE_ARRAY && type->type.array.length == 0) {
        type = create_struct(IR_Type);
        *type = **target_type;
        *target_type = type;
        tree->type = type;
    }

    if (node->is_assignment_expr) {
        assert(node->init.assignment_expr != NULL);
        IR_Expression* expr = analyze_assignment_expression(ctx, node->init.assignment_expr);
        if (expr == NULL) return;
        expr = analyze_initializer_scalar(ctx, node->token, expr, type);
        if (expr != NULL) {
            tree->expr = expr;
            tree->token = expr->token;
        }
        return;
    }

    assert(node->init.inits != NULL);
    if (type->type_kind != TYPE_ARRAY && type->type_kind != TYPE_STRUCT && type->type_kind != TYPE_UNION) {
        bool is_first = true;
        foreach (AST_InitializerItem*, item, node->init.inits) {
            assert(item->token != NULL);
            assert(item->initializer != NULL);
            if (!list_empty(item->designation)) {
                semantic_error(item->token, "Designator is not allowed for scalar type");
                analyze_error_initializer(ctx, item->initializer);
                continue;
            }
            if (!is_first) {
                semantic_warn(item->token, "Excess elements in scalar initializer");
                analyze_error_initializer(ctx, item->initializer);
                continue;
            }
            is_first = false;
            if (!item->initializer->is_assignment_expr)
                semantic_warn(item->token, "Too many braces around scalar initializer");
            analyze_initializer(ctx, item->initializer, target_type, tree);
        }
        return;
    }

    if (list_empty(node->init.inits)) {
        if (type->type_kind == TYPE_ARRAY && type->type.array.length == 0)
            semantic_error(node->token, "Cannot deduce array size from empty initializer");
        return;
    }

    InitCursor* cursor = &(InitCursor){.node = node->init.inits->head, .designator = NULL, .expr = NULL};
    assert(cursor->node != NULL && cursor->node->data != NULL);
    AST_InitializerItem* item = cursor->node->data;
    if (!list_empty(item->designation))
        cursor->designator = item->designation->head;

    if (type->type_kind == TYPE_ARRAY && is_char_type(type->type.array.element_type) && cursor->designator == NULL) {
        if (item->initializer->is_assignment_expr) {
            cursor->expr = analyze_assignment_expression(ctx, item->initializer->init.assignment_expr);
            if (cursor->expr == NULL || cursor->expr->expr_type == EXPR_STRING) {
                if (cursor->expr != NULL) {
                    IR_Expression* expr = analyze_initializer_scalar(ctx, item->token, cursor->expr, type);
                    if (expr != NULL) {
                        tree->expr = expr;
                        tree->token = expr->token;
                    }
                    if (cursor->node->next != NULL)
                        semantic_warn(((AST_InitializerItem*)cursor->node->next->data)->token, "Excess elements in char array initializer");
                }
                for (ListNode* excess = cursor->node->next; excess != NULL; excess = excess->next)
                    analyze_error_initializer(ctx, ((AST_InitializerItem*)excess->data)->initializer);
                return;
            }
        }
    }
    analyze_initializer_items(ctx, type, cursor, true, tree);
}

static void analyze_static_assert_decl(Semantic* ctx, AST_StaticAssertDecl* node) {
    assert(node != NULL);
    assert(node->token != NULL);
    assert(node->expr != NULL);
    assert(node->expr->token != NULL);
    assert(node->message != NULL);
    assert(node->message->type == TOKEN_STRING);

    IR_Expression* expr = analyze_conditional_expression(ctx, node->expr);
    if (expr == NULL) return;
    intmax_t value = 0;
    if (!eval_const_int(expr, &value))
        semantic_error(node->expr->token, "This expression is not a constant expression.");
    else if (value == 0)
        static_assert_report(ctx, node->token, node->message->literal.str);
}

static IR_Decl* analyze_init_decl(Semantic* ctx, AST_InitDecl* node, DeclSpecInfo* info) {
    assert(node != NULL);
    assert(node->token != NULL);
    assert(node->declarator != NULL);

    IR_Type* type = NULL;
    Token* id = analyze_declarator(ctx, node->declarator, info->type, &type);
    assert(id != NULL);
    if (type == NULL) return NULL;

    IR_SymbolKind kind = SYMBOL_VAR;
    if (info->storage == KEYWORD_TYPEDEF) kind = SYMBOL_TYPEDEF;
    else if (type->type_kind == TYPE_FUNCTION) kind = SYMBOL_FUNC;

    IR_Symbol* symbol = declare_name(ctx, id, type, kind, info->storage);
    if (symbol == NULL) return NULL;

    if (kind == SYMBOL_TYPEDEF) {
        if (node->initializer != NULL)
            semantic_error(node->token, "typedef is initialized");
        return NULL;
    }

    if (kind == SYMBOL_VAR && !is_complete_type(symbol->type)) {
        bool is_allowed = false;
        if (node->initializer != NULL)
            is_allowed = symbol->type->type_kind == TYPE_ARRAY;
        else
            is_allowed = info->storage == KEYWORD_EXTERN || (ctx->scope->kind == SCOPE_FILE && symbol->type->type_kind != TYPE_VOID);
        if (!is_allowed) {
            semantic_error(id, "Variable has incomplete type");
            return NULL;
        }
    }

    IR_Decl* decl = create_struct(IR_Decl);
    *decl = (IR_Decl){.token = node->token, .symbol = symbol};
    if (kind == SYMBOL_FUNC) {
        if (node->initializer != NULL)
            semantic_error(node->token, "Function is initialized like a variable");
        decl->is_func_proto = true;
        decl->decl.func_proto = type->type.func_type;
    } else if (node->initializer != NULL) {
        InitNode* tree = create_init_tree(symbol->type);
        analyze_initializer(ctx, node->initializer, &symbol->type, tree);
        decl->decl.initializer = create_list(IR_Initializer*);
        convert_init_tree(tree, false, decl->decl.initializer);
        symbol->is_defined = true;
    }
    return decl;
}

static list(IR_Decl*) analyze_var_decl(Semantic* ctx, AST_VarDecl* node) {
    assert(node != NULL);
    assert(node->token != NULL);
    if (!node->is_static_assert_decl) {
        assert(node->decl.general_decl.decl_specs != NULL);
        assert(node->decl.general_decl.init_decls != NULL);
    } else
        assert(node->decl.static_assert_decl != NULL);

    list(IR_Decl*) result = create_list(IR_Decl*);
    if (node->is_static_assert_decl) {
        analyze_static_assert_decl(ctx, node->decl.static_assert_decl);
        return result;
    }
    DeclSpecInfo* info = analyze_decl_specs(ctx, node->decl.general_decl.decl_specs);
    if (info == NULL) return result;

    foreach (AST_InitDecl*, init_decl, node->decl.general_decl.init_decls) {
        IR_Decl* decl = analyze_init_decl(ctx, init_decl, info);
        if (decl != NULL)
            append(result, decl);
    }
    return result;
}

static IR_FuncDef* analyze_func_decl(Semantic* ctx, AST_FuncDecl* node) {
    assert(node != NULL);
    assert(node->token != NULL);
    assert(node->decl_specs != NULL);
    assert(node->declarator != NULL);
    assert(node->body != NULL);

    DeclSpecInfo* info = analyze_decl_specs(ctx, node->decl_specs);
    if (info == NULL) return NULL;
    if (info->storage == KEYWORD_TYPEDEF || info->storage == KEYWORD_REGISTER || info->storage == KEYWORD_AUTO) {
        semantic_error(node->token, "Invalid storage class for function");
        return NULL;
    }
    IR_Type* type = NULL;
    Token* id = analyze_declarator(ctx, node->declarator, info->type, &type);
    assert(id != NULL);
    if (type == NULL) return NULL;
    if (type->type_kind != TYPE_FUNCTION || type == info->type) {
        semantic_error(node->token, "Function declarator must have function type");
        return NULL;
    }
    IR_FuncProto* proto = type->type.func_type;
    proto->name = id->value;
    if (proto->return_type->type_kind != TYPE_VOID && !is_complete_type(proto->return_type)) {
        semantic_error(node->token, "Function has incomplete return type");
        return NULL;
    }
    bool has_error = false;
    foreach (IR_Param*, param, proto->params) {
        if (!is_complete_type(param->type)) {
            semantic_error(param->token, "Function has incomplete parameter type");
            has_error = true;
        }
        if (param->symbol == NULL)
            semantic_warn(param->token, "Function has unnamed parameter");
    }
    if (has_error) return NULL;
    IR_Symbol* symbol = declare_name(ctx, id, type, SYMBOL_FUNC, info->storage);
    if (symbol == NULL) return NULL;
    if (symbol->is_defined) {
        semantic_error(node->token, "Function is already defined");
        return NULL;
    }
    symbol->is_defined = true;
    IR_FuncDef* func = create_struct(IR_FuncDef);
    *func = (IR_FuncDef){.token = node->token, .proto = proto, .locals = create_list(IR_Symbol*), .labels = create_list(IR_Symbol*)};
    ctx->func = func;
    ctx->scope = proto->scope;
    list(IR_Statement*) stmts = create_list(IR_Statement*);
    foreach (AST_DeclStmt*, item, node->body) {
        if (item->is_var_decl) {
            foreach (IR_Decl*, decl, analyze_var_decl(ctx, item->item.var_decl)) {
                IR_Statement* stmt = create_struct(IR_Statement);
                *stmt = (IR_Statement){.token = decl->token, .stmt.decl = decl, .stmt_type = IR_STMT_DECL};
                append(stmts, stmt);
            }
        } else {
            IR_Statement* stmt = analyze_statement(ctx, item->item.statement);
            if (stmt != NULL)
                append(stmts, stmt);
        }
    }
    func->body = create_struct(IR_CompoundStatement);
    *func->body = (IR_CompoundStatement){.token = node->token, .statements = stmts, .scope = proto->scope};
    foreach (IR_Symbol*, label, func->labels) {
        if (!label->is_defined)
            semantic_error(label->token, "Label is used but not defined");
    }
    ctx->scope = proto->scope->parent;
    ctx->func = NULL;
    return func;
}

static list(IR_ExternDecl*) analyze_extern_decl(Semantic* ctx, AST_ExternDecl* node) {
    assert(node != NULL);
    assert(node->token != NULL);
    if (node->is_func_decl)
        assert(node->decl.func_decl != NULL);
    else
        assert(node->decl.var_decl != NULL);

    list(IR_ExternDecl*) result = create_list(IR_ExternDecl*);
    if (node->is_func_decl) {
        IR_FuncDef* func_def = analyze_func_decl(ctx, node->decl.func_decl);
        if (func_def == NULL) return result;
        IR_ExternDecl* extern_decl = create_struct(IR_ExternDecl);
        *extern_decl = (IR_ExternDecl){.token = node->token, .decl.func_def = func_def, .is_func = true, .is_func_def = true};
        append(result, extern_decl);
        return result;
    }
    foreach (IR_Decl*, decl, analyze_var_decl(ctx, node->decl.var_decl)) {
        IR_ExternDecl* extern_decl = create_struct(IR_ExternDecl);
        if (decl->is_func_proto)
            *extern_decl = (IR_ExternDecl){.token = node->token, .decl.func_proto = decl->decl.func_proto, .is_func = true};
        else
            *extern_decl = (IR_ExternDecl){.token = node->token, .decl.var_decl = decl};
        append(result, extern_decl);
    }
    return result;
}

IR_TU* semantic_analyze(AST_TU* ast) {
    assert(ast != NULL);
    assert(ast->token != NULL);
    assert(ast->filename != NULL);
    assert(ast->extern_decls != NULL);

    IR_TU* tu = create_struct(IR_TU);
    *tu = (IR_TU){.token = ast->token, .extern_decls = create_list(IR_ExternDecl*), .global_scope = create_scope(NULL, SCOPE_FILE), .static_vars = create_list(IR_Symbol*), .filename = ast->filename};
    Semantic ctx = {.tu = tu, .func = NULL, .scope = tu->global_scope, .error_count = 0};
    foreach (AST_ExternDecl*, extern_decl, ast->extern_decls)
        foreach (IR_ExternDecl*, decl, analyze_extern_decl(&ctx, extern_decl))
            append(tu->extern_decls, decl);
    return tu;
}
