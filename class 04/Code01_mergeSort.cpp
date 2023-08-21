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

void merge(vector<int> &arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = 0;
    int p1 = left;
    int p2 = mid + 1;
    while (p1 <= mid && p2 <= right) {
        temp[i++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];
    }
    while (p1 <= mid) {
        temp[i++] = arr[p1++];
    }
    while (p2 <= right) {
        temp[i++] = arr[p2++];
    }
    for (i = 0; i < temp.size(); i++) {
        arr[left + i] = temp[i];
    }
}

void process(vector<int> &arr, int left, int right) {
    if (left == right) {
        return;
    }
    int mid = left + ((right - left) >> 1); // 等同于(left+right)/2,但是可以防止left+right越界
    process(arr, left, mid);
    process(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void mergeSort1(vector<int> &arr) { // 递归版本的归并排序
    if (arr.empty() || arr.size() < 2) {
        return;
    }
    process(arr, 0, arr.size() - 1);
}

void mergeSort2(vector<int> &arr) { //非递归方法的归并排序
    if (arr.empty() || arr.size() < 2) {
        return;
    }
    int step = 1; // 首先设置步长为1
    int n = arr.size();
    while (step < n) {
        int left = 0; // 设置第一个区间的左边届,第一个区间的范围为(left-mid),第二个区间的范围为(mid+1,right)
        while (left < n) {
            int mid = 0;
            if (n - left >= step) { //即处理第一个区间的右边界是否越界问题
                mid = left + step - 1;
            } else {
                mid = n - 1;
            }
            if (mid == n - 1) {
                break;
            }
            int right = 0; // 开始处理第二个区间 第二个区间的范围为(mid+1,right)
            if (n - 1 - mid >= step) {
                right = mid + step;
            } else {
                right = n - 1;
            }
            merge(arr, left, mid, right);
            if (right == n - 1) {
                break;
            } else {
                left = right + 1;
            }
        }
        if (step > n / 2) { // 每次合并完两个区间后,将step的值翻倍,但是为了防止step*2的值大于INT_MAX
            // 要判断下边界的条件
            break;
        }
        step *= 2;
    }
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
    int test_time = 10000;//进行测试的次数
    int size = 1000;//生成数组的最大长度
    int value = 1000;//生成数组的最大值
    cout << "测试开始" << endl;
    for (int i = 0; i < test_time; i++) {
        vector<int> nums1(generateRandomVector(size, value));
        vector<int> nums2(nums1);
        mergeSort1(nums1);
        mergeSort2(nums2);
        if (!isEqual(nums1, nums2)) {
            cout << "出错了!" << endl;
            printArray(nums1);
            printArray(nums2);
            break;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}