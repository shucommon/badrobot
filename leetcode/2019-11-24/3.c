#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quick_sort(char **arr, int s, int e)
{
    if(s >= e)
        return;

    int l = s, r = e;
    char *base = arr[l];
    while(l < r) {
        while(l < r && strcmp(arr[r], base) >= 0)
            r--;
        if(l < r)
            arr[l++] = arr[r];

        while(l < r && strcmp(arr[l], base) <= 0)
            l++;
        if(l < r)
            arr[r--] = arr[l];
    }
    arr[l] = base;
    quick_sort(arr, s, l - 1);
    quick_sort(arr, l + 1, e);
}

int have_same_pre(char *v, char *k, int n)
{
    while(*v && *k && n) {
        if(*v++ != *k++)
            return 0;
        n--;
    }
    if(n > 0)
        return 0;
    return 1;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char *** suggestedProducts(char ** products, int productsSize, char * searchWord, int* returnSize, int** returnColumnSizes){
    quick_sort(products, 0, productsSize - 1);
    char ***ret = (char ***)malloc(sizeof(char **) * strlen(searchWord));
    *returnColumnSizes = (int *)malloc(sizeof(int) * strlen(searchWord));

    for(int i = 0; i < strlen(searchWord); i++) {
        ret[i] = (char **)malloc(sizeof(char *) * 3);
        int cnt = 0;
        for(int j = 0; j < productsSize; j++) {
            if(have_same_pre(searchWord, products[j], i + 1)) {
                ret[i][cnt] = (char *)malloc(sizeof(char) * (strlen(products[j]) + 1));
                strcpy(ret[i][cnt++], products[j]);
                if(cnt == 3)
                    break;
            }
        }
        (*returnColumnSizes)[i] = cnt; 
    }
    *returnSize = strlen(searchWord);

    return ret;
}

int main()
{
    char *pro[5] = {"mobile","mouse","moneypot","monitor","mousepad"};
    int size = 5;
    char *search = "mouse";
    int rs = 0;
    int *rcs = NULL;
    char *** ret = suggestedProducts(pro, size, search, &rs, &rcs);
    for(int i = 0; i < rs; i++) {
        for(int j = 0; j < rcs[i]; j++)
            printf("%s\n", ret[i][j]);
        printf("\n");
    }

    return 0;
}

/*
输入：products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
输出：[
["mobile","moneypot","monitor"],
["mobile","moneypot","monitor"],
["mouse","mousepad"],
["mouse","mousepad"],
["mouse","mousepad"]
]
解释：按字典序排序后的产品列表是 ["mobile","moneypot","monitor","mouse","mousepad"]
输入 m 和 mo，由于所有产品的前缀都相同，所以系统返回字典序最小的三个产品 ["mobile","moneypot","monitor"]
输入 mou， mous 和 mouse 后系统都返回 ["mouse","mousepad"]
*/
