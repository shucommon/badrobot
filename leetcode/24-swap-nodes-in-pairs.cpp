/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* swapPairs(struct ListNode* head){
    if(head == NULL || head->next == NULL)
        return head;

    struct ListNode *next = head->next;
    head->next = swapPairs(next->next);
    next->next = head;
    return next;
}

struct ListNode* swapPairs(struct ListNode* head){
    if(head == NULL || head->next == NULL)
        return head;

    struct ListNode pre;
    pre.next = head;

    struct ListNode *it = &pre, *p = head;
    int bit = 1;
    while(p) {
        struct ListNode *q = p->next;
        if(bit) {
            bit = 0;
            it->next = p;
            p->next = NULL;
        } else {
            bit = 1;
            struct ListNode *tmp = it->next;
            it->next = p;
            p->next = tmp;
            it = tmp;
        }
        p = q;
    }
    return pre.next;
}

