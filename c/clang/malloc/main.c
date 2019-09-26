#include "malloc.h"

int main()
{
    char *test;
    test = (char *)malloc_t(sizeof(char) * 1024 * 2);
    test = (char *)malloc_t(sizeof(char) * 1024 *14);

    test = (char *)malloc_t(sizeof(char) * 1024 * 16);

    return 0;
}
