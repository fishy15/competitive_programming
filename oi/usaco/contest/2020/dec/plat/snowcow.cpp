// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll unsigned long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n, q;
int t = 1;

vector<vector<int>> tree;
vector<int> in;
vector<int> out;

vector<ll> segtree;
vector<ll> lazy;

map<int, set<int>> history;

// lca stuff
void dfs(int node, int p) {
    in[node] = t;
    t++;

    for (int node2 : tree[node]) {
        if (node2 != p) {
            dfs(node2, node);
        }
    }

    out[node] = t;
    t++;
}

bool is_ancestor(int p, int c) {
    return in[p] <= in[c] && out[p] >= out[c];
}

// segtree stuff
void push(int node, int l, int r) {
    lazy[2 * node] += lazy[node];
    lazy[2 * node + 1] += lazy[node];
    segtree[node] += (r - l + 1) * lazy[node];
    lazy[node] = 0;
}

void update(int node, int idx, int d, int l = 1, int r = 2 * n + 1) {
    if (in[idx] <= l && r <= out[idx]) {
        lazy[node] += d;
    } else if (l <= out[idx] && r >= in[idx]) {
        push(node, l, r);
        int mid = l + (r - l) / 2;
        update(2 * node, idx, d, l, mid);
        update(2 * node + 1, idx, d, mid + 1, r);
        segtree[node] = segtree[2 * node] + segtree[2 * node + 1] + lazy[2 * node] * (mid - l + 1) + lazy[2 * node + 1] * (r - mid);
    }
}

ll query(int node, int idx, int l = 1, int r = 2 * n + 1) {
    if (in[idx] <= l && r <= out[idx]) {
        return segtree[node] + (r - l + 1) * lazy[node];
    }

    if (r < in[idx] || l > out[idx]) return 0;

    push(node, l, r);
    int mid = l + (r - l) / 2;
    return query(2 * node, idx, l, mid) + query(2 * node + 1, idx, mid + 1, r);
}

int main() {
    ifstream fin("snowcow.in");
    ofstream fout("snowcow.out");

    fin >> n >> q;
    tree = vector<vector<int>>(n + 1);
    in = vector<int>(n + 1);
    out = vector<int>(n + 1);
    segtree = vector<ll>(9 * n);
    lazy = vector<ll>(9 * n);

    for (int i = 0; i < n - 1; i++) {
        int a, b; fin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(1, 1);

    for (int i = 0; i < q; i++) {
        int c; fin >> c;
        if (c == 1) {
            int x, cc; fin >> x >> cc;
            bool upd = true;
            for (int y : history[cc]) {
                if (is_ancestor(x, y)) {
                    update(1, y, -1);
                    history[cc].erase(y);
                } else if (is_ancestor(y, x)) {
                    upd = false;
                }
            }
            if (upd) {
                update(1, x, 1);
                history[cc].insert(x);
            }
        } else {
            int x; fin >> x;
            fout << query(1, x) / 2 << '\n';
        }
    }

    return 0;
}
