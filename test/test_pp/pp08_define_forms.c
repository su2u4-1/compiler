// pp08: 巨集定義形式與邊界（可與 gcc 比對）
#define OBJ_SP (x)
#define FUN_NOSP(x) [x]
#define OBJ_CMT/**/(x) 1
OBJ_SP(1)                 // => ( x ) ( 1 )        名稱後有空白 = 物件式
FUN_NOSP(1)               // => [ 1 ]              名稱後緊接 ( = 函式式
OBJ_CMT(1)                // => ( x ) 1 ( 1 )      註解算空白 = 物件式

#define AB 1
#define CAT(a, b) a ## b
CAT(A, B)                 // => 1                  貼完之後要再掃描
#define KW(a, b) a ## b
KW(in, t) kw_var;         // => int kw_var ;

#define BODY_CMT 1 /*c*/ + 2
BODY_CMT                  // => 1 + 2

#define STR(x) #x
#define ID(x) x
STR(a \
    b)                    // => "a b"              行拼接
STR(a
    b)                    // => "a b"              參數內換行
STR('\0') STR('\n')       // => "'\\0'" "'\\n'"
ID(#) ID(##)              // => # ##               參數中的 # ## 只是普通 token

// directive 後面多餘的 token：gcc 只警告，輸出相同
#define FOO 1
#ifdef FOO extra
int ifdef_extra;          // => int ifdef_extra ;
#else extra
#endif extra
#ifndef FOO extra
#endif
#undef FOO extra
#ifdef FOO
#error "undef with extra tokens failed"
#endif

// #if 內的行拼接
#if 1 \
  + 1 == 2
int if_splice_ok;         // => int if_splice_ok ;
#else
#error "splice in #if"
#endif
STR(a	+	b)    // => "a + b"   tab 在 stringize 中變成單一空格
