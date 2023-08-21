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

// 二叉树先序、中序、后序的非递归遍历
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
    // 栈顶出来记为cur;如果有右孩子就压入右孩子,有左孩子就压入左孩子,先右再左
    if (head) {
        stack<TreeNode *> s;
        s.push(head);
        while (!s.empty()) {
            head = s.top();
            s.pop();
            cout << head->val << " ";
            if (head->right) {
                s.push(head->right);
            }
            if (head->left) {
                s.push(head->left);
            }
        }
    }
    cout << endl;
}

void mid(TreeNode *head)//中序遍历
{
    // 当前节点为cur,将cur的整个左边界全部押入栈中,直到遇到null
    // 每当从栈中弹出一个元素的时候,就打印,并且将该弹出节点的右孩子记为cur,重复上面的步骤
    if (head) {
        stack<TreeNode *> s;
        while (!s.empty() || head) {
            if (head) {
                s.push(head);
                head = head->left;
            } else {
                head = s.top();
                s.pop();
                cout << head->val << " ";
                head = head->right;
            }
        }
    }
    cout << endl;
}

void pos(TreeNode *head)//先序遍历
{
    // 从先序遍历中,改动为先压入左,再压入右 , 然后借助第二个栈进行输出
    if (head) {
        stack<TreeNode *> s1;
        stack<TreeNode *> s2;
        s1.push(head);
        while (!s1.empty()) {
            head = s1.top();
            s1.pop();
            s2.push(head);
            if (head->left) {
                s1.push(head->left);
            }
            if (head->right) {
                s1.push(head->right);
            }
        }
        while (!s2.empty()) {
            cout << s2.top()->val << " ";
            s2.pop();
        }
    }
    cout << endl;
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