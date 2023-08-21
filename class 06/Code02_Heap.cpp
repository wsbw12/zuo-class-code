#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>
#include <cmath>

using namespace std;

// 堆结构
class MyMaxHeap {
public:
    int heap[10];
    int limit;
    int heapSize;

    MyMaxHeap(int limit) {
        int *heap = new int[limit];
        this->limit = limit;
        heapSize = 0;
    }

    bool isEmpty() {
        return heapSize == 0;
    }

    bool isFull() {
        return heapSize == limit;
    }

    void push(int value) {
        if (heapSize == limit) {
            cout << "此时堆已经满了" << endl;
            return;
        }
        heap[heapSize] = value;
        heapInsert(heap, heapSize++);
    }

    // 用户此时让你返回最大值,并且在大根堆中,把最大值删掉,剩下的数依然保持大根堆结构
    int pop() {
        int ans = heap[0];
        swap(heap, 0, --heapSize);
        heapify(heap, 0, heapSize);
        return ans;
    }

    // 新加进来的数,现在在Index位置,请依次向上移动,移动到 0 位置,或者不能与自己父节点交换了,停下
    void heapInsert(int arr[], int index) {
        while (arr[index] > arr[(index - 1) / 2]) {
            swap(arr, index, (index - 1) / 2);
            index = (index - 1) / 2;
        }
    }

    // 从index的位置不断下沉
    void heapify(int arr[], int index, int heapSize) {
        int left = index * 2 + 1;
        while (left < heapSize) { // 如果左孩子没越界,即此时存在左孩子的情况
            // 如果右孩子存在,并且右孩子大于左孩子的情况下,将更大的数的下标给largest
            int largest = left + 1 < heapSize && arr[left + 1] > arr[left] ? left + 1 : left;
            // 再将左右孩子节点中较大的那个与父节点进行比较,将较大的给largest
            largest = arr[largest] > arr[index] ? largest : index;
            if (largest == index) { // 如果较大的节点就是父节点,那么不需要调整,直接break
                break;
            }
            swap(arr, largest, index);
            index = largest;
            left = index * 2 + 1;
        }
    }

    void swap(int arr[], int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
};

class RightMaxHeap {
public:
    int arr[10];
    int limit;
    int size;

    RightMaxHeap(int limit) {
        int *arr = new int[limit];
        this->limit = limit;
        size = 0;
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == limit;
    }

    void push(int value) {
        if (size == limit) {
            cout << "此时堆已经满了" << endl;
            return;
        }
        arr[size++] = value;
    }

    int pop() {
        int maxIndex = 0;
        for (int i = 0; i < size; i++) {
            if (arr[i] > arr[maxIndex]) {
                maxIndex = i;
            }
        }
        int ans = arr[maxIndex];
        arr[maxIndex] = arr[--size];
        return ans;
    }
};

struct comp {
    bool operator()(const int a, const int b) {
        return a > b;
    }
};

int main() {
    priority_queue<int, vector<int>, comp> min_heap; // 定义一个小根堆
    min_heap.push(5);
    min_heap.push(5);
    min_heap.push(5);
    min_heap.push(3);
    cout << min_heap.top() << endl;
    min_heap.push(7);
    min_heap.push(0);
    min_heap.push(7);
    min_heap.push(0);
    min_heap.push(7);
    min_heap.push(0);
    cout << min_heap.top() << endl;
    while (!min_heap.empty()) {
        cout << min_heap.top() << endl;
        min_heap.pop();
    }
    cout << "====================" << endl;
    RightMaxHeap test(10);
    test.push(2);
    test.push(1);
    test.push(5);
    test.push(3);
    test.push(8);
    while (!test.isEmpty()) {
        cout << test.pop() << endl;
    }
    cout << "====================" << endl;
    int value = 1000;
    int limit = 100;
    int test_time = 1000000;
    int range = 10;
    srand((int) time(NULL));
    cout << "测试开始" << endl;
    for (int i = 0; i < 10; i++) {
        int curLimit = (int) (rand() % limit) + 1;
        MyMaxHeap my_heap(curLimit);
        RightMaxHeap max_heap(curLimit);
        int curOpTimes = (int) (rand() % limit);
        for (int j = 0; j < curOpTimes; j++) {
            if (my_heap.isEmpty() != max_heap.isEmpty()) {
                cout << "测试错误" << endl;
            }
            if (my_heap.isFull() != max_heap.isFull()) {
                cout << "测试错误" << endl;
            }
            if (my_heap.isEmpty()) {
                int curValue = (int) (rand() % value);
                my_heap.push(curValue);
                max_heap.push(curValue);
            } else if (my_heap.isFull()) {
                if (my_heap.pop() != max_heap.pop()) {
                    cout << "测试错误" << endl;
                }
            } else {
                if (((int) (rand() % range)) < 5) {
                    int curValue = (int) (rand() % value);
                    my_heap.push(curValue);
                    max_heap.push(curValue);
                } else {
                    if (my_heap.pop() != max_heap.pop()) {
                        cout << "测试错误" << endl;
                    }
                }
            }
        }
    }
    cout << "测试结束" << endl;
    return 0;
}