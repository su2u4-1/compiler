#ifndef _STDIO_H
#define _STDIO_H
#include <stddef.h>
#include <stdarg.h>
typedef struct {
    void* placeholder;
} FILE;
extern FILE* stderr;
#define SEEK_END 2
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
#endif
