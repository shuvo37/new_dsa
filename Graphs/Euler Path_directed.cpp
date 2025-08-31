
#include <bits/stdc++.h>
using namespace std;

vector<int> directedEulerCircuit(int n, vector<vector<int>>& graph) {
    vector<int> inDeg(n, 0), outDeg(n, 0);

    // Calculate degrees
    for (int u = 0; u < n; u++) {
        for (int v : graph[u]) {
            outDeg[u]++;
            inDeg[v]++;
        }
    }

    // Check degree condition
    for (int i = 0; i < n; i++) {
        if (inDeg[i] != outDeg[i]) {
            return {};
        }
    }

    // Hierholzer's algorithm
    vector<vector<int>> temp = graph;
    stack<int> st;
    vector<int> circuit;

    int start = 0;
    for (int i = 0; i < n; i++) {
        if (outDeg[i] > 0) {
            start = i;
            break;
        }
    }

    st.push(start);

    while (!st.empty()) {
        int u = st.top();
        if (!temp[u].empty()) {
            int v = temp[u].back();
            temp[u].pop_back();
            st.push(v);
        } else {
            circuit.push_back(u);
            st.pop();
        }
    }

    reverse(circuit.begin(), circuit.end());
    return circuit;
}
