// 與 gcc 不同 / 尚未支援的項目。出現 "gap_" 開頭的識別字 = 與 gcc 行為不同（不一定是 bug，看你的設計）
#ifndef __STDC__
int gap_no_stdc;                // gcc: __STDC__ 有定義，這行不會輸出
#endif
#ifndef __STDC_VERSION__
int gap_no_stdc_version;        // gcc: 有定義
#endif
#if !defined(__LINE__)
int gap_defined_line;           // gcc: defined(__LINE__) 為真（find_macro 找不到內建巨集）
#endif
#if !defined(__FILE__)
int gap_defined_file;           // 同上
#endif
_Pragma("once") int gap_pragma; // gcc: _Pragma(...) 被處理掉；這裡會原樣輸出 _Pragma ( "once" )
#line 50 "foo.c"                // 被忽略
int gap_line_ignored = __LINE__;// gcc: 50；這裡: 此行實體行號
int gap_digraph<:3:>;           // gcc: gap_digraph[3]；這裡: <: 3 :> 原樣輸出（未支援 digraph）
