#include <stdio.h>
#include <string.h>

int numJewelsInStones(char * J, char * S){
    int cnt = 0;
    unsigned char arr['z' + 1] = { 0 };
    for(int i = 0; i < strlen(S); i++) {
        arr[S[i]]++;
    }
    for(int i = 0; i < strlen(J); i++) {
        cnt += arr[J[i]];
    }
    return cnt;
}

int main()
{
    int ret = numJewelsInStones("aA", "aAAbbbb");
    printf("ret %d\n", ret);
    return 0;
}
