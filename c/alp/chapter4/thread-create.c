#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

long int x = 0, y = 0;

// print x's to stderr.
void* print_xs(void* unused)
{
    while(1)
    {
        x++;
        fputc('x', stderr);
    }
    return NULL;
}

void* print_c(void* unused)
{
    while(1)
    {
        printf("\n***********************************\n");
        printf("x=%ld, y=%ld, x-y = %ld\n", x, y, x-y);
        printf("\n***********************************\n");
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t thread_id;
    pthread_t thread_id_c;
    // create a new thread. the new thread will run the print_xs function
    pthread_create(&thread_id, NULL, &print_xs, NULL);
    pthread_create(&thread_id_c, NULL, &print_c, NULL);

    while(1)
    {
        y++;
        fputc('o', stderr);
    }
    
    return 0;
}
