/*
1、 记录最多8条错误记录，循环记录，对相同的错误记录（净文件名称和行号完全匹配）只记录一条，错误计数增加；
2、 超过16个字符的文件名称，只记录文件的最后有效16个字符；
3、 输入的文件可能带路径，记录文件名称不能带路径。

in:
一行或多行字符串。每行包括带路径文件名称，行号，以空格隔开。
out:
将所有的记录统计并将结果输出，格式：文件名 代码行数 数目，一个空格隔开，如：

E:\V1R2\product\fpgadrive.c   1325
输出
fpgadrive.c 1325 1
*/
#include <stdio.h>
#include <string.h>

typedef struct {
    char fn[17];
    int line;
    int cnt;
} err_rc;

char * get_file(char *in)
{
    char *s = in, *e = in;
    while(*e != '\0') {
        if(*e == '\\') {
            s = e+1;
        }
        e++;
    }
    int len;
    if((len = strlen(s)) > 16)
        s += (len - 16);
    return s;
}

void insert(char *p, int line, int *index, err_rc *er)
{
    for(int i = 0; i < *index; i++)
    {
        if(er[i].cnt != 0 && er[i].line == line && strcmp(er[i].fn, p) == 0)
        {
            er[i].cnt++;
            return;
        }
    }
    er[*index].line = line;
    er[*index].cnt = 1;
    strcpy(er[*index].fn, p);
    (*index)++;
}

int main()
{
    char in[128];
    char *p = in;
    int line;
    err_rc er[100];
    int index = 0;

    while(scanf("%s %d", in, &line) != EOF)
    {
        p = get_file(in);
        insert(p, line, &index, er);
    }
    int a = (index > 8 ? index - 8 : 0);
    for(int i = a; i < index; i++)
    {
        if(er[i].cnt != 0)
            printf("%s %d %d\n", er[i].fn, er[i].line, er[i].cnt);
    }
    

    return 0;
}
