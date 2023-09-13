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

using namespace std;

//给定一个整型数组arr，代表数值不同的纸牌排成一条线
//玩家A和玩家B依次拿走每张纸牌
//规定玩家A先拿，玩家B后拿
//但是每个玩家每次只能拿走最左或最右的纸牌
//玩家A和玩家B都绝顶聪明
//请返回最后获胜者的分数
int f1(vector<int> &arr, int left, int right);

int g1(vector<int> &arr, int left, int right);

int f2(vector<int> &arr, int left, int right, vector<vector<int>> &fMap, vector<vector<int>> &gMap);

int g2(vector<int> &arr, int left, int right, vector<vector<int>> &fMap, vector<vector<int>> &gMap);

int win1(vector<int> &arr) {
    if (arr.empty() || arr.size() == 0) {
        return 0;
    }
    int first = f1(arr, 0, arr.size() - 1);
    int second = g1(arr, 0, arr.size() - 1);
    return max(first, second);
}

// arr[L..R]，先手获得的最好分数返回
int f1(vector<int> &arr, int left, int right) {
    if (left == right) {
        return arr[left];
    }
    int p1 = arr[left] + g1(arr, left + 1, right);
    int p2 = arr[right] + g1(arr, left, right - 1);
    return max(p1, p2);
}

// // arr[L..R]，后手获得的最好分数返回
int g1(vector<int> &arr, int left, int right) {
    if (left == right) {
        return 0;
    }
    int p1 = f1(arr, left + 1, right);
    int p2 = f1(arr, left, right - 1);
    // 由于这个函数是后选，其中p1,p2是在先选的人选则left位置上的数和right位置上的数之后,自己尽力选出最大值
    // 但是由于先选的人不是弱智,所以自己候后选的情况下只能选择先选的人给自己留下的最小值
    return min(p1, p2);
}

int win2(vector<int> &arr) {
    if (arr.empty() || arr.size() == 0) {
        return 0;
    }
    int n = arr.size();
    vector<vector<int>> fMap(n, vector<int>(n));
    vector<vector<int>> gMap(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fMap[i][j] = -1;
            gMap[i][j] = -1;
        }
    }
    int first = f2(arr, 0, arr.size() - 1, fMap, gMap);
    int second = g2(arr, 0, arr.size() - 1, fMap, gMap);
    return max(first, second);
}

int f2(vector<int> &arr, int left, int right, vector<vector<int>> &fMap, vector<vector<int>> &gMap) {
    if (fMap[left][right] != -1) {
        return fMap[left][right];
    }
    int ans = 0;
    if (left == right) {
        ans = arr[left];
    } else {
        int p1 = arr[left] + g2(arr, left + 1, right, fMap, gMap);
        int p2 = arr[right] + g2(arr, left, right - 1, fMap, gMap);
        ans = max(p1, p2);
    }
    fMap[left][right] = ans;
    return ans;
}


int g2(vector<int> &arr, int left, int right, vector<vector<int>> &fMap, vector<vector<int>> &gMap) {
    if (gMap[left][right] != -1) {
        return gMap[left][right];
    }
    int ans = 0;
    if (left == right) {
        ans = 0;
    } else {
        int p1 = f2(arr, left + 1, right, fMap, gMap);
        int p2 = f2(arr, left, right - 1, fMap, gMap);
        ans = min(p1, p2);
    }
    gMap[left][right] = ans;
    return ans;
}


int win3(vector<int> &arr) {
    if (arr.empty() || arr.size() == 0) {
        return 0;
    }
    int n = arr.size();
    vector<vector<int>> fMap(n, vector<int>(n));
    vector<vector<int>> gMap(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fMap[i][j] = 0;
            gMap[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        fMap[i][i] = arr[i];
    }
    for (int startCol = 1; startCol < n; startCol++) {
        int left = 0;
        int right = startCol;
        while (right < n) {
            fMap[left][right] = max(arr[left] + gMap[left + 1][right], arr[right] + gMap[left][right - 1]);
            gMap[left][right] = min(fMap[left + 1][right], fMap[left][right - 1]);
            left++;
            right++;
        }
    }
    return max(fMap[0][n - 1], gMap[0][n - 1]);
}

int main() {
    vector<int> arr = {5, 7, 4, 5, 8, 1, 6, 0, 3, 4, 6, 1, 7};
    cout << win1(arr) << endl;
    cout << win2(arr) << endl;
    cout << win3(arr) << endl;
    return 0;
}