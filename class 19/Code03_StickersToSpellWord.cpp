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

//// 本题测试链接：https://leetcode.com/problems/stickers-to-spell-word

//// 所有贴纸stickers，每一种贴纸都有无穷张
//// target
//// 最少张数
string Minus(string &s1, string &s2) {
    vector<int> count(26);
    for (char cha:s1) {
        count[cha - 'a']++;
    }
    for (char cha:s2) {
        count[cha - 'a']--;
    }
    string builder = "";
    for (int i = 0; i < 26; i++) {
        if (count[i] > 0) {
            for (int j = 0; j < count[i]; j++) {
                builder += ((char) (i + 'a'));
            }
        }
    }
    return builder;
}

int process(vector<string> &stickers, string &target) {
    if (target.length() == 0) {
        return 0;
    }
    int min_num = INT_MAX;
    for (string first:stickers) {
        string rest = Minus(target, first);
        if (rest.length() != target.length()) {
            min_num = min(min_num, process(stickers, rest));
        }
    }
    return min_num += (min_num == INT_MAX ? 0 : 1);
}

int minStickers1(vector<string> &stickers, string &target) {
    int ans = process(stickers, target);
    return ans == INT_MAX ? -1 : ans;
}

// stickers[i] 数组，当初i号贴纸的字符统计 int[][] stickers -> 所有的贴纸
// 每一种贴纸都有无穷张
// 返回搞定target的最少张数
// 最少张数
int process2(vector<vector<int>> stickers, string &t) {
    if (t.length() == 0) {
        return 0;
    }
    // target做出词频统计
    // target  aabbc  2 2 1..
    //                0 1 2..
    //                a b c..
    vector<int> tCounts(26);
    for (char cha:t) {
        tCounts[cha - 'a']++;
    }
    int n = stickers.size();
    int min_num = INT_MAX;
    for (int i = 0; i < n; i++) {
        // 尝试第一张贴纸是谁
        vector<int> sticker = stickers[i];
        // 最关键的优化(重要的剪枝!这一步也是贪心!)
        if (sticker[t[0] - 'a'] > 0) {
            string builder = "";
            for (int j = 0; j < 26; j++) {
                if (tCounts[j] > 0) {
                    int nums = tCounts[j] - sticker[j];
                    for (int k = 0; k < nums; k++) {
                        builder += (char) (j + 'a');
                    }
                }
            }
            string rest = builder;
            min_num = min(min_num, process2(stickers, rest));
        }
    }
    return min_num += (min_num == INT_MAX ? 0 : 1);
}

int minStickers2(vector<string> &stickers, string &target) {
    int n = stickers.size();
    // 关键优化(用词频表替代贴纸数组)
    vector<vector<int>> counts(n, vector<int>(26));
    for (int i = 0; i < n; i++) {
        string str = stickers[i];
        for (char cha:str) {
            counts[i][cha - 'a']++;
        }
    }
    int ans = process2(counts, target);
    return ans == INT_MAX ? -1 : ans;
}


int process3(vector<vector<int>> stickers, string &t, unordered_map<string, int> &dp) {
    if (dp.count(t)) {
        return dp[t];
    }
    vector<int> tCounts(26);
    for (char cha:t) {
        tCounts[cha - 'a']++;
    }
    int n = stickers.size();
    int min_num = INT_MAX;
    for (int i = 0; i < n; i++) {
        // 尝试第一张贴纸是谁
        vector<int> sticker = stickers[i];
        // 最关键的优化(重要的剪枝!这一步也是贪心!)
        if (sticker[t[0] - 'a'] > 0) {
            string builder = "";
            for (int j = 0; j < 26; j++) {
                if (tCounts[j] > 0) {
                    int nums = tCounts[j] - sticker[j];
                    for (int k = 0; k < nums; k++) {
                        builder += (char) (j + 'a');
                    }
                }
            }
            string rest = builder;
            min_num = min(min_num, process3(stickers, rest, dp));
        }
    }
    int ans = min_num + (min_num == INT_MAX ? 0 : 1);
    dp[t] = ans;
    return ans;
}

int minStickers3(vector<string> &stickers, string &target) {
    int n = stickers.size();
    vector<vector<int>> counts(n, vector<int>(26));
    for (int i = 0; i < n; i++) {
        string str = stickers[i];
        for (char cha:str) {
            counts[i][cha - 'a']++;
        }
    }
    unordered_map<string, int> dp;
    dp[""] = 0;
    int ans = process3(counts, target, dp);
    return ans == INT_MAX ? -1 : ans;
}

int main() {

    return 0;
}