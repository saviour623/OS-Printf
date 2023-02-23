#include <stdio.h>
#include <limits.h>
#include <stdarg.h>
#include <stdint.h>

#define GABBAGE 65
#define cmp(type, x) (__builtin_types_compatible_p(typeof(x), type) ? x : GABBAGE)
void arg(int n, ...){
	va_list arg;
	va_start(arg, n);
	printf("%lld\n", cmp(int, (intmax_t)va_arg(arg,  unsigned int)));
	va_end(arg);
}
int main(){
    uint64_t oo = 0;
    int i = 0;
    oo |= 64;
    oo = 0b1000000;
    double mantissa = 0;
    uint64_t revBit = oo;

    while (revBit){
	mantissa += (revBit % 2) * ((double)2 << -1);//(1/(double)(2LL << i));
	revBit /= 2;
	i++;
    }
    printf("%.9f\n", mantissa);
    return 0;
}
