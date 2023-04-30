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

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 3000010

using namespace std;

int MOD;

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

constexpr int SORTED = 1 << 0;
constexpr int HAS_OTHER_LOWER = 1 << 1;
constexpr int HAS_OTHER_HIGHER = 1 << 2;

bool is_sorted(int mask) { return (mask & SORTED) > 0; }
bool has_other_lower(int mask) { return (mask & HAS_OTHER_LOWER) > 0; }
bool has_other_higher(int mask) { return (mask & HAS_OTHER_HIGHER) > 0; }
bool has_any(int mask) { return has_other_lower(mask) || has_other_higher(mask); }
bool has_one(int mask) { return has_other_lower(mask) ^ has_other_higher(mask); }

mi f[MAXN];
mi inv_f[MAXN];

void precalc() {
    f[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        f[i] = f[i - 1] * i;
    }

    inv_f[MAXN - 1] = f[MAXN - 1].inv();
    for (int i = MAXN - 2; i >= 0; i--) {
        inv_f[i] = inv_f[i + 1] * (i + 1);
    }
}

mi c(int n, int k) {
    return f[n] * inv_f[k] * inv_f[n - k];
}

void solve() {
    int n;
    cin >> n >> MOD;

    precalc();

    mi ans;

    const auto n_fact = f[n];
    const auto n2_fact = f[2 * n];
    const auto n3_fact = f[3 * n];

    mi zero, one, two, three;

    // ZERO

    // only sorted needs 0
    zero = 1;

    // ONE

    // each element in the correct group
    one += (n2_fact - 1) * 2; // 2 adj groups messed up
    one -= n_fact - 1; // group 2 is messed up only, double counted

    // TWO

    two += [&]() -> mi {
        // arrange group that doesn't mix
        auto pick_one = c(2 * n, n) * n_fact;
        auto pick_rest = n2_fact;
        return pick_one * pick_rest - zero - one;
    }() * 2;

    // 1 and 3 unsorted themselves, 2 maybe unsorted
    // double counted
    /* two -= (n_fact - 1) * n_fact * (n_fact - 1); */

    // two adj groups messed up + 3rd unsorted
    // also double counted
    two -= (n_fact - 1) * (n2_fact - 1) * 2;

    // THREE

    three = n3_fact - two - one - zero;

    ans = zero * 0 + one * 1 + two * 2 + three * 3;
    cout << ans.v << '\n';
    cout << zero.v << ' ' << one.v << ' ' << two.v << ' ' << three.v << '\n';

    /*
    // each element in the correct group
    ans += (n_fact - 1) * 3; // one group unsorted only
    ans += (n_fact - 1) * 2; // 2 adj groups unsorted
    ans += (n_fact - 1) * 2 * 2; // 1 and 3, or 1 2 3

    auto 
    for (int grp1 = 0; grp1 < (1 << 3); grp1++) {
        for (int grp2 = 0; grp2 < (1 << 1); grp2++) {
            for (int grp3 = 0; grp3 < (1 << 3); grp3++) {
                // only applies if all the same
                if (is_sorted(grp1) && has_any(grp1)) continue;
                if (is_sorted(grp3) && has_any(grp3)) continue;

                mi combos = 1;



                if (!is_sorted(grp1) && !has_any(grp1)) {
                    combos *= 
                }

                bool first = false;
                bool second = false;

            }
        }
    }
    if (n == 1) {
        cout << "9\n";
    } else if (n == 2) {
        cout << "1689\n";
    } else {
        // possible that there are all 3 in a section
        mi ans;

        // each element in the correct group
        ans += 


        
    }
    */
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    solve();

    return 0;
}
