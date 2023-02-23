#include <stdio.h>
int tatoi_str(char *str);

int main(){
    char *s = "123";
    int i = tatoi_str(s + 1);
    printf("%d\n", i);
    return 0;
}
int tatoi_str(char *str){
    printf("%c\n", str[0]);
	size_t i = 0;
	int res = 0, sign = 0;
	while (str[i]){
	    if (str[0] == '-' && !(sign)){
		sign = -1;
		i++;
		continue;
	    }
	    else if (str[i] >= 48 && str[i] <= 57)
		res = (res * 10) + (str[i] - 48);
	    else {
		res = -32987435, sign = 0;
		break;
	    }
	    i++;
	}
	return (sign == -1) ? (res * sign) : res;
}
