#include "file.h"

#include <sys/stat.h>
#if WIN_PATH
#include <direct.h>
#define is_sep(c) ((c) == '\\' || (c) == '/')
#define get_cwd(buf, size) _getcwd(buf, size)
#else
#include <unistd.h>
#define is_sep(c) ((c) == '/')
#define get_cwd(buf, size) getcwd(buf, size)
#endif

static size_t root_length(string s, size_t n, bool* rooted) {
    *rooted = false;
#if WIN_PATH
    if (n >= 2 && ((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z')) && s[1] == ':') {
        if (n >= 3 && s[2] == '/') {  // C:/
            *rooted = true;
            return 3;
        }
        return 2;  // C:
    }
    if (n >= 3 && s[0] == '/' && s[1] == '/') {  // UNC: //server/share[/]
        size_t j = 2;
        for (int part = 0; part < 2; part++) {
            size_t start = j;
            while (j < n && s[j] != '/')
                j++;
            size_t seg = j - start;
            if (seg == 0 || (s[start] == '.' && (seg == 1 || (seg == 2 && s[start + 1] == '.'))))
                break;
            if (part == 0) {
                if (j >= n) break;
                j++;
            } else {
                if (j < n) j++;
                *rooted = true;
                return j;
            }
        }
    }
#endif
    if (n >= 1 && s[0] == '/') {
        *rooted = true;
        return 1;
    }
    return 0;
}
static void path_normalize(Path* p, const char* raw) {
    assert(p != NULL && raw != NULL);
    size_t len = strlen(raw);
    char* out = (char*)malloc(len + 2);
    if (out == NULL) {
        fprintf(stderr, "[path Fatal] at <path_normalize>: Cannot allocate memory\n");
        abort();
    }
    size_t pos = 0;
    size_t k = 0;

#if WIN_PATH
    if (len >= 2 && is_sep(raw[0]) && is_sep(raw[1]) && !(len >= 3 && is_sep(raw[2]))) {
        out[pos++] = '/';
        out[pos++] = '/';
        k = 2;
    }
#endif
    for (; k < len; k++) {
        char c = raw[k];
        if (is_sep(c)) {
            if (pos == 0 || out[pos - 1] != '/')
                out[pos++] = '/';
        } else
            out[pos++] = c;
    }

    bool rooted;
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
            // empty segment
        } else if (seg_len == 1 && out[i] == '.') {
            // "."
        } else if (seg_len == 2 && out[i] == '.' && out[i + 1] == '.') {
            bool top_is_dotdot = (r - base >= 2 && out[r - 1] == '.' && out[r - 2] == '.' && (r - base == 2 || out[r - 3] == '/'));
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
    p->normalized = true;
    free(out);
}
static string compose(const char* root, const char* dir, const char* filename, const char* extension) {
    bool has_name = (filename[0] != '\0' || extension[0] != '\0');
    if (root[0] == '\0' && dir[0] == '\0' && !has_name)
        return create_string(".", 1);
    if (dir[0] != '\0' && has_name)
        return string_splice("%s%s/%s%s", root, dir, filename, extension);
    if (root[0] == '\0' && dir[0] == '\0')
        return string_splice("%s%s", filename, extension);
    return string_splice("%s%s%s%s", root, dir, filename, extension);
}
Path* create_path(string raw) {
    assert(raw != NULL);
    Path* p = create_struct(Path);
    path_normalize(p, raw);
    return p;
}

Path* path_join(const Path* a, const Path* b) {
    assert(a != NULL && b != NULL);
    if (b->rooted || a->str == SYMBOL_DOT)
        return create_path(b->str);
    size_t la = strlen(a->str);
    if (a->str[la - 1] == '/' || a->str == a->root)
        return create_path(string_splice("%s%s", a->str, b->str));
    else
        return create_path(string_splice("%s/%s", a->str, b->str));
}
Path* path_change_ext(const Path* p, string ext) {
    assert(p != NULL && ext != NULL);
    if (p->filename[0] == '\0' || p->filename == SYMBOL_DOT || strcmp(p->filename, "..") == 0)
        return create_path(p->str);
    string new_ext = (ext[0] == '\0' || ext[0] == '.') ? ext : string_splice(".%s", ext);
    return create_path(compose(p->root, p->dir, p->filename, new_ext));
}
Path* path_change_filename(const Path* p, string name) {
    assert(p != NULL && name != NULL);
    return create_path(compose(p->root, p->dir, name, p->extension));
}
Path* path_absolute(const Path* p) {
    assert(p != NULL);
    if (p->rooted)
        return create_path(p->str);
    char cwd[4096];
    if (get_cwd(cwd, sizeof(cwd)) == NULL) {
        fprintf(stderr, "[path Error] at <path_absolute>: Cannot get current working directory\n");
        return create_path(p->str);  // fallback to original path
    }
    return path_join(create_path(cwd), p);
}

string path_str(const Path* p) {
    assert(p != NULL);
    return p->str;
}
string path_dirname(const Path* p) {
    assert(p != NULL);
    return compose(p->root, p->dir, "", "");
}
string path_root_str(const Path* p) {
    assert(p != NULL);
    return p->root;
}
string path_filename(const Path* p) {
    assert(p != NULL);
    return p->filename;
}
string path_extension(const Path* p) {
    assert(p != NULL);
    return p->extension;
}

bool path_is_absolute(const Path* p) {
    assert(p != NULL);
    return p->rooted;
}
bool path_equal(const Path* a, const Path* b) {
    assert(a != NULL && b != NULL);
    return a->str == b->str;
}
bool path_exists(const Path* p) {
    assert(p != NULL);
    struct stat st;
    return stat(p->str, &st) == 0;
}
bool path_is_dir(const Path* p) {
    assert(p != NULL);
    struct stat st;
    return stat(p->str, &st) == 0 && S_ISDIR(st.st_mode);
}

// === for include ===

static list(string) include_dir = NULL;

void add_include_dir(string dir) {
    if (include_dir == NULL)
        include_dir = create_list(string);
    if (dir == NULL || dir[0] == '\0')
        return;
    string normalized_dir = create_path(dir)->str;
    foreach (string, d, include_dir)
        if (d == normalized_dir)
            return;
    append(include_dir, normalized_dir);
}

string find_file(string name, bool is_system, string current_file) {
    if (include_dir == NULL)
        include_dir = create_list(string);
    if (name == NULL || name[0] == '\0')
        return NULL;

    Path* n = create_path(name);

    if (n->rooted) {
        if (path_exists(n) && !path_is_dir(n))
            return n->str;
        return NULL;
    }

    if (!is_system && current_file != NULL) {
        Path* dir = create_path(path_dirname(create_path(current_file)));
        Path* path = path_join(dir, n);
        if (path_exists(path) && !path_is_dir(path))
            return path->str;
    }

    foreach (string, d, include_dir) {
        Path* path = path_join(create_path(d), n);
        if (path_exists(path) && !path_is_dir(path))
            return path->str;
    }
    return NULL;
}
