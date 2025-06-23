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
    ll n, m;
    cin >> n >> m;

    vector<ll> ans;
    ll cur = n;
    vector<ll> extra;
    vector<bool> placed(n+1);
    rep(i, 0, n) {
        // if we place cur down, then what happens
        ll after = n-i-1;
        while (cur > 0 && m-cur < after) {
            if (!placed[cur]) {
                extra.push_back(cur);
            }
            cur--;
        }

        if (placed[cur] && extra.empty()) {
            cur--;
        }

        if (cur < 0) {
            cout << "-1\n";
            return;
        }

        if (m - cur >= after) {
            if (!placed[cur]) {
                placed[cur] = true;
                ans.push_back(cur);
                m -= cur;
            } else {
                auto x = extra.back();
                extra.pop_back();
                ans.push_back(x);
                placed[x] = true;
                m -= cur;
            }
        }
    }

    if (m == 0) {
        cout << ans[0] << '\n';
        rep(i, 0, n-1) {
            cout << ans[i] << ' ' << ans[i+1] << '\n';
        }
    } else {
        cout << "-1\n";
    }
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
