#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
泰波那契序列 Tn 定义如下： 
T0 = 0, T1 = 1, T2 = 1, 且在 n >= 0 的条件下 Tn+3 = Tn + Tn+1 + Tn+2
给你整数 n，请返回第 n 个泰波那契数 Tn 的值。
*/
int tribonacci(int n){
    static int dp[38] = { 0 };
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 1;

    if(dp[n] == 0 && n > 2){
        dp[n] = tribonacci(n-1) + tribonacci(n-2) + tribonacci(n - 3);
    }
    return dp[n];
}


int main()
{
    int n;
    n = 4;
    printf("%d\n", tribonacci(n));
    n = 25;
    printf("%d\n", tribonacci(n));

    return 0;
}
