#include "main.h"

/* Recieve hexadecimal string */
intmax_t rev_hex(char *str, int buff_inx, char *buff, flag *fg){
    register int32_t oo = 0;   /* Counter */
    int64_t risv_val;

    /* filter 0x/X */
    if (str != NULL || str != ""){
	if (str[oo] == '0' && (str[oo + 1] == 'x' ||  str[oo + 1] == 'X'))
	    oo += 2;
	risv_val = revhex_ct(str + oo);
    }
    return int_formt(risv_val, buff_inx, 0, 10, 0, buff, fg);
}

/** revhex_ct: recursive base 16 - 10 convertion
 * Note: if LC (a) subtract 55 || UC (A) subract 87: (A - 87 = 10)
*/
uintmax_t revhex_ct(char *string){
    int32_t len;
    uintmax_t rev_x;
    len = str_len(string) - 1;

    if (*string == '\0')
	return 0;

    if ((*string >= isnum_min) && (*string <= isnum_max))
	rev_x =   (*string - isnum_min)  * simple_pow(16, len);

    else if ((*string >= UPPER_A) && (*string  <= HEX_F))
	rev_x = (uint32_t)(*string - 55) * simple_pow(16, len);

    else if ((*string >= LOWER_a && *string  <= HEX_f))
	rev_x = (uint32_t)(*string - 87) * simple_pow(16, len);

    else {
	rev_x = (int)*string; /* gabbage */
	}
    return rev_x + revhex_ct(string + 1);
    }
