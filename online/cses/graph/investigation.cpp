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

// change if necessary
#define MAXN 1000000

using namespace std;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi(ll _v) : mi((int)(_v % MOD)) {}
    mi operator+(const mi &m2) const { return mi(v + m2.v); }
    mi operator-(const mi &m2) const { return mi(v - m2.v); }
    mi operator*(const mi &m2) const { return mi((ll) v * m2.v); }
    mi operator/(const mi &m2) const { return mi((ll) v * m2.inv().v); }
    mi &operator+=(const mi &m2) { return *this = *this + m2; }
    mi &operator-=(const mi &m2) { return *this = *this - m2; }
    mi &operator*=(const mi &m2) { return *this = *this * m2; }
    mi &operator/=(const mi &m2) { return *this = *this / m2; }
    mi pow(ll e) const {
        mi res = 1;
        mi n = *this;
        while (e > 0) {
            if (e & 1) res *= n;
            n *= n;
            e >>= 1;
        }
        return res;
    }
    mi inv() const {
        return pow(MOD - 2);
    }
};

struct route {
    ll min_price;
    mi num_routes;
    ll min_flights;
    ll max_flights;

    bool comb(const route &other) {
        if (min_price == other.min_price) {
            num_routes += other.num_routes;
            min_flights = min(min_flights, other.min_flights);
            max_flights = max(max_flights, other.max_flights);
            return false;
        } else if (min_price > other.min_price) {
            *this = other;
            return true;
        }

        return false;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, ll>>> adj(n);

    for (int i = 0; i < m; i++) {
        int a, b; ll c;
        cin >> a >> b >> c;
        a--; b--;

        adj[a].push_back({b, c});
    }

    vector<route> shortest(n, {INFLL, 0, 0, 0});
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    vector<bool> vis(n);

    shortest[0] = {0, 1, 0, 0};
    pq.push({0, 0});

    while (!pq.empty()) {
        auto [_, u] = pq.top();
        pq.pop();

        auto r = shortest[u];

        if (vis[u]) continue;
        vis[u] = true;

        for (auto [v, w] : adj[u]) {
            route nxt_route = {r.min_price + w, r.num_routes, r.min_flights + 1, r.max_flights + 1};
            if (shortest[v].comb(nxt_route)) {
                pq.push({shortest[v].min_price, v});
            }
        }
    }

    auto ans = shortest[n - 1];
    cout << ans.min_price << ' ' << ans.num_routes.v << ' ' << ans.min_flights << ' ' << ans.max_flights << '\n';

    return 0;
}
