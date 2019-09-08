#include <stdio.h>

/*
1 <= n <= 10^4
distance.length == n
0 <= start, destination < n
0 <= distance[i] <= 10^4
*/
int distanceBetweenBusStops(int* distance, int distanceSize, int start, int destination){
    int dis1 = 0, dis2 = 0;
    if(start == destination)
        return 0;
    if(start > destination) {
        int tmp = start;
        start = destination;
        destination = tmp;
    }

    for(int i = start; i < destination; i++)
        dis1 += distance[i];
    for(int i = 0; i < start; i++)
        dis2 += distance[i];
    for(int i = destination; i < distanceSize; i++)
        dis2 += distance[i];
    return ((dis1 < dis2) ? dis1:dis2);
}
/*
class Solution {
public:
    int distanceBetweenBusStops(vector<int>& d, int start, int destination) {
        int sum = 0;
        int n = d.size();
        for (int i = 0; i < n; ++ i) sum += d[i];
        int ret = 0;
        for (int i = start; i != destination; i = (i+1)%n) ret += d[i];
        return min(ret, sum-ret);
    }
};

class Solution {
public:
  int distanceBetweenBusStops(vector<int>& distance, int start, int destination) {
    vector<int> P(1);
    partial_sum(distance.begin(), distance.end(), back_inserter(P));
    if (start > destination) swap(start, destination);
    int k = P[destination] - P[start];
    return min(P.back() - k, k);
  }
};
*/

int main()
{

    return 0;
}
