#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <unordered_map>

using namespace std;

// 二叉树先序、中序、后序的递归遍历
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void pre(TreeNode *head)//先序遍历
{
    if (head == NULL) {
        return;
    }
    cout << head->val << endl;
    pre(head->left);
    pre(head->right);
}

void mid(TreeNode *head)//中序遍历
{
    if (head == NULL) {
        return;
    }
    mid(head->left);
    cout << head->val << endl;
    mid(head->right);
}

void pos(TreeNode *head)//先序遍历
{
    if (head == NULL) {
        return;
    }
    pos(head->left);
    pos(head->right);
    cout << head->val << endl;
}

int main() {
    TreeNode *head = new TreeNode(1);
    head->left = new TreeNode(2);
    head->right = new TreeNode(3);
    head->left->left = new TreeNode(4);
    head->left->right = new TreeNode(5);
    head->right->left = new TreeNode(6);
    head->right->right = new TreeNode(7);
    cout << "该二叉树的前序遍历为: " << endl;
    pre(head);
    cout << "该二叉树的中序遍历为: " << endl;
    mid(head);
    cout << "该二叉树的后序遍历为: " << endl;
    pos(head);
    return 0;
}