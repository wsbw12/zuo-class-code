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

//最大线段重合问题(用堆的实现)
//给定很多线段，每个线段都有两个数[start, end].表示线段开始位置和结束位置，左右都是闭 区间 规定:
// 1)线段的开始和结束位置一定都是整数值 2)线段重合区域的长度必须>=1返回线段最多重合区域中，包含了几条线段

struct LINES {
    int start;
    int end;

    LINES(int x, int y) : start(x), end(y) {}
};


vector<LINES> line;
vector<LINES> l;

int Max(int a, int b) {
    return a > b ? a : b;
}

bool MyCmp(const LINES &L1, const LINES &L2) {
    return (L1.start < L2.start);
}

struct comp {
    bool operator()(int a, int b) {
        // 如果a->val > b->val 为true 则将第二个参数放前面
        // 如果a->val > b->val 为false 则将第一个参数放前面
        // 如果a->val = b->val 谁放前面都一样
        return a > b;
    }
};

// 用堆实现的优化的解法
int maxCover2(vector<vector<int>> &lines) {
    int n = lines.size();
    vector<LINES> *line = new vector<LINES>[n];
    for (int i = 0; i < n; i++) {
        LINES temp = {lines[i][0], lines[i][1]};
        line->push_back(temp);
    }
    sort(line->begin(), line->end(), MyCmp); //将每个线段按开始位置从小到大排序
    priority_queue<int, vector<int>, comp> minHeap; // 定义一个小根堆
    int max_num = 0;
    vector<LINES>::iterator iter;
    // 此时遍历的线段的顺序是按照起始位置从小到大进行排序的
    for (iter = line->begin(); iter != line->end(); iter++) { // 类似于for(int i=0;i<5;i++)
        // 每当遍历到一个线段的时候,首先判断小根堆的堆顶位置是否小于等于遍历到的线段的起始位置
        // 如果小根堆的堆顶位置小于等于遍历到的线段的起始位置,说明小根堆中存放的那些线段的终止位置还没遍历到的线段的起始位置长
        // 那么就不会产生重叠区域,所以不断弹出小根堆中的这种线段
        while (!minHeap.empty() && minHeap.top() <= iter->start) {
            minHeap.pop();
        }
        // 每次在小根堆里面放入的是每个线段的终点位置
        minHeap.push(iter->end);
        // 当while循环结束后,此时小根堆的长度就是能形成重叠区域的线段的个数
        max_num = Max(max_num, minHeap.size());
    }
    return max_num;
}


// 暴力解法
int maxCover1(vector<vector<int>> &lines) {
    int min_num = INT_MAX;
    int max_num = INT_MIN;
    for (int i = 0; i < lines.size(); i++) {
        min_num = min(min_num, lines[i][0]); // 找到每个线段起始点的最小值
        max_num = max(max_num, lines[i][1]); // 找到每个线段终点的最大值
    }
    // 所有线段能覆盖的长度为 max_num-min_num
    int cover = 0;
    for (double p = min_num + 0.5; p < max_num; p++) {
        int cur = 0;
        for (int i = 0; i < lines.size(); i++) { // 遍历每一个线段
            if (lines[i][0] < p && lines[i][1] > p) {
                cur++;
            }
        }
        cover = max(cover, cur);
    }
    return cover;
}

vector<vector<int>> generateLines(int N, int L, int R) {
    srand((int) time(NULL));
    int size = (int) (rand() % N) + 1;
    vector<vector<int>> ans(size, vector<int>(2));
    for (int i = 0; i < size; i++) {
        int a = L + (int) (rand() % (R - L + 1));
        int b = L + (int) (rand() % (R - L + 1));
        if (a == b) {
            b = a + 1;
        }
        ans[i][0] = min(a, b);
        ans[i][1] = max(a, b);
    }
    return ans;
}

int main() {
    vector<LINES> *l = new vector<LINES>[5];
    l->push_back({1, 2});
    l->push_back({3, 2});
    l->push_back({7, 2});
    l->push_back({2, 2});
    l->push_back({5, 2});
    sort(l->begin(), l->end(), MyCmp);
    for (int i = 0; i < 5; i++) {
        vector<LINES>::iterator iter;
        for (iter = l[i].begin(); iter != l[i].end(); iter++) {
            cout << iter->start << " ";
        }
    }
    cout << endl;
    cout << "测试开始" << endl;
    int N = 100;
    int L = 0;
    int R = 200;
    int test_time = 20000;
    for (int i = 0; i < test_time; i++) {
        vector<vector<int>> lines = generateLines(N, L, R);
        int ans1 = maxCover1(lines);
        int ans2 = maxCover2(lines);
        if (ans1 != ans2) {
            cout << "测试错误" << endl;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}