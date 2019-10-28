#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
[200~给你两个整数 n 和 start。你的任务是返回任意 (0,1,2,,...,2^n-1) 的排列 p，并且满足：

p[0] = start
p[i] 和 p[i+1] 的二进制表示形式只有一位不同
p[0] 和 p[2^n -1] 的二进制表示形式也只有一位不同
*/
/*
输入：n = 2, start = 3
输出：[3,2,0,1]
解释：这个排列的二进制表示是 (11,10,00,01)
     所有的相邻元素都有一位是不同的，另一个有效的排列是 [3,1,0,2]
*/
/*
输出：n = 3, start = 2
输出：[2,6,7,5,4,0,1,3]
解释：这个排列的二进制表示是 (010,110,111,101,100,000,001,011)
*/
/*
1 <= n <= 16
0 <= start < 2^n
*/
/*
insert 1 on the left
00
01

11
10

110
111
101
100

1100
1101
1111
1110
1010
1011
1001
1000
*/
int generate(int *arr, int n, int start)
{
    int ret = start;
    arr[0] = 0;
    arr[1] = 1;

    for(int i = 1; i < n; i++) {
        for(int j = (1 << (i+1)) - 1; j >= (1 << i); j--) {
            arr[j] = ((1 << i) | arr[(1<<(i+1)) - 1 - j]);
            if(arr[j] == start)
                ret = j;
        }
    }
    return ret;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* circularPermutation(int n, int start, int* returnSize){
    int last = pow(2, n) - 1;
    int *arr = (int *)malloc(sizeof(int) * (last + 1));
    *returnSize = last + 1;

    if(n == 1) {
        arr[0] = start;
        arr[1] = ((arr[0] + 1) & 1);
        return arr;
    }
    int index = generate(arr, n, start);
    int *ret = (int *)malloc(sizeof(int) * (last + 1));
    for(int i = 0; i < (1 << n); i++)
        ret[i] = arr[(index + i) % (1 << n)]; 
    free(arr);

    return ret;
}


int main()
{
    int rs = 0;
    int *ret = circularPermutation(2, 1, &rs);
    
    for(int i = 0; i < rs; i++)
        printf("0x%04x\n", ret[i]);

    return 0;
}
