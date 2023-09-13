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

//给定一个正数n，求n的裂开方法数，
//规定：后面的数不能比前面的数小
//比如4的裂开方法有：
//1+1+1+1、1+1+2、1+3、2+2、4
//5种，所以返回5
int process(int pre, int rest);

int ways(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return process(1, n);
}
// 上一个拆出来的数是pre
// 还剩rest需要去拆
// 返回拆解的方法数

int process(int pre, int rest) {
    if (rest == 0) {
        return 1;
    }
    if (pre > rest) {
        return 0;
    }
    int ways = 0;
    for (int first = pre; first <= rest; first++) {
        ways += process(first, rest - first);
    }
    return ways;
}

int dp1(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    for (int pre = 1; pre <= n; pre++) {
        dp[pre][0] = 1;
        dp[pre][pre] = 1;
    }
    for (int pre = n - 1; pre >= 1; pre--) {
        for (int rest = pre + 1; rest <= n; rest++) {
            int ways = 0;
            for (int first = pre; first <= rest; first++) {
                ways += dp[first][rest - first];
            }
            dp[pre][rest] = ways;
        }
    }
    return dp[1][n];
}

int dp2(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    for (int pre = 1; pre <= n; pre++) {
        dp[pre][0] = 1;
        dp[pre][pre] = 1;
    }
    for (int pre = n - 1; pre >= 1; pre--) {
        for (int rest = pre + 1; rest <= n; rest++) {
            dp[pre][rest] = dp[pre + 1][rest];
            dp[pre][rest] += dp[pre][rest - pre];
        }
    }
    return dp[1][n];
}

int main() {
    int test = 23;
    cout << ways(test) << " " << dp1(test) << " " << dp2(test) << endl;
    return 0;
}