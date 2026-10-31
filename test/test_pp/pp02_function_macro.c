// pp02: 函式式巨集
#define ADD(a, b) ((a) + (b))
#define ZERO() 0
#define FIRST(a, b) a
#define SECOND(a, b) b
#define APPLY(f, x) f(x)
#define NEST(x) ADD(x, ADD(x, x))
#define IDENT(x) x
#define fn(x) (x + 1)
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int a = ADD(1, 2);               // => ( ( 1 ) + ( 2 ) )
int b = ZERO();                  // => 0
int c = ADD(ADD(1, 2), 3);       // => ( ( ( ( 1 ) + ( 2 ) ) ) + ( 3 ) )
int d = ADD((1, 2), 3);          // => ( ( ( 1 , 2 ) ) + ( 3 ) )   括號內逗號不分參數
int e = FIRST(, 5);              // => int e = ;   空參數
int f = SECOND(, 5);             // => int f = 5 ;
int g = APPLY(IDENT, 3);         // => int g = 3 ;
int h = NEST(2);                 // => ( ( 2 ) + ( ( ( 2 ) + ( 2 ) ) ) )
int i = fn;                      // => int i = fn ;   沒有 '(' 不展開
int j = fn   (4);                // => int j = ( 4 + 1 ) ;
int k = fn
        (5);                     // => int k = ( 5 + 1 ) ;   名稱與 '(' 之間可換行
int l = ADD(1,
            2);                  // => ( ( 1 ) + ( 2 ) )   參數跨行
int m = IDENT(IDENT)(9);         // => int m = IDENT ( 9 ) ;   內層 IDENT 被 hideset 擋住（同 gcc）
int n = ADD(")", ',');           // => ( ( ")" ) + ( ',' ) )   字串/字元內的括號、逗號不算
int o = MAX(ZERO(), IDENT(1));   // => ( ( 0 ) > ( 1 ) ? ( 0 ) : ( 1 ) )
int p = fn
;                                // => int p = fn ;   往後看沒有 '(' 要能還原
