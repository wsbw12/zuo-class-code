#include <iostream>
#include <functional>
#include <unordered_map>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

template<typename T>
class HeapGreater {
private:
    typedef function<bool(T, T)> comparator; //function 可以存放函数对象
    vector<T> heap;
    unordered_map<T, int> indexMap; //反向索引表
    int heapSize;
    comparator comp;
public:
    HeapGreater(comparator c) {
        heapSize = 0;
        comp = c;
    }

    bool isEmpty() {
        return heapSize == 0;
    }

    int size() {
        return heapSize;
    }

    bool containsKey(T &obj) {
        //return indexMap.find(obj) != indexMap.end();
        return indexMap.count(obj);
    }

    T top() {
        return heap[0];
    }

    void heapInsert(int index) {
        while (comp(heap[index], heap[(index - 1) / 2])) {
            swap(index, (index - 1) / 2);
            index = (index - 1) / 2;
        }
    }

    void push(T &obj) {
        heap.push_back(obj);
        indexMap[obj] = heapSize;
        heapInsert(heapSize++);
    }

    T pop() {
        T ans = heap[0];
        swap(0, heapSize - 1);
        indexMap.erase(ans);
        heap.pop_back();
        --heapSize;
        heapify(0);
        return ans;
    }

    void remove(T &obj) {
        T replace = heap[heapSize - 1];
        int index = indexMap[obj];
        indexMap.erase(obj);
        heap.pop_back();
        --heapSize;
        if (obj != replace) { //两个对象比较大小，自定义类型必须重载该运算符
            heap[index] = replace;
            indexMap[replace] = index;
            resign(replace);
        }
    }

    void resign(T &obj) {
        heap[indexMap[obj]] = obj;
        heapInsert(indexMap[obj]);
        heapify(indexMap[obj]);
    }

    vector<T> getAllElements() {
        vector<T> ans;
        for (T c : heap) {
            ans.push_back(c);
        }
        return ans;
    }

    void heapify(int index) {
        int left = index * 2 + 1;
        while (left < heapSize) {
            int best = left + 1 < heapSize && comp(heap[left + 1], heap[left]) ? left + 1 : left;
            best = comp(heap[best], heap[index]) ? best : index;

            if (best == index)
                break;

            swap(best, index);
            index = best;
            left = index * 2 + 1;
        }
    }

    void swap(int i, int j) {
        T o1 = heap[i];
        T o2 = heap[j];
        heap[i] = o2;
        heap[j] = o1;
        indexMap[o2] = i;
        indexMap[o1] = j;
    }


    T get(int ind) {
        return heap[ind];
    }
};

int main() {
    HeapGreater<int> *heap;
    int a = 1, b = 4, c = 2, d = 7, e = 5;
    heap->push(a);
    heap->push(b);
    heap->push(c);
    heap->push(d);
    heap->push(e);
    while (!heap->isEmpty()) {
        cout << heap->pop() << endl;
    }
}