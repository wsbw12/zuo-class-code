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

// 快速排序
void swap(vector<int> &arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// 在arr[L...R]上,以arr[R]的位置进行划分
// <= arr[R]的数放在左边  > arr[R]的数放在右边

int partition(vector<int> &arr, int left, int right) {
    if (left > right) {
        return -1;
    }
    if (left == right) {
        return left;
    }
    // 定义一个区间为 <= 区间,该区间的右端点初始化为left-1 且arr[lessEqual]是划分之后第一个大于arr[right]的数
    int lessEqual = left - 1;
    int index = left; // index 表示当前元素的下标
    while (index <= right) {
        if (arr[index] <= arr[right]) { // 如果当前元素小于等于划分值,那么当前元素与<=区间的下一个数进行交换
            // 并且<= 区间向右移动一位 , 当前数也移动到下一个
            swap(arr, index, ++lessEqual);
        }
        // 如果当前元素大于划分值,那么当前元素向后移动一位即可
        index++;
    }
    // 最终走完循环之后,将划分值和<=区间的下一个数进行交换 并且<= 区间向右移动一位
    swap(arr, ++lessEqual, right);
    return lessEqual;
}

// arr[L...R]进行划分, 以arr[R]作为划分值
// < arr[R]的在左边  = arr[R]的在中间  > arr[R]的在右边 即荷兰国旗问题

pair<int, int> netherlandsFlag(vector<int> &arr, int left, int right) {
    if (left > right) {
        return {-1, -1};
    }
    if (left == right) {
        return {left, right};
    }
    int less = left - 1;// <= 区间的右边界
    int more = right;// > 区间的左边届
    int index = left; // index 表示当前元素的下标
    while (index < more) { // 当前位置不能和 > 区间的左边届撞上
        // 当前数如果等于划分值,那么直接将当前数下标向后移动一位即可
        if (arr[index] == arr[right]) {
            index++;
        } else if (arr[index] < arr[right]) {
            // 如果当前数小于划分值,那么将当前数与<= 区间的下一个数进行交换
            // 并且<= 区间向右移动一位 , 当前数也移动到下一个
            swap(arr, less + 1, index);
            less++;
            index++;
            // swap(arr,++less,index++) 这一行代码等于上面三行
        } else { // 如果当前数大于划分值,那么将当前数与>区间的前一个数进行交换 并且大于区间向前移动
            swap(arr, index, --more);
        }
    }
    // 因为上诉的划分中没有将arr[right]划分进去,所以此时在结束循环后,要将arr[right]与arr[more]交换
    // 最后返回等于划分值区间的左右端点
    swap(arr, more, right);
    return {less + 1, more};
}

// 快速排序 1.0版本

void process1(vector<int> &arr, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = partition(arr, left, right);//通过划分找到中间元素应该放置的位置
    process1(arr, left, mid - 1);
    process1(arr, mid + 1, right);
}

void quickSort1(vector<int> &arr) {
    if (arr.empty() || arr.size() < 2) {
        return;
    }
    process1(arr, 0, arr.size() - 1);
}

// 快速排序 2.0版本
void process2(vector<int> &arr, int left, int right) {
    if (left >= right) {
        return;
    }
    pair<int, int> equalArea = netherlandsFlag(arr, left, right);
    process2(arr, left, equalArea.first - 1);
    process2(arr, equalArea.second + 1, right);
}

void quickSort2(vector<int> &arr) {
    if (arr.empty() || arr.size() < 2) {
        return;
    }
    process2(arr, 0, arr.size() - 1);
}

// 快速排序 3.0版本

void process3(vector<int> &arr, int left, int right) {
    if (left >= right) {
        return;
    }
    srand((unsigned) time(NULL));
    swap(arr, left + (int) (rand() % (right - left + 1)), right);
    pair<int, int> equalArea = netherlandsFlag(arr, left, right);
    process3(arr, left, equalArea.first - 1);
    process3(arr, equalArea.second + 1, right);
}

void quickSort3(vector<int> &arr) {
    if (arr.empty() || arr.size() < 2) {
        return;
    }
    process3(arr, 0, arr.size() - 1);
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
    int test_time = 100000;//进行测试的次数
    int size = 1000;//生成数组的最大长度
    int value = 1000;//生成数组的最大值
    cout << "测试开始" << endl;
    for (int i = 0; i < test_time; i++) {
        vector<int> arr1 = generateRandomVector(size, value);
        vector<int> arr2(arr1);
        vector<int> arr3(arr1);
        if (!isEqual(arr1, arr2) || !isEqual(arr2, arr3)) {
            cout << "测试错误" << endl;
            printArray(arr1);
            printArray(arr2);
            printArray(arr3);
            break;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}