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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, p;
    cin >> n >> p;

    vector<int> c(n);
    rep(i, 0, n) {
        cin >> c[i];
    }

    // dp[(0, 0)][(0, 1)][(1, 0)][(1, 1)] = {# of configs w total 0 paths, # of configs w total 1 paths}
    vector dp(n+1, vector(n+1, vector(n+1, vector(n+1, array<mi, 2>{}))));
    dp[0][0][0][0] = {1, 0};

    vector<mi> pow2(n + 1);
    vector<mi> f(n + 1);
    vector<mi> inv_f(n + 1);
    pow2[0] = 1;
    f[0] = 1;
    inv_f[0] = 1;
    rep(i, 0, n) {
        pow2[i+1] = pow2[i] * 2;
        f[i+1] = f[i] * (i + 1);
        inv_f[i+1] = f[i+1].inv();
    }

    auto choose = [&](int n, int k) {
        return f[n] * inv_f[k] * inv_f[n - k];
    };

    rep(i, 0, n) {
        rep(zz, 0, i+1) {
            rep(zo, 0, (i - zz) + 1) {
                rep(oz, 0, (i - zz - zo) + 1) {
                    auto oo = i - zz - zo - oz;

                    if (c[i] != 1) {
                        // transition as if it is a 0
                        auto no_change_parity_arrows = pow2[zz + zo + oz];

                        rep(oo_taken, 0, oo + 1) {
                            auto choose_oo = choose(oo, oo_taken);
                            auto mult = no_change_parity_arrows * choose_oo;
                            if (oo_taken % 2 == 0) {
                                // parity stays the same (goes to 1)
                                dp[zz][zo + 1][oz][oo][1] += mult * dp[zz][zo][oz][oo][0];
                                dp[zz][zo + 1][oz][oo][0] += mult * dp[zz][zo][oz][oo][1];
                            } else {
                                dp[zz + 1][zo][oz][oo][0] += mult * dp[zz][zo][oz][oo][0];
                                dp[zz + 1][zo][oz][oo][1] += mult * dp[zz][zo][oz][oo][1];
                            }
                        }
                    }

                    if (c[i] != 0) {
                        // transition as if it is a 1
                        auto no_change_parity_arrows = pow2[zz + oz + oo];

                        rep(zo_taken, 0, zo + 1) {
                            auto choose_zo = choose(zo, zo_taken);
                            auto mult = no_change_parity_arrows * choose_zo;
                            if (zo_taken % 2 == 0) {
                                // parity stays the same (goes to 1)
                                dp[zz][zo][oz][oo + 1][1] += mult * dp[zz][zo][oz][oo][0];
                                dp[zz][zo][oz][oo + 1][0] += mult * dp[zz][zo][oz][oo][1];
                            } else {
                                dp[zz][zo][oz + 1][oo][0] += mult * dp[zz][zo][oz][oo][0];
                                dp[zz][zo][oz + 1][oo][1] += mult * dp[zz][zo][oz][oo][1];
                            }
                        }
                    }
                }
            }
        }
    }

    int i = n;
    mi ans = 0;
    rep(zz, 0, i+1) {
        rep(zo, 0, (i - zz) + 1) {
            rep(oz, 0, (i - zz - zo) + 1) {
                auto oo = i - zz - zo - oz;
                ans += dp[zz][zo][oz][oo][p];
            }
        }
    }

    cout << ans.v << '\n';

    return 0;
}
