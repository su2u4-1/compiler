// C17 6.10.3.5 EXAMPLE 4（拿掉 str(: @\n)：@ 與 \ 在你的 preprocessor 是錯誤字元，改測 pp_other 另見 err/e05）
#define str(s) # s
#define xstr(s) str(s)
#define debug(s, t) printf("x" # s "= %d, x" # t "= %s", \
 x ## s, x ## t)
#define INCFILE(n) vers ## n
#define glue(a, b) a ## b
#define xglue(a, b) glue(a, b)
#define HIGHLOW "hello"
#define LOW LOW ", world"
debug(1, 2);
fputs(str(strncmp("abc\0d", "abc", '\4') // this goes away
 == 0) str(: x), s);
xstr(INCFILE(2).h)
glue(HIGH, LOW);
xglue(HIGH, LOW)
// 預期:
// printf("x" "1" "= %d, x" "2" "= %s", x1, x2);
// fputs("strncmp(\"abc\\0d\", \"abc\", '\\4') == 0" ": x", s);
// "vers2.h"
// "hello";
// "hello" ", world"
