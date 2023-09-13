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

// 打印一个字符串的全部子序列
void process1(string &str, int index, vector<string> &ans, string &path);

vector<string> subs(string &s) {
    string path = "";
    vector<string> ans;
    process1(s, 0, ans, path);
    return ans;
}

// str 固定参数
// 来到了str[index]字符，index是位置
// str[0..index-1]已经走过了！之前的决定，都在path上
// 之前的决定已经不能改变了，就是path
// str[index....]还能决定，之前已经确定，而后面还能自由选择的话，
// 把所有生成的子序列，放入到ans里去
void process1(string &str, int index, vector<string> &ans, string &path) {
    if (index == str.size()) {
        ans.push_back(path);
        return;
    }
    // 没有要index位置的字符
    process1(str, index + 1, ans, path);
    // 要了index位置的字符
    string temp = path + str[index];
    process1(str, index + 1, ans, temp);
}

// 打印一个字符串的全部子序列,要求不出现重复子面值的子序列
void process2(string &str, int index, unordered_set<string> &set, string &path) {
    if (index == str.size()) {
        set.insert(path);
        return;
    }
    string no = path;
    process2(str, index + 1, set, no);
    string yes = path + str[index];
    process2(str, index + 1, set, yes);
}

vector<string> subsNoRepeat(string &s) {
    string path = "";
    unordered_set<string> set;
    process2(s, 0, set, path);
    vector<string> ans;
    for (auto cur:set) {
        ans.push_back(cur);
    }
    return ans;
}


int main() {
    string test = "accccb";
    vector<string> ans1 = subs(test);
    vector<string> ans2 = subsNoRepeat(test);
    for (auto str:ans1) {
        cout << str << endl;
    }
    cout << "=================" << endl;
    for (auto str:ans2) {
        cout << str << endl;
    }
    cout << "=================" << endl;
    return 0;
}