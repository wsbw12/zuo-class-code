/*************************************************************************
	> File Name: 001.加强堆的应用.cpp
	> Author:
	> Mail:
	> Created Time: Thu 19 May 2022 06:58:19 PM CST
 ************************************************************************/

#include <iostream>
#include <functional>
#include <unordered_map>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

/*
 * 加强堆
 */
template<typename T>
class HeapGreater {
private:
    typedef function<bool(T, T)> comparator; //function存储函数对象
    vector<T> heap;
    unordered_map<T, int> indexMap;
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

        int ind = indexMap[obj];
        heap[ind] = obj;

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

class Customer {
public:
    int id;
    int buyCnt;
    int enterTime;
public:
    Customer() {}

    Customer(int i, int c, int e) : id(i), buyCnt(c), enterTime(e) {}

    bool operator==(const Customer &c) const {
        return id == c.id;
    }

    bool operator!=(const Customer &c) const {
        return id != c.id;
    }
};

/*
 * Customer的哈希函数
 */
namespace std {
    template<>
    class hash<Customer> {
    public:
        size_t operator()(const Customer &c) const {
            int hashCode = hash<int>()(c.id);
            return hashCode;
        }
    };
};

/*
 * 候选区比较方式：
 *      如果购买数量不等，按照数量从大到小排序；
 *      若购买数量相等，按照进入时间从早到晚排序
 */
struct CandidateCompare {
    bool operator()(const Customer &c1, const Customer &c2) const {
        return c1.buyCnt != c2.buyCnt ? (c1.buyCnt > c2.buyCnt) : (c1.enterTime < c2.enterTime);
    }
};


/*
 * 得奖区比较方式：
 *      若购买数量不等，按照数量从小到大排序；
 *      若购买数量相等，按照进入时间从早到晚排序
 */
struct WinnerCompare {
    bool operator()(const Customer &c1, const Customer &c2) const {
        return c1.buyCnt != c2.buyCnt ? (c1.buyCnt < c2.buyCnt) : (c1.enterTime < c2.enterTime);
    }
};


class WhosTheWinners {
private:
    unordered_map<int, Customer> customers;
    HeapGreater<Customer> *candidateHeap;
    HeapGreater<Customer> *winnerHeap;
    int winnerLimit;
public:
    WhosTheWinners(int limit) : winnerLimit(limit) {
        winnerHeap = new HeapGreater<Customer>(WinnerCompare());
        candidateHeap = new HeapGreater<Customer>(CandidateCompare());
    }

    vector<int> getWinners() {
        vector<Customer> winners = winnerHeap->getAllElements();
        vector<int> ans;
        for (Customer c : winners) {
            ans.push_back(c.id);
        }
        return ans;
    }


    void operate(int time, int id, bool buyOrRefund) {
        if (!customers.count(id) && !buyOrRefund)
            return;

        if (!customers.count(id)) {
            customers[id] = Customer(id, 0, 0);
        }

        Customer &c = customers[id]; //注意这个地方，一定要用&，不然后续buyCnt修改的值不会被修改到customers中
        //cout << "c from customers : c.id = " << c.id << ", c.buyCnt = " << c.buyCnt << ", c.enterTime = " << c.enterTime << endl;
        if (buyOrRefund) {
            c.buyCnt++;
        } else {
            c.buyCnt--;
        }

        if (c.buyCnt == 0) {
            customers.erase(id);
        }

        //注意使用自定义类型作为哈希表的key时，一定要做的两点：（1）实现哈希函数，以获得自定类型的哈希值 （2）自定义类中实现operator==，以判断两个对象是否相等
        if (!candidateHeap->containsKey(c) && !winnerHeap->containsKey(c)) {
            if (winnerHeap->size() < winnerLimit) {
                c.enterTime = time;
                winnerHeap->push(c);
            } else {
                c.enterTime = time;
                candidateHeap->push(c);
            }
        } else if (candidateHeap->containsKey(c)) {
            if (c.buyCnt == 0) {
                candidateHeap->remove(c);
            } else {
                candidateHeap->resign(c);
            }
        } else {
            if (c.buyCnt == 0) {
                winnerHeap->remove(c);
            } else {
                winnerHeap->resign(c);
            }
        }
        winnerMove(time, customers);

        /*cout << "after : c from customers : c.id = " << c.id << ", c.buyCnt = " << c.buyCnt << ", c.enterTime = " << c.enterTime << endl;
        //打印候选区的用户信息
        cout << ">>Candidate Info:" << endl;
        cout << "candidateHeap->size() = " << candidateHeap->size() << endl;
        cout << "candidateHeap elements : " << endl;
        for (int i = 0; i < candidateHeap->size(); i++) {
            cout << "(" << candidateHeap->get(i).id << ", " << candidateHeap->get(i).buyCnt << ", " << candidateHeap->get(i).enterTime << ")" << endl;
        }
        cout << "<<==============" << endl;


        cout << ">>Winner Info : " << endl;
        cout << "winnerHeap->size() = " << winnerHeap->size() << endl;
        cout << "winnerHeap elements : " << endl;
        for (int i = 0; i < winnerHeap->size(); i++) {
            cout << "(" << winnerHeap->get(i).id << ", " << winnerHeap->get(i).buyCnt << ", " << winnerHeap->get(i).enterTime << ")" << endl;
        }
        cout << "<<<<!!!!!!!!!!!!!!!" << endl;*/

    }

