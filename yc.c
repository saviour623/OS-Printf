#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>

void exponent(double val, double inpt);
void print_exponent(double perm, double val, int prsn, int count);
long double round_exponent(long double val, int prsn);
void float_precision(double val, int prsn);
void long_double(long double val, int prsn);
void G_float(long double val, int prsn);
long double max(float);
int main(){
    float x = 0.00005;
    double y = 0.00005;
    long double z = max(x);
    G_float(z, 12);
    printf("\n%.12g\n", x);

    long_double(x, 16);
    printf("\n");

    float_precision(z, 16);
    printf("\n");

    printf("%.32f\n", y);

    return 0;
}
long double max(float x){
    long double y = (long double)(double)(x);
    return y;
}

void G_float(long double val, int prsn){
    long double p, y = 0.1;
    int x, zero_count, j;
    char *mem;
    long double ll = 0.1;
    mem = (char*)malloc(1024);
    x = (int)val;
    p = val - x;
    //preceeding decimal zeros
    p = p / ll;
    zero_count = 0;
    while (!(int)p){
	y *= ll;
	p = p / ll;
	zero_count += 1;
    }//exponent if preceeded by >3 0s.
    zero_count && prsn < 7 ? prsn = 0 : 0;
    prsn = prsn < 0 ? 0 : prsn;
    if ((int)val == 0 && zero_count >= 4){
	if (prsn == 0){
	    p = p + 0.5;
	    print_exponent(val, (int)p, prsn, zero_count + 1);
	}
	else
	    print_exponent(val, p, prsn, zero_count + 1);
    }
    //else:
    //print value according to number of prsn
    else {
	int k = 0;
	while ((int)val){
	    k += 1;
	    val = val / 10;
	}//if prsn is 5 print only five numbers (prsn - k)
	prsn -= k;

	p *= ll;
	y *= 10;
	p = (round_exponent(p, prsn) * y);
	//store int before floating point @mem
	j = 0;
	if (x == 0){
	    mem[j] = '0';
	    j++;
	}
	else {
	    while (x){
		mem[j] = (x % 10) + 48;
		x = x / 10;
		j++;
	    }//reverse array
	    int length = j - 1, mid = j / 2, i = 0;
	    char c;
	    while (mid){
		c = mem[length];
		mem[length] = mem[i];
		mem[i] = c;
		mid--; i++; length--;
	    }
	}
	mem[j] = '.';
	j += 1;

	//float to string(char)
	k = 0;
	while (k < (prsn + zero_count)){
	    p = p / ll + DBL_EPSILON;
	    mem[j] = (int)p + 48;
	    p = p - (int)p;
	    k++;
	    j++;
	}
	mem[j] = '\0';

	write(1, mem, j);
	free(mem);
    }
}
/** exponent - takes width and precision value from
 * the precision decimal input.
 * @prsn: A variadic variable for precision
 * @size_dbl: maximum float between 0 and 1 - EPSILON
 * @count: number of decimal point moved to be in between
 * first and second value of float.
 * @perm: stores unmodified value of val ##with sign
 */
void exponent(double val, double prsn){
    int count = 0;
    const double perm = val;
    double size_dbl = 1 - (DBL_EPSILON);

    if (val < 0)
	val = val * -1; //abs
    if (val == 0.0)
	write(1, "0.0e+00", 7);
    else if (val > size_dbl){
	int temp;
	while(val){
	    temp = val / (double)10;
	    if (temp == 0)
		break;
	    val /= (double)10;
	    count += 1; //power count
	}
    }
    else if (val <= size_dbl){
	while (!val || val){
	    if ((val * 10)  > 10)
		break;
	    val *= (double)10;
	    count += 1;
	}
    }
    //if prsn greater than 9 ignore precision
    if (prsn > 9)
	print_exponent(perm, val, prsn, count);
    else if (prsn && prsn <= 9){
	double store =  round_exponent(val, prsn);
	print_exponent(perm, store, prsn, count);
    }
    //if precision is 0 write float up to 0 dec places
    else if (prsn == 0){
	val = val + 0.5;
	double store = (int)val;
	print_exponent(perm, store, 0, count);
    }
}
void print_exponent(double perm, double val, int prsn, int count){
    int i = 0, j = 0;
    char buff[prsn + 7];
    if (perm < 0){
	buff[i] = '-';
	i += 1;
    }
    buff[i] = (int)val + 48;
    i += 1;
    if (prsn != 0){
	buff[i] = '.';
	i += 1;
    }
    while (j < prsn){
	val = val - (int)val;
	val = val / 0.1;
	buff[i] = (int)val + 48;
	i += 1;
	j += 1;
    }

    buff[i] = 'e';
    i++;
    if ((int)perm){
	buff[i] = '+';
	i += 1;
    }
    else{
	buff[i] = '-';
	i = i + 1;
    }
    if (count >= 0 && count < 9){
	buff[i] = '0';
	i++;
	buff[i] = count + 48;
	i++;
    }
    else if (count > 9){
	char tem[3];
	int j = 0;
	while (count){
	    tem[j] = (count % 10) + 48;
	    count = count / 10;
	    j++;
	}
	tem[j] = '\0';
	int k = 0;
	while (tem[k]){
	    k += 1;
	    buff[i] = tem[j - k]; i++;
	}
    }
    buff[i] = '\0';
    write(1, buff, sizeof(buff));
}
/** round_exponent - round up float
 * @num: stores integer of float
 * @stores: point float value after integer part
 * @k: Add 1 to precision value to allow roundup
 * Return: rounded up float(double)
 */
