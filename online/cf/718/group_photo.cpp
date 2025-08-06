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

void solve() {
    int n;
    cin >> n;

    vector<ll> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    if (n <= 3) {
        // any order works
        int ans = 0;
        rep(msk, 0, 1 << n) {
            ll p_sum = 0;
            ll c_sum = 0;
            rep(i, 0, n) {
                if ((msk >> i) & 1) {
                    p_sum += nums[i];
                } else {
                    c_sum += nums[i];
                }
            }

            if (c_sum < p_sum) {
                ans++;
            }
        }

        cout << ans << '\n';
        return;
    }

    vector<ll> psum{0}, even_psum{0}, odd_psum{0};
    rep(i, 0, n) {
        psum.push_back(psum.back() + nums[i]);
        if (i % 2 == 0) {
            even_psum.push_back(even_psum.back() + nums[i]);
            odd_psum.push_back(odd_psum.back() + 0);
        } else {
            even_psum.push_back(even_psum.back() + 0);
            odd_psum.push_back(odd_psum.back() + nums[i]);
        }
    }

    auto sum = [&](const auto &v, int l, int r) {
        return v[r] - v[l];
    };

    mi ans;
    
    // P before C
    rep(i, 1, n+1) {
        auto p_sum = sum(psum, 0, i);
        auto c_sum = sum(psum, i, n);
        if (c_sum < p_sum) {
            ans += 1;
        }
    }

    // C before P, follows the pattern (C or P) C... PC... P... (C or P)
    auto comp = [&](ll base_c, ll base_p, bool skip_first, bool skip_last) {
        mi res = 0;
        rep(c_pref, 1, n) {
            if (c_pref == 1 && skip_first) continue;
            int l = c_pref;
            int r = n - 1;
            if (skip_last) r = n - 2;
            int works = -1;
            while (l <= r) {
                int m = (l + r) / 2;
                // 1 -> c_pref is c
                // c_pref -> m is alternating
                // m -> n-1 is p
                auto init_c = sum(psum, 1, c_pref);
                auto alt_c = sum(even_psum, c_pref, m);
                auto alt_p = sum(odd_psum, c_pref, m);
                // c_pref is the index of the first p, so swap if even
                if (c_pref % 2 == 0) {
                    swap(alt_c, alt_p);
                }
                auto final_p = sum(psum, m, n-1);

                auto total_c = base_c + init_c + alt_c;
                auto total_p = base_p + alt_p + final_p;
                if (total_c < total_p) {
                    works = m;
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            }

            if (works != -1) {
                res += (works - c_pref + 2) / 2;
            }
        }

        return res;
    };

    ans += comp(nums[0] + nums[n-1], 0, false, true);
    ans += comp(nums[0], nums[n-1], false, false);
    ans += comp(nums[n-1], nums[0], true, true);
    ans += comp(0, nums[0] + nums[n-1], true, false);

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
