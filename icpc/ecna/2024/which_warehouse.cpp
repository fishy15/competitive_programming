#include <bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr ll INF = 0x3f3f3f3f3f3f3f3f;

using vi = vector<ll>;
#define sz(x) (int) (x).size()
#define rep(i, a, b) for (int i = (a); i < (b); i++)

pair<ll, vi> hungarian(const vector<vi> &a) {
    if (a.empty()) return {0, {}};
    ll n = sz(a) + 1, m = sz(a[0]) + 1;
    vi u(n), v(m), p(m), ans(n - 1);
    rep(i, 1, n) {
        p[0] = i;
        ll j0 = 0;
        vi dist(m, LLONG_MAX), pre(m, -1);
        vector<bool> done(m + 1);
        do {
            done[j0] = true;
            ll i0 = p[j0], j1, delta = LLONG_MAX;
            rep(j, 1, m) if (!done[j]) {
                auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
                if (dist[j] < delta) delta = dist[j], j1 = j;
            }
            rep(j, 0, m) {
                if (done[j]) u[p[j]] += delta, v[j] -= delta;
                else dist[j] -= delta;
            }
            j0 = j1;
        } while (p[j0]);
        while (j0) {
            ll j1 = pre[j0];
            p[j0] = p[j1], j0 = j1;
        }
    }
    rep(j, 1, m) if (p[j]) ans[p[j] - 1] = j - 1;
    return {-v[0], ans};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector cnt(n, vector<int>(m));
    for (auto &v : cnt) {
        for (auto &x : v) {
            cin >> x;
        }
    }

    vector dist(n, vector<ll>(n));
    for (auto &row : dist) {
        for (auto &x : row) {
            cin >> x;
            if (x == -1) {
                x = INF;
            }
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    // prod_cost[p][v]
    vector prod_cost(m, vector<ll>(n));
    for (int p = 0; p < m; p++) {
        for (int v = 0; v < n; v++) {
            for (int i = 0; i < n; i++) {
                prod_cost[p][v] += cnt[i][p] * dist[i][v];
            }
        }
    }

    cout << hungarian(prod_cost).first << '\n';

    return 0;
}
