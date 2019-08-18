class Solution:
    def lastSubstring(self, s: str) -> str:
        mx = ""
        for i in range(len(s)):
            print(i)
            mx = max(mx, s[i:])
            print(mx)

        return mx

sl = Solution()
sl.lastSubstring('abab')
sl.lastSubstring('aaaaaaaaaa')
