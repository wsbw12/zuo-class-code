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

//请同学们自行搜索或者想象一个象棋的棋盘，
//然后把整个棋盘放入第一象限，棋盘的最左下角是(0,0)位置
//那么整个棋盘就是横坐标上9条线、纵坐标上10条线的区域
//给你三个 参数 x，y，k
//返回“马”从(0,0)位置出发，必须走k步
//最后落在(x,y)上的方法数有多少种?

// 当前来到的位置是（x,y）
// 还剩下rest步需要跳
// 跳完rest步，正好跳到a，b的方法数是多少？
// 10 * 9
int process(int x, int y, int rest, int a, int b);

int pick(vector<vector<vector<int>>> &dp, int x, int y, int rest);

int jump(int a, int b, int k) {
    return process(0, 0, k, a, b);
}

int process(int x, int y, int rest, int a, int b) {
    if (x < 0 || x > 9 || y < 0 || y > 8) {
        return 0;
    }
    if (rest == 0) {
        return (x == a && y == b) ? 1 : 0;
    }
    int ways = process(x + 2, y + 1, rest - 1, a, b);
    ways += process(x + 1, y + 2, rest - 1, a, b);
    ways += process(x - 1, y + 2, rest - 1, a, b);
    ways += process(x - 2, y + 1, rest - 1, a, b);
    ways += process(x - 2, y - 1, rest - 1, a, b);
    ways += process(x - 1, y - 2, rest - 1, a, b);
    ways += process(x + 1, y - 2, rest - 1, a, b);
    ways += process(x + 2, y - 1, rest - 1, a, b);
    return ways;
}

// 动态规划版本
int dp(int a, int b, int k) {
    vector<vector<vector<int>>> dp(10, vector<vector<int>>(9, vector<int>(k + 1)));
    //dp[i][j][k]表示从(i,j)点还剩k步的情况下到目标位置有多少钟方法
    dp[a][b][0] = 1;
    for (int rest = 1; rest <= k; rest++) {
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 9; y++) {
                int ways = pick(dp, x + 2, y + 1, rest - 1);
                ways += pick(dp, x + 1, y + 2, rest - 1);
                ways += pick(dp, x - 1, y + 2, rest - 1);
                ways += pick(dp, x - 2, y + 1, rest - 1);
                ways += pick(dp, x - 2, y - 1, rest - 1);
                ways += pick(dp, x - 1, y - 2, rest - 1);
                ways += pick(dp, x + 1, y - 2, rest - 1);
                ways += pick(dp, x + 2, y - 1, rest - 1);
                dp[x][y][rest] = ways;
            }
        }
    }
    return dp[0][0][k];
}

int pick(vector<vector<vector<int>>> &dp, int x, int y, int rest) {
    if (x < 0 || x > 9 || y < 0 || y > 8) {
        return 0;
    }
    return dp[x][y][rest];
}

int main() {
    int x = 7;
    int y = 7;
    int step = 10;
    cout << jump(x, y, step) << endl;
    cout << dp(x, y, step) << endl;
    return 0;
}