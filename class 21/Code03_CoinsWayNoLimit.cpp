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
//返回组成aim的方法数
//例如：arr = {1,2}，aim = 4
//方法如下：1+1+1+1、1+1+2、2+2
//一共就3种方法，所以返回3
int process(vector<int> &arr, int index, int rest);

int coinWays(vector<int> &arr, int aim) {
    return process(arr, 0, aim);
}

// arr[index....] 所有的面值，每一个面值都可以任意选择张数，组成正好rest这么多钱，方法数多少？
int process(vector<int> &arr, int index, int rest) {
    if (index == arr.size()) {
        return rest == 0 ? 1 : 0;
    }
    int ways = 0;
    for (int zhang = 0; zhang * arr[index] <= rest; zhang++) {
        ways += process(arr, index + 1, rest - (zhang * arr[index]));
    }
    return ways;
}

int dp1(vector<int> &arr, int aim) {
    if (arr.empty() || arr.size() == 0 || aim < 0) {
        return 0;
    }
    int n = arr.size();
    vector<vector<int>> dp(n + 1, vector<int>(aim + 1));
    dp[n][0] = 1;
    for (int index = n - 1; index >= 0; index--) {
        for (int rest = 0; rest <= aim; rest++) {
            int ways = 0;
            for (int zhang = 0; zhang * arr[index] <= rest; zhang++) {
                ways += dp[index + 1][rest - (zhang * arr[index])];
            }
            dp[index][rest] = ways;
        }
    }
    return dp[0][aim];
}


int dp2(vector<int> &arr, int aim) {
    if (arr.empty() || arr.size() == 0 || aim < 0) {
        return 0;
    }
    int n = arr.size();
    vector<vector<int>> dp(n + 1, vector<int>(aim + 1));
    dp[n][0] = 1;
    for (int index = n - 1; index >= 0; index--) {
        for (int rest = 0; rest <= aim; rest++) {
            dp[index][rest] = dp[index + 1][rest];
            if (rest - arr[index] >= 0) {
                dp[index][rest] += dp[index][rest - arr[index]];
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
    int maxLen = 20;
    int maxValue = 30;
    int test_time = 100000;
    cout << "测试开始" << endl;
    for (int i = 0; i < test_time; i++) {
        srand((int) time(NULL));//为随机数生成器产生随机种子
        vector<int> arr = generateRandomVector(maxLen, maxValue);
        int aim = (int) (rand() % maxValue);
        int ans1 = coinWays(arr, aim);
        int ans2 = dp1(arr, aim);
        int ans3 = dp2(arr, aim);
        if (ans1 != ans2 || ans1 != ans3) {
            cout << "测试错误" << endl;
            printArr(arr);
            cout << aim << endl;
            cout << ans1 << endl;
            cout << ans2 << endl;
            cout << ans3 << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}