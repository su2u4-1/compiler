#foo bar                     // E: Unknown preprocessor directive
# 33 "file.c"                // E: Expected directive after #
#error this is a custom message   // E: Encountered #error directive: this is a custom message
#if 0
#error skipped group          // 不該觸發
#foo                          // 不該觸發
#endif
#line 5                      // 靜默忽略
#pragma once                 // 靜默忽略
int x = a @ b;               // E: Unexpected token: @
int y = `;                   // E: Unexpected token: `
char *s = "abc;              // E: Unterminated string literal
char c = 'a;                 // E: Unterminated char literal
