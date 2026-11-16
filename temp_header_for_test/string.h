#ifndef _STRING_H
#define _STRING_H
#include <stddef.h>
size_t strlen(const char* str);
int strcmp(const char* a, const char* b);
int strncmp(const char* a, const char* b, size_t count);
int memcmp(const void* a, const void* b, size_t size);
void* memcpy(void* dst, const void* src, size_t size);
void* memmove(void* dst, const void* src, size_t size);
void* memset(void* dst, int value, size_t size);
#endif
