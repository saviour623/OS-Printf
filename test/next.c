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
//    expon = expon < 0 ? -expon : expon;
int main(){
    union {
	double x;
	int64_t gg;
    } op;
    double resetdbl_k;
    double fracdec;
    int count;
    int64_t frop;
    int64_t expon;
    int32_t sign;

    op.x = 0.1356322;
    printf("%.30f\n", op.x);
    //printf("%Lb\n", op.x);
    fracdec = count = 0;

    sign = op.gg >> 63;
    op.gg <<= 1;

    /* extract exponent */
    expon = (op.gg & (SET << 53)) >> 53;
    expon = expon - 0X3FF; /*  bias */
    printf("expon %Ld\n", expon);
    op.gg <<= 11;

    printf("test %.64Lb\n", op.gg);
    /** if possibility of fraction :- 0 < @expon < 64
     * @fracdec: decimal part, @frop: decimal fraction */
    if (expon < 64){
	/* exponential */
	frop = op.gg;
	frop = expon ? frop << expon : frop; /* shift out decimal part */
	printf("check 1 %.64Lb\n", frop);
	/* extract only fractional. expel backward zeros */
	while (frop && !(frop & 1)){
	    count++;
	    frop >>= 1;
	}
	printf("check %.64Lb\n", frop);
	/* remove trailing ones if present:/
        if all ones swap to zeroselse don't */
	if (frop >> (64 - count))
	    frop = frop ^ (SET << (64 - count));

	/* divide by number of bits to power of radix(2) */
	fracdec = frop / (pow_r(2, 64 - count));

	printf("%f\n", fracdec);

        /* Extract decimal */
	op.gg = expon ? (op.gg >> 1) | (1LL << 63) : op.gg;
	op.gg = (op.gg >> (64 - (expon + 1)));
	op.gg = op.gg ^ (SET << (expon + 1));
	printf("%Ld\n", op.gg);
    }
    /* else reset bits to double representation */
    if (expon > 63){
	expon += 1023;
	op.gg = ((op.gg >> 12) ^ (SET << (64 - 12)));
	op.gg = (expon << 52) | op.gg; /*add exp */
	resetdbl_k = *(double *)&op.gg; /* copy */

	printf("p2 %f\n", resetdbl_k);
    }
    return 0;
}
