#include <bits/stdc++.h>
using namespace std;

// Bipartite check with BFS
bool isBipartite(int n, vector<vector<int>>& adj) {
    vector<int> color(n, -1);

    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            queue<int> q;
            q.push(i);
            color[i] = 0;

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (int neighbor : adj[node]) {
                    if (color[neighbor] == -1) {
                        color[neighbor] = 1 - color[node];
                        q.push(neighbor);
                    } else if (color[neighbor] == color[node]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

// Alternative: Return the two partitions if bipartite
pair<bool, vector<vector<int>>> getBipartitePartitions(int n, vector<vector<int>>& adj) {
    vector<int> color(n, -1);
    vector<vector<int>> partitions(2);

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
                        return {false, {}};
                    }
                }
            }
        }
    }
    return {true, partitions};
}

int main() {
    // Example 1: Bipartite graph (even cycle)
    int n1 = 4;
    vector<vector<int>> adj1(n1);
    adj1[0] = {1, 3};
    adj1[1] = {0, 2};
    adj1[2] = {1, 3};
    adj1[3] = {0, 2};

    cout << "Graph 1 (Even cycle): " << (isBipartite(n1, adj1) ? "Bipartite" : "Not Bipartite") << endl;

    // Example 2: Non-bipartite graph (odd cycle)
    int n2 = 3;
    vector<vector<int>> adj2(n2);
    adj2[0] = {1, 2};
    adj2[1] = {0, 2};
    adj2[2] = {0, 1};

    cout << "Graph 2 (Odd cycle): " << (isBipartite(n2, adj2) ? "Bipartite" : "Not Bipartite") << endl;

    // Example 3: Get partitions
    int n3 = 5;
    vector<vector<int>> adj3(n3);
    adj3[0] = {1, 3};
    adj3[1] = {0, 2};
    adj3[2] = {1, 4};
    adj3[3] = {0, 4};
    adj3[4] = {2, 3};

    auto result = getBipartitePartitions(n3, adj3);
    if (result.first) {
        cout << "Graph 3 is Bipartite" << endl;
        cout << "Partition 0: ";
        for (int node : result.second[0]) cout << node << " ";
        cout << endl;
        cout << "Partition 1: ";
        for (int node : result.second[1]) cout << node << " ";
        cout << endl;
    } else {
        cout << "Graph 3 is Not Bipartite" << endl;
    }

    return 0;
}
