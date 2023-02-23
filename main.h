#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include <limits.h>

typedef struct flags_al {
    int space;  int plus;
    int neg; int zero_pad;
    int width;  int prsn;
    int star;  int hash;
} flag;

enum stage{
 FL_CHAR = -2,
 FL_SHORT = -1,
 FL_INT = 0,
 FL_LONG = 1,
 FL_LONG_LONG = 2,
 FL_REV = 3
};

typedef enum base_diff{
    decimal = 10,
    hexadecimal = 16,
    octadecimal = 8,
    binary = 2
} base_type;

typedef struct float_properties {
    int32_t exponent;
    double fraction;
    double decimal;
    double mantissa;
} float_prop;

typedef long double ldbl_t;
#define MIN_S FL_CHAR
#define MAX_S FL_LONG_LONG
#define SIZE_BIT (3 + sizeof(void *) * (CHAR_BIT) / 4)
#define reset(val) val = 0
#define isnum_min 48
#define isnum_max 57
#define UNUSED(c) (void)(c)
#define ADD_1(x) x += 1
#define SUB_1(x) x -= 1
#define  PUSH(x, buff, t)\
    (*(buff + t) = x)
#define ischar_digit(str_val)\
   (str_val >= isnum_min && str_val <= isnum_max)
#define SWITCH_OFF(val) val = 0

#define HEX_F 70
#define HEX_f 102
#define UPPER_A 65
#define UPPER_Z 90
#define LOWER_a 97
#define LOWER_z 122

/* template for array reversal */
#define REV_AR(typename, val) \
    typename *REV_AR_##val(typename *oop, int len){	\
	int haf_len = (len / 2); \
	int i = 0; \
	--len; \
	while (i != haf_len){ \
	    oop[i] ^= oop[len - i]; \
	    oop[len - i] ^= oop[i]; \
	    oop[i] ^= oop[len - i]; \
	    i++;   \
	}	    \
	return oop;  \
    }		     \

/* prototypes */
int printf(const char *str, ...);
int specifier (const char *, va_list);
intmax_t int_formt(uintmax_t, int, int, int, int, char *, flag *);
uintmax_t sigd_unsgd(int, int, va_list *);
uintmax_t str_atoi(char *);
intmax_t simple_pow(int, int);
intmax_t rev_hex(char *, int, char *, flag *);
uintmax_t revhex_ct(char *);
intmax_t bina_ry(uintmax_t, char *, int);
intmax_t octal(uintmax_t, char *, int);
int32_t hex_conv(uintmax_t, int, unsigned int, char *, int);
intmax_t rev_bin(char *, int, char *, flag *);
uintmax_t rev_bin_ct(char *);
intmax_t rev_oct(char *, int, char *, flag *);
uintmax_t rev_oct_ct(char *);
uint8_t str_len(char *);
int str_fmt(char *, char *, int, int, int, flag *);

long double flt_selec(int, int, va_list *);
void exponent(long double, long double);
void print_exponent(long double, long double, int, int);
long double round_exponent(long double, int);
void float_precision(ldbl_t, char *, int);
void long_double(long double, int);
void G_float(long double, int);
double floatmanipul(double, float_prop *);
#endif /* MAIN_H */
