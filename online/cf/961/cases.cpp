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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

int to_mask(const array<int, 18> &arr, int c) {
    int res = 0;
    rep(i, 0, c) {
        if (arr[i] == 0) {
            res ^= 1 << i;
        }
    }
    return res;
}

void solve() {
    int n, c, k;
    cin >> n >> c >> k;

    string s;
    cin >> s;

    vector<bool> bad(1 << c);
    array<int, 18> cnts{};
    rep(i, 0, k) {
        cnts[s[i] - 'A']++;
    }
    bad[to_mask(cnts, c)] = true;
    rep(i, k, n) {
        cnts[s[i - k] - 'A']--;
        cnts[s[i] - 'A']++;
        bad[to_mask(cnts, c)] = true;
    }

    for (int m = (1 << c) - 1; m >= 0; m--) {
        if (bad[m]) {
            rep(j, 0, c) {
                if (m & (1 << j)) {
                    bad[m ^ (1 << j)] = true;
                }
            }
        }
    }

    int ans = c;
    int last_c = s.back() - 'A';
    rep(m, 0, 1 << c) {
        if (!bad[m] && (m & (1 << last_c))) {
            ans = min(ans, __builtin_popcount(m));
        }
    }

    cout << ans << '\n';
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
