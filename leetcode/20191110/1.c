/*
1 <= n <= 50
1 <= m <= 50
1 <= indices.length <= 100
0 <= indices[i][0] < n
0 <= indices[i][1] < m
*/

int oddCells(int n, int m, int** indices, int indicesSize, int* indicesColSize){
    int nm[n][m] = {0};
    for(int i = 0; i < indicesSize; i++) {
        for(int j = 0; j < m; j++) {
            nm[indices[i][0]][j]++;
        }
        for(int j = 0; j < n; j++) {
            nm[j][indices[i][1]]++;
        }
    }
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; i < m; j++) {
            if(nm[i][j] % 2 == 1)
                cnt++;
        }
    }
    return cnt;
}

