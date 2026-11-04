#define CAT(a, b) a ## b
#define STR(x) #x
#define V(...) __VA_ARGS__
#define EMPTY
#define F(x) x
#define BAD 1

CAT(1, 2)
STR(  a   +  b  )
V()
V(1, 2, 3)
F
F(EMPTY)

#if 0 && (1 / 0)
bad_short_circuit
#elif 1 || (1 / 0)
good_short_circuit
#endif

#if 0
#if 1 / 0
bad_nested
#endif
#else
good_nested
#endif
