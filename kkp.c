#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <float.h>
#include <stdlib.h>
double pow_r(int32_t base, int32_t powr);
double pow_r(int32_t base, int32_t powr){
    if (!base)
	return 0;
    if (base == 1)
	return 1;
    if (!powr)
	return 1;
    if (powr == 1)
	return base;
    return base * pow_r(base, powr - 1);
}

int main(){
    long double x = 0.005;
    int i = 0;
//    pow_r(3);

    char buff[1023];

    sprintf(buff, "%f", pow_r(2, 128));
    printf("%s\n", buff);
    return 0;
}
