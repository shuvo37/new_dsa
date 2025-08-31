#include <bits/stdc++.h>
using namespace std;

// Handles disconnected graphs and returns detailed result
struct BipartiteResult {
    bool isBipartite;
    vector<int> color;
    vector<vector<int>> partitions;
};

BipartiteResult checkBipartiteDetailed(int n, vector<vector<int>>& adj) {
    vector<int> color(n, -1);
    vector<vector<int>> partitions(2);
    BipartiteResult result;

    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            queue<int> q;
            q.push(i);
            color[i] = 0;
            partitions[0].push_back(i);

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (int neighbor : adj[node]) {
                    if (color[neighbor] == -1) {
                        color[neighbor] = 1 - color[node];
                        partitions[color[neighbor]].push_back(neighbor);
                        q.push(neighbor);
                    } else if (color[neighbor] == color[node]) {
                        result.isBipartite = false;
                        result.color = color;
                        result.partitions = {};
                        return result;
                    }
                }
            }
        }
    }

    result.isBipartite = true;
    result.color = color;
    result.partitions = partitions;
    return result;
}

// Usage example
void usageExample() {
    int n = 6;
    vector<vector<int>> adj(n);
    // Component 1: bipartite
    adj[0] = {1};
    adj[1] = {0, 2};
    adj[2] = {1};
    // Component 2: bipartite
    adj[3] = {4};
    adj[4] = {3, 5};
    adj[5] = {4};

    BipartiteResult result = checkBipartiteDetailed(n, adj);
    if (result.isBipartite) {
        cout << "Graph is bipartite" << endl;
        cout << "Color assignments: ";
        for (int i = 0; i < n; i++) {
            cout << "Node " << i << ": " << result.color[i] << ", ";
        }
        cout << endl;
    } else {
        cout << "Graph is not bipartite" << endl;
    }
}
