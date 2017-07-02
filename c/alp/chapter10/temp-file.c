#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

/*
 * Returns the file descriptor for a newly created temporary file.
 * The temporary file will be readable and writable by the effective
 * user ID of the current process but will not be readable or
 * writable by anybody else.
 * Returns -1 if the temporary file could not be created. 
 */

int secure_temp_file()
{
    /* This file descriptor points to /dev/random and allows us to get
     * a good source of random bits. */
    static int random_fd = -1;
    unsigned int random;
    /* A buffer, used to convert from a numeric to a string
     * representation of random. This buffer has fixed size, meaning
     * that we potentially have a buffer overrun bug if the integers on
     * this machine have a *lot* of bits. */
    char filename[128];
    /* The file descriptor for the new temporary file. */
    int fd;
    /* Information about the newly created file. */
    struct stat stat_buf;

    /* If we haven’t already opened /dev/random, do so now. (This is
     * not threadsafe.) */
    if(random_fd == -1)
    {
        /* Open /dev/random. Note that we’re assuming that /dev/random
         * really is a source of random bits, not a file full of zeros
         * placed there by an attacker. */
        random_fd = open("/dev/random", O_RDONLY);
        if(random_fd == -1)
        {
            printf("1\n");
            return -1;
        }
    }

    // read an integer from /dev/random
    if(read(random_fd, &random, sizeof(random)) != sizeof(random))
    {
        printf("2\n");
        return -1;
    }
    sprintf(filename, "/tmp/%u", random);
    // try to open the file
    fd = open(filename,
            /* Use O_EXECL, even though it doesn’t work under NFS. */
            O_RDWR | O_CREAT | O_EXCL,
            /* Make sure nobody else can read or write the file. */
            S_IRUSR | S_IWUSR);
    if(fd == -1)
    {
        printf("3\n");
        return -1;
    }

    /* Call lstat on the file, to make sure that it is not a symbolic
     * link. */
    if(lstat(filename, &stat_buf) == -1)
    {
        printf("4\n");
        return -1;
    }
    /* If the file is not a regular file, someone has tried to trick
     * us. */
    if(!S_ISREG(stat_buf.st_mode))
    {
        printf("5\n");
        return -1;
    }
    /* If we don’t own the file, someone else might remove it, read it,
     * or change it while we’re looking at it. */
    if(stat_buf.st_uid != geteuid() || stat_buf.st_gid != getegid())
    {
        printf("6\n");
        return -1;
    }
    /* If there are any more permission bits set on the file,
     * something’s fishy. */
    if((stat_buf.st_mode & ~(S_IRUSR | S_IWUSR)) != 0)
    {
        printf("7, st_mode = %x, r = %x, w = %x, S_ISUID = %d, S_IRWXU %d\n", stat_buf.st_mode, S_IRUSR, S_IWUSR, S_ISUID, S_IRWXU);
        return -1;
    }
    return fd;
}

int main()
{
    int fd = secure_temp_file();
    if(fd != -1)
    {
        printf("create file success, now close it\n");
        close(fd);
    }
}
