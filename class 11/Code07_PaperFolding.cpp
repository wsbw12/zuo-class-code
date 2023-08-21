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

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//折纸问题
//请把一段纸条竖着放在桌子上，然后从纸条的下边向上方对折1次，压出折痕后展开
//此时折痕是凹下去的，即折痕突起的方向指向纸条的背面
//如果从纸条的下边向上方连续对折2次，压出折痕后展开
//此时有三条折痕，从上到下依次是下折痕、下折痕和上折痕。
//给定一个输入参数N，代表纸条都从下边向上方连续对折N次
//请从上到下打印所有折痕的方向。
//N=1时，打印: down
//N=2时，打印: down down up

// 当前你来了一个节点，脑海中想象的！
// 这个节点在第i层，一共有N层，N固定不变的
// 这个节点如果是凹的话，down = T
// 这个节点如果是凸的话，down = F
// 函数的功能：中序打印以你想象的节点为头的整棵树！
// 左子树都是凹 右子树都是凸
void dfs(int i, int n, bool down) {
    if (i > n) {
        return;
    }
    dfs(i + 1, n, true);
    down ? cout << "凹 " : cout << "凸 ";
    dfs(i + 1, n, false);
}

void printAllFolds(int n) {
    dfs(1, n, true);
    cout << endl;
}

int main() {
    int n = 4;
    clock_t start, end;
    start = clock();
    printAllFolds(n);
    end = clock();   //结束时间
    cout << "测试的时间为: " << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ）
    return 0;
}