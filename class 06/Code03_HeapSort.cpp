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
#include <cmath>

using namespace std;

// 堆排序

void swap(vector<int> &arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void heapInsert(vector<int> &arr, int index) {
    while (arr[index] > arr[(index - 1) / 2]) {
        swap(arr, index, (index - 1) / 2);
        index = (index - 1) / 2;
    }
}

void heapify(vector<int> &arr, int index, int heapSize) {
    int left = index * 2 + 1;
    while (left < heapSize) {
        int largest = left + 1 < heapSize && arr[left + 1] > arr[left] ? left + 1 : left;
        largest = arr[largest] > arr[index] ? largest : index;
        if (largest == index) {
            break;
        }
        swap(arr, largest, index);
        index = largest;
        left = index * 2 + 1;
    }
}

void heapSort(vector<int> &arr) {
    if (arr.empty() || arr.size() < 2) {
        return;
    }
    for (int i = arr.size() - 1; i >= 0; i--) { // 这个方法是O(N)
        heapify(arr, i, arr.size());
    }
//    for (int i = 0; i < arr.size(); i++) { // 这个方法是O(NlogN)
//        heapInsert(arr, i);
//    }
    int heapSize = arr.size();
    swap(arr, 0, --heapSize);
    while (heapSize > 0) {
        heapify(arr, 0, heapSize);
        swap(arr, 0, --heapSize);
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

struct comp {
    bool operator()(const int a, const int b) {
        return a > b;
    }
};

int main() {
    priority_queue<int, vector<int>, comp> min_heap; // 定义一个小根堆
    min_heap.push(6);
    min_heap.push(8);
    min_heap.push(0);
    min_heap.push(2);
    min_heap.push(9);
    min_heap.push(1);
    while (!min_heap.empty()) {
        cout << min_heap.top() << endl;
        min_heap.pop();
    }
    cout << "====================" << endl;
    int value = 1000;
    int size = 100;
    int test_time = 1000000;
    srand((int) time(NULL));
    cout << "测试开始" << endl;
    for (int i = 0; i < test_time; i++) {
        vector<int> arr1 = generateRandomVector(size, value);
        vector<int> arr2(arr1);
        heapSort(arr1);
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
