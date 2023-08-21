#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <unordered_map>

using namespace std;

//给定两个可能有环也可能无环的单链表，头节点head1和head2
//请实现一个函数，如果两个链表相交，请返回相交的第一个节点。如果不相交返回null
struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}

};

ListNode *getLoopNode(ListNode *head);

ListNode *noLoop(ListNode *head1, ListNode *head2);

ListNode *bothLoop(ListNode *head1, ListNode *loop1, ListNode *head2, ListNode *loop2);

ListNode *getIntersectNode(ListNode *head1, ListNode *head2) {
    if (head1 == nullptr || head2 == nullptr) {
        return nullptr;
    }
    ListNode *loop1 = getLoopNode(head1);
    ListNode *loop2 = getLoopNode(head2);
    if (loop1 == nullptr && loop2 == nullptr) {
        return noLoop(head1, head2);
    }
    if (loop1 && loop2) {
        return bothLoop(head1, loop1, head2, loop2);
    }
    return nullptr;
}

// 找到链表第一个入环节点，如果无环，返回null
ListNode *getLoopNode(ListNode *head) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
        return nullptr;
    }
    ListNode *slow = head->next;
    ListNode *fast = head->next->next;
    while (slow != fast) {
        if (fast->next == nullptr || fast->next->next == nullptr) {
            return nullptr;
        }
        fast = fast->next->next;
        slow = slow->next;
    }
    // 此时慢指针和快指针就相遇了
    // 让快指针回到开头,慢指针留在相遇的位置,之后两个指针都向前移动一步,再次相遇的时候就是入环的节点
    fast = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

// 如果两个链表都无环，返回第一个相交节点，如果不想交，返回null
ListNode *noLoop(ListNode *head1, ListNode *head2) {
    if (head1 == nullptr || head2 == nullptr) {
        return nullptr;
    }
    ListNode *cur1 = head1;
    ListNode *cur2 = head2;
    int n = 0;
    while (cur1->next) {
        n++;
        cur1 = cur1->next;
    }
    while (cur2->next) {
        n--;
        cur2 = cur2->next;
    }
    if (cur1 != cur2) { // 如果两个链表的最后一个节点不相同那么说明两个链表并不相交
        return nullptr;
    }
    // 此时的n是链表1的长度-链表2的长度
    cur1 = n > 0 ? head1 : head2; // 如果n大于0,说明链表1更长,此时cur1指向链表1
    cur2 = cur1 == head1 ? head2 : head1;
    n = abs(n);
    while (n) { // 让长的链表先走 它们两者之差的步数
        n--;
        cur1 = cur1->next;
    }
    while (cur1 != cur2) {
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    return cur1;
}

// 两个有环链表，返回第一个相交节点，如果不想交返回null
ListNode *bothLoop(ListNode *head1, ListNode *loop1, ListNode *head2, ListNode *loop2) {
    ListNode *cur1 = nullptr;
    ListNode *cur2 = nullptr;
    if (loop1 == loop2) {
        cur1 = head1;
        cur2 = head2;
        int n = 0;
        while (cur1 != loop1) {
            n++;
            cur1 = cur1->next;
        }
        while (cur2 != loop2) {
            n--;
            cur2 = cur2->next;
        }
        // 此时的n是链表1的长度-链表2的长度
        cur1 = n > 0 ? head1 : head2; // 如果n大于0,说明链表1更长,此时cur1指向链表1
        cur2 = cur1 == head1 ? head2 : head1;
        n = abs(n);
        while (n) { // 让长的链表先走 它们两者之差的步数
            n--;
            cur1 = cur1->next;
        }
        while (cur1 != cur2) {
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        return cur1;
    } else {
        cur1 = loop1->next;
        while (cur1 != loop1) {
            if (cur1 == loop2) {
                return loop1;
            }
            cur1 = cur1->next;
        }
        return nullptr;
    }
}

int main() {
    // 1->2->3->4->5->6->7->null
    ListNode *head1 = new ListNode(1);
    head1->next = new ListNode(2);
    head1->next->next = new ListNode(3);
    head1->next->next->next = new ListNode(4);
    head1->next->next->next->next = new ListNode(5);
    head1->next->next->next->next->next = new ListNode(6);
    head1->next->next->next->next->next->next = new ListNode(7);
    // 0->9->8->6->7->null
    ListNode *head2 = new ListNode(0);
    head2->next = new ListNode(9);
    head2->next->next = new ListNode(8);
    head2->next->next->next = head1->next->next->next->next->next;
    cout << getIntersectNode(head1, head2)->val << endl;
    cout << "======================" << endl;
    // 1->2->3->4->5->6->7->4...
    head1 = new ListNode(1);
    head1->next = new ListNode(2);
    head1->next->next = new ListNode(3);
    head1->next->next->next = new ListNode(4);
    head1->next->next->next->next = new ListNode(5);
    head1->next->next->next->next->next = new ListNode(6);
    head1->next->next->next->next->next->next = new ListNode(7);
    head1->next->next->next->next->next->next = head1->next->next->next; // 7->4
    // 0->9->8->2...
    head2 = new ListNode(0);
    head2->next = new ListNode(9);
    head2->next->next = new ListNode(8);
    head2->next->next->next = head1->next; // 8->2
    cout << getIntersectNode(head1, head2)->val << endl;
    cout << "======================" << endl;
    // 0->9->8->6->4->5->6..
    head2 = new ListNode(0);
    head2->next = new ListNode(9);
    head2->next->next = new ListNode(8);
    head2->next->next->next = head1->next->next->next->next->next; // 8->6
    cout << getIntersectNode(head1, head2)->val << endl;
    cout << "======================" << endl;
    return 0;
}