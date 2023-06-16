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

    int n, m;
    cin >> n >> m;

    vector adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 0 means no color yet
    vector color(n, optional<int>{});

    auto color_cc = y_combinator([&](auto self, int v, int c1, int c2) -> bool {
        if (color[v].has_value()) {
            if (*color[v] != c1) {
                return false;
            }
        } else {
            // first time
            color[v] = c1;
            for (auto e : adj[v]) {
                auto ok = self(e, c2, c1);
                if (!ok) return false;
            }
        }

        return true;
    });

    int color_cnt = 0;
    for (int i = 0; i < n; i++) {
        if (!color[i].has_value()) {
            bool ok = color_cc(i, color_cnt, color_cnt + 1);
            color_cnt += 2;

            if (!ok) {
                cout << "0\n";
                return 0;
            }
        }
    }

    vector cc_count(color_cnt, 0);
    for (int i = 0; i < n; i++) {
        cc_count[*color[i]]++;
    }

    ll ans = (ll) n * (n - 1) / 2;
    ans -= m;

    for (auto cnt : cc_count) {
        ans -= (ll) cnt * (cnt - 1) / 2;
    }

    cout << ans << '\n';

    return 0;
}
