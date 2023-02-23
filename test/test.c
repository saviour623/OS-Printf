#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <limits.h>
#define _ARG_ (va_list)0

#define MAX 0b11111111111111111111111101111111
#define MIN 0b00000000000000000000000010000000
//_Pragma ("GCC error \"parse.y\"")
int main(){
	int p = 3;
	2 > 3 ? p = 2 : 0;

	char *op;
	printf("%#-05o\n", 45);
	return 0;
}
