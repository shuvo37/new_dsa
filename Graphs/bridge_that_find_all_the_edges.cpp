#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector<int> adj[N];
bool visited[N];
int disc[N], low[N], timer;
vector<pair<int,int>> bridges;

void dfs(int u, int parent) {
    visited[u] = true;
    disc[u] = low[u] = ++timer;

    for (int v : adj[u]) {
        if (v == parent) continue; // ignore edge to parent

        if (!visited[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);

            // condition for bridge
            if (low[v] > disc[u]) {
                bridges.push_back({u, v});
            }
        }
        else {
            // back edge
            low[u] = min(low[u], disc[v]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;  // n = number of nodes, m = number of edges

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected graph
    }

    timer = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, -1);
        }
    }

    cout << "Bridges in the graph:\n";
    for (auto x : bridges) {
        cout << x.first << " - " << x.second << "\n";
    }

    return 0;
}
