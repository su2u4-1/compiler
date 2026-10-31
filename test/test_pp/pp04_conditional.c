// pp04: #if 系列（自我檢查：沒有任何 #error 輸出就是通過）
// 每組用 #elif 串起來，所以同一組只會報第一個失敗項
#define T_ONE 1
#define T_ZERO 0
#define EMPTY
#define T_SIX_EXPR (T_ONE + 5)
#define T_DEFD defined(T_ONE)

// ---- 算術 ----
#if 0
#elif !(1 + 2 * 3 == 7)
#error "arith: * 優先於 +"
#elif !((1 + 2) * 3 == 9)
#error "arith: 括號"
#elif !(10 - 4 - 3 == 3)
#error "arith: - 左結合"
#elif !(100 / 7 == 14)
#error "arith: /"
#elif !(100 % 7 == 2)
#error "arith: %"
#elif !(-7 / 2 == -3)
#error "arith: 負數 /"
#elif !(-7 % 3 == -1)
#error "arith: 負數 %"
#elif !(7 / -1 == -7 && 7 % -1 == 0)
#error "arith: 除以 -1"
#elif !(- - 3 == 3 && +4 == 4)
#error "arith: 一元運算"
#endif

// ---- 位元 / 位移 ----
#if 0
#elif !((0xF0 | 0x0F) == 0xFF)
#error "bit: |"
#elif !((0xFF & 0x0F) == 0x0F)
#error "bit: &"
#elif !((0xFF ^ 0x0F) == 0xF0)
#error "bit: ^"
#elif !(~0 == -1)
#error "bit: ~"
#elif !((1 << 10) == 1024)
#error "bit: <<"
#elif !((-16 >> 2) == -4)
#error "bit: 算術右移"
#elif !((1 | 2 ^ 3 & 4) == 3)
#error "bit: & > ^ > | 優先順序"
#endif

// ---- 邏輯 / 比較 ----
#if 0
#elif !((1 && 0) == 0)
#error "logic: &&"
#elif !((0 || 2) == 1)
#error "logic: || 結果要正規化成 1"
#elif !(!0 == 1 && !5 == 0)
#error "logic: !"
#elif !(1 < 2 && 2 <= 2 && 3 > 2 && 2 >= 2 && 1 != 2 && 2 == 2)
#error "compare"
#elif !(1 < 2 == 1)
#error "compare: 左結合"
#endif

// ---- unsigned 規則 ----
#if 0
#elif !(-1 > 0u)
#error "unsigned: -1 > 0u 應為真"
#elif -1 < 0u
#error "unsigned: -1 < 0u 應為假"
#elif !((0u - 1) > 0)
#error "unsigned: 0u - 1"
#elif !(0xFFFFFFFFFFFFFFFF == -1)
#error "unsigned: 大的十六進位常數是 unsigned"
#elif !((1 ? -1 : 0u) > 0)
#error "unsigned: ?: 的型別提升"
#elif !(-1 < 0)
#error "signed: -1 < 0"
#endif

// ---- 字面值 ----
#if 0
#elif !('a' == 97)
#error "lit: 'a'"
#elif !('\n' == 10 && '\0' == 0 && '\\' == 92 && '\'' == 39)
#error "lit: 簡單跳脫"
#elif !('\x41' == 'A' && '\101' == 65)
#error "lit: 十六/八進位跳脫"
#elif !(0x10 == 16 && 010 == 8 && 0b101 == 5 && 0X1f == 31)
#error "lit: 進位制"
#elif !(10L == 10 && 10UL == 10 && 10LLU == 10 && 10lu == 10 && 10u == 10)
#error "lit: 後綴"
#endif

// ---- ?: 與短路 ----
#if 0
#elif !((1 ? 2 : 3) == 2 && (0 ? 2 : 3) == 3)
#error "ternary"
#elif !((0 ? 1 : 0 ? 2 : 3) == 3 && (1 ? 2 : 3 ? 4 : 5) == 2)
#error "ternary: 右結合"
#endif
#if 0 && (1 / 0)
#error "&& 不該計算右邊"
#endif
#if !(1 || (1 / 0))
#error "|| 不該計算右邊"
#endif
#if (0 ? 1 / 0 : 5) != 5
#error "?: 未選中的分支不該報除以零"
#endif
#if (1 ? 5 : 1 % 0) != 5
#error "?: 未選中的分支不該報模零"
#endif

// ---- defined / 識別字 / 巨集 ----
#if 0
#elif !(defined(T_ONE) && defined T_ONE)
#error "defined 兩種寫法"
#elif !(!defined(T_NOT_DEFINED) && !defined T_NOT_DEFINED)
#error "defined 未定義"
#elif !(defined ( EMPTY ))
#error "defined 空巨集也算有定義"
#elif !(T_NOT_DEFINED == 0 && !T_NOT_DEFINED)
#error "未定義識別字應為 0"
#elif !(T_SIX_EXPR == 6)
#error "巨集展開含括號"
#elif !(T_ONE + T_ZERO == 1)
#error "巨集相加"
#elif !(EMPTY 1 == 1)
#error "空巨集在運算式前面"
#elif !(T_DEFD)
#error "巨集展開出 defined(...)"
#elif __LINE__ < 1
#error "__LINE__ in #if"
#endif

// ---- 不啟用的區塊：裡面的垃圾都不能報錯 ----
#if 0
#foo bar
#include "does_not_exist.h"
#error should not fire
#define BAD(
#if garbage garbage (
#elif also (garbage
#else
#endif
don't let this unterminated char literal matter
"neither this one
#endif

// ---- 已經選中後的 #elif 不求值 ----
#if 1
int elif_not_evaluated_ok;     // => int elif_not_evaluated_ok ;
#elif this is ( not valid
#error "elif after taken"
#else
#error "else after taken"
#endif

// ---- 巢狀 ----
#if 0
#  if 1
#    error "inner if in inactive outer"
#  else
#    error "inner else in inactive outer"
#  endif
#else
int nested_ok_1;               // => int nested_ok_1 ;
#  if 0
#    error "if 0 taken"
#  elif 1
int nested_ok_2;               // => int nested_ok_2 ;
#  elif 1
#    error "elif after taken"
#  else
#    error "else after taken"
#  endif
#endif

// ---- ifdef / ifndef / undef（放最後，因為會 undef T_ONE）----
#ifdef T_ONE
int ifdef_ok;                  // => int ifdef_ok ;
#endif
#ifndef T_ONE
#error "ifndef on defined macro"
#endif
#undef T_ONE
#ifdef T_ONE
#error "undef failed"
#else
int undef_ok;                  // => int undef_ok ;
#endif
#ifndef T_NOT_DEFINED
int ifndef_ok;                 // => int ifndef_ok ;
#endif
