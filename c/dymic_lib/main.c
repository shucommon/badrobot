#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#define LIB_PATH "./lib.so"

// function pointer
typedef int (*func)(int, int);


int main()
{
    void *hdl;
    char *error;
    func cac_func = NULL;

    // open so
    hdl = dlopen(LIB_PATH, RTLD_LAZY);
    if(!hdl) {
        printf("%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    // clear previous errors
    dlerror();

    // get one function
    cac_func = (func)dlsym(hdl, "add");
    if((error = dlerror()) != NULL) {
        printf("%s\n", error);
        exit(EXIT_FAILURE);
    }
    printf("add(1, 1): %d\n", (*cac_func)(1, 1));

    cac_func = (func)dlsym(hdl, "sub");
    if((error = dlerror()) != NULL) {
        printf("%s\n", error);
        exit(EXIT_FAILURE);
    }
    printf("sub(1, 1): %d\n", (*cac_func)(1, 1));


    dlclose(hdl);

    return 0;
}
