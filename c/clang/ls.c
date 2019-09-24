/*
Let us begin with a short review of UNIX file system structure. A directory is a file that contains
a list of filenames and some indication of where they are located. The “location” is an index into
another table called the “inode list.” The inode for a file is where all information about a file
except its name is kept. A directory entry generally consists of only two items, the filename and an inode number.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>      // flags for read and write
#include <sys/types.h>  // typedefs
#include <sys/stat.h>   // structure returned by stat
#include <sys/dir.h>    // local directory structure
#include "dirent.h"

// fsize : print size of file "name"
void fsize(char *name)
{
    struct stat stbuf;

    if(stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }

    if((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, fsize);

    printf("%8lld %s\n", stbuf.st_size, name);
}

// dirwalk: apply fcn to all files in dir
void dirwalk(char *dir, void(*fcn)(char *))
{
    char name[MAX_PATH];
    Dirent *dp;
    DIR_t *dfd;

    fprintf(stderr, "dirwalk: %s\n", dir);
    if((dfd = opendir_t(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }

    while((dp = readdir_t(dfd)) != NULL) {
        if(strcmp(dp->name, ".") == 0
            || strcmp(dp->name, "..") == 0)
            continue;   // skip self and parent

        if(strlen(dir) + strlen(dp->name) + 2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->name);
        else {
            sprintf(name, "%s/%s", dir, dp->name);
            fprintf(stderr, "dirwalk: name %s/%s\n", dir, dp->name);
            (*fcn)(name);
        }
    }

    closedir_t(dfd);
}

// opendir: open a directory for readdir calls
DIR_t *opendir_t(char * dirname)
{
    int fd;
    struct stat stbuf;
    DIR_t *dp;

    if((fd = open(dirname, O_RDONLY, 0)) == -1
        || fstat(fd, &stbuf) == -1
        || (stbuf.st_mode & S_IFMT) != S_IFDIR
        || (dp = (DIR_t *)malloc(sizeof(DIR_t))) == NULL)
        return NULL;

    dp->fd = fd;
    return dp;
}

// closedir: close directory opened by opendir
void closedir_t(DIR_t *dp)
{
    if(dp) {
        close(dp->fd);
        free(dp);
    }
}

// readdir: read directory entries in sequence
Dirent *readdir_t(DIR_t *dp)
{
    struct dirent dirbuf;   // local directory structure
    static Dirent d;        // return: portable structure

    fprintf(stderr, "readdir: fd %u\n", dp->fd);
        
    //int ret = read(dp->fd, (char *)&dirbuf, sizeof(dirbuf));
    //fprintf(stderr, "readdir: ret %u, dirbuf %lu\n", ret, sizeof(dirbuf));
    while(read(dp->fd, (char *)&dirbuf, sizeof(dirbuf))
            == sizeof(dirbuf)) {
        fprintf(stderr, "readdir: ino %llu\n", dirbuf.d_ino);
        if(dirbuf.d_ino == 0)   // slot not in use
            continue;
        d.ino = dirbuf.d_ino;
        strncpy(d.name, dirbuf.d_name, DIRSIZ);
        d.name[DIRSIZ] = '\0';  // ensure termination
        fprintf(stderr, "readdir: name %s\n", d.name);
        return &d;
    }
    return NULL;
}

// print file sizes
int main(int argc, char **argv)
{
    if(argc == 1)   // default: current directory
        fsize(".");
    else
        while(--argc > 0)
            fsize(*++argv);

    return 0;
}

