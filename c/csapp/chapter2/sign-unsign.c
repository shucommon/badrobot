#include <stdio.h>
#include <string.h>

// #define size_t unsigned int
// size_t strlen(const char *s);

int strlonger(char *s, char *t) {
    // buggy, unsign compare with sign, compile will change sign value to unsigned, then do compare
    //return strlen(s) - strlen(t) > 0;
    return strlen(s) > strlen(t);
    
}

int main()
{
    char *s = "ab";
    char *t = "bcd";
    int longer = strlonger(s, t);
    printf("longer %d\n", longer);

    return 0;
}
