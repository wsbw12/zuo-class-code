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

using namespace std;

//派对的最大快乐值
// 员工信息的定义如下:
//class Employee {
//    public int happy; // 这名员工可以带来的快乐值
//    List<Employee> subordinates; // 这名员工有哪些直接下级
//}
//公司的每个员工都符合 Employee 类的描述。整个公司的人员结构可以看作是一棵标准的、 没有环的多叉树
//树的头节点是公司唯一的老板，除老板之外的每个员工都有唯一的直接上级
//叶节点是没有任何下属的基层员工(subordinates列表为空)，除基层员工外每个员工都有一个或多个直接下级
//这个公司现在要办party，你可以决定哪些员工来，哪些员工不来，规则：
//1.如果某个员工来了，那么这个员工的所有直接下级都不能来
//2.派对的整体快乐值是所有到场员工快乐值的累加
//3.你的目标是让派对的整体快乐值尽量大
//给定一棵多叉树的头节点boss，请返回派对的最大快乐值。
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}

};

class Employee{
public:
    int happy;
    vector<Employee*> sub;
    Employee(int h):happy(h){}

};
class returnData{
public:
    int yesMax;
    int noMax;
    returnData(int yes,int no):yesMax(yes),noMax(no)
    {}
};
returnData process(Employee* x) {
    int yesX = x -> happy;
    int noX = 0;
    if(x -> sub.size() == 0) {
        return returnData(yesX,noX);
    }
    else {
        for (auto next : x -> sub) {
            returnData subTree = process(next);
            yesX += subTree.noMax;
            noX += max(subTree.noMax,subTree.yesMax);
        }
    }
    return returnData(yesX,noX);
}
int getMaxHappy(Employee* boss) {
    returnData allTreeInfo =  process(boss);
    return max(allTreeInfo.yesMax,allTreeInfo.noMax);
}

// 当前来到的节点叫cur，
// up表示cur的上级是否来，
// 该函数含义：
// 如果up为true，表示在cur上级已经确定来，的情况下，cur整棵树能够提供最大的快乐值是多少？
// 如果up为false，表示在cur上级已经确定不来，的情况下，cur整棵树能够提供最大的快乐值是多少？
int process1(Employee *cur, bool up) {
    if (up) {// 如果cur的上级来的话，cur没得选，只能不来
        int ans = 0;
        for (auto next: cur->sub) {
            ans += process1(next, false);
        }
        return ans;
    } else {// 如果cur的上级不来的话，cur可以选，可以来也可以不来
        int p1 = cur->happy;
        int p2 = 0;
        for (auto next:cur->sub) {
            p1 += process1(next, true);
            p2 += process1(next, false);
        }
        return max(p1, p2);
    }
}

int maxHappy1(Employee *boss) {
    if (boss->sub.size() == 0 && boss->happy == 0) {
        return 0;
    }
    return process1(boss, false);
}


void generateNexts(Employee *e, int level, int maxLevel, int maxNexts, int maxHappy) {
    if (level > maxLevel) {
        return;
    }
    int nextSize = (int) (rand() % (maxNexts + 1));
    for (int i = 0; i < nextSize; i++) {
        Employee *next = new Employee((int) (rand() % (maxHappy + 1)));
        e->sub.push_back(next);
        generateNexts(next, level + 1, maxLevel, maxNexts, maxHappy);
    }
}

Employee *generateBoss(int maxLevel, int maxNexts, int maxHappy) {
    if (((int) rand() % 10) < 2) {
        return new Employee(0);
    }
    auto *boss = new Employee((int) (rand() % (maxHappy + 1)));
    generateNexts(boss, 1, maxLevel, maxNexts, maxHappy);
    return boss;
}

int main() {
    cout.precision(2);
    cout.setf(ios::fixed, ios::floatfield);
    int maxLevel = 4;
    int maxNexts = 7;
    int maxHappy = 100;
    int test_time = 100000;
    clock_t start, end;
    start = clock();
    cout << "测试开始" << endl;
    for (int i = 0; i < test_time; i++) {
        Employee *boss = generateBoss(maxLevel, maxNexts, maxHappy);
        if (maxHappy1(boss) != getMaxHappy(boss)) {
            cout << "测试失败" << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
    end = clock();   //结束时间
    cout << "测试的时间为: " << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ）
    return 0;
}