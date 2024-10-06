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

// b is invalid 
ll merge(map<int, int> &a, map<int, int> &b) {
    ll comb = 0;
    if (sz(a) < sz(b)) swap(a, b);
    for (auto [x, y] : b) {
        comb += a[x] * y;
        a[x] += y;
    }
    return comb;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> color(n);
    vector<int> color_count(n);
    vector<vector<int>> adj(n);
    rep(i, 0, n) {
        cin >> color[i];
        color[i]--;
        color_count[color[i]]++;
    }

    vector<pair<int, int>> edges;
    rep(i, 0, n - 1) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
        edges.push_back({a, b});
    }

    vector<ll> ans_of(n);
    vector<int> depth(n);
    auto dfs = [&](auto &&self, int v, int p, int d) -> pair<map<int, int>, ll> {
        map<int, int> counts;
        depth[v] = d;

        ll res = 0;
        for (auto e : adj[v]) {
            if (e != p) {
                auto &&[child_cnt, tot] = self(self, e, v, d+1);
                // remove any paths that do not use this edge
                auto child_c = color[e];
                if (color_count[child_c] > 1) { 
                    tot -= child_cnt[child_c] - 1;
                }
                res += tot;
                ans_of[e] = tot;
                auto ccc = merge(counts, child_cnt);
                res -= 2 * ccc;
            }
        }

        if (color_count[color[v]] > 1) {
            counts[color[v]] += 1;

            // how many new sequences are created as a result of color[v]
            res += color_count[color[v]] - counts[color[v]];
        }

        return {counts, res};
    };

    auto m = dfs(dfs, 0, 0, 0);

    for (auto [a, b] : edges) {
        int v = depth[a] > depth[b] ? a : b;
        cout << ans_of[v] << '\n';
    }

    return 0;
}
