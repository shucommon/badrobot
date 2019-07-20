/*
N位同学站成一排，音乐老师要请其中的(N-K)位同学出列，使得剩下的K位同学排成合唱队形。 
合唱队形是指这样的一种队形：设K位同学从左到右依次编号为1，2…，K，他们的身高分别为T1，T2，…，TK，   则他们的身高满足存在i（1<=i<=K）使得T1<T2<......<Ti-1<Ti>Ti+1>......>TK。 
你的任务是，已知所有N位同学的身高，计算最少需要几位同学出列，可以使得剩下的同学排成合唱队形。

输入描述:
整数N
输出描述:
最少需要几位同学出列

示例1
输入
8
186 186 150 200 160 130 197 200
输出
4
*/

#include <stdio.h>
#include <stdlib.h>

void dp_sub(int *arr, int *dp, int n)
{
    for(int i = 1; i < n; i++) {
        for(int j = i - 1; j >= 0; j--) {
            if(arr[j] < arr[i] && dp[i] < dp[j] + 1)
                dp[i] = dp[j] + 1;
        }
    }
}

int main()
{
    int n;

    while(scanf("%d", &n) != EOF) {
        int *inc = (int *)malloc(sizeof(int) * n);
        int *dec = (int *)malloc(sizeof(int) * n);
        int *arr = (int *)malloc(sizeof(int) * n);
        int *arr_rev = (int *)malloc(sizeof(int) * n);
        int *p = arr;
        for(int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
            arr_rev[n-i-1] = arr[i];
            *(inc + i) = 1; 
            *(dec + i) = 1; 
        }
        dp_sub(arr, inc, n);
        dp_sub(arr_rev, dec, n);
    
        int max = 0;
        for(int i = 0; i < n; i++)
        {
            if(max < inc[i] + dec[n-i-1]) 
                max = inc[i] + dec[n-i-1];
        }
        printf("%d\n", n-max+1);
    }

    return 0;
}

/*
首先计算每个数在最大递增子串中的位置

186  186  150  200  160  130  197  200   quene

1      1      1      2       2      1      3     4       递增计数


然后计算每个数在反向最大递减子串中的位置--->计算反向后每个数在最大递增子串中的位置

200  197  130  160  200  150  186  186   反向quene

1      1      1       2     3      2      3       3      递减计数


然后将每个数的递增计数和递减计数相加

186  186  150  200  160  130  197  200   quene

1      1      1      2       2     1      3      4       递增计数

3      3      2      3       2     1      1      1       递减计数

4      4      3      5       4     2      4      5       每个数在所在队列的人数+1（自己在递增和递减中被重复计算）

如160这个数

在递增队列中有2个人数

150  160

在递减队列中有2个人数

160  130

那么160所在队列中就有3个人

150  160  130

每个数的所在队列人数表达就是这个意思
总人数 - 该数所在队列人数 = 需要出队的人数
*/
