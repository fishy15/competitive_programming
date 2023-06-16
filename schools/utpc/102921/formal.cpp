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
#define MAXN 100010

using namespace std;

template<typename F>
struct y_combinator_result {
    F f;
    template<typename T> explicit y_combinator_result(T &&f) : f(forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(forward<F>(f));
}

struct p2 {
    ll x, y;
    p2() : p2(0, 0) {}
    p2(ll x, ll y) : x(x), y(y) {}

    p2 operator+(const p2 a) const {
        return p2(x + a.x, y + a.y);
    }

    p2 operator-(const p2 a) const {
        return p2(x - a.x, y - a.y);
    }

    void operator+=(const p2 a) {
        x += a.x;
        y += a.y;
    }
};

int n, k;
vector<array<ll, 2>> adj[MAXN];

p2 max(p2 a, p2 b) {
    if (a.x < b.x) {
        return b;
    }
    return a;
}

p2 solve(int c) {
    vector<array<p2, 2>> dp(n);

    p2 ans;
    auto dfs = y_combinator([&](auto self, int v, int p) -> void {
        for (auto [e, w] : adj[v]) {
            if (e != p) {
                self(e, v);
                dp[v][0] += max(dp[e][0], dp[e][1]);
            }
        }

        dp[v][1] = dp[v][0];

        p2 mm = dp[v][1];
        for (auto [e, w] : adj[v]) {
            if (e != p) {
                p2 res = dp[v][1] - max(dp[e][0], dp[e][1]) + dp[e][0];
                res.x += w - c;
                res.y++;
                mm = max(mm, res);
            }
        }

        dp[v][1] = mm;

        dp[v][0] = max(dp[v][0], p2());
        dp[v][1] = max(dp[v][1], p2());
        ans = max(dp[v][0], ans);
        ans = max(dp[v][1], ans);
    });

    dfs(0, 0);
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;

    for (int i = 0; i < n - 1; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    int l = -INF;
    int r = INF;

    ll opt = 0;
    while (l <= r) {
        int m = (l + r) / 2;
        p2 x = solve(m);
        if (x.y <= k) {
            opt = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    p2 x = solve(opt);
    cout << x.x + k * opt << '\n';

    return 0;
}
