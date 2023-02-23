#include <stdio.h>
#include "main.h"
#include <float.h>
int brk(long double, int *, int);
int rev_num(uintmax_t *);
#define diff_dbl (1 - DBL_EPSILON)

int main(){
    char s[100];
    int i = 0;
    long double k = -0.0005;
    printf("%12.32Lfh\n", k);
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
    ldbl_t p_dbl;
    uintmax_t c_int;
    int32_t track, negat;
    int32_t i, oo;
    int32_t spc, plus;
    flag tt = {.space = 0, .plus = 0, .neg = 0, .zero_pad = 0, .width = 0, .prsn = 55, .star = 0, .hash = 0};
    flag *fg = &tt;
    ldbl_t temp_dbl;
    int32_t temp_int;
    int32_t tmp_len = 0;
    int32_t *s = malloc(1024);
    int32_t k_int;
    int32_t j;
    int8_t c;
    int16_t expont;
    //c = 'e';
    track = 0;
    expont = 0;

    if (val < 0.0){
	val = -(ldbl_t)val;
	negat = 1;
	track++;
    }
    if (c == 'g'){
	temp_dbl = val;
	while (!(int)(temp_dbl)){
	    expont++;
	    if (expont > 4){
		expont = 0;
		goto exponential;
	    }
	    temp_dbl *= 10;
	}
    }
    /* exponential */
    if (c == 'e'){
    exponential:
	if (val > diff_dbl){
	    while ((int)(val / 10)){
		val /= 10;
		track++;
		expont++; /* keep track of exponent */
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

    if (fg->prsn == 0){
	val += 0.5;
	val = (uintmax_t)val;
    }
    c_int = val;
    p_dbl = (ldbl_t)(val - c_int);
    temp_int = c_int;

    track += (c_int == 0) ? 1 : 0;

    /* length of non-decimal float */
    while (temp_int){
	track++;
	temp_int /= 10;
    }
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

   i = 0;
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
	p_dbl = (double)p_dbl - k_int;
	s[j++] = k_int;
    }
    int kp = 0;
    while (kp != 55)
	printf("%d", s[kp++]);
    printf("\n");
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
    /* integer part */
    if (c_int)
	rev_num(&c_int);

    c_int == 0 ? buff[i++] = 48 : 0;
    /** TODO: strongly work on this */
    while (c_int){
	    buff[i++] = (c_int % 10) + 48;
	    c_int /= 10;
	}
    fg->prsn ? buff[i++] = '.' : 0;

    /* fractional part */
    /** TODO strongly work on this */
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
