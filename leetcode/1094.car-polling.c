/*
输入：trips = [[3,2,7],[3,7,9],[8,3,9]], capacity = 11
输出：true

你可以假设乘客会自觉遵守 “先下后上” 的良好素质
trips.length <= 1000
trips[i].length == 3
1 <= trips[i][0] <= 100
0 <= trips[i][1] < trips[i][2] <= 1000
1 <= capacity <= 100000

*/

#include <stdio.h>
#include <stdbool.h>

bool carPooling(int** trips, int tripsSize, int* tripsColSize, int capacity){
    int psgn[1001] = {0};
    int sum = 0;

    for(int i = 0; i < tripsSize; i++) {
        psgn[trips[i][1]] += trips[i][0];
        psgn[trips[i][2]] -= trips[i][0];
    }

    for(int i = 0; i < 1001; i++) {
        if(psgn[i] == 0)
            continue;

        sum += psgn[i];
        if(sum > capacity)
            return false;
    }
    return true;
}

int main()
{

    return 0;
}
