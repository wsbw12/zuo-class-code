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

//给定5个参数，N，M，row，col，k
//表示在N*M的区域上，醉汉Bob初始在(row,col)位置
//Bob一共要迈出k步，且每步都会等概率向上下左右四个方向走一个单位
//任何时候Bob只要离开N*M的区域，就直接死亡
//返回k步之后，Bob还在N*M的区域的概率
long long process(int row, int col, int rest, int N, int M);

long long pick(vector<vector<vector<int>>> &dp, int N, int M, int r, int c, int rest);

double livePosibility1(int row, int col, int k, int N, int M) {
    return (double) process(row, col, k, N, M) / (pow(4, k) * 1.0);
}

// 目前在row，col位置，还有rest步要走，走完了如果还在棋盘中就获得1个生存点，返回总的生存点数
long long process(int row, int col, int rest, int N, int M) {
    if (row < 0 || row == N || col < 0 || col == M) {
        return 0;
    }
    if (rest == 0) {
        return 1;
    }
    long long up = process(row - 1, col, rest - 1, N, M);
    long long down = process(row + 1, col, rest - 1, N, M);
    long long left = process(row, col - 1, rest - 1, N, M);
    long long right = process(row, col + 1, rest - 1, N, M);
    return up + down + left + right;
}

double livePosibility2(int row, int col, int k, int N, int M) {
    vector<vector<vector<int>>> dp(N, vector<vector<int>>(M, vector<int>(k + 1)));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j][0] = 1;
        }
    }
    for (int rest = 1; rest <= k; rest++) {
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < M; c++) {
                dp[r][c][rest] = pick(dp, N, M, r - 1, c, rest - 1);
                dp[r][c][rest] += pick(dp, N, M, r + 1, c, rest - 1);
                dp[r][c][rest] += pick(dp, N, M, r, c - 1, rest - 1);
                dp[r][c][rest] += pick(dp, N, M, r, c + 1, rest - 1);
            }
        }
    }
    return (double) dp[row][col][k] / (pow(4, k) * 1.0);
}

long long pick(vector<vector<vector<int>>> &dp, int N, int M, int r, int c, int rest) {
    if (r < 0 || r == N || c < 0 || c == M) {
        return 0;
    }
    return dp[r][c][rest];
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

void printArr(vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


int main() {
    cout << livePosibility1(6, 6, 10, 50, 50) << endl;
    cout << livePosibility2(6, 6, 10, 50, 50) << endl;
    return 0;
}