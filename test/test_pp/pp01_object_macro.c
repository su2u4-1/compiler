// pp01: 物件式巨集 / #undef / 重定義 / 遞迴保護 / 惰性展開 / 指令空白
// 註解裡的 "=>" 是預期輸出的 token 序列（忽略空白）
#define PI 3
#define TWO_PI (PI + PI)
#define EMPTY
#define ALIAS BASE_VALUE
#define BASE_VALUE 42
#define SELF SELF
#define LOOP_A LOOP_B
#define LOOP_B LOOP_A
#define OBJ_PAREN (x)

int a = PI;                  // => int a = 3 ;
int b = TWO_PI;              // => int b = ( 3 + 3 ) ;
int c = EMPTY 7 EMPTY;       // => int c = 7 ;
int d = ALIAS;               // => int d = 42 ;
int e = SELF;                // => int e = SELF ;
int f = LOOP_A + LOOP_B;     // => int f = LOOP_A + LOOP_B ;
int g = OBJ_PAREN(1);        // => int g = ( x ) ( 1 ) ;
int PIPE = 1;                // => PIPE 不是 PI，不能被展開

// 巨集本體是「使用時」才展開（惰性）
#define LAZY LAZY_VALUE
#define LAZY_VALUE 1
#undef LAZY_VALUE
#define LAZY_VALUE 2
int h = LAZY;                // => int h = 2 ;
#undef LAZY_VALUE
int i = LAZY;                // => int i = LAZY_VALUE ;

// 重定義：相同定義不該有警告，不同定義才有 [Warning] Macro redefined
#define SAME 1 + 2
#define SAME 1 + 2
#define SAME 1    +    2
#define DIFF 1
#define DIFF 2
#undef DIFF
#define DIFF 3
#undef NEVER_DEFINED
int j = SAME;                // => int j = 1 + 2 ;
int k = DIFF;                // => int k = 3 ;

// 指令前後的空白 / 註解 / 空指令
   #define SPACED 5
#   define SPACED2   6
/* comment */ # define AFTER_COMMENT 7
#
# /* null directive */
int l = SPACED + SPACED2 + AFTER_COMMENT;   // => int l = 5 + 6 + 7 ;
