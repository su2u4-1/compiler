// pp03: # 與 ## 與 variadic
#define CAT(a, b) a ## b
#define XCAT(a, b) CAT(a, b)
#define STR(x) #x
#define XSTR(x) STR(x)
#define V(name) var_ ## name
#define OP(a) a ## =
#define LOG(fmt, ...) printf(fmt, __VA_ARGS__)
#define ALL(...) __VA_ARGS__
#define STR_ALL(...) #__VA_ARGS__

CAT(x, y)                      // => xy
CAT(1, 2)                      // => 12
CAT(<, <)                      // => <<
CAT(<<, =)                     // => <<=
CAT(-, >)                      // => ->
CAT(x, 1)                      // => x1
CAT(, y)                       // => y
CAT(x, )                       // => x
CAT(,)                         // => (什麼都沒有)
CAT(a b, c d)                  // => a bc d    只有相鄰的兩個 token 被貼上
V(foo)                         // => var_foo
OP(+)                          // => +=
OP(<<)                         // => <<=
XCAT(L, __LINE__)              // => L<此行行號>
CAT(L, __LINE__)               // => L__LINE__   ## 旁邊的參數不先展開
STR(a   +   b)                 // => "a + b"
STR(  leading and trailing  )  // => "leading and trailing"
STR("quote\n")                 // => "\"quote\\n\""
STR('\'')                      // => "'\\''"
STR()                          // => ""
STR(/* c */ x /* c */ + /* c */ y)   // => "x + y"
XSTR(CAT(a, b))                // => "ab"
STR(CAT(a, b))                 // => "CAT(a, b)"
XSTR(__LINE__)                 // => "<此行行號>"
LOG("a")                       // => printf ( "a" , )
LOG("a", 1, 2)                 // => printf ( "a" , 1 , 2 )
ALL()                          // => (什麼都沒有)
ALL(1, 2, 3)                   // => 1 , 2 , 3
STR_ALL(1,   2 , 3)            // => "1, 2 , 3"
STR_ALL()                      // => ""
