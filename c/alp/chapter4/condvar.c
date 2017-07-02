#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

int thread_flag;
pthread_cond_t thread_flag_cv;
pthread_mutex_t thread_flag_mutex;

void initialize_flag(void)
{
    pthread_cond_init(&thread_flag_cv, NULL);
    pthread_mutex_init(&thread_flag_mutex, NULL);
    thread_flag = 0;
}

void do_work()
{
    printf("do work\n");
}

void* thread_function(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&thread_flag_mutex);
        while(!thread_flag)
        {
            // flas is clear, wait for signal on condition value
            pthread_cond_wait(&thread_flag_cv, &thread_flag_mutex);
            // to here, the flag is set
            pthread_mutex_unlock(&thread_flag_mutex);

            do_work();
        }
    }
    return NULL;
}

void set_thread_flag(int flag_value)
{
    pthread_mutex_lock(&thread_flag_mutex);
    thread_flag = flag_value;
    pthread_cond_signal(&thread_flag_cv);
    pthread_mutex_unlock(&thread_flag_mutex);
}

void *my_func()
{
    while(1)
    {
        set_thread_flag(0);
        sleep(1);
        set_thread_flag(1);
    }
}

int main()
{
    pthread_t thread_id[2];
    // create a new thread
    pthread_create(&thread_id[0], NULL, &thread_function, NULL);
    pthread_create(&thread_id[1], NULL, &my_func, NULL);

    pthread_join(thread_id[0], NULL); 
    pthread_join(thread_id[1], NULL); 

    return 0;
}
