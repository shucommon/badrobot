#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int index;
    char c;
} resize;

char * convert(char * s, int numRows){
    resize *rs = (resize *)malloc(sizeof(resize) * strlen(s));
    memset((void *)rs, 0, sizeof(resize) * strlen(s));

    int index = 0;
    int update = 1;
    for(int i = 0; i < strlen(s); i++){
        index += update;
        rs[i].index = index;
        rs[i].c = s[i];
        if(index == numRows)
            update = -1;
        if(index == 1 && update == -1)
            update = 1;
    }

    char *ret = (char *)malloc(sizeof(char)*(strlen(s) + 1));
    char *it = ret;
    int now = 1;
    while(1){
        for(int i = 0; i < strlen(s); i++)
            if(rs[i].index == now)
                *it++ = rs[i].c;
        *it = '\0';
        now++;
        if(strlen(ret) == strlen(s))
            break;
    }
    return ret;
}

int main()
{
    char *input = "LEETCODEISHIRING";
    int num = 3;
    char *ret = convert(input, num);
    printf("%s\n", ret);

    return 0;
}
