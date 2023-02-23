#include <stdint.h>
#include <stdio.h>
double pow_r(int32_t base, int32_t powr);
#define SET 0XFFFFFFFFFFFFFFFF
typedef struct float_properties {
    int32_t exponent;
    double fraction;
    double decimal;
    double mantissa;
} float_prop;
double floatmanipul(double, float_prop *);

double pow_r(int32_t base, int32_t powr){
    if (!base)
	return 0;
    if (base == 1)
	return 1;
    if (!powr)
	return 1;
    if (powr == 1)
	return base;
    return base * pow_r(base, powr - 1);
}
double floatmanipul(double flt_val, float_prop *properties){
    union {
	double x;
	uint64_t gg;
    } op;
    double resetdbl_k;
    double fracdec;
    int32_t i, count;
    uint64_t bits, revBit;
    uint64_t frop;
    int64_t expon;
    int32_t sign;
    double mantissa;

    op.x = flt_val;

    fracdec = count = 0;
    sign = (int64_t)op.gg >> 63;
    !(sign) ? sign = 1 : 0;
    op.gg <<= 1;

    /* extract exponent */
    expon = (op.gg >> 53) - 0X3FF;  /*  bias */
    properties->exponent = expon;
    op.gg <<= 11;
    bits = op.gg; /* save bit state for mantissa */

    /** if possibility of fraction :- 0 < @expon < 64
     * @fracdec: decimal part, @frop: decimal fraction */
    if (expon < 64){
	/* exponential */
	frop = op.gg;
	frop = expon > 0 ? frop << expon : frop; /* shift out decimal part */
	if (expon < 0)
	    frop = (frop >> 1) | (1LL << 63);

	/* extract only fractional. expel backward zeros */
	while (frop && !(frop & 1)){
	    count++;
	    frop >>= 1;
	}
	/** @expon < 0: remove sign @count: denomalizing power to base 2 */
	count -= expon < 0 ? (-expon - 1) : 0;

	/* divide by number of bits to power of radix(2) */
	fracdec = (frop / (pow_r(2, 64 - count))) * sign;

	properties->fraction = (double)fracdec;

        /* Extract decimal */
	op.gg = ((op.gg >> 1) | (1LL << 63))>>(64 - (expon + 1));
	properties->decimal = (double)op.gg * sign;
    }
    /* else reset bits to double representation */
    else if (expon > 63){
	expon += 1023;
	op.gg = (op.gg >> 12) | (expon << 52); /* add exp */
	resetdbl_k = *(volatile double *)&op.gg; /* copy bits */
	properties->decimal = (double)resetdbl_k * sign;
    }
    /* To conclude extract mantissa */
    revBit = count = i = 0;
    count |= 64;
    /* reverse bits */
    while (i < count){
	revBit |= bits & (1LL << i) ? 1LL << ((count - 1) - i) : 0;
	i++;
    }
    /* convert bits in base 2 to floating point */
    mantissa = i = 0;
    while (revBit){
	mantissa += (revBit % 2) * (1/(double)(2LL << i++));
	revBit >>= 1; /* revBit/2 */
    }
    mantissa += 1;
    properties->mantissa = mantissa * sign;
    /* return fractional */
    return fracdec;
}
#include <float.h>
int main(){
    double val;
    char s[1023];
    float_prop prop;

    val = DBL_MIN;
    floatmanipul(val, &prop);

    uintmax_t dec = (int)prop.mantissa;
    val = prop.mantissa - dec;

    uintmax_t dectr = val * pow_r(10, 17);
    int ct = 0;
    uintmax_t rev = 0;
    printf("%Ld\n", dectr);
    while (dectr){
	rev = (rev * 10) + (dectr % 10);
	dectr /= 10;
    }
    int tmp = dec;
    while(dec){
	s[ct++] = (dec % 10) + 48;
	dec /= 10;
    }
    s[ct++] = '.';
    while (rev){
	s[ct++] = (rev % 10) + 48;
	rev /= 10;
    }

    printf("%d\n", prop.exponent);
    printf("%s\n", s);
    printf("%.17a\n", val + tmp);
    return 0;
}
