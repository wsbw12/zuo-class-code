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
#include <iomanip>
#include <cmath>
#include <deque>

using namespace std;

//给定一个非负数组arr，代表直方图，返回直方图的最大长方形面积
// https://leetcode.cn/problems/largest-rectangle-in-histogram/ leetcode 84

int largestRectangleArea1(vector<int> &heights) {
    if (heights.empty() || heights.size() == 0) {
        return 0;
    }
    int maxArea = 0;
    stack<int> stk;
    for (int i = 0; i < heights.size(); i++) {
        while (!stk.empty() && heights[i] <= heights[stk.top()]) {
            int j = stk.top();
            stk.pop();
            int k = stk.empty() ? -1 : stk.top();
            int curArea = (i - k - 1) * heights[j];
            maxArea = max(maxArea, curArea);
        }
        stk.push(i);
    }
    while (!stk.empty()) {
        int j = stk.top();
        stk.pop();
        int k = stk.empty() ? -1 : stk.top();
        int curArea = (heights.size() - k - 1) * heights[j];
        maxArea = max(curArea, maxArea);
    }
    return maxArea;
}