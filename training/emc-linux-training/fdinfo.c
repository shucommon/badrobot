//  Create a simple program that reads from a file one byte at a time:
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
 
int main (int argc , char **argv)
{
        int fd = open (argv[1], O_RDONLY);
        while (1){
                char c;
                read(fd,&c,1);
                sleep(1);
        }
}
