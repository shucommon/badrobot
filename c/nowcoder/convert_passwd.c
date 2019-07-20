#include <stdio.h>

int main()
{
    int table['v' + 1];
    char in[101];
    char *p;

    table['s'] = '7';
    table['t'] = '8';
    table['u'] = '8';
    table['v'] = '8';

    while(scanf("%s", in) != EOF)
    {
        p = in;
        while(*p != '\0') {
            if(*p >= 'A' && *p <= 'Z') {
                if(*p == 'Z')
                    *p = 'a';
                else
                    *p = 'a' + *p - 'A' + 1;
            } else if ( *p >= 'a' && *p <= 'z') {
                if(*p <= 'r')
                    *p = (*p-'a')/3 + '2';
                else if(*p <= 'v')
                    *p = table[*p];
                else
                    *p = '9';
            }
            p++;
        }
        printf("%s\n", in);
    }
}
