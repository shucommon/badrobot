#include <stdio.h>
#include <stdlib.h>
#include "../common.h"

void quick_sort(int *arr, int s, int e)
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
    printf("ori\n");
    show(arr, len);
    quick_sort(arr, 0, len - 1);
    printf("sorted\n");
    show(arr, len);
    
    return 0;
}
