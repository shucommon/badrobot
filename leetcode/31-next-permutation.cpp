class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size(), i = 0;
        for(i = n - 1; i > 0; i--) {
            int j = i - 1;
            if(nums.at(j) >= nums.at(i))
                continue;
            int index = i;
            while(index < n && nums.at(index) > nums.at(j))
                index++;
            int tmp = nums.at(j);
            nums.at(j) = nums.at(index - 1);
            nums.at(index - 1) = tmp;
            int m = i, k = n - 1;
            while(m < k) {
                int tmp = nums.at(m);
                nums.at(m) = nums.at(k);
                nums.at(k) = tmp;
                m++;
                k--;
            }
            break;
        }
        if(i == 0) {
            int m = 0, k = n - 1;
            while(m < k) {
                int tmp = nums.at(m);
                nums.at(m) = nums.at(k);
                nums.at(k) = tmp;
                m++;
                k--;
            }
        }
    }
};
