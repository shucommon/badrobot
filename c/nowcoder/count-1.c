#include <stdio.h>

int count(int n)
{
    int tmp;
    int cnt = 0;
    while((tmp = n & (~n + 1)))
    {
        cnt++;
        n &= ~tmp;
    }
    return cnt;
}

int main()
{
    int n;
    scanf("%d", &n);
    printf("%d\n", count(n));

    return 0;
}
