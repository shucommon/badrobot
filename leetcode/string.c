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
    printf("cnt %d\n", cnt);

    char ** arr = (char **)malloc(sizeof(char *) * cnt);
    int n = 0;
    int len = 0;
    char tmp[1001];
    while(sscanf(sentence + len, "%s ", tmp) != EOF) {
        arr[n] = (char *)malloc(sizeof(char) * (strlen(tmp) + 1));
        strcpy(arr[n], tmp);
        printf("%s\n", arr[n]);
        n++;
        len += (strlen(tmp) + 1);
    }

    for(int i = 0; i < size; i++) {
    }


    char *ret;
    return ret;
}

int main()
{
    char ** dic = (char **)malloc(sizeof(char *) * 3);
    dic[0] = "abc"; 
    dic[1] = "def"; 
    dic[2] = "xyz"; 
    int size = 10;
    char *sen = "abcd defg xyza";
    char *ret = test(dic, size, sen);

    return 0;
}
