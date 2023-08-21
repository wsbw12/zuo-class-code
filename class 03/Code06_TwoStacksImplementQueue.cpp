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

// 用栈实现队列
class TwoStacksQueue {
    // 始终要保证pop栈里面的栈顶元素是队列中要返回的对头元素
public:
    stack<int> stackPush;
    stack<int> stackPop;

private:
    void pushToPop() { // 将push栈里面的内容全部导出到pop栈中
        if (stackPop.empty()) // 只有在pop栈为空的时候,才能将数据倒进去
        {
            while (!stackPush.empty()) {
                stackPop.push(stackPush.top());
                stackPush.pop();
            }
        }
    }

public:
    void add(int pushInt) {
        stackPush.push(pushInt);
        pushToPop();
    }

    int poll() { // 弹出队头元素
        if (stackPush.empty() && stackPop.empty()) {
            cout << "队列为空" << endl;
            return -1;
        }
        pushToPop();
        int num = stackPop.top();
        stackPop.pop();
        return num;
    }

    int peak() // 返回队头元素的值
    {
        if (stackPop.empty() && stackPush.empty()) {
            cout << "队列为空" << endl;
            return -1;
        }
        pushToPop();
        return stackPop.top();
    }
};

int main() {
    TwoStacksQueue test;
    test.add(1);
    test.add(2);
    test.add(3);
    cout << test.peak() << endl;
    cout << test.poll() << endl;
    cout << test.peak() << endl;
    cout << test.poll() << endl;
    cout << test.peak() << endl;
    cout << test.poll() << endl;
    return 0;
}