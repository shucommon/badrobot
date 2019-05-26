import time

class Solution:
    def heightChecker(self, heights: 'List[int]') -> 'int':
        h = sorted(heights)
        cnt = 0
        for i in range(len(h)):
            if h[i] != heights[i]:
                cnt += 1

        return cnt

sl = Solution()
start = time.time()
rt = sl.heightChecker([1,1,4,2,1,3])
end = time.time()
print(rt)
print((end - start) * 1000 , 'ms')
