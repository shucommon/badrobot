#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>

struct job
{
    struct job* next;

    // other filed
};

struct job * job_queue;

pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

sem_t job_queue_count;

void initialize_job_queue(void)
{
   job_queue = NULL;
   
   // param 3 = init value
   sem_init(&job_queue_count, 0, 0);

void process_job(struct job *job)
{

}

void* thread_function(void* arg)
{
    while(1)
    {
        struct job *next_job;

        // value is positive then decrement by 1
        // empty, block until a new job enqueue
        sem_wait(&job_queue_conut);

        pthread_mutex_lock(&job_queue_mutex);
        next_job = job_queue;
        job_queue = job_queue->next;
        pthread_mutex_unlock(&job_queue_mutex);

        process_job(next_job);
        free(next_job);
    }
    return NULL;
}

void enqueue_job(struct job * new_job)
{
    struct job * new_job;
    new_job =  (struct job *)malloc(sizeof(struct job));

    pthread_mutex_lock(&job_queue_mutex);
    new_job->next = job_queue;
    job_queue = new_job;

    sem_post(&job_queue_count);

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
