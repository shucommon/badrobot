// not passed leetcode, passed local
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
1 <= colsum.length <= 10^5
0 <= upper, lower <= colsum.length
0 <= colsum[i] <= 2
*/


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** reconstructMatrix(int upper, int lower, int* colsum, int colsumSize, int* returnSize, int** returnColumnSizes){
    int **arr = (int **)malloc(sizeof(int *) * 2);
    arr[0] = (int *)malloc(sizeof(int) * colsumSize);
    arr[1] = (int *)malloc(sizeof(int) * colsumSize);

    memset(arr[0], 0, sizeof(int)  * colsumSize);
    memset(arr[1], 0, sizeof(int)  * colsumSize);

    int up = 0;
    int low = 0;
    int tmp = 0;
    for(int i = 0; i < colsumSize; i++) {
        if(colsum[i] == 0) {
            arr[0][i] = 0;
            arr[1][i] = 0;
        } else if(colsum[i] == 2) {
            arr[0][i] = 1;
            arr[1][i] = 1;
            up++;
            low++;
        } else {
            arr[0][i] = 2;
            arr[1][i] = 2;
            tmp++;
        }
    }
    *returnSize = 2;

    *returnColumnSizes = (int *)malloc(sizeof(int));
    **returnColumnSizes = colsumSize;

    if((up > upper) || (low > lower) || (upper + lower - up - low != tmp)) {
        memset(arr[0], 0, sizeof(int)  * colsumSize);
        memset(arr[1], 0, sizeof(int)  * colsumSize);
        return arr;
    }

    up = upper - up;
    low = lower - low;
    for(int j = 0; j < colsumSize; j++) {
        if(up && (arr[0][j] == 2)) {
            arr[0][j] = 1;
            arr[1][j] = 0;
            up--;
        }
        if((up == 0) && low && (arr[1][j] == 2)) {
            arr[0][j] = 0;
            arr[1][j] = 1;
            low--;
        }
    } 
    return arr;
}

int main()
{
    int upper = 2, lower = 1;
    int col[3] = {1,1,1}; 
    int *colsum = col; 
    int colsumSize = 3;
    int returnSize, *returnColumnSizes;
    int** ret = reconstructMatrix(upper, lower, colsum, colsumSize, &returnSize, &returnColumnSizes);
    printf("%d\n", *returnColumnSizes);
    for(int i = 0; i < *returnColumnSizes; i++)
        printf("%d %d\n", ret[0][i], ret[1][i]);

    return 0;
}
