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
#define sz(x) (int)(x).size()

using namespace std;

struct tree {
    vector<vector<int>> adj;
    vector<map<int, int>> cnt;
    vector<int> w, c;
    ll cost = 0;

    tree(int n, const vector<int> &_w, const vector<int> &_c) : adj(n), cnt(n), w(_w), c(_c), cost{} {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs_floor(int v, int p, int par_col) {
        if (c[v] == 0) {
            c[v] = par_col;
        }

        for (auto e : adj[v]) {
            if (e != p) {
                dfs_floor(e, v, c[v]);
            }
        }
    }

    void dfs(int v, int p) {
        map<int, int> dup;
        for (auto e : adj[v]) {
            if (e != p) {
                dfs(e, v);
                if (sz(cnt[e]) > sz(cnt[v])) {
                    swap(cnt[e], cnt[v]);
                }
                for (auto [x, _] : cnt[e]) {
                    if (cnt[v].count(x)) {
                        dup[x] = 1;
                    } else {
                        cnt[v][x] = 1;
                    }
                }
            }
        }

        if (c[v] == 0) {
            if (!dup.empty()) {
                c[v] = begin(dup)->first;
            } else if (!cnt[v].empty()) {
                c[v] = begin(cnt[v])->first;
            }
        }

        if (sz(dup) >= 2 || (sz(dup) == 1 && c[v] != begin(dup)->first)) {
            cost += w[v];
        }

        if (c[v] != 0) {
            cnt[v][c[v]] = 1;
        }
    }
};

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> w(n), c(n);
    rep(i, 0, n) {
        cin >> w[i];
    }
    rep(i, 0, n) {
        cin >> c[i];
    }

    tree t(n, w, c);

    rep(i, 0, n-1) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        t.add_edge(u, v);
    }

    t.dfs(0, 0);
    t.dfs_floor(0, 0, 1);

    cout << t.cost << '\n';
    for (auto x : t.c) cout << x << ' ';
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
