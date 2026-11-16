#ifndef _STDARG_H
#define _STDARG_H
typedef void* va_list;
void va_start(va_list ap, ...);
void va_end(va_list ap);
#endif
