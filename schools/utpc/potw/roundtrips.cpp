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

// change if necessary
#define MAXN 1000000

using namespace std;
template<typename F>
struct y_combinator_result {
    F f;
    template<typename T> explicit y_combinator_result(T &&f) : f(forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(forward<F>(f));
}

struct SCC {
    int sz;
    vector<vector<int>> adj;
    vector<vector<int>> radj;
    vector<int> comp;
    vector<bool> vis;
    vector<int> ord;
    vector<int> cur_comp;

    SCC(int m) : sz(m), adj(m), radj(m), comp(m), vis(m) {}

    void add_edge(int a, int b) {
        adj[a].push_back(b);
        radj[b].push_back(a);
    }

    void dfs_ord(int v) {
        vis[v] = true;
        for (int e : adj[v]) {
            if (!vis[e]) {
                dfs_ord(e);
            }
        }
        ord.push_back(v);
    }

    void dfs_scc(int v) {
        vis[v] = true;
        cur_comp.push_back(v);
        for (int e : radj[v]) {
            if (!vis[e]) {
                dfs_scc(e);
            }
        }
    }

    void find_scc() {
        for (int i = 0; i < sz; i++) {
            if (!vis[i]) {
                dfs_ord(i);
            }
        }

        fill(vis.begin(), vis.end(), false);
        reverse(ord.begin(), ord.end());

        int cnt = 0;
        for (int v : ord) {
            if (!vis[v]) {
                cur_comp = {};
                dfs_scc(v);
                for (int i : cur_comp) {
                    comp[i] = cnt;
                }
                cnt++;
            }
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    SCC scc(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        scc.add_edge(a, b);
    }

    scc.find_scc();

    ll ans = 0;
    ll diff = 0;
    vector<int> scc_sz(scc.comp.size());

    for (int v = 0; v < n; v++) {
        scc_sz[scc.comp[v]]++;
        for (auto w : scc.adj[v]) {
            if (scc.comp[v] != scc.comp[w]) {
                diff++;
            }
        }
    }

    ll prev = 0;
    for (int x : scc_sz) {
        ans += prev * x;
        prev += x;
    }

    cout << ans - diff << '\n';

    return 0;
}
