#ifndef FILE_H
#define FILE_H

#include "lib.h"

typedef struct Path {
    string root;
    string dir;
    string filename;
    string extension;
    string str;
    bool rooted;
    bool normalized;
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
bool path_is_absolute(const Path* p);
bool path_equal(const Path* a, const Path* b);
bool path_exists(const Path* p);
bool path_is_dir(const Path* p);

void add_include_dir(string dir);
string find_file(string name, bool is_system, string current_file);

#endif  // FILE_H
