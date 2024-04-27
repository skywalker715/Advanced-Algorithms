#include <iostream>
#include <list>
#include <stack>
using namespace std;

class Graph {
    int nodeCount;
    list<int>* adjacency;

    void fillOrder(int node, bool visited[], stack<int>& nodeStack);
    void traverseDFS(int node, bool visited[]);

public:
    Graph(int count);
    void addConnection(int from, int to);
    void printComponents();
    Graph transpose();
};

Graph::Graph(int count) {
    nodeCount = count;
    adjacency = new list<int>[count];
}

void Graph::traverseDFS(int node, bool visited[]) {
    visited[node] = true;
    cout << node << " ";

    for (auto i = adjacency[node].begin(); i != adjacency[node].end(); ++i)
        if (!visited[*i])
            traverseDFS(*i, visited);
}

Graph Graph::transpose() {
    Graph gT(nodeCount);
    for (int node = 0; node < nodeCount; node++) {
        for (auto i = adjacency[node].begin(); i != adjacency[node].end(); ++i) {
            gT.adjacency[*i].push_back(node);
        }
    }
    return gT;
}

void Graph::addConnection(int from, int to) {
    adjacency[from].push_back(to);
}

void Graph::fillOrder(int node, bool visited[], stack<int>& nodeStack) {
    visited[node] = true;

    for (auto i = adjacency[node].begin(); i != adjacency[node].end(); ++i)
        if (!visited[*i])
            fillOrder(*i, visited, nodeStack);

    nodeStack.push(node);
}

void Graph::printComponents() {
    stack<int> nodeStack;
    bool* visited = new bool[nodeCount];
    fill(visited, visited + nodeCount, false);

    for (int i = 0; i < nodeCount; i++)
        if (!visited[i])
            fillOrder(i, visited, nodeStack);

    Graph gT = transpose();
    fill(visited, visited + nodeCount, false);

    while (!nodeStack.empty()) {
        int node = nodeStack.top();
        nodeStack.pop();

        if (!visited[node]) {
            gT.traverseDFS(node, visited);
            cout << endl;
        }
    }
}

int main() {
    Graph g(7);
    g.addConnection(0, 1);
    g.addConnection(1, 2);
    g.addConnection(2, 0);
    g.addConnection(2, 3);
    g.addConnection(3, 4);
    g.addConnection(4, 5);
    g.addConnection(5, 3);
    g.addConnection(5, 6);

    cout << "Strongly Connected Components are:\n";
    g.printComponents();
    return 0;
}