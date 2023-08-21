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

// 用链表实现双端队列和队列以及栈
struct DoubleNode {
    int val;
    DoubleNode *last;
    DoubleNode *next;

    DoubleNode() : val(0), next(nullptr), last(nullptr) {}

    DoubleNode(int x) : val(x), next(nullptr), last(nullptr) {}

    DoubleNode(int x, DoubleNode *next, DoubleNode *last) : val(x), next(next), last(last) {}

};

class DoubleEndsQueue {
public:
    DoubleNode *head;
public:
    DoubleNode *tail;
public:
    void addFromHead(int value) { // 在双端队列中从头部添加元素
        DoubleNode *cur = new DoubleNode(value);
        if (head == nullptr) {
            head = cur;
            tail = cur;
        } else {
            cur->next = head;
            head->last = cur;
            head = cur;
        }
    }

    void addFromTail(int value) { // 在双端队列中从尾部添加元素
        DoubleNode *cur = new DoubleNode(value);
        if (head == nullptr) {
            head = cur;
            tail = cur;
        } else {
            cur->last = tail;
            tail->next = cur;
            tail = cur;
        }
    }

    int popFromHead() { // 从头部弹出一个元素
        if (head == nullptr) {
            return NULL;
        }
        DoubleNode *cur = head;
        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            cur->next = nullptr;
            head->last = nullptr;
        }
        return cur->val;
    }

    int popFromBottom() {
        if (head == nullptr) {
            return NULL;
        }
        DoubleNode *cur = tail;
        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            tail = tail->last;
            tail->next = cur;
            cur->last = nullptr;
        }
        return cur->val;
    }

    bool isEmpty() {
        return head == nullptr;
    }
};

class MyStack {
private:
    DoubleEndsQueue stack;
public:
    void push(int value) {
        stack.addFromHead(value);
    }

    int pop() {
        return stack.popFromHead();
    }

    bool isEmpty() {
        return stack.isEmpty();
    }
};

class MyQueue {
private:
    DoubleEndsQueue queue;
public:
    void push(int value) {
        queue.addFromHead(value);
    }

    int poll() {
        return queue.popFromBottom();
    }

    bool isEmpty() {
        return queue.isEmpty();
    }
};


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

// 生成一个[0,range-1]范围内的随机数
int randomNumber(int range) {
    srand((unsigned) time(NULL));
    return (int) (rand() % (range + 1));
}

//大样本测试
//函数名：main
//函数功能描述：大样本测试
//函数参数： size    生成数组最大尺寸
//         value   数组每个元素的最大值
//返回值：  vector<int> 生成的数组

int main() {
    int test_time = 100000;//进行测试的次数
    int oneTestDataNum = 100;
    int range = 10;
    int size = 200;//生成数组的最大长度
    int value = 200;//生成数组的最大值
    srand((unsigned) time(NULL));
    cout << "测试开始" << endl;
    for (int i = 0; i < test_time; i++) {
        MyStack s1;
        MyQueue q1;
        stack<int> s2;
        queue<int> q2;
        for (int j = 0; j < oneTestDataNum; j++) {
            int num = randomNumber(value);
            if (s2.empty()) {
                s1.push(num);
                s2.push(num);
            } else {
                if ((int) (rand() % range) < 5) {
                    s1.push(num);
                    s2.push(num);
                } else {
                    if (s1.pop() != s2.top()) {
                        cout << "出错了" << endl;
                    }
                    s2.pop();
                }
            }
            int numQ = randomNumber(value);
            if (q2.empty()) {
                q1.push(numQ);
                q2.push(numQ);
            } else {
                if ((int) (rand() % range) < 0.5) {
                    q1.push(numQ);
                    q2.push(numQ);
                } else {
                    if (q1.poll() != q2.front()) {
                        cout << "出错了" << endl;
                    }
                    q2.pop();
                }
            }
        }
    }
    cout << "测试结束" << endl;
    return 0;
}