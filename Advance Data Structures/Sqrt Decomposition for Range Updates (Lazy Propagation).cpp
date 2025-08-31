#include <bits/stdc++.h>
using namespace std;

class SqrtDecompositionLazy {
private:
    int n, blockSize, blockCount;
    vector<int> arr;
    vector<int> blockSum;
    vector<int> lazy;

public:
    SqrtDecompositionLazy(const vector<int>& input) {
        arr = input;
        n = arr.size();
        blockSize = sqrt(n);
        blockCount = (n + blockSize - 1) / blockSize;

        blockSum.resize(blockCount, 0);
        lazy.resize(blockCount, 0);

        for (int i = 0; i < n; i++) {
            blockSum[i / blockSize] += arr[i];
        }
    }

    void rangeUpdate(int l, int r, int value) {
        int startBlock = l / blockSize;
        int endBlock = r / blockSize;

        if (startBlock == endBlock) {
            for (int i = l; i <= r; i++) {
                arr[i] += value;
                blockSum[startBlock] += value;
            }
        } else {
            // Left partial block
            for (int i = l; i < (startBlock + 1) * blockSize; i++) {
                arr[i] += value;
                blockSum[startBlock] += value;
            }

            // Middle complete blocks - apply lazy update
            for (int i = startBlock + 1; i < endBlock; i++) {
                lazy[i] += value;
                blockSum[i] += value * blockSize;
            }

            // Right partial block
            for (int i = endBlock * blockSize; i <= r; i++) {
                arr[i] += value;
                blockSum[endBlock] += value;
            }
        }
    }

    int query(int l, int r) {
        int sum = 0;
        int startBlock = l / blockSize;
        int endBlock = r / blockSize;

        if (startBlock == endBlock) {
            for (int i = l; i <= r; i++) {
                sum += arr[i] + lazy[startBlock];
            }
        } else {
            // Left partial block
            for (int i = l; i < (startBlock + 1) * blockSize; i++) {
                sum += arr[i] + lazy[startBlock];
            }

            // Middle complete blocks
            for (int i = startBlock + 1; i < endBlock; i++) {
                sum += blockSum[i];
            }

            // Right partial block
            for (int i = endBlock * blockSize; i <= r; i++) {
                sum += arr[i] + lazy[endBlock];
            }
        }

        return sum;
    }
};
