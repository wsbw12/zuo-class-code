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

// 以O(1)的时间复杂度获取栈中的最小值
// 第一种实现方式
class MyStack1 {
private:
    stack<int> stackData; // 正常存放数据的栈
    stack<int> stackMin;  // 以O(1)的时间复杂度获取栈中的最小值
public:
    void push(int num) {
        if (stackMin.empty() || num <= stackMin.top()) { // 如果最小值栈为空,或者要插入的数小于最小栈的栈顶
            stackMin.push(num);
        }
        stackData.push(num);
    }

    int pop() {
        if (stackData.empty()) {
            cout << "your stack is empty." << endl;
            return -1;
        }
        int value = stackData.top();
        stackData.pop();
        if (value == getmin()) {
            stackMin.pop();
        }
        return value;
    }


    int getmin() {
        if (stackMin.empty()) {
            cout << "your stack is empty." << endl;
            return -1;
        }
        return stackMin.top();
    }
};

class MyStack2 {
private:
    stack<int> stackData;
    stack<int> stackMin;
public:

    int getMin() {
        if (stackMin.empty()) {
            cout << "your stack is empty." << endl;
            return -1;
        }
        return stackMin.top();
    }

    void push(int newNum) {
        if (stackMin.empty() || newNum < getMin()) {
            stackMin.push(newNum);
        } else {
            stackMin.push(stackMin.top());
        }
        stackData.push(newNum);
    }

    int pop() {
        if (stackData.empty()) {
            cout << "your stack is empty." << endl;
            return -1;
        }
        stackMin.pop();
        int num = stackData.top();
        stackData.pop();
        return num;
    }
};

int main() {
    MyStack1 stack1;
    stack1.push(3);
    cout << stack1.getmin() << endl;
    stack1.push(4);
    cout << stack1.getmin() << endl;
    stack1.push(1);
    cout << stack1.getmin() << endl;
    cout << stack1.pop() << endl;
    cout << stack1.getmin() << endl;
    cout << "=================" << endl;
    MyStack1 stack2;
    stack2.push(3);
    cout << stack2.getmin() << endl;
    stack2.push(4);
    cout << stack2.getmin() << endl;
    stack2.push(1);
    cout << stack2.getmin() << endl;
    cout << stack2.pop() << endl;
    cout << stack2.getmin() << endl;
    return 0;
}