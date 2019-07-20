#include <stdio.h>

int main()
{
    char in[21];
    char *p;

    while(scanf("%s", in) != EOF) {
        int table['z' + 1] = {0};
        p = in;
        char cnt = 20;
        while(*p != '\0')
            table[*p++]++;

        p = in;
        while(*p != '\0') {
            if(table[*p] < cnt)
                cnt = table[*p];
            p++;
        }

        p = in;
        int i = 0;
        while(*p != '\0') {
            if(table[*p] == cnt) {
                p++;
                continue;
            }
            in[i++] = *p;
            p++;
        }
        in[i] = '\0';
        printf("%s\n", in);
    }

    return 0;
}
