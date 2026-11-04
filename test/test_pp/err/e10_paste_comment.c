#define CAT(a, b) a ## b
CAT(/, *)                    // E: Pasting "/" and "*" 會變成註解開頭，不是合法 token
