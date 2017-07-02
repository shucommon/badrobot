#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static int alloc_size;
static char* memory;

void segv_handler(int signal_number)
{
    printf("memory accessed!\n");
    mprotect(memory, alloc_size, PROT_READ | PROT_WRITE);
}

int main()
{
    int fd;
    struct sigaction sa;

    // install segv_handler as the handler for SIGSEGV
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &segv_handler;
    sigaction(SIGSEGV, &sa, NULL);

    // allocate one page of memroy by mapping /dev/zero. map the momory as write-only, initally
    alloc_size = getpagesize();
    fd = open("/dev/zero", O_RDONLY);
    memory = mmap(NULL, alloc_size, PROT_WRITE, MAP_PRIVATE, fd, 0);
    close(fd);

    // write to the page to obtain a private copy
    memory[0] = 0;

    // make the memory unwritable
    mprotect(memory, alloc_size, PROT_NONE);

    // write to the allocated memroy region
    memory[0] = 1;

    // all done, unmap the memory
    printf("all done\n");
    munmap(memory, alloc_size);
    return 0;
}

