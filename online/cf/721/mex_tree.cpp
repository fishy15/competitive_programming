/*
 * For getting a mex of 0, we can compute it by seeing which paths are within subtrees of 0 (for a tree 
 * rooted at 0). For the rest of the values, we can first find the value that the mex is greater than or
 * equal to a value and then take differences to get the answer. We note that path with a mex >= k will be
 * a path going through all the values 0, 1, ..., k - 1. Since all of these points must land on the same
 * path (including 0), the endpoints must be two points whose LCA is 0. We can maintain the "lowest" points
 * that must be in the path, and all of the other points must be ancestors of either one of these. In order
 * to add point k to the path, we take the following cases:
 *   - one of the endpoints for the points 0, 1, ..., k - 1 is an ancestor of k. This means k becomes a new
 *     endpoint as long as the LCA is zero.
 *   - k is an ancestor of one of the previous endpoints. This means k is already in the path, so the answer
 *     is the same as the previous case.
 *   - otherwise, we cannot make a path with all of the previous points, so the answer is 0.
 * Finally, we just have to take the differences as mentioned earlier to recover the answer.
 */

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

struct tree {
    vector<vector<int>> adj;
    vector<int> depth, in, out, sz;
    vector<array<int, 20>> up;

    tree(int n) : adj(n), depth(n), in(n), out(n), sz(n), up(n, array<int, 20>{}) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs() {
        int t = 0;
        dfs(0, 0, t);
    }

    void dfs(int v, int p, int &t) {
        in[v] = t++;
        up[v][0] = p;

        for (int i = 1; i < 20; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }

        sz[v] = 1;
        for (int e : adj[v]) {
            if (e != p) {
                depth[e] = depth[v] + 1;
                dfs(e, v, t);
                sz[v] += sz[e];
            }
        }

        out[v] = t++;
    }

    int anc(int u, int v) {
        return in[u] <= in[v] && out[v] <= out[u];
    }

    int lca(int u, int v) {
        if (anc(u, v)) return u;
        if (anc(v, u)) return v;

        for (int i = 19; i >= 0; i--) {
            if (!anc(up[v][i], u)) {
                v = up[v][i];
            }
        }

        return up[v][0];
    }

    // remove a subtree of 0 if needed
    ll get_sz(int u, int v) {
        if (u == 0) {
            for (int i = 19; i >= 0; i--) {
                if (up[v][i] != 0) {
                    v = up[v][i];
                }
            }
            return sz[u] - sz[v];
        } else {
            return sz[u];
        }
    }
};

void solve() {
    int n; cin >> n;

    tree t(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        t.add_edge(a, b);
    }

    t.dfs();

    vector<ll> ans(n + 1);
    
    for (int e : t.adj[0]) {
        ans[0] += (ll) t.sz[e] * (t.sz[e] - 1) / 2;
    }

    int l_bound = 0;
    int r_bound = 0;

    ans[1] = (ll) n * (n - 1) / 2 - ans[0];
    for (int i = 1; i < n; i++) {
        if (t.anc(i, l_bound) || t.anc(i, r_bound)) {
            ans[i + 1] = ans[i];
        } else if (t.anc(l_bound, i)) {
            l_bound = i;
            ans[i + 1] = t.get_sz(l_bound, r_bound) * t.get_sz(r_bound, l_bound);
        } else if (t.anc(r_bound, i)) {
            r_bound = i;
            ans[i + 1] = t.get_sz(l_bound, r_bound) * t.get_sz(r_bound, l_bound);
        } else {
            break;
        }

        if (t.lca(l_bound, r_bound) != 0) {
            ans[i + 1] = 0;
            break;
        }
    }

    for (int i = 1; i < n; i++) {
        ans[i] -= ans[i + 1];
    }

    for (int i = 0; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
