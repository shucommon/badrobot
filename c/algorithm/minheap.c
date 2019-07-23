#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
void print_heap(int arr[], int len)
{
    printf("sorted heap:\n");
    for(int i = 0; i < len; i++) {
        printf("%d", arr[i]);
        i == len-1 ? printf("\n") : printf(" ");
    }
}

void print_heap_struct(int arr[], int len)
{
    int newline = 1;
    int cnt = 0;
    printf("heap struct:\n");
    for(int i = 0; i < len; i++) {
        printf("%d", arr[i]);
        if(i == cnt) {
            newline *= 2;
            cnt += newline;
            printf("\n");
        } else {
            i == len - 1 ? printf("\n") : printf(" ");
        }
    }
}

void min_heap_fixup(int arr[], int len, int i_f)    // i_f means index father
{
    int l = 2 * i_f + 1;
    int r = l + 1;
    int min_i = i_f;

    if(l < len && arr[l] < arr[min_i]) {
        min_i = l;
    }
    if(r < len && arr[r] < arr[min_i]) {
        min_i = r;
    }

    if(min_i != i_f) {    // min value is not father
        int tmp = arr[i_f];
        arr[i_f] = arr[min_i];
        arr[min_i] = tmp;

        min_heap_fixup(arr, len, min_i); // go through until lead node
    }
}

void build_min_heap(int arr[], int len)
{
    for(int i = (len - 2)/2; i >= 0; i--) {
        min_heap_fixup(arr, len, i);
    }
}

// min heap sort get decrease arr
void min_heap_sort(int arr[], int len)
{
    build_min_heap(arr, len);
    print_heap_struct(arr, len);

    // sort
    for(int i = len - 1; i >= 1; i--) { // each loop, a[0] is the min value, swap to last
        int tmp = arr[i];
        arr[i] = arr[0];
        arr[0] = tmp;

        min_heap_fixup(arr, i-1, 0);
    }
    
}

int main()
{
    int a_len = 20;
    int *a = (int *)malloc(sizeof(int) * a_len);

    time_t t;
    /* Intializes random number generator */
    srand((unsigned) time(&t));
    for(int i = 0; i < a_len; i++)
        a[i] = rand() % 10000 + 1;

    min_heap_sort(a, a_len);
    print_heap(a, a_len);

    int arr[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int len = sizeof(arr) / sizeof(int);
    min_heap_sort(arr, len);
    print_heap(arr, len);
 
    return 0;
}
