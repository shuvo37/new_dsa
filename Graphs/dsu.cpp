#include <bits/stdc++.h>
using namespace std;

class DSU {
private:
    vector<int> parent;
    vector<int> rank;
    vector<int> size;
    int components;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        size.resize(n, 1);
        components = n;

        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Union by rank
    bool unionByRank(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return false;

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }

        components--;
        return true;
    }

    // Union by size
    bool unionBySize(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return false;

        if (size[rootX] < size[rootY]) {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        } else {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }

        components--;
        return true;
    }

    // Check if two elements are in same set
    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    // Get number of connected components
    int countComponents() {  // Renamed from getComponents()
        return components;
    }

    // Get size of component containing x
    int getSize(int x) {
        int root = find(x);
        return size[root];
    }

    // Get the root nodes of all components
    vector<int> getRoots() {
        vector<int> roots;
        for (int i = 0; i < parent.size(); i++) {
            if (parent[i] == i) {
                roots.push_back(i);
            }
        }
        return roots;
    }

    // Get all components grouped by root
    vector<vector<int>> getComponents() {  // Keep this name
        int n = parent.size();
        vector<vector<int>> comps(n);
        for (int i = 0; i < n; i++) {
            comps[find(i)].push_back(i);
        }

        vector<vector<int>> result;
        for (int i = 0; i < n; i++) {
            if (!comps[i].empty()) {
                result.push_back(comps[i]);
            }
        }
        return result;
    }
};

// Example usage
int main() {
    int n = 5;
    DSU dsu(n);

    cout << "Initial components: " << dsu.countComponents() << endl;  // Updated function name

    // Union operations
    dsu.unionByRank(0, 1);
    dsu.unionByRank(2, 3);
    dsu.unionBySize(3, 4);

    cout << "After unions - components: " << dsu.countComponents() << endl;  // Updated function name
    cout << "Size of component containing 0: " << dsu.getSize(0) << endl;
    cout << "Size of component containing 2: " << dsu.getSize(2) << endl;

    cout << "Are 0 and 1 connected? " << (dsu.connected(0, 1) ? "Yes" : "No") << endl;
    cout << "Are 0 and 2 connected? " << (dsu.connected(0, 2) ? "Yes" : "No") << endl;

    // Get all components
    vector<vector<int>> components = dsu.getComponents();
    cout << "\nAll components:" << endl;
    for (int i = 0; i < components.size(); i++) {
        cout << "Component " << i << ": ";
        for (int node : components[i]) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
