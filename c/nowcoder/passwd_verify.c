/*
1.长度超过8位
2.包括大小写字母.数字.其它符号,以上四种至少三种
3.不能有相同长度超2的子串重复
输入描述:
一组或多组长度超过2的子符串。每组占一行

输出描述:
如果符合要求输出：OK，否则输出NG
*/


#include <stdio.h>
#include <string.h>

int validate(char *in)
{
    int len = 0;
    int a = 0, b = 0, c = 0, d = 0;
    char *p = in;

    if((len = strlen(in)) < 9)
        return 0;
    
    while(*p != '\0') {
        if(*p >= '0' && *p <= '9')
            a = 1;
        else if(*p >= 'a' && *p <= 'z')
            b = 1;
        else if(*p >= 'A' && *p <= 'Z')
            c = 1;
        else
            d = 1;
        p++;
    }
    if(a + b + c + d < 3)
        return 0;

    for(int i = 0; i < len - 3; i++)    
    {
        for(int j = i+1; j < len - 2; j++)
            if(strncmp(in+i, in+j, 3) == 0)
                return 0;
    }
    return 1;
}

int main()
{
    char in[128];
    while(scanf("%s", in) != EOF) {
        if(validate(in))
            printf("OK\n");
        else
            printf("NG\n");
    }
}
