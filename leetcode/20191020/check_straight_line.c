#include <stdio.h>
#include <stdbool.h>

bool checkStraightLine(int** coordinates, int coordinatesSize, int* coordinatesColSize){
    float k = (coordinates[1][1] - coordinates[0][1]) / (coordinates[1][0] - coordinates[0][0]);
    float b = coordinates[0][1] - k * coordinates[0][0];
    for(int i = 2; i < coordinatesSize; i++)
    {
        if((k * coordinates[i][0] + b) != coordinates[i][1])
            return false;
    }
    return true;
}

int main()
{
    return 0;
}
