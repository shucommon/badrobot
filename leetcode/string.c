#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char * test( char ** dic, int size, char *sentence)
{
    int cnt = 1;
    char *it = sentence;
    while(*it) {
        if(*it == ' ') {
            while(*it == ' ')
                it++;
            cnt++;
        }
        it++;
    }

    char ** arr = (char **)malloc(sizeof(char *) * cnt);
    int n = 0;
    int len = 0;
    char tmp[1001];
    while(sscanf(sentence + len, "%s ", tmp) != EOF) {
        arr[n] = (char *)malloc(sizeof(char) * (strlen(tmp) + 1));
        strcpy(arr[n], tmp);
        n++;
        len += (strlen(tmp) + 1);
    }

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < n; j++) {
            char *index;
            if(((index = strstr(arr[j], dic[i])) != NULL) && (index == &arr[j][0])) {
                strcpy(arr[j], dic[i]);
            }
        }
    }

    int l = 0;
    char *ret = (char *)malloc(sizeof(char) * 1001001);
    for(int i = 0; i < cnt; i++) {
        strcpy(ret + l, arr[i]);
        l += strlen(arr[i]);
        if(i < n - 1) {
            *(ret + l) = ' ';
            l++;
        }
    }
    *(ret + l) = '\0';

    return ret;
}

int main()
{
    char ** dic = (char **)malloc(sizeof(char *) * 3);
    dic[0] = "cat";
    dic[1] = "bat";
    dic[2] = "rat";
    int size = 3;
    char *sen = "the cattle was rattled by the battery";
    char *ret = test(dic, size, sen);
    printf("%s\n", ret);

    return 0;
}
