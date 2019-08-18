/*
给你一个整数数组 nums，每次 操作 会从中选择一个元素并 将该元素的值减少 1。
如果符合下列情况之一，则数组 A 就是 锯齿数组：
每个偶数索引对应的元素都大于相邻的元素，即 A[0] > A[1] < A[2] > A[3] < A[4] > ...
或者，每个奇数索引对应的元素都小于相邻的元素，即 A[0] < A[1] > A[2] < A[3] > A[4] < ...
返回将数组 nums 转换为锯齿数组所需的最小操作次数。
输入：nums = [1,2,3]
输出：2
解释：我们可以把 2 递减到 0，或把 3 递减到 1。
输入：nums = [9,6,1,6,2]
输出：4
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int movesToMakeZigzag(int* nums, int numsSize){
    int cnts = 0, cnts2 = 0;
    for(int i = 0; i < numsSize; i += 2) {
        if(i == 0 && nums[0] <= nums[1]) {
            cnts += (nums[1] - nums[0] + 1);
            printf("cnts 0 %d\n", cnts); 
        }
        if(i == 0 && nums[0] >= nums[1]) {
            cnts2 += (nums[0] - nums[1] + 1);
            printf("cnts2 0 %d\n", cnts2); 
        }
        if(i == numsSize - 1 && nums[i] <= nums[i - 1]) {
            cnts += (nums[i - 1] - nums[i] + 1);
            printf("cnts last %d\n", cnts); 
        }
        if(i == numsSize - 1 && nums[i] >= nums[i - 1]) {
            cnts2 += (nums[i] - nums[i - 1] + 1);
            printf("cnts2 last %d\n", cnts2); 
        }
        if(i > 0 && i < numsSize - 1 && (nums[i] <= nums[i+1] || nums[i] <= nums[i-1])) {
            int max = nums[i-1] > nums[i+1] ? nums[i-1] : nums[i+1];
            cnts += (max - nums[i] + 1);
            printf("cnts %d\n", cnts); 
        }
        if(i > 0 && i < numsSize - 1 && (nums[i] >= nums[i+1] || nums[i] >= nums[i-1])) {
            int min = nums[i-1] < nums[i+1] ? nums[i-1] : nums[i+1];
            cnts2 += (nums[i] - min + 1);
            printf("cnts2 %d\n", cnts); 
        }
    }
    printf("cnts %d cnts2 %d\n", cnts, cnts2);
    return (cnts > cnts2 ? cnts2 : cnts);
}

int main()
{
    int a[3] = {1, 2, 3};
    int b[5] = {9,6,1,6,2};
    int c[7] = {7,4,8,9,7,7,5};
    int cnts = movesToMakeZigzag(a, 3);
    int cnts1 = movesToMakeZigzag(b, 5);
    int cnts2 = movesToMakeZigzag(c, 7);

    printf("%d %d %d\n", cnts, cnts1, cnts2);
    return 0;
}
