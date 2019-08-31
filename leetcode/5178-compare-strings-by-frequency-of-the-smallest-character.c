#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
输入：queries = ["bbb","cc"], words = ["a","aa","aaa","aaaa"]
输出：[1,2]
解释：第一个查询 f("bbb") < f("aaaa")，第二个查询 f("aaa") 和 f("aaaa") 都 > f("cc")。

1 <= queries.length <= 2000
1 <= words.length <= 2000
1 <= queries[i].length, words[i].length <= 10
queries[i][j], words[i][j] 都是小写英文字母
*/


int alp[26] = {0};
int f(char *str)
{
    memset((char*)alp, 0, 26*sizeof(int)); 
    while(*str != '\0') {
        alp[*str++ - 'a']++;
    }    
    for(int i = 0; i < 26; i++) {
        if(alp[i])
            return alp[i]; 
    }
    return 0;
}

void quick_sort(int arr[], int s, int e)
{
    if(s >= e)
        return;

    int l = s, r = e;
    int base = arr[l];
    while(l < r) {
        while(l < r && arr[r] >= base)
            r--;
        if(l < r)
            arr[l++] = arr[r];

        while(l < r && arr[l] <= base)
            l++;
        if(l < r)
            arr[r--] = arr[l];
    }
    arr[l] = base;
    quick_sort(arr, s, l - 1);
    quick_sort(arr, l + 1, e);
}

int get_count(int *words_len, int wordsSize, int querey)
{
    for(int i = 0; i < wordsSize; i++)
        if(words_len[i] > querey)
            return wordsSize - i;
    return 0;

/*
    int l = 0, r = wordsSize - 1;
    while(l <= r) {
        int mid = (l + r)/2;
        if(words_len[mid] == querey)
            return wordsSize - mid - 1;
        else if(words_len[mid] > querey)
            r = mid - 1;
        else if(words_len[mid] < querey)
            l = mid + 1;
    }
    return wordsSize - l;
*/
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* numSmallerByFrequency(char ** queries, int queriesSize, char ** words, int wordsSize, int* returnSize){
    int *words_len = (int *)malloc(sizeof(int) * wordsSize); 
    memset((char*)words_len, 0, wordsSize * sizeof(int));
    for(int i = 0; i < wordsSize; i++)
        words_len[i] = f(words[i]);
    quick_sort(words_len, 0, wordsSize - 1);

    int *ret_arr = (int *)malloc(sizeof(int) * queriesSize);
    memset((char*)ret_arr, 0, queriesSize * sizeof(int));
    for(int i = 0; i < queriesSize; i++) {
        int len = f(queries[i]); 
        ret_arr[i] = get_count(words_len, wordsSize, len);    
    }
    *returnSize = queriesSize;
    return ret_arr;
}

int main()
{
    int queriesSize = 2;
    int wordsSize = 4;
    char ** queries = (char **)malloc(sizeof(char *) * 2);
    char a[4] = "bbb";
    char b[3] = "cc";
    queries[0] = a;
    queries[1] = b;
    char ** words = (char **)malloc(sizeof(char *) * 4);
    char c[2] = "a";
    char d[3] = "aa";
    char e[4] = "aaa";
    char f[5] = "aaaa";
    words[0] = c;
    words[1] = d;
    words[2] = e;
    words[3] = f;
    int ret_size = 0;
    int *ret = numSmallerByFrequency(queries, queriesSize, words, wordsSize, &ret_size);
    for(int i = 0; i < ret_size; i++)
        printf("len %d\n", ret[i]);

    return 0;
}
