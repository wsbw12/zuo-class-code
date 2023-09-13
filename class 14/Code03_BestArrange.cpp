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
//一些项目要占用一个会议室宣讲，会议室不能同时容纳两个项目的宣讲，给你每一个项目开始的时间和结束的时间
//你来安排宣讲的日程，要求会议室进行的宣讲的场次最多，返回最多的宣讲场次

struct Program {
    int start;
    int end;

    Program() : start(0), end(0) {}

    Program(int a, int b) : start(a), end(b) {}
};

// 贪心
bool MyCom(const Program &p1, const Program &p2) {
    return (p1.end < p2.end);
}

int bestArrange(vector<Program> &programs) {
    sort(programs.begin(), programs.end(), MyCom);
    int timeLine = 0;// 当前来到的时间点
    int result = 0;
    // 依次遍历每一个会议，结束时间早的会议先遍历
    for (int i = 0; i < programs.size(); i++) {
        if (timeLine <= programs[i].start) {
            result++;
            timeLine = programs[i].end;
        }
    }
    return result;
}


// 暴力解法

vector<Program> copyButExcept(vector<Program> &programs, int i) {
    vector<Program> ans(programs.size() - 1);
    int index = 0;
    for (int k = 0; k < programs.size(); k++) {
        if (k != i) {
            ans[index++] = programs[k];
        }
    }
    return ans;
}


// 还剩下的会议都放在programs里
// done之前已经安排了多少会议的数量
// timeLine目前来到的时间点是什么

// 目前来到timeLine的时间点，已经安排了done多的会议，剩下的会议programs可以自由安排
// 返回能安排的最多会议数量
int process(vector<Program> &programs, int done, int timeLine) {
    if (programs.size() == 0) {
        return done;
    }
    // 还剩下的会议
    int max_num = done;
    // 当前安排的会议是什么,每一个都进行枚举
    for (int i = 0; i < programs.size(); i++) {
        if (programs[i].start >= timeLine) {
            vector<Program> next = copyButExcept(programs, i);
            max_num = max(max_num, process(next, done + 1, programs[i].end));
        }
    }
    return max_num;
}

int bestArrange1(vector<Program> &programs) {
    if (programs.empty() || programs.size() == 0) {
        return 0;
    }
    return process(programs, 0, 0);
}


vector<Program> generatePrograms(int programSize, int timeMax) {
    vector<Program> ans((int) (rand() % (programSize + 1)));
    for (int i = 0; i < ans.size(); i++) {
        int r1 = (int) (rand() % (timeMax + 1));
        int r2 = (int) (rand() % (timeMax + 1));
        if (r1 == r2) {
            ans[i] = {r1, r1 + 1};
        } else {
            ans[1] = {min(r1, r2), max(r1, r2)};
        }
    }
    return ans;
}


int main() {
    int programSize = 12;
    int timeMax = 20;
    int times = 10000;
    clock_t start, end;
    start = clock();
    cout << "测试开始" << endl;
    for (int i = 0; i < times; i++) {
        vector<Program> programs = generatePrograms(programSize, timeMax);
        if (bestArrange(programs) != bestArrange1(programs)) {
            cout << "测试错误" << endl;
        }
    }
    cout << "测试结束" << endl;
    end = clock();   //结束时间
    cout << "测试的时间为: " << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ）
    return 0;
}