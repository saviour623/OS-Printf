#include "main.h"

/** Some important functions;
 * @str_len: returns length of string;
 * @simple_pow: returns the power of a  base;
 * @str_atoi: converts string to integer.
 */
uint8_t str_len(char *str){
    uint8_t i = 0;
    while (str[i] != '\0')
	i++;
    return i;
}

intmax_t simple_pow(int base, int power){
    if (base < 0 || power < 0)
	return -1;
    if (!base)
	return 0;
    else if (!power)
	return 1;
    else if (base == 1)
	return 1;
    return (base * simple_pow(base, power - 1));
}

uintmax_t str_atoi(char *str){
    register int64_t i = 0;
    uintmax_t res = 0;
    int sign = 0;

    while (str[i]){
	if (str[0] == '-' && !(sign)){
	    sign = -1;
	    i++;
	    continue;
	}
	else if (str[i] >= 48 && str[i] <= 57)
	    res = (res * 10) + (str[i] - 48);
	else {
	    res = 0;
	    sign = 0;
	    break;
	}
	i++;
    }
	return (sign == -1) ? (res * sign) : res;
}
