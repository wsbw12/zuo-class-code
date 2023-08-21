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

// 给定一棵二叉树的头节点head，任何两个节点之间都存在距离，返回整棵二叉树的最大距离
struct Info {
    int maxDistance;
    int height;

    Info() : maxDistance(0), height(0) {}

    Info(int a, int b) : maxDistance(a), height(b) {}

};


void fillPreList(TreeNode *head, vector<TreeNode *> &arr) {
    if (head == nullptr) {
        return;
    }
    arr.push_back(head);
    fillPreList(head->left, arr);
    fillPreList(head->right, arr);
}


vector<TreeNode *> getPreList(TreeNode *head) {
    vector<TreeNode *> arr;
    fillPreList(head, arr);
    return arr;
}

void fillParentMap(TreeNode *head, unordered_map<TreeNode *, TreeNode *> &map) {
    if (head->left) {
        map[head->left] = head;
        fillParentMap(head->left, map);
    }
    if (head->right) {
        map[head->right] = head;
        fillParentMap(head->right, map);
    }
}

unordered_map<TreeNode *, TreeNode *> getParentMap(TreeNode *head) {
    unordered_map<TreeNode *, TreeNode *> map;
    map[head] = nullptr;
    fillParentMap(head, map);
    return map;
}

int distance(unordered_map<TreeNode *, TreeNode *> parentMap, TreeNode *o1, TreeNode *o2) {
    unordered_set<TreeNode *> o1Set;
    TreeNode *cur = o1;
    o1Set.insert(cur);
    while (parentMap[cur]) {
        cur = parentMap[cur];
        o1Set.insert(cur);
    }
    cur = o2;
    while (o1Set.count(cur) == 0) {
        cur = parentMap[cur];
    }
    TreeNode *lowestAncestor = cur;
    cur = o1;
    int distance1 = 1;
    while (cur != lowestAncestor) {
        cur = parentMap[cur];
        distance1++;
    }
    cur = o2;
    int distance2 = 1;
    while (cur != lowestAncestor) {
        cur = parentMap[cur];
        distance2++;
    }
    return distance1 + distance2 - 1;
}

int maxDistance1(TreeNode *head) {
    if (head == nullptr) {
        return 0;
    }
    vector<TreeNode *> arr = getPreList(head);
    unordered_map<TreeNode *, TreeNode *> parentMap = getParentMap(head);
    int max_num = 0;
    for (int i = 0; i < arr.size(); i++) {
        for (int j = i; j < arr.size(); j++) {
            max_num = max(max_num, distance(parentMap, arr[i], arr[j]));
        }
    }
    return max_num;
}


// 最大距离分为三种情况
// 1.这个最大距离不经过头节点   ---> 那么就是在它左子树的最大距离和右子树的最大距离之间求max
// 2.这个最大距离经过头节点     ---> 那么就是左树的最大高度+右树的最大高度+1

Info process(TreeNode *root) {
    if (root == nullptr) {
        return {0, 0};
    }
    Info leftInfo = process(root->left);
    Info rightInfo = process(root->right);
    int height = max(leftInfo.height, rightInfo.height) + 1;
    int p1 = leftInfo.maxDistance;
    int p2 = rightInfo.maxDistance;
    int p3 = leftInfo.height + rightInfo.height + 1;
    int maxDistance = max(max(p1, p2), p3);
    return {maxDistance, height};
}

int maxDistance(TreeNode *head) {
    return process(head).maxDistance;
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
        if (maxDistance(head) != maxDistance1(head)) {
            cout << maxDistance(head) << endl;
            cout << maxDistance1(head) << endl;
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