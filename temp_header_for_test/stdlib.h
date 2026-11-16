#ifndef _STDLIB_H
#define _STDLIB_H
#include <stddef.h>
void* malloc(size_t size);
void* calloc(size_t count, size_t size);
void free(void* p);
void abort(void);
double strtod(const char* str, char** end);
float strtof(const char* str, char** end);
long double strtold(const char* str, char** end);
#endif
