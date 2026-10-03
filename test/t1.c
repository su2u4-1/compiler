#include "lib.h"
#include <stdlib.h>

#define abc

#if defined(abc)
#define def 1
#else
#define def 2
#endif

#if def == 1
#define ghi 'c'
#elif not defined(abc)
#define ghi 'd'
#endif

#define ff(temp) \
    temp * 2

int main(void) {
    int x = ff(21);
    float f = 3.14f;
    double d = .5;
    long l = 0x1FULL;
    unsigned u = def;
    int oct = 0755;
    char c = '\n';
    char h = '\x41';
    char u4 = ghi;
    string s = "\"hello\tworld\"";
    char* str =
        "This is a string literal\
 with escape sequences: \n\t\\\"\'";
    int a\
b\
cd = 5;
    x++;
    --x;
    x += 2;
    x <<= 1;
    if (x > 0 && x != 1) return 0;
    else return 1;
    // line comment
    /* block
       comment */
    for (;;) break;
}
