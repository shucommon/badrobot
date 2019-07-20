/*
           -> 1
         3          2 <--
 -->  4     5     6    7
   15  14 13 12 11 10 9 8  <---
在一棵无限的二叉树上，每个节点都有两个子节点，树中的节点 逐行 依次按 “之” 字形进行标记。
如下图所示，在奇数行（即，第一行、第三行、第五行……）中，按从左到右的顺序进行标记；
而偶数行（即，第二行、第四行、第六行……）中，按从右到左的顺序进行标记。
给你树上某一个节点的标号 label，请你返回从根节点到该标号为 label 节点的路径，该路径是由途经的节点标号所组成的。
*/

/*
输入：label = 14
输出：[1,3,4,14]

输入：label = 26
输出：[1,2,6,10,26]

1 <= label <= 10^6
*/

/*
1. 求出label 所在行k, 起始行1
2. 求出label 镜像值m = 2^(k-1) + 2^k - 1 - label
3. 得到father 值 n = m/2
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>

int power(int a, int e)
{
    int ret = 1;
    while(e) {
        ret *= a; 
        e--;
    }
    return ret;
}

int* pathInZigZagTree(int label, int* returnSize){
    int k = 1;
    int tmp = 1;
    while((tmp *= 2) <= label)
        k++;
    *returnSize = k;

    int *ret = (int *)malloc(sizeof(int) * k);

    ret[k-1] = label;
    while(k > 1) {
        int m = power(2, k-1) + power(2, k) - 1 - label;
        k--;
        ret[k-1] = m/2; 
        label = ret[k-1];
    }
    
    return ret;
}

int main()
{
    int size;
    int *p = pathInZigZagTree(14, &size);
    printf("label 14:\n");
    for(int i = 0; i < size; i++)
        printf("%d ", p[i]);
    printf("label 26:\n");
    p = pathInZigZagTree(26, &size);
    for(int i = 0; i < size; i++)
        printf("%d ", p[i]);
    return 0;
}
