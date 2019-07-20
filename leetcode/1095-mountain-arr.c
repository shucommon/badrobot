#include <stdio.h>

typedef int MountainArray;

/**
 * *********************************************************************
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * *********************************************************************
 *
 */
int get(MountainArray *arr, int index)
{
    return arr[index];
}

int length(MountainArray *arr)
{
    return sizeof(arr)/sizeof(arr[0]);
}

int find(int target, int s, int e, MountainArray *arr)
{
    while(s < e)
    {
        int val = get(arr, (s+e)/2);
        if(val == target) {
            return (s+e)/2;
        } else if (val < target) {
            s = (s+e)/2 + 1;
        } else {
            e = (s+e)/2 - 1;
        }
    }
    return -1;
}

int findInMountainArray(int target, MountainArray* mountainArr, int n){
    int len = n;	
    int mid1 = (len - 1)/2;
    int mid2 = mid1 + 1;
    int mid, start = 0, end = len - 1;
    
    int i = 0, n1, n2;

    while(start < end - 2)
    {
        n1 = get(mountainArr, mid1);
        n2 = get(mountainArr, mid2);
        if(n1 < n2)
            start = mid1;
        else
            end = mid2; 

        mid1 = start + (end - start)/2;
        mid2 = mid1 + 1;
    }
    mid = start + 1;

    int ret = 0;
    ret = find(target, 0, mid, mountainArr);
    if(ret == -1)
        ret = find(target, mid, len - 1, mountainArr);
        
    return ret;
}

int main()
{
    MountainArray arr[] = {1,2,3,4,5,3,1};
    //MountainArray arr[] = {0,1,2,4,2,1};
    int n = sizeof(arr)/sizeof(arr[0]);
    int result = findInMountainArray(3, arr, n);
    printf("result %d\n", result);

    return 0;
}
    

