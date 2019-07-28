/*
从R依次中取出R<i>，对I进行处理，找到满足条件的I<j>： 
I<j>整数对应的数字需要连续包含R<i>对应的数字。比如R<i>为23，I<j>为231，那么I<j>包含了R<i>，条件满足 。
(1)先输出R<i>； 
(2)再输出满足条件的I<j>的个数； 
(3)然后输出满足条件的I<j>在I序列中的位置索引(从0开始)； 
(4)最后再输出I<j>。
附加条件： 
(1)R<i>需要从小到大排序。相同的R<i>只需要输出索引小的以及满足条件的I<j>，索引大的需要过滤掉 
(2)如果没有满足条件的I<j>，对应的R<i>不用输出 
(3)最后需要在输出序列的第一个整数位置记录后续整数序列的个数(不包含“个数”本身)
序列I：15,123,456,786,453,46,7,5,3,665,453456,745,456,786,453,123（第一个15表明后续有15个整数） 
序列R：5,6,3,6,3,0（第一个5表明后续有5个整数） 
输出：30, 3,6,0,123,3,453,7,3,9,453456,13,453,14,123,6,7,1,456,2,786,4,46,8,665,9,453456,11,456,12,786
input:
15 123 456 786 453 46 7 5 3 665 453456 745 456 786 453 123
5 6 3 6 3 0
output:
30 3 6 0 123 3 453 7 3 9 453456 13 453 14 123 6 7 1 456 2 786 4 46 8 665 9 453456 11 456 12 786
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quick_sort(int *arr, int left, int right)
{
    if(left >= right)
        return;

    int l = left, r = right;
    int base = arr[l];
    while(l < r) {
        while(l < r && arr[r] > base)
            r--;
        if(l < r)
            arr[l++] = arr[r];
        while(l < r && arr[l] < base)
            l++;
        if(l < r)
            arr[r--] = arr[l];
    }
    arr[l] = base;
    quick_sort(arr, left, l - 1);
    quick_sort(arr, l + 1, right);
}

int i_contain_r(int i, int r) 
{
/*
    char ii[11] = {'\0'}, rr[11] = {'\0'};
    
    int index=0;
    while(i) {
        ii[index++] = (i%10) + '0';
        i /= 10;
    }
    ii[index] = '\0';
    if(r == 0)
        rr[0] = '0';
    else {
        index=0;
        while(r) {
            rr[index++] = (r%10) + '0';
            r /= 10;
        }
        rr[index] = '\0';
    }

    char *p;
    if((p = strstr(ii, rr)) != NULL)
    {
        printf("found %s\n", p);
        return 1;
    }
    return 0;
*/

    if(i == 0 && r == 0)
        return 1;

    while(i > 0) {
        char ic = i % 10;
        int rr = r;
        char rc = rr % 10;
        while(ic != rc && i > 0) {
            i /= 10;
            ic = i % 10;
        }
        if(i == 0)
            return 0;

        while(ic == rc && i > 0 && rr > 0) {
            i /= 10;
            ic = i % 10;
            rr /= 10;
            rc = rr % 10;
        }
        if(rr == 0)
            return 1;
    }

    return 0;
}

int main()
{
    int *R, *I, ni, nr;
    int *out;
    while(scanf("%d", &ni) != EOF) {
        I = (int *)malloc(sizeof(int)*ni);
        for(int i = 0; i < ni; i++)
            scanf("%d", I + i);

        scanf("%d", &nr);
        R = (int *)malloc(sizeof(int)*nr);
        for(int i = 0; i < nr; i++)
            scanf("%d", R + i);
        quick_sort(R, 0, nr - 1);
        out = (int *)malloc(sizeof(int) * (ni * nr * 2 + 2*nr + 1));
        int index = 1;
        int cur = R[0], pre = R[0] + 1;
        int total = 0;
        for(int i = 0; i < nr; i++) {
            cur = R[i];
            if(cur != pre) {
                out[index++] = R[i];
                out[index++] = 0;
                //printf("search %d:\n", R[i]);
                int found = 0;
                for(int j = 0; j < ni; j++) {
                    if(i_contain_r(I[j], R[i])) {
                        found++;
                        //printf("I[%d]=%d contain R[%d]=%d\n", j, I[j], i, R[i]);
                        out[index++] = j;
                        out[index++] = I[j];
                    }
                }
                if(found) {
                    out[index - 2*found - 1] = found;
                    total += found * 2 + 2;
                } else {
                    index -= 2;
                }
            }
            pre = R[i];
        }
        out[0] = total;
        for(int i = 0; i <= total; i++) {
            printf("%d", out[i]);
            if(i == total)
                printf("\n");
            else
                printf(" ");
        }

    }

    return 0;
}
