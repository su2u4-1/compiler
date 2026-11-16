# simple c compiler
一個簡單的c compiler，寫著玩的，別太認真

- c standard: c17
- compiler: gcc 13.2.0
- 平台: windows 11
    - linux 目前有稍微測試過了，應該是沒問題

> 下文所有`"目前"`都帶入這個時間: 2026/11/16 10:12

- 編譯腳本在`./build.bat`，直接執行後應該會建立一個`./build`資料夾，裡面有個`./build/program.exe`
- 執行的話跑`./run.bat <other args>`，會自動把參數傳進去執行
- ~~目前的執行參數是`<executable> <source file> [<output file>]`~~
    - ~~如果沒填output file的話會怎樣我忘了~~
    - ~~目前不支援多檔案編譯與其他的任何編譯參數~~
- 目前的執行參數是`<executable> <source files> [-o <output file>] [output option...]`
    - 可以給多個 source file，每個都會各自跑完 preprocess → tokenize → parse，其中一個失敗也會繼續跑其他的，最後回傳 1
    - `-o` 指定最終輸出，沒填就是`a.out`(codegen 還沒寫，所以目前不會真的產生)
    - output option 可以混著用，會把中間結果輸出成`<output file>`換副檔名:
        - `-p` : 輸出 pp-tokens -> `.pp`
        - `-pc`: 把 pp-tokens 還原成 code -> `.pp.c`
        - `-t` : 輸出 tokens -> `.tok`
        - `-tc`: 把 tokens 還原成 code -> `.tok.c`
        - `-a` : 輸出 AST -> `.ast`
        - `-ac`: 把 AST 還原成 code -> `.ast.c`
    - 有多個 source file 時，中間結果的檔名會換成 source file 的檔名，避免互相覆蓋(例: `-o build/a.out x.c y.c -a` -> `build/x.ast`, `build/y.ast`)
    - 不管有沒有給 output option 都會編譯到底；preprocess 或 parse 有錯就停在該檔案

- ~~目前寫完 preprocessor，通過了claude寫的測試(`./test/test_pp/*`, in test_pp run: `./compare.ps1`)~~
- ~~完善了一遍 test_pp 的測試，並且在 windows 與 linux 上都通過了(linux 上的測試是 claude 跑的，因為我懶得開 wsl)~~
- ~~現在`./test`內的t1, t2, t3是舊的測試，沒用了，先留著~~
- 我把測試刪了，之後有要測再重寫一個

- 目前不支援`#line`和`#pragma`、`_Pragma(...)`、`\uxxx`，其他不支援的我也忘了，應該還有一些
- `__STDC__`、`__STDC_VERSION__`、`__STDC_HOSTED__`暫不支援，因為並沒有完整實作
- Trigraph 和 Digraph 都不支援

- parser 應該是寫完了，但還沒 review 也還沒測試，先 push 上來，等 claude 重置後叫他 review
