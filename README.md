# simple c compiler
一個簡單的c compiler，寫著玩的，別太認真

- c standard: c17
- compiler: gcc 13.2.0
- 平台: windows 11
    - linux 是否支援還沒測試，但我覺得沒問題

> 下文所有`"目前"`都帶入這個時間: 2026/10/30 23:00

- 編譯腳本在`./build.bat`，直接執行後應該會建立一個`./build`資料夾，裡面有個`./build/program.exe`
- 執行的話跑`./run.bat <other args>`，會自動把參數傳進去執行
- 目前的執行參數是`<executable> <source file> [<output file>]`
    - 如果沒填output file的話會怎樣我忘了
    - 目前不支援多檔案編譯與其他的任何編譯參數
- 目前寫完 preprocessor，但還沒測試，現在`./test`內的是舊的測試，之後會換掉
- 目前不支援`#line`和`#pragma`、`_Pragma(...)`、`\uxxx`，其他不支援的我也忘了，應該還有一些
