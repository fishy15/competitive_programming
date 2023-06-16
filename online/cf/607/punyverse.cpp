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

int m, n;

void ckmax(array<ll, 3> &p1, array<ll, 3> p2) {
    p1 = max(p1, p2);
}

vector<array<ll, 3>> dfs(int v, int p, vector<ll> &val, vector<vector<int>> &adj) {
    vector<array<ll, 3>> res(1, {-1, -1, -1});
    res[0] = {0, 0, val[v]};
    for (int e : adj[v]) {
        if (e != p) {
            auto res2 = dfs(e, v, val, adj);
            vector<array<ll, 3>> ans(res.size() + res2.size(), {-1, -1, -1});
            for (auto a1 : res) {
                if (a1[0] == -1) continue;
                for (auto a2 : res2) {
                    if (a2[0] == -1) continue;
                    // merge regions
                    if (a1[0] + a2[0] <= m) {
                        ckmax(ans[a1[0] + a2[0]], {a1[0] + a2[0], a1[1] + a2[1], a1[2] + a2[2]});
                    }
                    // put barrier in between
                    if (a1[0] + a2[0] + 1 <= m) {
                        ckmax(ans[a1[0] + a2[0] + 1], {a1[0] + a2[0] + 1, a1[1] + a2[1] + (a2[2] > 0), a1[2]});
                    }
                }
            }
            res = ans;
        }
    }
    /* cout << "values for " << v << '\n'; */
    /* for (int i = 0; i < n; i++) { */
    /*     cout << res[i][0] << ' ' << res[i][1] << ' ' << res[i][2] << '\n'; */
    /* } */
    return res;
}

void solve() {
    cin >> n >> m;
    vector<ll> val;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        val.push_back(x);
    }
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        val[i] = x - val[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    auto res = dfs(0, 0, val, adj);
    cout << res[m - 1][1] + (res[m - 1][2] > 0) << '\n';
}

int main() {
    /* cin.tie(0)->sync_with_stdio(0); */

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
