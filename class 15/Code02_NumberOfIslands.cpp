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

// leetcode 200. 岛屿数量 https://leetcode.cn/problems/number-of-islands
// 并查集的解法
class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
    int count;
public:
    UnionFind(vector<vector<char>> &grid) {
        count = 0;
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    parent.push_back(i * n + j);
                    ++count;
                } else {
                    parent.push_back(-1);
                }
                rank.push_back(0);
            }
        }
    }

    int find(int i) {
        if (parent[i] != i) {
            parent[i] = find(parent[i]);
        }
        return parent[i];
    }

    void unite(int x, int y) {
        int rootx = find(x);
        int rooty = find(y);
        if (rootx != rooty) {
            if (rank[rootx] < rank[rooty]) {
                swap(rootx, rooty);
            }
            parent[rooty] = rootx;
            if (rank[rootx] == rank[rooty]) {
                --count;
            }
        }
    }

    int getCount() const {
        return count;
    }
};

int numIslands1(vector<vector<char>> &grid) {
    int nr = grid.size();
    if (!nr) {
        return 0;
    }
    int nc = grid[0].size();
    UnionFind uf(grid);
    int num_islands = 0;
    for (int r = 0; r < nr; r++) {
        for (int c = 0; c < nc; c++) {
            if (grid[r][c] == '1') {
                grid[r][c] = '0';
                if (r - 1 >= 0 && grid[r - 1][c] == '1') {
                    uf.unite(r * nc + c, (r - 1) * nc + c);
                }
                if (r + 1 < nr && grid[r + 1][c] == '1') {
                    uf.unite(r * nc + c, (r + 1) * nc + c);
                }
                if (c - 1 >= 0 && grid[r][c - 1] == '1') {
                    uf.unite(r * nc + c - 1, r * nc + c - 1);
                }
                if (c + 1 < nc && grid[r][c + 1] == '1') {
                    uf.unite(r * nc + c + 1, r * nc + c + 1);
                }
            }
        }
    }
    return uf.getCount();
}

// dfs的方法
void dfs(vector<vector<char>> &grid, int x, int y) {
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    grid[x][y] = '0';
    for (int i = 0; i < 4; i++) {
        int new_x = x + dx[i], new_y = y + dy[i];
        if (new_x >= 0 && new_x < grid.size() && new_y >= 0 && new_y < grid[0].size() && grid[new_x][new_y] == '1') {
            dfs(grid, new_x, new_y);
        }
    }
}

int numIslands2(vector<vector<char>> &grid) {
    if (grid.empty() || grid[0].empty()) {
        return 0;
    }
    int res = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '1') {
                res++;
                dfs(grid, i, j);
            }
        }
    }
    return res;
}