import time

class Solution:
    def lastStoneWeight(self, stones: 'List[int]') -> 'int':
        sort_stone = sorted(stones)

        while len(sort_stone) > 1 :
            if sort_stone[-1] == sort_stone[-2]:
                sort_stone = sort_stone[:-2]
            elif sort_stone[-1] > sort_stone[-2]:
                tmp = sort_stone[-1] - sort_stone[-2]
                sort_stone = sort_stone[:-2]
                sort_stone.append(tmp)

            sort_stone = sorted(sort_stone)

        if len(sort_stone) == 1:
            return sort_stone[0]
        else:
            return 0


sl = Solution()
start = time.time()
rt = sl.lastStoneWeight([2,7,4,1, 8, 1])
end = time.time()
print(rt)
print((end - start) * 1000 , 'ms')
