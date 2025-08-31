#include <bits/stdc++.h>
using namespace std;

int main() {
    int rows = 3, cols = 3;

    // Create difference array with extra padding
    vector<vector<int>> diff(rows + 2, vector<int>(cols + 2, 0));

    // Function to add value to submatrix from (r1, c1) to (r2, c2)
    auto rangeAdd = [&](int r1, int c1, int r2, int c2, int value) {
        diff[r1][c1] += value;
        diff[r1][c2+1] -= value;
        diff[r2+1][c1] -= value;
        diff[r2+1][c2+1] += value;
    };

    // Add 5 to top-left 2x2 [rows 0-1, cols 0-1]
    rangeAdd(0, 0, 1, 1, 5);

    // Add 3 to entire matrix [rows 0-2, cols 0-2]
    rangeAdd(0, 0, 2, 2, 3);

    // Create result matrix
    vector<vector<int>> result(rows, vector<int>(cols, 0));

    // First pass: row-wise reconstruction (apply horizontal prefix sum)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j > 0) {
                diff[i][j] += diff[i][j-1];
            }
        }
    }

    // Second pass: column-wise reconstruction (apply vertical prefix sum)
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            if (i > 0) {
                diff[i][j] += diff[i-1][j];
            }
            result[i][j] = diff[i][j];
        }
    }

    // Display the final matrix
    cout << "Final matrix after range updates:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
