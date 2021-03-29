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
#include <cstdio>
#include <cstring>
#include <functional>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200010

using namespace std;

int n, q;
int val[MAXN];
vector<int> adj[MAXN];

struct st {
    int st[4 * MAXN];

    void upd(int x, int y, int v = 1, int l = 0, int r = n - 1) {
        if (l == r) {
            st[v] = y;
        } else {
            int m = (l + r) / 2;
            if (x <= m) {
                upd(x, y, 2 * v, l, m);
            } else {
                upd(x, y, 2 * v + 1, m + 1, r);
            }
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }

    int qry(int x, int y, int v = 1, int l = 0, int r = n - 1) {
        if (x <= l && r <= y) {
            return st[v];
        } else if (x > r || y < l) {
            return 0;
        } else {
            int m = (l + r) / 2;
            return max(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m + 1, r));
        }
    }
} st;

int par[MAXN];
int in[MAXN];
int sz[MAXN];
int head[MAXN];
int d[MAXN];
int t;

void dfs_size(int v, int p) {
    sz[v] = 1;
    for (int &e : adj[v]) {
        if (e != p) {
            d[e] = d[v] + 1;
            par[e] = v;
            dfs_size(e, v);
            sz[v] += sz[e];
            if (sz[e] > sz[adj[v][0]] || adj[v][0] == p) swap(e, adj[v][0]);
        }
    }
}

void dfs_hld(int v, int p) {
    in[v] = t++;
    for (int e : adj[v]) {
        if (e != p) {
            head[e] = (e == adj[v][0]) ? head[v] : e;
            dfs_hld(e, v);
        }
    }
}

void op_path(int x, int y, function<void(int,int)> op) {
    while (head[x] != head[y]) {
        if (d[head[x]] > d[head[y]]) swap(x, y);
        op(in[head[y]], in[y]);
        y = par[head[y]];
    }
    if (d[x] > d[y]) swap(x, y);
    op(in[x], in[y]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs_size(0, 0);
    dfs_hld(0, 0);

    for (int i = 0; i < n; i++) {
        st.upd(in[i], val[i]);
    }

    while (q--) {
        int t, a, b; 
        cin >> t >> a >> b;

        if (t == 1) {
            st.upd(in[a - 1], b);
        } else {
            int res = 0;
            op_path(a - 1, b - 1, [&res](int x, int y) { res = max(res, st.qry(x, y)); });
            cout << res << ' ';
        }
    }
    cout << '\n';

    return 0;
}
