#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>
#include <set>

using namespace std;

// 不用其他的变量,如何交换两个数

int main() {
    int a = 6;
    int b = 34;
    cout << "a= " << a << " " << "b= " << b << endl;
    // 使用异或的前提是两个数不能位于内存的同一个位置
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    cout << "a= " << a << " " << "b= " << b << endl;
    return 0;
}
