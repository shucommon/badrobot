#include <stdio.h>

void a(int *a[])
{
    printf("addr a %p, addr a[0] %p, *a %p, *(a+1) %p, *a[0] %d\n", a, a[0], *a, *(a+1), *a[0]);
}

int main()
{
    int *e[10];
    int g[10] = {1,2,3,4,5,6,7,8,9,10};

    for(int i = 0; i < 10; i++)
    {
        e[i] = &g[i];
        printf("e[%d] addr %p\n", i, e[i]);
        printf("e%d addr %p\n", i, e+i);
        printf("e%d val %p\n", i, *(e+i));
    }

    a(e);

//    int (*a)[4] = { {1,2,3,4}, {5,6,7,8}} ;
    int b[2][4] = { {1,2,3,4}, {5,6,7,8}} ;
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            printf("b[%d][%d] %d, addr %p\n",i, j, b[i][j], &b[i][j]);
            printf("b[%d][%d] %p, addr %p\n",i, j, b, b[i]);
        }
    }

    return 0;
}
