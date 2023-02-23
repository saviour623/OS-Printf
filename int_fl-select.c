#include "main.h"

/** @sigd_unsgd: Select typecast integers (signed and unsigned) to appropriate types */
uintmax_t sigd_unsgd(int stage, int signed_, va_list *args){
/* signed && unsigned types */
    uintmax_t val;

    switch (stage){
    case FL_CHAR:
	if (signed_)
	    val = (uintmax_t)(intmax_t)(char)va_arg(*args, int);
	else
	    val = (unsigned char)va_arg(*args, unsigned int);
	break;
    case FL_SHORT:
	if (signed_)
	    val = (uintmax_t)(intmax_t)(short)va_arg(*args, int);
	else
	    val = (unsigned short)va_arg(*args, unsigned int);
	break;
    case FL_INT:
	if (signed_)
	    val = (uintmax_t)(intmax_t)va_arg(*args, int);
	else
	    val = (uintmax_t)va_arg(*args, unsigned int);
	break;
    case FL_LONG:
	if (signed_)
	    val = (uintmax_t)(intmax_t)va_arg(*args, long);
	else
	    val = va_arg(*args, unsigned long);
	break;
    case FL_LONG_LONG:
	if (signed_)
	    val = (uintmax_t)(intmax_t)va_arg(*args, long long);
	else
	    val = (uintmax_t)va_arg(*args, unsigned long long);
	break;
    default:
	break;
    }
    return val;
}
long double flt_selec(int stage, int signed_, va_list *args){
/* float/double/long double */
    long double val;

    switch (stage){
    case FL_INT:
	val = (long double)va_arg(*args, double);
	break;
    case FL_LONG:
	val = (long double)va_arg(*args, long double);
	break;
    }
    return val;
}
