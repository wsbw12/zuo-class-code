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

// 判断一个树是否是 搜索二叉树
struct Info {
    int max_num;
    int min_num;
    bool isBST;

    Info() : max_num(INT_MIN), min_num(INT_MAX), isBST(true) {}

    Info(int a, int b, bool c) : max_num(a), min_num(b), isBST(c) {}

};

bool dfs(TreeNode *root, long long min_val, long long max_val);

Info *process(TreeNode *head) {
    auto temp = new Info();
    if (head == nullptr) {
        return temp;
    }
    Info *leftInfo = process(head->left);
    Info *rightInfo = process(head->right);
    int max_num = head->val;
    // 求整个树的最大值和最小值
    int min_num = head->val;
    if (leftInfo != temp) {
        max_num = max(max_num, leftInfo->max_num);
        min_num = min(min_num, leftInfo->min_num);
    }
    if (rightInfo != temp) {
        max_num = max(max_num, rightInfo->max_num);
        min_num = min(min_num, rightInfo->min_num);
    }
    bool isBST = true;
    if (leftInfo != temp && !leftInfo->isBST) {
        isBST = false;
    }
    if (rightInfo != temp && !rightInfo->isBST) {
        isBST = false;
    }
    if (leftInfo != temp && leftInfo->max_num >= head->val) {
        isBST = false;
    }
    if (rightInfo != temp && rightInfo->min_num <= head->val) {
        isBST = false;
    }
    return new Info(max_num, min_num, isBST);

}

bool isBST(TreeNode *head) {
    if (head == nullptr) {
        return true;
    }
    return process(head)->isBST;
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

bool isValidBST(TreeNode *root) {
    return dfs(root, INT_MIN, INT_MAX);
}

bool dfs(TreeNode *root, long long min_val, long long max_val) {
    if (root == nullptr) {
        return true;
    }
    if (root->val < min_val || root->val > max_val) {
        return false;
    }
    return dfs(root->left, min_val, root->val - 1ll) && dfs(root->right, root->val + 1ll, max_val);
    //1ll为long long 类型的1
}

int main() {
    int maxLevel = 5;
    int maxValue = 100;
    int test_time = 10000000;
    cout << "测试开始" << endl;
    clock_t start, end;
    start = clock();
    for (int i = 0; i < test_time; i++) {
        TreeNode *head = generateRandomBST(maxLevel, maxValue);
        if (isBST(head) != isValidBST(head)) {
            cout << "测试错误" << endl;
            break;
        }
    }
    end = clock();   //结束时间
    cout << "测试结束" << endl;
    cout << "测试的时间为: " << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ）
    return 0;
}