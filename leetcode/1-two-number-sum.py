import time

class Solution:
    #def twoSum(self, nums, target: int):
    def twoSum(self, nums: 'List[int]', target: 'int') -> 'List[int]':
        for i in range(0, len(nums)):
            num1 = nums[i]
            for j in range(i+1, len(nums)):
                if num1 + nums[j] == target:
                    return [i, j]

        return [int]

class best_solution:
    def twoSum(self, nums: 'List[int]', target: 'int') -> 'List[int]':
        dict = {}
        for i in range(0, len(nums)):
            if nums[i] in dict:
                return [dict[nums[i]], i]
            else:
                dict[target - nums[i]] = i

sl = Solution()
start = time.time()
rt = sl.twoSum([2,5,7,9, 3, 4, 20, 30, 32, 32, 45, 56, 32, 34, 34, 9], 65)
end = time.time()
print(rt)
print((end - start) * 1000 , 'ms')

sl = best_solution()
start = time.time()
rt = sl.twoSum([2,5,7,9, 3, 4, 20, 30, 32, 32, 45, 56, 32, 34, 34, 9], 65)
end = time.time()
print(rt)
print((end - start) * 1000 , 'ms')
