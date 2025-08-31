
#include <bits/stdc++.h>
using namespace std;

class MosWithCompression {
private:
    int n;
    vector<int> arr;
    vector<Query> queries;
    vector<int> ans;
    vector<int> freq;
    int distinct;

    void compress(vector<int>& a) {
        vector<int> temp = a;
        sort(temp.begin(), temp.end());
        temp.erase(unique(temp.begin(), temp.end()), temp.end());
        for (int& x : a) {
            x = lower_bound(temp.begin(), temp.end(), x) - temp.begin();
        }
    }

    void add(int index) {
        freq[arr[index]]++;
        if (freq[arr[index]] == 1) {
            distinct++;
        }
    }

    void remove(int index) {
        freq[arr[index]]--;
        if (freq[arr[index]] == 0) {
            distinct--;
        }
    }

public:
    MosWithCompression(vector<int>& array) : arr(array) {
        n = arr.size();
        compress(arr);
        blockSize = sqrt(n);
        freq.resize(n, 0);
        distinct = 0;
    }

    void addQuery(int l, int r, int idx) {
        queries.push_back({l, r, idx});
    }

    vector<int> process() {
        int q = queries.size();
        ans.resize(q);
        sort(queries.begin(), queries.end());

        int currL = 0, currR = -1;
        distinct = 0;

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
            ans[q.idx] = distinct;
        }

        return ans;
    }
};
