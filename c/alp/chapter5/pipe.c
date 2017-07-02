#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// write COUNT copies of MESSAGE to STREAM
void writer(const char* message, int count, FILE* stream)
{
    for(; count > 0; count--)
    {
        // write the message to the stream, and send it off immediately
        fprintf(stream, "%s\n", message);
        fflush(stream);
        // snooze a while
        sleep(1);
    }
}

// read random strings from the stream as long as possible
void reader(FILE* stream)
{
    char buffer[1024];
    // read until we hit the end of the stream. fgets reads until either a newline or the end of file
    while(!feof(stream) && !ferror(stream) && fgets(buffer, sizeof(buffer), stream) != NULL)
    {
        fputs(buffer, stdout);
    }
}

int main()
{
    int fd[2];
    pid_t pid;

    // create a pipe.
    pipe(fd);

    // fork a child process
    pid = fork();
    if(pid == (pid_t)0)
    {
        FILE* stream;
        // child process, close our copy of the write end of the file descriptor
        close(fd[1]);
        // convert the read file descriptor to a FILE object, and read from it
        stream = fdopen(fd[0], "r");
        reader(stream);
        close(fd[0]);
    }
    else
    {
        // parent process
        FILE* stream;
        // close our copy of the read end of the file descriptor
        close(fd[0]);
        // convert the write file descriptor to a FILE object, and write to it
        stream = fdopen(fd[1], "w");
        writer("Hello world.", 5, stream);
        close(fd[1]);
    }

    return 0;
}

