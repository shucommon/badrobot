#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* distributeCandies(int candies, int num_people, int* returnSize){
    int *arr = (int *)malloc(sizeof(int) * num_people);
    int n = num_people, k = 0;
    int left = candies;
    int cd = 1;
    *returnSize = num_people;

    for(int i = 0; i < n; i++)
        arr[i] = 0;

    int i = 0;
    while(candies > 0)
    {
        if(candies >= cd)
            arr[i++] += cd++; 
        else
        {
            arr[i] += candies;
            break;
        }
        candies -= (cd - 1);
        if(i == num_people)
            i = 0; 
    }
    
    return arr;
}

int main()
{
    
    int rt;
    //int *ret = distributeCandies(7, 4, &rt);
    int *ret = distributeCandies(10, 3, &rt);
    for(int i = 0; i < rt; i++)
        printf("%d ", ret[i]);

    return 0;
}
