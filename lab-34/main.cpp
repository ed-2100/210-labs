// COMSC-210 | Lab 34 | Edwin Burwell
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

const int SIZE = 9;
const int MIN_VERTEX = 0;
const int START_VERTEX = 0;

struct Edge {
    int src, dest, weight;
};

// Alias 'Pair' for the pair<int, int> data type
typedef pair<int, int> Pair;

class Graph {
public:
    // Vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph() constructs an undirected graph from a vector of Edge structs
    // arguments: edges - constant reference to a vector of Edge objects
    // returns: none (constructor)
    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);

        // Add edges to the undirected graph
        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // printGraph() outputs the graph's adjacency list to the console
    // arguments: none
    // returns: void
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i]) {
                cout << "(" << v.first << ", " << v.second << ") ";
            }
            cout << endl;
        }
    }

    // dfs() performs an iterative Depth-First Search from a starting vertex
    // arguments: start - integer representing the starting vertex index
    // returns: void
    void dfs(int start) {
        if (start < MIN_VERTEX || start >= adjList.size()) {
            cout << "Error: Starting vertex " << start << " is out of range. "
                 << "Please specify a vertex between " << MIN_VERTEX
                 << " and " << adjList.size() - 1 << "." << endl;
            return;
        }

        vector<bool> visited(adjList.size(), false);
        stack<int> vertexStack;
        vertexStack.push(start);

        cout << "DFS starting from vertex " << start << ":" << endl;

        // Traverse deeply through the graph using a LIFO stack
        while (!vertexStack.empty()) {
            int curr = vertexStack.top();
            vertexStack.pop();

            if (!visited[curr]) {
                visited[curr] = true;
                cout << curr << " ";

                // Push all unvisited adjacent vertices onto the stack
                for (auto &neighbor : adjList[curr]) {
                    int nextVertex = neighbor.first;
                    if (!visited[nextVertex]) {
                        vertexStack.push(nextVertex);
                    }
                }
            }
        }
        cout << endl;
    }

    // bfs() performs an iterative Breadth-First Search from a starting vertex
    // arguments: start - integer representing the starting vertex index
    // returns: void
    void bfs(int start) {
        if (start < MIN_VERTEX || start >= adjList.size()) {
            cout << "Error: Starting vertex " << start << " is out of range. "
                 << "Please specify a vertex between " << MIN_VERTEX
                 << " and " << adjList.size() - 1 << "." << endl;
            return;
        }

        vector<bool> visited(adjList.size(), false);
        queue<int> vertexQueue;

        visited[start] = true;
        vertexQueue.push(start);

        cout << "BFS starting from vertex " << start << ":" << endl;

        // Traverse the graph level-by-level using a FIFO queue
        while (!vertexQueue.empty()) {
            int curr = vertexQueue.front();
            vertexQueue.pop();
            cout << curr << " ";

            // Enqueue all unvisited adjacent vertices
            for (auto &neighbor : adjList[curr]) {
                int nextVertex = neighbor.first;
                if (!visited[nextVertex]) {
                    visited[nextVertex] = true;
                    vertexQueue.push(nextVertex);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    // Define updated graph edges as (source, destination, weight)
    vector<Edge> edges = {
        {0, 1, 8}, {0, 2, 21}, {1, 2, 6}, {1, 3, 5}, {1, 4, 4},
        {3, 4, 9}, {5, 6, 10}, {6, 7, 3}, {5, 7, 15}, {5, 8, 5},
        {6, 8, 7}, {2, 7, 11}, {2, 8, 8}
    };

    // Instantiate the graph and run adjacency list, DFS, and BFS operations
    Graph graph(edges);
    graph.printGraph();
    graph.dfs(START_VERTEX);
    graph.bfs(START_VERTEX);

    return 0;
}
