#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main ()
{
    for (;;) {
        char *c = (char *) malloc (16 *1024*1024);
        if (c)
        {
            memset(c, 'a', 16*1024*1024);
        }
        sleep(1);
    }
}
