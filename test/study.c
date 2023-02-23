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
	uint64_t gg;
    } op;
    double resetdbl_k;
    double fracdec;
    int count;
    uint64_t frop;
    int64_t expon;
    int32_t sign;

    op.x = 0.45315;
    
//    op.x = DBL_MAX;
    printf("%.64Lb\n", op.x);
    fracdec = count = 0;

    sign = op.gg >> 63;
    op.gg <<= 1;

    /* extract exponent */
    expon = op.gg >> 53;
    expon = expon - 0X3FF; /*  bias */
    op.gg <<= 11;

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
//	if (frop >> (64 - count))
	    //frop = frop ^ (SET << (64 - count));

	/** @expon < 0: remove sign @count: denomalizing power to base 2 */
	if (expon < 0){
	    expon = -expon;
	    count -= (expon - 1);
	}
	/* divide by number of bits to power of radix(2) */
	fracdec = frop / (pow_r(2, 64 - count));

	printf("%.127f\n", fracdec);

        /* Extract decimal */
	op.gg = (op.gg >> 1) | (1LL << 63);
	op.gg = (op.gg >> (64 - (expon + 1)));
	//op.gg = op.gg ^ (SET << (expon + 1));
	printf("%Ld\n", op.gg);
    }
    /* else reset bits to double representation */
    else if (expon > 63){
	expon += 1023;
	op.gg = op.gg >> 12;
	op.gg = (expon << 52) | op.gg; /*add exp */
	resetdbl_k = *(double *)&op.gg; /* copy */
	printf("p2 %f\n", resetdbl_k);
    }
    return 0;
}
