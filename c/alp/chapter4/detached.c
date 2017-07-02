#include <pthread.h>
#include <stdio.h>

void* myfuc(void* parm)
{
    int * par = (int*)parm; 
    printf("thread id = %d, pid = %d, parm = %d\n", pthread_self(), (int)getpid(), *par);
    return NULL;
}

int main()
{
    pthread_t thread_id;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    int ret;
    int parm = 1;
    // create a new thread
    pthread_create(&thread_id, &attr, &myfuc, &parm);
    pthread_attr_destroy(&attr);

    return 0;
}
