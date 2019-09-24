#include <stdio.h>

#define ALLOCSIZE 10000     // size of available space

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

// return pointer to n characters
char *alloc(int n)
{
    if(allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else
        return NULL;
}

// free storage pointer to by p
void afree(char *p)
{
    if(p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}
