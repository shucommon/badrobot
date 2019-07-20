#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * defangIPaddr(char * address){
    char * ret = (char*)malloc(strlen(address) + 7);
    char *p = address, *q = ret;
    while(*p != '\0') {
        if(*p == '.') {
            *q++ = '[';
            *q++ = '.';
            *q++ = ']';
        }
        else {
            *q++ = *p;
        }
        p++;
    }
    *q = *p;
    return ret;
}

int main()
{
    char *a = defangIPaddr("10.10.10.111");
    printf("%s\n", a);
    return 0;
}
