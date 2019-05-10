import time

class Solution(object):
    def twoCitySchedCost(self, costs):
        A, B, ttc = 0, 0, 0
        a_list, b_list = [], []

        for i in range(len(costs)):
            if costs[i][0] <= costs[i][1]:
                A += 1
                ttc += costs[i][0]
                a_list.append(costs[i][1] - costs[i][0])
            else:
                B += 1
                ttc += costs[i][1]
                b_list.append(costs[i][0] - costs[i][1])

        if A > B:
            a_list.sort()
            for i in range(0, int((A-B)/2)):
                ttc += a_list[i]
        elif A < B:
            b_list.sort()
            for i in range(0, int((B-A)/2)):
                ttc += b_list[i]

        return ttc

    def twoCitySchedCost_min_time(self, costs):
        costs.sort(key = lambda x:  x[0]-x[1])

        N = len(costs) // 2
        cost = 0
        for i in range(N):
            cost += costs[i][0]
        for i in range(N):
            cost += costs[N+i][1]
        return cost

sl = Solution()
start = time.time()
print(sl.twoCitySchedCost([[10,20],[30,200],[400,50],[30,20]]))
end = time.time()
print((end - start) * 1000 , 'ms')

start = time.time()
print(sl.twoCitySchedCost_min_time([[10,20],[30,200],[400,50],[30,20]]))
end = time.time()
print((end - start) * 1000 , 'ms')
