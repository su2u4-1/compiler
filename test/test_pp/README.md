# preprocessor 測試集

```
pp01_object_macro.c      物件式巨集 / undef / 重定義 / 遞迴保護 / 指令空白
pp02_function_macro.c    函式式巨集 / 參數切分 / 跨行 / 回溯
pp03_paste_stringize.c   # ## variadic / placemarker
pp04_conditional.c       #if 運算式、unsigned、短路、跳過區塊、巢狀（自我檢查：有 #error 輸出就是失敗）
pp05_include.c + inc/    include guard、相對路徑、巨集組檔名、同名檔優先順序
pp06_lexical.c           行拼接、註解、pp-number、符號最長匹配、字串/字元
pp07_builtin.c           __LINE__ / __FILE__ / __DATE__ / __TIME__ / #line / #pragma
pp_all.c                 include pp01~06
pp_known_gaps.c          與 gcc 不同或尚未支援（出現 gap_ 開頭 = 不同）
std/ex3,4,5,7.c          C17 6.10.3.5 標準範例，預期輸出寫在檔尾註解
err/e01~e09.c            預期報錯；每行 "E:" 是該行預期錯誤，"W:" 是警告
warn_backslash_space.c   反斜線後有空白的警告
compare.sh               用 gcc -E -P 當標準答案比對（忽略空白）
```

執行: `program.exe pp01_object_macro.c out.txt`（錯誤檔應回傳 1）。
自動比對（Git Bash）: `./compare.sh ../build/program.exe`
