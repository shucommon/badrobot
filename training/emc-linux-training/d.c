#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#define RTLD_NEXT ((void*)-1)

typedef size_t (*read_fun)(int fd, void *buf, size_t count);
read_fun real_read = NULL;

size_t read(int fd, void *buf, size_t count)
{
    if(real_read == NULL)
    {
        printf("Failed to find real read\n");
        return -1;
    }
    else
    {
        printf("hooking\n");
        size_t rt = real_read(fd, buf, count);
        memset(buf, 'X', rt);
    }
}

__attribute((constructor)) void _init()
{
    real_read = (read_fun)dlsym(RTLD_NEXT, "read");
}


__attribute((destructor)) void _fini()
{
    printf("bye\n");
}

