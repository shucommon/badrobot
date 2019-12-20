class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> ret;

        for(int i = 0; i < n - 3;) {
            int tg = target - nums.at(i);
            for(int j = i + 1; j < n - 2;) {
                int l = j + 1, r = n - 1;
                while(l < r) {
                    int sum = nums.at(j) + nums.at(l) + nums.at(r);
                    if(sum == tg) {
                        vector<int> a;
                        a.push_back(nums.at(i));
                        a.push_back(nums.at(j));
                        a.push_back(nums.at(l));
                        a.push_back(nums.at(r));
                        ret.push_back(a);
                    }
                    if(sum >= tg)
                        while(l < r && nums.at(r) == nums.at(--r)); 
                    else
                        while(l < r && nums.at(l) == nums.at(++l)); 
                }
                while(j < n - 1 && nums.at(j) == nums.at(++j));
            }
            while(i < n - 2 && nums.at(i) == nums.at(++i));
        }
        return ret;
    }
};
