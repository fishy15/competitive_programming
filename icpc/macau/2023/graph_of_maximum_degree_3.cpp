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
#define MOD 998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct mi {
    int v;
    mi(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi(ll _v) : v(_v % MOD) {}

    mi operator+(const mi &other) const { return mi(v + other.v); }
    mi &operator+=(const mi &other) { return *this = *this + other; }
    mi operator*(const mi &other) const { return mi((ll) v * other.v); }
    mi &operator*=(const mi &other) { return *this = *this * other; }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> red(n), blue(n);
    map<pair<int, int>, int> cnt;
    for (int i = 0; i < m; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        u--;
        v--;

        if (t == 0) {
            red[u].push_back(v);
            red[v].push_back(u);
        } else {
            blue[u].push_back(v);
            blue[v].push_back(u);
        }

        cnt[minmax(u, v)]++;
    }

    auto exists = [&](auto &color, int u, int v) {
        return count(color[u].begin(), color[u].end(), v) > 0;
    };

    mi single_ans = n;

    mi double_ans = 0;
    mi triple_ans = 0;
    for (auto [uv, c] : cnt) {
        if (c == 2) {
            double_ans += 1;

            auto [u, v] = uv;
            for (auto w : red[u]) {
                if (exists(blue, v, w)) {
                    triple_ans += 1;
                }
            }
            for (auto w : blue[u]) {
                if (exists(red, v, w)) {
                    triple_ans += 1;
                }
            }
        }
    }

    mi fourth_ans = 0;
    vector<bool> vis(n);
    array<int, 4> st{};
    auto dfs = [&](auto &&self, int u, int depth) -> void {
        st[depth++] = u;
        vis[u] = true;

        if (depth == 4) {
            if (exists(blue, st[0], st[3])) {
                if (exists(blue, st[0], st[1]) && exists(blue, st[2], st[3])) {
                    fourth_ans += 1;
                }
                if (exists(blue, st[0], st[2]) && exists(blue, st[1], st[3])) {
                    fourth_ans += 1;
                }
            }
        } else {
            for (auto v : red[u]) {
                if (!vis[v]) {
                    self(self, v, depth);
                }
            }
        }

        vis[u] = false;
        depth--;
    };

    for (int i = 0; i < n; i++) {
        dfs(dfs, i, 0);
    }

    mi two_inv = mi(499122177);

    mi ans = single_ans + double_ans + triple_ans + (fourth_ans * two_inv);
    cout << ans.v << '\n';

    return 0;
}
