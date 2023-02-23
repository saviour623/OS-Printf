#include <stdio.h>
#include <float.h>
#include <stdlib.h>
void expon(double val);
void expon(double val){
//exponent and precision
	int count = 0;
	const double perm = val; //stores val for adverse use.

//include float.h. 1 - dbl_epsilon gives us the biggest double between 0 and 1 e.g 0.99………

	double size_dbl = 1 - DBL_EPSILON;

	printf("%f\n", val);

//place decimal between first two integers and count exponent. e.g 1.2………if val is greater than 0 and when it's less than 0

	if (val == 0.0){
		printf("yes\n");
		printf("0.0e+00\n");
		exit(0);
	}
       
	if (val > size_dbl){
		printf("%e\n", size_dbl);
		while(val){
			int temp = val /10;
			if (temp == 0)
				break;
			val = val / 10;
			count += 1;
		}
	}

	else{
		if (val <= size_dbl){
			while (!val || val){
				if ((val * 10)  > 10)
					break;
				val *= 10;
				count += 1;
			}
		}
	}

//precision and print exponential
	char *str = perm <= size_dbl ? "e-" : "e+";

/**if (prsn != 0)
   double store =  round_exponent(val, prsn);
   print store, str
   if (count > 0 && count < 9)
   print 0 and count.
   else print count
*/
	printf("%f%s", val, str);
	if (count > 0 && count < 9)
		printf("%d%d\n", 0, count);
	else printf("%d\n", count);
}

int main(){
	double y = 234.56;
	expon(y);
	return 0;
}
