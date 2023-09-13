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

//假设有排成一行的N个位置记为1~N，N一定大于或等于2
//开始时机器人在其中的M位置上(M一定是1~N中的一个)
//如果机器人来到1位置，那么下一步只能往右来到2位置；
//如果机器人来到N位置，那么下一步只能往左来到N-1位置；
//如果机器人来到中间位置，那么下一步可以往左走或者往右走；
//规定机器人必须走K步，最终能来到P位置(P也是1~N中的一个)的方法有多少种
//给定四个参数 N、M、K、P，返回方法数
int process1(int cur, int rest, int aim, int N);

int process2(int cur, int rest, int aim, int N, vector<vector<int>> &dp);

// 暴力递归的方法
int ways1(int N, int start, int aim, int K) {
    if (N < 2 || start < 1 || start > N || aim < 1 || aim > N || K < 1) {
        return -1;
    }
    return process1(start, K, aim, N);
}

// 机器人当前来到的位置是cur，
// 机器人还有rest步需要去走，
// 最终的目标是aim，
// 有哪些位置？1~N
// 返回：机器人从cur出发，走过rest步之后，最终停在aim的方法数，是多少？
int process1(int cur, int rest, int aim, int N) {
    if (rest == 0) {
        return cur == aim ? 1 : 0;
    }
    if (cur == 1) {
        return process1(2, rest - 1, aim, N);
    }
    if (cur == N) {
        return process1(N - 1, rest - 1, aim, N);
    }
    return process1(cur - 1, rest - 1, aim, N) + process1(cur + 1, rest - 1, aim, N);
}

// 用一张缓存表 ---- 实现记忆化搜索
int ways2(int N, int start, int aim, int K) {
    if (N < 2 || start < 1 || start > N || aim < 1 || aim > N || K < 1) {
        return -1;
    }
    // 建议缓存表
    vector<vector<int>> dp(N + 1, vector<int>(K + 1));
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            dp[i][j] = -1;
        }
    }
    // dp就是缓存表
    // dp[cur][rest] == -1 -> process1(cur, rest)之前没算过！
    // dp[cur][rest] != -1 -> process1(cur, rest)之前算过！返回值，dp[cur][rest]
    // N+1 * K+1
    return process2(start, K, aim, N, dp);
}

int process2(int cur, int rest, int aim, int N, vector<vector<int>> &dp) {
    if (dp[cur][rest] != -1) {
        return dp[cur][rest];
    }
    int ans;
    if (rest == 0) {
        ans = cur == aim ? 1 : 0;
    } else if (cur == 1) {
        ans = process2(2, rest - 1, aim, N, dp);
    } else if (cur == N) {
        ans = process2(N - 1, rest - 1, aim, N, dp);
    } else {
        ans = process2(cur - 1, rest - 1, aim, N, dp) + process2(cur + 1, rest - 1, aim, N, dp);
    }
    dp[cur][rest] = ans;
    return ans;
}

int ways3(int N, int start, int aim, int K) {
    if (N < 2 || start < 1 || start > N || aim < 1 || aim > N || K < 1) {
        return -1;
    }
    vector<vector<int>> dp(N + 1, vector<int>(K + 1));
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            dp[i][j] = 0;
        }
    }
    //dp[cur][rest]
    dp[aim][0] = 1;// 当rest=0的时候,cur来到aim此时算一个
    // for循环一列一列的计算
    for (int rest = 1; rest <= K; rest++) {
        dp[1][rest] = dp[2][rest - 1]; // 对应暴力递归中的边界条件
        for (int cur = 2; cur < N; cur++) {
            dp[cur][rest] = dp[cur - 1][rest - 1] + dp[cur + 1][rest - 1];
        }
        dp[N][rest] = dp[N - 1][rest - 1];
    }
    return dp[start][K];
}

int main() {
    cout << ways1(5, 2, 4, 6) << endl;
    cout << ways2(5, 2, 4, 6) << endl;
    cout << ways3(5, 2, 4, 6) << endl;
    return 0;
}