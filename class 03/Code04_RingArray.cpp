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

// 用数组实现循环队列
class MyQueue {
public:
    int arr[10];
    int end;
    int begin;
    int size;
    int limit;// 限制这个队列能放入的最大长度
    MyQueue(int limit) {
        int *arr = new int[limit];
        end = 0;
        begin = 0;
        size = 0;
        this->limit = limit;
    }

    void push(int value) {
        if (size == limit) {
            cout << "队列满了不能在加入元素了" << endl;
            return;
        }
        size++;
        arr[end] = value;
        end = nextIndex(end);
    }

    int pop() {
        if (size == 0) {
            cout << "队列空了,不能在取出元素了" << endl;
            return -1;
        }
        size--;
        int ans = arr[begin];
        begin = nextIndex(begin);
        return ans;
    }

    bool isEmpty() {
        return size == 0;
    }

    int nextIndex(int i) {
        return i < limit - 1 ? i + 1 : 0;
    }
};


void printArr(vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

//函数名：generateRandomVector
//函数功能描述：随机数组（样本）生成器
//函数参数： size    生成数组最大尺寸
//         value   数组每个元素的最大值
//返回值：  vector<int> 生成的数组

vector<int> generateRandomVector(int maxSize, int maxValue) {
    //time 函数返回从 1970 年 1 月 1 日午夜开始到现在逝去的秒数，因此每次运行程序时，它都将提供不同的种子值。
    srand((int) time(NULL));//为随机数生成器产生随机种子
    vector<int> result(rand() % (maxSize + 1));
    for (int i = 0; i < result.size(); i++) {
        result[i] = rand() % (maxValue + 1);
    }
    return result;
}

// 生成一个[0,range-1]范围内的随机数
int randomNumber(int range) {
    srand((unsigned) time(NULL));
    return (int) (rand() % (range + 1));
}

//大样本测试
//函数名：main
//函数功能描述：大样本测试
//函数参数： size    生成数组最大尺寸
//         value   数组每个元素的最大值
//返回值：  vector<int> 生成的数组

int main() {
    int test_time = 100000;//进行测试的次数
    int oneTestDataNum = 100;
    int range = 10;
    int size = 200;//生成数组的最大长度
    int value = 200;//生成数组的最大值
    srand((unsigned) time(NULL));
    cout << "测试开始" << endl;
    MyQueue q(5);
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);
    cout << q.pop() << endl;
    cout << q.pop() << endl;
    cout << q.pop() << endl;
    cout << q.pop() << endl;
    cout << q.pop() << endl;
    cout << q.pop() << endl;
    cout << "测试结束" << endl;
    return 0;
}