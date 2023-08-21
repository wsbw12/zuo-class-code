#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>

using namespace std;
// leetcode 链接:https://leetcode.cn/problems/count-of-range-sum/
// 327. 区间和的个数
int merge(vector<long> &sum, int left, int mid, int right, int lower, int upper) {
    int res = 0;
    int windowL = left;
    int windowR = left;
    for (int i = mid + 1; i <= right; i++) {
        long min_num = sum[i] - upper;
        long max_num = sum[i] - lower;
        while (windowR <= mid && sum[windowR] <= max_num) {
            // 这个循环结束之后,windowR指向的是第一个> max_num的值
            windowR++;
        }
        while (windowL <= mid && sum[windowL] < min_num) {
            // 这个循环结束之后,windowL指向的是第一个>= min_num的值
            windowL++;
        }
        // 那么此时res应该包括的区间就是[WindowL...windowR-1] 元素个数为windowR-1-windowL+1=windowR-windowL
        res += (windowR - windowL);
    }
    vector<long> help(right - left + 1);
    int i = 0;
    int p1 = left;
    int p2 = mid + 1;
    while (p1 <= mid && p2 <= right) {
        help[i++] = sum[p1] <= sum[p2] ? sum[p1++] : sum[p2++];
    }
    while (p1 <= mid) {
        help[i++] = sum[p1++];
    }
    while (p2 <= right) {
        help[i++] = sum[p2++];
    }
    for (int i = 0; i < help.size(); i++) {
        sum[left + i] = help[i];
    }
    return res;
}

int process(vector<long> &sum, int left, int right, int lower, int upper) {
    if (left == right) {
        return sum[left] >= lower && sum[left] <= upper ? 1 : 0;
    }
    int mid = left + ((right - left) >> 1);
    return process(sum, left, mid, lower, upper) + process(sum, mid + 1, right, lower, upper) +
           merge(sum, left, mid, right, lower, upper);
}

int countRangeSum(vector<int> &nums, int lower, int upper) {
    if (nums.empty() || nums.size() == 0) {
        return 0;
    }
    vector<long> sum(nums.size());//求原数组的前缀合数组
    sum[0] = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        sum[i] = sum[i - 1] + nums[i];
    }
    return process(sum, 0, sum.size() - 1, lower, upper);
}

int test_process(vector<int> &nums, int lower, int upper) {
    if (nums.empty() || nums.size() == 0) {
        return 0;
    }
    vector<int> sum(nums.size());//求原数组的前缀合数组
    sum[0] = nums[0];
    int count = 0;
    for (int i = 1; i < nums.size(); i++) {
        sum[i] = sum[i - 1] + nums[i];
    }
    for (int i = 0; i < nums.size(); i++) {
        for (int j = i; j < nums.size(); j++) {
            if (i == j) {
                if (sum[i] >= lower && sum[i] <= upper) {
                    count++;
                }
            } else {
                int temp_sum = sum[j] - sum[i];
                if (temp_sum >= lower && temp_sum <= upper) {
                    count++;
                }
            }
        }
    }
    return count;
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

void printArray(vector<int> &arr) {
    if (arr.empty()) {
        return;
    }
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// 生成一个[-range,range]范围的随机数
int randomNumber(int range) {
    srand((unsigned) time(NULL));
    return (int) (rand() % (range + 1)) - (int) (rand() % (range + 1));
}

int main() {
    int test_time = 100000;//进行测试的次数
    int size = 1000;//生成数组的最大长度
    int value = 1000;//生成数组的最大值
    cout << "测试开始" << endl;
    for (int i = 0; i < test_time; i++) {
        int a = randomNumber(value);
        int b = randomNumber(value);
        int lower = min(a, b);
        int upper = max(a, b);
        if (lower == upper) {
            upper += 1;
        }
        vector<int> arr1 = generateRandomVector(size, value);
        vector<int> arr2(arr1);
        if (test_process(arr1, lower, upper) != countRangeSum(arr2, lower, upper)) {
            cout << "测试错误" << endl;
            printArray(arr1);
            printArray(arr2);
            break;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}