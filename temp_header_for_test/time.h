#ifndef _TIME_H
#define _TIME_H
#include <stddef.h>
typedef long long time_t;
struct tm {
    int placeholder;
};
time_t time(time_t* t);
struct tm* localtime(const time_t* t);
size_t strftime(char* buffer, size_t size, const char* format, const struct tm* tm);
#endif
