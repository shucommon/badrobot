import time

class Solution:
    def isValid_demo(self, s: 'str') -> 'bool':
        dict = {'(': ')', '[': ']', '{': '}'}
        stack = []
        for i in range(0, len(s)):
            if s[i] == '(' or s[i] == '[' or s[i] == '{':
                stack.append(s[i])
            else:
                if len(stack) == 0 or dict[stack.pop()] != s[i]:
                    return False
        return len(stack) == 0

    def isValid(self, s: str) -> bool:
        '''
        while '{}' in s or '[]' in s or '()' in s:
            s = s.replace('{}', '')
            s = s.replace('[]', '')
            s = s.replace('()', '')
        return s == ''
        '''

        tmp_s = ''
        lens = 0
        for i in range(len(s)):
            if s[i] == '(' or s[i] == '{' or s[i] == '[':
                tmp_s += s[i]
                lens += 1
            elif lens and ((ord(s[i]) == ord(tmp_s[lens-1]) + 1) or (ord(s[i]) == ord(tmp_s[lens-1]) + 2)):
                tmp_s.remove(s[i]
                lens -= 1
            else:
                return False
            print(tmp_s)

        if lens:
            return False

        return True

sl = Solution()
start = time.time()
#rt = sl.isValid('{[]}')
rt = sl.isValid("()[]{}")
end = time.time()
print(rt)
print((end - start) * 1000 , 'ms')

