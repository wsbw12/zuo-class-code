#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <unordered_map>
#include <queue>
#include <cstdlib>
#include <unordered_set>
#include <set>

using namespace std;

class Node;

class Edge;

class Graph;

class Edge {
public:
    int weight;
    Node *from;
    Node *to;
public:
    Edge(int weight, Node *from, Node *to) {
        this->weight = weight;
        this->from = from;
        this->to = to;
    }
};

class Graph {
public:
    unordered_set<Edge *> edges;
    unordered_map<int, Node *> nodes;
};

class Node {
public:
    int value;
    int in;
    int out;

public:
    Node(int value) {//value为节点的值
        this->value = value;
        this->in = 0;
        this->out = 0;
    }

    vector<Edge *> edge;
    vector<Node *> nexts;
};

// matrix 所有的边
// N*3 的矩阵
// [weight, from节点上面的值，to节点上面的值]
//
// [ 5 , 0 , 7] 表示从0节点到7节点有一条边权重为5
// [ 3 , 0,  1]
class GraphGenerator {
public:
    Graph *createGraph(vector<vector<int>> matrix) {
        Graph *graph = new Graph();
        for (int i = 0; i < matrix.size(); i++) {
            // 拿到每一条边， matrix[i]
            int weight = matrix[i][0];
            int from = matrix[i][1];
            int to = matrix[i][2];
            if (!graph->nodes.count(from)) {
                Node *temp = new Node(from);
                graph->nodes[from] = temp;
            }
            if (!graph->nodes.count(to)) {
                Node *temp = new Node(to);
                graph->nodes[to] = temp;
            }
            Node *fromNode = graph->nodes[from];
            Node *toNode = graph->nodes[to];
            Edge *newEdge = new Edge(weight, fromNode, toNode);
            fromNode->nexts.push_back(toNode);
            fromNode->out++;
            toNode->in++;
            fromNode->edge.push_back(newEdge);
            graph->edges.insert(newEdge);
        }
        return graph;
    }
};

class UnionFind {
public:
    // key 某一个节点， value key节点往上的节点(父节点)
    unordered_map<Node *, Node *> fatherMap;
    // key 某一个集合的代表节点, value key所在集合的节点个数
    unordered_map<Node *, int> sizeMap;

    void makeSets(Node *nodes) {
        fatherMap[nodes] = nodes;
        sizeMap[nodes] = 1;
    }

    Node *findFather(Node *n) {
        stack<Node *> path;
        while (n != fatherMap[n]) {
            path.push(n);
            n = fatherMap[n];
        }
        while (!path.empty()) {
            fatherMap[path.top()] = n;
            path.pop();
        }
        return n;
    }


    bool isSameSet(Node *a, Node *b) {
        return findFather(a) == findFather(b);
    }

    void Union(Node *a, Node *b) {
        if (a == nullptr || b == nullptr) {
            return;
        }
        Node *aDai = findFather(a);
        Node *bDai = findFather(b);
        if (aDai != bDai) {
            int aSetSize = sizeMap[aDai];
            int bSetSize = sizeMap[bDai];
            if (aSetSize <= bSetSize) {
                fatherMap[aDai] = bDai;
                sizeMap[bDai] = aSetSize + bSetSize;
                sizeMap.erase(aDai);
            } else {
                fatherMap[bDai] = aDai;
                sizeMap[aDai] = aSetSize + bSetSize;
                sizeMap.erase(bDai);
            }
        }
    }
};

struct cmpWeight {
    bool operator()(const Edge &o1, const Edge &o2) {
        return (o1.weight < o2.weight);
    }
};

// 最小生成树  PrimMST算法
set<Edge *> primMST(Graph *graph) {
    // 解锁的边进入小根堆
    priority_queue<Edge *, vector<Edge *>, cmpWeight> minHeap;
    // 哪些点被解锁出来了
    unordered_set<Node *> nodeSet;
    set<Edge *> result; // 依次挑选的的边在result里
    unordered_map<int, Node *> Node = graph->nodes;
    for (int i = 0; i < graph->nodes.size(); i++) {
        if (!nodeSet.count(graph->nodes[i])) {
            nodeSet.insert(graph->nodes[i]);
            for (Edge *edge:graph->nodes[i]->edge) {
                minHeap.push(edge);
            }
            while (!minHeap.empty()) {
                Edge *edge = minHeap.top();
                minHeap.pop();
                auto to_node = edge->to;
                if (!nodeSet.count(to_node)) {
                    nodeSet.insert(to_node);
                    result.insert(edge);
                    for (Edge *nextEdge: to_node->edge) {
                        minHeap.push(nextEdge);
                    }
                }
            }
        }
    }
    return result;
}

int main() {
    return 0;
}