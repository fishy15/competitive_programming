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

void solve() {
    int n, k;
    cin >> n >> k;

    auto dub = 2*k;

    vector<int> a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }

    sort(all(a));

    vector<int> cov(2 * k);
    for (auto x : a) {
        x %= dub;
        if (x < k) {
            cov[x]++;
            cov[x + k]--;
        } else {
            auto rot = x - k;
            cov[0]++;
            cov[rot]--;
            cov[x]++;
        }
    }

    rep(i, 1, dub) {
        cov[i] += cov[i - 1];
    }

    auto last = a.back();
    auto nxt_mul = (last + dub - 1) / dub * dub;

    int ans = -1;
    rep(i, 0, dub) {
        if (cov[i] == n) {
            auto pos = nxt_mul + i;
            if (pos - dub >= last) {
                pos -= dub;
            }
            
            if (ans == -1) {
                ans = pos;
            } else {
                ans = min(ans, pos);
            }
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
