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

//二叉树的序列化和反序列化
/*
     * 二叉树可以通过先序、后序或者按层遍历的方式序列化和反序列化，
     * 以下代码全部实现了。
     * 但是，二叉树无法通过中序遍历的方式实现序列化和反序列化
     * 因为不同的两棵树，可能得到同样的中序序列，即便补了空位置也可能一样。
     * 比如如下两棵树
     *         __2
     *        /
     *       1
     *       和
     *       1__
     *          \
     *           2
     * 补足空位置的中序遍历结果都是{ null, 1, null, 2, null}
     *
     * */
void dfs_pre(TreeNode *root, string &res);

TreeNode *dfs_de_pre(string &data, int &u);

void traverse(TreeNode *root);

// 按照先序遍历的方式序列化
string serialize_pre(TreeNode *root) {
    string res;
    dfs_pre(root, res);
    return res;
}

void dfs_pre(TreeNode *root, string &res) {
    if (root == nullptr) {
        res += "#,";
        return;
    }
    res += to_string(root->val) + ',';
    dfs_pre(root->left, res);
    dfs_pre(root->right, res);
}

// 按照后序遍历的方式序列化和反序列化
string data;


void dfs_pos(TreeNode *root, string &res) {
    if (root == nullptr) {
        res += "#,";
        return;
    }
    dfs_pos(root->left, res);
    dfs_pos(root->right, res);
    res += to_string(root->val) + ',';
}

string serialize_pos(TreeNode *root) {
    string res;
    dfs_pos(root, res);
    res.pop_back();
    return res;
}


// Encodes a tree to a single string.

stack<string> split(string &str) {
    stack<string> ans;
    if (str.empty()) return ans;
    int size = str.size();
    int pre = 0;
    for (int i = 0; i <= size; ++i) {
        if (i == size || str[i] == ',') {
            ans.emplace(str.substr(pre, i - pre)); // emplace 类似于push_back
            pre = i + 1;
        }
    }
    return ans;
}

TreeNode *deserialize(stack<string> &data) {
    if (data.empty()) return nullptr;
    string first = data.top();
    data.pop();
    if (first == "#") return nullptr;

    auto *root = new TreeNode(stoi(first)); //stoi 将n进制的字符串转化为十进制
    root->right = deserialize(data);
    root->left = deserialize(data);

    return root;
}

// Decodes your encoded data to tree.
TreeNode *deserialize(string data) {
    stack<string> iters = split(data);
    return deserialize(iters);
}

// 按照先序遍历的方式反序列化
TreeNode *deserialize_pre(string data) {
    int u = 0;
    return dfs_de_pre(data, u);
}

TreeNode *dfs_de_pre(string &data, int &u) {
    if (data[u] == '#') {
        u += 2;
        return nullptr;
    }
    int t = 0; // t用来代表节点的数值
    bool is_minus = false; // 这个用来判断这个节点的数值是不是负数
    while (data[u] != ',') {
        if (data[u] == '-') {
            is_minus = true;
        } else {
            t = t * 10 + data[u] - '0';
        }
        u++;
    }
    u++;
    if (is_minus) {
        t = -t;
    }
    auto root = new TreeNode(t);
    root->left = dfs_de_pre(data, u);
    root->right = dfs_de_pre(data, u);
    return root;
}


/******** 层序遍历序列化与反序列化 *************/

// Encodes a tree to a single string.
string serialize_level(TreeNode *root) {
    if (root == nullptr) return "";
    string str;
    queue<TreeNode *> q; // 用来辅助进行层次遍历的队列
    q.push(root);
    while (!q.empty()) {
        TreeNode *node = q.front();
        q.pop();
        if (node)
            str += (to_string(node->val) + ",");
        else {
            str += "#,";
            continue;
        }
        q.push(node->left);
        q.push(node->right);
    }
    str.pop_back();
    return str;
}

vector<string> Split(string &str) {
    vector<string> ans;
    if (str.empty()) return ans;
    int size = str.size();
    int pre = 0;
    for (int i = 0; i <= size; ++i) {
        if (i == size || str[i] == ',') {
            ans.emplace_back(str.substr(pre, i - pre));
            pre = i + 1;
        }
    }
    return ans;
}

