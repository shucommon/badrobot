#include <stdio.h>
#include <time.h>

int count(int in)
{
    int cnt = 0, tmp;
    while((tmp = in & (~in + 1))) {
        cnt++;
        in &= ~tmp; 
    }
    return cnt;
}

int count_slow(int in)
{
    int cnt = 0, tmp;
    while(in) {
        if(in % 2 == 1)
            cnt++;
        in /= 2;
    }
    return cnt;
}

int main()
{
    int x;
    scanf("%d", &x);

    int cnt = count(x);
    printf("cnt %d\n", cnt);

    //int cnt = count_slow(x);
    //printf("cnt %d\n", cnt);

    return 0;
}
