#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
输入：hours = [9,9,6,0,6,6,9]
输出：3
解释：最长的表现良好时间段是 [9,9,6]。
*/

int longestWPI(int* hours, int hoursSize){
    int *dp = (int *)malloc(sizeof(int) * hoursSize);
    int l = 0; r = 0;

    for(int i = 0; i < hoursSize; i++)
    {
        if(hours[i] > 8)
            dp[i] = 1;
        else
            dp[i] = 0;
    }

    for(int i = 0; i < hoursSize; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            if(dp[l] 

        }
    }

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
