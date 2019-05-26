class Solution:
    def isRobotBounded(self, instructions: str) -> bool:
        move = {0:[0, 1], 1:[-1, 0], 2:[0, -1], 3:[1, 0]}
        k = 0
        p = [0, 0]
        for i in range(4):
            for i in range(len(instructions)):
                if instructions[i] == 'L':
                    k += 1
                    k %= 4
                elif instructions[i] == 'R':
                    k += 3
                    k %= 4
                if instructions[i] == 'G':
                    p[0] += move[k][0]
                    p[1] += move[k][1]
            if p == [0, 0]:
                break

        if p == [0, 0]:
            return True
        return False

sl = Solution()
rt = sl.isRobotBounded('GLR')
print(rt)
rt = sl.isRobotBounded('G')
print(rt)

print("start true")
rt = sl.isRobotBounded('L')
print(rt)
rt = sl.isRobotBounded('R')
print(rt)
rt = sl.isRobotBounded('GL')
print(rt)
rt = sl.isRobotBounded('LRRRRLLLRL')
print(rt)
rt = sl.isRobotBounded("GGRGGRGGRGGR")
print(rt)
