import time

class Solution:
    def longestPalindrome(self, s: str) -> str:
        if len(s) < 1:
            return ''
        start, end = 0, 0
        for i in range(len(s)):
            len1 = self.search_around(s, i, i)
            len2 = self.search_around(s, i, i + 1)
            max_len = max(len1, len2)
            if max_len > end - start:
                start = i - int((max_len - 1) / 2)
                end = i + int(max_len / 2)

        return s[start:end+1]

    def search_around(self, s, left, right):
        l, r = left, right
        while (l >= 0 and r < len(s)) and s[l] == s[r]:
            l -= 1;
            r += 1;

        return r - l - 1

    def longestPalindrome_min_time(self, s: 'str') -> 'str':
        length = len(s)
        if length < 2 or s == s[::-1]: return s
        max_len, begin = 1, 0
        for i in range(1, length):
            odd = s[i - max_len - 1:i + 1]
            even = s[i - max_len:i + 1]
            if i - max_len >= 1 and odd == odd[::-1]:
                begin = i - max_len - 1
                max_len += 2
                continue
            if i - max_len >= 0 and even == even[::-1]:
                begin = i - max_len
                max_len += 1
        return s[begin:begin + max_len]

sl = Solution()
start = time.time()
print(sl.longestPalindrome('abcdedcbaaaaaabcbaaaaaaadd'))
end = time.time()
print((end - start) * 1000 , 'ms')

start = time.time()
print(sl.longestPalindrome_min_time('abcdedcbaaaaaabcbaaaaaaadd'))
end = time.time()
print((end - start) * 1000 , 'ms')