    void winnerMove(int time, unordered_map<int, Customer> &customers) {
        if (candidateHeap->isEmpty())
            return;
        if (winnerHeap->size() < winnerLimit) {
            Customer p = candidateHeap->pop();
            p.enterTime = time;
            winnerHeap->push(p);
            customers[p.id].enterTime = time;
        } else {
            if (candidateHeap->top().buyCnt > winnerHeap->top().buyCnt) {
                Customer oldWinner = winnerHeap->pop();
                Customer newWinner = candidateHeap->pop();
                oldWinner.enterTime = time;
                newWinner.enterTime = time;
                winnerHeap->push(newWinner);
                candidateHeap->push(oldWinner);


                //切记要更新customers中用户的id对应的时间
                customers[oldWinner.id].enterTime = time;
                customers[newWinner.id].enterTime = time;
            }
        }
    }

};

void print(vector<int> &arr);

vector<vector<int> > topK(vector<int> &arr, vector<bool> &op, int k) {
    vector<vector<int> > ans;
    WhosTheWinners *whosTheWinners = new WhosTheWinners(k);
    for (int i = 0; i < arr.size(); i++) {
        //cout << "=================" << endl;
        //cout << "topK : " << "arr[" << i << "] = " << arr[i] << ", op[" << i << "] = "<< op[i] <<endl;
        whosTheWinners->operate(i, arr[i], op[i]);
        ans.push_back(whosTheWinners->getWinners());

        //print(ans[i]);
    }
    return ans;
}


//For test
void compareAndMove(unordered_map<int, Customer> &customers, vector<Customer> &cands, vector<Customer> &winners, int k,
                    int time) {
    if (cands.empty()) return;

    if (winners.size() < k) {
        Customer c = cands[0];
        c.enterTime = time;
        winners.push_back(c);
        cands.erase(cands.begin());
        customers[c.id].enterTime = time;
    } else {
        if (cands[0].buyCnt > winners[0].buyCnt) {
            Customer oldWinner = winners[0];
            Customer newWinner = cands[0];
            winners.erase(winners.begin());
            cands.erase(cands.begin());
            newWinner.enterTime = time;
            oldWinner.enterTime = time;
            winners.push_back(newWinner);
            cands.push_back(oldWinner);

            customers[oldWinner.id].enterTime = time;
            customers[newWinner.id].enterTime = time;
        }
    }
}

void cleanZeroBuy(int id, vector<Customer> &arr) {
    vector<Customer> noZero;
    for (Customer &c : arr) {
        if (c.id == id) {
            c.buyCnt = 0;
        }
        if (c.buyCnt != 0) {
            noZero.push_back(c);
        }
    }

    arr.clear();
    for (Customer c : noZero) {
        arr.push_back(c);
    }
}

void resignBuy(vector<Customer> &arr, int id, int buyCnt) {
    for (Customer &c : arr) {
        if (c.id == id) {
            c.buyCnt = buyCnt;
        }
    }
}

vector<int> getCurAns(vector<Customer> &winners) {
    vector<int> ans;
    for (Customer &c : winners) {
        ans.push_back(c.id);
    }
    return ans;
}


vector<vector<int> > compare(vector<int> &arr, vector<bool> op, int k) {
    unordered_map<int, Customer> customers;
    vector<Customer> cands;
    vector<Customer> winners;
    vector<vector<int> > ans;
    for (int i = 0; i < arr.size(); i++) {
        int id = arr[i];
        //cout << "=======================" << endl;
        //cout << "compare : id = " << id << ", op[" << i << "] = " << op[i] << endl;
        bool buyOrRefund = op[i];
        if (!buyOrRefund && !customers.count(id)) {
            ans.push_back(getCurAns(winners));
            continue;
        }

        if (!customers.count(id)) {
            customers[id] = Customer(id, 0, 0);
        }

        Customer &c = customers[id];

        if (buyOrRefund) {
            c.buyCnt++;
        } else {
            c.buyCnt--;
        }

        if (c.buyCnt == 0) {
            customers.erase(id);
        }


        if (!count(cands.begin(), cands.end(), c) && !count(winners.begin(), winners.end(), c)) {
            if (winners.size() < k) {
                c.enterTime = i;
                //Tips：更改c的相关属性时，并没有更改到winners中的对象，winners中保存的是c的备份
                winners.push_back(c);
            } else {
                c.enterTime = i;
                cands.push_back(c);
            }
        } else if (count(cands.begin(), cands.end(), c)) {
            if (c.buyCnt == 0) {
                cleanZeroBuy(c.id, cands);
            } else {
                resignBuy(cands, c.id, c.buyCnt);
            }
        } else {
            if (c.buyCnt == 0) {
                cleanZeroBuy(c.id, winners);
            } else {
                resignBuy(winners, c.id, c.buyCnt);
            }
        }

        //候选区buyCnt 从大到小
        //得奖区buyCnt 从小到大
        sort(cands.begin(), cands.end(), CandidateCompare());
        sort(winners.begin(), winners.end(), WinnerCompare());

        compareAndMove(customers, cands, winners, k, i);

        sort(cands.begin(), cands.end(), CandidateCompare());
        sort(winners.begin(), winners.end(), WinnerCompare());

        //打印候选区和得奖区的用户信息
        /*cout << "!!!!!!Candidate info:" << endl;
        for (Customer c : cands) {
            cout << "(" << c.id << ", " << c.buyCnt << ", " << c.enterTime <<  ")" << endl;
        }

        cout << "!!!!!!!Winner info:" << endl;
        for (Customer c : winners) {
            cout << "(" << c.id << ", " << c.buyCnt << ", " << c.enterTime << ")" << endl;
        }*/

        ans.push_back(getCurAns(winners));
    }
    return ans;
}


//构造测试数据
class Data {
public:
    vector<int> arr;
    vector<bool> op;

