#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void f()
{
    char c[1024*10];
}

int main(int argc, char ** argv)
{
    int j = 0;
    char c[10];
    strcpy(c, argv[1]);
    printf("address of c if %p, j = %d\n", &c[0], j);
    f();
}
