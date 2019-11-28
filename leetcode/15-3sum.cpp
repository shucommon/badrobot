class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
		int n = nums.size();
		vector<vector<int>> ret;
		sort(nums.begin(), nums.end());

		for(int i = 0; i < n-2;) {
			if(nums.at(i) > 0)
				break;
			int l = i+1, r = n - 1;
			while(l < r) {
				int sum = nums.at(i) + nums.at(l) + nums.at(r);
				if(sum == 0) {
					vector<int> tmp;
					tmp.push_back(nums[i]);
					tmp.push_back(nums[l]);
					tmp.push_back(nums[r]);
					ret.push_back(tmp);
				}
				if(sum <= 0)
					while(l < r && nums.at(l) == nums.at(++l));
				else
					while(l < r && nums.at(r) == nums.at(--r));
			}
			while(i < n - 1 && nums.at(i) == nums.at(++i));
		}
		return ret;
    }
};
