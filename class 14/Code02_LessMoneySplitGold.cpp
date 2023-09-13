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

using namespace std;
//一块金条切成两半，是需要花费和长度数值一样的铜板
//比如长度为20的金条，不管怎么切都要花费20个铜板，一群人想整分整块金条，怎么分最省铜板?
//例如，给定数组{10,20,30}，代表一共三个人，整块金条长度为60，金条要分成10，20，30三个部分。
//如果先把长度60的金条分成10和50，花费60；再把长度50的金条分成20和30，花费50；一共花费110铜板
//但如果先把长度60的金条分成30和30，花费60；再把长度30金条分成10和20，花费30；一共花费90铜板
//输入一个数组，返回分割的最小代价
// 即哈夫曼编码

// 贪心解法
struct compID {
    bool operator()(int a, int b) {
        return a > b;
    }
};

int lessMoney2(vector<int> &arr) {
    priority_queue<int, vector<int>, compID> minHeap;
    for (int i = 0; i < arr.size(); i++) {
        minHeap.push(arr[i]);
    }
    int sum = 0;
    int cur = 0;
    while (minHeap.size() > 1) {
        int a = minHeap.top();
        minHeap.pop();
        int b = minHeap.top();
        minHeap.pop();
        cur = a + b;
        sum += cur;
        minHeap.push(cur);
    }
    return sum;
}

// 暴力解法

vector<int> copyAndMergeTwo(vector<int> &arr, int i, int j) {
    vector<int> ans(arr.size() - 1);
    int ansi = 0;
    for (int arri = 0; arri < arr.size(); arri++) {
        if (arri != i && arri != j) {
            ans[ansi++] = arr[arri];
        }
    }
    ans[ansi] = arr[i] + arr[j];
    return ans;
}

// 等待合并的数都在arr里，pre之前的合并行为产生了多少总代价
// arr中只剩一个数字的时候，停止合并，返回最小的总代价
int process(vector<int> arr, int pre) {
    if (arr.size() == 1) {
        return pre;
    }
    int ans = INT_MAX;
    for (int i = 0; i < arr.size(); i++) {
        for (int j = i + 1; j < arr.size(); j++) {
            ans = min(ans, process(copyAndMergeTwo(arr, i, j), pre + arr[i] + arr[j]));
        }
    }
    return ans;
}

int lessMoney1(vector<int> &arr) {
    if (arr.empty() || arr.size() == 0) {
        return 0;
    }
    return process(arr, 0);
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

int main() {
    int programSize = 12;
    int timeMax = 20;
    int times = 100000;
    clock_t start, end;
    start = clock();
    cout << "测试开始" << endl;
    for (int i = 0; i < times; i++) {
        vector<int> arr = generateRandomVector(programSize, timeMax);
        if (lessMoney1(arr) != lessMoney2(arr)) {
            cout << "测试错误" << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
    end = clock();   //结束时间
    cout << "测试的时间为: " << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ）
    return 0;
}