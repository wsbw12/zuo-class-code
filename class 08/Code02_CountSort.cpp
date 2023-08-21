#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// 计数排序
// 限制是需要确定排序数据的范围,如果数据范围特大不适合使用计数排序
void countSort(vector<int> &arr) {
    if (arr.empty() || arr.size() < 2) {
        return;
    }
    int max_num = INT_MIN;
    for (int i = 0; i < arr.size(); i++) {
        max_num = max(max_num, arr[i]);
    }
    vector<int> bucket(max_num + 1);
    for (int i = 0; i < arr.size(); i++) {
        bucket[arr[i]]++;
    }
    int i = 0;
    for (int j = 0; j < bucket.size(); j++) {
        while (bucket[j]--) {
            arr[i++] = j;
        }
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
    int maxValue = 150;
    cout << "测试开始" << endl;
    for (int i = 0; i < test_time; i++) {
        vector<int> arr1 = generateRandomVector(maxSize, maxValue);
        vector<int> arr2(arr1);
        countSort(arr1);
        sort(arr2.begin(), arr2.end());
        if (!isEqual(arr1, arr2)) {
            cout << "测试失败" << endl;
            printArray(arr1);
            printArray(arr2);
            break;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}