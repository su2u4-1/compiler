#define CAT(a, b) a ## b
CAT(+, -)                    // E: Pasting "+" and "-" does not give a valid preprocessing token
CAT(1, +)                    // E: 同上
CAT(., .)                    // E: 同上
CAT(/, /)                    // E: 同上（變成註解）
CAT("a", "b")                // E: 同上
CAT(a, "b")                  // E: 同上
CAT(ok, 1)                   // => ok1（沒有錯誤）
