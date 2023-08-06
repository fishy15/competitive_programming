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

template<typename T>
T &ckmax(T &a, T b) {
    return a = max(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<vector<int>> child(n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        child[p].push_back(i);
    }

    vector<int> sz(n);
    vector<int> ans(n);

    auto dfs = y_combinator([&](auto self, int v) -> void {
        vector dp(1, 0);

        for (auto e : child[v]) {
            self(e);

            int psz = sz[v];
            sz[v] += sz[e];

            vector nxt(sz[v] + 1, 0);
            for (int bef = 0; bef <= psz; bef++) {
                int aft = psz - bef;
                for (int new_b = 0; new_b <= sz[e]; new_b++) {
                    int new_a = sz[e] - new_b;
                    ckmax(nxt[bef + new_b], dp[bef] + (bef * new_a) + (aft * new_b));
                }
            }
            dp = nxt;
        }

        sz[v]++;
        ans[v] = *max_element(dp.begin(), dp.end());
    });

    dfs(0);
    cout << accumulate(ans.begin(), ans.end(), 0LL) << '\n';

    return 0;
}
