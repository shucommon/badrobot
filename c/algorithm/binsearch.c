#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_arr(int arr[], int len)
{
    for(int i = 0; i < len; i++) {
        printf("%d", arr[i]);
        i == len - 1 ? printf("\n") : printf(" ");
    }
}

int binsearch(int arr[], int key, int len)
{
    int l = 0, r = len - 1;
    while(l <= r) {
        int mid = (l + r)/2;
        if(arr[mid] == key)
            return mid;
        else if(arr[mid] > key) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return -1;
}

int main()
{
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    for(int i = 1; i <= 10; i++) {
        int sub = binsearch(arr, i, 10);
        printf("key %d sub is %d\n", i, sub);
    }

    return 0;
}
