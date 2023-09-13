#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <unordered_map>
#include <queue>
#include <cstdlib>
#include <unordered_set>
#include <set>

using namespace std;

// 将一个栈中的元素进行逆序
int f(stack<int> &stk);
void reverse(stack<int> &stk) {
    if (stk.empty()) {
        return;
    }
    int i = f(stk);
    reverse(stk);
    stk.push(i);
}

// 栈底元素移除掉
// 上面的元素盖下来
// 返回移除掉的栈底元素
int f(stack<int> &stk) {
    int result = stk.top();
    stk.pop();
    if (stk.empty()) {
        return result;
    } else {
        int last = f(stk);
        stk.push(result);
        return last;
    }
}

int main() {
    stack<int> test;
    test.push(1);
    test.push(2);
    test.push(3);
    test.push(4);
    test.push(5);
    reverse(test);
    while (!test.empty()) {
        cout << test.top() << endl;
        test.pop();
    }
    cout << "=================" << endl;
    return 0;
}