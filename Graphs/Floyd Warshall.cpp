#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

// Floyd Warshall algorithm for all-pairs shortest paths
void floydWarshall(int n, vector<vector<ll>>& dist) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

// Function to detect negative cycles
bool hasNegativeCycle(int n, const vector<vector<ll>>& dist) {
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            return true;
        }
    }
    return false;
}

int main() {
    int n = 4;
    vector<vector<ll>> dist(n, vector<ll>(n, INF));

    // Initialize distance matrix (diagonal = 0)
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }

    // Add edges (directed graph)
    dist[0][1] = 5;
    dist[0][3] = 10;
    dist[1][2] = 3;
    dist[2][3] = 1;
    dist[3][1] = 2;

    // Run Floyd Warshall
    floydWarshall(n, dist);

    cout << "All-pairs shortest distances:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) {
                cout << "INF\t";
            } else {
                cout << dist[i][j] << "\t";
            }
        }
        cout << endl;
    }
    cout << endl;

    // Check for negative cycles
    if (hasNegativeCycle(n, dist)) {
        cout << "Graph contains negative cycle!" << endl;
    } else {
        cout << "No negative cycles found" << endl;
    }

    return 0;
}
