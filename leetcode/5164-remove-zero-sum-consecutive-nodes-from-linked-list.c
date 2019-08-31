#include <stdio.h>

/*
给你的链表中可能有 1 到 1000 个节点。
对于链表中的每个节点，节点的值：-1000 <= node.val <= 1000.
*/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 typedef struct ListNode {
     int val;
     struct ListNode *next;
 }list;


struct ListNode* removeZeroSumSublists(struct ListNode* head){
    if(head == NULL)
        return NULL;

    struct ListNode *l = head->next, *r = head->next, *it;
    if(l == NULL)
        if(head->val == 0) {
            free(head);
            return NULL;
        } else
            return head;
    }

    int sum = -1;
    while(l != NULL) {
        while(l && l->val == 0) {
            struct ListNode *tmp = l;
            l = l->next;
            free(tmp);
        }
        if(l == NULL)
            break;

        sum = l->val;
        it = l->next;
        while(it) {
            sum += it->val;
            if(sum == 0) {
                head->next = it->next; 
                while(l->next != it) {
                }
                l = head;
                break;
            }
            it = it->next;
        }

        l = l->next;
    }
}


int main()
{
    return 0;
}
