'''
给你的链表中可能有 1 到 1000 个节点。
对于链表中的每个节点，节点的值：-1000 <= node.val <= 1000.
'''

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.next = None

def to_list(h):
    ans = []
    while h:
        ans.append(h.val)
        h = h.next
    return ans


def to_link(l):
    n = ListNode(None)
    h = n
    for node in l:
        n.next = ListNode(node)
        n = n.next
    return h.next


class Solution(object):
    def removeZeroSumSublists(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        l = to_list(head)
        ans = list()
        for n in l:
            ans.append(n)
            s = 0
            for k in reversed(xrange(len(ans))):
                s += ans[k]
                if s == 0:
                    ans = ans[:k]
                    break
        return to_link(ans)


