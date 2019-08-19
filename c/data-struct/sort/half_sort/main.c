#include <stdio.h>
#include "common.h"

void half_sort(int *arr, int len)
{
    if(len < 2)
        return;

    int i = 0, j = 1;
    while(j < len) {
        int l = 0, r = j - 1;
        int tmp = arr[j];
        while(l <= r) {
            int mid = (l + r)/2;
            if(arr[mid] >= tmp)
                r = mid - 1;
            else
                l = mid + 1;
        }
        i = j;
        while(i > l) {
            arr[i] = arr[i-1];
            i--;
        }
        arr[l] = tmp;
        j++;
    }
}

int main()
{
    int len = 25;
    int *arr = get_random_arr(len);
    show(arr, len);
    half_sort(arr, len);
    show(arr, len);
    
    return 0;
}
