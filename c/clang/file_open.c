#include <fcntl.h>

int fd;
/*
flags:
    O_RDONLY	open for reading only
    O_WRONLY	open for writing only
    O_RDWR	open for both reading and writing
The perms argument is always zero for the uses of open that we will discuss.
*/
int open(char *name, int flags, int perms);

fd = open(name, flags, perms);

/*
It is an error to try to open a file that does not exist. The system call creat is provided to create new files, or to re-write old ones.
*/
int creat(char *name, int perms);
fd = creat(name, perms);
