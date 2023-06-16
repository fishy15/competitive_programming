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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n, q;
int arr[MAXN];
int st[4 * MAXN];
int par[MAXN];
int sz[MAXN];
int in[MAXN];
int head[MAXN];
int d[MAXN];
vector<int> adj[MAXN];
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
            if (e == adj[v][0]) {
                head[e] = head[v];
            } else {
                head[e] = e;
            }
            dfs_hld(e, v);
        }
    }
}

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
        st[v] = st[2 * v] ^ st[2 * v + 1];
    }
}

int qry(int x, int y, int v = 1, int l = 0, int r = n - 1) {
    if (x <= l && r <= y) {
        return st[v];
    } else if (r < x || l > y) {
        return 0;
    } else {
        int m = (l + r) / 2;
        return qry(x, y, 2 * v, l, m) ^ qry(x, y, 2 * v + 1, m + 1, r);
    }
}

void qry_path(int x, int y, function<void(int,int)> op) {
    while (head[x] != head[y]) {
        if (d[head[x]] > d[head[y]]) swap(x, y);
        op(in[head[y]], in[y]);
        y = par[head[y]];
    }
    if (d[x] > d[y]) swap(x, y);
    op(in[x], in[y]);
}

int main() {
    ifstream fin("cowland.in");
    ofstream fout("cowland.out");

    fin >> n >> q;
    for (int i = 0; i < n; i++) {
        fin >> arr[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b; fin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs_size(0, 0);
    dfs_hld(0, 0);

    for (int i = 0; i < n; i++) {
        upd(in[i], arr[i]);
    }

    for (int i = 0; i < q; i++) {
        int tt; fin >> tt;
        if (tt == 1) {
            int x, v; fin >> x >> v;
            x--;
            upd(in[x], v);
        } else {
            int x, y; fin >> x >> y;
            x--; y--;
            int res = 0;
            qry_path(x, y, [&res](int x, int y) { res ^= qry(x, y); });
            fout << res << '\n';
        }
    }

    return 0;
}
