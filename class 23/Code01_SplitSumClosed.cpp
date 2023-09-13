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

//给定一个正数数组arr，
//请把arr中所有的数分成两个集合，尽量让两个集合的累加和接近
//返回最接近的情况下，较小集合的累加和
int process(vector<int> &arr, int i, int rest);

int right(vector<int> &arr) {
    if (arr.empty() || arr.size() < 2) {
        return 0;
    }
    int sum = 0;
    for (int num:arr) {
        sum += num;
    }
    return process(arr, 0, sum / 2);
}

// arr[i...]可以自由选择，请返回累加和尽量接近rest，但不能超过rest的情况下，最接近的累加和是多少？
int process(vector<int> &arr, int i, int rest) {
    if (i == arr.size()) {
        return 0;
    } else {// 还有数，arr[i]这个数
        // 可能性1，不使用arr[i]
        int p1 = process(arr, i + 1, rest);
        // 可能性2，要使用arr[i]
        int p2 = 0;
        if (arr[i] <= rest) {
            p2 = arr[i] + process(arr, i + 1, rest - arr[i]);
        }
        return max(p1, p2);
    }
}

int dp(vector<int> &arr) {
    if (arr.empty() || arr.size() < 2) {
        return 0;
    }
    int sum = 0;
    for (int num:arr) {
        sum += num;
    }
    sum /= 2;
    int n = arr.size();
    vector<vector<int>> dp(n + 1, vector<int>(sum + 1));
    for (int i = n - 1; i >= 0; i--) {
        for (int rest = 0; rest <= sum; rest++) {
            int p1 = dp[i + 1][rest];
            int p2 = 0;
            if (arr[i] <= rest) {
                p2 = arr[i] + dp[i + 1][rest - arr[i]];
            }
            dp[i][rest] = max(p1, p2);
        }
    }
    return dp[0][sum];
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
    int maxValue = 50;
    int test_time = 10000;
    cout << "测试开始" << endl;
    for (int i = 0; i < test_time; i++) {
        srand((int) time(NULL));//为随机数生成器产生随机种子
        int len = (int) (rand() % maxLen);
        vector<int> arr = generateRandomVector(len, maxValue);
        int ans1 = right(arr);
        int ans2 = dp(arr);
        if (ans1 != ans2) {
            cout << ans1 << " " << ans2 << endl;
            cout << "测试失败" << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}