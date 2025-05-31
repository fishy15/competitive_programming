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
#include <cassert>

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

pair<int, int> ask(const vector<int> &v) {
    cout << "? " << sz(v);
    for (auto x : v) {
        cout << ' ' << x+1;
    }
    cout << endl;

    int x, d;
    cin >> x >> d;
    if (x == -1 || d == -1) {
        exit(0);
    }

    return {x-1, d};
}

void answer(int x, int y) {
    cout << "! " << x+1 << ' ' << y+1 << endl;

    string ans;
    cin >> ans;
    if (ans != "Correct") {
        exit(0);
    }
}

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    rep(i, 0, n-1) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    auto get_dists = [&](int x) {
        vector<int> dist(n);
        auto dfs = [&](auto &&self, int v, int p, int cur_d) -> void {
            dist[v] = cur_d;
            for (auto e : adj[v]) {
                if (e != p) {
                    self(self, e, v, cur_d+1);
                }
            }
        };
        dfs(dfs, x, -1, 0);
        return dist;
    };

    vector<int> all_nodes(n);
    iota(all(all_nodes), 0);

    auto [on_line, gap] = ask(all_nodes);
    auto on_line_dists = get_dists(on_line);

    int l = (gap + 1) / 2;
    int r = gap;
    int endpoint1 = on_line;
    while (l <= r) {
        int m = (l + r) / 2;

        // construct list
        vector<int> pts;
        rep(v, 0, n) {
            if (on_line_dists[v] == m) {
                pts.push_back(v);
            }
        }

        if (pts.empty()) {
            r = m - 1;
        } else {
            auto [pt, pt_d] = ask(pts);
            if (pt_d == gap) {
                endpoint1 = pt;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
    }

    auto endpoint1_dists = get_dists(endpoint1);
    vector<int> right_dist;
    rep(v, 0, n) {
        if (endpoint1_dists[v] == gap) {
            right_dist.push_back(v);
        }
    }

    auto [endpoint2, _] = ask(right_dist);
    answer(endpoint1, endpoint2);
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
