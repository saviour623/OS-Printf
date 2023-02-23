#include <string.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define ST_LINE "\e[1;1H\e[2J" //_Generic((x)
#define clr() printf("\e[1;1H\e[2J") //clear screen
#define printf_dec_format(x) __builtin_types_compatible_p(x,	\
    char: "%c", \
    signed char: "%hhd", \
    unsigned char: "%hhu", \
    signed short: "%hd", \
    unsigned short: "%hu", \
    signed int: "%d", \
    unsigned int: "%u", \
    long int: "%ld", \
    unsigned long int: "%lu", \
    long long int: "%lld", \
    unsigned long long int: "%llu", \
    float: "%f", \
    double: "%f", \
    long double: "%Lf", \
    char *: "%s", \
    void *: "%p")
#define print(x) printf(printf_dec_format(x), x)
#define printnl(x) printf(printf_dec_format(x), x), printf("\n");

struct tim {
	int secs;
	int mins;
	int hour;
} pt;

void struc(struct tim *, const int);

int main(void){
	__label__ brk;

	pt.secs = 0;
	pt.mins = 0;
	pt.hour = 0;
	struc(&pt, 0);
	return 0;
}
void struc(struct tim *ts, const int d){
	int secs;
	int mins;
	int hour;
	if (!d){
		secs = ts->secs;
		mins = ts->mins;
		hour = ts->hour;
	}
	if (d){
		time_t p;
		p = time(NULL);
		struct tm *tv;
		tv = localtime(&p);
		mins = tv->tm_min;
		secs = tv->tm_sec;
		hour = tv->tm_hour;
	}
	clock_t x;
	x = clock();
	for(; secs < 60; secs){
		clr();
		printf("%02u : %02u : %02u\n", hour, mins, secs);
		secs += 1;
		if (secs == 59){
			mins += 1;
			secs = -1;
		}
		if (mins == 59){
			hour += 1;
			mins = -1, secs = -1;
		}
		sleep(1);
	}
	x = clock() - x;
	printf("%f\n", (double)x /CLOCKS_PER_SEC);
}
