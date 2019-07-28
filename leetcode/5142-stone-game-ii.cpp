/*
亚历克斯和李继续他们的石子游戏。许多堆石子 排成一行，每堆都有正整数颗石子 piles[i]。游戏以谁手中的石子最多来决出胜负。
亚历克斯和李轮流进行，亚历克斯先开始。最初，M = 1。
在每个玩家的回合中，该玩家可以拿走剩下的 前 X 堆的所有石子，其中 1 <= X <= 2M。然后，令 M = max(M, X)。
游戏一直持续到所有石子都被拿走。
假设亚历克斯和李都发挥出最佳水平，返回亚历克斯可以得到的最大数量的石头。
*/
class Solution {
public:
    int stoneGameII(vector<int>& a) {
        int dp[105][105],s[105],n=a.size(),i,j,k;
        memset(dp,0,sizeof(dp));
        memset(s,0,sizeof(s));
        for (i=1;i<=n;i++) s[i]=s[i-1]+a[i-1];
        for (i=n;i>=1;i--) {
            for (j=1;j<=100;j++) {
                for (k=1;i+k-1<=n&&k<=2*j;k++)
                    dp[i][j]=max(dp[i][j],s[n]-s[i-1]-dp[i+k][min(100,max(j,k))]);
            }
        }
        return dp[1][1];
    }
};
