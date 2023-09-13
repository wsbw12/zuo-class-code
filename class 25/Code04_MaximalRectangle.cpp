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

// 给定一个二维数组matrix，其中的值不是0就是1，返回全部由1组成的最大子矩形内部有多少个1（面积）
// https://leetcode.cn/problems/maximal-rectangle/ leetcode 85

int largestRectangleArea(vector<int> &heights);

int maximalRectangle(vector<vector<char>> &matrix) {
    if (matrix.empty() || matrix.size() == 0 || matrix[0].size() == 0) {
        return 0;
    }
    int maxArea = 0;
    vector<int> height(matrix[0].size());
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            height[i] = matrix[i][j] == '0' ? 0 : height[j] + 1;
        }
        maxArea = max(largestRectangleArea(height), maxArea);
    }
    return maxArea;
}


int largestRectangleArea(vector<int> &heights) {
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