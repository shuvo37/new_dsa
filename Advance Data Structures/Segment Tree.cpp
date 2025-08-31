#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;
int n;
int tree[4 * MAXN];
int arr[MAXN];

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node] = val;
        arr[idx] = val;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

int query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return 0;
    }
    if (l <= start && end <= r) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    int left_sum = query(2 * node, start, mid, l, r);
    int right_sum = query(2 * node + 1, mid + 1, end, l, r);
    return left_sum + right_sum;
}

int main() {
    // Example array
    n = 5;
    arr[0] = 1; arr[1] = 3; arr[2] = 5; arr[3] = 7; arr[4] = 9;

    // Build segment tree
    build(1, 0, n - 1);

    // Test queries
    cout << "Sum [0, 2]: " << query(1, 0, n - 1, 0, 2) << endl; // 1+3+5 = 9
    cout << "Sum [1, 3]: " << query(1, 0, n - 1, 1, 3) << endl; // 3+5+7 = 15
    cout << "Sum [2, 4]: " << query(1, 0, n - 1, 2, 4) << endl; // 5+7+9 = 21

    // Update and test
    update(1, 0, n - 1, 2, 10); // Change arr[2] from 5 to 10
    cout << "After update - Sum [0, 2]: " << query(1, 0, n - 1, 0, 2) << endl; // 1+3+10 = 14
    cout << "After update - Sum [1, 3]: " << query(1, 0, n - 1, 1, 3) << endl; // 3+10+7 = 20

    return 0;
}
