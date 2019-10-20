/*
ID: qianggu1 
LANG: C
TASK: beads 
*/
#include <stdio.h>
#include <stdlib.h>

int main () {
    FILE *fin  = fopen ("beads.in", "r");
    FILE *fout = fopen ("beads.out", "w");
    int a;
    fscanf (fin, "%d", &a);
    char *b = (char *)malloc(sizeof(char) * (2*a + 1));
    fscanf (fin, "%s", b);

    for(int i = 0; i < a; i++)
        b[a+i] = b[i];
    b[2*a] = '\0';

    int rb = 0, index = 0, cnt = 0, max = 0;
    char tmp = 'x';
    for(int i = 0; i < 2 * a; i++) {
        cnt++;
        if((b[i] == 'r' || b[i] == 'b')) {
            if(rb == 0) {
                index = i;
                rb++;
                tmp = b[i];
            } else if(rb == 1 && b[i] == tmp) {
                index = i;
            } else if(rb == 1 && b[i] != tmp) {
                rb++;
            } else if(rb == 2 && b[i] == tmp) {
                rb = 0;
                i = index; 
                cnt -= 1;
                max = (cnt > max ? cnt : max);
                cnt = 0;
                if(i+1 >= a)
                    break;
            }
        }
        if(rb != 2 && i >= a) {
            cnt--;
            break;
        }
    }
    max = (cnt > max ? cnt : max);
    max = (max > a ? a : max);
        
    fprintf (fout, "%d\n", max);

    return 0;
}
