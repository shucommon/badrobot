#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    long max = atoi(argv[1]);
    int number;
    unsigned position;
    volatile unsigned result;

    for(number = 1; number <= max; number++)
    {
        // compute the position of the most significant set bit using the bsrl assembly instruction
        __asm__("bsrl %1, %0" : "=r" (position) : "r" (number));
        result = position;
    }

    return 0;
}
