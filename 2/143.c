struct ListNode *FindMiddleNode(struct ListNode *head)
{
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}

struct ListNode *ReverseList(struct ListNode *head)
{
    struct ListNode *prev = NULL;
    struct ListNode *curr = head;
    
    while (curr != NULL) {
        struct ListNode *nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }
    
    return prev;
}

void MergeLists(struct ListNode *l1, struct ListNode *l2)
{
    struct ListNode *l1Next = NULL;
    struct ListNode *l2Next = NULL;
    
    while (l1 != NULL && l2 != NULL) {
        l1Next = l1->next;
        l2Next = l2->next;
        
        l1->next = l2;
        if (l1Next == NULL) {
            break;
        }
        l2->next = l1Next;
        
        l1 = l1Next;
        l2 = l2Next;
    }
}

void ReorderList(struct ListNode *head)
{
    if (head == NULL || head->next == NULL) {
        return;
    }
    
    /* 找到中间节点 */
    struct ListNode *middle = FindMiddleNode(head);
    
    /* 反转后半部分链表 */
    struct ListNode *reversedHalf = ReverseList(middle->next);
    middle->next = NULL; /* 切断前半部分 */
    
    /* 合并两个链表 */
    MergeLists(head, reversedHalf);
}
