#ifndef FILE_H
#define FILE_H

#include "lib.h"

void add_include_dir(string dir);
string find_file(string name, bool is_system, string current_file);

#endif  // FILE_H
