import time

class Solution:
    def findMedianSortedArrays(self, nums1: 'List[int]', nums2: 'List[int]') -> 'float':
        lt = sorted(nums1 + nums2)
        print(lt)

sl = Solution()
start = time.time()
rt = sl.findMedianSortedArrays([1, 3, 5], [2, 4, 6])
end = time.time()
print(rt)
print((end - start) * 1000 , 'ms')
