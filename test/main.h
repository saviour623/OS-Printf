#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include <limits.h>


int fgt(int);
void hk();

void hk(){
    int x;
    x = fgt(5);
    printf("%d\n", x);
}
#endif
