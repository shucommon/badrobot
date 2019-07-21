#include "defs.h"

extern void command();

int main()
{
    printf("this is main, below is called from main:\n");

    kbd();
    display();
    insert();
    search();
    file();
    utils();
    command();

    return 0;
}
