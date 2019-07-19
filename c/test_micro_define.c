#include <stdio.h>

typedef struct {
    int a;
    int b;
    char *name;
} micro_test; 

#define begin static const micro_test mt_table[] = {
#define end { ~0, 0, ""} };
#define test(name, a, b)  {a, b, #name},

int main()
{
    begin
    test(TEST1, 1, 1)
    test(TEST2, 2, 2)
    test(TEST3, 3, 3)
    end

    printf("mt table 0 name %s, a %d, b %d\n", mt_table[0].name, mt_table[0].a, mt_table[0].b);
    printf("mt table 1 name %s, a %d, b %d\n", mt_table[1].name, mt_table[1].a, mt_table[1].b);
    printf("mt table 2 name %s, a %d, b %d\n", mt_table[2].name, mt_table[2].a, mt_table[2].b);
    
    return 0;
}
