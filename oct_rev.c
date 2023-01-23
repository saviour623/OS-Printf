#include "main.h"

/* Reverse octadecimal */
intmax_t rev_oct(char *str, int buff_inx, char *buff, flag *fg){

    register int32_t oo = 0;   /* Counter */
    uintmax_t risv_val;   /* recieves val */

    /* Convert hex to int */
    if (str != NULL && *str != '\0'){
	if (str[oo] == '0')
	    oo += 1;
	risv_val = rev_oct_ct(str + oo);
    }
    return int_formt(risv_val, buff_inx, 0, 10, 0, buff, fg);
}

uintmax_t rev_oct_ct(char *string){
    int str_num; /* stores integer */
    int length; /* variable length of string */
    int conv_rt; /* stores converted Oct */

    str_num = *string - 48;
    length = str_len(string) - 1;

    if (*string == '\0')
	return 0;
    conv_rt = str_num * simple_pow(8, length);

    return conv_rt + rev_oct_ct(string + 1);
}
