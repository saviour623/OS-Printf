#include <stdio.h>
#include "main.h"
#include <float.h>
int brk(long double, int *, int);
int rev_num(uintmax_t *);
#define diff_dbl (1 - DBL_EPSILON)
#define INTDIV(val, length_of_dec, buff, len)			\
    val = val / pow_r(10, length_of_dec);			\

int main(){
    char s[100];
    int i = 0;
    long double k = 0.0005;
    printf("%Lfh\n", k);
//    printf("%-6dh\n", -1234);
    float_precision(k, s, 6);

    i = 0;
    printf("%s", s);
    printf("\n");

     return 0;
}

int rev_num(uintmax_t *val){
    uintmax_t rev = 0;
    int len = 0;
    while (*val){
	rev = (rev * 10) + (*val % 10);
	len++;
	*val /= 10;
    }
    *val = rev;
    return len;
}

void float_precision(ldbl_t val, char *buff, int prsn){
    float_prop properties;
    ldbl_t p_dbl;
    uintmax_t c_int;
    int32_t track, sign;
    int32_t i, oo;
    int32_t spc, plus;
    flag tt = {1, 1, 1, 0, 0, 12, -1, 0};
    flag *fg = &tt;
    ldbl_t temp_dbl;
    double temp_dec;
    int32_t tmp_len = 0;
    int32_t *s = malloc(1024);
    int32_t k_int;
    int32_t j;
    int8_t c = 'e';
    int32_t exponent;
    int32_t lenth_of_dec;

    lenth_of_val = 0;
    track = 0;
    sign = 0;

    if (val < 0){
	val = -val;
	sign = 1;
    }
    /* %G */
    if (c == 'G' || c = 'g'){
	temp_dbl = val;
	while (!(int)(temp_dbl)){
	    expont++;
	    if (expont > 4)
		goto exponential;
	    temp_dbl *= 10;
	}
    }
    /* %E */
    if (c == 'E' || c == 'e'){
    exponential:
	if (val > diff_dbl){
	    while ((int)(val / 10)){
		val /= 10;
		track++;
		expont++; /* keep track of exponient */
	    }
	}
	else if (val <= diff_dbl){
	    while (1){
		if ((int)(val * 10) > 9)
		    break;
		val *= 10;
		track++;
		expont++;
	    }
	}
    }

    if (!(fg->prsn))
	val += 0.5;
    float_manipul(val, &properties);
    properties.exponent = exponent;
    properties.decimal = c_int;
    properties.fractional = p_dbl;

    if (c_int > (double)(ULLONG_MAX)){
	int islargenum = 1;
	goto handlebuffer;
    }
    else 
    if (sign)
	track |= 1;
    track |= (c_int == 0) ? 1 : 0;

    /* length of decimal integer */
    while ((int)temp_dec){
	length_of_dec |= 1;
	temp_dec /= 10;
    }
    track |= length_of_dec;

    /* canonicalize precision */
    fg->prsn = fg->prsn < 0 ? 6 : fg->prsn;
    track += fg->prsn;
    /* space for '.' */
    track += fg->prsn ? 1 : 0;

    /* Assign space && plus */
    spc = 0;
    if (fg->space || negat){
	!(fg->plus) && !(negat) ? spc = 1, track++ : 0;
	if (!(fg->neg) && negat)
	    spc ? SWITCH_OFF(spc), track-- : 0;
    }

    plus = 0;
    if (fg->plus)
	(!negat) ? plus = 1, --fg->width : 0;
   /* width assignment*/
   fg->width = track < fg->width ? fg->width - track : 0;

   i = 0; /* pre-width skip */
   if (fg->width && !(fg->neg)){
       tmp_len = 0;
       i = fg->width;
   }

   /* Push some flags to buffer */
    plus ? PUSH('+', buff, i++) : 0;
    spc ? PUSH(' ', buff, i++) : 0;
    negat ? PUSH('-', buff, i++) : 0;

    /* push float values with precision to temporary buffer */
    k_int = 0;
    j = 0;
    while (j < fg->prsn){
	p_dbl = p_dbl * 10;
	k_int = p_dbl;
	p_dbl = p_dbl - k_int;
	s[j++] = k_int;
    }

    /* Precision */
    oo = j;
    while (j){
        /* run once */
	if(j == oo)
	    (int32_t)(p_dbl * 10) >= 5 ? s[j - 1] += 1, s[j] : 0;
	if (j - 1 == 0 && s[j - 1] == 10){
	    c_int += 1;
	    s[j - 1] = 0;
	    j--;
	    break;
	}
	s[j - 1] == 10 ? s[j - 2] += 1, s[j - 1] = 0 : -1;
	j--;
    }
    /* decimal integer part */
    if (!(int)c_int)
	buff[i++] = 48;
    /** TODO: strongly work on this */
    else {
	c_int = c_int / pow_r(10, length_of_dec);
	while (length_of_dec){
	    c_int = 10 * c_int;
	    buff[i++] = (int32_t)c_int + 48;
	    c_int = c_int - (int32_t)c_int;
	}
    }
    fg->prsn ? buff[i++] = '.' : 0;

    /* fractional part */
    while (j < oo)
	buff[i++] = s[j++] + 48;

    /* exponent part */
    /** TODO: Exponent */

    /* width */
    while (fg->width){
	!(fg->neg) ? PUSH(' ', buff, tmp_len++) : 0;
	fg->neg ? PUSH(' ', buff, i++) : 0;
	fg->width--;
    }
    buff[i++] = 'h';
    buff[i] = '\0';
}
