// pp08: 邊界案例（可與 gcc 比對）
// ---- 物件式 vs 函式式：只看名稱後面有沒有「空白」（註解也算空白）----
#define OBJ (x)
#define FUN(x) [x]
OBJ(1) FUN(1)                  // => ( x ) ( 1 ) [ 1 ]
#define F1/**/(x) z            // 註解 = 空白，所以是物件式，本體是 (x) z
#define F2(x) z
F1(2) F2(2)                    // => ( x ) z ( 2 ) z

// ---- ## 的結果會再被掃描 ----
#define AB 1
#define CAT(a, b) a ## b
CAT(A, B)                      // => 1
CAT(in, t) kw;                 // => int kw ;

// ---- 替換列表中的註解 ----
#define CM 1 /*c*/ + 2
int cm = CM;                   // => int cm = 1 + 2 ;

// ---- 多行 stringize ----
#define STR(x) #x
STR(a \
    b)                         // => "a b"

// ---- #if 內的行拼接 ----
#if 1 \
  + 1 == 2
int if_splice_ok;              // => int if_splice_ok ;
#else
#error "if splice"
#endif

// ---- directive 後面多餘的 token（gcc 只警告）----
#ifdef FOO extra
#endif extra
#ifndef FOO extra2
int extra_tokens_ok;           // => int extra_tokens_ok ;
#else extra3
#error "else branch"
#endif extra4

// ---- include 檔名後面有註解 ----
#include "inc/part_2.h" /* c */ // d

// ---- 標準 6.10.3 EXAMPLE 6：合法與不合法的重定義 ----
#define OBJ_LIKE (1-1)
#define OBJ_LIKE /* white space */ (1-1) /* other */
#define FUNC_LIKE(a) ( a )
#define FUNC_LIKE( a )( /* note the white space */ \
 a /* other stuff on this line
 */ )
int ex6_valid = OBJ_LIKE + FUNC_LIKE(2);   // => int ex6_valid = ( 1 - 1 ) + ( 2 ) ;   （以上不該有警告）
#define OBJ_LIKE (0)                // W: 本體不同
#define OBJ_LIKE (1 - 1)            // W: 空白不同
#define FUNC_LIKE(b) ( a )          // W: 參數名不同
#define FUNC_LIKE(b) ( b )          // W: 本體不同
int ex6_last = OBJ_LIKE + FUNC_LIKE(3);    // => int ex6_last = ( 1 - 1 ) + ( 3 ) ;
