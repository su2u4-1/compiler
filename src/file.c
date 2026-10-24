#include "file.h"

#if WIN_PATH
#define is_sep(c) ((c) == '\\' || (c) == '/')
#else
#define is_sep(c) ((c) == '/')
#endif

// `/x`, `\ x`, `C:\ x`, `C:/x`
static bool path_is_absolute(string path) {
    return false;  // placeholder
}

// get directory part
static string path_dirname(string path) {
    return NULL;  // placeholder
}

// get filename part
static string path_basename(string path) {
    return NULL;  // placeholder
}

// if b is abs_path return b; if a is empty return b;
static string path_join(string a, string b) {
    return NULL;  // placeholder
}

// return extension part, including `.`
static string path_extension(string path) {
    return NULL;  // placeholder
}

// check if path exists
static string path_exists(string path) {
    return NULL;  // placeholder
}

// check if path is directory
static string path_is_dir(string path) {
    return NULL;  // placeholder
}

// return absolute path
static string path_absolute(string path) {
    return NULL;  // placeholder
}

static size_t root_length(const char* s, size_t n, bool* rooted) {
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

static string path_normalize(string path) {
    assert(path != NULL);
    size_t len = strlen(path);
    char* out = (char*)malloc(len + 2);
    if (out == NULL) {
        fprintf(stderr, "[path Fatal] at <path_normalize>: Cannot allocate memory\n");
        abort();
    }
    size_t pos = 0;
    size_t k = 0;

#if WIN_PATH
    if (len >= 2 && is_sep(path[0]) && is_sep(path[1]) && !(len >= 3 && is_sep(path[2]))) {
        out[pos++] = '/';
        out[pos++] = '/';
        k = 2;
    }
#endif
    for (; k < len; k++) {
        char c = path[k];
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

    string result = create_string(out, r);
    free(out);
    return result;
}

static list(string) include_dir = NULL;

void add_include_dir(string dir) {
    if (include_dir == NULL)
        include_dir = create_list(string);
}

string find_file(string name, bool is_system, string current_file) {
    if (include_dir == NULL)
        include_dir = create_list(string);

    // TODO

    return NULL;  // placeholder
}
