#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void print_arr(int arr[], int len)
{
    for(int i = 0; i < len; i++) {
        printf("%d", arr[i]);
        i == len - 1 ? printf("\n") : printf(" ");
    }
}

void quick_sort(int arr[], int s, int e)
{
    if(s >= e)
        return;

    int l = s, r = e;
    int base = arr[l];
    while(l < r) {
        while(l < r && arr[r] >= base)
            r--;
        if(l < r)
            arr[l++] = arr[r];

        while(l < r && arr[l] <= base)
            l++;
        if(l < r)
            arr[r--] = arr[l];
    }
    arr[l] = base;
    quick_sort(arr, s, l - 1);
    quick_sort(arr, l + 1, e);
}

int main()
{
    int len = 25;
    int *arr = get_random_arr(len);
    print_arr(arr, len);
    quick_sort(arr, 0, len - 1);
    print_arr(arr, len);

    return 0;
}
