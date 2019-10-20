#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_str(char ** arr, int size)
{
    for(int i = 0; i < size; i++)
        printf("%s\n", arr[i]);
}

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

int is_subfolder(char *s, char *d)
{
    int i = 0;
    while(s[i] == d[i])
        i++;
    if((i == strlen(s)) &&(i < strlen(d)) && (d[i] == '/'))
        return 1;
    return 0;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** removeSubfolders(char ** folder, int folderSize, int* returnSize){
    int rlen = 1;
    for(int i = 0; i < folderSize - 1; i++) {
        if(!is_subfolder(folder[0], folder[i+1]))
            folder[rlen++] = folder[i+1];
    }
    folderSize = rlen; 
    if(folderSize == 1) {
        char ** ret = (char **)malloc(sizeof(char *));
        *ret = folder[0];
        *returnSize = 1;
        return ret;
    }

    quick_sort(folder, 0, folderSize - 1);
 
    int len = 0;
    char ** ret = (char **)malloc(sizeof(char *) * folderSize);
    for(int i = 0; i < folderSize;) {
        ret[len++] = folder[i]; 
        int j = i+1;
        while(is_subfolder(folder[i], folder[j]) && j < folderSize - 1)
            j++;
        if(j == folderSize - 1) {
            if(!is_subfolder(folder[i], folder[j]))
                ret[len++] = folder[j];
            break;
        }
        i = j;
    }
    *returnSize = len;
    return ret;
}

int main()
{
    char ** arr = (char **)malloc(sizeof(char *) * 5);
    arr[0] = "/a";
    arr[1] = "/a/b";
    arr[2] = "/c/d";
    arr[3] = "/c/d/e";
    arr[4] = "/c/f";
    int retsize = 0;
    char ** ret = removeSubfolders(arr, 5, &retsize);
    printf("retsize %d\n", retsize);
    
    return 0;
}
