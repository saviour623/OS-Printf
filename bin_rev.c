#include "main.h"

/* Reverse binary */
intmax_t rev_bin(char *str, int buff_inx, char *buff, flag *fg){

    register int32_t oo = 0;   /* Counter */
    uintmax_t risv_val;   /* recieves val */

    /* Convert hex to int */
    if (str != NULL || str != ""){
	if (str[oo] == '0' && (str[oo + 1] == 'b' ||  str[oo + 1] == 'B'))
	    oo += 2;
	risv_val = rev_bin_ct(str + oo);
    }
    return int_formt(risv_val, buff_inx, 0, 10, 0, buff, fg);
}

uintmax_t rev_bin_ct(char *string){
    uintmax_t str_num; /* convert to integer */
    int length; /* variable length of string */
    int conv_rt; /* stores converted binary */

    str_num = *string - 48;
    length = str_len(string) - 1;

    if (*string == '\0')
	return 0;
    conv_rt = str_num * simple_pow(2, length);

    return conv_rt + rev_bin_ct(string + 1);
}
