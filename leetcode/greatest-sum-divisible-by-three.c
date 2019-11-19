/*
给你一个整数数组 nums，请你找出并返回能被三整除的元素最大和。

示例 1：
输入：nums = [3,6,5,1,8]
输出：18
解释：选出数字 3, 6, 1 和 8，它们的和是 18（可被 3 整除的最大和）。
*/

const int INF = 1000000000;

class Solution {
public:
    int maxSumDivThree(vector<int>& a) {
        int n = a.size();
        vector<vector<int>> f(n+1, vector<int>(3, -INF));
        f[0][0] = 0;
        for (int i = 1; i <= n; ++ i)
        {
            for (int j = 0; j < 3; ++ j)
                f[i][(j+a[i-1])%3] = max(f[i-1][(j+a[i-1])%3], f[i-1][j]+a[i-1]);
        }
        return f[n][0];
    }
};
