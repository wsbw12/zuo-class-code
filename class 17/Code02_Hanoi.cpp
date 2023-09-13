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

void leftToRight(int n);

void leftToMid(int n);

void rightToMid(int n);

void midToRight(int n);

void midToLeft(int n);

void rightToLeft(int n);

void func(int N, string from, string to, string other);

class Record {
public:
    int level;
    string from;
    string to;
    string other;

    Record(int l, string f, string t, string o) : level(l), from(f), to(t), other(o) {};
};

void hanoi1(int n) {
    leftToRight(n);
}

// 请把1~N层圆盘 从左 -> 右
void leftToRight(int n) {
    if (n == 1) {
        cout << "Move 1 from left to right" << endl;
        return;
    }
    leftToMid(n - 1);
    cout << "Move " << n << " from left to right" << endl;
    midToRight(n - 1);
}

// 请把1~N层圆盘 从左 -> 中
void leftToMid(int n) {
    if (n == 1) {
        cout << "Move 1 from left to mid" << endl;
        return;
    }
    leftToRight(n - 1);
    cout << "Move " << n << " from left to mid" << endl;
    rightToMid(n - 1);
}

void rightToMid(int n) {
    if (n == 1) {
        cout << "Move 1 from right to mid" << endl;
        return;
    }
    rightToLeft(n - 1);
    cout << "Move " << n << " from right to mid" << endl;
    leftToMid(n - 1);
}

void midToRight(int n) {
    if (n == 1) {
        cout << "Move 1 from mid to right" << endl;
        return;
    }
    midToLeft(n - 1);
    cout << "Move " << n << " from mid to right" << endl;
    leftToRight(n - 1);
}


void midToLeft(int n) {
    if (n == 1) {
        cout << "Move 1 from mid to left" << endl;
        return;
    }
    midToRight(n - 1);
    cout << "Move " << n << " from mid to left" << endl;
    rightToLeft(n - 1);
}

void rightToLeft(int n) {
    if (n == 1) {
        cout << "Move 1 from right to left" << endl;
        return;
    }
    rightToMid(n - 1);
    cout << "Move " << n << " from right to left" << endl;
    midToLeft(n - 1);
}


void hanoi2(int n) {
    if (n > 0) {
        func(n, "left", "right", "mid");
    }
}

void func(int N, string from, string to, string other) {
    if (N == 1) {
        cout << "Move 1 from " << from << "to " << to << endl;
        return;
    } else {
        func(N - 1, from, other, to);
        cout << "Move " << N << " from " << from << " to " << to << endl;
        func(N - 1, other, to, from);
    }
}

// 之前的迭代版本，很多同学表示看不懂
// 所以我换了一个更容易理解的版本
// 看注释吧！好懂！
// 你把汉诺塔问题想象成二叉树
// 比如当前还剩i层，其实打印这个过程就是：
// 1) 去打印第一部分 -> 左子树
// 2) 打印当前的动作 -> 当前节点
// 3) 去打印第二部分 -> 右子树
// 那么你只需要记录每一个任务 : 有没有加入过左子树的任务
// 就可以完成迭代对递归的替代了
void hanoi3(int N) {
    if (N < 1) {
        return;
    }
    // 每一个记录进栈
    stack<Record *> stk;
    // 记录每一个记录有没有加入过左子树的任务
    unordered_set<Record *> finishLeft;
    // 初始的任务，认为是种子
    Record *temp = new Record(N, "left", "right", "mid");
    stk.push(temp);
    while (!stk.empty()) {
        // 弹出当前任务
        Record *cur = stk.top();
        stk.pop();
        if (cur->level == 1) {
            // 如果层数只剩1了
            // 直接打印
            cout << "Move 1 from " << cur->from << " to " << cur->to << endl;
        } else {
            // 如果不只1层
            if (!finishLeft.count(cur)) {
                // 如果当前任务没有加入过左子树的任务
                // 现在就要加入了！
                // 把当前的任务重新压回去，因为还不到打印的时候
                // 再加入左子树任务！
                finishLeft.insert(cur);
                stk.push(cur);
                stk.push(new Record(cur->level - 1, cur->from, cur->other, cur->to));
            } else {
                // 如果当前任务加入过左子树的任务
                // 说明此时已经是第二次弹出了！
                // 说明左子树的所有打印任务都完成了
                // 当前可以打印了！
                // 然后加入右子树的任务
                // 当前的任务可以永远的丢弃了！
                // 因为完成了左子树、打印了自己、加入了右子树
                // 再也不用回到这个任务了
                cout << "Move " << cur->level << " from " << cur->from << " to " << cur->to << endl;
                stk.push(new Record(cur->level - 1, cur->other, cur->to, cur->from));
            }

        }
    }

}

int main() {
    int n = 3;
    hanoi1(n);
    cout << "==============" << endl;
    hanoi2(n);
    cout << "==============" << endl;
    hanoi3(n);
    cout << "==============" << endl;
    return 0;
}