    Data(vector<int> &a, vector<bool> &o) {
        arr = a;
        op = o;
    }
};

Data randomData(int maxValue, int maxLen) {
    int len = (rand() % maxLen) + 1;
    vector<int> arr(len);
    vector<bool> op(len);

    for (int i = 0; i < len; i++) {
        arr[i] = rand() % maxValue;
        op[i] = ((rand() % 101 / (double) 101)) < 0.5 ? true : false;
    }
    return Data(arr, op);
}

bool cmp(int &a, int &b) {
    return a < b;
}


//比较两种方法的答案是否一致
bool sameAnswer(vector<vector<int>> &ans1, vector<vector<int>> &ans2) {
    if (ans1.size() != ans2.size()) return false;

    for (int i = 0; i < ans1.size(); i++) {
        vector<int> cur1 = ans1[i];
        vector<int> cur2 = ans2[i];
        if (cur1.size() != cur2.size()) return false;

        sort(cur1.begin(), cur1.end(), cmp);
        sort(cur2.begin(), cur2.end(), cmp);

        for (int j = 0; j < cur1.size(); j++) {
            if (cur1[j] != cur2[j]) return false;
        }
    }
    return true;
}


void printArray(vector<vector<int>> &ans) {
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].size(); j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
}

void print(vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));
    int maxValue = 100;
    int maxLen = 1000;
    int maxK = 10;
    int testTime = 100;

    cout << "测试开始" << endl;
    for (int i = 0; i < testTime + 1; i++) {
        Data testData = randomData(maxValue, maxLen);
        int k = (rand() % maxK) + 1;

        vector<int> arr = testData.arr;
        vector<bool> op = testData.op;

        vector<vector<int>> ans1 = topK(arr, op, k);

        vector<vector<int>> ans2 = compare(arr, op, k);

        if (!sameAnswer(ans1, ans2)) {
            for (int j = 0; j < arr.size(); j++) {
                cout << endl << "[" << arr[j] << " , " << op[j] << ", " << j << "]";
            }
            cout << endl;
            cout << "k = " << k << endl;

            cout << "ans1 : " << endl;
            printArray(ans1);


            cout << "ans2 : " << endl;
            printArray(ans2);

            cout << "出错了！" << endl;
            break;
        }

        if (i && i % 100 == 0) cout << i << " cases passed!" << endl;
    }

    cout << "测试结束！" << endl;
    return 0;
}
