// :pray: :fishy:

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n, q;
vector<segtree> st;

class segtree {
    int n;
    vector<int> arr;
    vector<int> tree;

    segtree(int n, vector<int> &arr) {
        this->n = n;
        this->arr = {0};
        for (int i = 0; i < n; i++) {
            this->arr.push_back(arr[i]);
        }

        tree = vector<int>(4 * n + 4);
        build(1, 1, n);
    }

    void build(int node, int left, int right) {
        if (left == right) {
            tree[node] = arr[left];
        } else {
            int mid = (left + right) / 2;
            
            build(2 * node, left, mid);
            build(2 * node + 1, mid + 1, right);
            
            tree[node] = min(tree[2 * node], tree[2 * node + 1]);
        }
    }

    void update(int node, int left, int right, int index, int value) {
        if (left == right) {
            arr[index] = value;
            tree[node] = value;
        } else {
            int mid = (left + right) / 2;
            if (index <= mid) {
                update(2 * node, left, mid, index, value);
            } else {
                update(2 * node + 1, mid + 1, right, index, value);
            }
            
            tree[node] = min(tree[2 * node], tree[2 * node + 1]);
        }
    }

    int query(int node, int left, int right, int l, int r) {
        if (r < left || l > right) {
            return INF + 1;
        }
        
        if (l <= left && r >= right) {
            return tree[node];
        }
        
        int mid = (left + right) / 2;
        int res1 = query(2 * node, left, mid, l, r);
        int res2 = query(2 * node + 1, mid + 1, right, l, r);
        
        return min(res1, res2);
    }
};

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    return 0;
}
