int min_time(int *p1, int *p2)
{
    int a = abs(p1[0] - p2[0]); 
    int b = abs(p1[1] - p2[1]); 
    return ( a > b ? a : b);
}

int minTimeToVisitAllPoints(int** points, int pointsSize, int* pointsColSize){
    int time = 0;
    for(int i = 0; i < pointsSize - 1; i++) {
        time += min_time(points[i], points[i + 1]);
    }
    return time;
}
