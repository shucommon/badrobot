#include <stdio.h>

int main()
{
    FILE *fp = fopen("text", "r");
    int a, b;
    while(fscanf(fp, "%d / %d", &a, &b) != EOF)
        printf("%d / %d\n", a, b);
    return 0;
}
