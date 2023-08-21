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

//给定一个由字符串组成的数组strs，必须把所有的字符串拼接起来，返回所有可能的拼接结果中字典序最小的结果

// {"abc", "cks", "bct"}
// 0 1 2
// removeIndexString(arr , 1) -> {"abc", "bct"}
vector<string> removeIndexString(vector<string> &arr, int index) {
    int n = arr.size();
    vector<string> ans(n-1);
    int ansIndex = 0;
    for (int i = 0; i < n; i++) {
        if (i != index) {
            ans[ansIndex++] = arr[i];
        }
    }
    return ans;
}

// strs中所有字符串全排列，返回所有可能的结果
set<string> process(vector<string> &strs) {
    set<string> ans;
    if (strs.size() == 0) {
        ans.insert("");
        return ans;
    }
    for (int i = 0; i < strs.size(); i++) {
        string first = strs[i];
        vector<string> nexts = removeIndexString(strs, i);
        set<string> next = process(nexts);
        for (string cur:next) {
            ans.insert(first + cur);
        }
    }
    return ans;
}

string lowestString1(vector<string> &strs) {
    if (strs.empty() || strs.size() == 0) {
        return "";
    }
    set<string> ans = process(strs);
    set<string>::iterator it;
    it = ans.begin();
    if (ans.size() == 0) {
        return "";
    } else {
        return *it;
    }
}

bool MyCmp(const string &s1, const string &s2) {
    return (s1 + s2) < (s2 + s1);
}

string lowestString2(vector<string> &strs) {
    if (strs.empty() || strs.size() == 0) {
        return "";
    }
    sort(strs.begin(), strs.end(), MyCmp);
    string res = "";
    for (int i = 0; i < strs.size(); i++) {
        res += strs[i];
    }
    return res;
}

string generateRandomString(int strLen) {
    vector<char> ans((int) (rand() % strLen) + 1);
    for (int i = 0; i < ans.size(); i++) {
        int value = (int) (rand() % 5);
        ans[i] = (((int) (rand() % 10)) <= 5) ? (char) (65 + value) : (char) (97 + value);
    }
    string res = "";
    for (int i = 0; i < ans.size(); i++) {
        res += ans[i];
    }
    return res;
}

vector<string> generateRandomStringArray(int arrLen, int strLen) {
    vector<string> ans((int) (rand() % arrLen) + 1);
    for (int i = 0; i < ans.size(); i++) {
        ans[i] = generateRandomString(strLen);
    }
    return ans;
}

int main() {
    int arrLen = 6;
    int strLen = 5;
    int test_time = 10000;
    clock_t start, end;
    start = clock();
    cout << "测试开始" << endl;
    for (int i = 0; i < test_time; i++) {
        vector<string> arr1 = generateRandomStringArray(arrLen, strLen);
        vector<string> arr2(arr1);
        if (lowestString1(arr1) != lowestString2(arr2)) {
            for (string str:arr1) {
                cout << str << ", ";
            }
            cout << endl;
            cout << "测试错误" << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
    end = clock();   //结束时间
    cout << "测试的时间为: " << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ）
    return 0;
}