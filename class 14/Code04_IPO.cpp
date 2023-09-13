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

//输入正数数组costs、正数数组profits、正数K和正数M
//costs[i]表示i号项目的花费
//profits[i]表示i号项目在扣除花费之后还能挣到的钱(利润)
//K表示你只能串行的最多做k个项目
//M表示你初始的资金
//说明：每做完一个项目，马上获得的收益，可以支持你去做下一个项目，不能并行的做项目。
//输出：最后获得的最大钱数
// Leetcode 502. IPO : https://leetcode.cn/problems/ipo/
// 贪心解法
struct Program {
    int p;// 收益
    int c;// 花费
    Program(int a, int b) : p(a), c(b) {}
};

struct MinCostComp {
    bool operator()(Program a, Program b) {
        return a.c > b.c;
    }
};

struct MaxProfitComp {
    bool operator()(Program a, Program b) {
        return a.p < b.p;
    }
};

// 最多K个项目
// W是初始资金
// Profits[] Capital[] 一定等长
// 返回最终最大的资金
int findMaximizedCapital(int k, int w, vector<int> &profits, vector<int> &capital) {
    priority_queue<Program, vector<Program>, MinCostComp> minHeap;
    priority_queue<Program, vector<Program>, MaxProfitComp> maxHeap;
    for (int i = 0; i < profits.size(); i++) {
        Program *temp = new Program(profits[i], capital[i]);
        minHeap.push(*temp);
    }
    for (int i = 0; i < k; i++) {
        while (!minHeap.empty() && minHeap.top().c <= w) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
        if (maxHeap.empty()) { // 如果初始资金不够,直接返回
            return w;
        }
        w += maxHeap.top().p;
        maxHeap.pop();
    }
    return w;
}

int main() {
    int programSize = 12;
    int timeMax = 20;
    int times = 100000;
    clock_t start, end;
    start = clock();
    cout << "测试开始" << endl;

    cout << "测试结束" << endl;
    end = clock();   //结束时间
    cout << "测试的时间为: " << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ）
    return 0;
}