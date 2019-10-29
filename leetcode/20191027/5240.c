/*
输入：arr = ["un","iq","ue"]
输出：4
解释：所有可能的串联组合是 "","un","iq","ue","uniq" 和 "ique"，最大长度为 4。
*/

/*
1 <= arr.length <= 16
1 <= arr[i].length <= 26
arr[i] 中只含有小写英文字母
*/

#include <stdio.h>
#include <string.h>

int maxLength(char ** arr, int arrSize){
    int max = 0;
    for(int i = 1; i < (1 << arrSize); i++) {
        int table['z' + 1] = {0};
        int size = 0;
        for(int j = 0; j < arrSize; j++)
            if((i >> j) & 1) {
                int flag = 0;
                for(int m = 0; m < strlen(arr[j]); m++) {
                    table[arr[j][m]]++;
                    if(table[arr[j][m]] > 1) {
                        flag = 1;
                        break;
                    }
                }
                if(flag) break;
                size += strlen(arr[j]); 
                max = (max > size ? max : size);
            }
    }
    return max;
}


int main()
{
    char *arr[] = {"cusy","s","imelfbpuoawkrq","roxckjm","vkaxcbespwotzq","jrnhyslwbifteqox","fnisjhckr","ubvpwtzxh","sgxkqdlw","hzsngeotfxbcm","zhrextvndpcmbql","bdfxez","rzgnbf","hbw","cohurlnjqpefzayig","xoqgyjsm"};
    char ** a = arr;
    int max = maxLength(a, 16);
    printf("max %d\n", max);

    return 0;
}
