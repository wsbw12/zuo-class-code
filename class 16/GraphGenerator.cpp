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
private:
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
public:
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


int main() {
    return 0;
}