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
#include <deque>

using namespace std;

//给定一个只包含正数的数组arr，arr中任何一个子数组sub，
//一定都可以算出(sub累加和 )* (sub中的最小值)是什么，
//那么所有子数组中，这个值最大是多少？
// https://leetcode.cn/problems/maximum-subarray-min-product/ leetcode 1856
// 暴力解法
int max1(vector<int> &arr) {
    int max_num = INT_MIN;
    for (int i = 0; i < arr.size(); i++) {
        for (int j = i; j < arr.size(); j++) {
            int minNum = INT_MAX;
            int sum = 0;
            for (int k = i; k <= j; k++) {
                sum += arr[k];
                minNum = min(minNum, arr[k]);
            }
            max_num = max(max_num, minNum * sum);
        }
    }
    return max_num;
}


int max2(vector<int> &arr) {
    int size = arr.size();
    vector<int> sums(size);
    sums[0] = arr[0];
    // 先计算原数组的前缀和数组
    for (int i = 1; i < size; i++) {
        sums[i] = sums[i - 1] + arr[i];
    }
    int max_num = INT_MIN;
    stack<int> stk;
    for (int i = 0; i < size; i++) {
        while (!stk.empty() && arr[stk.top()] >= arr[i]) {
            int j = stk.top();
            stk.pop();
            max_num = max(max_num, (stk.empty() ? sums[i - 1] : (sums[i - 1] - sums[stk.top()])) * arr[j]);
        }
        stk.push(i);
    }
    while (!stk.empty()) {
        int j = stk.top();
        stk.pop();
        max_num = max(max_num, (stk.empty() ? sums[size - 1] : (sums[size - 1] - sums[stk.top()])) * arr[j]);
    }
    return max_num;
}

int maxSumMinProduct(vector<int>& arr) {
    int size = arr.size();
    vector<long long> sums(size);
    sums[0] = arr[0];
    // 先计算原数组的前缀和数组
    for (int i = 1; i < size; i++) {
        sums[i] = sums[i - 1] + arr[i];
    }
    long long max_num = LLONG_MIN;
    stack<int> stk;
    for (int i = 0; i < size; i++) {
        while (!stk.empty() && arr[stk.top()] >= arr[i]) {
            int j = stk.top();
            stk.pop();
            max_num = max(max_num, (stk.empty() ? sums[i - 1] : (sums[i - 1] - sums[stk.top()])) * arr[j]);
        }
        stk.push(i);
    }
    while (!stk.empty()) {
        int j = stk.top();
        stk.pop();
        max_num = max(max_num, (stk.empty() ? sums[size - 1] : (sums[size - 1] - sums[stk.top()])) * arr[j]);
    }
    return (int)(max_num % 1000000007);
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

int main() {
    int test_time = 20000;
    int maxSize = 100;
    int maxValue = 100;
    cout << "test begin " << endl;
    for (int i = 0; i < test_time; i++) {
        vector<int> arr = generateRandomVector(maxSize, maxValue);
        if (max1(arr) != max2(arr)) {
            cout << "test error" << endl;
            break;
        }
    }
    cout << "test finished" << endl;
    return 0;
}