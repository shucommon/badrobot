#include <stdio.h>
#include "common.h"

void dir_sort(int *arr, int len)
{
    if(len < 2)
        return;

    int i = 0, j = 1;
    while(j < len) {
        i = j;
        while(i > 0 && arr[i] < arr[i-1]) {
            int tmp = arr[i-1];
            arr[i-1] = arr[i];
            arr[i] = tmp;
            i--;
        }
        j++;
    }
}

int main()
{
    int len = 25;
    int *arr = get_random_arr(len);
    show(arr, len);
    dir_sort(arr, len);
    show(arr, len);
    
    return 0;
}
