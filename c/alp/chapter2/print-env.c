#include <stdio.h>
#include <stdlib.h>
// the environ variable contains the environment
extern char **environ;

int main()
{
    char **var;
    char * home_name = getenv("HOME");
    printf("HOME: %s\n", home_name);
    for(var = environ; *var != NULL; ++var)
        printf("%s\n", *var);
    return 0;
}
