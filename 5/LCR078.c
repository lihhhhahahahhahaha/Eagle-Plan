struct ListNode *mergeTwoLists(struct ListNode *l1, struct ListNode *l2)
{
    struct ListNode dummy;
    struct ListNode *tail = &dummy;
    dummy.next = NULL;
    
    while (l1 && l2) {
        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

struct ListNode *mergeKLists(struct ListNode **lists, int listsSize)
{
    if (listsSize == 0) return NULL;
    
    // 分治合并
    int interval = 1;
    while (interval < listsSize) {
        for (int i = 0; i < listsSize - interval; i += interval * 2) {
            lists[i] = mergeTwoLists(lists[i], lists[i + interval]);
        }
        interval *= 2;
    }
    
    return lists[0];
}
