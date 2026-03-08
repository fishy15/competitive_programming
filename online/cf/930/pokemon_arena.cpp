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

    vector<ll> cost(n);
    rep(i, 0, n) {
        cin >> cost[i];
    }

    vector attr(n, vector<ll>(m));
    vector in_attr(m, vector<ll>(n));
    vector<map<ll, vector<int>>> has_attr(m);
    rep(i, 0, n) {
        rep(j, 0, m) {
            cin >> attr[i][j];
            in_attr[j][i] = attr[i][j];
            has_attr[j][attr[i][j]].push_back(i);
        }
    }

    for (auto &row : in_attr) {
        sort(all(row));
        row.erase(unique(all(row)), end(row));
    }

    vector<int> start_attr(m);
    int cur = n; // after original n
    rep(i, 0, m) {
        start_attr[i] = cur;
        cur += sz(in_attr[i]);
    }

    vector dist(cur, INFLL);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;
    pq.push({0, 0});
    dist[0] = 0;

    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (d != dist[v]) {
            continue;
        }

        if (v < n) {
            // go to its attrs for free
            rep(j, 0, m) {
                auto attr_pos = lower_bound(all(in_attr[j]), attr[v][j]) - begin(in_attr[j]);
                int nv = attr_pos + start_attr[j];
                auto nd = dist[v];
                if (nd < dist[nv]) {
                    dist[nv] = nd;
                    pq.push({nd, nv});
                }
            }
        } else {
            auto j = upper_bound(all(start_attr), v) - begin(start_attr) - 1;
            auto attr_pos = v - start_attr[j];
            auto attr_val = in_attr[j][attr_pos];
            for (auto nv : has_attr[j][attr_val]) {
                auto nd = dist[v] + cost[nv];
                if (nd < dist[nv]) {
                    dist[nv] = nd;
                    pq.push({nd, nv});
                }
            }

            // go up
            if (attr_pos < sz(in_attr[j]) - 1) {
                auto nv = v + 1;
                auto nd = dist[v];
                if (nd < dist[nv]) {
                    dist[nv] = nd;
                    pq.push({nd, nv});
                }
            }

            // go down
            if (attr_pos > 0) {
                auto nv = v - 1;
                auto nd = dist[v] + (attr_val - in_attr[j][attr_pos - 1]);
                if (nd < dist[nv]) {
                    dist[nv] = nd;
                    pq.push({nd, nv});
                }
            }
        }
    }

    cout << dist[n-1] << '\n';
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
