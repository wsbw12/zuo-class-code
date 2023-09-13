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

//n 皇后问题
int process1(int i, vector<int> &record, int n);

bool isValid(vector<int> &record, int i, int j);


int num1(int n) {
    if (n < 1) {
        return 0;
    }
    vector<int> record(n);
    return process1(0, record, n);
}

// 当前来到i行，一共是0~N-1行
// 在i行上放皇后，所有列都尝试
// 必须要保证跟之前所有的皇后不打架
// int[] record record[x] = y 之前的第x行的皇后，放在了y列上
// 返回：不关心i以上发生了什么，i.... 后续有多少合法的方法数
int process1(int i, vector<int> &record, int n) {
    if (i == n) {
        return 1;
    }
    int res = 0;
    // i行的皇后，放哪一列呢？j列，
    for (int j = 0; j < n; j++) {
        if (isValid(record, i, j)) {
            record[i] = j;
            res += process1(i + 1, record, n);
        }
    }
    return res;
}

bool isValid(vector<int> &record, int i, int j) {
    // 0..i-1
    for (int k = 0; k < i; k++) {
        if (j == record[k] || abs(record[k] - j) == abs(i - k)) {
            return false;
        }
    }
    return true;
}

int process2(int limit, int colLim, int leftDiaLim, int rightDiaLim);

// 请不要超过32皇后问题
int num2(int n) {
    if (n < 1 || n > 32) {
        return 0;
    }
    // 如果你是13皇后问题，limit 最右13个1，其他都是0
    int limit = n == 32 ? -1 : (1 << n) - 1;
    return process2(limit, 0, 0, 0);
}

// 7皇后问题
// limit : 0....0 1 1 1 1 1 1 1
// 之前皇后的列影响：colLim
// 之前皇后的左下对角线影响：leftDiaLim
// 之前皇后的右下对角线影响：rightDiaLim
int process2(int limit, int colLim, int leftDiaLim, int rightDiaLim) {
    if (colLim == limit) {
        return 1;
    }
    // pos中所有是1的位置，是你可以去尝试皇后的位置
    int pos = limit & (~(colLim | leftDiaLim | rightDiaLim));
    int mostRightOne = 0;
    int res = 0;
    while (pos != 0) {
        mostRightOne = pos & (~pos + 1);
        pos = pos - mostRightOne;
        res += process2(limit, colLim | mostRightOne, (leftDiaLim | mostRightOne) << 1,
                        (rightDiaLim | mostRightOne) >> 1);
    }
    return res;
}

int main() {
    int n = 9;
    cout << num1(n) << endl;
    cout << num2(n) << endl;
    return 0;
}