import time

class Solution:
    def cmp(self, s1, s2):
        for i in range(len(s1)):
            if s1[i] != s2[i] and s1[i] != s2[i+1]:
                return False

        return True

    def longestStrChain(self, words):
        print(words)
        if len(words) == 1:
            return 0

        wk = {}
        for i in range(len(words)):
            wk[len(words[i])].append(words[i])

        print(wk)

        return 0



sl = Solution()
rt = sl.longestStrChain(["a","b","ba","bca","bda","bdca"])
print(4, rt)

rt = sl.longestStrChain(["ksqvsyq","ks","kss","czvh","zczpzvdhx","zczpzvh","zczpzvhx","zcpzvh","zczvh","gr","grukmj","ksqvsq","gruj","kssq","ksqsq","grukkmj","grukj","zczpzfvdhx","gru"])
print(7, rt)
