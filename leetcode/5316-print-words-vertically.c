#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** printVertically(char* s, int* returnSize){
    int sub[200] = {0}, sube[200] = {0};
    char *it = s;
    int index = 0, max = 0;
    while(*it) {
        if(*it == ' ') {
            sube[index] = it - s - 1;
            max = max > (sube[index] - sub[index] + 1) ? max : (sube[index] - sub[index] + 1);
            index++;
            sub[index] = it - s + 1;
        } 
        it++;
    }
    sube[index] = it - s - 1;
    max = max > (sube[index] - sub[index] + 1) ? max : (sube[index] - sub[index] + 1);

    char **ret = (char **)malloc(sizeof(char *) * max);
    *returnSize = max;
    for(int i = 0; i < max; i++) {
        ret[i] = (char *)malloc(sizeof(char) * (index + 2));
    }

    for(int i = 0; i < max; i++) {
        for(int j = 0; j <= index; j++) {
            if(sub[j] + i > sube[j])
                ret[i][j] = ' ';        
            else
                ret[i][j] = s[sub[j] + i];        
        }
        printf("%s\n", ret[i]);
    }
    for(int i = 0; i < max; i++) {
        int j = index;
        while(ret[i][j--] == ' ');
        ret[i][j+2] = '\0';
    }
    return ret;
}

int main()
{
    char s[] = "HOW ARE YOU";
    int rs;
    char** ret = printVertically(s, &rs);

    return 0;
}
