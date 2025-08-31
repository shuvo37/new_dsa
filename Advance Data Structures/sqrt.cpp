#include <bits/stdc++.h>
using namespace std;

class SqrtDecompositionAdvanced {
private:
    int n, blockSize, blockCount;
    vector<int> arr;
    vector<int> blockSum;
    vector<int> blockMin;
    vector<int> blockMax;

public:
    SqrtDecompositionAdvanced(const vector<int>& input) {
        arr = input;
        n = arr.size();
        blockSize = sqrt(n);
        blockCount = (n + blockSize - 1) / blockSize;

        blockSum.resize(blockCount, 0);
        blockMin.resize(blockCount, INT_MAX);
        blockMax.resize(blockCount, INT_MIN);

        // Precompute block statistics
        for (int i = 0; i < n; i++) {
            int blockIdx = i / blockSize;
            blockSum[blockIdx] += arr[i];
            blockMin[blockIdx] = min(blockMin[blockIdx], arr[i]);
            blockMax[blockIdx] = max(blockMax[blockIdx], arr[i]);
        }
    }

    void update(int index, int value) {
        int blockIdx = index / blockSize;
        int oldValue = arr[index];

        // Update block statistics
        blockSum[blockIdx] += value - oldValue;
        arr[index] = value;

        // Recompute min and max for the block if needed
        if (value < blockMin[blockIdx] || oldValue == blockMin[blockIdx] ||
            value > blockMax[blockIdx] || oldValue == blockMax[blockIdx]) {

            int start = blockIdx * blockSize;
            int end = min(start + blockSize, n);
            blockMin[blockIdx] = INT_MAX;
            blockMax[blockIdx] = INT_MIN;

            for (int i = start; i < end; i++) {
                blockMin[blockIdx] = min(blockMin[blockIdx], arr[i]);
                blockMax[blockIdx] = max(blockMax[blockIdx], arr[i]);
            }
        }
    }

    int querySum(int l, int r) {
        int sum = 0;
        int startBlock = l / blockSize;
        int endBlock = r / blockSize;

        if (startBlock == endBlock) {
            for (int i = l; i <= r; i++) sum += arr[i];
        } else {
            for (int i = l; i < (startBlock + 1) * blockSize; i++) sum += arr[i];
            for (int i = startBlock + 1; i < endBlock; i++) sum += blockSum[i];
            for (int i = endBlock * blockSize; i <= r; i++) sum += arr[i];
        }
        return sum;
    }

    int queryMin(int l, int r) {
        int minVal = INT_MAX;
        int startBlock = l / blockSize;
        int endBlock = r / blockSize;

        if (startBlock == endBlock) {
            for (int i = l; i <= r; i++) minVal = min(minVal, arr[i]);
        } else {
            for (int i = l; i < (startBlock + 1) * blockSize; i++) minVal = min(minVal, arr[i]);
            for (int i = startBlock + 1; i < endBlock; i++) minVal = min(minVal, blockMin[i]);
            for (int i = endBlock * blockSize; i <= r; i++) minVal = min(minVal, arr[i]);
        }
        return minVal;
    }

    int queryMax(int l, int r) {
        int maxVal = INT_MIN;
        int startBlock = l / blockSize;
        int endBlock = r / blockSize;

        if (startBlock == endBlock) {
            for (int i = l; i <= r; i++) maxVal = max(maxVal, arr[i]);
        } else {
            for (int i = l; i < (startBlock + 1) * blockSize; i++) maxVal = max(maxVal, arr[i]);
            for (int i = startBlock + 1; i < endBlock; i++) maxVal = max(maxVal, blockMax[i]);
            for (int i = endBlock * blockSize; i <= r; i++) maxVal = max(maxVal, arr[i]);
        }
        return maxVal;
    }
};



