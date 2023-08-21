#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;
// 希尔排序  即调整步长的插入排序


void swap(vector<int> &arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void shellSort(vector<int> &arr) {
    if (arr.empty() || arr.size() < 2) {
        return;
    }
    // 步长依次为5、2、1
    // 在插入排序中，一步一步往前交换，直到左边的数<=当前的数，停止
    // 在希尔排序中，如果步长依次为5、2、1
    // 那么来到每个数，每次跳5 步往前交换，直到往前5步的数<=当前的数，停止
    // 然后再来到每个数，每次跳3 步往前交换，直到往前3步的数<=当前的数，停止
    // 然后再来到每个数，每次跳1 步往前交换，直到往前1步的数<=当前的数，停止
    vector<int> step = {5, 2, 1};
    for (int s = 0; s < step.size(); s++) {
        for (int i = step[s]; i < arr.size(); i++) {
            for (int j = i - step[s]; j >= 0 && arr[j] > arr[j + step[s]]; j -= step[s]) {
                swap(arr, j, j + step[s]);
            }
        }
    }
}

void insertionSort(vector<int> &arr) {
    if (arr.empty() || arr.size() < 2) {
        return;
    }
    for (int i = 1; i < arr.size(); i++) {
        for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--) {
            swap(arr, j, j + 1);
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
    int test_time = 50000;
    int maxSize = 100;
    int maxValue = 100;
    bool succeed = true;
    cout << "测试开始" << endl;
    srand((int) time(NULL));
    for (int i = 0; i < test_time; i++) {
        int len = (int) (rand() % maxSize);
        vector<int> arr1 = generateRandomVector(len, maxSize);
        vector<int> arr2(arr1);
        shellSort(arr1);
        insertionSort(arr2);
        if (!isEqual(arr1, arr2)) {
            succeed = false;
            printArray(arr1);
            printArray(arr2);
            cout << "测试错误" << endl;
            break;
        }
    }
    cout << "测试通过" << endl;
    cout << "=============" << endl;
    int len = 100000;
    cout << "数据样本的长度 : " << len << " ";
    vector<int> arr1 = generateRandomVector(len, maxValue);
    vector<int> arr2(arr1);
    clock_t start, end;
    start = clock();
    shellSort(arr1);
    end = clock();   //结束时间
    cout << "希尔排序的时间为: " << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ）
    start = clock();
    insertionSort(arr2);
    end = clock();   //结束时间
    cout << "数据样本的长度 : " << len << " ";
    cout << "插入排序的时间为: " << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}