#include <bits/stdc++.h>
using namespace std;

// Precompute the 2D prefix sum array
vector<vector<int>> buildPrefixSum(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<vector<int>> prefix(rows + 1, vector<int>(cols + 1, 0));

    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            prefix[i][j] = matrix[i-1][j-1]
                         + prefix[i-1][j]
                         + prefix[i][j-1]
                         - prefix[i-1][j-1];
        }
    }

    return prefix;
}

// Query the sum of submatrix from (r1, c1) to (r2, c2) [0-indexed]
int querySubmatrix(const vector<vector<int>>& prefix,
                  int r1, int c1, int r2, int c2) {
    return prefix[r2+1][c2+1]
         - prefix[r1][c2+1]
         - prefix[r2+1][c1]
         + prefix[r1][c1];
}

int main() {
    // Example matrix
    vector<vector<int>> matrix = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    // Build prefix sum array
    vector<vector<int>> prefix = buildPrefixSum(matrix);

    // Query examples
    cout << "Sum of entire matrix: "
         << querySubmatrix(prefix, 0, 0, 3, 3) << endl;

    cout << "Sum of top-left 2x2: "
         << querySubmatrix(prefix, 0, 0, 1, 1) << endl;

    cout << "Sum of center 2x2: "
         << querySubmatrix(prefix, 1, 1, 2, 2) << endl;

    return 0;
}
