#include <mcheck.h>

__attribute((constructor)) void _init()
{
    mtrace();
}


__attribute((destructor)) void _fini()
{
}

