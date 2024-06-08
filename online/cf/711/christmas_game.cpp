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
    template<typename T> explicit y_combinator_result(T &&f) : f(std::forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), std::forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(std::forward<F>(f));
}

template<int k = 1>
void solve(int n, int kp) {
    if (k < kp) return solve<min(k+1, 20)>(n, kp);

    vector<vector<int>> adj(n);
    for (int i = 0; i < n-1; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;

        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }

    vector<bool> ans(n);
    vector dp(n, array<int, 2*k>{});

    auto xor_into = [&dp](int v, int e) {
        for (int i = 0; i < 2 * k; i++) {
            int nxt = i + 1;
            if (nxt == 2 * k) nxt = 0;
            dp[v][nxt] ^= dp[e][i];
        }
    };

    auto move_to = [&](int old_root, int new_root) {
        xor_into(old_root, new_root);
        xor_into(new_root, old_root);
    };

    auto dfs1 = y_combinator([&](auto &&self, int v, int p) -> void {
        dp[v][0] ^= a[v];
        for (auto e : adj[v]) {
            if (e != p) {
                self(e, v);
                xor_into(v, e);
            }
        }
    });

    auto dfs2 = y_combinator([&](auto &&self, int v, int p) -> void {
        int nimsum = accumulate(dp[v].begin() + k, dp[v].end(), 0, std::bit_xor{});
        ans[v] = (nimsum != 0);

        for (auto e : adj[v]) {
            if (e != p) {
                move_to(v, e);
                self(e, v);
                move_to(e, v);
            }
        }
    });

    dfs1(0, 0);
    dfs2(0, 0);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';


}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    solve(n, k);

    return 0;
}
