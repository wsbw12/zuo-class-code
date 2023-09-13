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

// 打印一个字符串的全部排列
void g1(string &str, int index, vector<string> &ans);

void swap(string &s, int i, int j);

void g2(string &str, int index, vector<string> &ans);

vector<string> permutation1(string &s) {
    vector<string> ans;
    if (s.empty() || s.size() == 0) {
        return ans;
    }
    g1(s, 0, ans);
    return ans;
}

void g1(string &str, int index, vector<string> &ans) {
    if (index == str.size()) {
        ans.push_back(str);
    } else {
        for (int i = index; i < str.size(); i++) {
            swap(str, index, i);
            g1(str, index + 1, ans);
            swap(str, index, i);
        }
    }
}

void swap(string &s, int i, int j) {
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

// 打印一个字符串的全部排列,要求不出现重复的排列
vector<string> permutation2(string &s) {
    vector<string> ans;
    if (s.empty() || s.size() == 0) {
        return ans;
    }
    g2(s, 0, ans);
    return ans;
}

void g2(string &str, int index, vector<string> &ans) {
    if (index == str.size()) {
        ans.push_back(str);
    } else {
        vector<bool> visited(256);
        for (int i = index; i < str.size(); i++) {
            if (!visited[str[i]]) {
                visited[str[i]] = true;
                swap(str, index, i);
                g2(str, index + 1, ans);
                swap(str, index, i);
            }
        }
    }
}

int main() {
    string test = "acc";
    vector<string> ans1 = permutation1(test);
    vector<string> ans2 = permutation2(test);
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