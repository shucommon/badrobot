class Solution:
    def maxSumAfterPartitioning(self, A: 'List[int]', K: 'int') -> 'int':
        sort = sorted(A)
        max_k = [sort[val] for val in range(len(A) - 1, len(A) - K - 1, -1)]

        print(sort)
        print(max_k)
        #for i in range(len(A)):

sl = Solution()
rt = sl.maxSumAfterPartitioning([1,15,7,9,2,5,10], 3)
print(rt)
