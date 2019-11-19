#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_brother(char *target, char *to_find)
{
    if(strcmp(target, to_find) == 0)
        return 0;
    if(strlen(target) != strlen(to_find))
        return 0;
    
    int table[26] = {0};
    int table1[26] = {0};
    for(int i = 0; i < sizeof(target); i++)
        table[target[i] - 'a']++;
    for(int i = 0; i < sizeof(to_find); i++)
        table1[to_find[i] - 'a']++;
    for(int i = 0; i < 26; i++){
        if(table[i] != table1[i])
            return 0;
    }
    return 1;
}

void q_sort(char **arr, int s, int e)
{
    int l = s, r = e;
    if(l >= r)
        return;
    char *base = arr[l];
    while(l < r){
        while((l < r) && (strcmp(base, arr[r]) <= 0))
            r--;
        if(l<r)
            arr[l++] = arr[r];
        while((l < r) && (strcmp(arr[l], base) <= 0))
            l++;
        if(l<r)
            arr[r--] = arr[l];
    }
    arr[l] = base;
    q_sort(arr, s, l-1);
    q_sort(arr, l+1, e);
}

int main()
{
    int n, id;
    char find[51];
    char *finding = NULL;
    while(scanf("%d", &n) != EOF) {
        char **arr = (char **)malloc(sizeof(char *) * n);
        for(int i = 0; i < n; i++) {
            char tmp[51];
            scanf("%s", tmp);
            arr[i] = (char *)malloc(sizeof(char) * (strlen(tmp)+1));
            strncpy(arr[i], tmp, strlen(tmp) + 1);
        }
        q_sort(arr, 0, n - 1);
        scanf("%s", find);
        scanf("%d", &id);
        int cnt = 0;
        for(int i = 0; i < n; i++){
            if(is_brother(arr[i], find)){
                cnt++;
                if(cnt == id)
                    finding = arr[i];
            }
        }
        printf("%d\n", cnt);
        if(id <= cnt) {
            printf("%s\n", finding);
        }
        finding = NULL;
    }

    return 0;
}
