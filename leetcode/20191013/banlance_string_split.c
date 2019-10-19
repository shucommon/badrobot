#include <stdio.h>

// RL LLLRRR LR
int balancedStringSplit(char * s){
    int cnt = 0, l = 0, r = 0;
    char *p = s;
    while(*p) {
        if(*p == 'L')
            l++;
        else if(*p == 'R')
            r++;
        if(l == r) {
            cnt++;
            l = 0;
            r = 0;
        }
        p++;
    } 
    return cnt;
}

int main()
{
    return 0;
}
