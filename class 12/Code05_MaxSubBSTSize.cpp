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

// 力扣 333题: https://leetcode.com/problems/largest-bst-subtree
// 给定一棵二叉树的头节点head，返回这颗二叉树中最大的二叉搜索子树的大小
struct Info {
    // 判断一个树是不是二叉搜索树 可以用maxBSTSubtreeSize==allSize来判断
    // 即 我的最大二叉搜索子树的大小跟我自己的大小一样大说明我就是二叉搜索树
    int maxBSTSubtreeSize;
    int allSize;
    int max_num;
    int min_num;

    Info() : maxBSTSubtreeSize(0), allSize(0), max_num(INT_MIN), min_num(INT_MAX) {}

    Info(int a, int b, int c, int d) : maxBSTSubtreeSize(a), allSize(b), max_num(c), min_num(d) {}
};


Info *process(TreeNode *root) {
    // 1.这个二叉搜索树不包含root节点,那么最大的就是在 root->left 和 root->right 中取最大值
    // 2.这个二叉搜索树包含root节点,那么要满足既要满足二叉搜索树的大小关系又要满足左子树是二叉搜索树并且右子树是二叉搜索树
    Info *temp = new Info(); // temp相当于空节点
    if (root == nullptr) {
        return temp;
    }
    Info *leftInfo = process(root->left);
    Info *rightInfo = process(root->right);
    int max_num = root->val;
    int min_num = root->val;
    int allSize = 1;
    if (leftInfo != temp) {
        max_num = max(max_num, leftInfo->max_num);
        min_num = min(min_num, leftInfo->min_num);
        allSize += leftInfo->allSize;
    }
    if (rightInfo != temp) {
        max_num = max(max_num, rightInfo->max_num);
        min_num = min(min_num, rightInfo->min_num);
        allSize += rightInfo->allSize;
    }
    int p1 = -1;
    if (leftInfo != temp) {
        p1 = leftInfo->maxBSTSubtreeSize;
    }
    int p2 = -1;
    if (rightInfo != temp) {
        p2 = rightInfo->maxBSTSubtreeSize;
    }
    int p3 = -1;
    bool leftBST = leftInfo == temp ? true : (leftInfo->maxBSTSubtreeSize == leftInfo->allSize);
    bool rightBST = rightInfo == temp ? true : (rightInfo->maxBSTSubtreeSize == rightInfo->allSize);
    if (leftBST && rightBST) { // 在我的左子树是二叉搜索树并且右子树是二叉搜索树的情况下，比较大小
        bool leftMaxLessX = leftInfo == temp ? true : (leftInfo->max_num < root->val);
        bool rightMinMoreX = rightInfo == temp ? true : (rightInfo->min_num < root->val);
        if (leftMaxLessX && rightMinMoreX) {
            int leftSize = leftInfo == temp ? 0 : leftInfo->allSize;
            int rightSize = rightInfo == temp ? 0 : rightInfo->allSize;
            p3 = leftSize + rightSize + 1;
        }
    }
    return new Info(max(p1, max(p2, p3)), allSize, max_num, min_num);
}


int largestBSTSubtree(TreeNode *head) {
    if (head == nullptr) {
        return 0;
    }
    return process(head)->maxBSTSubtreeSize;
}


int main() {
    return 0;
}