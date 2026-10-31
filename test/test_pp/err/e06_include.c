#include "nonexistent.h"             // E: Cannot find header file: nonexistent.h
#include <config.h>                  // E: Cannot find header file（main 沒呼叫 add_include_dir，<> 永遠找不到）
#include                             // E: Expected header name in #include
#include 123                         // E: Invalid token in #include header name
#include "inc/ok.h" extra            // E: Unexpected token after #include header name
#include "unterminated               // E: Invalid token in #include header name
#include <unterminated               // E: Invalid token in #include header name
#include ""                          // E: Empty header name in #include
#include "inc/bad_header.h"          // E: 錯誤訊息的檔名應是 inc/bad_header.h（含 #else without #if 與 Unterminated conditional）
#include "inc/ok.h"                  // OK => ok_h
