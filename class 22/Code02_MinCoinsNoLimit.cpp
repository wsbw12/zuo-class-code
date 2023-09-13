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

//arr是面值数组，其中的值都是正数且没有重复。再给定一个正数aim。
//每个值都认为是一种面值，且认为张数是无限的。
//返回组成aim的最少货币数
int process(vector<int> &arr, int index, int rest);

int minCoins(vector<int> &arr, int aim) {
    return process(arr, 0, aim);
}

// arr[index...]面值，每种面值张数自由选择，
// 搞出rest正好这么多钱，返回最小张数
// 拿Integer.MAX_VALUE标记怎么都搞定不了
int process(vector<int> &arr, int index, int rest) {
    if (index == arr.size()) {
        return rest == 0 ? 0 : INT_MAX;
    } else {
        int ans = INT_MAX;
        for (int zhang = 0; zhang * arr[index] <= rest; zhang++) {
            int next = process(arr, index + 1, rest - zhang * arr[index]);
            if (next != INT_MAX) {
                ans = min(ans, zhang + next);
            }
        }
        return ans;
    }
}

int dp1(vector<int> &arr, int aim) {
    if (aim == 0) {
        return 0;
    }
    int n = arr.size();
    vector<vector<int>> dp(n + 1, vector<int>(aim + 1));
    dp[n][0] = 0;
    for (int j = 1; j <= aim; j++) {
        dp[n][j] = INT_MAX;
    }
    for (int index = n - 1; index >= 0; index--) {
        for (int rest = 0; rest <= aim; rest++) {
            int ans = INT_MAX;
            for (int zhang = 0; zhang * arr[index] <= rest; zhang++) {
                int next = dp[index + 1][rest - zhang * arr[index]];
                if (next != INT_MAX) {
                    ans = min(ans, zhang + next);
                }
            }
            dp[index][rest] = ans;
        }
    }
    return dp[0][aim];
}

int dp2(vector<int> &arr, int aim) {
    if (aim == 0) {
        return 0;
    }
    int n = arr.size();
    vector<vector<int>> dp(n + 1, vector<int>(aim + 1));
    dp[n][0] = 0;
    for (int j = 1; j <= aim; j++) {
        dp[n][j] = INT_MAX;
    }
    for (int index = n - 1; index >= 0; index--) {
        for (int rest = 0; rest <= aim; rest++) {
            dp[index][rest] = dp[index + 1][rest];
            if (rest - arr[index] >= 0 && dp[index][rest - arr[index] != INT_MAX]) {
                dp[index][rest] = min(dp[index][rest], dp[index][rest - arr[index]] + 1);
            }
        }
    }
    return dp[0][aim];
}

vector<int> generateRandomVector(int maxSize, int maxValue) {
    //time 函数返回从 1970 年 1 月 1 日午夜开始到现在逝去的秒数，因此每次运行程序时，它都将提供不同的种子值。
    srand((int) time(NULL));//为随机数生成器产生随机种子
    vector<int> result(rand() % (maxSize + 1));
    for (int i = 0; i < result.size(); i++) {
        result[i] = rand() % (maxValue + 1);
    }
    return result;
}

void printArr(vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


int main() {
    int maxLen = 10;
    int maxValue = 30;
    int test_time = 30;
    cout << "测试开始" << endl;
    for (int i = 0; i < test_time; i++) {
        int N = (int) (rand() % maxLen);
        vector<int> arr = generateRandomVector(N, maxValue);
        int aim = (int) (rand() % maxValue);
        int ans = minCoins(arr, aim);
        int ans1 = dp1(arr, aim);
        int ans2 = dp2(arr, aim);
        if (ans != ans1 || ans != ans2) {
            cout << "测试错误" << endl;
            cout << ans << " " << ans1 << " " << ans2 << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}