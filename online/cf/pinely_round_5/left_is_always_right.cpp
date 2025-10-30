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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

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

constexpr int MAXN = 2e5;

mi f[MAXN];
mi inv_f[MAXN];

void precalc() {
    f[0] = 1;
    rep(i, 1, MAXN+1) {
        f[i] = f[i-1] * i;
    }
    inv_f[MAXN-1] = f[MAXN-1].inv();
    for (int i = MAXN-2; i >= 0; i--) {
        inv_f[i] = inv_f[i + 1] * (i + 1);
    }
}

mi c(int n, int k) {
    if (k < 0 || k > n) return 0;
    return f[n] * inv_f[k] * inv_f[n - k];
}

mi start_one(string s, int n, int k) {
    mi ans = 0;

    int first_zero = n;
    rep(i, 0, n) {
        if (s[i] == '0') {
            first_zero = i;
            break;
        }
    }

    auto make = [&](int open, int balance) {
        if ((open % 2 == 0) == (balance % 2 == 0)) {
            int ones = (open + balance) / 2;
            return c(open, ones);
        }
        return mi(0);
    };

    int unforced = k-1;
    int balance = 0;
    for (int i = n - 1; i >= 0; i--) {
        // consider the prefix before is all 1s
        if (i == n - k) {
            if (first_zero > i) {
                // all 1s in the beginning, so the ending just needs to have more 1s than 0s
                for (int goal = 0; goal <= k; goal += 2) {
                    ans += make(unforced, goal - balance);
                }
            }
        } else if (first_zero > i && i < n - k) {
            bool ok = true;
            if (s[i+1] == '?') {
                unforced--;
                balance--;
            } 
            if (s[i+1] == '1') {
                ok = false;
            }
            if (ok) {
                ans += make(unforced, -balance);
            }
            if (s[i+1] == '?') {
                unforced++;
                balance++;
            }
        }

        if (i + k - 1 < n) {
            if (s[i] == '?') {
                s[i] = s[i + k - 1];
            } else {
                if (s[i + k - 1] != '?') {
                    if (s[i] != s[i + k - 1]) {
                        break;
                    } 
                } else {
                    unforced--;
                    balance += s[i] == '1' ? 1 : -1;
                }
            }
        } else if (s[i] != '?') {
            unforced--;
            balance += s[i] == '1' ? 1 : -1;
        }
    }

    return ans;
}

void solve() {
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    mi ans = start_one(s, n, k);
    rep(i, 0, n) {
        if (s[i] != '?') {
            s[i] = '0' ^ '1' ^ s[i];
        }
    }
    ans += start_one(s, n, k);

    cout << ans.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
