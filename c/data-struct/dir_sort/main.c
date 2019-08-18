#include <stdio.h>

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
    dir_sort(arr, 10);
    show(arr, 10);
    
    return 0;
}
