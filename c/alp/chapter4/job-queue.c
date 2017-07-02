#include <malloc.h>
#include <pthread.h>

struct job
{
    struct job* next;

    // other filed
};

struct job * job_queue = NULL;

pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

void process_job(struct job *job)
{

}

void* thread_function(void* arg)
{
    while(1)
    {
        struct job *next_job;

        pthread_mutex_lock(&job_queue_mutex);
        if(job_queue == NULL)
        {
            next_job = NULL;
        }
        else
        {
            next_job = job_queue;
            job_queue = job_queue->next;
        }
        pthread_mutex_unlock(&job_queue_mutex);

        if(next_job == NULL)
        {
            break;
        }

        process_job(next_job);
        free(next_job);
    }
    return NULL;
}

void enqueue_job(struct job * new_job)
{
    pthread_mutex_lock(&job_queue_mutex);
    new_job->next = job_queue;
    job_queue = new_job;
    pthread_mutex_unlock(&job_queue_mutex);
}

int main()
{
    pthread_t thread_id;
    int ret;
    int parm = 1;
    // create a new thread
    pthread_create(&thread_id, NULL, &thread_function, &parm);

    pthread_join(thread_id, (void*)&ret); 

    printf("ret = %d, thread_id = %d\n", ret, (int)thread_id);

    return 0;
}
