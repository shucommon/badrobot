#include <stdio.h>
#include <stdlib.h>

/* 最小值、最大值、平均值、中位数和众数 */
/* [0,1,3,4,0] */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
double* sampleStats(int* count, int countSize, int* returnSize){
    int min, max, max_cnt = 0, cnt = 0, most = 0;
    long sum = 0;
    double *ret;
    double middle;

    int i = 0;
    while(count[i++] == 0);
    min = i - 1;

    i = countSize - 1;
    while(count[i--] == 0);
    max = i + 1;

    for(i = min; i <= max; i++) {
        if(count[i] != 0) {
            cnt += count[i];
            sum += i * count[i];
            if(max_cnt < count[i]) {
                max_cnt = count[i];
                most = i;
            }
        }
    }
    
    
    if(cnt % 2 == 0) {
        int mid1 = cnt/2 - 1, mid2 = cnt/2, tmp_cnt=0;
        unsigned char found = 0;
        for(i = min; i <= max; i++){
            if(count[i] != 0) {
                if(found){
                    middle += (double)i;
                    middle /= 2.0;
                    break;
                }
                tmp_cnt += count[i];
                if(tmp_cnt < mid1) {
                    continue;
                } else if(tmp_cnt > mid2 ){
                    middle = (double)i;
                    break;
                } else {
                    found = 1;
                    middle = (double)i;
                }
            }
        }
    } else {
        int mid = (cnt - 1)/2, tmp_cnt = 0;
        for(i = min; i <= max; i++){
            if(count[i] != 0) {
                tmp_cnt += count[i];
                if(tmp_cnt < mid) {
                    continue;
                } else {
                    middle = (double)i;
                    break;
                }
            }
        }
    }
    ret = (double *)malloc(sizeof(double) * 5);
    ret[0] = (double)min;
    ret[1] = (double)max;
    ret[2] = (double)sum/(double)cnt;
    ret[3] = (double)middle;
    ret[4] = (double)most;
    *returnSize = 5;

    return ret;
}


int main()
{
    int count[] = {264,912,1416,1903,2515,3080,3598,4099,4757,5270,5748,6451,7074,7367,7847,8653,9318,9601,10481,10787,11563,11869,12278,12939,13737,13909,14621,15264,15833,16562,17135,17491,17982,18731,19127,19579,20524,20941,21347,21800,22342,21567,21063,20683,20204,19818,19351,18971,18496,17974,17677,17034,16701,16223,15671,15167,14718,14552,14061,13448,13199,12539,12265,11912,10931,10947,10516,10177,9582,9102,8699,8091,7864,7330,6915,6492,6013,5513,5140,4701,4111,3725,3321,2947,2357,1988,1535,1124,664,206,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    int retsize;
    double* rec =  sampleStats(count, sizeof(count)/sizeof(int), &retsize);
    
    printf("%f %f %f %f %f\n", rec[0], rec[1], rec[2], rec[3], rec[4]);
    return 0;
}
