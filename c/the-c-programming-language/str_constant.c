#include <stdio.h>

int main()
{
    char *p = "hello world";
    printf("%s\n", p);

    // wrong, can't change string constant
/*
    p[1] = 'E';
    printf("%s\n", p);
*/
    
    char a[] = "hello world";
    printf("%s\n", a);
    a[1] = 'E';
    printf("%s\n", a);
   
    p = a; 
    p[2] = 'L';
    printf("%s\n", p);
    
    printf("*++p %c\n", *++p);

    return 0;
}
