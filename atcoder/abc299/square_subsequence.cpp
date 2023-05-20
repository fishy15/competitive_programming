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

    array<int, 26> cur_nxt{};
    cur_nxt.fill(-1);

    vector<array<int, 26>> nxt(n);
    for (int i = n - 1; i >= 0; i--) {
        nxt[i] = cur_nxt;
        cur_nxt[s[i] - 'a'] = i;
    }

    vector dp(n, vector<mi>(n));
    mi ans;
    for (int s2 = 0; s2 < n; s2++) {
        // this means it is the first occurence
        int s1 = cur_nxt[s[s2] - 'a'];
        if (s1 == s2) {
            continue;
        }

        // clear everything
        for (auto &v : dp) {
            fill(v.begin(), v.end(), 0);
        }

        dp[s1][s2] = 1;
        for (int i = s1; i < s2; i++) {
            for (int j = s2; j < n; j++) {
                for (int c = 0; c < 26; c++) {
                    int n1 = nxt[i][c];
                    int n2 = nxt[j][c];

                    if (n1 != -1 && n2 != -1) {
                        dp[n1][n2] += dp[i][j];
                    }
                }

                if (nxt[i][s[s2] - 'a'] == s2) {
                    ans += dp[i][j];
                }
            }
        }
    }
    
    cout << ans.v << '\n';

    return 0;
}
