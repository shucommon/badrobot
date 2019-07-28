#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
我们从一块字母板上的位置 (0, 0) 出发，该坐标对应的字符为 board[0][0]。

在本题里，字母板为board = ["abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"].

我们可以按下面的指令规则行动：

如果方格存在，'U' 意味着将我们的位置上移一行；
如果方格存在，'D' 意味着将我们的位置下移一行；
如果方格存在，'L' 意味着将我们的位置左移一列；
如果方格存在，'R' 意味着将我们的位置右移一列；
'!' 会把在我们当前位置 (r, c) 的字符 board[r][c] 添加到答案中。
返回指令序列，用最小的行动次数让答案和目标 target 相同。你可以返回任何达成目标的路径。
1 <= target.length <= 100
target 仅含有小写英文字母。
*/
char board[6][5] = {"abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"};

char * alphabetBoardPath(char * target){
    //char board[6][5] = {"abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"};
    int cur_x = 0;
    int cur_y = 0;
    char *ret = (char*)malloc(sizeof(char)*4096);
    int index = 0;
    while(*target) {
        int x = (*target - 'a') % 5;
        int y = (*target - 'a') / 5;
        char x_move, y_move;
        int x_n = 0, y_n = 0;
        if(y > cur_y) {
            y_n = y - cur_y;
            y_move = 'D';
        } else {
            y_n = cur_y - y;
            y_move = 'U';
        }
        if(x > cur_x) {
            x_n = x - cur_x;
            x_move = 'R';
        } else {
            x_n = cur_x - x;
            x_move = 'L';
        }
        if(y == 5 && cur_y != 5) {
            for(int i = 0; i < y_n - 1; i++)
                ret[index++] = y_move;
            for(int i = 0; i < x_n; i++)
                ret[index++] = x_move;
            ret[index++] = y_move;
        } else {
            for(int i = 0; i < y_n; i++)
                ret[index++] = y_move;
            for(int i = 0; i < x_n; i++)
                ret[index++] = x_move;
        }
        ret[index++] = '!';
        cur_x = x;
        cur_y = y;
        target++;
    }
    ret[index] = '\0';
    return ret;
}

int main()
{
    char * ret = alphabetBoardPath("leet");
    printf("%s\n", ret);
    ret = alphabetBoardPath("zdz");
    printf("%s\n", ret);
    return 0;
}
