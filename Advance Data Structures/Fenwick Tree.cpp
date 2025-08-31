#include <bits/stdc++.h>
using namespace std;

class FenwickTree {
private:
    int n;
    vector<int> tree;

public:
    FenwickTree(int size) : n(size), tree(size, 0) {}

    void update(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1)) {
            tree[idx] += delta;
        }
    }

    int query(int idx) {
        int sum = 0;
        for (; idx >= 0; idx = (idx & (idx + 1)) - 1) {
            sum += tree[idx];
        }
        return sum;
    }

    int range_query(int l, int r) {
        if (l == 0) return query(r);
        return query(r) - query(l - 1);
    }

    void build(const vector<int>& arr) {
        for (int i = 0; i < n; i++) {
            update(i, arr[i]);
        }
    }
};

int main() {
    vector<int> arr = {2, 4, 6, 8, 10};
    FenwickTree ft(arr.size());
    ft.build(arr);

    cout << "Range [1, 3]: " << ft.range_query(1, 3) << endl; // 4+6+8 = 18
    cout << "Range [0, 4]: " << ft.range_query(0, 4) << endl; // 2+4+6+8+10 = 30

    ft.update(2, 5); // Add 5 to index 2 (6 → 11)
    cout << "After update - Range [1, 3]: " << ft.range_query(1, 3) << endl; // 4+11+8 = 23

    return 0;
}
