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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}

};

struct Info {
    TreeNode *maxSubBSTHead;
    int maxSubBSTSize;
    int min_num;
    int max_num;

    Info() : maxSubBSTHead(nullptr), maxSubBSTSize(0), min_num(INT_MAX), max_num(INT_MIN) {}

    Info(TreeNode *h, int a, int b, int c) : maxSubBSTHead(h), maxSubBSTSize(a), min_num(b), max_num(c) {}
};
//给定一棵二叉树的头节点head，返回这颗二叉树中最大的二叉搜索子树的头节点

void in(TreeNode *head, vector<TreeNode *> &arr) {
    if (head == nullptr) {
        return;
    }
    in(head->left, arr);
    arr.push_back(head);
    in(head->right, arr);
}

int getBSTSize(TreeNode *head) {
    if (head == nullptr) {
        return 0;
    }
    vector<TreeNode *> arr;
    in(head, arr);
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i]->val <= arr[i - 1]->val) {
            return 0;
        }
    }
    return arr.size();
}

TreeNode *maxSubBSTHead1(TreeNode *head) {
    if (head == nullptr) {
        return nullptr;
    }
    if (getBSTSize(head)) {
        return head;
    }
    TreeNode *leftAns = maxSubBSTHead1(head->left);
    TreeNode *rightAns = maxSubBSTHead1(head->right);
    return getBSTSize(leftAns) >= getBSTSize(rightAns) ? leftAns : rightAns;
}

Info *process(TreeNode *head) {
    Info *temp = new Info();
    if (head == nullptr) {
        return temp;
    }
    Info *leftInfo = process(head->left);
    Info *rightInfo = process(head->right);
    int min_num = head->val;
    int max_num = head->val;
    TreeNode *maxSubBSTHead = nullptr;
    int maxSubBSTSize = 0;
    if (leftInfo != temp) {
        min_num = min(min_num, leftInfo->min_num);
        max_num = max(max_num, leftInfo->max_num);
        maxSubBSTHead = leftInfo->maxSubBSTHead;
        maxSubBSTSize = leftInfo->maxSubBSTSize;
    }
    if (rightInfo != temp) {
        min_num = min(min_num, rightInfo->min_num);
        max_num = max(max_num, rightInfo->max_num);
        if (rightInfo->maxSubBSTSize > maxSubBSTSize) {
            maxSubBSTHead = rightInfo->maxSubBSTHead;
            maxSubBSTSize = rightInfo->maxSubBSTSize;
        }
    }
    if ((leftInfo == temp ? true : (leftInfo->maxSubBSTHead == head->left && leftInfo->max_num < head->val))
        && (rightInfo == temp ? true : (rightInfo->maxSubBSTHead == head->right && rightInfo->min_num > head->val))) {
        maxSubBSTHead = head;
        maxSubBSTSize = (leftInfo == temp ? 0 : leftInfo->maxSubBSTSize)
                        + (rightInfo == temp ? 0 : rightInfo->maxSubBSTSize) + 1;
    }
    Info *res = new Info(maxSubBSTHead, maxSubBSTSize, min_num, max_num);
    return res;
}

TreeNode *maxSubBSTHead2(TreeNode *head) {
    if (head == nullptr) {
        return nullptr;
    }
    return process(head)->maxSubBSTHead;
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
    int maxLevel = 4;
    int maxValue = 100;
    int test_time = 1000000;
    clock_t start, end;
    start = clock();
    cout << "测试开始" << endl;
    for (int i = 0; i < test_time; i++) {
        TreeNode *head = generateRandomBST(maxLevel, maxValue);
        if (maxSubBSTHead1(head) != maxSubBSTHead2(head)) {
            cout << "测试错误" << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
    end = clock();   //结束时间
    cout << "测试的时间为: " << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ）
    return 0;
}