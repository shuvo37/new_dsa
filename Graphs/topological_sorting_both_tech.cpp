#include <bits/stdc++.h>
using namespace std;

// Kahn's Algorithm with cycle detection
vector<int> topologicalSort(int n, vector<vector<int>>& adj) {
    vector<int> inDegree(n, 0);
    vector<int> result;

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

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        result.push_back(node);

        for (int neighbor : adj[node]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    if (result.size() != n) {
        cout << "Cycle detected! Topological sort not possible." << endl;
        return {};
    }

    return result;
}

// Alternative: DFS with stack
vector<int> topologicalSortDFSStack(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    stack<int> st;
    vector<int> result;

    function<void(int)> dfs = [&](int node) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor);
            }
        }
        st.push(node);
    };

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    while (!st.empty()) {
        result.push_back(st.top());
        st.pop();
    }

    return result;
}

int main() {
    // Example 1: Valid DAG
    int n1 = 6;
    vector<vector<int>> adj1(n1);
    adj1[5] = {2, 0};
    adj1[4] = {0, 1};
    adj1[2] = {3};
    adj1[3] = {1};
    adj1[0] = {};
    adj1[1] = {};

    cout << "Example 1 - Valid DAG:" << endl;
    vector<int> result1 = topologicalSort(n1, adj1);
    if (!result1.empty()) {
        cout << "Topological Order: ";
        for (int node : result1) cout << node << " ";
        cout << endl;
    }

    // Example 2: Graph with cycle
    int n2 = 3;
    vector<vector<int>> adj2(n2);
    adj2[0] = {1};
    adj2[1] = {2};
    adj2[2] = {0}; // Cycle: 0->1->2->0

    cout << "\nExample 2 - Graph with cycle:" << endl;
    vector<int> result2 = topologicalSort(n2, adj2);
    if (!result2.empty()) {
        cout << "Topological Order: ";
        for (int node : result2) cout << node << " ";
        cout << endl;
    }

    // Example 3: Using DFS stack method
    cout << "\nExample 3 - DFS Stack method:" << endl;
    vector<int> result3 = topologicalSortDFSStack(n1, adj1);
    cout << "Topological Order (DFS): ";
    for (int node : result3) cout << node << " ";
    cout << endl;

    return 0;
}
