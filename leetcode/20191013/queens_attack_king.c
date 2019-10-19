#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** queensAttacktheKing(int** queens, int queensSize, int* queensColSize, int* king, int kingSize, int* returnSize, int** returnColumnSizes){
    int **target = (int **)malloc(sizeof(int *) * 8);
   
    int found[8] = { 0 };
    for(int i = 0; i < queensSize; i++) {
        if(queens[i][0] == king[0]) {  // x same
            int *tmp = (int *)malloc(sizeof(int) * 2);
            tmp[0] = queens[i][0];
            tmp[1] = queens[i][1];
            if(queens[i][1] > king[1]) {
                if(found[0]) {
                    if(target[0][1] > queens[i][1])
                        target[0] = tmp;
                } else {
                    found[0] = 1;
                    target[0] = tmp;
                }
            }else {
                if(found[1]) {
                    if(target[1][1] < queens[i][1])
                        target[1] = tmp;
                } else {
                    found[1] = 1;
                    target[1] = tmp;
                }
            }
        } else if(queens[i][1] == king[1]) {  // y same
            int *tmp = (int *)malloc(sizeof(int) * 2);
            tmp[0] = queens[i][0];
            tmp[1] = queens[i][1];
            if(queens[i][0] > king[0]) {
                if(found[2]) {
                    if(target[2][0] > queens[i][0])
                        target[2] = tmp;
                } else {
                    found[2] = 1;
                    target[2] = tmp;
                }
            }else {
                if(found[3]) {
                    if(target[3][0] < queens[i][0])
                        target[3] = tmp;
                } else {
                    found[3] = 1;
                    target[3] = tmp;
                }
            }
        } else if(abs(queens[i][0] - queens[i][1]) == abs(king[0] - king[1])) {
            int *tmp = (int *)malloc(sizeof(int) * 2);
            tmp[0] = queens[i][0];
            tmp[1] = queens[i][1];
            if(queens[i][0] > king[0]) {
                int index;
                if(queens[i][1] < king[1])
                    index = 4;
                else
                    index = 5;
                if(found[index]) {
                    if(target[index][0] > queens[i][0])
                        target[index] = tmp;
                } else {
                    found[index] = 1;
                    target[index] = tmp;
                }
            } else {
                int index;
                if(queens[i][1] < king[1])
                    index = 6;
                else
                    index = 7;
                if(found[index]) {
                    if(target[index][0] < queens[i][0])
                        target[index] = tmp;
                } else {
                    found[index] = 1;
                    target[index] = tmp;
                }
            }
        }
    }
    int cnt = 0;
    for(int i = 0; i < 8; i++) {
        if(found[i])
            target[cnt++] = target[i];
    }    

    returnSize = (int *)malloc(sizeof(int));    
    *returnSize = cnt;    
    
    returnColumnSizes = (int **)malloc(sizeof(int *));
    *returnColumnSizes = (int *)malloc(sizeof(int));
    **returnColumnSizes = 2;

    return target;
}

int main()
{
    int **queens = {{0,1},{1,0},{4,0},{0,4},{3,3},{2,4}};
    int *king = {0,0};
    int queensSize = 6;
    int queensColSize = 2;
    int *returnSize;
    int **returnColumnSizes;

    int** ret = queensAttacktheKing(queens, queensSize, &queensColSize, king, 1, returnSize, returnColumnSizes);


    return 0;
}
