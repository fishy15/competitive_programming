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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    auto get = [&](const deque<ll> &a, int idx) {
        if (idx < 0 || idx >= (int) a.size()) return 0LL;
        return a[idx];
    };

    ll ans = 0;
    auto comb = [&](deque<ll> &a, deque<ll> &b) {
        if (a.size() < b.size()) swap(a, b);
        for (int i = 0; i < (int) b.size(); i++) {
            ans += b[i] * get(a, k - i);
        }
        for (int i = 0; i < (int) b.size(); i++) {
            a[i] += b[i];
        }
    };

    auto dfs = y_combinator([&](auto self, int v, int p) -> deque<ll> {
        deque<ll> combo = {1};
        for (auto e : adj[v]) {
            if (e != p) {
                auto res = self(e, v);
                res.push_front(0);
                comb(combo, res);
            }
        }
        return combo;
    });

    dfs(0, 0);
    cout << ans << '\n';

    return 0;
}
