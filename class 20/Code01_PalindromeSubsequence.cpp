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
#include <iomanip>
#include <cmath>

using namespace std;
//// https://leetcode.cn/problems/longest-palindromic-subsequence/
int f(string &s, int left, int right);

int longestPalindromeSubseq(string &s) {
    if (s.empty() || s.size() == 0) {
        return 0;
    }
    return f(s, 0, s.size() - 1);
}

// str[L..R]最长回文子序列长度返回
int f(string &s, int left, int right) {
    if (left == right) {
        return 1;
    }
    if (left == right - 1) {
        return s[left] == s[right] ? 2 : 1;
    }
    int p1 = f(s, left + 1, right);
    int p2 = f(s, left, right - 1);
    int p3 = f(s, left + 1, right - 1);
    int p4 = s[left] != s[right] ? 0 : (2 + f(s, left + 1, right - 1));
    return max(max(p1, p2), max(p3, p4));
}

int longestPalindromeSubseq(string &s) {
    if (s.empty() || s.size() == 0) {
        return 0;
    }
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n));
    // dp[i][j]表示从(i...j)位置上的最长公共子序列
    // 先将递归中的baseCase填好
    dp[n - 1][n - 1] = 1;
    for (int i = 0; i < n - 1; i++) {
        dp[i][i] = 1;
        dp[i][i + 1] = s[i] == s[i + 1] ? 2 : 1;
    }
    // 通过递归函数的依赖关系找到遍历的顺序
    for (int left = n - 3; left >= 0; left--) {
        for (int right = left + 2; right < n; right++) {
            dp[left][right] = max(dp[left][right - 1], dp[left + 1][right]);
            if (s[left] == s[right]) {
                dp[left][right] = max(dp[left][right], 2 + dp[left + 1][right - 1]);
            }
        }
    }
    return dp[0][n - 1];
}

int main() {
    return 0;
}