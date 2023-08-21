#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//1.输入链表头节点，奇数长度返回中点，偶数长度返回上中点
//2.输入链表头节点，奇数长度返回中点，偶数长度返回下中点
//3.输入链表头节点，奇数长度返回中点前一个，偶数长度返回上中点前一个
//4.输入链表头节点，奇数长度返回中点前一个，偶数长度返回下中点前一个
struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}

};

//1.输入链表头节点，奇数长度返回中点，偶数长度返回上中点
ListNode *midOrUpMidNode(ListNode *head) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
        return head;
    }
    // 当链表有三个及以上的节点的时候
    // 此时让快慢指针不从同一个点出发
    ListNode *slow = head->next;
    ListNode *fast = head->next->next;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

//2.输入链表头节点，奇数长度返回中点，偶数长度返回下中点
ListNode *midOrDownMidNode(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode *slow = head->next;
    ListNode *fast = head->next;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

//3.输入链表头节点，奇数长度返回中点前一个，偶数长度返回上中点前一个
ListNode *midOrUpMidPreNode(ListNode *head) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
        return nullptr;
    }
    ListNode *slow = head;
    ListNode *fast = head->next->next;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

//4.输入链表头节点，奇数长度返回中点前一个，偶数长度返回下中点前一个
ListNode *midOrDownMidPreNode(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
        return nullptr;
    }
    if (head->next->next == nullptr) {
        return head;
    }
    ListNode *slow = head;
    ListNode *fast = head->next;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

//1.输入链表头节点，奇数长度返回中点，偶数长度返回上中点 暴力解法
ListNode *right1(ListNode *head) {
    if (head == nullptr) {
        return nullptr;
    }
    ListNode *cur = head;
    vector<ListNode *> arr;
    while (cur) {
        arr.push_back(cur);
        cur = cur->next;
    }
    return arr[(arr.size() - 1) / 2];
}

//2.输入链表头节点，奇数长度返回中点，偶数长度返回下中点 暴力解法
ListNode *right2(ListNode *head) {
    if (head == nullptr) {
        return nullptr;
    }
    ListNode *cur = head;
    vector<ListNode *> arr;
    while (cur) {
        arr.push_back(cur);
        cur = cur->next;
    }
    return arr[(arr.size()) / 2];
}


//3.输入链表头节点，奇数长度返回中点前一个，偶数长度返回上中点前一个 暴力解法
ListNode *right3(ListNode *head) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
        return nullptr;
    }
    ListNode *cur = head;
    vector<ListNode *> arr;
    while (cur) {
        arr.push_back(cur);
        cur = cur->next;
    }
    return arr[(arr.size() - 3) / 2];
}


//4.输入链表头节点，奇数长度返回中点前一个，偶数长度返回下中点前一个 暴力解法
ListNode *right4(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
        return nullptr;
    }
    ListNode *cur = head;
    vector<ListNode *> arr;
    while (cur) {
        arr.push_back(cur);
        cur = cur->next;
    }
    return arr[(arr.size() - 2) / 2];
}

int main() {
    ListNode *test = nullptr;
    test = new ListNode(1);
    test->next = new ListNode(2);
    test->next->next = new ListNode(3);
    test->next->next->next = new ListNode(4);
    test->next->next->next = new ListNode(5);
    test->next->next->next->next = new ListNode(6);
    test->next->next->next->next->next = new ListNode(7);
    test->next->next->next->next->next->next = new ListNode(8);
    ListNode *ans1 = nullptr;
    ListNode *ans2 = nullptr;
    ans1 = midOrUpMidNode(test);
    ans2 = right1(test);
    ans1 != nullptr ? cout << ans1->val << endl : cout << "无" << endl;
    ans2 != nullptr ? cout << ans2->val << endl : cout << "无" << endl;
    cout << "===================" << endl;
    ans1 = midOrDownMidNode(test);
    ans2 = right2(test);
    ans1 != nullptr ? cout << ans1->val << endl : cout << "无" << endl;
    ans2 != nullptr ? cout << ans2->val << endl : cout << "无" << endl;
    cout << "===================" << endl;
    ans1 = midOrUpMidPreNode(test);
    ans2 = right3(test);
    ans1 != nullptr ? cout << ans1->val << endl : cout << "无" << endl;
    ans2 != nullptr ? cout << ans2->val << endl : cout << "无" << endl;
    cout << "===================" << endl;
    ans1 = midOrDownMidPreNode(test);
    ans2 = right4(test);
    ans1 != nullptr ? cout << ans1->val << endl : cout << "无" << endl;
    ans2 != nullptr ? cout << ans2->val << endl : cout << "无" << endl;
    cout << "===================" << endl;
    return 0;
}