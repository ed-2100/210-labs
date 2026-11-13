// COMSC-210 | Lab 34 | Edwin Burwell
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <climits>
#include <cctype>
using namespace std;

const int SIZE = 9;
const int MIN_VERTEX = 0;
const int START_VERTEX = 0;
const int CAPACITY_SCALE = 100;
const int INF_DIST = INT_MAX;
const int ZERO_DIST = 0;
const int NO_PARENT = -1;

const int OPT_EXIT = 0;
const int OPT_DISPLAY = 1;
const int OPT_BFS = 2;
const int OPT_DFS = 3;
const int OPT_SHORTEST = 4;
const int OPT_MST = 5;
const int MIN_CHOICE = OPT_EXIT;
const int MAX_CHOICE = OPT_MST;
const int MAX_INPUT_LEN = 6;
const int FIRST_IDX = 0;
const int SECOND_IDX = 1;

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

    // minimumSpanningTree() finds and prints the MST using Prim's algorithm
    // arguments: start - integer representing the starting vertex index
    // returns: void
    void minimumSpanningTree(int start) {
        if (start < MIN_VERTEX || start >= adjList.size()) {
            cout << "Error: Starting substation " << start
                 << " is out of range. Please specify an index between "
                 << MIN_VERTEX << " and " << adjList.size() - 1 << "."
                 << endl;
            return;
        }

        vector<int> key(adjList.size(), INF_DIST);
        vector<int> parent(adjList.size(), NO_PARENT);
        vector<bool> inMST(adjList.size(), false);
        priority_queue<Pair, vector<Pair>, greater<Pair>> minHeap;

        key[start] = ZERO_DIST;
        minHeap.push(make_pair(ZERO_DIST, start));

        cout << "Minimum Spanning Tree edges:" << endl;

        // Greedily select minimum-weight edges connecting new vertices to MST
        while (!minHeap.empty()) {
            int u = minHeap.top().second;
            minHeap.pop();

            if (inMST[u]) {
                continue;
            }

            inMST[u] = true;

            if (parent[u] != NO_PARENT) {
                cout << "Edge from " << u << " to " << parent[u]
                     << " with capacity: " << key[u] << " units" << endl;
            }

            for (auto &neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    minHeap.push(make_pair(key[v], v));
                }
            }
        }
        cout << endl;
    }
};

// Function prototypes
void displayMenu();
int getMenuChoice();
bool isNumericInput(string const &input);

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

    Graph powerGrid(edges, facilityTypes);
    int choice = OPT_DISPLAY;

    // Run interactive menu loop until the user selects Exit
    while (choice != OPT_EXIT) {
        displayMenu();
        choice = getMenuChoice();
        cout << endl;

        switch (choice) {
            case OPT_DISPLAY:
                powerGrid.printGraph();
                break;
            case OPT_BFS:
                powerGrid.bfs(START_VERTEX);
                break;
            case OPT_DFS:
                powerGrid.dfs(START_VERTEX);
                break;
            case OPT_SHORTEST:
                powerGrid.shortestPath(START_VERTEX);
                break;
            case OPT_MST:
                powerGrid.minimumSpanningTree(START_VERTEX);
                break;
            case OPT_EXIT:
                cout << "Exiting Regional Power Grid Network System." << endl;
                break;
        }
    }

    return 0;
}

// displayMenu() prints the interactive power grid options menu to the console
// arguments: none
// returns: void
void displayMenu() {
    cout << "Regional Power Grid Network Menu:" << endl;
    cout << "[" << OPT_DISPLAY << "] Display power grid network" << endl;
    cout << "[" << OPT_BFS << "] Inspect delivery zones (BFS)" << endl;
    cout << "[" << OPT_DFS << "] Trace cascading fault paths (DFS)" << endl;
    cout << "[" << OPT_SHORTEST << "] Calculate shortest paths" << endl;
    cout << "[" << OPT_MST << "] Find Minimum Spanning Tree" << endl;
    cout << "[" << OPT_EXIT << "] Exit" << endl;
    cout << "Enter your choice: ";
}

// isNumericInput() checks whether a string represents a signed or unsigned int
// arguments: input - constant reference to the user's raw input string
// returns: true if input contains only valid integer digits, false otherwise
bool isNumericInput(string const &input) {
    if (input.empty()) {
        return false;
    }

    int startPos = FIRST_IDX;
    if (input[FIRST_IDX] == '-' || input[FIRST_IDX] == '+') {
        if (input.length() == SECOND_IDX) {
            return false;
        }
        startPos = SECOND_IDX;
    }

    for (size_t i = startPos; i < input.length(); i++) {
        if (!isdigit(static_cast<unsigned char>(input[i]))) {
            return false;
        }
    }
    return true;
}

// getMenuChoice() reads and validates a menu selection from standard input
// arguments: none
// returns: validated integer choice between MIN_CHOICE and MAX_CHOICE
int getMenuChoice() {
    string rawInput;

    while (true) {
        if (!getline(cin, rawInput)) {
            return OPT_EXIT;
        }

        if (rawInput.empty()) {
            cout << "Invalid input: entry cannot be blank. Please type a "
                 << "digit from " << MIN_CHOICE << " to " << MAX_CHOICE
                 << " and try again: ";
            continue;
        }

        if (!isNumericInput(rawInput)) {
            cout << "Invalid input: '" << rawInput << "' contains non-digit "
                 << "characters. Please enter a number from " << MIN_CHOICE
                 << " to " << MAX_CHOICE << " and try again: ";
            continue;
        }

        if (rawInput.length() > MAX_INPUT_LEN) {
            cout << "Invalid choice: '" << rawInput << "' is out of range. "
                 << "Please enter a menu option between " << MIN_CHOICE
                 << " and " << MAX_CHOICE << " and try again: ";
            continue;
        }

        int value = stoi(rawInput);
        if (value < MIN_CHOICE || value > MAX_CHOICE) {
            cout << "Invalid choice: " << value << " is out of range. "
                 << "Please enter a menu option between " << MIN_CHOICE
                 << " and " << MAX_CHOICE << " and try again: ";
            continue;
        }

        return value;
    }
}
