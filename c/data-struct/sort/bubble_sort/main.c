#include <stdio.h>
#include <stdlib.h>
#include "../common.h"

void bubble_sort(int *arr, int len)
{
    for(int i = 0; i < len - 1; i++) {
        for(int j = 0; j < len - 1 - i; j++) {
            if(arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

// break ahead
void bubble_sort_refine(int *arr, int len)
{
    for(int i = 0; i < len - 1; i++) {
        int flag = 1;
        for(int j = 0; j < len - 1 - i; j++) {
            if(arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                flag = 0;
            }
        }
        if(flag)
            break;
    }
}

int main()
{
    int len = 25;
    int *arr = get_random_arr(len);
    printf("ori\n");
    show(arr, len);
    bubble_sort_refine(arr, len);
    printf("sorted\n");
    show(arr, len);
    
    return 0;
}
