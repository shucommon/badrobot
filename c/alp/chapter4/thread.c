#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* myfuc(void* parm)
{
    int * par = (int*)parm; 
    printf("thread id = %lx, pid = %d, parm = %d\n", pthread_self(), (int)getpid(), *par);
    return NULL;
}

int main()
{
    pthread_t thread_id;
    int ret;
    int parm = 1;
    // create a new thread
    pthread_create(&thread_id, NULL, &myfuc, &parm);

    pthread_join(thread_id, (void*)&ret); 
    printf("ret = %d, thread_id = %d\n", ret, (int)thread_id);

    return 0;
}
