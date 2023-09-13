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

//arr是货币数组，其中的值都是正数。再给定一个正数aim。
//每个值都认为是一张货币，
//认为值相同的货币没有任何不同，
//返回组成aim的方法数
//例如：arr = {1,2,1,1,2,1,2}，aim = 4
//方法：1+1+1+1、1+1+2、2+2
//一共就3种方法，所以返回3
class Info {
public:
    vector<int> coins;
    vector<int> zhangs;

    Info(vector<int> &c, vector<int> &z) {
        this->coins = c;
        this->zhangs = z;
    }
};

Info *getInfo(vector<int> &arr) {
    unordered_map<int, int> counts;
    for (int i = 0; i < arr.size(); i++) {
        int value = arr[i];
        if (!counts.count(value)) {
            counts[value] = 1;
        } else {
            counts[value]++;
        }
    }
    int n = counts.size();
    vector<int> coins(n);
    vector<int> zhangs(n);
    int index = 0;
    for (auto iter = counts.begin(); iter != counts.end(); ++iter) {
        coins[index] = iter->first;
        zhangs[index++] = iter->second;
    }
    return new Info(coins, zhangs);
}

int process(vector<int> &coins, vector<int> &zhangs, int index, int rest);

int coinWays(vector<int> &arr, int aim) {
    if (arr.empty() || arr.size() == 0 || aim < 0) {
        return 0;
    }
    Info *info = getInfo(arr);
    return process(info->coins, info->zhangs, 0, aim);
}
// coins 面值数组，正数且去重
// zhangs 每种面值对应的张数

int process(vector<int> &coins, vector<int> &zhangs, int index, int rest) {
    if (index == coins.size()) {
        return rest == 0 ? 1 : 0;
    }
    int ways = 0;
    for (int zhang = 0; zhang * coins[index] <= rest && zhang <= zhangs[index]; zhang++) {
        ways += process(coins, zhangs, index + 1, rest - (zhang * coins[index]));
    }
    return ways;
}

int dp1(vector<int> &arr, int aim) {
    if (arr.empty() || arr.size() == 0 || aim < 0) {
        return 0;
    }
    Info *info = getInfo(arr);
    vector<int> coins = info->coins;
    vector<int> zhangs = info->zhangs;
    int n = coins.size();
    vector<vector<int>> dp(n + 1, vector<int>(aim + 1));
    dp[n][0] = 1;
    for (int index = n - 1; index >= 0; index--) {
        for (int rest = 0; rest <= aim; rest++) {
            int ways = 0;
            for (int zhang = 0; zhang * coins[index] <= rest && zhang <= zhangs[index]; zhang++) {
                ways += dp[index + 1][rest - (zhang * coins[index])];
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
    Info *info = getInfo(arr);
    vector<int> coins = info->coins;
    vector<int> zhangs = info->zhangs;
    int n = coins.size();
    vector<vector<int>> dp(n + 1, vector<int>(aim + 1));
    dp[n][0] = 1;
    for (int index = n - 1; index >= 0; index--) {
        for (int rest = 0; rest <= aim; rest++) {
            dp[index][rest] = dp[index + 1][rest];
            if (rest - coins[index] >= 0) {
                dp[index][rest] += dp[index][rest - coins[index]];
            }
            if (rest - coins[index] * (zhangs[index] + 1) >= 0) {
                dp[index][rest] -= dp[index + 1][rest - coins[index] * (zhangs[index] + 1)];
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