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

using namespace std;

//给定一棵二叉树的头节点head，和另外两个节点a和b，返回a和b的最低公共祖先
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}

};

struct Info {
    bool findA;
    bool findB;
    TreeNode *ans;

    Info() : findA(false), findB(false), ans(nullptr) {}

    Info(bool a, bool b, TreeNode *c) : findA(a), findB(b), ans(c) {}
};

Info process(TreeNode *head, TreeNode *a, TreeNode *b) {
    if (head == nullptr) {
        return {false, false, nullptr};
    }
    Info leftInfo = process(head->left, a, b);
    Info rightInfo = process(head->right, a, b);
    bool findA = (head == a) || (leftInfo.findA) || (rightInfo.findA);
    bool findB = (head == b) || (leftInfo.findB) || (rightInfo.findB);
    TreeNode *ans = nullptr;
    if (leftInfo.ans != nullptr) { // 如果左树找到了答案,那么就返回左树的这个答案
        ans = leftInfo.ans;
    } else if (rightInfo.ans != nullptr) {
        ans = rightInfo.ans;
    } else { // 如果左树上没有答案并且右树上没有答案
        if (findA && findB) { // 此时也找到了a和b那么答案就是头节电
            ans = head;
        }
    }
    return {findA, findB, ans};
}

TreeNode *lowestAncestor(TreeNode *head, TreeNode *a, TreeNode *b) {
    return process(head, a, b).ans;
}


void fillParentMap(TreeNode *head, unordered_map<TreeNode *, TreeNode *> &parentMap) {
    if (head->left) {
        parentMap[head->left] = head;
        fillParentMap(head->left, parentMap);
    }
    if (head->right) {
        parentMap[head->right] = head;
        fillParentMap(head->right, parentMap);
    }
}

TreeNode *lowestAncestor1(TreeNode *head, TreeNode *a, TreeNode *b) {
    if (head == nullptr) {
        return nullptr;
    }
    unordered_map<TreeNode *, TreeNode *> parentMap;
    parentMap[head] = nullptr;
    fillParentMap(head, parentMap);
    unordered_set<TreeNode *> o1Set;
    TreeNode *cur = a;
    o1Set.insert(cur);
    while (parentMap.count(cur) != 0) {
        cur = parentMap[cur];
        o1Set.insert(cur);
    }
    cur = b;
    while (!o1Set.count(cur)) {
        cur = parentMap[cur];
    }
    return cur;
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

void fillPrelist(TreeNode *head, vector<TreeNode *> &arr) {
    if (head == nullptr) {
        return;
    }
    arr.push_back(head);
    fillPrelist(head->left, arr);
    fillPrelist(head->right, arr);
}

TreeNode *pickRandomOne(TreeNode *head) {
    if (head == nullptr) {
        return nullptr;
    }
    vector<TreeNode *> arr;
    fillPrelist(head, arr);
    int randomIndex = (int) (rand() % arr.size());
    return arr[randomIndex];
}

int main() {
    cout.precision(2);
    cout.setf(ios::fixed, ios::floatfield);
    int maxLevel = 4;
    int maxValue = 100;
    int test_time = 1000000;
    clock_t start, end;
    start = clock();
    cout << "测试开始" << endl;
    for (int i = 0; i < test_time; i++) {
        TreeNode *head = generateRandomBST(maxLevel, maxValue);
        TreeNode *o1 = pickRandomOne(head);
        TreeNode *o2 = pickRandomOne(head);
        if (lowestAncestor(head, o1, o2) != lowestAncestor1(head, o1, o2)) {
            cout << "测试失败" << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
    end = clock();   //结束时间
    cout << "测试的时间为: " << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ）
    return 0;
}