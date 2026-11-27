#ifndef TARGET_H
#define TARGET_H

#include <float.h>
#include <limits.h>
#include <stdint.h>

// TODO: this is a placeholder for target-specific definitions. In a real implementation, these would be determined based on the target architecture and platform.

#define CHAR_IS_SIGNED ((char)-1 < 0)
#define normalize_char(c, count) ((count) == 1 ? (CHAR_IS_SIGNED ? (int)(signed char)(c) : (int)(unsigned char)(c)) : (int)(c))

#define DEFAULT_INCLUDE_PATHS {"TODO"}
#define COUNT_OF_DEFAULT_INCLUDE_PATHS 1
#define DEFAULT_DEFINES {"TODO"}
#define COUNT_OF_DEFAULT_DEFINES 1

#define VOID_SIZE 0
#define CHAR_SIZE sizeof(char)
#define SIGNED_CHAR_SIZE sizeof(signed char)
#define UNSIGNED_CHAR_SIZE sizeof(unsigned char)
#define SHORT_SIZE sizeof(short)
#define UNSIGNED_SHORT_SIZE sizeof(unsigned short)
#define INT_SIZE sizeof(int)
#define UNSIGNED_INT_SIZE sizeof(unsigned int)
#define LONG_SIZE sizeof(long)
#define UNSIGNED_LONG_SIZE sizeof(unsigned long)
#define LONG_LONG_SIZE sizeof(long long)
#define UNSIGNED_LONG_LONG_SIZE sizeof(unsigned long long)
#define FLOAT_SIZE sizeof(float)
#define DOUBLE_SIZE sizeof(double)
#define LONG_DOUBLE_SIZE sizeof(long double)
#define BOOL_SIZE sizeof(_Bool)
#define POINTER_SIZE sizeof(void*)
#define ENUM_SIZE sizeof(int)

#define VOID_ALIGN 0
#define CHAR_ALIGN _Alignof(char)
#define SIGNED_CHAR_ALIGN _Alignof(signed char)
#define UNSIGNED_CHAR_ALIGN _Alignof(unsigned char)
#define SHORT_ALIGN _Alignof(short)
#define UNSIGNED_SHORT_ALIGN _Alignof(unsigned short)
#define INT_ALIGN _Alignof(int)
#define UNSIGNED_INT_ALIGN _Alignof(unsigned int)
#define LONG_ALIGN _Alignof(long)
#define UNSIGNED_LONG_ALIGN _Alignof(unsigned long)
#define LONG_LONG_ALIGN _Alignof(long long)
#define UNSIGNED_LONG_LONG_ALIGN _Alignof(unsigned long long)
#define FLOAT_ALIGN _Alignof(float)
#define DOUBLE_ALIGN _Alignof(double)
#define LONG_DOUBLE_ALIGN _Alignof(long double)
#define BOOL_ALIGN _Alignof(_Bool)
#define POINTER_ALIGN _Alignof(void*)
#define ENUM_ALIGN _Alignof(int)

// unsigned max of an N-byte type
#define TARGET_UMAX_OF_SIZE(size) (~0ULL >> (sizeof(unsigned long long) * 8 - (size) * 8))

#define TARGET_UNSIGNED_CHAR_MAX TARGET_UMAX_OF_SIZE(UNSIGNED_CHAR_SIZE)
#define TARGET_UNSIGNED_SHORT_MAX TARGET_UMAX_OF_SIZE(UNSIGNED_SHORT_SIZE)
#define TARGET_UNSIGNED_INT_MAX TARGET_UMAX_OF_SIZE(UNSIGNED_INT_SIZE)
#define TARGET_UNSIGNED_LONG_MAX TARGET_UMAX_OF_SIZE(UNSIGNED_LONG_SIZE)
#define TARGET_UNSIGNED_LONG_LONG_MAX TARGET_UMAX_OF_SIZE(UNSIGNED_LONG_LONG_SIZE)

#define TARGET_SIGNED_CHAR_MAX (TARGET_UMAX_OF_SIZE(SIGNED_CHAR_SIZE) >> 1)
#define TARGET_SHORT_MAX (TARGET_UMAX_OF_SIZE(SHORT_SIZE) >> 1)
#define TARGET_INT_MAX (TARGET_UMAX_OF_SIZE(INT_SIZE) >> 1)
#define TARGET_LONG_MAX (TARGET_UMAX_OF_SIZE(LONG_SIZE) >> 1)
#define TARGET_LONG_LONG_MAX (TARGET_UMAX_OF_SIZE(LONG_LONG_SIZE) >> 1)
#define TARGET_CHAR_MAX (CHAR_IS_SIGNED ? TARGET_UMAX_OF_SIZE(CHAR_SIZE) >> 1 : TARGET_UMAX_OF_SIZE(CHAR_SIZE))

#define TARGET_UNSIGNED_CHAR_MIN 0
#define TARGET_UNSIGNED_SHORT_MIN 0
#define TARGET_UNSIGNED_INT_MIN 0
#define TARGET_UNSIGNED_LONG_MIN 0
#define TARGET_UNSIGNED_LONG_LONG_MIN 0

