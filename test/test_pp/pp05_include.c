// pp05: #include
// 預期輸出（依序）:
//   guarded_once outer_begin inner_begin deep_begin up_h sibling_h deep_end inner_end outer_end
//   no_newline_h rec_guarded_body shadow_root uses_shadow_begin shadow_inc
//   part_2 macro_included version_ok(=((3)*(3)))
#include "inc/config.h"
#include "inc/guarded.h"
#include "inc/guarded.h"               // 第二次被 include guard 擋掉
#include "inc/outer.h"                 // outer -> inner -> sub/deep -> ../up 與 sibling
#include "inc/no_newline.h"            // 檔案結尾沒有換行
#include "inc/recursive_guarded.h"     // 自己 include 自己，被 guard 擋掉
#include "shadow.h"                    // 與本檔同目錄的 shadow.h -> shadow_root
#include "inc/uses_shadow.h"           // 內部的 "shadow.h" 要先找自己目錄 -> inc/shadow.h -> shadow_inc
#include "inc//../inc/./guarded.h"     // 路徑正規化後同一個檔案（被 guard 擋掉，只要不報錯就好）

// 用巨集組出 include 的檔名
#define INC_STR(x) #x
#define INC_XSTR(x) INC_STR(x)
#define INC_PATH(n) INC_XSTR(inc/part_##n.h)
#include INC_PATH(2)                   // => "inc/part_2.h"
#define INC_HEADER "inc/macro_included.h"
#include INC_HEADER

#if 0
#include "this_file_does_not_exist.h"  // 在被跳過的區塊內，不應報錯
#endif

#if VERSION >= 3 && defined(FEATURE_X)
int version_ok = SQUARE(VERSION);      // => int version_ok = ( ( 3 ) * ( 3 ) ) ;
#else
#error "config.h 的巨集沒有帶進來"
#endif
