#include <stdio.h>

int myAtoi(char * str){
    long long a = 0;
    int sign = 1;
    while(*str == ' ')
        str++;
    if(*str != '+' && *str != '-' && (*str < '0' || *str > '9'))
        return 0;
    if(*str == '-') {
        sign = -1;
        str++;
    } else if(*str == '+') {
        str++;
    }
	while(*str >= '0' && *str <= '9') {
		int b = *str - '0';
		a = a * 10 + b;
		if(a > (2^31-1))
			break;
		str++;
	}
    a *= sign;
    if(a > (2^31-1))
        return 2^31 - 1;
    if(a < (-2^31))
        return -2^31;
    return (int)a;
}

int main()
{
    char *str = "  -42";
    int a = myAtoi(str);
    printf("a %d\n", a);

    return 0;
}
