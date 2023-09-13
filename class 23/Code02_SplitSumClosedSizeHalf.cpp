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

//给定一个正数数组arr，请把arr中所有的数分成两个集合
//如果arr长度为偶数，两个集合包含数的个数要一样多
//如果arr长度为奇数，两个集合包含数的个数必须只差一个
//请尽量让两个集合的累加和接近
//返回最接近的情况下，较小集合的累加和
int process(vector<int> &arr, int i, int picks, int rest);

int right(vector<int> &arr) {
    if (arr.empty() || arr.size() < 2) {
        return 0;
    }
    int sum = 0;
    for (int num:arr) {
        sum += num;
    }
    if ((arr.size() & 1) == 0) { // 个数是偶数的情况下
        return process(arr, 0, arr.size() / 2, sum / 2);
    } else {
        return max(process(arr, 0, arr.size() / 2, sum / 2), process(arr, 0, arr.size() / 2 + 1, sum / 2));
    }
}

// arr[i....]自由选择，挑选的个数一定要是picks个，累加和<=rest, 离rest最近的返回
int process(vector<int> &arr, int i, int picks, int rest) {
    if (i == arr.size()) {
        return picks == 0 ? 0 : -1;
    } else {
        int p1 = process(arr, i + 1, picks, rest);
        // 就是要使用arr[i]这个数
        int p2 = -1;
        int next = -1;
        if (arr[i] <= rest) {
            next = process(arr, i + 1, picks - 1, rest - arr[i]);
        }
        if (next != -1) {
            p2 = arr[i] + next;
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
    int m = (n + 1) / 2;
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(sum + 1)));
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= sum; k++) {
                dp[i][j][k] = -1;
            }
        }
    }
    for (int rest = 0; rest <= sum; rest++) {
        dp[n][0][rest] = 0;
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int picks = 0; picks <= m; picks++) {
            for (int rest = 0; rest <= sum; rest++) {
                int p1 = dp[i + 1][picks][rest];
                // 就是要使用arr[i]这个数
                int p2 = -1;
                int next = -1;
                if (picks - 1 >= 0 && arr[i] <= rest) {
                    next = dp[i + 1][picks - 1][rest - arr[i]];
                }
                if (next != -1) {
                    p2 = arr[i] + next;
                }
                dp[i][picks][rest] = max(p1, p2);
            }
        }
    }
    if ((arr.size() & 1) == 0) {
        return dp[0][arr.size() / 2][sum];
    } else {
        return max(dp[0][arr.size() / 2][sum], dp[0][(arr.size() / 2) + 1][sum]);
    }
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
    int maxValue = 50;
    int test_time = 1000;
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