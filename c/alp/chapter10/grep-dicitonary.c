#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int grep_for_word(const char* word)
{
    size_t length;
    char* buffer;
    int exit_code;

    length = strlen("grep -x ") + strlen(word) + strlen(" /usr/share/dict/words") + 1;
    buffer = (char*)malloc(length);
    sprintf(buffer, "grep -x %s /usr/share/dict/words", word);

    exit_code = system(buffer);
    free(buffer);
    return exit_code;
}

int main(int argc, char* argv[])
{
    char* word = argv[1];
    int rval = grep_for_word(word);
    if(rval == 0)
    {
        printf("find word %s\n", word);
    }
    else
    {
        printf("not find word %s\n", word);
    }
    return 0;
}

