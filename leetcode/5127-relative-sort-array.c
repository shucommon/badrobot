#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void sort_up(int *sort_arr, int cnt)
{
    for(int i = 0; i < cnt; i++)
    {
        for(int j = 0; j < cnt - i - 1; j++)
        {
            if(sort_arr[j] > sort_arr[j+1])
            {
                int tmp = sort_arr[j];
                sort_arr[j] = sort_arr[j+1];
                sort_arr[j + 1] = tmp;
            }
        }
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* relativeSortArray(int* arr1, int arr1Size, int* arr2, int arr2Size, int* returnSize){
    int arr[1000] = {0};
    int sort_arr[1000] = {0};
    int cnt = 0;
    int *ret = (int *)malloc(sizeof(int)*arr1Size);
    *returnSize = arr1Size;

    for(int i = 0; i < arr2Size; i++)
        arr[arr2[i]] = 1;

    for(int i = 0; i < arr1Size; i++)
    {
        if(arr[arr1[i]] > 0) {
            arr[arr1[i]]++;
            continue;
        }
        sort_arr[cnt++] = arr1[i];
    }
    //sort_up(sort_arr, cnt);
    for(int i = 0; i < cnt; i++)
    {
        for(int j = 0; j < cnt - i - 1; j++)
        {
            if(sort_arr[j] > sort_arr[j+1])
            {
                int tmp = sort_arr[j];
                sort_arr[j] = sort_arr[j+1];
                sort_arr[j + 1] = tmp;
            }
        }
    }

    int cnt1 = 0;
    for(int i = 0; i < arr2Size; i++)
    {
        while(arr[arr2[i]]-- > 1)
            ret[cnt1++] = arr2[i];
    }
    for(int i = 0; i < cnt; i++)
        ret[cnt1++] = sort_arr[i];
    return ret;
}


int main()
{
    int arr1[] = {2,3,1,3,2,4,6,19,9,2,7}, arr2[] = {2,1,4,3,9,6};
    int *p1 = arr1, *p2 = arr2;
    int retsize;
    int *a = relativeSortArray(p1, 11, p2, 6, &retsize);
    for(int i = 0; i < retsize; i++)
        printf("%d ", a[i]);

    return 0;
}
