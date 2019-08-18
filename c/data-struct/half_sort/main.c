#include <stdio.h>

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

void show(int *arr, int len)
{
    for(int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[] = {4, 2, 5, 9, 3, 2, 1, 8, 6, 7};
    half_sort(arr, 10);
    show(arr, 10);
    
    return 0;
}
