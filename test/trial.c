#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <stdint.h>
//11 1023 53
#define ones 0b1111111111111111111111111111111111111111111111111111111111111111
long double modfl(long double x, long double *y);

int main(){
    union bypass {
	double val;
	int64_t k;
    } op;
    int32_t sign;
    double mant;
    int64_t expon;
    int32_t count = 0;
    int i = 0;
    int64_t rev = 0;
    double dec = 0, fracdec;
    int64_t one1 = 0;
    long double gg = FLT_MAX;
    op.val = gg;

    int64_t kl= FLT_MAX;
    printf("%Ld\n", kl);
    printf("%f\n", gg);
    printf("bit %64Lb\n", op.k);
    sign = op.k >> 63;
    op.k <<= 1;

    /* exponent */
    printf("op.k %.64Lb\n", op.k);
    expon = (op.k & (ones << 53)) >> 53;
    expon = expon - 0X3FF; /*  bias */
    printf("%lld\n", expon);
    /* mantissa */
    op.k <<= 11;
    dec = op.k;

/*    while (!(op.k & 1LL)){
	count++;
	op.k >>= 1;
    } /* remove preceding trailing ones if present */
    op.k = op.k ^ (ones << (64 - count));
    printf("decbit %Lb\n", dec);
    /* collect decimal part */
    dec = (((op.k >> 1) >> (64 - expon)) ^ (ones << expon))  << 1;
    dec = dec * 9.7453140113E288;
    printf("dec %f\n", dec);
    /* collect fractional part */
//    fracdec = ((bit << (expon - 1)) >> (23 - expon)) & 0X7FFFFF;

    /* reverse bits */
    rev = i = 0;
    count = 64 - count;
    while (i < count){
	rev |= op.k & (1LL << i) ? 1LL << ((count - 1) - i) : 0;
	i++;
    }
    printf("rev %Lb\n", rev);

    /* extract mantissa */
    mant = i = 0;
    while (rev){
	mant += (rev % 2) * (1/(double)(2LL << i));
	rev /= 2;
	i++;
    }
    mant += 1;
    printf("result %f\n", 9223372036854775808 * mant);
    return 0;
}

    /*
    */
/* intmax_t int_formt(uintmax_t risv_val, int buff_inx, int alpha_case, int base, int _signed, char *buff, flag *fg){
 */

/*int dbl_n_prsn(ldbl_t k, int *s, int prsn){
    int i = 0;
   int c = 0;

    while (i < prsn){
	k = k * 10;
	c = k;
	k = k - c;
	s[i++] = c;
    }
    if (prsn){
  xcx  !((c = k * 10) < 5) ? s[i - 1] += 1, s[i] = 0 : 0;
    s[i - 1] == 10 ? s[i - 2] += 1, s[i - 1] = 0 : -1;
    }
    return i;
}
*/

/*
*(volatile unsigned int *)(volatile float *)(&f);
Joshua
May 31, 2010 at 2:44;




/*
Date: 01/01/2017
Author:root
*/
/*
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
//macros
#define GetHexValue_32(f) (GetHexValue((f), 32, 8)) 
#define GetDoubleValue_32(i) (GetDoubleValue((i), 32, 8))
#define GetHexValue_64(f) (GetHexValue((f), 64, 11))
#define GetDoubleValue_64(f) (GetDoubleValue((f), 64, 11))

uint64_t GetHexValue(long double f, unsigned bits, unsigned expBits)
{
    long double fNorm;
    int shift;
    long long sign, exp, significand;
    unsigned significandBits = bits - expBits - 1; // -1 for sign bit

    if (f == 0.0) return 0; // get this special case out of the way

    // check sign and begin normalization
    if (f < 0) { sign = 1; fNorm = -f; }
    else { sign = 0; fNorm = f; }

    // get the normalized form of f and track the exponent
    shift = 0;
    while(fNorm >= 2.0) { fNorm /= 2.0; shift++; }
    while(fNorm < 1.0) { fNorm *= 2.0; shift--; }
    fNorm = fNorm - 1.0;

    // calculate the binary form (non-float) of the significand data
    significand = fNorm * ((1LL<<significandBits) + 0.5f);

    // get the biased exponent
    exp = shift + ((1<<(expBits-1)) - 1); // shift + bias

    // return the final answer
    return (sign<<(bits-1)) | (exp<<(bits-expBits-1)) | significand;
}

long double GetDoubleValue(uint64_t i, unsigned bits, unsigned expBits)
{
    long double result;
    long long shift;
    unsigned bias;
    unsigned significandBits = bits - expBits - 1; // -1 for sign bit

    if (i == 0) return 0.0;

    // pull the significand
    result = (i&((1LL<<significandBits)-1)); // mask
    result /= (1LL<<significandBits); // convert back to float
    result += 1.0f; // add the one back on

    // deal with the exponent
    bias = (1<<(expBits-1)) - 1;
    shift = ((i>>significandBits)&((1LL<<expBits)-1)) - bias;
    while(shift > 0) { result *= 2.0; shift--; }
    while(shift < 0) { result /= 2.0; shift++; }

    // sign it
    result *= (i>>(bits-1))&1? -1.0: 1.0;

    return result;
}

int main(void)
{
    double d = 5.14159265359, d2;
    uint64_t di;

    di = GetHexValue_64(d);  // hex value 
    d2 = GetDoubleValue_64(di); // double value... converted hex value. 

    printf("double before : %.20lf\n", d); // it can change after point.  
    printf("double encoded: 0x%016" PRIx64 "\n", di);  // prix using Formatting.. 
    printf("double after  : %.20lf\n", d2); 
    return 0;
}
*/

/*
int main(void){
    float f = 28834.38282;
    char *x = (char *)&f; 
    printf("%f = ", f);

    for(i=0; i<sizeof(float); i++){ 
	printf("%02X ", *x++ & 0x0000FF); 
    }

    printf("\n");
    }						      */
//    op.k = op.k ^ (ones << (32 - count));
//expon = (expon ^ (ones << 11)) - 0X3FF; /* extract and bias */

/*while (!(op.k & 1)){
	count++;
	op.k >>= 1;
	}*/
    /* remove trailing ones */
//    op.k = op.k ^ (ones << (64 - count));

//    dec = ((op.k >> 1) | (1LL << count));
