# simple c compiler
一個簡單的c compiler，寫著玩的，別太認真

- c standard: c17
- compiler: gcc 13.2.0
- 平台: windows 11
    - linux 目前有稍微測試過了，應該是沒問題

> 下文所有`"目前"`都帶入這個時間: 2026/11/04 21:25

- 編譯腳本在`./build.bat`，直接執行後應該會建立一個`./build`資料夾，裡面有個`./build/program.exe`
- 執行的話跑`./run.bat <other args>`，會自動把參數傳進去執行
- 目前的執行參數是`<executable> <source file> [<output file>]`
    - 如果沒填output file的話會怎樣我忘了
    - 目前不支援多檔案編譯與其他的任何編譯參數

- ~~目前寫完 preprocessor，通過了claude寫的測試(`./test/test_pp/*`, in test_pp run: `./compare.ps1`)~~
- ~~完善了一遍 test_pp 的測試，並且在 windows 與 linux 上都通過了(linux 上的測試是 claude 跑的，因為我懶得開 wsl)~~
- ~~現在`./test`內的t1, t2, t3是舊的測試，沒用了，先留著~~
- 我把測試刪了，之後有要測再重寫一個

- 目前不支援`#line`和`#pragma`、`_Pragma(...)`、`\uxxx`，其他不支援的我也忘了，應該還有一些
- `__STDC__`、`__STDC_VERSION__`、`__STDC_HOSTED__`暫不支援，因為並沒有完整實作
- Trigraph 和 Digraph 都不支援
