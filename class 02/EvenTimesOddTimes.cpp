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

// 一个数组中有一种数出现了奇数次，其他数都出现了偶数次，怎么找到并打印这种数
void printOddTimesNum(vector<int> &arr) {
    int eor = 0;
    for (int i = 0; i < arr.size(); i++) {
        eor ^= arr[i];
    }
    cout << eor << endl;
}

// 如何将一个整数二进制中最右侧的1提取出来   直接将 a&(-a)即可 也即 a&(~a+1)
// 一个数组中有两种数出现了奇数次，其他数都出现了偶数次，怎么找到并打印这两种数
void printOddTimesNum2(vector<int> &arr) {
    // 假设数组中只有a,b两种数出现了奇数次,其他的都出现了偶数次
    int eor = 0;
    for (int i = 0; i < arr.size(); i++) { // 将所有数都进行异或一遍,最终得到的结果一定与a,b两个数异或结果相同
        // 并且a^b的结果不是0,因为a不等于b
        eor ^= arr[i];
    }
    // 将eor最右侧的1提取出来
    // 假如eor = 00110010110110100
    // 此时rightOne = 00000000000000100
    int rightOne = eor & (-eor);
    // 此时假设eor里面最右侧的1为第i位,此时数组中的数可以分为两种,一种为二进制表示中第i位为1,一种为二进制表示中第i位为0
    // 并且a,b分别位于这两位之中,假设a位于第一类,b位于第二类,其他出现偶数次的数也是分别位于这两类之中
    int onlyOne = 0; // 用onlyOne这个变量去异或所有位于第一类之中的数,最后得到的结果一定是a
    for (int i = 0; i < arr.size(); i++) {
        // rightOne = 00000000000000100
        if ((arr[i] & rightOne) != 0) { //(arr[i] & rightOne) != 0 就能选出数组中元素二进制表示中第i位为1的数
            onlyOne ^= arr[i];
        }
    }
    cout << onlyOne << ", " << (eor ^ onlyOne) << endl;
}

int main() {
    vector<int> nums1 = {1, 2, 3, 7, 2, 3, 3, 1, 1, 1, 7};
    vector<int> nums2 = {1, 2, 3, 7, 2, 3, 3, 1, 1, 1, 7, 5, 5, 5};
    printOddTimesNum(nums1);
    printOddTimesNum2(nums2);
    return 0;
}
