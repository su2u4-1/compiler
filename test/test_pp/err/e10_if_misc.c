#undef 123                   // E: Expected macro name after #undef
#if 1 ## 2                   // E: Unexpected token after conditional expression
#endif
#if 0x1p3                    // E: Floating constant
#endif
#if .5                       // E: Floating constant
#endif
#if 5.                       // E: Floating constant
#endif
#if 1e5                      // E: Floating constant
#endif
#if sizeof(int)              // E: Unexpected token（sizeof 不是運算子，被當成識別字 0）
#endif
#if (int)1                   // E: Unexpected token
#endif
#if 1, 2                     // E: Unexpected token（沒有逗號運算子）
#endif
#if a->b                     // E: Unexpected token
#endif
#define EMPTY2
#include EMPTY2              // E: Expected header name in #include
#include UNDEFINED_MACRO     // E: Invalid token in #include header name
#define CAT(a, b) a ## b
CAT(/, *)                    // E: Pasting "/" and "*" does not give a valid preprocessing token
