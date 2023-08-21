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

unordered_map<int, int> K_map;

// 生成一个[-range,range]范围的随机数
int randomNumber(int range) {
    srand((unsigned) time(NULL));
    return (int) (rand() % (range + 1)) - (int) (rand() % (range + 1));
}

int test(vector<int> &arr, int k) { // 暴力解法,用于测试
    unordered_map<int, int> kMap;
    for (int num:arr) {
        if (kMap.find(num) != kMap.end()) //找到了
        {
            kMap[num]++;
        } else { //没找到,将这个数插入进哈希表
            kMap.insert({num, 1});
        }
    }
    int ans = 0;
    for (auto num:arr) {
        if (kMap[num] == k) { // 表示这个数出现了k次,直接break返回
            ans = num;
            break;
        }
    }
    return ans;
}

void mapCreate(unordered_map<int, int> &k_map) {
    int num = 1;
    // 将每个2的次方数与它在二进制表示中1对应的位置存放起来
    // 比如 2的2次方为4 key=4,value=2
    for (int i = 0; i < 32; i++) {
        k_map.insert({num, i});
        num <<= 1;
    }
}

// 一个数组中有一种数出现K次，其他数都出现了M次   M>1 K<M 找到出现了K次的数 要求额外空间复杂度O(1)，时间复杂度O(N)
// 以下为第一种写法
int OnlyKTimes(vector<int> &arr, int k, int m) {
    if (K_map.size() == 0) {
        mapCreate(K_map);
    }
    vector<int> t(32);
    //t[0]表示数组中的数在二进制表示里面 0 位置上的1出现了几次
    for (int num:arr) {
        while (num) { // 这个while循环结束后会将数组中的每个数对应的二进制表示中 1 所在的位置++
            int rightOne = num & (-num); // 首先找到num中最右边的1是在第几位
            // 但是rightOne会返回一个2的k次方这样一个数,所以要用这个哈希表找到这个数中的1对应第几位
            // K_map[rightOne]返回的是这个数中的1对应第几位
            t[K_map[rightOne]]++;
            num ^= rightOne; // num^rightOne表示将最右边的1去掉,下一个循环找右边的第二个1
        }
    }
    int ans = 0;
    for (int i = 0; i < 32; i++) {
        if (t[i] % m != 0) { // 如果i位置上的1的总数之和不能被m整除,那么说明那个出现了k次的数在第i位上是1
            ans |= (1 << i); // ans=ans|(1<<i) 将ans里面的第i位变为1
        }
    }
    return ans;
}

// 第二种写法
int km(vector<int> &arr, int k, int m) {
    vector<int> help(32); //help[0]表示数组中的数在二进制表示里面 0 位置上的1出现了几次
    for (int num:arr) {
        for (int i = 0; i < 32; i++) {
            // 0110101>>1 = 0011010   0011010 & 1 = 0011010 & 0000001 = 0000000 = 0
            // 所以如果(num >> i) & 1= 1 表示num在第i位是1,否则表示在第i位是0
            help[i] += (num >> i) & 1; //将Num这个数不断进行右移判断这一位是不是1
        }
    }
    int ans = 0;
    for (int i = 0; i < 32; i++) {
        help[i] = help[i] % m;
        if (help[i] != 0) {
            ans |= 1 << i;
        }
    }
    return ans;
}

// 生成一个符合题意的随机数组
vector<int> randomArray(int maxKinds, int range, int k, int m) {
    srand((unsigned) time(NULL));
    int KTimeNum = randomNumber(range);// 这个生成的数就是我们要找的数,它出现k次
    int times = k;
    int numKinds = (int) (rand() % maxKinds) + 2; // 生成的numKinds表示数组中有多少类型的数
    // +2确保种类是大于等于2的
    vector<int> arr(times + (numKinds - 1) * m);
    int index = 0;
    for (; index < times; index++) {
        arr[index] = KTimeNum; // 让真名天子出现K次
    }
    numKinds--;//此时数组里面还需要放入的数的种类减减
    set<int> hash_set;
    hash_set.insert(KTimeNum);
    while (numKinds != 0) { //只要数组中数据的种类没变为0就要继续循环
        int curNum = 0;
        do {
            curNum = randomNumber(range); // 生成一个随机数
        } while (hash_set.contains(curNum)); // 如果这个随机数在之前出现过就继续循环生成,直到与之前生成的数不同
        hash_set.insert(curNum);
        numKinds--;
        for (int i = 0; i < m; i++) { // 将这个数插入m次
            arr[index++] = curNum;
        }
    }
    // 最后将arr里面的数据打乱
    for (int i = 0; i < arr.size(); i++) {
        int j = (int) (rand() % arr.size());
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    return arr;
}

void printArr(vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    srand((unsigned) time(NULL));
    int kinds = 5;
    int range = 30;
    int testTimes = 1000;
    int maxNum = 9;
    cout << "测试开始" << endl;
    for (int i = 0; i < testTimes; i++) {
        int a = (int) (rand() % maxNum) + 1;
        int b = (int) (rand() % maxNum) + 1;
        int k = min(a, b);
        int m = max(a, b);
        if (k == m) {
            m++;
        }
        vector<int> arr = randomArray(kinds, range, k, m);
        int ans1 = test(arr, k);
        int ans2 = OnlyKTimes(arr, k, m);
        int ans3 = km(arr, k, m);
        if (ans1 != ans2 || ans2 != ans3) {
            cout << ans1 << endl;
            cout << ans2 << endl;
            cout << ans3 << endl;
            cout << "出错了" << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}
