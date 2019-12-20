/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int num = 0;
        ListNode *ln = head;
        while(ln) {
            num++;      
            ln = ln->next;
        }
        if(num == n) {
            ListNode *tmp = head;
            head = head->next;
            tmp->next = NULL;
            delete(tmp);
        } else {
            num -= n;
            ln = head;
            while(ln && --num)
                ln = ln->next;
            ListNode *tmp = ln->next;
            ln->next = ln->next->next;
            tmp->next = NULL;
            delete(tmp);
        }
        return head;
    }
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode ln(0);
        ln.next = head;
        ListNode *f = head, *s = &ln;
        while(n--)
            f = f->next;
        while(f) {
            s = s->next;
            f = f->next;
        }
        ListNode *tmp = s->next;
        s->next = s->next->next;
        tmp->next = NULL;
        delete(tmp);
        return ln.next;
    }
};
