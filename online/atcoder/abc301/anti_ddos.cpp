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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s;
    cin >> s;

    int n = s.size();

    array<int, 26> upper_cnt{};
    vector<int> prev_cnt(n);
    vector<int> fixed_bef(n);

    int fixed_cnt = 0;
    for (int i = 0; i < n; i++) {
        if ('A' <= s[i] && s[i] <= 'Z') {
            int idx = s[i] - 'A';
            upper_cnt[idx]++;
            prev_cnt[i] = upper_cnt[idx];

            fixed_bef[i] = fixed_cnt;
            if (upper_cnt[idx] == 1) {
                fixed_cnt++;
            }
        }
    }

    // 0 - 26 - matched those many capital letters
    // 27 - matched a repeat capital as before
    // 28 - matched a lowercase after
    vector dp(n + 1, array<mi, 29>{});
    dp[0][0] = 1;

    for (int i = 0; i < n; i++) {
        if ('a' <= s[i] && s[i] <= 'z') {
            // number of capitals matched is still the same
            for (int j = 0; j <= 26; j++) {
                dp[i + 1][j] += dp[i][j];
            }

            // after 2 capitals, moves forward
            dp[i + 1][28] += dp[i][27];
            dp[i + 1][28] += dp[i][28];
        } else if ('A' <= s[i] && s[i] <= 'Z') {
            if (prev_cnt[i] == 1) {
                // transitions from current
                for (int j = fixed_bef[i]; j <= 26; j++) {
                    int free = j - fixed_bef[i];
                    int open = 26 - fixed_bef[i];
                    
                    // fraction that include s[i] is C(open - 1, free - 1) / C(open, free) = free / open;
                    mi include = mi(free) / mi(open);
                    mi not_include = mi(1) - include;

                    if (j != 26) {
                        dp[i + 1][j + 1] += not_include * dp[i][j];
                    }

                    dp[i + 1][27] += include * dp[i][j];
                }
            } else {
                // everything must be completed
                for (int j = 1; j <= 26; j++) {
                    dp[i + 1][27] += dp[i][j];
                }
            }

            // once we get two matches, still have two matches
            dp[i + 1][27] += dp[i][27];

            // ignore the case where we complete DDoS string
        } else {
            for (int j = 0; j <= 26; j++) {
                // lowercase letter
                dp[i + 1][j] += dp[i][j] * 26;

                // uppercase, not a repeat
                if (j != 26) {
                    dp[i + 1][j + 1] += mi(26 - j) * dp[i][j];
                }

                dp[i + 1][27] += mi(j) * dp[i][j];
            }

            // uppercase stays the same, lowercase moves forward
            dp[i + 1][27] += dp[i][27] * 26;
            dp[i + 1][28] += dp[i][27] * 26;

            // uppercase moves forward, lowercase stays the same
            dp[i + 1][28] += dp[i][28] * 26;
        }
    }

    mi ans;
    for (int i = 0; i < 29; i++) {
        ans += dp[n][i];
    }

    cout << ans.v << '\n';

    return 0;
}
