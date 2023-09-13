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

//给定一个整型数组arr，和一个整数num
//某个arr中的子数组sub，如果想达标，必须满足：sub中最大值 – sub中最小值 <= num，
//返回arr中达标子数组的数量

// 暴力的方法
int right(vector<int> &arr, int sum) {
    if (arr.empty() || arr.size() == 0 || sum < 0) {
        return 0;
    }
    int n = arr.size();
    int count = 0;
    for (int left = 0; left < n; left++) {
        for (int right = left; right < n; right++) {
            int max_num = arr[left];
            int min_num = arr[left];
            for (int i = left + 1; i <= right; i++) {
                max_num = max(max_num, arr[i]);
                min_num = min(min_num, arr[i]);
            }
            if (max_num - min_num <= sum) {
                count++;
            }
        }
    }
    return count;
}

// 滑动窗口的方法
int num(vector<int> &arr, int sum) {
    if (arr.empty() || arr.size() == 0 || sum < 0) {
        return 0;
    }
    int n = arr.size();
    int count = 0;
    // 双端队列中存放的是数组的下标
    deque<int> maxWindow;
    deque<int> minWindow;
    int right = 0;
    for (int left = 0; left < n; left++) {
        while (right < n) {
            while (!maxWindow.empty() && arr[maxWindow.back()] <= arr[right]) {
                maxWindow.pop_back();
            }
            maxWindow.push_back(right);
            while (!minWindow.empty() && arr[minWindow.back()] >= arr[right]) {
                minWindow.pop_back();
            }
            minWindow.push_back(right);
            if (arr[maxWindow.front()] - arr[minWindow.front()] > sum) {
                break;
            } else {
                right++;
            }
        }
        count += right - left;
        if (maxWindow.front() == left) {
            maxWindow.pop_front();
        }
        if (minWindow.front() == left) {
            minWindow.pop_front();
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

void printArr(vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int test_time = 10000;
    int maxSize = 100;
    int maxValue = 200;
    cout << "test begin" << endl;
    for (int i = 0; i < test_time; i++) {
        vector<int> arr = generateRandomVector(maxSize, maxValue);
        int sum = (int) (rand() % (arr.size() + 1));
        int ans1 = num(arr, sum);
        int ans2 = right(arr, sum);
        if (ans1 != ans2) {
            cout << "Oops!" << endl;
            printArr(arr);
            cout << sum << endl;
            cout << ans1 << endl;
            cout << ans2 << endl;
        }
    }
    cout << "test finish!" << endl;
    return 0;
}