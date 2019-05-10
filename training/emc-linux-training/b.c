#include <stdio.h>

#ifdef DEBUG
    #define dprintf printf
#else
    #define dprintf(...)
#endif

void main()
{
    printf("hello\n");
    dprintf("hello from debug\n");

};
