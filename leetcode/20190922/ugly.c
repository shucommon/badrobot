/*
*/
#include <stdio.h>
//#include <math.h>
#include <stdlib.h>
#define MIN(a, b) (a > b ? b:a)
#define MAX(a, b) (a > b ? a:b)
int nthUglyNumber(int n, int a, int b, int c){
    int i = 1, cnt = 0;
    int a1 = MIN(MIN(a,b),c);
    int c1 = MAX(MAX(a,b),c);
    int tmp = (a == a1 ? b:a);
    int b1 = (tmp == c1 ? c:tmp);
        
    i = b;
    while(cnt < n) {
        if(i/a >= n)
            return n * a;
        cnt += i/a;
        if(cnt + 1 == n)
            return i;
        cnt += 1;
       
        i = c;
        if(i/a + i/b >= n)
        
    }
    return i-1;
}

int main()
{

    return 0;
}
