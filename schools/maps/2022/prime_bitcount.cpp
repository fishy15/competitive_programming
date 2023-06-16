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
#define MOD 1000000607

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 110

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

bool p[MAXN];
mi f[MAXN];
mi invf[MAXN];

mi dp_2[2][100][100];
mi dp_3[2][100][100][100];

mi c(int n, int k) {
    return f[n] * invf[n - k] * invf[k];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    // primes
    fill(p, p + MAXN, true);
    p[0] = false;
    p[1] = false;

    for (ll i = 2; i < MAXN; i++) {
        if (p[i]) {
            for (ll j = i * i; j < MAXN; j += i) {
                p[j] = false;
            }
        }
    }

    // factorial
    f[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        f[i] = f[i - 1] * i;
    }
    invf[MAXN - 1] = f[MAXN - 1].inv();
    for (int i = MAXN - 2; i >= 0; i--) {
        invf[i] = invf[i + 1] * (i + 1);
    }

    int n, k;
    cin >> n >> k;

    if (k == 2) {
        cout << "1\n";
    } else {
        // everything besides 2, 3
        mi ans;
        for (int i = 5; i <= k; i++) {
            if (p[i]) {
                ans += c(k, i); 
            }
        }

        /* cout << "got here" << endl; */

        // init
        for (int i = 0; i < k; i++) {
            for (int j = i + 1; j < k; j++) {
                dp_2[0][i][j] += 1;
            }
        }

        for (int a = 0; a < k; a++) {
            for (int b = a + 1; b < k; b++) {
                for (int c = b + 1; c < k; c++) {
                    dp_3[0][a][b][c] += 1;
                }
            }
        }

        /* cout << "init done" << endl; */

        // transitions
        for (int i = 1; i < n - k + 1; i++) {
            int cc = i & 1;
            int pp = cc ^ 1;

            /* cout << cc << ' ' << pp << endl; */

            for (int a = 0; a < k; a++) {
                for (int b = a + 1; b < k; b++) {
                    dp_2[cc][a][b] = 0;
                }
            }

            /* cout << ans.v << '\n'; */

            // transition 3 -> smth
            for (int a = 0; a < k; a++) {
                for (int b = a + 1; b < k; b++) {
                    for (int c = b + 1; c < k; c++) {
                        dp_3[cc][a][b][c] = 0;
                    }
                }
            }

            // reset cur
            // transition 2 -> smth
            for (int a = 0; a < k; a++) {
                for (int b = a + 1; b < k; b++) {
                    // we are losing one of the 1s, have to replace
                    if (a == 0) {
                        /* cout << b - 1 << ' ' << k - 1 << " from " << a << ' ' << b << '\n'; */
                        dp_2[cc][b - 1][k - 1] += dp_2[pp][a][b];
                    } else {
                        /* cout << a - 1 << ' ' << b - 1 << " from " << a << ' ' << b << '\n'; */
                        /* cout << a - 1 << ' ' << b - 1 << ' ' << k - 1 << " from " << a << ' ' << b << '\n'; */
                        dp_2[cc][a - 1][b - 1] += dp_2[pp][a][b];
                        dp_3[cc][a - 1][b - 1][k - 1] += dp_2[pp][a][b];
                    }
                }
            }

            // transition 3 -> smth
            for (int a = 0; a < k; a++) {
                for (int b = a + 1; b < k; b++) {
                    for (int c = b + 1; c < k; c++) {
                        // we are losing one of the 1s, could replace or go down
                        if (a == 0) {
                            /* cout << b - 1 << ' ' << c - 1 << " from " << a << ' ' << b << ' ' << c << '\n'; */
                            /* cout << b - 1 << ' ' << c - 1 << ' ' << k - 1 << " from " << a << ' ' << b << ' ' << c << '\n'; */
                            dp_2[cc][b - 1][c - 1] += dp_3[pp][a][b][c];
                            dp_3[cc][b - 1][c - 1][k - 1] += dp_3[pp][a][b][c];
                        } else {
                            /* cout << a - 1 << ' ' << b - 1 << ' ' << c - 1 << " from " << a << ' ' << b << ' ' << c << '\n'; */
                            dp_3[cc][a - 1][b - 1][c - 1] += dp_3[pp][a][b][c];
                        }
                    }
                }
            }
            
            /* cout << "transition done " << i << endl; */
        }

        for (int a = 0; a < k; a++) {
            for (int b = a + 1; b < k; b++) {
                /* cout << a << ' ' << b << ' ' << dp_2[n - k][a][b].v << '\n'; */
                ans += dp_2[(n - k) & 1][a][b];
            }
        }

        /* cout << ans.v << '\n'; */

        // transition 3 -> smth
        for (int a = 0; a < k; a++) {
            for (int b = a + 1; b < k; b++) {
                for (int c = b + 1; c < k; c++) {
                    ans += dp_3[(n - k) & 1][a][b][c];
                }
            }
        }

        cout << ans.v << '\n';
    }

    return 0;
}
