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
    mi(ll _v) : v((int)(_v % MOD)) {}

    mi operator+(const mi &other) const { return mi(v + other.v); }
    mi operator-(const mi &other) const { return mi(v - other.v); }
    mi operator*(const mi &other) const { return mi((ll) v * other.v); }

    mi operator+=(const mi &other) { return *this = *this + other; }
    mi operator-=(const mi &other) { return *this = *this - other; }
    mi operator*=(const mi &other) { return *this = *this * other; }

    mi inv() const { return pow(MOD - 2); }
    mi pow(ll e) const {
        mi res = 1;
        mi cur = *this;
        while (e > 0) {
            if (e & 1) res *= cur;
            cur *= cur;
            e >>= 1;
        }
        return res;
    }
};

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    string s, t;
    cin >> s >> t;

    mi p = 2309;
    vector<mi> pow(max(n, m) + 1);
    vector<mi> invpow(max(n, m) + 1);
    invpow[0] = pow[0] = 1;
    rep(i, 1, max(n, m) + 1) {
        pow[i] = pow[i-1] * p;
        invpow[i] = pow[i].inv();
    }

    vector<mi> s_psum = {0};
    rep(i, 0, n) {
        s_psum.push_back(s_psum.back() + pow[i] * (s[i] - 'a' + 1));
    }

    vector<mi> t_psum = {0};
    rep(i, 0, m) {
        t_psum.push_back(t_psum.back() + pow[i] * (t[i] - 'a' + 1));
    }

    auto get_s = [&](int l, int r) {
        return (s_psum[r] - s_psum[l]) * invpow[l];
    };

    auto get_t = [&](int l, int r) {
        return (t_psum[r] - t_psum[l]) * invpow[l];
    };

    vector<int> s_substrs;
    rep(i, 0, n) {
        rep(j, i+1, n+1) {
            s_substrs.push_back(get_s(i, j).v);
        }
    }

    sort(all(s_substrs));
    auto compress = [&](mi h) -> int { 
        auto it = lower_bound(all(s_substrs), h.v);
        if (it == end(s_substrs) || *it != h.v) {
            return -1;
        }
        return it - begin(s_substrs);
    };

    vector next(m+1, vector<int>(sz(s_substrs), -1));
    for (int i = m-1; i >= 0; i--) {
        next[i] = next[i+1];
        rep(j, i+1, m+1) {
            auto t_hash = get_t(i, j);
            auto pos = compress(t_hash);
            if (pos != -1) {
                next[i][pos] = i;
            }
        }
    }

    int ans = n;

    // initialize dp
    vector dp(n+1, vector(m+1, INF));
    dp[0][0] = 0;
    rep(i, 1, n+1) {
        if (i <= min(n, m) && get_s(0, i).v == get_t(0, i).v) {
            dp[i][i] = i;
        } else {
            ans = min(ans, i+1);
        }
    }

    vector s_pos(n, vector(n+1, 0));
    rep(i, 0, n) {
        rep(j, i+1, n+1) {
            s_pos[i][j] = compress(get_s(i, j));
        }
    }

    rep(j, 0, m+1) {
        int min_cost = INF;
        rep(l, 0, n) {
            min_cost = min(min_cost, dp[l][j]);
            rep(r, l+1, n+1) {
                auto s_hash = get_s(l, r);
                auto pos = s_pos[l][r];
                auto nxt = next[j][pos];
                auto len = r - l;

                // check to exit
                // with *
                if (nxt == -1) {
                    ans = min(ans, min_cost + 1 + (r - l) + 1);
                }

                // without *
                if (r == n) {
                    if (len <= m) {
                        auto t_hash = get_t(m - len, m);
                        if (s_hash.v != t_hash.v) {
                            ans = min(ans, 1 + min_cost + (r - l));
                        }
                    } else {
                        ans = min(ans, 1 + min_cost + (r - l));
                    }
                }

                if (nxt != -1) {
                    auto nxt_end = nxt + len;
                    ckmin(dp[r][nxt_end], min_cost + 1 + (r - l));
                }
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
