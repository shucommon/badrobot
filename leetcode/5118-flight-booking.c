#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
1 <= bookings.length <= 20000
1 <= bookings[i][0] <= bookings[i][1] <= n <= 20000
1 <= bookings[i][2] <= 10000
*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
/*
int* corpFlightBookings(int** bookings, int bookingsSize, int* bookingsColSize, int n, int* returnSize){
    int * ret = (int *)malloc(sizeof(int) * n);
    memset((char*)ret, 0, n*sizeof(int));

    for(int i = 0; i < bookingsSize; i++)
        for(int j = bookings[i][0]; j <= bookings[i][1]; j++)
            ret[j-1] += bookings[i][1];

    *returnSize = n;
    return ret;

}
*/

int* corpFlightBookings(int** bookings, int bookingsSize, int* bookingsColSize, int n, int* returnSize){
    int * ret = (int *)malloc(sizeof(int) * n);
    memset((char*)ret, 0, n*sizeof(int));

    for(int i = 0; i < bookingsSize; i++) {
        ret[bookings[i][0] - 1] += bookings[i][2];
        if(bookings[i][1] < n)
            ret[bookings[i][1]] -= bookings[i][2];
    }

    for(int i = 0; i < n - 1; i++)
        ret[i+1] += ret[i];
     
    *returnSize = n;
    return ret;

}

int main()
{
    int **in;
    int *tmp = (int *)malloc(sizeof(int) * 3);
    tmp[0] = 1;
    tmp[1] = 2;
    tmp[2] = 10;
    in[0] = tmp;

    tmp = (int *)malloc(sizeof(int) * 3);
    tmp[0] = 2;
    tmp[1] = 3;
    tmp[2] = 20;
    in[1] = tmp;

    tmp = (int *)malloc(sizeof(int) * 3);
    tmp[0] = 2;
    tmp[1] = 5;
    tmp[2] = 25;
    in[2] = tmp;

    int retsize = 0;
    int col = 3;
    int *a = corpFlightBookings(in, 3, &col, 5, &retsize);
    for(int i = 0; i < retsize; i++)
        printf("%d ", a[i]);

    return 0;
}
