#include <stdio.h>

int main()
{
#ifdef TEST
    printf("test\n");
#elif TEST_ELSE
    printf("test else\n");
#else
    printf("else\n");
#endif

    return 0;
}
