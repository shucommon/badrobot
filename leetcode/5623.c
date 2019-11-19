/*
1 <= grid.length <= 50
1 <= grid[i].length <= 50
-1000 <= grid[i][j] <= 1000
0 <= k <= 100
*/

void shift_grid(vector<vector<int>> &grid, int n, int m)
{
    int tmp = grid[n-1][m-1]; 
    for(int i = n - 1; i >= 1; i--) {
        for(int j = m - 1; j >= 1; j--) {
            grid[i][j] = grid[i][j-1];
        }
        grid[i][0] = grid[i-1][m-1];
    }
    for(int i = m - 1; i >= 1; i--)
        grid[0][i] = grid[0][i-1];
    grid[0][0] = tmp
}

class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
        for(int i = 0; i < k; i++)
            shift_grid(grid, n, m);
        vector<vector<int>> ret = grid;
        return ret;
    }
};



/*void shift_grid(int **grid, int n, int m, int **ret)
{
    ret[0][0] = grid[n-1][m-1]; 
    for(int i = n - 1; i >= 1; i--) {
        for(int j = m - 1; j >= 1; j--) {
            ret[i][j] = ret[i][j-1];
        }
        ret[i][0] = ret[i-1][m-1];
    }
    for(int i = m - 1; i >= 1; i--)
        ret[0][i] = ret[0][i-1];
}
*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** shiftGrid(int** grid, int gridSize, int* gridColSize, int k, int* returnSize, int** returnColumnSizes){
    int **ret = (int **)malloc(sizeof(int *) * gridSize);
    for(int i = 0; i < gridSize; i++){
        ret[i] = (int *)malloc(sizeof(int) * (*gridColSize));
        memset((void *)ret[i], 0, sizeof(int) * (*gridColSize));
    }
    
    for(int i = 0; i < k; i++)
        shift_grid(grid, gridSize, *gridColSize, ret);

    *returnSize = gridSize;
    *returnColumnSizes = (int *)malloc(sizeof(int));
    **returnColumnSizes = *gridColSize;
 
    return ret;
}
