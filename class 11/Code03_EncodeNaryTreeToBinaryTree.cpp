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

class Node {
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node *> _children) {
        val = _val;
        children = _children;
    }
};

// LeetCode431：将 N 叉树编码为二叉树
// https://leetcode-cn.com/problems/encode-n-ary-tree-to-binary-tree/
// 设计一个算法，可以将 N 叉树编码为二叉树，并能将该二叉树解码为原 N 叉树。
// 一个 N 叉树是指每个节点都有不超过 N 个孩子节点的有根树。
// 第一个子节点2接到父节点1的left，其余的兄弟节点 3，4 都接在其左边兄弟节点的right

TreeNode *dfs_en(vector<Node *> children);

vector<Node *> dfs_de(TreeNode *root);

TreeNode *encode(Node *root) {  // 将N叉树编码为二叉树
    if (root == nullptr) {
        return nullptr;
    }
    // N叉树的头节点一定是二叉树的头节电
    auto *head = new TreeNode(root->val);
    // 将N叉树中每个节点(x)的所有儿子节点全部挂在对应二叉树的节点(x)的左子树的右孩子上
    head->left = dfs_en(root->children);
    return head;
}

TreeNode *dfs_en(vector<Node *> children) {
    TreeNode *head = nullptr;
    TreeNode *cur = nullptr;
    for (auto child:children) { // 遍历每个孩子节点
        auto *tNode = new TreeNode(child->val);
        if (head == nullptr) {
            head = tNode;
        } else {
            cur->right = tNode;
        }
        cur = tNode;
        cur->left = dfs_en(child->children);
    }
    return head;
}


// 将二叉树解码回N叉树
Node *decode(TreeNode *root) {
    if (root == nullptr) {
        return nullptr;
    }
    return new Node(root->val, dfs_de(root->left));
}

vector<Node *> dfs_de(TreeNode *root) {
    vector<Node *> children;
    while (root != nullptr) {
        Node *cur = new Node(root->val, dfs_de(root->left));
        children.push_back(cur);
        root = root->right;
    }
    return children;
}

int main() {

    return 0;
}