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

// 用队列实现栈
class TwoQueueStack {
public:
    queue<int> q;
    queue<int> help;

    void push(int value) {
        q.push(value);
    }

    int poll() {
        while (q.size() > 1) {
            help.push(q.front());
            q.pop();
        }
        int ans = q.front();
        q.pop();
        // 本质上是将q,help两个队列互换,相当于交换了内存地址
        queue<int> temp = q;
        q = help;
        help = temp;
        return ans;
    }

    int peek() {
        while (q.size() > 1) {
            help.push(q.front());
            q.pop();
        }
        int ans = q.front();
        q.pop();
        // 为啥要在help中放入ans,因为这个函数本质是返回栈顶元素,并不是弹出,而且后面还要对q,help进行交换
        // 所以要将ans放入help中,在进行交换之后,q中的元素并没有改变
        help.push(ans);
        queue<int> temp = q;
        q = help;
        help = temp;
        return ans;
    }

    bool isEmpty() {
        return q.empty();
    }
};

int main() {
    cout << "test begin" << endl;
    TwoQueueStack myStack;
    stack<int> test;
    srand((unsigned) time(NULL));
    int test_time = 12000;
    int max_num = 100;
    int range = 10;
    for (int i = 0; i < test_time; i++) {
        if (myStack.isEmpty()) {
            if (!test.empty()) {
                cout << "出错了" << endl;
            }
            int num = (int) (rand() % max_num);
            myStack.push(num);
            test.push(num);
        } else {
            if (((int) (rand() % range)) < 3) {
                int num = (int) (rand() % max_num);
                myStack.push(num);
                test.push(num);
            } else if (((int) (rand() % range)) < 5) {
                if (myStack.peek() != test.top()) {
                    cout << "出错了" << endl;
                }
            } else if (((int) (rand() % range)) < 8) {
                int num1 = myStack.poll();
                int num2 = test.top();
                test.pop();
                if (num1 != num2) {
                    cout << "出错了" << endl;
                }
            } else {
                if (myStack.isEmpty() != test.empty()) {
                    cout << "出错了" << endl;
                }
            }
        }
    }
    cout << "test finished" << endl;
    return 0;
}