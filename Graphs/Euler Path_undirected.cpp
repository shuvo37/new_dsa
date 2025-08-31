#include <bits/stdc++.h>
using namespace std;

vector<int> eulerPath(int n, vector<vector<int>>& graph) {
    vector<int> deg(n, 0);
    for (int i = 0; i < n; i++) {
        deg[i] = graph[i].size();
    }

    // Check connectivity and odd degrees
    int odd = 0, start = 0;
    for (int i = 0; i < n; i++) {
        if (deg[i] % 2) odd++, start = i;
    }
    if (odd != 0 && odd != 2) return {};

    stack<int> st;
    vector<int> path;
    st.push(start);

    while (!st.empty()) {
        int u = st.top();
        if (!graph[u].empty()) {
            int v = graph[u].back();
            graph[u].pop_back();
            for (auto it = graph[v].begin(); it != graph[v].end(); it++) {
                if (*it == u) {
                    graph[v].erase(it);
                    break;
                }
            }
            st.push(v);
        } else {
            path.push_back(u);
            st.pop();
        }
    }

    reverse(path.begin(), path.end());
    return path;
}
