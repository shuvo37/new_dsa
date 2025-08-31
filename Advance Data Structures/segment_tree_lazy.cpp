
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;
int n;
int tree[4 * MAXN];
int lazy[4 * MAXN];
int arr[MAXN];

void build(int node, int start, int end) {
    lazy[node] = 0;
    if (start == end) {
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

void push(int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void updateRange(int node, int start, int end, int l, int r, int val) {
    push(node, start, end);
    if (start > r || end < l) return;

    if (l <= start && end <= r) {
        lazy[node] += val;
        push(node, start, end);
        return;
    }

    int mid = (start + end) / 2;
    updateRange(2 * node, start, mid, l, r, val);
    updateRange(2 * node + 1, mid + 1, end, l, r, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

int queryRange(int node, int start, int end, int l, int r) {
    push(node, start, end);
    if (start > r || end < l) return 0;
    if (l <= start && end <= r) return tree[node];

    int mid = (start + end) / 2;
    int left_sum = queryRange(2 * node, start, mid, l, r);
    int right_sum = queryRange(2 * node + 1, mid + 1, end, l, r);
    return left_sum + right_sum;
}

int main() {
    // Example array
    n = 5;
    arr[0] = 1; arr[1] = 3; arr[2] = 5; arr[3] = 7; arr[4] = 9;

    // Build segment tree
    build(1, 0, n - 1);

    cout << "Initial sum [0, 4]: " << queryRange(1, 0, n - 1, 0, 4) << endl; // 25

    // Add 2 to range [1, 3]
    updateRange(1, 0, n - 1, 1, 3, 2);
    cout << "After adding 2 to [1, 3]: " << queryRange(1, 0, n - 1, 0, 4) << endl; // 25 + 2*3 = 31

    // Add 5 to range [0, 2]
    updateRange(1, 0, n - 1, 0, 2, 5);
    cout << "After adding 5 to [0, 2]: " << queryRange(1, 0, n - 1, 0, 4) << endl; // 31 + 5*3 = 46

    return 0;
}
