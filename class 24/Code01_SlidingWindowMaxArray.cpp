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

//窗口内最大值或最小值更新结构的实现
//假设一个固定大小为W的窗口，依次划过arr，
//返回每一次滑出状况的最大值
//例如，arr = [4,3,5,4,3,3,6,7], W = 3
//返回：[5,5,5,4,6,7]

// 暴力的方法
vector<int> right(vector<int> &arr, int w) {
    vector<int> temp;
    if (arr.empty() || w < 1 || arr.size() < w) {
        return temp;
    }
    int n = arr.size();
    vector<int> res(n - w + 1);
    int index = 0;
    int left = 0;
    int right = w - 1;
    while (right < n) {
        int max_num = arr[left];
        for (int i = left + 1; i <= right; i++) {
            max_num = max(max_num, arr[i]);
        }
        res[index++] = max_num;
        left++;
        right++;
    }
    return res;
}

// 滑动窗口的方法
vector<int> genMaxWindow(vector<int> &arr, int w) {
    vector<int> temp;
    if (arr.empty() || w < 1 || arr.size() < w) {
        return temp;
    }
    // q max 窗口最大值的更新结构
    // 放下标
    deque<int> qMax;
    int n = arr.size();
    vector<int> res(n - w + 1);
    int index = 0;
    for (int right = 0; right < arr.size(); right++) {
        while (!qMax.empty() && arr[qMax.back()] <= arr[right]) {
            qMax.pop_back();
        }
        qMax.push_back(right);
        if (qMax.front() == right - w) {
            qMax.pop_front();
        }
        if (right >= w - 1) {
            res[index++] = arr[qMax.front()];
        }
    }
    return res;
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

int main() {
    int test_time = 100000;
    int maxSize = 100;
    int maxValue = 100;
    cout << "test begin" << endl;
    for (int i = 0; i < test_time; i++) {
        vector<int> arr = generateRandomVector(maxSize, maxValue);
        int w = (int) (rand() % (arr.size() + 1));
        vector<int> ans1 = genMaxWindow(arr, w);
        vector<int> ans2 = right(arr, w);
        if (!isEqual(ans1, ans2)) {
            cout << "Oops!" << endl;
        }
    }
    cout << "test finish!" << endl;
    return 0;
}