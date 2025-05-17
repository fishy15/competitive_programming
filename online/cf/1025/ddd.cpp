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
    int n, m, l;
    cin >> n >> m >> l;

    vector<int> odds, evens;
    rep(i, 0, l) {
        int x;
        cin >> x;
        if (x % 2 == 0) {
            evens.push_back(x);
        } else {
            odds.push_back(x);
        }
    }

    vector<vector<int>> adj(n);
    rep(i, 0, m) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<array<ll, 2>> dist(n, {INFLL, INFLL});
    queue<pair<int, int>> q;
    dist[0][0] = 0;
    q.push({0, 0});
    while (!q.empty()) {
        auto [u, par] = q.front();
        q.pop();

        for (auto v : adj[u]) {
            if (dist[v][par ^ 1] == INFLL) {
                dist[v][par ^ 1] = dist[u][par] + 1;
                q.push({v, par ^ 1});
            }
        }
    }

    sort(all(odds));
    sort(all(evens));
    auto all_moves = 
          accumulate(all(odds), 0LL) 
        + accumulate(all(evens), 0LL);

    ll other = 0;
    if (sz(odds) >= 1) {
        other = max(other, all_moves - odds[0]);
    }

    ll max_even, max_odd;
    if (all_moves % 2 == 0) {
        max_even = all_moves;
        max_odd = other;
    } else {
        max_odd = all_moves;
        max_even = other;
    }

    rep(i, 0, n) {
        if (dist[i][0] <= max_even || dist[i][1] <= max_odd) {
            cout << 1;
        } else {
            cout << 0;
        }
    }
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
