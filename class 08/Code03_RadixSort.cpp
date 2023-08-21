#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// 基数排序
int maxBits(vector<int> &arr);

void radixSort(vector<int> &arr, int left, int right, int digit);

int getDigit(int x, int d);

void radix_sort(vector<int> &arr) {
    if (arr.empty() || arr.size() < 2) {
        return;
    }
    radixSort(arr, 0, arr.size() - 1, maxBits(arr));
}

int maxBits(vector<int> &arr) {
    int max_num = INT_MIN;
    for (int i = 0; i < arr.size(); i++) {
        max_num = max(max_num, arr[i]);
    }
    int res = 0;
    while (max_num) {
        res++;
        max_num /= 10;
    }
    return res;
}

// 在arr[left...right]范围内进行排序
// 数组中数据的最大十进制位为digit
void radixSort(vector<int> &arr, int left, int right, int digit) {
    int radix = 10;
    int i = 0, j = 0;
    vector<int> help(right - left + 1);
    for (int d = 1; d <= digit; d++) {
        // count[0] 当前位(d位)是0的数字有多少个
        // count[1] 当前位(d位)是(0和1)的数字有多少个
        // count[i] 当前位(d位)是(0~i)的数字有多少个
        vector<int> count(radix);
        for (i = left; i <= right; i++) {
            j = getDigit(arr[i], d); // 获取arr[i]中第d位上的数字是几
            count[j]++;
        }
        for (i = 1; i < radix; i++) {
            count[i] = count[i] + count[i - 1];
        }
        // 代码执行到这里就完成了count数组的任务
        // 从后往前遍历
        for (i = right; i >= left; i--) {
            j = getDigit(arr[i], d); // 先找到每个数第d个位置的数字是多少
            // 查看count数组得知从count[j]表示的是当前位(d位)是(0~j)的数字有多少个
            // 假如有x个,那么当前位(d位)是(0~j)的数字应该放在区间为(0 ~ x-1)的数组位置上
            // 由于是从后往前遍历的,那么此时遍历的数应该放在count[j] - 1位置
            help[count[j] - 1] = arr[i];
            count[j]--;
        }
        // 将help数组整理后的数据重新放入arr数组中,循环遍历每个位置
        for (i = left, j = 0; i <= right; i++, j++) {
            arr[i] = help[i];
        }
    }
}

int getDigit(int x, int d) {
    return ((x / ((int) pow(10, d - 1))) % 10);
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
        radix_sort(arr1);
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