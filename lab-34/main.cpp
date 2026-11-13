// COMSC-210 | Lab 34 | Edwin Burwell
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <climits>
using namespace std;

const int SIZE = 9;
const int MIN_VERTEX = 0;
const int START_VERTEX = 0;
const int CAPACITY_SCALE = 100;
const int INF_DIST = INT_MAX;
const int ZERO_DIST = 0;

struct Edge {
    int src, dest, weight;
};

// Alias 'Pair' for the pair<int, int> data type
typedef pair<int, int> Pair;

class Graph {
public:
    // Vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;
    vector<string> nodeTypes;

    // Graph() constructs an undirected power grid graph with facility labels
    // arguments: edges - constant reference to a vector of Edge objects
    //            types - constant reference to a vector of facility names
    // returns: none (constructor)
    Graph(vector<Edge> const &edges, vector<string> const &types) {
        adjList.resize(SIZE);
        nodeTypes = types;

        // Add transmission lines to the undirected power grid graph
        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // printGraph() outputs the power grid network topology to the console
    // arguments: none
    // returns: void
    void printGraph() {
        cout << "Regional Power Grid Network Topology:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << "Substation " << i << " (" << nodeTypes[i]
                 << ") connects to:" << endl;
            for (Pair v : adjList[i]) {
                int cap = v.second * CAPACITY_SCALE;
                cout << "  -> Substation " << v.first << " (Capacity: "
                     << cap << " MW)" << endl;
            }
        }
        cout << endl;
    }

    // dfs() performs a Depth-First Search to trace cascading surge paths
    // arguments: start - integer representing the starting substation index
    // returns: void
    void dfs(int start) {
        if (start < MIN_VERTEX || start >= adjList.size()) {
            cout << "Error: Starting substation " << start
                 << " is out of range. Please specify an index between "
                 << MIN_VERTEX << " and " << adjList.size() - 1 << "."
                 << endl;
            return;
        }

        vector<bool> visited(adjList.size(), false);
        stack<int> vertexStack;

        visited[start] = true;
        vertexStack.push(start);

        cout << "Grid Fault Trace (DFS) from Substation " << start << " ("
             << nodeTypes[start] << "):" << endl;
        cout << "Purpose: Tracing possible cascading surge paths through the "
             << "grid" << endl;
        cout << "============================================================"
             << "====" << endl;

        // Traverse deeply through the grid using a LIFO stack
        while (!vertexStack.empty()) {
            int curr = vertexStack.top();
            vertexStack.pop();

            cout << "Inspecting Substation " << curr << " ("
                 << nodeTypes[curr] << ")" << endl;

            // Mark and push all unvisited adjacent substations onto the stack
            for (auto &neighbor : adjList[curr]) {
                int nextVertex = neighbor.first;
                int cap = neighbor.second * CAPACITY_SCALE;
                if (!visited[nextVertex]) {
                    visited[nextVertex] = true;
                    vertexStack.push(nextVertex);
                    cout << "  -> Potential surge to Substation " << nextVertex
                         << " (" << nodeTypes[nextVertex] << ") - Capacity: "
                         << cap << " MW" << endl;
                }
            }
        }
        cout << endl;
    }

    // bfs() performs a Breadth-First Search for layer-by-layer load inspection
    // arguments: start - integer representing the starting substation index
    // returns: void
    void bfs(int start) {
        if (start < MIN_VERTEX || start >= adjList.size()) {
            cout << "Error: Starting substation " << start
                 << " is out of range. Please specify an index between "
                 << MIN_VERTEX << " and " << adjList.size() - 1 << "."
                 << endl;
            return;
        }

        vector<bool> visited(adjList.size(), false);
        queue<int> vertexQueue;

        visited[start] = true;
        vertexQueue.push(start);

        cout << "Layer-by-Layer Grid Inspection (BFS) from Substation "
             << start << " (" << nodeTypes[start] << "):" << endl;
        cout << "Purpose: Analyzing power delivery zones by distance from "
             << "source" << endl;
        cout << "============================================================"
             << "===" << endl;

        // Traverse the grid level-by-level using a FIFO queue
        while (!vertexQueue.empty()) {
            int curr = vertexQueue.front();
            vertexQueue.pop();

            cout << "Checking Substation " << curr << " ("
                 << nodeTypes[curr] << ")" << endl;

            // Mark and enqueue all unvisited adjacent substations
            for (auto &neighbor : adjList[curr]) {
                int nextVertex = neighbor.first;
                int cap = neighbor.second * CAPACITY_SCALE;
                if (!visited[nextVertex]) {
                    visited[nextVertex] = true;
                    vertexQueue.push(nextVertex);
                    cout << "  -> Next delivery zone: Substation "
                         << nextVertex << " (" << nodeTypes[nextVertex]
                         << ") - Capacity: " << cap << " MW" << endl;
                }
            }
        }
        cout << endl;
    }

    // shortestPath() calculates shortest distances from start via Dijkstra's
    // arguments: start - integer representing the source node index
    // returns: void
    void shortestPath(int start) {
        if (start < MIN_VERTEX || start >= adjList.size()) {
            cout << "Error: Starting substation " << start
                 << " is out of range. Please specify an index between "
                 << MIN_VERTEX << " and " << adjList.size() - 1 << "."
                 << endl;
            return;
        }

        vector<int> dist(adjList.size(), INF_DIST);
        priority_queue<Pair, vector<Pair>, greater<Pair>> minHeap;

        dist[start] = ZERO_DIST;
        minHeap.push(make_pair(ZERO_DIST, start));

        // Relax edges in order of increasing cumulative path weight
        while (!minHeap.empty()) {
            int currDist = minHeap.top().first;
            int u = minHeap.top().second;
            minHeap.pop();

            if (currDist > dist[u]) {
                continue;
            }

            for (auto &neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    minHeap.push(make_pair(dist[v], v));
                }
            }
        }

        cout << "Shortest path from node " << start << ":" << endl;
        for (int i = 0; i < dist.size(); i++) {
            cout << start << " -> " << i << " : ";
            if (dist[i] == INF_DIST) {
                cout << "Unreachable" << endl;
            } else {
                cout << dist[i] << endl;
            }
        }
        cout << endl;
    }
};

int main() {
    // Define power grid transmission lines as (source, destination, weight)
    vector<Edge> edges = {
        {0, 1, 8}, {0, 2, 21}, {1, 2, 6}, {1, 3, 5}, {1, 4, 4},
        {3, 4, 9}, {5, 6, 10}, {6, 7, 3}, {5, 7, 15}, {5, 8, 5},
        {6, 8, 7}, {2, 7, 11}, {2, 8, 8}
    };

    // Define facility types for each of the 9 substations in the grid
    vector<string> facilityTypes = {
        "Main Power Plant",
        "Primary Transformer Hub",
        "High-Voltage Switchyard",
        "Industrial Converter",
        "Battery Storage Bank",
        "Regional Distribution Hub",
        "Grid Breaker Station",
        "Backup Battery Bank",
        "Solar Generation Array"
    };

    // Instantiate the power grid graph and run all network analyses
    Graph powerGrid(edges, facilityTypes);
    powerGrid.printGraph();
    powerGrid.dfs(START_VERTEX);
    powerGrid.bfs(START_VERTEX);
    powerGrid.shortestPath(START_VERTEX);

    return 0;
}