TreeNode *deserialize_level(vector<string> &data) {
    if (data.empty()) return nullptr;
    string node = data[0];

    auto *root = new TreeNode(stoi(node));
    queue<TreeNode *> q;
    q.push(root);

    for (int i = 1; i < data.size();) {
        TreeNode *node = q.front();
        q.pop();
        if (node == nullptr) continue;

        string s_left = data[i++];
        if (s_left == "#")
            node->left = nullptr;
        else
            node->left = new TreeNode(stoi(s_left));
        q.push(node->left);

        string s_right = data[i++];
        if (s_right == "#")
            node->right = nullptr;
        else
            node->right = new TreeNode(stoi(s_right));
        q.push(node->right);
    }
    return root;
}

// Decodes your encoded data to tree.
TreeNode *deserialize_level(string data) {
    vector<string> iters = Split(data);
    return deserialize_level(iters);
}


void level(TreeNode *head) {
    if (head == nullptr) {
        return;
    }
    queue<TreeNode *> q;
    q.push(head);
    while (!q.empty()) {
        TreeNode *cur = q.front();
        q.pop();
        cout << cur->val << endl;
        if (cur->left) {
            q.push(cur->left);
        }
        if (cur->right) {
            q.push(cur->right);
        }
    }
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

bool isSameValueStructure(TreeNode *head1, TreeNode *head2) {
    if (head1 == nullptr && head2 != nullptr) {
        return false;
    }
    if (head1 != nullptr && head2 == nullptr) {
        return false;
    }
    if (head1 == nullptr && head2 == nullptr) {
        return true;
    }
    if (head1->val != head2->val) {
        return false;
    }
    return isSameValueStructure(head1->right, head2->right) && isSameValueStructure(head1->left, head2->left);
}

int main() {
    auto *head = new TreeNode(1);
    head->left = new TreeNode(2);
    head->right = new TreeNode(3);
    head->left->left = new TreeNode(4);
    head->left->right = new TreeNode(5);
    head->right->left = new TreeNode(6);
    head->right->right = new TreeNode(17);
    cout << "该二叉树的层序遍历为: " << endl;
    level(head);
    string res_pre = serialize_pre(head);
    cout << "该二叉树的先序遍历序列化的结果为: " << endl;
    cout << res_pre << endl;
    string res_pos = serialize_pos(head);
    cout << "该二叉树的后序遍历序列化的结果为: " << endl;
    cout << res_pos << endl;
    string res_level = serialize_level(head);
    cout << "该二叉树的层序遍历序列化的结果为: " << endl;
    cout << res_level << endl;
    cout << "该二叉树的先序遍历反序列化的结果为: " << endl;
    auto *res1 = deserialize_pre(res_pre);
    level(res1);
    cout << "该二叉树的后序遍历反序列化的结果为: " << endl;
    auto *res2 = deserialize(res_pos);
    level(res2);
    cout << "该二叉树的层序遍历反序列化的结果为: " << endl;
    auto *res3 = deserialize_level(res_level);
    level(res3);
    delete head;
    cout << "=================" << endl;
    int maxLevel = 5;
    int maxValue = 100;
    int test_time = 1000000;
    clock_t start, end;
    start = clock();
    cout << "测试开始" << endl;
    for (int i = 0; i < test_time; i++) {
        TreeNode *root = generateRandomBST(maxLevel, maxValue);
        string pre = serialize_pre(root);
        string pos = serialize_pos(root);
        string level = serialize_level(root);
        TreeNode *preBuild = deserialize_pre(pre);
        TreeNode *posBuild = deserialize(pos);
        TreeNode *levelBuild = deserialize_level(level);
        if (!isSameValueStructure(preBuild, posBuild) || !isSameValueStructure(posBuild, levelBuild)) {
            cout << pre << endl;
            cout << pos << endl;
            cout << level << endl;
            cout << "测试错误" << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
    end = clock();   //结束时间
    cout << "测试的时间为: " << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ）
    return 0;
}