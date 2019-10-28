#include <stdio.h>

int main()
{
    // avoid below style
    int i = 1, j =2, m =2;
    if(i == 0)
        if(j == 1)
            printf("j==1\n");
        else
            printf("j!=1\n");
    else
        printf("i != 0\n");

    return 0;
}
