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

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, r;
    cin >> n >> r;

    vector<pair<int, int>> temps(n);
    rep(i, 0, n) {
        int t;
        cin >> t;
        temps[i] = {t, i};
    }

    sort(all(temps));

    vector<vector<pair<int, int>>> adj(n);
    rep(_, 0, r) {
        int x, y, d;
        cin >> x >> y >> d;
        x--;
        y--;
        adj[x].push_back({y, d});
        adj[y].push_back({x, d});
    }
    
    // create temperature groups
    vector<vector<int>> groups;
    rep(i, 0, n) {
        if (i > 0 && temps[i - 1].first == temps[i].first) {
            groups.back().push_back(temps[i].second);
        } else {
            groups.push_back({temps[i].second});
        }
    }

    int q;
    cin >> q;
    vector<ll> ans(q);

    vector<vector<array<int, 3>>> cold_queries(sz(groups));
    vector<vector<array<int, 3>>> hot_queries(sz(groups));

    rep(i, 0, q) {
        int a, b, k, t;
        cin >> a >> b >> k >> t;
        a--;
        b--;

        k = min(k, sz(groups));
        k--;

        auto &v = t == 0 ? cold_queries : hot_queries;
        v[k].push_back({a, b, i});
    }

    auto compute = [&](const vector<vector<int>> &ord, const vector<vector<array<int, 3>>> &queries) {
        vector<ll> res(n * n, INFLL);
        auto get = [&](int x, int y) -> ll & {
            int idx = x * n + y;
            return res[idx];
        };

        auto step = [&](int k) {
            rep(i, 0, n) {
                rep(j, 0, n) {
                    ckmin(get(i, j), get(i, k) + get(k, j));
                }
            }
        };

        // init
        rep(u, 0, n) {
            get(u, u) = 0;
            for (auto [v, w] : adj[u]) {
                get(u, v) = w;
            }
        }

        rep(i, 0, sz(ord)) {
            for (auto x : ord[i]) {
                step(x);
            }

            // solve every query here
            for (auto [a, b, idx] : queries[i]) {
                ans[idx] = get(a, b);
                if (ans[idx] == INFLL) {
                    ans[idx] = -1;
                }
            }
        }
    };

    compute(groups, cold_queries);
    reverse(all(groups));
    compute(groups, hot_queries);

    rep(i, 0, q) {
        cout << ans[i] << '\n';
    }

    return 0;
}
