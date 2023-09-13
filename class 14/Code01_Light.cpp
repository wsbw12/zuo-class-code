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

//给定一个字符串str，只由'X'和'.'两种字符构成
//'X'表示墙，不能放灯，也不需要点亮；'.'表示居民点，可以放灯，需要点亮
//如果灯放在i位置，可以让i-1，i和i+1三个位置被点亮
//返回如果点亮str中所有需要点亮的位置，至少需要几盏灯
// 贪心解法
int minLight2(const string road) {
    int i = 0;
    int light = 0;
    while (i < road.size()) {
        if (road[i] == 'X') { // 如果i位置是墙直接考虑i+1位置
            i++;
        } else {
            light++;
            if (i + 1 == road.size()) { // 如果i+1到底了直接返回
                break;
            } else {
                if (road[i + 1] == 'X') { // 如果i+1位置是墙那么在i位置放之后去i+2位置考虑
                    i = i + 2;
                } else {
                    i = i + 3;
                }
            }
        }
    }
    return light;
}

// 暴力解法
// str[index....]位置，自由选择放灯还是不放灯
// str[0..index-1]位置呢？已经做完决定了，那些放了灯的位置，存在lights里
// 要求选出能照亮所有.的方案，并且在这些有效的方案中，返回最少需要几个灯
int process(string str, int index, unordered_set<int> &lights) {
    if (index == str.length()) {
        for (int i = 0; i < str.length(); i++) {
            if (str[i] != 'X') {
                if (!lights.count(i - 1) && !lights.count(i) && !lights.count(i + 1)) {
                    return INT_MAX;
                }
            }
        }
        return lights.size();
    } else {
        int no = process(str, index + 1, lights);
        int yes = INT_MAX;
        if (str[index] == '.') {
            lights.insert(index);
            yes = process(str, index + 1, lights);
            lights.erase(index);
        }
        return min(no, yes);
    }
}

int minLight1(const string road) {
    if (road.empty() || road.size() == 0) {
        return 0;
    }
    unordered_set<int> lights;
    return process(road, 0, lights);
}

int minLight3(const string road) {
    int cur = 0;
    int light = 0;
    for (char c:road) {
        if (c == 'X') {
            light += (cur + 2) / 3;
            cur = 0;
        } else {
            cur++;
        }
    }
    light += (cur + 2) / 3;
    return light;
}

string randomString(int len) {
    vector<char> res((int) (rand() % len) + 1);
    for (int i = 0; i < res.size(); i++) {
        res[i] = ((rand() % 10) < 5) ? 'X' : '.';
    }
    string ans = "";
    for (int i = 0; i < res.size(); i++) {
        ans += res[i];
    }
    return ans;
}


int main() {
    int len = 20;
    int times = 100000;
    clock_t start, end;
    start = clock();
    cout << "测试开始" << endl;
    for (int i = 0; i < times; i++) {
        string test = randomString(len);
        int ans1 = minLight1(test);
        int ans2 = minLight2(test);
        int ans3 = minLight3(test);
        if (ans1 != ans2 || ans1 != ans3) {
            cout << "测试失败" << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
    end = clock();   //结束时间
    cout << "测试的时间为: " << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ）
    return 0;
}