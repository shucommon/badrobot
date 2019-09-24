#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>      // flags for read and write
#include <sys/stat.h>   // structure returned by stat

void p_dir(char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr, "Can't open directory %s\n", dir);
        return;
    }

    chdir(dir);
    while((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name, &statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            if(strcmp(entry->d_name, ".") == 0
            || strcmp(entry->d_name, "..") == 0)
                continue;
            printf("%*s%s/\n", depth, "", entry->d_name);
            p_dir(entry->d_name, depth+4);
        } else
            printf("%*s%s\n", depth, "", entry->d_name);
    }
    chdir("..");
    closedir(dp);
}

int main(int argc, char *argv[])
{
    char *topdir = ".";
    if(argc >= 2)
        topdir = argv[1];

    printf("Directory scan of %s\n", topdir);
    p_dir(topdir, 0);

    return 0;
}
