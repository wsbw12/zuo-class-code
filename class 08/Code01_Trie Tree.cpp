#include <iostream>

using namespace std;
//26 个小写英文字母
#define NUMBER 26

// 节点的结构
class TrieNode {
public:
    int pass; // 表示这个节点有多少个字符串进过
    int end;  // 表示有多少个字符串以这个节点作为结束
    TrieNode *nexts[NUMBER]; // 每个节点 的 下一层都有26个分支

    TrieNode() {
        pass = 0;
        end = 0;
        for (int i = 0; i < NUMBER; i++) {
            nexts[i] = nullptr;
        }
    }

    ~TrieNode() {
        for (int i = 0; i < NUMBER; i++) {
            if (nexts[i]) delete nexts[i];
        }
    }
};

// 所调用的树结构
class TrieTree {
    TrieNode *root = nullptr;
public:
    TrieTree() {
        root = new TrieNode();
    }

    // 插入
    void insert(string word) {
        TrieNode *cur = root;
        cur->pass++;
        for (int i = 0; i < word.size(); i++) {
            int num = word[i] - 'a'; // 计算这个字符应该位于哪个位置
            if (cur->nexts[num] == nullptr) { //如果这个字符位于的位置是空的话,就创建一个节点
                cur->nexts[num] = new TrieNode();
            }
            cur = cur->nexts[num];
            cur->pass++; // 每个节点被经过的时候pass值都要进行加一
        }
        cur->end++;//最后一个节点的end值加1
    }

    //查找字符串数量
    int find(string word) {
        TrieNode *cur = root;
        for (int i = 0; i < word.size(); i++) {
            int num = word[i] - 'a';
            if (cur->nexts[num] == nullptr) return 0;
            cur = cur->nexts[num];
        }
        return cur->end;
    }

    //查找前缀数量
    int findContain(string word) {
        TrieNode *cur = root;
        for (int i = 0; i < word.size(); i++) {
            int num = word[i] - 'a';
            if (cur->nexts[num] == nullptr) return 0;
            cur = cur->nexts[num];
        }
        return cur->pass;
    }

    //删除
    bool erase(string word) {
        if (find(word) == 0) return false; //如果前缀树中不存在该字符串,则直接返回false
        TrieNode *cur = root;
        for (int i = 0; i < word.size(); i++) {
            int num = word[i] - 'a';
            if (cur->nexts[num]->pass <= 1) {
                delete cur->nexts[num];
                cur->nexts[num] = nullptr;
                return true;
            }
            cur = cur->nexts[num];
            cur->pass--;
        }
        cur->end--;
        return true;
    }
};

int main() {
    TrieTree temp;
    temp.insert("abc");
    temp.insert("abe");
    temp.insert("bcf");
    temp.insert("abcg");
    int a = temp.find("abc");
    cout << a << endl;
    int c = temp.findContain("ab");
    cout << c << endl;
    temp.erase("abc");
    a = temp.find("abc");
    cout << a << endl;
    int b = temp.findContain("ab");
    cout << b << endl;
    cout << temp.find("bcf") << endl;
    temp.erase("bcf");
    cout << temp.find("bcf") << endl;
    return 0;
}
