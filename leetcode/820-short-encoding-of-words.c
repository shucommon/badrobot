#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int reverse_cmp(char *s, char *d)
{
    int len1 = strlen(s) - 1;
    int len2 = strlen(d) - 1;
    while(len1 >= 0 &&  len2 >= 0) {
        if(*(s+len1) > *(d + len2))
            return 1;
        else if(*(s+len1) < *(d + len2))
            return -1;
        len1--;
        len2--;
    }
    return (len1 - len2);
}

int in(char *s, char *d)
{
    int len1 = strlen(s) - 1;
    int len2 = strlen(d) - 1;
    while(len1 >= 0 &&  len2 >= 0) {
        if(*(s+len1) != *(d + len2))
            return 0;
        len1--;
        len2--;
    }
    return 1;
}

void quick_sort(char **arr, int s, int e)
{
    if(s >= e)
        return;

    int l = s, r = e;
    char *base = arr[l];
    while(l < r) {
        while(l < r && reverse_cmp(arr[r], base) >= 0)
            r--;
        if(l < r)
            arr[l++] = arr[r];

        while(l < r && reverse_cmp(arr[l], base) <= 0)
            l++;
        if(l < r)
            arr[r--] = arr[l];
    }
    arr[l] = base;
    quick_sort(arr, s, l - 1);
    quick_sort(arr, l + 1, e);
}

int minimumLengthEncoding(char ** words, int wordsSize){
    quick_sort(words, 0, wordsSize - 1);

    int cnt = strlen(words[0]), max = strlen(words[0]) + 1, last = 0;
    for(int i = 1; i < wordsSize; i++) {
        if(in(words[i-1], words[i])) {
            max -= (cnt + 1);
        }
        max += strlen(words[i]) + 1; 
        cnt = strlen(words[i]); 
    }
    return max;
}

int main()
{
    char ** words = (char **) malloc(sizeof(char *) * 3);
    words[0] = "time";
    words[1] = "me";
    words[2] = "bell";
    int max = minimumLengthEncoding(words, 3);
    printf("max %d\n", max);

    return 0;
}
