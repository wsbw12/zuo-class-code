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

// 判断一个树是否是 平衡二叉树
struct Info {
    bool isBalanced;
    int height;

    Info() : isBalanced(true), height(0) {}

    Info(bool x, int y) : isBalanced(x), height(y) {}
};

Info process1(TreeNode *root) {
    if (root == nullptr) {
        return {true, 0};
    }
    Info leftInfo = process1(root->left);
    Info rightInfo = process1(root->right);
    int height = max(leftInfo.height, rightInfo.height) + 1;
    bool isBalanced = leftInfo.isBalanced && rightInfo.isBalanced && abs(leftInfo.height - rightInfo.height) < 2;
    return {isBalanced, height};
}

bool isBalanced1(TreeNode *root) {
    return process1(root).isBalanced;
}

int getHeight(TreeNode *node) {
    if (node == nullptr) {
        return 0;
    }
    int left_height = getHeight(node->left);
    if (left_height == -1) {
        return -1;
    }
    int right_height = getHeight(node->right);
    if (right_height == -1) {
        return -1;
    }
    int res;
    //如果左右子树高度之差大于1,那么就不是平衡二叉树
    if (abs(left_height - right_height) > 1) {
        res = -1;
    } else {
        res = max(left_height, right_height) + 1;
    }
    return res;
}

bool isBalanced2(TreeNode *root) {
    int num = getHeight(root);
    if (num == -1) {
        return false;
    } else {
        return true;
    }
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
    int maxLevel = 5;
    int maxValue = 100;
    int test_time = 1000000;
    cout << "测试开始" << endl;
    clock_t start, end;
    start = clock();
    for (int i = 0; i < test_time; i++) {
        TreeNode *head = generateRandomBST(maxLevel, maxValue);
        if (isBalanced1(head) != isBalanced2(head)) {
            cout << "测试错误" << endl;
            break;
        }
    }
    end = clock();   //结束时间
    cout << "测试结束" << endl;
    cout << "测试的时间为: " << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ）
    return 0;
}