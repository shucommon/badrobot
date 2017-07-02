#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    char *file = argv[1];
    int fd;
    struct flock lock;

    printf("open %s\n", file);
    fd = open(file, O_WRONLY);
    printf("locking\n");
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;
    // place a write lock on the file
    fcntl(fd, F_SETLKW, &lock);
    printf("locked, hit enter to unlock...");
    // wait for user to hit enter
    getchar();

    printf("unlocking...\n");
    // release the lock
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);

    close(fd);
    return 0;
}

