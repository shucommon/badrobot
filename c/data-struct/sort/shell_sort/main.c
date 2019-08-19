#include <stdio.h>
#include <stdlib.h>
#include "../common.h"

void shell_sort(int *arr, int len)
{
    int gap, i, j;
    for(gap = len/2; gap > 0; gap /= 2) {
        for(i = gap; i < len; i++) {
            for(j = i - gap; j>=0 && (arr[j + gap] < arr[j]); j -= gap) {
                int tmp = arr[j];
                arr[j] = arr[j+gap];
                arr[j+gap] = tmp;
            }
        }
    }
}

int main()
{
    int len = 25;
    int *arr = get_random_arr(len);
    printf("ori\n");
    show(arr, len);
    shell_sort(arr, len);
    printf("sorted\n");
    show(arr, len);
    
    return 0;
}
