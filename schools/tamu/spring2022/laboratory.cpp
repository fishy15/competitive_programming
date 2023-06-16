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
#include <bitset>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

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

int n;
string s;
int nums[MAXN];
mi mcnt[1 << 20];
mi subset[1 << 20];

array<int, 20> cnt[MAXN];

void reduce() {
    map<char, int> idx;
    int c = 0;

    for (int i = 0; i < n; i++) {
        if (!idx.count(s[i])) {
            idx[s[i]] = c++;
        }

        nums[i] = idx[s[i]];
    }
}

int get_mask(int l, int r) {
    int res = 0;

    for (int i = 0; i < 20; i++) {
        if (cnt[r][i] - cnt[l][i] > 0) {
            res += 1 << i;
        }
    }

    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> n >> s;
    reduce();

    for (int i = 0; i < n; i++) {
        cnt[i + 1] = cnt[i];
        cnt[i + 1][nums[i]]++;
    }

    for (int r = 1; r <= n; r++) {
        int cur_mask = get_mask(r - 1, r);
        int cur_start = r - 1;

        while (true) {
            int lo = 0;
            int hi = cur_start;
            int ans = -1;

            while (lo <= hi) {
                int m = (lo + hi) / 2;
                if (get_mask(m, r) == cur_mask) {
                    hi = m - 1;
                    ans = m;
                } else {
                    lo = m + 1;
                }
            }

            mcnt[cur_mask] += cur_start - ans + 1;
            if (ans == 0) break;

            cur_mask = get_mask(ans - 1, r);
            cur_start = ans - 1;
        }
    }

    for (int i = 0; i < (1 << 20); i++) {
        subset[i] = mcnt[i];
    }

    for (int i = 0; i < 20; i++) {
        for (int m = 0; m < (1 << 20); m++) {
            if (m & (1 << i)) {
                subset[m] += subset[m ^ (1 << i)];
            }
        }
    }

    mi ans;
    int inv = (1 << 20) - 1;
    for (int i = 0; i < (1 << 20); i++) {
        ans += mcnt[i] * subset[inv ^ i];
    }

    ans /= 2;

    cout << ans.v << '\n';

    return 0;
}
