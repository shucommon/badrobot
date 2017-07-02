#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

/* compute successive prime numbes (very inefficiently)
 * return the Nth prime number
 */
void* compute_prime(void* arg)
{
    int candidate = 2;
    int n = *((int*)arg);

    while(1)
    {
        int factor;
        int is_prime = 1;

        for(factor = 2; factor < candidate; factor++)
        {
            if(candidate % factor == 0)
            {
                is_prime = 0;
                break;
            }
        }
        if(is_prime)
        {
            if(--n == 0)
                return (void*)candidate;
        }
        ++candidate;
    }

    return NULL;
}

int main()
{
    pthread_t thread;
    int which_prime = 5000;
    int prime;

    // create a new thread.
    pthread_create(&thread, NULL, &compute_prime, &which_prime);

    // do some othe work

    // make sure the first thread has finished
    pthread_join(thread,(void*)&prime);

    printf("the %dth prime number is %d\n", which_prime, prime);
    // now we can safely return
    return 0;
}
