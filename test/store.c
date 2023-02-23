#include <stdio.h>
#include <stdint.h>
#include <float.h>
#define tty 1643456277217746643563311552l
double pow_r(int32_t base, int32_t powr);
#define SET 0b1111111111111111111111111111111111111111111111111111111111111111

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
int main(){
    union {
	double x;
	int64_t gg;
    } op;
    double resetdbl_k;
    double fracdec;
    int32_t i, count;
    int64_t bits, revBit;
    int64_t frop;
    int64_t expon;
    int32_t sign;
    double mantissa;

    op.x = 1643456277217746643563311552.765;
    printf("%.64Lb\n", op.x);
    fracdec = count = 0;

    sign = op.gg >> 63;
    op.gg <<= 1;

    /* extract exponent */
    expon = (op.gg & (SET << 53)) >> 53;
    expon = expon - 0X3FF; /*  bias */
    op.gg <<= 11;

    printf("expon %Ld\n", expon);
    /** save bit state for mantissa */
    bits = op.gg;

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
	/* remove trailing ones if present:/
        if all ones swap to zeros else don't */
	if (frop >> (64 - count))
	    frop = frop ^ (SET << (64 - count));

	/** @expon < 0: remove sign @count: denomalizing power to base 2 */
	count -= expon < 0 ? (-expon - 1) : 0;

	/* divide by number of bits to power of radix(2) */
	fracdec = frop / (pow_r(2, 64 - count));

	printf("%f\n", fracdec);

        /* Extract decimal */
	op.gg = (op.gg >> 1) | (1LL << 63);
	op.gg = (op.gg >> (64 - (expon + 1)));
	op.gg = op.gg ^ (SET << (expon + 1));
	printf("dec %Ld\n", op.gg);
    }
    /* else reset bits to double representation */
    else if (expon > 63){
	expon += 1023; printf("%.64Lb\n", op.gg);
	op.gg = ((op.gg >> 12) ^ (SET << (64 - 12)));
	op.gg = (expon << 52) | op.gg; /*add exp */
	resetdbl_k = *(double *)&op.gg; /* copy */

	printf("p2 %f\n", resetdbl_k);
    }
    /* To conclude extract mantissa */
    revBit = i = 0;
    count = 64;
    /* reverse bits */
    while (i < count){
	revBit |= bits & (1LL << i) ? 1LL << ((count - 1) - i) : 0;
	i++;
    }
    /* extract mantissa as floating point */
    mantissa = i = 0;
    while (revBit){
	mantissa += (revBit % 2) * (1/(double)(2LL << i));
	revBit /= 2;
	i++;
    }
    mantissa += 1;
    printf("mantissa %f\n", mantissa);

    return 0;
}
