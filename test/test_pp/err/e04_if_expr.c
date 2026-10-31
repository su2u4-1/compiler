#define F(x) x
#if                          // E: Expected primary expression
#endif
#if 1 +                      // E: Expected primary expression
#endif
#if (1                       // E: Expected ) after expression
#endif
#if 1.5                      // E: Floating constant in preprocessor expression
#endif
#if 08                       // E: Invalid digit in integer constant
#endif
#if 1abc                     // E: Invalid digit in integer constant
#endif
#if 12xyz                    // E: Invalid suffix on integer constant
#endif
#if 0x                       // E: Integer constant has no digits
#endif
#if 99999999999999999999     // E: Integer constant is too large
#endif
#if 1 / 0                    // E: Division by zero
#endif
#if 1 % 0                    // E: Modulo by zero
#endif
#if 1 << -1                  // E: Negative shift count
#endif
#if 1 << 64                  // E: Shift count too large
#endif
#if 1 2                      // E: Unexpected token after conditional expression
#endif
#if "str"                    // E: Expected primary expression
#endif
#if defined                  // E: Expected identifier after defined
#endif
#if defined(X                // E: Expected ) after defined(identifier)
#endif
#if 1 ? 2                    // E: Expected : in conditional expression
#endif
#if F(1                      // E: Unterminated macro arguments（指令內不能跨行）
#endif
#if 0
#elif 1.5                    // E: #elif 內同樣會報
#endif
// ---- 以下只有警告 ----
#if 'ab' == 24930            // W: Multi-character character constant
#endif
#if 18446744073709551615 > 0 // W: Integer constant is so large that it is unsigned
#endif
