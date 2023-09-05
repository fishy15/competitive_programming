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
#define MAXN 200000

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

template<typename T>
struct BIT {
    int n;
    vector<T> bit;

    BIT(int n) : n(n), bit(n + 1) {}

    void upd(int x, T v) {
        x++;
        while (x <= n) {
            bit[x] += v;
            x += x & -x;
        }
    }

    T qry(int r) {
        T res{};
        while (r > 0) {
            res += bit[r];
            r -= r & -r;
        }
        return res;
    }

    T qry(int l, int r) {
        return qry(r) - qry(l);
    }
};

mi f[MAXN + 1];
mi inv_f[MAXN + 1];

void precalc() {
    f[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        f[i] = f[i - 1] * i;
    }

    inv_f[MAXN] = f[MAXN].inv();
    for (int i = MAXN - 1; i >= 0; i--) {
        inv_f[i] = inv_f[i + 1] * (i + 1);
    }
}

struct info {
    int total;
    mi total_combos;
    BIT<int> prefix_cnt;
    vector<int> only_cnt;

    info() : total(0), total_combos(1), prefix_cnt(MAXN + 1), only_cnt(MAXN + 1) {}

    void add(int x) {
        total++;
        prefix_cnt.upd(x, 1);
        only_cnt[x]++;

        total_combos *= total;
        total_combos /= only_cnt[x];
    }

    void rem(int x) {
        total_combos /= total;
        total_combos *= only_cnt[x];

        total--;
        prefix_cnt.upd(x, -1);
        only_cnt[x]--;
    }

    mi frac_below(int x) {
        if (total == 0) return 1;
        return mi(prefix_cnt.qry(x)) / total;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    int n, m;
    cin >> n >> m;

    vector<int> s(n), t(m);
    for (auto &x : s) cin >> x;
    for (auto &x : t) cin >> x;

    info f;
    for (auto x : s) {
        f.add(x);
    }

    mi ans;
    for (int len_match = 0; len_match < m; len_match++) {
        // next elem is below
        auto fb = f.frac_below(t[len_match]);
        ans += fb * f.total_combos;

        // next elem is equal
        if (f.only_cnt[t[len_match]] == 0) {
            break;
        } else {
            f.rem(t[len_match]);
        }
    }

    cout << ans.v << '\n';

    return 0;
}
