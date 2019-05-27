#include <stdio.h>
#include <limits.h>
#include <string.h>


/* wrong, duplicate
void test_same_name_parm(int a)
{
    int a = a;
    printf("a %d\n", a);
}
*/

void test_register_a(int b)
{
    register int *a = &b;
    printf("add b %p, a %p\n", (void*)&b, a);
    printf("test register %d\n", *a);
}

/* can't get register val addr
void test_register(register int b)
{
    int *a = &b;
}
*/

int main()
{
    unsigned long max = 1;
    //unsigned long long max = ULLONG_MAX;
    printf("scha %d, %d, %u\n", SCHAR_MIN, SCHAR_MAX, UCHAR_MAX);
    printf("char %d, %d, %d\n", CHAR_BIT, CHAR_MIN, CHAR_MAX);
    printf("int  %d, %d, %u\n", INT_MIN, INT_MAX, UINT_MAX);
    printf("hrt  %d, %d, %u\n", SHRT_MIN, SHRT_MAX, USHRT_MAX);
    printf("long %ld, %ld, %lu\n", LONG_MIN, LONG_MAX, ULONG_MAX);
    printf("ll   %lld, %lld, %llu\n", LLONG_MIN, LLONG_MAX, ULLONG_MAX);


    int i = 0;
    for(int i = 0; i < 8; i++){
        printf("%d max %lu\n", i, max);
        max *= (unsigned long)256;
        printf("[%d] max %lu\n", i, max);
    }
    printf("3 max %lu\n", max-1);

    printf("2.1e-2 %f\n", 2.1e-2);
    printf("037 %d\n", 037);

    printf("a\aa");
    printf("b\bb");
    printf("c\fc");
    printf("d\nd");
    printf("e\re");
    printf("f\tf");
    printf("g\vg");
    printf("\\");
    printf("\?");
    printf("\'");
    printf("\"");
    printf("\n");

    char *a = "abcde\bfg";
    printf("strlen a %lu\n", strlen(a));
    while(*a) {
        putchar(*a++);
    }

    int b = 2;
    printf("b addr %p\n", (void*)&b);
    test_register_a(b);


    int c[10] = {1};
    int d[10] = {2};
    printf("addr c[-1] %p, c[0] %p, c[9] %p, d[-1] %p, d[0] %p, d[9] %p\n", (void*)(c-1), (void*)c, (void*)(c+9), (void*)(d-1), (void*)d, (void*)(d+9));
    printf("c[9] %d, d[-1] %d\n", c[9], d[-1]);
    printf("compare c[0] > d[0] : %d\n", (int)(c > d));


    return 0;

}
