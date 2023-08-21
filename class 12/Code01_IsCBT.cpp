```
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

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}

};

// 判断一个树是否是完全二叉树

bool isCBT1(TreeNode *head) {
    if (head == nullptr) {
        return true;
    }
    queue<TreeNode *> q;
    bool leaf = false; // 用来判断是否 遇到了 左右两个孩子不双全的节点
    TreeNode *leftChildren = nullptr;
    TreeNode *rightChildren = nullptr;
    q.push(head);
    while (!q.empty()) {
        head = q.front();
        q.pop();
        leftChildren = head->left;
        rightChildren = head->right;
        // 1.当碰到这个节点左孩子为空右孩子不为空的情况,肯定不是完全二叉树
        // 2.当已经遇到了左右两个孩子不是全部存在的情况时,后面的节点不是叶节点说明也不是完全二叉树
        if ((leftChildren == nullptr && rightChildren != nullptr) || (leaf && (leftChildren || rightChildren))) {
            return false;
        }
        if (leftChildren) {
            q.push(leftChildren);
        }
        if (rightChildren) {
            q.push(rightChildren);
        }
        if (leftChildren == nullptr || rightChildren == nullptr) {
            leaf = true;
        }
    }
    return true;
}


// 用二叉树的递归套路讨论
struct Info {
    bool isFull; // 是否是 满二叉树
    bool isCBT;  // 是否是 完全二叉树
    int height;  // 高度

    Info() : isFull(true), isCBT(true), height(0) {}

    Info(bool a, bool b, int c) : isFull(a), isCBT(b), height(c) {}
};

Info process(TreeNode *head) {
    if (head == nullptr) {
        return {true, true, 0};
    }
    Info leftInfo = process(head->left);
    Info rightInfo = process(head->right);
    int height = max(leftInfo.height, rightInfo.height) + 1;
    bool isFull = leftInfo.isFull && rightInfo.isFull && leftInfo.height == rightInfo.height;
    bool isCBT = false;
    if (isFull) { // 如果是满二叉树的情况下,那么此时也是完全二叉树
        isCBT = true;
    } else {
        // 如果左子树是满二叉树 并且 右子树是满二叉树 并且 左子树的高度等于右子树的高度加一
        if (leftInfo.isFull && rightInfo.isFull && leftInfo.height == rightInfo.height + 1) {
            isCBT = true;
        } else if (leftInfo.isCBT && rightInfo.isFull && leftInfo.height == rightInfo.height + 1) {
            // 如果左子树是完全二叉树 并且 右子树是满二叉树 并且 左子树的高度等于右子树的高度加一
            isCBT = true;
        } else if (leftInfo.isFull && rightInfo.isCBT && leftInfo.height == rightInfo.height) {
            // 如果左子树是满二叉树 并且 右子树是完全二叉树 并且 左子树的高度等于右子树的高度
            isCBT = true;
        }
    }
    return {isFull, isCBT, height};
}


bool isCBT2(TreeNode *head) {
    if (head == nullptr) {
        return true;
    }
    return process(head).isCBT;
}


TreeNode *generate(int level, int maxLevel, int maxValue) {
    if (level > maxLevel) {
        return nullptr;
    }
    auto *head = new TreeNode((int) (rand() % maxValue));
    head->left = generate(level + 1, maxLevel, maxValue);
    head->right = generate(level + 1, maxLevel, maxValue);
    return head;
}

TreeNode *generateRandomBST(int maxLevel, int maxValue) {
    return generate(1, maxLevel, maxValue);
}

int main() {
    cout.precision(2);
    cout.setf(ios::fixed, ios::floatfield);
    int maxLevel = 5;
    int maxValue = 100;
    int test_time = 1000000;
    clock_t start, end;
    start = clock();
    cout << "测试开始" << endl;
    for (int i = 0; i < test_time; i++) {
        TreeNode *head = generateRandomBST(maxLevel, maxValue);
        if (isCBT1(head) != isCBT2(head)) {
            cout << "测试失败" << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
    end = clock();   //结束时间
    cout << "测试的时间为: " << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ）
    return 0;
}
```