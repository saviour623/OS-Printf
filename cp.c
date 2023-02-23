#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>

int main(){
    long double val;
    uintmax_t save;
    char s[1023];

    int c = 0;
    while (c < 10){
	printf("%d\n", c  1);
	c++;
    }

    val = 1.33453l;
    uintmax_t dec = (int)val;
    val = val - dec;

    uintmax_t dectr = val * pow(10, 17);
    int ct = 0;
    uintmax_t rev = 0;
    printf("%Ld\n", dectr);
    while (dectr){
	rev = (rev * 10) + (dectr % 10);
	dectr /= 10;
    }
    s[ct++] = (dec % 10) + 48;
    s[ct++] = '.';
    while (rev){
	s[ct++] = (rev % 10) + 48;
	rev /= 10;
    }

    printf("%s\n", s);
    printf("%.17Lf\n", val + dec);
    return 0;
}