#define TARGET_SIGNED_CHAR_MIN (-(long long)(TARGET_UMAX_OF_SIZE(SIGNED_CHAR_SIZE) >> 1) - 1)
#define TARGET_SHORT_MIN (-(long long)(TARGET_UMAX_OF_SIZE(SHORT_SIZE) >> 1) - 1)
#define TARGET_INT_MIN (-(long long)(TARGET_UMAX_OF_SIZE(INT_SIZE) >> 1) - 1)
#define TARGET_LONG_MIN (-(long long)(TARGET_UMAX_OF_SIZE(LONG_SIZE) >> 1) - 1)
#define TARGET_LONG_LONG_MIN (-(long long)(TARGET_UMAX_OF_SIZE(LONG_LONG_SIZE) >> 1) - 1)
#define TARGET_CHAR_MIN (CHAR_IS_SIGNED ? -(long long)(TARGET_UMAX_OF_SIZE(CHAR_SIZE) >> 1) - 1 : 0)

#define TARGET_MAXINT_BITS (LONG_LONG_SIZE * 8)
#define TARGET_MAXINT_MAX TARGET_LONG_LONG_MAX
#define TARGET_MAXINT_MIN TARGET_LONG_LONG_MIN
#define TARGET_MAXUINT_MAX TARGET_UNSIGNED_LONG_LONG_MAX
#define TARGET_MAXUINT_MIN TARGET_UNSIGNED_LONG_LONG_MIN
_Static_assert(sizeof(uintmax_t) * CHAR_BIT >= TARGET_MAXINT_BITS, "host uintmax_t is narrower than target intmax_t");

#define TARGET_PTRDIFF_MAX (TARGET_UMAX_OF_SIZE(POINTER_SIZE) >> 1)

#define TARGET_FLT_MANT_DIG 24
#define TARGET_FLT_MAX_EXP 128
#define TARGET_DBL_MANT_DIG 53
#define TARGET_DBL_MAX_EXP 1024
#define TARGET_LDBL_MANT_DIG 64
#define TARGET_LDBL_MAX_EXP 16384
_Static_assert(FLT_MANT_DIG == TARGET_FLT_MANT_DIG && FLT_MAX_EXP == TARGET_FLT_MAX_EXP, "host float format differs from target");
_Static_assert(DBL_MANT_DIG == TARGET_DBL_MANT_DIG && DBL_MAX_EXP == TARGET_DBL_MAX_EXP, "host double format differs from target");
_Static_assert(LDBL_MANT_DIG == TARGET_LDBL_MANT_DIG && LDBL_MAX_EXP == TARGET_LDBL_MAX_EXP, "host long double format differs from target");

#include <complex.h>
#ifdef __STDC_NO_COMPLEX__
#define FLOAT_COMPLEX_SIZE (2 * sizeof(float))
#define DOUBLE_COMPLEX_SIZE (2 * sizeof(double))
#define LONG_DOUBLE_COMPLEX_SIZE (2 * sizeof(long double))
#define FLOAT_COMPLEX_ALIGN _Alignof(float)
#define DOUBLE_COMPLEX_ALIGN _Alignof(double)
#define LONG_DOUBLE_COMPLEX_ALIGN _Alignof(long double)
#else
#define FLOAT_COMPLEX_SIZE sizeof(float _Complex)
#define DOUBLE_COMPLEX_SIZE sizeof(double _Complex)
#define LONG_DOUBLE_COMPLEX_SIZE sizeof(long double _Complex)
#define FLOAT_COMPLEX_ALIGN _Alignof(float _Complex)
#define DOUBLE_COMPLEX_ALIGN _Alignof(double _Complex)
#define LONG_DOUBLE_COMPLEX_ALIGN _Alignof(long double _Complex)
#endif

#ifdef _Imaginary_I
#define FLOAT_IMAGINARY_SIZE sizeof(float _Imaginary)
#define DOUBLE_IMAGINARY_SIZE sizeof(double _Imaginary)
#define LONG_DOUBLE_IMAGINARY_SIZE sizeof(long double _Imaginary)
#define FLOAT_IMAGINARY_ALIGN _Alignof(float _Imaginary)
#define DOUBLE_IMAGINARY_ALIGN _Alignof(double _Imaginary)
#define LONG_DOUBLE_IMAGINARY_ALIGN _Alignof(long double _Imaginary)
#else
#define FLOAT_IMAGINARY_SIZE sizeof(float)
#define DOUBLE_IMAGINARY_SIZE sizeof(double)
#define LONG_DOUBLE_IMAGINARY_SIZE sizeof(long double)
#define FLOAT_IMAGINARY_ALIGN _Alignof(float)
#define DOUBLE_IMAGINARY_ALIGN _Alignof(double)
#define LONG_DOUBLE_IMAGINARY_ALIGN _Alignof(long double)
#endif

#endif  // TARGET_H
