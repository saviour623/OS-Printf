#include <stdint.h>
#include <stdlib.h>

int16_t arr_cal(uintmax_t val, uintmax_t mult, int16_t *buff);
#define UNUSED(var) (void)var
#define ASSIGN(ARR, VAL, LEN)\
     while (VAL){\
	ARR[LEN++] = VAL % 10;\
	VAL /= 10;\
    }
#define REV(ARR, ST, LEN)\
    --LEN; \
    while (ST < LEN){ \
	ARR[ST] ^= ARR[LEN];\
	ARR[LEN] ^= ARR[ST]; \
	ARR[ST++] ^= ARR[LEN--];\
    }
#define RESET(buff, x, len) for (int16_t i = 0; i < len;) \
	    buff[x][i++] = 0;

int16_t arr_cal(uintmax_t val, uintmax_t mult, int16_t *buff){
    int16_t *a_buff = malloc(1023);
    int16_t *b_buff = malloc(1023);
    int16_t *reslt[2];
    reslt[0] = malloc(1023);
    reslt[1] = malloc(1023);

    int32_t a_len, b_len;
    int16_t temp;

    /* all buffers contains reverse integers */
    a_len = b_len = 0;
    ASSIGN(a_buff, val, a_len);
    ASSIGN(b_buff, mult, b_len);

    int16_t carry_over = 0;
    /* length and iterator variables */
    register int16_t oo = 0;
    register int16_t bb = 0;
    int16_t x = 0;
    int16_t j = 0;
    int16_t len = 0;

    int16_t u, e, m;
    UNUSED(u); UNUSED(e); UNUSED(m);

    /* handle mul */
    for (; bb < b_len; bb++){
	while (oo < a_len){
	    temp = (b_buff[bb] * a_buff[oo]) + carry_over;
	    carry_over = 0;

	    while(x && j < bb){
		reslt[x][j++] = 0;
	    }
	    if (temp > 9)
		carry_over = temp / 10;
	    reslt[x][j++] = temp % 10;

	    oo++;
	    if (oo == a_len && carry_over)
		reslt[x][j++] = carry_over;
	}

        /* length of first array */
	if (x == 0)
	    len = j;
        /* handle sum */
	if (x){
	    u = e = 0;
	    while (u < len){
	        m  = reslt[0][u] + reslt[x][e];
		if (m < 10)
		    reslt[0][u] = m;
		else {
		    reslt[0][u] = m % 10;
		    if ((e + 1) >= j){
			reslt[x][e + 1] = m / 10;
			j++;
		    }
		    else reslt[x][e + 1] += (m / 10);
		}
		e++; u++;
	    }
	   /* canonicalize 'e' with 'j' since 'u' may be lesser */
	    e < j ? e = j : 0;

	    /* because 'e' might always be larger than 'u' */
	    for (u; u < e; u++)
		reslt[0][u] = reslt[x][u];
	    len = u;
	}

	carry_over = oo = j = 0;
	b_len > 1 ? x = 1 : 0;
	RESET(reslt, 1, len);
    }
    oo = 0; /* (oo reused) Emit reslt to buffer */
    for (; oo < len; oo++)
	buff[oo] = reslt[0][oo];
    oo = 0; u = len;
    REV(buff, oo, u);

    /* free mem */
    free(a_buff); free(b_buff);
    free(reslt[0]); free(reslt[1]);
    return len;
}
