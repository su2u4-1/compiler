#define ADD(a, b) ((a) + (b))
#define ZERO() 0
#define VA(a, b, ...) a
ADD(1)                       // E: Incorrect number of macro arguments
ADD(1, 2, 3)                 // E: 同上
ADD()                        // E: 同上（一個空參數）
ZERO(1)                      // E: 同上
VA(1)                        // E: 同上（variadic 至少要有具名參數）
ADD(1,                       // E: Unterminated macro arguments（必須放最後，吃到 EOF）
