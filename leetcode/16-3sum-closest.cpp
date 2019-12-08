class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int closet = nums.at(0) + nums.at(1) + nums.at(2);
        int min = abs(target - closet);
        for(int i = 0; i < n - 2;){
            int ii = i+1, iii = n-1;
            while(ii < iii) {
                int tmp = nums.at(i) + nums.at(ii) + nums.at(iii); 
                int tmp_min = target - tmp;
                if(tmp_min == 0)
                    return tmp;
                else if (tmp_min > 0)
                    while(ii < iii && nums.at(ii) == nums.at(++ii));
                else
                    while(ii < iii && nums.at(iii) == nums.at(--iii));
                if(min > abs(tmp_min)) {
                    min = abs(tmp_min);
                    closet = tmp; 
                }
            }
            while(i < n - 1 && nums.at(i) == nums.at(++i));
        }
        return closet;
    }
};
