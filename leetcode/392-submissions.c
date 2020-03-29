#include <stdio.h>
#include <stdbool.h>

bool isSubsequence(char * s, char * t){
    while(s) {
        while(*s != *t++ && *t != '\0') {
            printf("%c != %c\n", *s, *(t-1));
        }
        if(*t == '\0') {
            if(*(t-1) == *s)
                s++;
            break;
        }
        printf("%c ====\n", *s);
        s++;
    }
    if(*s == '\0')
        return true;
    return false;
}

int main()
{
    char *s = "abc";
    char *t = "ahbgdc";
    //char *s = "axc";
    //char *t = "ahbgdc";
    bool issub = isSubsequence(s, t);
    printf("%d\n", issub);

    return 0;
}
