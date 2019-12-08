#include <iostream>
#include <vector>
using namespace std;
/*
groupSizes.length == n
1 <= n <= 500
1 <= groupSizes[i] <= n
*/
/*
输入：groupSizes = [3,3,3,3,3,1,3]
输出：[[5],[0,1,2],[3,4,6]]
解释： 
其他可能的解决方案有 [[2,1,6],[5],[0,4,3]] 和 [[5],[0,6,2],[4,3,1]]。
*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
/*
int** groupThePeople(int* groupSizes, int groupSizesSize, int* returnSize, int** returnColumnSizes){
    int *arr = (int *)malloc(sizeof(int) * groupSizesSize);
    memset(arr, 0, sizeof(int) * groupSizesSize);

    for(int i = 0; i < groupSizesSize; i++) {

    } 
}
*/
class Solution {
public:
    vector<vector<int> > groupThePeople(vector<int>& groupSizes) {
        int n = groupSizes.size();
        vector<vector<int> > ret;
        int arr[501] = {0};
        vector<int> one[501];
        for(int i = 0; i < n; i++) {
            if(groupSizes[i] == 1) {
                ret.push_back(vector<int> (1, i));
                continue;
            }
            one[groupSizes[i]].push_back(i);
            if(arr[groupSizes[i]] == 0) {
                arr[groupSizes[i]] = groupSizes.at(i) - 1;
            } else if(arr[groupSizes[i]] > 1) {
                arr[groupSizes[i]]--;
            } else if(arr[groupSizes[i]]) {
                arr[groupSizes[i]] = 0;
                ret.push_back(one[groupSizes[i]]);
                one[groupSizes[i]].clear();
            }
        }
        return ret;
    }
};

class Solution {
public:
    vector<int> v[505];
    vector<vector<int>> groupThePeople(vector<int>& a) {
        vector<vector<int>> ans;
        for(int i=0;i<a.size();++i) {
            v[a[i]].push_back(i);
            if(v[a[i]].size() == a[i]) {
                vector<int> v2 = v[a[i]];
                ans.push_back(v2);
                v[a[i]].clear();
            }
        }
        return ans;
    }
};
