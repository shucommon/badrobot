/*
你是一位施工队的工长，根据设计师的要求准备为一套设计风格独特的房子进行室内装修。
房子的客厅大小为 n x m，为保持极简的风格，需要使用尽可能少的 正方形 瓷砖来铺盖地面。
假设正方形瓷砖的规格不限，边长都是整数。
请你帮设计师计算一下，最少需要用到多少块方形瓷砖？
1 <= n <= 13
1 <= m <= 13
*/

class Solution {
public:
    int tilingRectangle(int n, int m) {
        int dp[15][15];
        for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
            dp[i][j]=i==j?1:i*j;
            for(int p=1;p<i;p++)dp[i][j]=min(dp[i][j],dp[p][j]+dp[i-p][j]);
            for(int p=1;p<j;p++)dp[i][j]=min(dp[i][j],dp[i][p]+dp[i][j-p]);
            for(int x=2;x<i;x++)for(int y=2;y<j;y++){
                dp[i][j]=min(dp[i][j],dp[x-1][y]+dp[x][j-y]+dp[i-x+1][y-1]+dp[i-x][j-y+1]+1);
            }
        }return dp[n][m];
    }
};
