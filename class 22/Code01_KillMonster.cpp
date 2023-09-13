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

//给定3个参数，N，M，K
//怪兽有N滴血，等着英雄来砍自己
//英雄每一次打击，都会让怪兽流失[0~M]的血量
//到底流失多少？每一次在[0~M]上等概率的获得一个值
//求K次打击之后，英雄把怪兽砍死的概率
long long process(int times, int M, int hp);

double right(int N, int M, int K) {
    if (N < 1 || M < 1 || K < 1) {
        return 0;
    }
    long long all = 1LL * (pow(M + 1, K));
    long long kill = process(K, M, N);
    return (double) ((double) kill / (double) all * 1.0);
}

// 怪兽还剩hp点血
// 每次的伤害在[0~M]范围上
// 还有times次可以砍
// 返回砍死的情况数！
long long process(int times, int M, int hp) {
    if (times == 0) {
        return hp <= 0 ? 1 : 0;
    }
    if (hp <= 0) {
        return 1LL * pow(M + 1, times);
    }
    long long ways = 0;
    for (int i = 0; i <= M; i++) {
        ways += process(times - 1, M, hp - i);
    }
    return ways;
}

double dp1(int N, int M, int K) {
    if (N < 1 || M < 1 || K < 1) {
        return 0;
    }
    long long all = 1LL * (pow(M + 1, K));
    vector<vector<long long>> dp(K + 1, vector<long long>(N + 1));
    dp[0][0] = 1; //递归中的baseCase
    for (int times = 1; times <= K; times++) {
        dp[times][0] = 1LL * pow(M + 1, times);
        for (int hp = 1; hp <= N; hp++) {
            long long ways = 0;
            for (int i = 0; i <= M; i++) {
                if (hp - i >= 0) { // 怪物没被我们的伤害打死的情况
                    ways += dp[times - 1][hp - i];
                } else { // 怪物被我们的伤害打死的情况,此时攻击相当与鞭尸
                    ways += 1LL * pow(M + 1, times - 1);
                }
            }
            dp[times][hp] = ways;
        }
    }
    long long kill = dp[K][N];
    return (double) ((1.0 * kill) / (1.0 * all));
}

double dp2(int N, int M, int K) {
    if (N < 1 || M < 1 || K < 1) {
        return 0;
    }
    long long all = 1LL * (pow(M + 1, K));
    vector<vector<long long>> dp(K + 1, vector<long long>(N + 1));
    dp[0][0] = 1; //递归中的baseCase
    for (int times = 1; times <= K; times++) {
        dp[times][0] = 1LL * pow(M + 1, times);
        for (int hp = 1; hp <= N; hp++) {
            dp[times][hp] = dp[times][hp - 1] + dp[times - 1][hp];
            if (hp - 1 - M >= 0) {
                dp[times][hp] -= dp[times - 1][hp - 1 - M];
            } else {
                dp[times][hp] -= pow(M + 1, times - 1);
            }
        }
    }
    long long kill = dp[K][N];
    return (double) ((1.0 * kill) / (1.0 * all));
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
    int NMax = 10;
    int MMax = 10;
    int KMax = 10;
    int test_time = 200;
    cout << "测试开始" << endl;
    for (int i = 0; i < test_time; i++) {
        int N = (int) (rand() % NMax);
        int M = (int) (rand() % MMax);
        int K = (int) (rand() % KMax);
        double ans1 = dp1(N, M, K);
        double ans2 = dp2(N, M, K);
        if (ans1 != ans2) {
            cout << "测试错误" << endl;
            cout << ans1 << " " << ans2 << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}