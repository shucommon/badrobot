import time

class Solution:
    def numMovesStones(self, a: int, b: int, c: int) -> 'List[int]':
        a, b, c = sorted([a, b, c])

        left = 0
        if b - a > 2 and c - b > 2:
            left = 2
        elif b - a == 2 or c - b == 2 or (b - a <= 1 and c - b > 2) or (c - b <= 1 and b - a > 2):
            left = 1

        if c - a > 2:
            return [left, c - a - 2]
        else:
            return [0, 0]

sl = Solution()
start = time.time()
print(sl.numMovesStones(1,5,3))
print(sl.numMovesStones(1,2,5))
end = time.time()
print((end - start) * 1000 , 'ms')
