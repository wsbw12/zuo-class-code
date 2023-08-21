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
#include <set>
#include <unordered_set>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 判断一个树是否是 满二叉树
// 收集整棵树的高度h，和节点数n
// 只有满二叉树满足 : 2 ^ h - 1 == n
struct Info {
    int nodes;// 节点的个数
    int height;

    Info() : nodes(0), height(0) {}

    Info(int a, int b) : nodes(a), height(b) {}

};

struct Info2 {
    bool isFull;
    int height;

    Info2() : isFull(true), height(0) {}

    Info2(bool a, int b) : isFull(a), height(b) {}
};


Info process1(TreeNode *head) {
    if (head == nullptr) {
        return {0, 0};
    }
    Info leftInfo = process1(head->left);
    Info rightInfo = process1(head->right);
    int height = max(leftInfo.height, rightInfo.height) + 1;
    int nodes = leftInfo.nodes + rightInfo.nodes + 1;
    return {nodes, height};
}

bool isFull(TreeNode *head) {
    if (head == nullptr) {
        return true;
    }
    Info all = process1(head);
    return (1 << all.height) - 1 == all.nodes;
}

// 第二种方法
// 收集子树是否是 满二叉树
// 收集子树的高度
// 左树满 && 右树满 && 左右树高度一样 -> 整棵树是满的

Info2 process2(TreeNode *root) {
    if (root == nullptr) {
        return {true, 0};
    }
    Info2 leftInfo = process2(root->left);
    Info2 rightInfo = process2(root->right);
    bool isFull = leftInfo.isFull && rightInfo.isFull && leftInfo.height == rightInfo.height;
    int height = max(leftInfo.height, rightInfo.height) + 1;
    return {isFull, height};
}

bool isFull2(TreeNode *head) {
    if (head == nullptr) {
        return true;
    }
    return process2(head).isFull;
}


TreeNode *generate(int level, int maxLevel, int maxValue) {
    if (level > maxLevel || ((int) (rand() % 10) < 5)) {
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

void printInOrder(TreeNode *head, int height, string to, int len);

string getSpace(int num);

void printTree(TreeNode *head) {
    cout << "Binary Tree:" << endl;
    printInOrder(head, 0, "H", 17);
    cout << endl;
}

void printInOrder(TreeNode *head, int height, string to, int len) {
    if (head == nullptr) {
        return;
    }
    printInOrder(head->right, height + 1, "v", len);
    string val = to + to_string(head->val) + to;
    int lenM = val.length();
    int lenL = (len - lenM) / 2;
    int lenR = len - lenM - lenL;
    val = getSpace(lenL) + val + getSpace(lenR);
    cout << getSpace(height * len) + val << endl;
    printInOrder(head->left, height + 1, "^", len);
}

string getSpace(int num) {
    string space = " ";
    for (int i = 0; i < num; i++) {
        space += ' ';
    }
    return space;
}

int main() {
    int maxLevel = 5;
    int maxValue = 100;
    int test_time = 100000;
    cout << "测试开始" << endl;
    clock_t start, end;
    start = clock();
    for (int i = 0; i < test_time; i++) {
        TreeNode *head = generateRandomBST(maxLevel, maxValue);
        if (isFull(head) != isFull2(head)) {
            cout << isFull(head) << endl;
            cout << isFull2(head) << endl;
            printTree(head);
            cout << "测试错误" << endl;
            break;
        }
    }
    end = clock();   //结束时间
    cout << "测试结束" << endl;
    cout << "测试的时间为: " << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ）
    return 0;
}