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
    TreeNode *parent;

    TreeNode() : val(0), left(nullptr), right(nullptr), parent(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr), parent(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right, TreeNode *parent) : val(x), left(left), right(right),
                                                                         parent(parent) {}
};

// 求二叉树某个节点 的 后继节点
//二叉树结构如下定义：
//Class Node {
//	V value;
//	Node left;
//	Node right;
//	Node parent;
//}
//给你二叉树中的某个节点，返回该节点 的 后继节点  ：即在中序遍历过程中的下一个节点
TreeNode *getLeftMost(TreeNode *node);

TreeNode *getSuccessorNode(TreeNode *node) {
    if (node == nullptr) {
        return node;
    }
    if (node->right) { //如果这个节点存在右子树,那么返回它右子树中最左侧的节点
        return getLeftMost(node->right);
    } else { // 如果这个节点没有右子树
        TreeNode *parent = node->parent;
        while (parent && parent->right == node) { // 只要我存在父节点并且我是我父节点的右孩子,就一直往上找
            node = parent;
            parent = node->parent;
        }
        return parent;
    }
}

TreeNode *getLeftMost(TreeNode *node) {
    if (node == nullptr) {
        return node;
    }
    while (node->left) {
        node = node->left;
    }
    return node;
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
    TreeNode *head = new TreeNode(6);
    head->parent = nullptr;
    head->left = new TreeNode(3);
    head->left->parent = head;
    head->left->left = new TreeNode(1);
    head->left->left->parent = head->left;
    head->left->left->right = new TreeNode(2);
    head->left->left->right->parent = head->left->left;
    head->left->right = new TreeNode(4);
    head->left->right->parent = head->left;
    head->left->right->right = new TreeNode(5);
    head->left->right->right->parent = head->left->right;
    head->right = new TreeNode(9);
    head->right->parent = head;
    head->right->left = new TreeNode(8);
    head->right->left->parent = head->right;
    head->right->left->left = new TreeNode(7);
    head->right->left->left->parent = head->right->left;
    head->right->right = new TreeNode(10);
    head->right->right->parent = head->right;
    printTree(head);
    // 中序遍历为1 2 3 4 5 6 7 8 9 10
    TreeNode *test = head->left->left;
    cout << test->val << " next: " << getSuccessorNode(test)->val << endl;
    test = head->left->left->right;
    cout << test->val << " next: " << getSuccessorNode(test)->val << endl;
    test = head->left;
    cout << test->val << " next: " << getSuccessorNode(test)->val << endl;
    test = head->left->right;
    cout << test->val << " next: " << getSuccessorNode(test)->val << endl;
    test = head->left->right->right;
    cout << test->val << " next: " << getSuccessorNode(test)->val << endl;
    test = head;
    cout << test->val << " next: " << getSuccessorNode(test)->val << endl;
    test = head->right->left->left;
    cout << test->val << " next: " << getSuccessorNode(test)->val << endl;
    test = head->right->left;
    cout << test->val << " next: " << getSuccessorNode(test)->val << endl;
    test = head->right;
    cout << test->val << " next: " << getSuccessorNode(test)->val << endl;
    return 0;
}