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

void solve() {
    int n;
    cin >> n;

    vector<int> p(n);
    vector<int> loc(n, -1);
    rep(i, 0, n) {
        cin >> p[i];
        if (p[i] != -1) {
            loc[p[i]] = i;
        }
    }

    int l = -1;
    int r = -1;

    // how many subarrays with that many holes
    vector<mi> with_holes(n + 1);
    rep(i, 0, n) {
        int holes = 0;
        rep(j, i, n) {
            holes += (p[j] == -1) ? 1 : 0;
            with_holes[holes] += 1;
        }
    }

    int total_holes = count(all(p), -1);

    vector<mi> f(n + 1), inv_f(n + 1);
    f[0] = inv_f[0] = 1;
    rep(i, 1, n+1) {
        f[i] = f[i-1] * i;
        inv_f[i] = f[i].inv();
    }

    auto comp = [&](int N, int H) {
        if (H < N || H > total_holes) {
            return mi(0);
        }
        
        auto top_prod = f[H] * inv_f[H - N];
        auto bot_prod = inv_f[total_holes] * f[total_holes - N];
        return top_prod * bot_prod;
    };

    mi ans = 0;
    int missing_so_far = 0;
    rep(i, 0, n) {
        if (loc[i] == -1) {
            // its a missing number
            missing_so_far++;
        } else {
            auto pos = loc[i];
            if (l == -1) {
                l = r = pos;
                fill(all(with_holes), mi(0));
                rep(a, 0, n) {
                    int holes = 0;
                    rep(b, a, n) {
                        holes += (p[b] == -1) ? 1 : 0;
                        if (a <= pos && pos <= b) {
                            with_holes[holes] += 1;
                        }
                    }
                }
            } else {
                while (l > pos) {
                    int holes = 0;
                    rep(r2, l, n) {
                        holes += (p[r2] == -1) ? 1 : 0;
                        if (r2 >= r) {
                            with_holes[holes] -= 1;
                        }
                    }
                    l--;
                }

                while (r < pos) {
                    int holes = 0;
                    for (int l2 = r; l2 >= 0; l2--) {
                        holes += (p[l2] == -1) ? 1 : 0;
                        if (l2 <= l) {
                            with_holes[holes] -= 1;
                        }
                    }
                    r++;
                }
            }
        }

        rep(H, 0, n+1) {
            ans += with_holes[H] * comp(missing_so_far, H);
        }
    }

    cout << (ans * f[total_holes]).v << '\n';
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
