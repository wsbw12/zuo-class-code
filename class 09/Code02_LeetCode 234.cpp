#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stack>

using namespace std;

//给定一个单链表的头节点head，请判断该链表是否为回文结构
// LeetCode 234:  https://leetcode-cn.com/problems/palindrome-linked-list/

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}

};

// 1.需要O(n)的额外空间复杂度
bool isPalindrome1(ListNode *head) {
    stack<ListNode *> s;
    ListNode *cur = head;
    while (cur) {
        s.push(cur);
        cur = cur->next;
    }
    while (head) {
        if (head->val != s.top()->val) {
            s.pop();
            return false;
        } else {
            s.pop();
        }
        head = head->next;
    }
    return true;
}

// 2.需要O(n/2)的额外空间复杂度
bool isPalindrome2(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
        return true;
    }
    ListNode *right = head->next;
    ListNode *cur = head;
    while (cur->next && cur->next->next) {
        right = right->next;
        cur = cur->next->next;
    }
    stack<ListNode *> s;
    while (right) {
        s.push(right);
        right = right->next;
    }
    while (!s.empty()) {
        if (head->val != s.top()->val) {
            s.pop();
            return false;
        } else {
            s.pop();
        }
        head = head->next;
    }
    return true;
}

// 3.需要O(1)的额外空间复杂度
bool isPalindrome3(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
        return true;
    }
    ListNode *n1 = head;
    ListNode *n2 = head;
    while (n2->next && n2->next->next) {
        n1 = n1->next;
        n2 = n2->next->next;
    }
    // 例如 1->2->3->3->2->1
    // 执行完上面的代码后 1->2->3(n1)->3->2->1
    n2 = n1->next;
    n1->next = nullptr;
    ListNode *n3 = nullptr;
    while (n2) {
        n3 = n2->next;
        n2->next = n1;
        n1 = n2;
        n2 = n3;
    }
    // 执行完上面的代码后 1->2->3<-3<-2<-1
    n3 = n1;
    n2 = head;
    bool res = true;
    while (n1 && n2) {
        if (n1->val != n2->val) {
            res = false;
            break;
        }
        n1 = n1->next;
        n2 = n2->next;
    }
    n1 = n3->next;
    n3->next = nullptr;
    while (n1) {
        n2 = n1->next;
        n1->next = n3;
        n3 = n1;
        n1 = n2;
    }
    // 最后要将链表变为 1->2->3->3->2->1 原样
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
    ListNode *head = nullptr;
    printLinkedList(head);
    cout << isPalindrome1(head) << "|" << isPalindrome2(head) << "|" << isPalindrome3(head) << "|";
    cout << endl;
    printLinkedList(head);
    cout << "=====================" << endl;
    head = new ListNode(1);
    printLinkedList(head);
    cout << isPalindrome1(head) << "|" << isPalindrome2(head) << "|" << isPalindrome3(head) << "|";
    cout << endl;
    printLinkedList(head);
    cout << "=====================" << endl;
    head = new ListNode(1);
    head->next = new ListNode(2);
    printLinkedList(head);
    cout << isPalindrome1(head) << "|" << isPalindrome2(head) << "|" << isPalindrome3(head) << "|";
    cout << endl;
    printLinkedList(head);
    cout << "=====================" << endl;
    head = new ListNode(1);
    head->next = new ListNode(1);
    printLinkedList(head);
    cout << isPalindrome1(head) << "|" << isPalindrome2(head) << "|" << isPalindrome3(head) << "|";
    cout << endl;
    printLinkedList(head);
    cout << "=====================" << endl;
    head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    printLinkedList(head);
    cout << isPalindrome1(head) << "|" << isPalindrome2(head) << "|" << isPalindrome3(head) << "|";
    cout << endl;
    printLinkedList(head);
    cout << "=====================" << endl;
    head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(1);
    printLinkedList(head);
    cout << isPalindrome1(head) << "|" << isPalindrome2(head) << "|" << isPalindrome3(head) << "|";
    cout << endl;
    printLinkedList(head);
    cout << "=====================" << endl;
    head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(1);
    printLinkedList(head);
    cout << isPalindrome1(head) << "|" << isPalindrome2(head) << "|" << isPalindrome3(head) << "|";
    cout << endl;
    printLinkedList(head);
    cout << "=====================" << endl;
    head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(2);
    head->next->next->next = new ListNode(1);
    printLinkedList(head);
    cout << isPalindrome1(head) << "|" << isPalindrome2(head) << "|" << isPalindrome3(head) << "|";
    cout << endl;
    printLinkedList(head);
    cout << "=====================" << endl;
    head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(2);
    head->next->next->next->next = new ListNode(1);
    printLinkedList(head);
    cout << isPalindrome1(head) << "|" << isPalindrome2(head) << "|" << isPalindrome3(head) << "|";
    cout << endl;
    printLinkedList(head);
    cout << "=====================" << endl;
    return 0;
}