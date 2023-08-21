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

int maxWidthUseMap(TreeNode *head) {
    if (head == nullptr) {
        return 0;
    }
    queue<TreeNode *> q;
    q.push(head);
    // key 在 哪一层，value
    unordered_map<TreeNode *, int> levelMap;
    levelMap[head] = 1;
    int curLevel = 1; // 当前你正在统计哪一层的宽度
    int curLevelNodes = 0; // 当前层curLevel层，宽度目前是多少
    int max_num = 0;
    while (!q.empty()) {
        TreeNode *cur = q.front();
        q.pop();
        int curNodeLevel = levelMap[cur];
        if (cur->left != nullptr) {
            levelMap[cur->left] = curNodeLevel + 1;
            q.push(cur->left);
        }
        if (cur->right != nullptr) {
            levelMap[cur->right] = curNodeLevel + 1;
            q.push(cur->right);
        }
        if (curNodeLevel == curLevel) {
            curLevelNodes++;
        } else {
            max_num = max(max_num, curLevelNodes);
            curLevel++;
            curLevelNodes = 1;
        }
    }
    max_num = max(max_num, curLevelNodes);
    return max_num;
}

int maxWidthNoMap(TreeNode *head) {
    if (head == nullptr) {
        return 0;
    }
    queue<TreeNode *> q;
    q.push(head);
    TreeNode *curEnd = head; // 当前层，最右节点是谁
    TreeNode *nextEnd = nullptr; // 下一层，最右节点是谁
    int max_num = 0;
    int curLevelNodes = 0; // 当前层的节点数
    while (!q.empty()) {
        TreeNode *cur = q.front();
        q.pop();
        if (cur->left != nullptr) {
            q.push(cur->left);
            nextEnd = cur->left;
        }
        if (cur->right != nullptr) {
            q.push(cur->right);
            nextEnd = cur->right;
        }
        curLevelNodes++;
        if (cur == curEnd) {
            max_num = max(max_num, curLevelNodes);
            curLevelNodes = 0;
            curEnd = nextEnd;
        }
    }
    return max_num;
}
// 用对数器进行测试

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
    int maxLevel = 10;
    int maxValue = 100;
    int testTimes = 100000;
    clock_t start, end;
    start = clock();
    cout << "测试开始" << endl;
    for (int i = 0; i < testTimes; i++) {
        TreeNode *head = generateRandomBST(maxLevel, maxValue);
        if (maxWidthUseMap(head) != maxWidthNoMap(head)) {
            cout << "测试错误" << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
    end = clock();   //结束时间
    cout << "测试的时间为: " << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ）
    return 0;
}