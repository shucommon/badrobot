#include <stdio.h>


int main()
{
    printf("sizeof int %lu\n", sizeof(int)); 
    printf("sizeof int* %lu\n", sizeof(int *)); 
    printf("sizeof double %lu\n", sizeof(double)); 
    printf("sizeof long %lu\n", sizeof(long)); 
    printf("sizeof long double %lu\n", sizeof(long double)); 

    //#pragma pack(4)
    typedef struct {
        char a;
        int b;
    } sizeof_test;

    typedef struct {
        char a;
        int b;
    } __attribute__((__packed__)) sizeof_test_pack;
    
    sizeof_test st[2];
    printf("sizeof struct %lu\n", sizeof(sizeof_test));
    printf("sizeof struct st %lu %lu\n", sizeof st, sizeof(st));
 
    sizeof_test_pack stp[2];
    printf("sizeof struct %lu\n", sizeof(sizeof_test_pack));
    printf("sizeof struct st %lu %lu\n", sizeof stp, sizeof(stp));

    return 0;
}
