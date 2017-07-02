#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

typedef int temp_file_handle;

temp_file_handle write_temp_file(char* buffer, size_t length)
{
    char temp_filename[] = "/tmp/temp_file.XXXXXX";
    int fd =  mkstemp(temp_filename);
    printf("fd %d, errno %d string %s\n", fd, errno, strerror(errno));
    // unlink the file immediatel, so that it will be removed when the file descriptor is closed.
    printf("file name %s\n", temp_filename);
    unlink(temp_filename);

    // write the number of bytes to the file first.
    write(fd, &length, sizeof(length));

    write(fd, buffer, length);

    return fd;
}

char* read_temp_file(temp_file_handle temp_file, size_t *length)
{
    char *buffer;
    int fd = temp_file;

    // rewind to the beginning of the file
    lseek(fd, 0, SEEK_SET);

    read(fd, length, sizeof(*length));

    buffer = (char*)malloc(*length);
    read(fd, buffer, *length);
    printf("buffer: %s\n", buffer);
    
    // close the file descriptor, which will cause the temporary file to go away.
    close(fd);
    return buffer;
}

int main()
{
    char *buffer = "Hello World";
    size_t length = 12;
    printf("length %lu\n", length);
    temp_file_handle fd = write_temp_file(buffer, length);

    read_temp_file(fd, &length); 

    return 0;
}

