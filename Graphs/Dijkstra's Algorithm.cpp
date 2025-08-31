#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, int> pli; // (distance, node)

const ll INF = 1e18;

// Dijkstra's algorithm to find shortest paths from source to all nodes
vector<ll> dijkstra(int source, vector<vector<pair<int, int>>>& adj)
{
    int n = adj.size();
    vector<ll> dist(n, INF);
    priority_queue<pli, vector<pli>, greater<pli>> pq; // min-heap

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty())
    {
        auto x = pq.top();
        ll d = x.first;
        int u = x.second;
        pq.pop();

        // Skip if we found a better path already
        if (d > dist[u]) continue;

        for (auto x : adj[u])
        {
            int v = x.first;
            ll weight = x.second;
            ll new_dist = dist[u] + weight;
            if (new_dist < dist[v])
            {
                dist[v] = new_dist;
                pq.push({new_dist, v});
            }
        }
    }

    return dist;
}

// Dijkstra with path reconstruction
vector<ll> dijkstra_with_path(int source, vector<vector<pair<int, int>>>& adj, vector<int>& parent)
{
    int n = adj.size();
    vector<ll> dist(n, INF);
    parent.assign(n, -1);
    priority_queue<pli, vector<pli>, greater<pli>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty())
    {
        auto x = pq.top();
        ll d = x.first;
        int u = x.second;
        pq.pop(); // This was missing!

        if (d > dist[u]) continue;

        for (auto x : adj[u])
        {
            int v = x.first;
            ll weight = x.second;
            ll new_dist = dist[u] + weight;
            if (new_dist < dist[v])
            {
                dist[v] = new_dist;
                parent[v] = u;
                pq.push({new_dist, v});
            }
        }
    }

    return dist;
}

// Reconstruct shortest path from source to target
vector<int> get_shortest_path(int target, const vector<int>& parent)
{
    vector<int> path;
    for (int v = target; v != -1; v = parent[v])
    {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

int main()
{
    int n = 5; // Number of nodes
    vector<vector<pair<int, int>>> adj(n);

    // Build weighted graph (node, weight)
    adj[0] = {{1, 4}, {2, 1}};
    adj[1] = {{3, 1}};
    adj[2] = {{1, 2}, {3, 5}};
    adj[3] = {{4, 3}};
    adj[4] = {};

    int source = 0;

    // Standard Dijkstra
    vector<ll> dist = dijkstra(source, adj);

    cout << "Shortest distances from node " << source << ":\n";
    for (int i = 0; i < n; i++)
    {
        if (dist[i] == INF)
        {
            cout << "Node " << i << ": unreachable\n";
        }
        else
        {
            cout << "Node " << i << ": " << dist[i] << "\n";
        }
    }
    cout << endl;

    // Dijkstra with path reconstruction
    vector<int> parent;
    dist = dijkstra_with_path(source, adj, parent);

    int target = 4;
    if (dist[target] < INF)
    {
        vector<int> path = get_shortest_path(target, parent);
        cout << "Shortest path to node " << target << ": ";
        for (int node : path) cout << node << " ";
        cout << "\nDistance: " << dist[target] << endl;
    }
    else
    {
        cout << "Node " << target << " is unreachable\n";
    }

    return 0;
}
