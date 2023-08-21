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

// 给你一个无序数组和一个整数k,满足无序数组排好序的过程中,每个数移动的距离不超过k
// 以O(NlogK)的时间复杂度将这个数组排好序

void swap(vector<int> &arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int mathMin(int a, int b) {
    return a < b ? a : b;
}

vector<int> randomArrayNoMoveMoreK(int maxSize, int maxValue, int k) {
    srand((int) time(NULL));
    vector<int> arr((int) (rand() % (maxSize + 1)));
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = (int) (rand() % (maxSize + 1)) - (int) (rand() % maxSize);
    }
    // 先将生成的数组进行排序
    sort(arr.begin(), arr.end());
    // 然后进行随意的交换,但是保证每个数的距离不超过k
    // swap[i]==true, 表示i位置已经参与过交换了 为false表示没有参与过交换
    vector<bool> isSwap(arr.size());
    for (int i = 0; i < arr.size(); i++) {
        // 找到一个下标与i的距离不超过k,并且下标不能超过数组的长度
        int j = mathMin(i + (int) (rand() % (k + 1)), arr.size() - 1);
        if (!isSwap[i] && !isSwap[j]) { // 如果这两个位置上的数都没有被交换过那么就先标记再交换
            isSwap[i] = true;
            isSwap[j] = true;
            swap(arr, i, j);
        }
    }
    return arr;
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


void sortedArrDistanceLessK(vector<int> &arr, int k) {
    if (k == 0) { // k==0 表示此时数组是有序的
        return;
    }
    priority_queue<int, vector<int>, comp> min_heap;// 定义一个小根堆
    int index = 0;
    // 将(0..k-1)位置上的数先放入小根堆中,因为根据题目条件,排完序后arr[0]位置上的数一定在(0..k-1)范围上
    for (; index <= mathMin(arr.size() - 1, k - 1); index++) {
        min_heap.push(arr[index]);
    }
    int i = 0;
    for (; index < arr.size(); i++, index++) {
        min_heap.push(arr[index]);
        arr[i] = min_heap.top(); // 将小根堆的堆顶元素依次放入排序数组的前后位置
        min_heap.pop();
    }
    while (!min_heap.empty()) {
        arr[i++] = min_heap.top();
        min_heap.pop();
    }
}


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
        int k = (int) (rand() % size) + 1;
        vector<int> arr = randomArrayNoMoveMoreK(size, value, k);
        vector<int> arr1(arr);
        vector<int> arr2(arr);
        sortedArrDistanceLessK(arr1, k);
        sort(arr2.begin(), arr2.end());
        if (!isEqual(arr1, arr2)) {
            cout << "K= " << k << endl;
            printArray(arr);
            printArray(arr1);
            printArray(arr2);
            cout << "测试错误" << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}