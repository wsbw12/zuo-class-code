#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>
#include <set>

using namespace std;
// https://leetcode.com/problems/reverse-pairs/ leetcode 493题

int merge(vector<int> &arr, int left, int mid, int right) {
    int ans = 0;
    int windowR = mid + 1;
    for (int i = left; i <= mid; i++) {
        while (windowR <= right && (long)arr[i] > ((long)(arr[windowR] << 1))) {
            // 此循环结束后windowR指向的就是第一个不满足arr[i]>arr[windowR]*2的数
            windowR++;
        }
        ans += windowR - (mid + 1);
    }
    vector<int> help(right - left + 1);
    int i = 0;
    int p1 = left;
    int p2 = mid + 1;
    while (p1 <= mid && p2 <= right) {
        help[i++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];
    }
    while (p1 <= mid) {
        help[i++] = arr[p1++];
    }
    while (p2 <= right) {
        help[i++] = arr[p2++];
    }
    for (i = 0; i < help.size(); i++) {
        arr[left + i] = help[i];
    }
    return ans;
}

int process(vector<int> &arr, int left, int right) {
    if (left == right) {
        return 0;
    }
    int mid = left + ((right - left) >> 1);
    return process(arr, left, mid) + process(arr, mid + 1, right) + merge(arr, left, mid, right);
}

int reversePairs(vector<int> &arr) {
    if (arr.empty() || arr.size() < 2) {
        return 0;
    }
    return process(arr, 0, arr.size() - 1);
}


int comparator(vector<int> &arr) {
    int ans = 0;
    for (int i = 0; i < arr.size(); i++) {
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[i] > (arr[j] << 1)) {
                ans++;
            }
        }
    }
    return ans;
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

bool isEqual(vector<int> &arr1, vector<int> &arr2) {
    if ((arr1.empty() && !arr2.empty()) || (!arr1.empty() && arr2.empty())) {
        return false;
    }
    if (arr1.empty() && arr2.empty()) {
        return true;
    }
    if (arr1.size() != arr2.size()) {
        return false;
    }
    for (int i = 0; i < arr1.size(); i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
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

int main() {
    int test_time = 500000;
    int maxSize = 100;
    int maxValue = 100;
    bool succeed = true;
    cout << "测试开始" << endl;
    vector<int> arr = {2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647};
    cout << reversePairs(arr) << endl;
//    for (int i = 0; i < test_time; i++) {
//        vector<int> arr1 = generateRandomVector(maxSize, maxValue);
//        vector<int> arr2(arr1);
//        if (reversePairs(arr1) != comparator(arr2)) {
//            succeed = false;
//            printArray(arr1);
//            printArray(arr2);
//            break;
//        }
//    }
    if (succeed) {
        cout << "测试结束" << endl;
    } else {
        cout << "测试失败" << endl;
    }
    return 0;
}