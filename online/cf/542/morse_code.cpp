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

vector<int> suffix_array(const string &s) {
    int n = s.size();
    vector<int> sa(n), c(n);
    for (int i = 0; i < n; i++) {
        sa[i] = n - i - 1;
        c[i] = s[i];
    }

    stable_sort(sa.begin(), sa.end(), [&s](int i, int j) { return s[i] < s[j]; });

    for (int len = 1; len < n; len *= 2) {
        vector<int> old_c(c), idx(n), old_sa(sa);
        iota(idx.begin(), idx.end(), 0);

        for (int i = 0; i < n; i++) {
            bool same = i > 0 && sa[i - 1] + len < n
                && old_c[sa[i - 1]] == old_c[sa[i]]
                && old_c[sa[i - 1] + len / 2] == old_c[sa[i] + len / 2];
            c[sa[i]] = same ? c[sa[i - 1]] : i;
        }

        for (int i = 0; i < n; i++) {
            int loc = old_sa[i] - len;
            if (loc >= 0) {
                sa[idx[c[loc]]++] = loc;
            }
        }
    }

    return sa;
}

vector<int> find_lcp(const string &s, const vector<int> &sa) {
    int n = s.size();
    vector<int> rank(n);
    for (int i = 0; i < n; i++) {
        rank[sa[i]] = i;
    }

    int len = 0;
    vector<int> lcp(n - 1);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            len = 0;
        } else {
            int j = sa[rank[i] + 1];
            while (max(i, j) + len < n && s[i + len] == s[j + len]) len++;
            lcp[rank[i]] = len;
            if (len > 0) len--;
        }
    }

    return lcp;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    string s;
    rep(i, 0, n) {
        int x;
        cin >> x;
        s.push_back('0' + x);
    }

    auto sa = suffix_array(s);
    auto lcp = find_lcp(s, sa);

    vector<mi> ans(n);
    rep(i, 0, n) {
        auto l = sa[i];

        int min_unique = 0;
        int cur_lcp = n - l;
        for (int j = i - 1; j >= 0; j--) {
            cur_lcp = min(cur_lcp, lcp[j]);
            if (sa[j] < l) {
                min_unique = max(min_unique, cur_lcp + 1);
                break;
            }
        }

        cur_lcp = n - l;
        for (int j = i + 1; j < n; j++) {
            cur_lcp = min(cur_lcp, lcp[j - 1]);
            if (sa[j] < l) {
                min_unique = max(min_unique, cur_lcp + 1);
                break;
            }
        }

        // everything from [min_unique, n - l] in length is unique
        vector<mi> dp(n - l + 1);
        dp[0] = 1;

        rep(j, 1, n - l + 1) {
            dp[j] += dp[j - 1]; 
            if (j >= 2) {
                dp[j] += dp[j - 2];
            }
            if (j >= 3) {
                dp[j] += dp[j - 3];
            }
            if (j >= 4) {
                auto substr = s.substr(l + j - 4, 4);
                if (substr != "0011" && substr != "0101" && substr != "1110" && substr != "1111") {
                    dp[j] += dp[j - 4];
                }
            }

            if (j >= min_unique) {
                ans[l + j - 1] += dp[j];
            }
        }
    }

    rep(i, 0, n) {
        if (i > 0) {
            ans[i] += ans[i - 1];
        }
        cout << ans[i].v << '\n';
    }

    return 0;
}
