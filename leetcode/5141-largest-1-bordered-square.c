#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
给你一个由若干 0 和 1 组成的二维网格 grid，请你找出边界全部由 1 组成的最大 正方形 子网格，并返回该子网格中的元素数量。如果不存在，则返回 0。
示例 1：
输入：grid = [[1,1,1],[1,0,1],[1,1,1]]
输出：9
示例 2：
输入：grid = [[1,1,0,0]]
输出：1
 
提示：
1 <= grid.length <= 100
1 <= grid[0].length <= 100
grid[i][j] 为 0 或 1
*/
typedef struct _point {
    int x;
    int y;
} point;

int is_square(int ** grid, point start, point end)
{
    for(int i = start.x; i <= start.x + end.x - start.x; i++) {
        if(grid[i][start.y] == 0 || grid[i][end.y] == 0)
            return 0;
    }

    for(int j = start.y; j <= start.y + end.y - start.y; j++) {
        if(grid[start.x][j] == 0 || grid[end.x][j] == 0)
            return 0;
    }
    return 1;
}

int largest1BorderedSquare(int** grid, int gridSize, int* gridColSize)
{
    int min = gridSize;
    min = (min < *gridColSize ? min : *gridColSize);
    printf("min %d\n", min);
    point start, end;
    start.x = 0;
    start.y = 0;
    end.x = min - 1;
    end.y = min - 1; 
    int len = min - 1;
    while(len >= 0) {
        while(end.x < gridSize) {
            while(end.y < *gridColSize) {
                if(is_square(grid, start, end)) 
                    return (len + 1) * (len + 1); 
                else {
                    start.y++;
                    end.y++;
                }
            }
            start.x++;
            end.x++;
            start.y = 0;
            end.y = start.y + len;
        }
        len--;
        start.x = 0;
        start.y = 0;
        end.x = start.x + len;
        end.y = start.y + len;
    }
    return 0;
}

int main()
{
    int grid[3][3] = {{1,1,1},{1,0,1},{1,1,1}};
    int **p = (int **)malloc(sizeof(int *) * 3);
    p[0] = grid[0];
    p[1] = grid[1];
    p[2] = grid[2];
    int size = 3;
    int len = largest1BorderedSquare(p, 3, &size);
    printf("len %d\n", len);

/*
    int grid[2][2] = {{0,0},{0,0}};
    int **p = (int **)malloc(sizeof(int *) * 2);
    p[0] = grid[0];
    p[1] = grid[1];
    int size = 2;
    int len = largest1BorderedSquare(p, 2, &size);
    printf("len %d\n", len);
*/

    return 0;
}
