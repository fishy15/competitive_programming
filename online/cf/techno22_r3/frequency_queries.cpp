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
#include <cassert>

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

// kactl
struct FT {
    vector<ll> s;
    FT(int n) : s(n) {}
    void update(int pos, ll dif) { // a[pos] += dif
        for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
    }
    ll query(int pos) { // sum of values in [0, pos)
        ll res = 0;
        for (; pos > 0; pos &= pos - 1) res += s[pos-1];
        return res;
    }
    int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
        // Returns n if no sum is >= sum, or -1 if empty sum is.
        if (sum <= 0) return -1;
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1) {
            if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
                pos += pw, sum -= s[pos-1];
        }
        return pos;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    rep(i, 0, n) {
        cin >> a[i];
        a[i]--;
    }

    vector<int> par(n, -1);
    vector<vector<int>> child(n);
    rep(i, 1, n) {
        cin >> par[i];
        par[i]--;
        child[par[i]].push_back(i);
    }

    vector<vector<array<int, 3>>> qrys_at(n);
    vector<int> ans(q);
    rep(i, 0, q) {
        int v, l, k;
        cin >> v >> l >> k;
        v--;
        qrys_at[v].push_back({i, l, k});
    }

    FT freq_cnt(n+1);
    vector<vector<int>> freq_colors(n+1);
    vector<int> freq_of(n);

    freq_cnt.update(0, n);
    auto add_freq = [&](int c, int cnt) {
        freq_cnt.update(cnt, 1);
        freq_colors[cnt].push_back(c);
    };

    auto rem_freq = [&](int c, int cnt) {
        freq_cnt.update(cnt, -1);
    };

    auto upd_freq = [&](int c, int diff) {
        rem_freq(c, freq_of[c]);
        freq_of[c] += diff;
        add_freq(c, freq_of[c]);
    };

    auto get = [&](int cnt) {
        while (!freq_colors[cnt].empty() && freq_of[freq_colors[cnt].back()] != cnt) {
            freq_colors[cnt].pop_back();
        }
        assert(!freq_colors[cnt].empty());
        return freq_colors[cnt].back();
    };

    auto dfs = [&](auto &&self, int v) -> void {
        upd_freq(a[v], 1);

        for (auto [idx, l, k] : qrys_at[v]) {
            auto small_cnt = freq_cnt.query(l);
            auto pos = freq_cnt.lower_bound(small_cnt + k);
            if (pos == -1 || pos == n+1) {
                ans[idx] = -1;
            } else {
                ans[idx] = get(pos) + 1;
            }
        }

        for (auto e : child[v]) {
            self(self, e);
        }

        upd_freq(a[v], -1);
    };
    dfs(dfs, 0);

    for (auto x : ans) {
        cout << x << ' ';
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
