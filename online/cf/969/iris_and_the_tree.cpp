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
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)

using namespace std;

template<bool op_edges = false>
struct hld {
    vector<vector<int>> adj;
    vector<int> par;
    vector<int> sz;
    vector<int> in;
    vector<int> head;
    vector<int> d;
    vector<int> max_below;
    int t{};

    hld(int n) : adj(n), par(n), sz(n), in(n), head(n), d(n), max_below(n) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs_size(int v = 0, int p = 0) {
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

    void dfs_hld(int v = 0, int p = 0) {
        in[v] = t++;
        max_below[v] = v;
        for (int e : adj[v]) {
            if (e != p) {
                if (e == adj[v][0]) {
                    head[e] = head[v];
                } else {
                    head[e] = e;
                }
                dfs_hld(e, v);
                max_below[v] = max(max_below[v], max_below[e]);
            }
        }
    }

    template<typename F, bool enabled = !op_edges, enable_if_t<enabled, bool> = true>
    void op_node(int x, F op) {
        op(in[x]);
    }

    template<typename F, bool enabled = op_edges, enable_if_t<enabled, bool> = true>
    void op_edge(int x, int y, F op) {
        if (d[x] < d[y]) swap(x, y);
        op(in[x]);
    }

    template<typename F>
    void op_path(int x, int y, F op) {
        while (head[x] != head[y]) {
            if (d[head[x]] > d[head[y]]) swap(x, y);
            op(in[head[y]], in[y] + 1);
            y = par[head[y]];
        }
        if (d[x] > d[y]) swap(x, y);
        op(in[x] + (op_edges ? 1 : 0), in[y] + 1);
    }

    template<typename F>
    void op_subtree(int x, F op) { 
        op(in[x] + (op_edges ? 1 : 0), in[x] + sz[x]);
    }
};

template<typename T>
struct BIT {
    int n;
    vector<T> bit;

    BIT(int n) : n(n), bit(n + 1) {}

    void upd(int x, int v) {
        x++;
        while (x <= n) {
            bit[x] += v;
            x += x & -x;
        }
    }

    T qry(int r) {
        T res{};
        while (r > 0) {
            res += bit[r];
            r -= r & -r;
        }
        return res;
    }

    T qry(int l, int r) {
        return qry(r) - qry(l);
    }
};

void solve() {
    int n;
    ll w;
    cin >> n >> w;

    hld<true> t(n);
    rep(i, 1, n) {
        int p;
        cin >> p;
        p--;
        t.add_edge(p, i);
    }

    t.dfs_size();
    t.dfs_hld();

    BIT<int> unpresent(n);
    BIT<ll> fixed_sum(n);

    rep(i, 1, n) {
        t.op_edge(i, t.par[i], [&](int x) { unpresent.upd(x, 1); });
    }

    ll unfixed = w;
    ll ans = w * n;
    int fixed_path = 0;

    rep(_, 0, n-1) {
        int x;
        ll y;
        cin >> x >> y;
        x--;

        t.op_edge(x, t.par[x], [&](int z) { unpresent.upd(z, -1); });

        auto proc = [&](int u, int v) {
            int unpresent_on_path = 0;
            t.op_path(u, v, [&](int l, int r) { unpresent_on_path += unpresent.qry(l, r); });
            if (unpresent_on_path == 0) {
                fixed_path++;
                ans -= unfixed;
            }
        };

        unfixed -= y;
        ans -= (n - fixed_path - 2) * y;

        proc(x-1, x);
        int nxt = t.max_below[x];
        proc(nxt, (nxt+1)%n);

        cout << ans << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
