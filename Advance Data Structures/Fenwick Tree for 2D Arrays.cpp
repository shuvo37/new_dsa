
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100;
int n, m;
int fenw[MAXN][MAXN];

void update_2d(int x, int y, int delta) {
    for (int i = x; i < n; i = i | (i + 1)) {
        for (int j = y; j < m; j = j | (j + 1)) {
            fenw[i][j] += delta;
        }
    }
}

int query_2d(int x, int y) {
    int sum = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
            sum += fenw[i][j];
        }
    }
    return sum;
}

int range_query_2d(int x1, int y1, int x2, int y2) {
    return query_2d(x2, y2) - query_2d(x1 - 1, y2) - query_2d(x2, y1 - 1) + query_2d(x1 - 1, y1 - 1);
}

void build_2d(const vector<vector<int>>& grid) {
    n = grid.size();
    m = grid[0].size();
    memset(fenw, 0, sizeof(fenw));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            update_2d(i, j, grid[i][j]);
        }
    }
}

int main() {
    vector<vector<int>> grid = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    build_2d(grid);

    cout << "Sum of submatrix [0,0] to [1,1]: " << range_query_2d(0, 0, 1, 1) << endl; // 1+2+4+5 = 12
    cout << "Sum of submatrix [1,1] to [2,2]: " << range_query_2d(1, 1, 2, 2) << endl; // 5+6+8+9 = 28

    update_2d(1, 1, 10); // Add 10 to grid[1][1] (5 → 15)
    cout << "After update - Sum of submatrix [1,1] to [2,2]: " << range_query_2d(1, 1, 2, 2) << endl; // 15+6+8+9 = 38

    return 0;
}
