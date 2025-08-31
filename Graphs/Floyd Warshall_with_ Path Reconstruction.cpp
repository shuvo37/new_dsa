
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

// Floyd Warshall with path reconstruction
void floydWarshallWithPath(int n, vector<vector<ll>>& dist, vector<vector<int>>& next) {
    // Initialize next matrix
    next.assign(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] < INF && i != j) {
                next[i][j] = j;
            }
        }
    }

    // Run Floyd Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF &&
                    dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

// Reconstruct shortest path between two nodes
vector<int> getPath(int i, int j, const vector<vector<int>>& next) {
    if (next[i][j] == -1) return {};

    vector<int> path;
    path.push_back(i);
    while (i != j) {
        i = next[i][j];
        path.push_back(i);
    }
    return path;
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
    vector<vector<int>> next;

    // Initialize distance matrix
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }

    // Add edges
    dist[0][1] = 3;
    dist[0][2] = 6;
    dist[1][2] = 2;
    dist[2][3] = 4;
    dist[3][0] = 1;

    // Run Floyd Warshall with path reconstruction
    floydWarshallWithPath(n, dist, next);

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

    // Get and display some paths
    vector<int> path1 = getPath(0, 3, next);
    cout << "Path from 0 to 3: ";
    for (int node : path1) cout << node << " ";
    cout << "(Distance: " << dist[0][3] << ")" << endl;

    vector<int> path2 = getPath(1, 0, next);
    cout << "Path from 1 to 0: ";
    for (int node : path2) cout << node << " ";
    cout << "(Distance: " << dist[1][0] << ")" << endl;

    // Check for negative cycles
    if (hasNegativeCycle(n, dist)) {
        cout << "Graph contains negative cycle!" << endl;
    } else {
        cout << "No negative cycles found" << endl;
    }

    return 0;
}
