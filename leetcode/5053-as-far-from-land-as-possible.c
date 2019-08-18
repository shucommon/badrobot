/*
你现在手里有一份大小为 N x N 的『地图』（网格） grid，上面的每个『区域』（单元格）都用 0 和 1 标记好了。其中 0 代表海洋，1 代表陆地，你知道距离陆地区域最远的海洋区域是是哪一个吗？请返回该海洋区域到离它最近的陆地区域的距离。
我们这里说的距离是『曼哈顿距离』（ Manhattan Distance）：(x0, y0) 和 (x1, y1) 这两个区域之间的距离是 |x0 - x1| + |y0 - y1| 。
如果我们的地图上只有陆地或者海洋，请返回 -1。
输入：[[1,0,1],[0,0,0],[1,0,1]]
输出：2
解释： 
海洋区域 (1, 1) 和所有陆地区域之间的距离都达到最大，最大距离为 2。

输入：[[1,0,0],[0,0,0],[0,0,0]]
输出：4
解释： 
海洋区域 (2, 2) 和所有陆地区域之间的距离都达到最大，最大距离为 4。

1 <= grid.length == grid[0].length <= 100
grid[i][j] 不是 0 就是 1

*/
#include <stdio.h>
#include <stdlib.h>

typedef struct point {
    int x;
    int y;
} pt;

int dis(pt pt1, pt pt2)
{
    return (abs(pt1.x - pt2.x) + abs(pt1.y - pt2.y)); 
}

int maxDistance(int** grid, int gridSize, int* gridColSize){
    int max = 0;
    pt pt1 = {0,0}, pt2 = {0,0};

    for(int x = 0; x < *gridColSize; x++) {
        for(int y = 0; y < gridSize; y++) {
            if(grid[x][y] == 0) {
            }
        }
    }
        
    printf("pt1 x %d, y %d\n", pt1.x, pt1.y);
    printf("pt2 x %d, y %d\n", pt2.x, pt2.y);
    return max;
}

int main()
{
    int **grid = (int **)malloc(sizeof(int *) * 2);
    int arr[2] = {0,1};
    int arr1[2] = {0,1};
    grid[0] =  arr;
    grid[1] =  arr1;
    int size = 2;
    int max = maxDistance(grid, size, &size);

    return 0;
}
