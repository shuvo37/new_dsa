#include <bits/stdc++.h>
using namespace std;

// Method 1: DFS approach
bool hasCycleDFS(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false);

    function<bool(int)> dfs = [&](int node) {
        if (!visited[node]) {
            visited[node] = true;
            recStack[node] = true;

            for (int neighbor : adj[node]) {
                if (!visited[neighbor] && dfs(neighbor)) {
                    return true;
                } else if (recStack[neighbor]) {
                    return true;
                }
            }
        }
        recStack[node] = false;
        return false;
    };

    for (int i = 0; i < n; i++) {
        if (!visited[i] && dfs(i)) {
            return true;
        }
    }
    return false;
}

// Method 2: BFS (Kahn's algorithm)
bool hasCycleBFS(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> inDegree(n, 0);

    for (int i = 0; i < n; i++) {
        for (int neighbor : adj[i]) {
            inDegree[neighbor]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    int count = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        count++;

        for (int neighbor : adj[node]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    return count != n;
}

// Function to find the cycle path using DFS (assuming no self-loops)
vector<int> findCyclePath(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false);
    vector<int> parent(n, -1);
    vector<int> cycle;

    function<bool(int)> dfs = [&](int node) {
        visited[node] = true;
        recStack[node] = true;

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                parent[neighbor] = node;
                if (dfs(neighbor)) {
                    return true;
                }
            } else if (recStack[neighbor]) {
                // Cycle found, reconstruct the path
                int cur = node;
                while (cur != neighbor) {
                    cycle.push_back(cur);
                    cur = parent[cur];
                }
                cycle.push_back(neighbor);
                reverse(cycle.begin(), cycle.end());
                return true;
            }
        }

        recStack[node] = false;
        return false;
    };

    for (int i = 0; i < n; i++) {
        if (!visited[i] && dfs(i)) {
            return cycle;
        }
    }
    return {};
}

int main() {
    // Example 1: Graph without cycle
    int n1 = 4;
    vector<vector<int>> adj1(n1);
    adj1[0] = {1, 2};
    adj1[1] = {3};
    adj1[2] = {3};
    adj1[3] = {};

    cout << "Graph 1 (No cycle):" << endl;
    cout << "DFS Cycle Detection: " << (hasCycleDFS(adj1) ? "Cycle found" : "No cycle") << endl;
    cout << "BFS Cycle Detection: " << (hasCycleBFS(adj1) ? "Cycle found" : "No cycle") << endl;

    vector<int> cycle1 = findCyclePath(adj1);
    if (!cycle1.empty()) {
        cout << "Cycle path: ";
        for (int node : cycle1) cout << node << " ";
        cout << endl;
    } else {
        cout << "No cycle path found" << endl;
    }
    cout << endl;

    // Example 2: Graph with cycle
    int n2 = 5;
    vector<vector<int>> adj2(n2);
    adj2[0] = {1};
    adj2[1] = {2};
    adj2[2] = {3};
    adj2[3] = {4};
    adj2[4] = {1}; // Creates cycle: 1->2->3->4->1

    cout << "Graph 2 (With cycle):" << endl;
    cout << "DFS Cycle Detection: " << (hasCycleDFS(adj2) ? "Cycle found" : "No cycle") << endl;
    cout << "BFS Cycle Detection: " << (hasCycleBFS(adj2) ? "Cycle found" : "No cycle") << endl;

    vector<int> cycle2 = findCyclePath(adj2);
    if (!cycle2.empty()) {
        cout << "Cycle path: ";
        for (int node : cycle2) cout << node << " ";
        cout << endl;
    } else {
        cout << "No cycle path found" << endl;
    }
    cout << endl;

    // Example 3: Another cycle
    int n3 = 6;
    vector<vector<int>> adj3(n3);
    adj3[0] = {1};
    adj3[1] = {2};
    adj3[2] = {3};
    adj3[3] = {4};
    adj3[4] = {5};
    adj3[5] = {2}; // Creates cycle: 2->3->4->5->2

    cout << "Graph 3 (With cycle):" << endl;
    cout << "DFS Cycle Detection: " << (hasCycleDFS(adj3) ? "Cycle found" : "No cycle") << endl;
    cout << "BFS Cycle Detection: " << (hasCycleBFS(adj3) ? "Cycle found" : "No cycle") << endl;

    vector<int> cycle3 = findCyclePath(adj3);
    if (!cycle3.empty()) {
        cout << "Cycle path: ";
        for (int node : cycle3) cout << node << " ";
        cout << endl;
    } else {
        cout << "No cycle path found" << endl;
    }

    return 0;
}
