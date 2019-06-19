/*
开发一个坐标计算工具， A表示向左移动，D表示向右移动，W表示向上移动，S表示向下移动。从（0,0）点开始移动，从输入字符串里面读取一些坐标，并将最终输入结果输出到输出文件里面。
输入：
合法坐标为A(或者D或者W或者S) + 数字（两位以内）
坐标之间以;分隔。o
A10;S20;W10;D30;X;A1A;B10A11;;A10;
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} point;

int validate(char *a, int len)
{
    int good = 0;
    if(len < 2 || len > 3)
        return 0;

    if(a[1] >= '0' && a[1] <= '9')
        good = 1;

    if(len == 3)
    {
        if(a[2] >= '0' && a[2] <= '9' && good)
            return 1;
        else
            return 0;
    }

    return good; 
}

int main()
{
    char a[10];
    int i = 0;
    int step = 0;
    point pt;
    pt.x = 0;
    pt.y = 0;
    
    while((a[i] = getchar()) != EOF) {
        if(a[i] == '\n'){
            i = 0;
            printf("%d,%d\n", pt.x, pt.y);
            pt.x = 0;
            pt.y = 0;
            continue;
        }

        if(a[i] != ';') {
            i++;
            continue;
        } else {
            a[i] = '\0';
            if(!validate(a, i)) {
                i = 0;
                continue;
            }
            step = atoi(&a[1]);
            switch(a[0]) {
                case 'A':
                    pt.x -= step;
                    break;
                case 'D':
                    pt.x += step;
                    break;
                case 'W':
                    pt.y += step;
                    break;
                case 'S':
                    pt.y -= step;
                    break;
                default:
                    break;
            }
            i = 0;
        }
    }

    return 0;
}

