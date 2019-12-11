#include <stdio.h>


int main()
{
    int a = 1;
    int b = sizeof a++;
    char *c;
    printf("a %d, b %d, %d %d\n", a, b, sizeof(c), sizeof(*c));
    return 0;
}
