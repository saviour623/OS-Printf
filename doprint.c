#include "main.h"
void mai(const char *, ...);

void mai(const char *str, ...){
    va_list args;
    va_start(args, str);

    specifier(str, args);
}

int main(){
    mai("%05d %5d michael %.4s", -35, 4455, "Saviour");
    printf("%05d %5d michael %.4s\n", -35, 4455, "Saviour");
    return 0;
}

int specifier (const char *str, va_list args){
    register int8_t  i = 0;
    flag fg = {0, 0, 0, 0, 0, -1, 0, 0};
    char *buff = malloc(1024);
    register intmax_t len = 0;
    int8_t stage = FL_INT;
    uintmax_t val; /* integers */
    long double db_val; /* floats */
    char *sr_val; /* strings */
    int8_t cr_val; /* char */
    char *rev;
    int32_t base, HASH, SIGNED, CASE;

    UNUSED(HASH);

    enum {
	normal_s,
	flag_s,
	width_s,
	prsn_s,
	modifiers_s,
	output_mod_s
    } off_fmt;
    off_fmt = normal_s;

    while (str[i]) {
	switch (off_fmt) {
	case normal_s:
	    if (str[i] == '%'){
		stage = FL_INT;
		off_fmt = flag_s;
		HASH = 0, CASE = 0, SIGNED = 0;
	    }
	    else
		PUSH(str[i], buff, len++);
	    break;
	case flag_s:
	    switch (str[i]) {
	    case ' ':
		fg.space = 1;
		break;
	    case '+':
		fg.plus = 1;
		break;
	    case '-':
		fg.neg = 1;
		break;
	    case '0':
		fg.zero_pad = 1;
		break;
	    case '#':
		fg.hash = 1;
		break;
	    default:
		i--;
		off_fmt = width_s;
	    }
	    break;
	case width_s:
	    switch (str[i]){
	    case '*':
		fg.width = va_arg(args, int);
		break;
	    case '1': case '2': case '3': case '4':
	    case '5': case '6': case '7': case '8':
	    case '9':
		while (ischar_digit(str[i])){
		    fg.width = (fg.width * 10) + (str[i] - 48);
		    i++;
		}
		SUB_1(i);
		break;
	    default:
		i--;
		off_fmt = prsn_s;
		break;
	    }
	    break;
	case prsn_s:
	    switch (str[i]){
	    case '.':
		if (str[i + 1] == '*'){
		    fg.prsn = va_arg(args, int);
		    ADD_1(i);
		}
		else if (ischar_digit(str[i + 1])){
		    ADD_1(i);
		    fg.prsn = 0;
		    while (ischar_digit(str[i])){
			fg.prsn = (fg.prsn * 10) + (str[i] - 48);
			i++;
		    }
		    SUB_1(i);
		}
		else if (str[i + 1])
		    fg.prsn = 0;
		break;
	    default:
		i--;
		off_fmt = modifiers_s;
	    }
	    break;
	case modifiers_s:
	    switch (str[i]){
	    case 'h':
		SUB_1(stage); /*for  Short*/
		break;
	    case 'l':
		ADD_1(stage); /* for Long*/
		break;
	    case 'z':
		stage = FL_LONG; /*size_t*/
		break;
	    case 't':
		stage = FL_LONG;
		break;
	    case 'j':
		stage = FL_LONG_LONG; /* ptrdiff_t */
		break;
	    case 'L':
	    case 'q':
		stage = FL_LONG_LONG;
		break;
	    case '~':
		stage = FL_REV;
		break;
	    default:
		i--;
		off_fmt = output_mod_s;
	    }
	    stage < MIN_S ? stage = MIN_S : 0;
	    stage > MAX_S ? stage = MAX_S : 0;
	    str[i] == '~' ? stage += 1 : 0;
	    stage > FL_REV ? stage = FL_REV : 0;
	    break;
	case output_mod_s:
	    switch (str[i]) {
	    case 'P':
		CASE = 1;
	    case 'p':
		fg.hash += 1;
		fg.prsn = SIZE_BIT;
		val = (uintmax_t)(uintptr_t) va_arg(args, void *);
		len = int_formt(val, len, CASE, 16, SIGNED, buff, &fg);
		break;
	    case 'X':
		CASE = 1;
	    case 'x':
		if (stage == FL_REV){
		    rev = va_arg(args, char *);
		    len = rev_hex(rev, len, buff, &fg);
		    break;
		}
		fg.prsn = -1;
		val = sigd_unsgd(stage, SIGNED, &args);
		len = int_formt(val, len, CASE, 16, SIGNED, buff, &fg);
		break;
	    case 'O':
		CASE = 1;
	    case 'o':
		if (stage == FL_REV){
		    rev = va_arg(args, char *);
		    len = rev_oct(rev, len, buff, &fg);
		    break;
		}
		fg.prsn = -1;
		val = sigd_unsgd(stage, SIGNED, &args);
		len = int_formt(val, len, CASE, 8, SIGNED, buff, &fg);
		break;
	    case 'B':
		CASE = 1;
	    case 'b':
		if (stage == FL_REV){
		    rev = va_arg(args, char *);
		    len = rev_bin(rev, len, buff, &fg);
		    break;
		}
		val = sigd_unsgd(stage, SIGNED, &args);
		len = int_formt(val, len, CASE, 2, SIGNED, buff, &fg);
		break;
	    case 'u':
		val = sigd_unsgd(stage, SIGNED, &args);
		base = decimal;
		len = int_formt(val, len, CASE, 10, SIGNED, buff, &fg);
		break;
	    case 'i':
	    case 'd':
		SIGNED = 1;
		val = sigd_unsgd(stage, SIGNED, &args);
		len = int_formt(val, len, CASE, 10, SIGNED, buff, &fg);
		break;
	    case 'c':
		fg.prsn = -1;
		cr_val = (char)va_arg(args, int);
		len = str_fmt(&cr_val, buff, 1, len, stage, &fg);
		break;
	    case 's':
		sr_val = va_arg(args, char *);
		uint8_t k = str_len(sr_val);
		len = str_fmt(sr_val, buff, k, len, stage, &fg);
		break;
	    }
	    off_fmt = normal_s;
	    break;
	default:
	    i--;
	    off_fmt = normal_s;
	}
	i++;
    }
    buff[len] = '\0';
    printf("%s\n", buff);
}

int str_fmt(char *s, char *buff, int len, int buff_inx, int stage, flag *fg){
    int i, k, tmp_len;

    tmp_len = buff_inx;
    i = 0; k = 0;

    if (stage == FL_REV && len != 1){
	while (1){
	    if (s[i] == ' ')
		i++;
	    else
		break;
	}
	k = 1;
	while (1){
	    if (s[len - k] == ' ')
		k++;
	    else
		break;
	}
	len -= (i + (--k));
    }

    if (fg->prsn > len)
	fg->prsn = -1;
    len = !(fg->prsn) ? 0 : len;
    len = fg->prsn > 0 ? fg->prsn : len;

    fg->width = len < fg->width ? fg->width - len : 0;
    if (fg->width && !(fg->neg))
	buff_inx += fg->width;

    while (len){
	buff[buff_inx++] = s[i];
	i++; len--;
    }

    while (fg->width){
	if (fg->neg)
	    buff[buff_inx++] = ' ';
	else
	    buff[tmp_len++]= ' ';
	fg->width--;
    }
    return buff_inx;
}
