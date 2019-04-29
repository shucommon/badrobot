import time

class Solution:
    def allCellsDistOrder(self, R: int, C: int, r0: int, c0: int) -> 'List[List[int]]':
        ret = {}
        tmp = []
        for r in range(0, R):
            for c in range(0, C):
                if abs(r - r0) + abs(c - c0) in ret:
                    ret[abs(r - r0) + abs(c - c0)].append([r, c])
                else:
                    ret[abs(r - r0) + abs(c - c0)] = [[r, c]]

        for i in range(0, max(ret.keys()) + 1):
            if i in ret:
                for lis in ret[i]:
                    tmp.append(lis)

        return tmp

    def allCellsDistOrder_min_time(self, R: int, C: int, r0: int, c0: int) -> 'List[List[int]]':
        mat = [[i, j] for i in range(R) for j in range(C)]

        return sorted(mat, key = lambda x: abs(r0 - x[0]) + abs(c0 - x[1]))

sl = Solution()
start = time.time()
print(sl.allCellsDistOrder(3,4,0,1))
end = time.time()
print((end - start) * 1000 , 'ms')

start = time.time()
print(sl.allCellsDistOrder_min_time(3,4,0,1))
end = time.time()
print((end - start) * 1000 , 'ms')
