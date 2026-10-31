// 預期每行對應的錯誤；程式應回傳 1 並印出 [Preprocess Error]
#else                       // E: #else without #if
#elif 1                     // E: #elif without #if
#endif                      // E: #endif without #if
#if 1
#else
#else                       // E: #else after #else
#elif 1                     // E: #elif after #else
#endif
#ifdef                      // E: Expected identifier after #if[n]def
#endif
#ifdef 123                  // E: 同上
#endif
#ifndef
#endif
#if 1                       // E: Unterminated conditional directive（檔案結尾才報，指向此行）
