#include "target_value.h"

#include <assert.h>
#include <string.h>

#define is_int_bits(n) (0 < (n) && (n) <= 128)
#define is_float_bits(n) ((n) == 32 || (n) == 64 || (n) == 80)
#define check_int(x) assert(!(x).is_float && is_int_bits((x).count_of_bits))
#define check_float(x) assert((x).is_float && !(x).is_unsigned && is_float_bits((x).count_of_bits))
#define check_same(a, b) assert((a).is_float == (b).is_float && (a).count_of_bits == (b).count_of_bits && (a).is_unsigned == (b).is_unsigned)

TV tv_integer_from_uintmax(uintmax_t v, unsigned int count_of_bits, bool is_unsigned, TVStatus* status) {
    assert(is_int_bits(count_of_bits));
    return (TV){0};  // placeholder
}

TV tv_integer_from_intmax(intmax_t v, unsigned int count_of_bits, bool is_unsigned, TVStatus* status) {
    assert(is_int_bits(count_of_bits));
    return (TV){0};  // placeholder
}

uintmax_t tv_integer_to_uintmax(TV v, TVStatus* status) {
    check_int(v);
    return 0;  // placeholder
}

intmax_t tv_integer_to_intmax(TV v, TVStatus* status) {
    check_int(v);
    return 0;  // placeholder
}

TV tv_integer_parse(const char* s, TVStatus* status) {
    assert(s != NULL);
    return (TV){0};  // placeholder
}

TV tv_float_parse(const char* s, unsigned int count_of_bits, TVStatus* status) {
    assert(s != NULL && is_float_bits(count_of_bits));
    return (TV){0};  // placeholder
}

void tv_to_bytes(TV v, unsigned char* out, uintmax_t size) {
    assert(v.is_float ? is_float_bits(v.count_of_bits) : is_int_bits(v.count_of_bits));
    return;  // placeholder
}

TV tv_integer_add(TV a, TV b, TVStatus* status) {
    check_int(a);
    check_same(a, b);
    return (TV){0};  // placeholder
}

TV tv_integer_sub(TV a, TV b, TVStatus* status) {
    check_int(a);
    check_same(a, b);
    return (TV){0};  // placeholder
}

TV tv_integer_mul(TV a, TV b, TVStatus* status) {
    check_int(a);
    check_same(a, b);
    return (TV){0};  // placeholder
}

TV tv_integer_div(TV a, TV b, TVStatus* status) {
    check_int(a);
    check_same(a, b);
    return (TV){0};  // placeholder
}

TV tv_integer_mod(TV a, TV b, TVStatus* status) {
    check_int(a);
    check_same(a, b);
    return (TV){0};  // placeholder
}

TV tv_integer_neg(TV a, TVStatus* status) {
    check_int(a);
    return (TV){0};  // placeholder
}

TV tv_integer_and(TV a, TV b) {
    check_int(a);
    check_same(a, b);
    return (TV){0};  // placeholder
}

TV tv_integer_or(TV a, TV b) {
    check_int(a);
    check_same(a, b);
    return (TV){0};  // placeholder
}

TV tv_integer_xor(TV a, TV b) {
    check_int(a);
    check_same(a, b);
    return (TV){0};  // placeholder
}

TV tv_integer_not(TV a) {
    check_int(a);
    return (TV){0};  // placeholder
}

TV tv_integer_shl(TV a, TV b, TVStatus* status) {
    check_int(a);
    check_int(b);
    return (TV){0};  // placeholder
}

TV tv_integer_shr(TV a, TV b, TVStatus* status) {
    check_int(a);
    check_int(b);
    return (TV){0};  // placeholder
}

TVCompare tv_integer_cmp(TV a, TV b) {
    check_int(a);
    check_same(a, b);
    return (TVCompare){0};  // placeholder
}

bool tv_integer_is_zero(TV a) {
    check_int(a);
    return false;  // placeholder
}

TV tv_integer_cast(TV a, unsigned int count_of_bits, bool is_unsigned) {
    check_int(a);
    assert(is_int_bits(count_of_bits));
    return (TV){0};  // placeholder
}

TV tv_float_add(TV a, TV b) {
    check_float(a);
    check_same(a, b);
    return (TV){0};  // placeholder
}

TV tv_float_sub(TV a, TV b) {
    check_float(a);
    check_same(a, b);
    return (TV){0};  // placeholder
}

TV tv_float_mul(TV a, TV b) {
    check_float(a);
    check_same(a, b);
    return (TV){0};  // placeholder
}

TV tv_float_div(TV a, TV b) {
    check_float(a);
    check_same(a, b);
    return (TV){0};  // placeholder
}

TV tv_float_neg(TV a) {
    check_float(a);
    return (TV){0};  // placeholder
}

TVCompare tv_float_cmp(TV a, TV b) {
    check_float(a);
    check_same(a, b);
    return (TVCompare){0};  // placeholder
}

bool tv_float_is_zero(TV a) {
    check_float(a);
    return false;  // placeholder
}

TV tv_float_cast(TV a, unsigned int count_of_bits) {
    check_float(a);
    assert(is_float_bits(count_of_bits));
    return (TV){0};  // placeholder
}

TV tv_float_from_integer(TV a, unsigned int count_of_bits) {
    check_int(a);
    assert(is_float_bits(count_of_bits));
    return (TV){0};  // placeholder
}

TV tv_float_to_integer(TV a, unsigned int count_of_bits, bool is_unsigned, TVStatus* status) {
    check_float(a);
    assert(is_int_bits(count_of_bits));
    return (TV){0};  // placeholder
}
