// pp07: 內建巨集。註解中的數字是預期行號（token 所在的實體行）
// 含 __FILE__/__DATE__/__TIME__，無法直接跟 gcc 比對
#define LINE_OF __LINE__
#define FILE_OF() __FILE__
#define STR(x) #x
#define XSTR(x) STR(x)

int l1 = __LINE__;              // => 8
int l2 = LINE_OF;               // => 9
int l3 = XSTR(LINE_OF);         // => "10"
char *f1 = __FILE__;            // => 檔名字串，路徑與命令列傳入的一致
char *f2 = FILE_OF();           // => 同上
char *f3 = XSTR(__FILE__);      // => 上一行的字串再被 stringize（引號與反斜線被跳脫）
char *dt = __DATE__;            // => "Mmm dd yyyy"，日個位數補空白
char *tm = __TIME__;            // => "hh:mm:ss"
int l6 = __LINE__ \
       + __LINE__;              // => int l6 = 16 + 17 ;
#line 100
int l7 = __LINE__;              // => 19（#line 尚未支援，被忽略）
#pragma once
int after_pragma;               // => #pragma 被忽略，這行照常輸出
#define __FILE__ "fake.c"       // [Warning] Redefining predefined macro
char *f4 = __FILE__;            // => "fake.c"
