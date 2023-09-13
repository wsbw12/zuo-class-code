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
//规定1和A对应、2和B对应、3和C对应...26和Z对应
//那么一个数字字符串比如"111”就可以转化为:
//"AAA"、"KA"和"AK"
//给定一个只有数字字符组成的字符串str，返回有多少种转化结果

// str只含有数字字符0~9
// 返回多少种转化方案
int process(const string &str, int i);

int number(const string &str) {
    if (str.empty() || str.length() == 0) {
        return 0;
    }
    return process(str, 0);
}

// str[0..i-1]转化无需过问
// str[i.....]去转化，返回有多少种转化方法
int process(const string &str, int i) {
    if (i == str.length()) { // 如果i已经遍历到最后了说明此时前面的方法都是对的,返回一种方法
        return 1;
    }
    if (str[i] == '0') { // 如果只留下单独一个i位置的字符是0无法转化,说明之前的决定有问题,直接返回0
        return 0;
    }
    // str[i] != '0'
    // 可能性一，i单转
    int ways = process(str, i + 1);
    if (i + 1 < str.length() && (str[i] - '0') * 10 + str[i + 1] - '0' < 27) {
        ways += process(str, i + 2);
    }
    return ways;
}

// 从右往左的动态规划
// 就是上面方法的动态规划版本
// dp[i]表示：str[i...]有多少种转化方式
int process_dp(const string &str) {
    if (str.empty() || str.length() == 0) {
        return 0;
    }
    int n = str.length();
    vector<int> dp(n + 1);
    dp[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        if (str[i] != '0') {
            int ways = dp[i + 1];
            if (i + 1 < str.length() && (str[i] - '0') * 10 + str[i + 1] - '0' < 27) {
                ways += dp[i + 2];
            }
            dp[i] = ways;
        }
    }
    return dp[0];
}

int process_dp2(const string &str) {
    if (str.empty() || str.length() == 0) {
        return 0;
    }
    int n = str.length();
    vector<int> dp(n + 1);
    if (str[0] == '0') {
        return 0;
    }
    dp[0] = 1;
    for (int i = 1; i < n; i++) {
        if (str[i] == '0') {
            // 如果此时str[i]=='0'，那么他是一定要拉前一个字符(i-1的字符)一起拼的，
            // 那么就要求前一个字符，不能也是‘0’，否则拼不了。
            // 前一个字符不是‘0’就够了嘛？不够，还得要求拼完了要么是10，要么是20，如果更大的话，拼不了。
            // 这就够了嘛？还不够，你们拼完了，还得要求str[0...i-2]真的可以被分解！
            // 如果str[0...i-2]都不存在分解方案，那i和i-1拼成了也不行，因为之前的搞定不了。
            if (str[i - 1] == '0' || str[i - 1] > '2' || (i - 2 >= 0 && dp[i - 2] == 0)) {
                return 0;
            } else {
                dp[i] = i - 2 >= 0 ? dp[i - 2] : 1;
            }
        } else {
            dp[i] = dp[i - 1];
            if (str[i - 1] != '0' && (str[i - 1] - '0') * 10 + str[i] - '0' <= 26) {
                dp[i] += i - 2 >= 0 ? dp[i - 2] : 1;
            }
        }
    }
    return dp[n - 1];
}

string randomString(int len) {
    string str = "";
    for (int i = 0; i < len; i++) {
        str += (char) ((int) (rand() % 10) + '0');
    }
    return str;
}

int main() {
    int n = 30;
    int test_time = 1000000;
    cout << "测试开始" << endl;
    for (int i = 0; i < test_time; i++) {
        int len = (int) (rand() % n);
        string s = randomString(len);
        int ans1 = process_dp(s);
        int ans2 = process_dp2(s);
        if (ans1 != ans2) {
            cout << s << endl;
            cout << ans1 << " " << ans2 << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}