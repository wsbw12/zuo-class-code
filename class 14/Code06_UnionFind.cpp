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

// 并查集的实现
const int MAXN = 1000001;

vector<int> father(MAXN);
vector<int> size(MAXN);
vector<int> help(MAXN);

// 初始化并查集
void init(int n) {
    for (int i = 0; i <= n; i++) {
        father[i] = i;
        size[i] = 1;
    }
}

// 从i开始寻找集合代表点
int find(int i) {
    int hi = 0;
    while (i != father[i]) { // 将沿途找爹的过程中碰到的节点全都记录下来,准备扁平化处理
        help[hi++] = i;
        i = father[i];
    }
    for (hi--; hi >= 0; hi--) {
        father[help[hi]] = i;
    }
    return i;
}

// 查询x和y是不是一个集合
bool isSameSet(int x, int y) {
    return find(x) == find(y);
}

// x所在的集合，和y所在的集合，合并成一个集合
void union_set(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy) {
        if (size[fx] >= size[fy]) {
            size[fx] += size[fy];
            father[fy] = fx;
        } else {
            size[fy] += size[fx];
            father[fx] = fy;
        }
    }
}
