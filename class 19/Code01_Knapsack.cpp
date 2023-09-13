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
//背包问题
//给定两个长度都为N的数组weights和values，weights[i]和values[i]分别代表 i号物品的重量和价值
//给定一个正数bag，表示一个载重bag的袋子，装的物品不能超过这个重量
//返回能装下的最大价值


// 所有的货，重量和价值，都在w和v数组里
// 为了方便，其中没有负数
// bag背包容量，不能超过这个载重
// 返回：不超重的情况下，能够得到的最大价值
int process(vector<int> &w, vector<int> &v, int index, int rest);

int maxValue(vector<int> &w, vector<int> &v, int bag) {
    if (w.empty() || v.empty() || w.size() != v.size() || w.size() == 0) {
        return 0;
    }
    return process(w, v, 0, bag);
}

int process(vector<int> &w, vector<int> &v, int index, int rest) {
    if (rest < 0) { // 剩余的可用容量小于0的话说明不能在装了
        return -1;
    }
    if (index == w.size()) {
        return 0;
    }
    int p1 = process(w, v, index + 1, rest); // 不考虑index的位置上的东西
    int p2 = 0;
    int next = process(w, v, index + 1, rest - w[index]); // 考虑index上的东西
    if (next != -1) { // 如果选了index上的东西导致接下来背包容量不够了会返回-1,那么这种选择是排除的
        p2 = v[index] + next;
    }
    return max(p1, p2);
}

int process_dp(vector<int> &w, vector<int> &v, int bag) {
    if (w.empty() || v.empty() || w.size() != v.size() || w.size() == 0) {
        return 0;
    }
    int n = w.size();
    vector<vector<int>> dp(n + 1, vector<int>(bag + 1));
    for (int index = n - 1; index >= 0; index--) { // 因为由暴力递归的版本可知每一个普遍位置的依赖关系是依赖后一个位置
        // 所以从后往前遍历
        for (int rest = 0; rest <= bag; rest++) {
            int p1 = dp[index + 1][rest];
            int p2 = 0;
            int next = rest - w[index] < 0 ? -1 : dp[index + 1][rest - w[index]];
            if (next != -1) {
                p2 = v[index] + next;
            }
            dp[index][rest] = max(p1, p2);
        }
    }
    return dp[0][bag];
}

int main() {
    vector<int> weights = {3, 2, 4, 7, 3, 1, 7};
    vector<int> values = {5, 6, 3, 19, 12, 4, 2};
    int bag = 15;
    cout << maxValue(weights, values, bag) << endl;
    cout << process_dp(weights, values, bag) << endl;
    return 0;
}