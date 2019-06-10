#include <stdio.h>

//int const a = 1;
int a = 1;
void init(void)
{
    // val for *tmp is const
    void const *tmp;
    tmp = (void const *)&a;

    // pointer tmp is const
    //void * const tmp;
    //tmp = (void const *)&a;  // will generated error

    printf("ori a %d\n", a);

    a = 2;
    printf("now a %d\n", a);
   
    // error, const can't be assigned 
    //*tmp = 3;
    //printf("now a %d\n", a);
}

int main()
{
    init();
    return 0;
}
