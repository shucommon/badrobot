int countServers(int** grid, int gridSize, int* gridColSize){
    for(int i = 0; i < gridSize; i++) {
        int index = -1;
        for(int j = 0; j < *gridColSize; j++) {
            if(grid[i][j] && index == -1) {
                index = j;
            }
            else if(index > -1 && grid[i][j]) {
                grid[i][index] = 2;
                grid[i][j] = 2;
            }
        }
    }
    for(int i = 0; i < *gridColSize; i++) {
        int index = -1;
        for(int j = 0; j < gridSize; j++) {
            if(grid[j][i] && index == -1) {
                index = j;
            }
            else if(index > -1 && grid[j][i]) {
                grid[index][i] = 2;
                grid[j][i] = 2;
            }
        }
    }

    int cnt = 0;
    for(int i = 0; i < gridSize; i++) {
        for(int j = 0; j < *gridColSize; j++) {
            if(grid[i][j] == 2)
                cnt++;
        }
    }

    return cnt;
}
