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
#include <optional>

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

#define flip(x) x = !x

using vi = vector<int>;
using pii = pair<int, int>;
vi eulerWalk(vector<vector<pii>>& gr, int nedges, int src=0) {
	int n = sz(gr);
	vi D(n), its(n), eu(nedges), ret, s = {src};
	D[src]++; // to allow Euler paths, not just cycles
	while (!s.empty()) {
		int x = s.back(), y, e, &it = its[x], end = sz(gr[x]);
		if (it == end){ ret.push_back(x); s.pop_back(); continue; }
		tie(y, e) = gr[x][it++];
		if (!eu[e]) {
			D[x]--, D[y]++;
			eu[e] = 1; s.push_back(y);
		}}
	for (int x : D) if (x < 0 || sz(ret) != nedges+1) return {};
	return {ret.rbegin(), ret.rend()};
}

// solve on a cc
optional<vector<int>> subsolve(const vector<vector<pair<int, int>>> &adj, const vector<bool> &bad) {
    int n = sz(adj);
    if (count(all(bad), true) % 2 == 1) {
        return optional<vector<int>>{};
    }

    vector<bool> vis(n);
    vector<int> odd_edges;
    auto dfs = [&](auto &&self, int v) -> int {
        vis[v] = true;
        int tot = (bad[v] ? 1 : 0);
        for (auto [e, i] : adj[v]) {
            if (!vis[e]) {
                auto res = self(self, e);
                if (res % 2 == 1) {
                    odd_edges.push_back(i);
                }
                tot += res;
            }
        }
        return tot;
    };

    dfs(dfs, 0);
    
    return odd_edges; 
}

optional<vector<bool>> get_included(int n, int m, const vector<array<int, 3>> &edges) {
    vector<bool> included(m);
    vector<bool> deg(n);
    vector adj(n, vector<pair<int, int>>{});
    rep(i, 0, m) {
        auto [u, v, c] = edges[i];
        if (c == 1) {
            flip(included[i]);
            flip(deg[u]);
            flip(deg[v]);
        } else {
            adj[u].push_back({v, i});
            adj[v].push_back({u, i});
        }
    }

    vector<bool> vis(n);
    auto get_cc = [&](int x) {
        vector<int> ans;

        queue<int> q;
        q.push(x);
        vis[x] = true;
        while (!q.empty()) {
            auto t = q.front();
            q.pop();
            ans.push_back(t);

            for (auto [e, _] : adj[t]) {
                if (!vis[e]) {
                    vis[e] = true;
                    q.push(e);
                }
            }
        }

        return ans;
    };

    auto contains = [&](auto &v, int x) {
        auto it = lower_bound(all(v), x);
        return it != v.end() && *it == x;
    };

    auto g = [&](auto &v, int x) -> int {
        auto it = lower_bound(all(v), x);
        return it - v.begin();
    };

    rep(i, 0, n) {
        if (!vis[i]) {
            auto cc = get_cc(i);
            sort(all(cc));

            vector<vector<pair<int, int>>> subadj(sz(cc));
            vector<bool> bad(sz(cc));
            rep(j, 0, sz(cc)) {
                auto u = cc[j];
                for (auto [v, i] : adj[u]) {
                    if (contains(cc, v)) {
                        subadj[j].push_back({g(cc, v), i});
                    }
                }

                bad[j] = deg[u];
            }

            auto res = subsolve(subadj, bad);
            if (res) {
                for (auto x : *res) {
                    flip(included[x]);
                }
            } else {
                return optional<vector<bool>>{};
            }
        }
    }

    return included;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<array<int, 3>> edges;
    rep(i, 0, m) {
        int u, v, c;
        cin >> u >> v >> c;
        u--;
        v--;
        edges.push_back({u, v, c});
    }

    auto included = get_included(n, m, edges);
    if (included) {
        // answer is euler tour on included graph
        vector<vector<pair<int, int>>> all_included(n);
        int cnt = 0;
        rep(i, 0, m) {
            auto [u, v, c] = edges[i];
            if ((*included)[i]) {
                all_included[u].push_back({v, cnt});
                all_included[v].push_back({u, cnt});
                cnt++;
            }
        }

        cout << "YES\n";
        auto walk = eulerWalk(all_included, cnt);
        cout << sz(walk) - 1 << '\n';
        for (auto x : walk) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
    } else {
        cout << "NO\n";
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
