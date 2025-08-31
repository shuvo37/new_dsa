#include <bits/stdc++.h>
using namespace std;

class LCA {
private:
    int n, logn;
    vector<vector<int>> adj, table;
    vector<int> level, parent;

    void dfs(int u, int p, int depth) {
        parent[u] = p;
        level[u] = depth;
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, depth + 1);
            }
        }
    }

    void buildTable() {
        for (int i = 0; i < n; i++) {
            table[i][0] = parent[i];
        }

        for (int j = 1; j <= logn; j++) {
            for (int i = 0; i < n; i++) {
                if (table[i][j-1] != -1) {
                    table[i][j] = table[table[i][j-1]][j-1];
                }
            }
        }
    }

public:
    LCA(int nodes, const vector<vector<int>>& graph) {
        n = nodes;
        adj = graph;
        logn = log2(n) + 1;
        level.resize(n);
        parent.resize(n);
        table.assign(n, vector<int>(logn + 1, -1));

        dfs(0, -1, 0);
        buildTable();
    }

    int query(int a, int b) {
        if (level[a] < level[b]) swap(a, b);

        // Lift a to same level as b
        int diff = level[a] - level[b];
        for (int i = 0; i <= logn; i++) {
            if (diff & (1 << i)) {
                a = table[a][i];
            }
        }

        if (a == b) return a;

        // Lift both until their parents are the same
        for (int i = logn; i >= 0; i--) {
            if (table[a][i] != -1 && table[a][i] != table[b][i]) {
                a = table[a][i];
                b = table[b][i];
            }
        }

        return parent[a];
    }

    int getLevel(int node) {
        return level[node];
    }
};

int main() {
    int n = 5;
    vector<vector<int>> graph(n);
    graph[0] = {1, 2};
    graph[1] = {0};
    graph[2] = {0, 3, 4};
    graph[3] = {2};
    graph[4] = {2};

    LCA lca(n, graph);

    cout << "LCA of 3 and 4: " << lca.query(3, 4) << endl;
    cout << "LCA of 1 and 4: " << lca.query(1, 4) << endl;
    cout << "Level of node 3: " << lca.getLevel(3) << endl;

    return 0;
}
