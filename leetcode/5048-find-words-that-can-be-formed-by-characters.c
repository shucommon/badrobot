/*
给你一份『词汇表』（字符串数组） words 和一张『字母表』（字符串） chars。
假如你可以用 chars 中的『字母』（字符）拼写出 words 中的某个『单词』（字符串），那么我们就认为你掌握了这个单词。
注意：每次拼写时，chars 中的每个字母都只能用一次。
返回词汇表 words 中你掌握的所有单词的 长度之和

输入：words = ["cat","bt","hat","tree"], chars = "atach"
输出：6
解释： 
可以形成字符串 "cat" 和 "hat"，所以答案是 3 + 3 = 6

1 <= words.length <= 1000
1 <= words[i].length, chars.length <= 100
所有字符串中都仅包含小写英文字母

*/
#include <stdio.h>
#include <string.h>

int countCharacters(char ** words, int wordsSize, char * chars){
    int cnt = 0;

    for(int i = 0; i < wordsSize; i++) {
        char *p = words[i];
        int len = strlen(p);
        int len1 = len;
        char *c = chars;
        while(*c && len) {
            char *f = strchr(p, *c);
            if(f) {
                *f = *(p + len - 1);
                *(p + len - 1) = '\0';
                len--;
            }
            c++;
        }
        if(len == 0)
            cnt += len1;
    }
    return cnt;
}



int main()
{
    return 0;
}
