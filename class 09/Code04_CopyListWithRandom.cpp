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
// LeetCode 138. 复制带随机指针的链表:  https://leetcode.cn/problems/copy-list-with-random-pointer/

class ListNode {
public:
    int val;
    ListNode *next;
    ListNode *random;

    ListNode(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

ListNode *copyRandomList1(ListNode *head) {
    // Key老节点 value新节点
    unordered_map<ListNode *, ListNode *> map;
    ListNode *cur = head;
    while (cur) {
        map[cur] = new ListNode(cur->val);
        cur = cur->next;
    }
    cur = head;
    while (cur) {
        map[cur]->next = map[cur->next];
        map[cur]->random = map[cur->random];
        cur = cur->next;
    }
    return map[head];
}

ListNode *copyRandomList2(ListNode *head) {
    if (head == nullptr) {
        return nullptr;
    }
    ListNode *cur = head;
    ListNode *next = nullptr;
    // 1 -> 2 -> 3 -> null
    // 1 -> 1' -> 2 -> 2' -> 3 -> 3'
    while (cur) {
        next = cur->next;
        cur->next = new ListNode(cur->val);
        cur->next->next = next;
        cur = next;
    }
    cur = head;
    ListNode *copy = nullptr;
    // 1 1' 2 2' 3 3'
    // 依次设置 1' 2' 3' random指针
    while (cur) {
        next = cur->next->next;
        copy = cur->next;
        copy->random = cur->random ? cur->random->next : nullptr;
        cur = next;
    }
    ListNode *res = head->next;
    cur = head;
    // 老 新 混在一起，next方向上，random正确
    // next方向上，把新老链表分离
    while (cur) {
        next = cur->next->next;
        copy = cur->next;
        cur->next = next;
        copy->next = next ? next->next : nullptr;
        cur = next;
    }
    return res;
}


void printLinkedList(ListNode *node) {
    cout << "Linked List: ";
    while (node) {
        cout << node->val << ' ';
        node = node->next;
    }
    cout << endl;
}


int main() {

    return 0;
}