import time

class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        max_len = 0
        for i in range(0, len(s)):
            dic_str = {}
            tmp_max = 1
            for j in range(i + 1, len(s)):
                dic_str[s[j - 1]] = j - 1
                if s[j] in dic_str.keys():
                    break
                tmp_max += 1
            max_len = max(max_len, tmp_max)

        return max_len

class Solution1:
    def lengthOfLongestSubstring(self, s: str) -> int:
        max_len = 0
        tmp_max = 0
        last_max = 1
        dic_str = {}
        for i in range(0, len(s)):
            for j in range(i + last_max - 1, len(s)):
                if s[j] in dic_str.keys():
                    break
                dic_str[s[j]] = j
                tmp_max += 1
            del dic_str[s[i]]
            max_len = max(max_len, tmp_max)
            last_max = tmp_max
            tmp_max -= 1

            if len(s) - i - 1 <= max_len:
                break

        return max_len

# from other's sample
class Solution2:
    def lengthOfLongestSubstring(self, s: 'str') -> 'int':
        start = best = 0
        checked = {}
        for i in range(0, len(s)):
            if s[i] in checked and checked[s[i]] >= start:
                start = checked[s[i]] + 1
            else:
                if i+1-start > best:
                    best = i+1-start
            checked[s[i]] = i

        return best

class best_solution:
    def lengthOfLongestSubstring(self, s: 'str') -> 'int':
        max_len = start = 0
        dic = {}
        for i in range(0, len(s)):
            if s[i] in dic and dic[s[i]] >= start:
                start = dic[s[i]] + 1
            else:
                # function call takes more time
                #max_len = max(max_len, i + 1 - start)
                if max_len < i + 1 - start:
                    max_len = i + 1 -start
            dic[s[i]] = i

        return max_len


sl = Solution()
start = time.time()
rt = sl.lengthOfLongestSubstring('asbadljalfjaldkfjalkjdjfiwojnasjdcjal;djkfljaklj1380u8fja0u80fu2fka')
end = time.time()
print(rt)
print((end - start) * 1000 , 'ms')

sl = Solution1()
start = time.time()
rt = sl.lengthOfLongestSubstring('asbadljalfjaldkfjalkjdjfiwojnasjdcjal;djkfljaklj1380u8fja0u80fu2fka')
end = time.time()
print(rt)
print((end - start) * 1000 , 'ms')

sl = Solution2()
start = time.time()
rt = sl.lengthOfLongestSubstring('asbadljalfjaldkfjalkjdjfiwojnasjdcjal;djkfljaklj1380u8fja0u80fu2fka')
end = time.time()
print(rt)
print((end - start) * 1000 , 'ms')

sl = best_solution()
start = time.time()
rt = sl.lengthOfLongestSubstring('asbadljalfjaldkfjalkjdjfiwojnasjdcjal;djkfljaklj1380u8fja0u80fu2fka')
end = time.time()
print(rt)
print((end - start) * 1000 , 'ms')
