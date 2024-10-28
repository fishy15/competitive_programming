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
#define MOD 998244353

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

using contrib = array<mi, 128>;

contrib &operator+=(contrib &a, const contrib &b) {
    for (int i = 0; i < 128; i++) {
        a[i] += b[i];
    }
    return a;
}

contrib &operator-=(contrib &a, const contrib &b) {
    for (int i = 0; i < 128; i++) {
        a[i] -= b[i];
    }
    return a;
}

contrib &operator*=(contrib &a, mi x) {
    for (int i = 0; i < 128; i++) {
        a[i] *= x;
    }
    return a;
}

int get_p(ll x) {
    int p = 0;
    while ((1LL << p) <= x) p++;
    return p;
}

ll get_sz(int layers) {
    return (1LL << layers) - 1;
}

mi pow2(int e) {
    static array<mi, 128> cache{};
    if (cache[0].v == 0) {
        cache[0].v = 1;
        for (int i = 1; i < 128; i++) {
            cache[i] = cache[i - 1] * 2;
        }
    }

    if (e < 128) {
        return cache[e];
    } else {
        return mi(2).pow(e);
    }
}

contrib pairwise(int cur_layer, int tot_layers, ll extra) {
    static array<optional<contrib>, 128> full_cache{};

    if (extra == 0) {
        return contrib{};
    }

    if (cur_layer + 1 == tot_layers) {
        contrib res{};
        res[1] += 1;
        return res;
    }

    auto diff = tot_layers - cur_layer - 1;

    auto max_rem = 1LL << diff;
    if (max_rem == extra) {
        if (!full_cache[diff]) {
            auto res = pairwise(cur_layer + 1, tot_layers, extra / 2);
            res *= 2;
            res[2 * diff + 1] += pow2(2 * diff - 2);
            full_cache[diff] = res;
        }
        return *full_cache[diff];
    } else {
        auto extra_r = max_rem >> 1;
        if (extra_r >= extra) {
            return pairwise(cur_layer + 1, tot_layers, extra);
        }

        auto extra_l = extra - extra_r;
        auto res = pairwise(cur_layer + 1, tot_layers, extra_l);
        res += pairwise(cur_layer + 1, tot_layers, extra_r);
        res[2 * diff + 1] += mi(extra_l) * mi(extra_r);
        return res;
    }
}

// assume always extra 2 missing all the way to the right
contrib single(int tot_layers) {
    contrib res{};
    res[1] += 1;
    res[2] += 1;
    res[3] += 1;

    for (int i = tot_layers - 3; i >= 0; i--) {
        int d = tot_layers - i - 1;
        res[d + 1] += 1;
        for (int j = 1; j <= d; j++) {
            res[d + j + 1] += pow2(j - 1);
        }
    }

    return res;
}

mi comp(int x) {
    if (x == 1) return 1;
    return pow2(x - 2);
}

contrib full_tree(int tot_layers) {
    if (tot_layers == 1) {
        contrib res{};
        res[1] += 1;
        return res;
    } else {
        contrib res = full_tree(tot_layers - 1);
        res *= 2;
        for (int i = 1; i <= tot_layers; i++) {
            for (int j = 1; j <= tot_layers; j++) {
                res[i + j - 1] += comp(i) * comp(j);
            }
        }
        return res;
    }
}

void solve() {
    ll n;
    int m;
    cin >> n >> m;

    auto layers = get_p(n);
    auto extra = get_sz(layers) - n;
    auto pair_contrib = pairwise(0, layers, extra);
    auto only_contrib = single(layers);

    auto total_to_rem = only_contrib;
    total_to_rem *= extra;
    total_to_rem -= pair_contrib;
    total_to_rem[1] += extra;

    // total overall
    auto total = full_tree(layers);
    total -= total_to_rem;

    mi exp_value = 0;
    mi m_inv = mi(m).inv();
    for (int i = 1; i < 128; i++) {
        mi exp_for_len = 0;
        for (int j = 1; j <= m; j++) {
            mi p_fail = mi(j - 1) * m_inv;
            exp_for_len += mi(1) - p_fail.pow(i);
        }
        exp_value += exp_for_len * total[i];
    }

    mi ans = exp_value * mi(m).pow(n);
    cout << ans.v << '\n';
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
