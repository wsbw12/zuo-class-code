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

const int Max = 100;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}

};

ListNode *removeValue(ListNode *head, int num) {
    while (head) {  // 这个while循环是找到链表中第一个节点的值不为num的节点,这个节点将作为最后的头节点返回
        if (head->val != num) {
            break;
        }
        head = head->next;
    }
    //此时跳出循环就只有两种情况 1) head==NULL 2)head!=NULL
    ListNode *pre = head;
    ListNode *cur = head;
    while (cur) {
        if (cur->val == num) {
            pre->next = cur->next;
        } else {
            pre = cur;
        }
        cur = cur->next;
    }
    return head;
}

ListNode *createList(vector<int> &ve)//尾插法构建单链表
{
    ListNode *head = nullptr, *s = nullptr;
    for (int each:ve) {
        if (!head) {
            head = s = new ListNode(each);
        } else {
            ListNode *p = new ListNode(each);
            s->next = p;
            s = s->next;
        }
    }
    return head;
}

void printArr(vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

//打印单链表
void printList(ListNode *head) {
    do {
        cout << head->val << " ";
        head = head->next;
    } while (head);
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

//验证删除后的链表节点中是否有值等于num
bool checkListNum(ListNode *head, int num) {
    while (head) {
        if (head->val == num) {
            return false;
        }
        head = head->next;
    }
    return true;
}
//大样本测试
//函数名：main
//函数功能描述：大样本测试
//函数参数： size    生成数组最大尺寸
//         value   数组每个元素的最大值
//返回值：  vector<int> 生成的数组

int main() {
    int test_time = 100000;//进行测试的次数
    int size = 200;//生成数组的最大长度
    int value = 200;//生成数组的最大值
    bool is_accept = true;
    cout << "测试开始" << endl;
    for (int i = 0; i < test_time; i++) {
        vector<int> arr1 = generateRandomVector(size, value);
        ListNode *node1 = createList(arr1);
        int index = randomNumber(arr1.size());
        int num = arr1[index];
        node1 = removeValue(node1, num);
        if (!checkListNum(node1, num)) {
            cout << "出错了" << endl;
            printArr(arr1);
            printList(node1);
            cout << num << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}