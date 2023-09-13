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

// leetcode 305. 岛屿数量2： https://leetcode.cn/problems/number-of-islands-ii/
// 并查集的解法
class UnionFind {
private:
    vector<int> parent;
    vector<int> size;
    vector<int> help;
    int row;
    int col;
    int count;
public:
    UnionFind(vector<vector<int>> &grid) {
        count = 0;
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    parent.push_back(i * n + j);
                    ++count;
                } else {
                    parent.push_back(-1);
                }
                size.push_back(0);
            }
        }
    }

    int find(int i) {
        if (parent[i] != i) {
            parent[i] = find(parent[i]);
        }
        return parent[i];
    }

    void unite(int r1, int c1, int r2, int c2) {
        if (r1 < 0 || r1 == row || r2 < 0 || r2 == row || c1 < 0 || c1 == col || c2 < 0 || c2 == col) {
            return;
        }
        int i1 = r1 * col + c1;
        int i2 = r2 * col + c2;
        if (size[i1] == 0 || size[i2] == 0) {
            return;
        }
        int f1 = find(i1);
        int f2 = find(i2);
        if (f1 != f2) {
            if (size[f1] >= size[f2]) {
                size[f1] += size[f2];
                parent[f2] = f1;
            }
            if (size[f1] <= size[f2]) {
                size[f2] += size[f1];
                parent[f1] = f2;
            }
            count--;
        }
    }

    int connect(int r, int c) {
        int index = r * col + c;
        if (size[index] == 0) {
            parent[index] = index;
            size[index] = 1;
            count++;
            unite(r - 1, c, r, c);
            unite(r + 1, c, r, c);
            unite(r, c - 1, r, c);
            unite(r, c + 1, r, c);
        }
        return count;
    }

    int getCount() const {
        return count;
    }
};

vector<int> numIslands1(vector<vector<int>> &grid, int m, int n) {
    UnionFind *uf = new UnionFind(grid);
    vector<int> ans;
    for (auto position:grid) {
        ans.push_back(uf->connect(position[0], position[1]));
    }
    return ans;
}

// dfs的解法
class Solution {
public:
    //主要用于将给定的岛屿使用新的数字进行标识
    void dfs(vector<vector<int>> &mp, const int &cur_index, int old_index, pair<int, int> cur_pos) {
        if (mp[cur_pos.first][cur_pos.second] != old_index) {//说明当前位置不是要修改的岛屿的位置
            return;
        }
        mp[cur_pos.first][cur_pos.second] = cur_index;//将岛屿的标识修改为新的数字
        //对相邻的位置进行判断
        if (cur_pos.first > 0) {
            dfs(mp, cur_index, old_index, {cur_pos.first - 1, cur_pos.second});
        }
        if (cur_pos.first < mp.size() - 1) {
            dfs(mp, cur_index, old_index, {cur_pos.first + 1, cur_pos.second});
        }
        if (cur_pos.second > 0) {
            dfs(mp, cur_index, old_index, {cur_pos.first, cur_pos.second - 1});
        }
        if (cur_pos.second < mp[0].size() - 1) {
            dfs(mp, cur_index, old_index, {cur_pos.first, cur_pos.second + 1});
        }
    }

    vector<int> numIslands2(int m, int n, vector<vector<int>> &positions) {
        vector<vector<int>> mp(m, vector<int>(n, 0));//整个水域
        vector<int> res(positions.size(), 0);//统计每次插入后造成的岛屿的数量
        //插入
        for (int i = 0; i < positions.size(); ++i) {
            unordered_map<int, pair<int, int>> st;//统计当前插入位置处可能的相邻的岛屿
            //当前插入的位置
            int row = positions[i][0];
            int col = positions[i][1];
            if (mp[row][col] != 0) {//避免重复的插入
                res[i] = res[i - 1];
                continue;
            }
            //判断各个相邻的位置是否是岛屿
            if (row > 0 && mp[row - 1][col] != 0) {
                st[mp[row - 1][col]] = {row - 1, col};
            }
            if (row < m - 1 && mp[row + 1][col] != 0) {
                st[mp[row + 1][col]] = {row + 1, col};
            }
            if (col > 0 && mp[row][col - 1] != 0) {
                st[mp[row][col - 1]] = {row, col - 1};
            }
            if (col < n - 1 && mp[row][col + 1] != 0) {
                st[mp[row][col + 1]] = {row, col + 1};
            }
            //若当前位置没有相邻的岛屿
            if (st.empty()) {
                mp[row][col] = i + 1;//标识当前岛屿
                //处理特殊的情形
                if (i == 0) {
                    res[i] = 1;
                } else {
                    res[i] = res[i - 1] + 1;//新增一个岛屿，既在之前岛屿数量基础上，新增一个岛屿
                }
            } else if (st.size() == 1) {//若新插入的位置只和一个岛屿相邻
                //将当前位置和相邻的岛屿使用相同的数字进行标识
                mp[row][col] = st.begin()->first;
                res[i] = res[i - 1];//说明没有造成新增岛屿，故和之前岛屿数量相同
            } else {//相邻的岛屿的数量大于一个
                //在相邻的岛屿中选择一个，使用其数字作为标识
                int cur_index = st.begin()->first;
                mp[row][col] = cur_index;//使用岛屿的数字标识当前位置
                res[i] = res[i - 1] - st.size() + 1;//由于合并了一些岛屿，故需要根据相邻的岛屿的数量进行标识
                for (auto &it:st) {//将其他几个岛屿的表示数字也修改为相同的标识数字，来标识是同一个新的岛屿
                    if (it.first != cur_index) {
                        dfs(mp, cur_index, mp[it.second.first][it.second.second], it.second);
                    }
                }
            }
        }
        return res;
    }
};