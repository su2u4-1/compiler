int main(void) {
    int x = 42;
    float f = 3.14f;
    double d = .5;
    long l = 0x1FULL;
    unsigned u = 0b1010u;
    int oct = 0755;
    char c = '\n';
    char h = '\x41';
    char u4 = '\u00E9';
    string s = "\"hello\tworld\"";
    x++;
    --x;
    x += 2;
    x <<= 1;
    if (x > 0 && x != 1) return 0;
    else return 1;
    // line comment
    /* block
       comment */
    for (;;) break;
}
