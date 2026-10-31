// pp06: 詞法層級。除了文字，也請用 print_pp_token 看 token 切分（"=>" 後是預期切法）

// ---- 行拼接 ----
#define LONG_MACRO(a, b) \
    ((a) +   \
     (b))
int lm = LONG_MACRO(1,
                    2);               // => int lm = ( ( 1 ) + ( 2 ) ) ;
in\
t splice_kw;                          // => int splice_kw ;   拼接後是同一個識別字 int
char *spliced = "str\
ing";                                 // => char * spliced = "string" ;
// 註解結尾的反斜線會讓註解延續到下一行 \
這一行仍然是註解
int after_line_comment;               // => int after_line_comment ;

// ---- 註解 ----
int a/* c */b;                        // => int a b ;   註解變一個空白，是兩個 token
int c = 1 /* multi
line */ + 2;                          // => int c = 1 + 2 ;
char *s1 = "/* not comment */ // not comment";   // => 字串內容原封不動
char s2 = '/';                        // => '/' 是一個 PP_CHAR
int d // trailing
    = 1;                              // => int d = 1 ;
/* /* 區塊註解不會巢狀 */ int after_block;   // => int after_block ;

// ---- pp-number：每個都是「一個」token ----
int n[] = { 1.5e+10, 0x1p-3, .5, 5., 1e5, 0b101 };

// ---- 符號的最長匹配 ----
int s = a+++++b;                      // => a ++ ++ + b
x <<= 1; x >>= 2; p->q;               // => x <<= 1 ; x >>= 2 ; p -> q ;
a && b || c; a ? b : c;               // => && || ? :
a <= b >= c; a == b != c;             // => <= >= == !=
a .. b; f(...);                       // => '.' '.' 兩個 token ; '...' 一個 token
a ## b # c;                           // 一般文字中的 # ## 只是 symbol
a -= 1; a *= 2; a /= 3; a %= 4; a &= 5; a ^= 6; a |= 7;

// ---- 字串 / 字元 ----
char *e1 = "esc \" quote \\ backslash";   // => 一個 PP_STRING
char e2 = '\'';                           // => 一個 PP_CHAR
char e3 = '"';                            // => '"' 一個 PP_CHAR，不會開始字串
char *e4 = "'";                           // => "'" 一個 PP_STRING
char e5 = '\\';
