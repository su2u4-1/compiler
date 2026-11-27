#ifndef TARGET_VALUE_H
#define TARGET_VALUE_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    TV_OK,
    TV_OVERFLOW,            // signed integer overflow / value does not fit
    TV_DIV_BY_ZERO,         // x / 0, x % 0
    TV_SHIFT_NEGATIVE,      // x << -1
    TV_SHIFT_TOO_LARGE,     // shift count >= count_of_bits
    TV_FLOAT_OUT_OF_RANGE,  // float -> integer out of range, or literal overflows to inf
    TV_FLOAT_UNDERFLOW,     // nonzero literal rounds to zero
} TVStatus;

typedef enum {
    TV_LESS,
    TV_EQUAL,
    TV_GREATER,
    TV_UNORDERED,  // NaN used
} TVCompare;

typedef struct TargetValue {
#ifdef __SIZEOF_INT128__
    __extension__ unsigned __int128 value;
#else
    uintmax_t value_h;
    uintmax_t value_l;
#endif
    unsigned int count_of_bits;  // integer: 1..128, float: 32 / 64 / 80
    bool is_float;
    bool is_unsigned;  // integer only
} TV;

// uintmax_t -> TV[integer]
TV tv_integer_from_uintmax(uintmax_t v, unsigned int count_of_bits, bool is_unsigned, TVStatus* status);
// intmax_t -> TV[integer]
TV tv_integer_from_intmax(intmax_t v, unsigned int count_of_bits, bool is_unsigned, TVStatus* status);
// TV[integer] -> uintmax_t
uintmax_t tv_integer_to_uintmax(TV v, TVStatus* status);
// TV[integer] -> intmax_t
intmax_t tv_integer_to_intmax(TV v, TVStatus* status);
// "literal" -> TV[integer]
TV tv_integer_parse(const char* s, TVStatus* status);
// "literal" -> TV[float]
TV tv_float_parse(const char* s, unsigned int count_of_bits, TVStatus* status);
// TV[integer|float] -> bytes (target endianness)
void tv_to_bytes(TV v, unsigned char* out, uintmax_t size);

TV tv_integer_add(TV a, TV b, TVStatus* status);
TV tv_integer_sub(TV a, TV b, TVStatus* status);
TV tv_integer_mul(TV a, TV b, TVStatus* status);
TV tv_integer_div(TV a, TV b, TVStatus* status);
TV tv_integer_mod(TV a, TV b, TVStatus* status);
TV tv_integer_neg(TV a, TVStatus* status);
TV tv_integer_and(TV a, TV b);
TV tv_integer_or(TV a, TV b);
TV tv_integer_xor(TV a, TV b);
TV tv_integer_not(TV a);
TV tv_integer_shl(TV a, TV b, TVStatus* status);
TV tv_integer_shr(TV a, TV b, TVStatus* status);

TVCompare tv_integer_cmp(TV a, TV b);
bool tv_integer_is_zero(TV a);
// TV[integer] -> TV[integer]
TV tv_integer_cast(TV a, unsigned int count_of_bits, bool is_unsigned);

TV tv_float_add(TV a, TV b);
TV tv_float_sub(TV a, TV b);
TV tv_float_mul(TV a, TV b);
TV tv_float_div(TV a, TV b);
TV tv_float_neg(TV a);

TVCompare tv_float_cmp(TV a, TV b);
bool tv_float_is_zero(TV a);

// TV[float] -> TV[float]
TV tv_float_cast(TV a, unsigned int count_of_bits);
// TV[integer] -> TV[float]
TV tv_float_from_integer(TV a, unsigned int count_of_bits);
// TV[float] -> TV[integer]
TV tv_float_to_integer(TV a, unsigned int count_of_bits, bool is_unsigned, TVStatus* status);

#endif  // TARGET_VALUE_H
