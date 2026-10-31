#define                      // E: Expected macro name after #define
#define 123                  // E: 同上
#define defined 1            // E: Invalid macro name after #define
#define __VA_ARGS__ 1        // E: Invalid macro name after #define
#define F1(a, a) a           // E: Duplicate parameter name
#define F2(a,) a             // E: Expected parameter name after ,
#define F3(a b) a            // E: Expected , or )
#define F4(a                 // E: Expected , or ) in macro definition
#define F5(__VA_ARGS__) 1    // E: Invalid parameter name __VA_ARGS__
#define F6(1) 1              // E: Expected parameter name
#define F7(x) #y             // E: Invalid parameter after #
#define F8(x) #              // E: Macro body cannot end with #
#define F9(x) # 1            // E: Expected parameter after #
#define F11(... x) 1         // E: Expected ) after ...
#define G1 ## x              // E: Macro body cannot start with ##
#define G2 x ##              // E: Macro body cannot end with ##
#define G3 __VA_ARGS__       // E: Invalid use of __VA_ARGS__ in macro body
#undef                       // E: Expected macro name after #undef
#undef defined               // E: Invalid macro name after #undef
// ---- 以下只有警告 ----
#define W1+1                 // W: Missing space between macro name and replacement list
#define __LINE__ 5           // W: Redefining predefined macro
