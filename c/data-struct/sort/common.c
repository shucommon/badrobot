#include "common.h"

// caller have the duty to free return arr
int * get_random_arr(int len)
{
    int *arr = (int *)malloc(sizeof(int) * len);

    time_t t;
    /* Intializes random number generator */
    srand((unsigned) time(&t));
    for(int i = 0; i < len; i++)
        arr[i] = rand() % 10000 + 1;

    return arr;
}

void show(int *arr, int len)
{
    for(int i = 0; i < len; i++) {
        printf("%d", arr[i]);
        if(i < len - 1)
            printf(" ");
        else
            printf("\n");
    }
}
