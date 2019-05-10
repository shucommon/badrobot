import time

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> 'ListNode':
        nl = ListNode((l1.val + l2.val)%10)
        it = nl
        over = int((l1.val + l2.val)/10)
        val = 0

        while l1.next != None or l2.next != None:
            if l1.next == None:
                val = l2.next.val + over
                l2 = l2.next
            elif l2.next == None:
                val = l1.next.val + over
                l1 = l1.next
            else:
                val = l1.next.val + l2.next.val + over
                l2 = l2.next
                l1 = l1.next

            over = int(val / 10)
            val = int(val % 10)
            it.next = ListNode(val)
            it = it.next

        if over:
            it.next = ListNode(over)

        return nl

l1 = ListNode(2)
l1.next = ListNode(4)
l1.next.next = ListNode(3)
l2 = ListNode(5)
l2.next = ListNode(6)
l2.next.next = ListNode(4)

sl = Solution()
start = time.time()
rt = sl.addTwoNumbers(l1, l2)
end = time.time()
while rt.next != None:
    print(rt.val)
    rt = rt.next
print(rt.val)
print((end - start) * 1000 , 'ms')
