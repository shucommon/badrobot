int search(int* nums, int numsSize, int target){
    int l = 0, r = numsSize - 1;

    while(l <= r) {
        int mid = (l + r)/2;
        if(target == nums[mid])
            return mid;
        if(nums[mid] >= nums[0]) {
            if(target >= nums[l] && target < nums[mid])
                r = mid - 1;
            else
                l = mid + 1;
        } else {
            if(target > nums[r] || target < nums[mid])
                r = mid - 1;
            else
                l = mid + 1;
        }
    }
    return -1;
}
