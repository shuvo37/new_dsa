#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

struct Edge {
    int u, v;
    ll weight;
};

// Bellman-Ford algorithm to find shortest paths from source
// Returns true if negative cycle exists, false otherwise
bool bellmanFord(int source, int n, vector<Edge>& edges, vector<ll>& dist, vector<int>& parent) {
    dist.assign(n, INF);
    parent.assign(n, -1);
    dist[source] = 0;

    // Relax all edges n-1 times
    for (int i = 0; i < n - 1; i++) {
        bool updated = false;
        for (const Edge& e : edges) {
            if (dist[e.u] < INF && dist[e.u] + e.weight < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.weight;
                parent[e.v] = e.u;
                updated = true;
            }
        }
        if (!updated) break; // Early termination if no updates
    }

    // Check for negative cycles
    for (const Edge& e : edges) {
        if (dist[e.u] < INF && dist[e.u] + e.weight < dist[e.v]) {
            return true; // Negative cycle found
        }
    }

    return false;
}

// Reconstruct shortest path from source to target
vector<int> get_shortest_path(int target, const vector<int>& parent) {
    vector<int> path;
    for (int v = target; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int n = 5; // Number of nodes
    vector<Edge> edges;

    // Add edges (u, v, weight)
    edges.push_back({0, 1, 4});
    edges.push_back({0, 2, 1});
    edges.push_back({2, 1, 2});
    edges.push_back({1, 3, 1});
    edges.push_back({2, 3, 5});
    edges.push_back({3, 4, 3});

    int source = 0;
    vector<ll> dist;
    vector<int> parent;

    bool hasNegativeCycle = bellmanFord(source, n, edges, dist, parent);

    if (hasNegativeCycle) {
        cout << "Graph contains negative weight cycle!" << endl;
    } else {
        cout << "Shortest distances from node " << source << ":\n";
        for (int i = 0; i < n; i++) {
            if (dist[i] == INF) {
                cout << "Node " << i << ": unreachable\n";
            } else {
                cout << "Node " << i << ": " << dist[i] << "\n";
            }
        }
        cout << endl;

        int target = 4;
        if (dist[target] < INF) {
            vector<int> path = get_shortest_path(target, parent);
            cout << "Shortest path to node " << target << ": ";
            for (int node : path) cout << node << " ";
            cout << "\nDistance: " << dist[target] << endl;
        } else {
            cout << "Node " << target << " is unreachable\n";
        }
    }

    return 0;
}
