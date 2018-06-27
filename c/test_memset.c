#include<stdio.h>
#include<string.h>

void tx()
{
    char buf[8*1024*1024];
    memset(buf, 0, sizeof(buf));
}

int main()
{
    tx();
    return 0;
}
