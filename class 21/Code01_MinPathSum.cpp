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
//// 给定一个二维数组matrix，一个人必须从左上角出发，最后到达右下角
//沿途只可以向下或者向右走，沿途的数字都累加就是距离累加和
//返回最小距离累加和

int minPathSum1(vector<vector<int>> &matrix) {
    if (matrix.empty() || matrix.size() == 0 || matrix[0].empty() || matrix[0].size() == 0) {
        return 0;
    }
    int row = matrix.size();
    int col = matrix[0].size();
    vector<vector<int>> dp(row, vector<int>(col));
    dp[0][0] = matrix[0][0];
    for (int i = 1; i < row; i++) {
        dp[i][0] = dp[i - 1][0] + matrix[i][0];
    }
    for (int j = 1; j < col; j++) {
        dp[0][j] = dp[0][j - 1] + matrix[0][j];
    }
    for (int i = 1; i < row; i++) {
        for (int j = 1; j < col; j++) {
            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + matrix[i][j];
        }
    }
    return dp[row - 1][col - 1];
}

// 空间压缩
int minPathSum2(vector<vector<int>> &matrix) {
    if (matrix.empty() || matrix.size() == 0 || matrix[0].empty() || matrix[0].size() == 0) {
        return 0;
    }
    int row = matrix.size();
    int col = matrix[0].size();
    vector<int> dp(col);
    dp[0] = matrix[0][0];
    for (int j = 1; j < col; j++) {
        dp[j] = dp[j - 1] + matrix[0][j];
    }
    for (int i = 1; i < row; i++) {
        dp[0] += matrix[i][0];
        for (int j = 1; j < col; j++) {
            dp[j] = min(dp[j - 1], dp[j]) + matrix[i][j];
        }
    }
    return dp[col - 1];
}

vector<vector<int>> generateRandomMatrix(int rowSize, int colSize) {
    vector<vector<int>> temp;
    if (rowSize < 0 || colSize < 0) {
        return temp;
    }
    vector<vector<int>> result(rowSize, vector<int>(colSize));

   srand((unsigned) time(NULL));

​    for (int i = 0; i < result.size(); i++) {
​        for (int j = 0; j < result[0].size(); j++) {
​            result[i][j] = (int) (rand() % 100);
​        }
​    }
​    return result;
}

void printMatrix(vector<vector<int>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int rowSize = 10;
    int colSize = 10;
    vector<vector<int>> test = generateRandomMatrix(rowSize, colSize);
    cout << minPathSum1(test) << endl;
    cout << minPathSum2(test) << endl;
    return 0;
}