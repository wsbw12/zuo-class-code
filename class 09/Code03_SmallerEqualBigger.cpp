#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stack>

using namespace std;
// 给定一个单链表的头节点head，给定一个整数n，将链表按n划分成左边<n、中间==n、右边>n
// LeetCode 86. 分隔链表:  https://leetcode.cn/problems/partition-list/

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}

};

void swap(vector<ListNode *> &arr, int i, int j) {
    ListNode *temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void arrPartition(vector<ListNode *> &nodeArr, int pivot) {
    int small = -1;
    int big = nodeArr.size();
    int index = 0;
    while (index != big) {
        if (nodeArr[index]->val < pivot) {
            swap(nodeArr, ++small, index++);
        } else if (nodeArr[index]->val == pivot) {
            index++;
        } else {
            swap(nodeArr, --big, index);
        }
    }
}


ListNode *listPartition1(ListNode *head, int pivot) {
    if (head == nullptr) {
        return head;
    }
    ListNode *cur = head;
    int i = 0;
    while (cur) {
        i++;
        cur = cur->next;
    }
    vector<ListNode *> nodeArr(i);
    i = 0;
    cur = head;
    for (i = 0; i != nodeArr.size(); i++) {
        nodeArr[i] = cur;
        cur = cur->next;
    }
    arrPartition(nodeArr, pivot);
    for (i = 1; i != nodeArr.size(); i++) {
        nodeArr[i - 1]->next = nodeArr[i];
    }
    nodeArr[i - 1]->next = nullptr;
    return nodeArr[0];
}

ListNode *listPartition2(ListNode *head, int pivot) {
    ListNode *sH = nullptr; // 小于区域的头
    ListNode *sT = nullptr;
    ListNode *eH = nullptr; // 等于区域的头
    ListNode *eT = nullptr;
    ListNode *mH = nullptr; // 大于区域的头
    ListNode *mT = nullptr;
    ListNode *next = nullptr;
    while (head) {
        next = head->next;
        head->next = nullptr;
        if (head->val < pivot) {
            if (sH == nullptr) {
                sH = head;
                sT = head;
            } else {
                sT->next = head;
                sT = head;
            }
        } else if (head->val == pivot) {
            if (eH == nullptr) {
                eH = head;
                eT = head;
            } else {
                eT->next = head;
                eT = head;
            }
        } else {
            if (mH == nullptr) {
                mH = head;
                mT = head;
            } else {
                mT->next = head;
                mT = head;
            }
        }
        head = next;
    }
    // 小于区域的尾巴，连等于区域的头，等于区域的尾巴连大于区域的头
    if (sT) {
        sT->next = eH;
        eT = eT == nullptr ? sT : eT; // 下一步，谁去连大于区域的头，谁就变成eT
    }
    // 下一步，一定是需要用eT 去接 大于区域的头
    // 有等于区域，eT -> 等于区域的尾结点
    // 无等于区域，eT -> 小于区域的尾结点
    // eT 尽量不为空的尾巴节点
    if (eT) {
        eT->next = mH;
    }
    return sH != nullptr ? sH : (eH != nullptr ? eH : mH);
}

//给你一个链表的头节点head和一个特定值x,请你对链表进行分隔,使得所有小于x的节点都出现在大于或等于x的节点之前。
//你应当保留两个分区中每个节点的初始相对位置。
ListNode *partition2(ListNode *head, int pivot) {
    ListNode *sH = nullptr; // 小于区域的头
    ListNode *sT = nullptr;
    ListNode *mH = nullptr; // 大于等于区域的头
    ListNode *mT = nullptr;
    ListNode *next = nullptr;
    while (head) {
        next = head->next;
        head->next = nullptr;
        if (head->val < pivot) {
            if (sH == nullptr) {
                sH = head;
                sT = head;
            } else {
                sT->next = head;
                sT = head;
            }
        } else {
            if (mH == nullptr) {
                mH = head;
                mT = head;
            } else {
                mT->next = head;
                mT = head;
            }
        }
        head = next;
    }
    // 小于区域的尾巴，连大于等于区域的头
    if (sT) {
        sT->next = mH;
    }
    return sH != nullptr ? sH : mH;
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
    ListNode *head;
    head = new ListNode(7);
    head->next = new ListNode(9);
    head->next->next = new ListNode(1);
    head->next->next->next = new ListNode(8);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = new ListNode(2);
    head->next->next->next->next->next->next = new ListNode(5);
    printLinkedList(head);
    head = listPartition1(head, 4);
    printLinkedList(head);
    cout << "=====================" << endl;
    head = new ListNode(7);
    head->next = new ListNode(9);
    head->next->next = new ListNode(1);
    head->next->next->next = new ListNode(8);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = new ListNode(2);
    head->next->next->next->next->next->next = new ListNode(5);
    printLinkedList(head);
    head = listPartition2(head, 5);
    printLinkedList(head);
    cout << "=====================" << endl;
    return 0;
}