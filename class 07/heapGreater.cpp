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
#include<assert.h>

using namespace std;

// 加强堆的实现
// 因为系统堆有一些不足，那就是堆不能做到修改堆中元素的值，并且只能删掉头部的值，不能够删除堆中其他的值，
// 因为这样会破坏堆的结构。如果想要不破坏堆的结构也很好办，只需要重新向上或者向下堆的结构即可，
// 但是这样又会有新的问题，那就是修改或删除元素在堆中的位置是未知的，如果想要获取该位置，则需要重新遍历整个堆，
// 时间复杂度为O（N），很显然时间复杂度过高，并不符合堆高效的特点。为了解决这一问题，则需要加强堆。

//加强堆和普通堆的区别在于多了一个哈希表unordered_map<T, int>indexMap，
// 其作用主要是用来记录每个元素在vector<T> heap的具体下标位置，
// 只要有了具体的下标位置，对元素进行修改或者删除就非常容易且高效了。
// 值得注意的是在向上或向下调整的时候，不光vector中的元素要交换，indexMap中对应的映射关系也要交换。


//但是这样还有一个问题：
// vector<T> heap中如果出现相同元素的话，就会导致unordered_map<T, int>indexMap中它们的下标无法映射，
// 因为哈希表的key不能重复，即使换成能够重复的unordered_multimap也不行，因为要获取其中一个key的下标时，
// 会与其他相同的key产生冲突。
// 要解决这个问题也很简单，那就是传入对象的指针，而不是传入具体的对象，因为对象的地址是不会冲突的，
// 另外传指针也会比传对象减少很多空间。

template<class T, class Compare> // 声明一个模版,其虚拟类型为T,(类似于int,float型)
class HeapGreater {
public:
    HeapGreater() {}

    //迭代器初始化
    template<class InputIterator>
    HeapGreater(InputIterator first, InputIterator last) {
        while (first != last) {
            push(*first);
            first++;
        }
    }

    ~HeapGreater() {}

    void push(const T &x) {
        heap.push_back(x);
        indexMap[x] = heapSize;
        AdjustUp(heapSize++);
    }

    void pop() {
        assert(!empty());
        T &node = heap[0];
        //交换首尾元素，然后删除
        swap(0, heapSize - 1);
        heapSize--;
        indexMap.erase(node);
        heap.pop_back();
        AdjustDown(0);
    }

    //将obj改为target
    void set(const T &obj, const T &target) {
        //获取obj在vector的位置
        //将obj改为target
        int index = indexMap[obj];
        heap[index] = target;
        //修改obj的位置，value不变，但是key要改变
        //采用的方式是删除后重新插入
        indexMap.erase(obj);
        indexMap[target] = index;
        //向上或向下调整
        AdjustUp(index);
        AdjustDown(index);
    }

    //删除指定的值
    void erase(const T &obj) {
        //获取尾部的值
        T &replace = heap[heapSize - 1];
        //获取obj在vector的位置
        int index = indexMap[obj];
        indexMap.erase(obj);

        --heapSize;
        //用尾部的值替换掉obj，然后调整
        if (obj != replace) {
            heap[index] = replace;
            indexMap[replace] = index;
            resign(replace);
        }
        heap.pop_back();
    }

    T top() {
        assert(!empty());
        return heap[0];
    }

    size_t size() {
        return heapSize;
    }

    bool empty() {
        return heap.empty();
    }

private:
    //需要封装交换函数，因为heap和indexMap的值都需要交换
    void swap(int i, int j) {
        T o1 = heap[i];
        T o2 = heap[j];
        heap[i] = o2;
        heap[j] = o1;
        indexMap[o2] = i;
        indexMap[o1] = j;

    }

    //向上调整算法，每push一个数都要调用向上调整算法，保证插入后是一个大堆
    void AdjustUp(int child) {
        Compare com;
        int parent = (child - 1) / 2;
        while (child > 0) {
            if (com(heap[parent], heap[child])) {
                swap(parent, child);
                child = parent;
                parent = (child - 1) / 2;
            } else {
                break;
            }
        }
    }

    //向下调整算法，每次调用pop都要进行向下调整算法重新构成大堆
    void AdjustDown(int parent) {
        Compare com;
        int child = parent * 2 + 1;
        while (child < heapSize) {
            if (child + 1 < heapSize && com(heap[child], heap[child + 1])) {
                child++;
            }
            if (com(heap[parent], heap[child])) {
                swap(parent, child);
                parent = child;
                child = parent * 2 + 1;
            } else {
                break;
            }
        }
    }

    //调整obj所在的位置
    void resign(const T &obj) {
        //obj位置的值发生改变，向上和向下调整
        //向上调整和向下调整只会发生一个
        AdjustUp(indexMap[obj]);
        AdjustDown(indexMap[obj]);
    }

    vector<T> heap;
    //反向索引表
    unordered_map<T, int> indexMap;
    int heapSize = 0;
};

void test_HeapGreater1() {
    HeapGreater<string, less<string>> heap;
    heap.push("abc");
    heap.push("ccc");
    heap.push("bbb");
    heap.push("dd");
    heap.push("eee");
    heap.push("yyy");
    heap.push("ppp");

    heap.erase("eee");
    heap.set("ccc", "new ccc");
    while (!heap.empty()) {
        cout << heap.top() << endl;
        heap.pop();
    }
}

struct cmp {
    bool operator()(string *&l, string *&r) {
        return *l < *r;
    }
};

void test_HeapGreater2() {
    string *s1 = new string("abc");
    string *s2 = new string("ccc");
    string *s3 = new string("bbb");
    string *s4 = new string("dd");
    string *s5 = new string("eee");
    string *s6 = new string("yyy");
    string *s7 = new string("ppp");
    string *s8 = new string("new ccc");

    HeapGreater<string *, cmp> heap;
    heap.push(s1);
    heap.push(s2);
    heap.push(s3);
    heap.push(s4);
    heap.push(s5);
    heap.push(s6);
    heap.push(s7);

    heap.erase(s5);
    heap.set(s2, s8);
    while (!heap.empty()) {
        cout << *heap.top() << endl;
        heap.pop();
    }
}

void test_HeapGreater3() {
    vector<string> v = {"abc", "ccc", "bbb", "dd", "eee", "yyy", "ppp"};
    HeapGreater<string, less<string>> heap(v.begin(), v.end());

    heap.erase("eee");
    heap.set("ccc", "new ccc");
    while (!heap.empty()) {

        cout << heap.top() << endl;
        heap.pop();
    }
}

int main() {
    test_HeapGreater1();
    cout << endl << endl;
    test_HeapGreater2();
    cout << endl << endl;
    test_HeapGreater3();
    return 0;
}