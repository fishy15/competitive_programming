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

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n), radj(n);
    vector<int> deg(n);
    rep(i, 0, m) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        radj[v].push_back(u);
        deg[u]++;
    }

    vector<pair<int, int>> deleted;
    vector<int> taken(n);

    vector<int> is_bad(n);
    queue<int> bad;
    bad.push(n - 1);
    is_bad[n - 1] = true;

    while (!bad.empty()) {
        auto v = bad.front();
        bad.pop();

        if (v == 0) {
            cout << "-1\n";
            return;
        }

        for (auto e : radj[v]) {
            if (!is_bad[e]) {
                // need to delete this edge
                if (2 * (taken[e] + 1) <= deg[e]) {
                    deleted.push_back({e, v});
                    taken[e]++;
                } else {
                    is_bad[e] = true;
                    bad.push(e);
                }
            }
        }
    }

    cout << sz(deleted) << '\n';
    for (auto [u, v] : deleted) {
        cout << u+1 << ' ' << v+1 << '\n';
    }
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