long double round_exponent(long double val, int prsn){
    int num, i;
    long double point;
    int array[prsn + 1];
    int k;

    num = (int)val;
    point = val - num;
    i = 0;
    k = prsn + 1;
    //convert float to int and store in a buffer@array
    while (i < k){
	point = point - (int)point;
	point = point / 0.1;
	array[i] = (int)point;
	i += 1;
    }
    i -= 1;
    //precision
    while (i >= prsn){
	if (prsn > 9)
	    break;
	if (array[i] < 5){
	    array[i - 1] += 0;
	}
	if (array[i] >= 5){
	    array[i - 1] += 1;
	}
	i -= 1;
    }
    //convert precised buff to float & return
    int j = 0, p = 0;
    double f = 1;
    long long valt = 0;
    while (!array[p]){
	f *= 0.1; //stores zero in front of point
	p++;
    }//prsn + 1 to prevent precision loss
    while (j < prsn + 1){
	valt = valt * 10 + array[j];
	j += 1;
    }
    long double store = valt;
    while ((int)store)
	store = store / (double)10;
    if (f != 0)
	store *= f;
    return (long double)(num + store);
}
/** float_precision - print float +with precision
 * @x: integer part of val
 * @p: float part of val
 * @mem: character buff that stores char float (malloc)
 */
void float_precision(double val, int prsn){
    int i, x, y, temp;
    double p;
    char *mem;
    mem = (char*)malloc(1024);
    //if no precision print float 0 dec places
    if (prsn == 0){
	val += 0.5;
	val = (int)val;
    }
    x = (int)val;
    p = val - x;

    //convert int part to string
    i = 0;
    if (x){
	while (x){
	    mem[i] = (x % 10) + '0';
	    i = i + 1;
	    x = x / 10;
	}
	//reverse array
	int sht = (i) / 2, length = i - 1;
	char tmp;
	int j = 0;
	while (j < sht){
	    tmp = mem[length];
	    mem[length] = mem[j];
	    mem[j] = tmp;
	    j++;
	    length--;
	}
    }
    else{
	mem[i] = '0';
	i++;
    }
    if (prsn != 0){
	mem[i] = '.';
	i += 1;
    }
    //converts float to character & stored in @mem
    while (prsn > 0){
	p = p / (0.1);
	mem[i] = (int)p + '0';
	p = p - (int)p;
	i += 1;
	prsn -= 1;
    }
    mem[i] = '\0';
    write(1, mem, i);
    free(mem);
}
void long_double(long double val, int prsn){
    int i, x, y, temp;
    long double p;
    char *mem;
    mem = (char*)malloc(1024);
    //if no precision print val in  0 dec places
    if (prsn == 0){
	val += 0.5;
	val = (int)val;
    }
    if (prsn && prsn < 10){
	val = round_exponent(val, prsn);
    }
    x = (int)val;
    p = val - x;
    //convert int part to string
    i = 0;
    if (x){
	while (x){
	    mem[i] = (x % 10) + '0';
	    i = i + 1;
	    x = x / 10;
	}
	//reverse array
	int sht = (i) / 2, length = i - 1;
	char tmp;
	int j = 0;
	while (j < sht){
	    tmp = mem[length];
	    mem[length] = mem[j];
	    mem[j] = tmp;
	    j++;
	    length--;
	}
    }
    else{
	mem[i] = '0';
	i++;
    }
    if (prsn != 0){
	mem[i] = '.';
	i += 1;
    }
    //converts float to character & stored in @mem
    while (prsn > 0){
	p = p - (int)p;
	p = p / 0.1 + DBL_EPSILON;
	mem[i] = (int)p + 48;
	i += 1;
	prsn -= 1;
    }
    mem[i] = '\0';
    write(1, mem, i);
    free(mem);
}
