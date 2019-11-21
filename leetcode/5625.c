#include <stdio.h>
#include <math.h>
/*
1 <= nums.length <= 4 * 10^4
1 <= nums[i] <= 10^4
*/

int maxSumDivThree(int* nums, int numsSize){ 
    int sum = 0;
    for(int i = 0; i < numsSize; i++)
        sum += nums[i];
    if(sum % 3 == 0)
        return sum;

    int mask = 1;
    int max = 0;
    for(int mask = pow(2, numsSize) - 1; mask > 0; mask--) {
        int sum = 0;
        for(int i = 0; i < numsSize; i++) {
            if(mask & (1 << i)) {
                sum += nums[i];
            }
        }
        if((sum % 3 == 0) && (sum > max))
            max = sum;
    }
    return max;
}

int main()
{
    //int arr[5] = {3,6,5,1,8};
    int arr[] = {366,809,6,792,822,181,210,588,344,618,341,410,121,864,191,749,637,169,123,472,358,908,235,914,322,946,738,754,908,272,267,326,587,267,803,281,586,707,94,627,724,469,568,57,103,984,787,552,14,545,866,494,263,157,479,823,835,100,495,773,729,921,348,871,91,386,183,979,716,806,639,290,612,322,289,910,484,300,195,546,499,213,8,623,490,473,603,721,793,418,551,331,598,670,960,483,154,317,834,352};
    printf("size %d\n", sizeof(arr));
    int ret = maxSumDivThree(arr, sizeof(arr)); 

    printf("ret %d\n", ret);
    return 0;
}
