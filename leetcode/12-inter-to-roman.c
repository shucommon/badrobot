#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
*/
char * itr(int n, char a, char b, char c)
{
	char *ret = (char *)malloc(sizeof(char) * 5);
	if(n < 4) {
		ret[n] = '\0';
		while(n--)
			ret[n] = a;
	} else if(n == 4) {
		ret[0] = a;
		ret[1] = b;
		ret[2] = '\0';
	} else if(n < 9) {
		n -= 4;
		ret[n] = '\0';
		ret[0] = b;
		while(n-- > 1)
			ret[n] = a;
	} else {
		ret[0] = a;
		ret[1] = c;
		ret[2] = '\0';
	}
	return ret;
}

char * intToRoman_t(int num){
	char *ret = (char *)malloc(sizeof(char *) * 16);
	memset(ret, 0, 16);
	if(num / 1000) {
		char *tmp = itr(num/1000, 'M', 'z', 'z');
		strcat(ret, tmp);
		free(tmp);
	}
	num %= 1000;
	if(num / 100) {
		char *tmp = itr(num/100, 'C', 'D', 'M');
		strcat(ret, tmp);
		free(tmp);
	}
	num %= 100;
	if(num / 10) {
		char *tmp = itr(num/10, 'X', 'L', 'C');
		strcat(ret, tmp);
		free(tmp);
	}
	num %= 10;
	if(num) {
		char *tmp = itr(num, 'I', 'V', 'X');
		strcat(ret, tmp);
		free(tmp);
	}
	return ret;
}

/*
字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
*/
char * intToRoman(int num){
	int nums[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
	char str[13][3] = {{"M"}, {"CM"}, {"D"}, {"CD"}, {"C"}, {"XC"}, {"L"}, {"XL"}, {"X"}, {"IX"}, {"V"}, {"IV"}, {"I"}}; 
	char *ret = (char *)malloc(sizeof(char) *16);
	memset(ret, 0, 16);
	for(int i = 0; i < 13; i++) {
		while(num >= nums[i]) {
			num -= nums[i];
			strcat(ret, str[i]);
		}
	}
	return ret;
}

int main()
{
	char *ret = intToRoman(1994);
	printf("%s\n", ret);
	return 0;
}
