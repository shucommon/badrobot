/*
*/
#include <stdio.h>
//#include <math.h>
#include <stdlib.h>

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
    quick_sort(arr, s, l-1);
    quick_sort(arr, l+1, e);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** minimumAbsDifference(int* arr, int arrSize, int* returnSize, int** returnColumnSizes){
    quick_sort(arr, 0, arrSize - 1);
    if(arrSize < 2)
        return NULL;
    int cnt = 0, min = abs(arr[0] - arr[1]);
    for(int i = 0; i < arrSize - 1; i++) {
        int val = abs(arr[i] - arr[i+1]);
        if(min > val) {
            cnt = 1;
            min = val;
        } else {
            cnt++;
        }
    }
    int ** ret = (int **)malloc(sizeof(int *) * cnt);
    for(int i = 0; i < cnt; i++) {
        ret[i] = (int *)malloc(sizeof(int) * 2);
    }
    *returnSize = cnt; 
    *returnColumnSizes = (int *)malloc(sizeof(int));
    **returnColumnSizes = 2;
    cnt = 0;
    for(int i = 0; i < arrSize - 1; i++) {
        int val = abs(arr[i] - arr[i+1]);
        if(val == min) {
            ret[cnt][0] = arr[i];
            ret[cnt][1] = arr[i+1];
            cnt++;
        }
    }
    return ret;
}

//demo
class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& a) {
        sort(a.begin(), a.end());
        int n = a.size();
        int diff = 100000000;
        for (int i = 1; i < n; ++ i) diff = min(diff, a[i]-a[i-1]);
        vector<vector<int>> ret;
        for (int i = 1; i < n; ++ i) if (diff == a[i]-a[i-1]) ret.push_back({a[i-1], a[i]});
        return ret;
    }
};

int main()
{
    int arr[4] = {4,2,1,3};
    int rs, *rcs;
    int **ret = minimumAbsDifference(arr, 4, &rs, &rcs);
    printf("rsize %d, rcolsize %d\n", rs, *rcs);

    return 0;
}
