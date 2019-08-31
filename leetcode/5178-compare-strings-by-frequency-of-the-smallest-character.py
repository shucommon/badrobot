'''
输入：queries = ["bbb","cc"], words = ["a","aa","aaa","aaaa"]
输出：[1,2]
解释：第一个查询 f("bbb") < f("aaaa")，第二个查询 f("aaa") 和 f("aaaa") 都 > f("cc")。

1 <= queries.length <= 2000
1 <= words.length <= 2000
1 <= queries[i].length, words[i].length <= 10
queries[i][j], words[i][j] 都是小写英文字母
'''

def count(word):
    c = collections.Counter(word)
    k = c.keys()
    key = min(k)
    return c[key]


class Solution(object):
    def numSmallerByFrequency(self, queries, words):
        """
        :type queries: List[str]
        :type words: List[str]
        :rtype: List[int]
        """
        ws = map(count, words)
        ws.sort()
        qs = map(count, queries)
        ans = []
        for q in qs:
            index = bisect.bisect(ws, q)
            ans.append(len(ws) - index)
        return ans
