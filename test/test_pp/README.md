# preprocessor 測試集

- 跑法: `cd test_pp; .\compare.ps1`（參數見 compare.ps1 開頭）
- 第一次: 先 `.\compare.ps1 -Update`，再人工檢查 `expected\` 裡的快照（尤其 err 的 .err 與 pp06/pp07 的 .out）
- 正向測試: gcc 比對 + 快照；err/: 快照（訊息、檔名、行列號、數量都被固定）
- 檔案說明見各檔開頭註解；`// E:` `// W:` 是給人看的預期說明，由快照負責實際斷言
