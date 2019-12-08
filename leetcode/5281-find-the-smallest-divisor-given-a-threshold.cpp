#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <math.h>
using namespace std;

class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int n = nums.size();
        int l = 1, r = 1000000;
        while(l < r) {
            int mid = (l + r) / 2;
            int sum = 0;
            for(int i = 0; i < n; i++) {
                sum += ((nums.at(i) + mid - 1) / mid);
                if(sum > threshold)
                    break;
            }
            if(sum > threshold)
                l = mid + 1;
            else
                r = mid;
        }
        return l;
    }
};

int main()
{
    return 0;
}
