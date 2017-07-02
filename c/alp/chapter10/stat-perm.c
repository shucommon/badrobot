#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
    const char* const file_name  = argv[1];
    struct stat buf;

    stat(file_name, &buf);
    // if file's owner can wirte to it, print  a message
    if(buf.st_mode & S_IWUSR) 
    {
        printf("owning user can wirte '%s' .\n", file_name);
    }
    return 0;
}

