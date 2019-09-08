#include <stdio.h>

/*
*/
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

int makeArrayIncreasing(int* arr1, int arr1Size, int* arr2, int arr2Size){
    int step = -1, index = 0;

    quick_sort(arr2, 0, arr2Size - 1);
    for(int i = 1; i < arr1Size; i++) {
        if(arr1[i-1] >= arr1[i]) {
        }
    }

    return step;
}

int main()
{

    return 0;
}
