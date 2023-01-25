#include "main.h"

/* Handle decimal/octa/hexa/binary formating */
intmax_t int_formt(uintmax_t risv_val, int buff_inx, int alpha_case, int base, int _signed, char *buff, flag *fg){
    int8_t c;       /* stores space || zero */
    int8_t p; /* stores extra characters invoked by hash */
    uintmax_t tmp_val;
    int32_t sign;
    int32_t len;
    int32_t spc;
    int32_t plus;
    int32_t tmp_len;
    int32_t _case;

    /* ... */
    base == decimal ? _case = 0 : 0;
    base == hexadecimal ? _case = 1 : 0;
    base == octadecimal ? _case = 2 : 0;
    base == binary ? _case = 3 : 0;
    /* */

    len = 0;
    /* signed and negative? Remove sign */
    sign = 0;
    if (_signed && (intmax_t)risv_val < 0){
	risv_val = (intmax_t)risv_val * -1;
	sign = 1;
	len += 1;
    }
    fg->width -= sign ? 1 : 0;
    /* length */
    tmp_val = risv_val;
    while (tmp_val){
	len++;
	tmp_val /= base;
    }

    /* Assign space && plus */
    spc = 0;
    if (fg->space || sign){
	!(fg->plus) && !(sign) ? spc = 1, --fg->width : 0;
	!(fg->neg) && sign ? SWITCH_OFF(spc), fg->width++ : 0;
	fg->neg && sign ? fg->width++ : 0;
    }

    plus = 0;
    if (fg->plus)
	(!sign) ? plus = 1, --fg->width : 0;

    /* switch off some flags */
    if (_case == 1 || _case == 2 || _case == 3){
	plus ? SWITCH_OFF(plus), ++fg->width : 0;
	spc && _case != 2 ? SWITCH_OFF(spc), ++fg->width : 0;
    }

    /*store character for padding*/
    c = fg->zero_pad && !(fg->neg) ? '0' : ' ';

    /* create space for special input from hash */
    _case == 1 && fg->hash ? len += 2 : 0;
    _case == 2 && fg->hash && !fg->zero_pad ? len += 1  : 0;
    _case == 3 && fg->hash ? len += 2 : 0;

    /* Canonicalize width with length */
    if (fg->width)
	fg->width = fg->width > len ? fg->width - len : 0;

    /* Push some flags to buffer */
    plus && fg->zero_pad ? PUSH('+', buff, buff_inx++) : 0;
    spc ? PUSH(' ', buff, buff_inx++) : 0;
    sign && fg->zero_pad ? PUSH('-', buff, buff_inx++) : 0;

    /* front padding */
    while (fg->width && !(fg->neg)){
	PUSH(c, buff, buff_inx++);
	fg->width--;
    }
    plus && !fg->zero_pad ? PUSH('+', buff, buff_inx++) : 0;
    sign && !fg->zero_pad ? PUSH('-', buff, buff_inx++) : 0;

    /* Dec */
    if (_case == 0){
	tmp_len = buff_inx;
	while (risv_val){
	    PUSH((risv_val % 10) + 48, buff, buff_inx++);
	    risv_val /= 10;
	}
	REV_AR(char, buff);
	REV_AR_buff(buff + tmp_len, buff_inx - tmp_len);
    }
    /* Hex */
    else if (_case == 1){
	if (fg->hash){
	    PUSH('0', buff, buff_inx++);
	    p = alpha_case ? 'X' : 'x';
	    PUSH(p, buff, buff_inx++);
	}
	buff_inx = hex_conv(risv_val, buff_inx, alpha_case, buff, fg->prsn);
    }
    /* Oct */
    else if (_case == 2){
	if (fg->hash){
	    if (fg->hash && !fg->zero_pad)
		PUSH('0', buff, buff_inx++);
	}
	buff_inx = octal(risv_val, buff, buff_inx);
    }
    /* Bin */
    else if (_case == 3){
	if (fg->hash){
	    PUSH('0', buff, buff_inx++);
	    p = alpha_case ? 'B' : 'b';
	    PUSH(p, buff, buff_inx++);
	}
	buff_inx = bina_ry(risv_val, buff, buff_inx);
    }

    /* Back padding */
    while (fg->width && fg->neg){
	PUSH(c, buff, buff_inx++);
	fg->width--;
    }

    return buff_inx;
}

/* Octadecimal */
intmax_t octal(uintmax_t oct, char *buff, int buff_inx){
    REV_AR(char, buff);
    int32_t tmp_len = 0;

    tmp_len = buff_inx;

    while (oct){
	buff[buff_inx++] = (oct % 8) + 48;
	oct /= 8;
    }
    REV_AR_buff(buff + tmp_len, buff_inx - tmp_len);

    return buff_inx;
}

/* Binary */
intmax_t bina_ry(uintmax_t binr, char *buff, int buff_inx){
    REV_AR(char, buff);
    int len = 0;

    while (binr){
	buff[buff_inx++] = binr % 2 ? 49 : 48;
	binr /= 2; len++;
    }
    while (len < 4)
	buff[buff_inx++] = 48, len++;

    REV_AR_buff(buff + (buff_inx - len), len);
    return buff_inx;
}

/* Hexadecimal */
int32_t hex_conv(uintmax_t val, int buff_inx, unsigned int alp_case, char *buff, int prsn){
    unsigned int s;      /* hex a(A) */
    unsigned int e;     /*hex f(F) */
    register int i; /* variable counter  */
    int tmp_len; /* initial length */
    int c; /* stores remainder */

    s = 65;
    tmp_len = buff_inx;
    prsn = ~prsn + 1;  /* reverse sign */

    while (val && prsn){
	c = val % 16;
	if (c >= 0 && c <= 9)
	    buff[buff_inx++] = c + 48;
	else {
	    i = 10;
	    s = !(alp_case) ? LOWER_a : UPPER_A;
	    e = !(alp_case) ? HEX_f : HEX_F;

	    for (; i < 16 && s <= e; i++, s++){
		if (c == i){
		    buff[buff_inx++] = s;
		    break;
		}
	    }
	}
	val /= 16;
	prsn += 1;
    }
    REV_AR(char, buff);
    REV_AR_buff(buff + tmp_len, buff_inx - tmp_len);
    return buff_inx;
}
