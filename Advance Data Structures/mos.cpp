
#include <bits/stdc++.h>
using namespace std;

int blockSize;

struct Query {
    int l, r, idx;
    bool operator<(const Query& other) const {
        if (l / blockSize != other.l / blockSize)
            return l < other.l;
        return (l / blockSize) & 1 ? r < other.r : r > other.r;
    }
};

class MosRangeSum {
private:
    int n;
    vector<int> arr;
    vector<Query> queries;
    vector<long long> ans;
    long long currSum;

    void add(int index) {
        currSum += arr[index];
    }

    void remove(int index) {
        currSum -= arr[index];
    }

public:
    MosRangeSum(const vector<int>& array) : arr(array) {
        n = arr.size();
        blockSize = sqrt(n);
        currSum = 0;
    }

    void addQuery(int l, int r, int idx) {
        queries.push_back({l, r, idx});
    }

    vector<long long> process() {
        int q = queries.size();
        ans.resize(q);
        sort(queries.begin(), queries.end());

        int currL = 0, currR = -1;
        currSum = 0;

        for (const Query& q : queries) {
            while (currL > q.l) {
                currL--;
                add(currL);
            }
            while (currR < q.r) {
                currR++;
                add(currR);
            }
            while (currL < q.l) {
                remove(currL);
                currL++;
            }
            while (currR > q.r) {
                remove(currR);
                currR--;
            }
            ans[q.idx] = currSum;
        }

        return ans;
    }
};

class MosRangeFreq {
private:
    int n;
    vector<int> arr;
    vector<Query> queries;
    vector<int> ans;
    vector<int> freq;
    int target;

    void add(int index) {
        freq[arr[index]]++;
    }

    void remove(int index) {
        freq[arr[index]]--;
    }

public:
    MosRangeFreq(const vector<int>& array, int maxVal, int targetValue)
        : arr(array), target(targetValue) {
        n = arr.size();
        blockSize = sqrt(n);
        freq.resize(maxVal + 1, 0);
    }

    void addQuery(int l, int r, int idx) {
        queries.push_back({l, r, idx});
    }

    vector<int> process() {
        int q = queries.size();
        ans.resize(q);
        sort(queries.begin(), queries.end());

        int currL = 0, currR = -1;

        for (const Query& q : queries) {
            while (currL > q.l) {
                currL--;
                add(currL);
            }
            while (currR < q.r) {
                currR++;
                add(currR);
            }
            while (currL < q.l) {
                remove(currL);
                currL++;
            }
            while (currR > q.r) {
                remove(currR);
                currR--;
            }
            ans[q.idx] = freq[target];
        }

        return ans;
    }
};
