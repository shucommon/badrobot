#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    if( a > b)
        return a;
    return b;
}

int main()
{
    int N, m;
    int v[60], p[60], q[60];
    int cnt = 0;
    scanf("%d %d", &N, &m);
    int dp[60][32000] = {0};

    for(int i = 1; i <= m; i++)
    {
        scanf("%d %d %d", &v[i], &p[i], &q[i]);
    }

    for(int i = 1; i < m + 1; i++) {
        for(int j = 1; j < N + 1; j++) {
            if(q[i] == 0) {  // main obj 
                if(j >= v[i])
                    dp[i][j] = max(dp[i-1][j], dp[i-1][j-v[i]] + v[i] * p[i]);
                else
                    dp[i][j] = dp[i - 1][j];
            } else {
                if(j >= v[q[i]] + v[i])
                    dp[i][j] = max(dp[i-1][j], dp[i-1][j - v[q[i]] - v[i]] + v[i] * p[i] + v[q[i]] * p[q[i]]);
                else
                    dp[i][j] = dp[i-1][j];
            }
        }
    }
    printf("%d\n", dp[m][N]);

    return 0;
}

