/*
编写一个程序，将输入字符串中的字符按如下规则排序。
规则 1 ：英文字母从 A 到 Z 排列，不区分大小写。
       如，输入： Type   输出： epTy
规则 2 ：同一个英文字母的大小写同时存在时，按照输入顺序排列。
     如，输入： BabA   输出： aABb
规则 3 ：非英文字母的其它字符保持原来的位置。
     如，输入： By?e   输出： Be?y

样例：
    输入：
   A Famous Saying: Much Ado About Nothing(2012/8).
    输出：
   A  aaAAbc   dFgghh :  iimM   nNn   oooos   Sttuuuy  (2012/8).
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void sort_puple(char *in, int len)
{
    for(int i = 0; i < len - 1; i++) {
        for(int j = 0; j < len - i - 1; j++) {
            if(!isalpha(in[j]))
                continue;
            int m = j + 1;
            while(m < len && !isalpha(in[m]))
                m++;
            if(m == len)
                break;
            if(toupper(in[j]) > toupper(in[m])) {
                char tmp = in[j];
                in[j] = in[m];
                in[m] = tmp;
            }
        }
    }
}

void sort(char *in, int left, int right)
{
    if(left >= right)
        return;

    int l = left, r = right;
    while(l < r && !isalpha(in[l]))
        l++;
    if(l == r)
        return;

    char base = in[l];
    while(l < r) {
        if(!isalpha(in[r])) {
            r--; 
            continue;
        }
        while(l < r && toupper(in[r]) >= toupper(base)) {
            r--;
            while(l < r && !isalpha(in[r]))
                r--;
            if(l == r) {
                in[l] = base;
                goto end;
            }
        }
        if(l < r)
            in[l++] = in[r];

        while(l < r && !isalpha(in[l]))
            l++;
        if(l == r) {
            in[r] = base;
            goto end;
        }

        while(l < r && toupper(in[l]) <= toupper(base)) {
            l++;
            while(l < r && !isalpha(in[l]))
                l++;
            if (l == r) {
                in[r] = base;
                goto end;
            }
        }
        if(l < r)
            in[r--] = in[l];
    }
    in[l] = base;
    end:
    sort(in, left, l - 1);
    sort(in, l + 1, right);
}

int main()
{
    char in[1024];
    char *p = in;
    //while(scanf("%s", in) != EOF)
    while(gets(in) != NULL)
    {
        int len = strlen(in);
        sort_puple(in, len);
        printf("%s\n", in);
        //sort(in, 0, len-1);
        //printf("%s\n", in);
    }
    return 0;
}
