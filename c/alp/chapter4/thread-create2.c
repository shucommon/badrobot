#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct char_print_params
{
    char character;
    int count;
} char_print_params_t;

// print char to stderr given by param
void* char_print(void* param)
{
    char_print_params_t *p =(char_print_params_t*)param;
    int i;
    for(i = 0; i < p->count; i++)
    {
        fputc(p->character, stderr);
    }
    return NULL;
}

int main()
{
    pthread_t thread1_id;
    pthread_t thread2_id;
    char_print_params_t thread1_args;
    char_print_params_t thread2_args;
    thread1_args.character = 'x';
    thread1_args.count = 30000;
    // create a new thread.
    pthread_create(&thread1_id, NULL, &char_print, &thread1_args);

    thread2_args.character = 'o';
    thread2_args.count = 20000;
    // create a new thread.
    pthread_create(&thread2_id, NULL, &char_print, &thread2_args);

    // make sure the first thread has finished
    pthread_join(thread1_id, NULL);
    // make sure the second thread has finished
    pthread_join(thread2_id, NULL);

    // now we can safely return
    return 0;
}
