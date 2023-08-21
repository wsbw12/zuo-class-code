#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>
#include <set>

using namespace std;

const int Max = 100;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}

};


struct DoubleNode {
    int val;
    DoubleNode *last;
    DoubleNode *next;

    DoubleNode() : val(0), next(nullptr), last(nullptr) {}

    DoubleNode(int x) : val(x), next(nullptr), last(nullptr) {}

    DoubleNode(int x, DoubleNode *next, DoubleNode *last) : val(x), next(next), last(last) {}
};

//单链表的反转
ListNode *reverseLinkedList(ListNode *head) {
    ListNode *pre = nullptr;
    ListNode *next = nullptr;
    while (head) {
        next = head->next;
        head->next = pre;
        pre = head;
        head = next;
    }
    return pre;
}

ListNode *testReverseLinkedList(ListNode *head) {
    if (head == nullptr) {
        return NULL;
    }
    vector<ListNode *> list;
    while (head != nullptr) {
        list.push_back(head);
        head = head->next;
    }
    list[0]->next = nullptr;
    int n = list.size();
    for (int i = 1; i < n; i++) {
        list[i]->next = list[i - 1];
    }
    return list[n - 1];
}

//双链表的反转
DoubleNode *reverseDoubleList(DoubleNode *head) {
    DoubleNode *pre = nullptr;
    DoubleNode *next = nullptr;
    while (head) {
        next = head->next;
        head->next = pre;
        head->last = next;
        pre = head;
        head = next;
    }
    return pre;
}

DoubleNode *testReverseDoubleList(DoubleNode *head) {
    if (head == nullptr) {
        return NULL;
    }
    vector<DoubleNode *> list;
    while (head) {
        list.push_back(head);
        head = head->next;
    }
    list[0]->next = nullptr;
    DoubleNode *pre = list[0];
    int n = list.size();
    for (int i = 1; i < n; i++) {
        DoubleNode *cur = list[i];
        cur->last = nullptr;
        cur->next = pre;
        pre->last = cur;
        pre = cur;
    }
    return list[n - 1];
}

DoubleNode *createDouble(vector<int> &ve) { //尾插法构建双链表
    DoubleNode *head = nullptr, *pre = nullptr, *next = nullptr, *s = nullptr;
    for (int num:ve) {
        if (!head) {
            head = s = new DoubleNode(num);
        } else {
            auto *p = new DoubleNode(num);
            s->next = p;
            p->last = s;
            s = s->next;
        }
    }
    return head;
}

ListNode *createList(vector<int> &ve)//尾插法构建单链表
{
    ListNode *head = nullptr, *s = nullptr;
    for (int each:ve) {
        if (!head) {
            head = s = new ListNode(each);
        } else {
            ListNode *p = new ListNode(each);
            s->next = p;
            s = s->next;
        }
    }
    return head;
}

void printArr(vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void printDoubleList(DoubleNode *head) {
    do {
        cout << head->val << " ";
        head = head->next;
    } while (head);
}

//打印单链表
void printList(ListNode *head) {
    do {
        cout << head->val << " ";
        head = head->next;
    } while (head);
}
//函数名：generateRandomVector
//函数功能描述：随机数组（样本）生成器
//函数参数： size    生成数组最大尺寸
//         value   数组每个元素的最大值
//返回值：  vector<int> 生成的数组

vector<int> generateRandomVector(int maxSize, int maxValue) {
    //time 函数返回从 1970 年 1 月 1 日午夜开始到现在逝去的秒数，因此每次运行程序时，它都将提供不同的种子值。
    srand((int) time(NULL));//为随机数生成器产生随机种子
    vector<int> result(rand() % (maxSize + 1));
    for (int i = 0; i < result.size(); i++) {
        result[i] = rand() % (maxValue + 1);
    }
    return result;
}

bool checkLinkedListReverse(vector<int> &origin, ListNode *head) {
    for (int i = origin.size() - 1; i >= 0; i--) {
        if (origin[i] != head->val) {
            return false;
        }
        head = head->next;
    }
    return true;
}

bool checkDoubleListReverse(vector<int> &origin, DoubleNode *head) {
    DoubleNode *end = nullptr;
    for (int i = origin.size() - 1; i >= 0; i--) {
        if (origin[i] != head->val) {
            return false;
        }
        end = head;
        head = head->next;
    }
    //这一个循环结束后,end指针会来到链表反转之后的尾节点
    for (int i = 0; i < origin.size(); i++) {
        if (origin[i] != end->val) {
            return false;
        }
        end = end->last;// end指针不断往前走
    }
    return true;
}
//大样本测试
//函数名：main
//函数功能描述：大样本测试
//函数参数： size    生成数组最大尺寸
//         value   数组每个元素的最大值
//返回值：  vector<int> 生成的数组

int main() {
    int test_time = 100000;//进行测试的次数
    int size = 200;//生成数组的最大长度
    int value = 200;//生成数组的最大值
    bool is_accept = true;
    cout << "测试开始" << endl;
    for (int i = 0; i < test_time; i++) {
        vector<int> arr1 = generateRandomVector(size, value);
        ListNode *node1 = createList(arr1);
        node1 = reverseLinkedList(node1);
        if (!checkLinkedListReverse(arr1, node1)) {
            cout << "出错了" << endl;
        }

        vector<int> arr2 = generateRandomVector(size, value);
        ListNode *node2 = createList(arr2);
        node2 = testReverseLinkedList(node2);
        if (!checkLinkedListReverse(arr2, node2)) {
            cout << "出错了" << endl;
        }

        vector<int> arr3 = generateRandomVector(size, value);
        DoubleNode *node3 = createDouble(arr3);
        node3 = reverseDoubleList(node3);
        if (!checkDoubleListReverse(arr3, node3)) {
            cout << "出错了" << endl;
        }

        vector<int> arr4 = generateRandomVector(size, value);
        DoubleNode *node4 = createDouble(arr4);
        node4 = testReverseDoubleList(node4);
        if (!checkDoubleListReverse(arr4, node4)) {
            cout << "出错了" << endl;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}