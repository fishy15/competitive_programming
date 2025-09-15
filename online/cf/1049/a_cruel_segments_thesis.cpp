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
    int n;
    cin >> n;

    vector<pair<ll, ll>> segs(n);
    rep(i, 0, n) {
        cin >> segs[i].first >> segs[i].second;
    }

    ll r_sum = 0;
    vector<pair<ll, int>> ord;
    ll base = 0;
    rep(i, 0, n) {
        r_sum += segs[i].second;
        ord.push_back({segs[i].first + segs[i].second, i});
        base += segs[i].second - segs[i].first;
    }
    sort(all(ord));

    ll half_sum = 0;
    set<int> in_half;
    rep(i, 0, n / 2) {
        half_sum += ord[i].first;
        in_half.insert(ord[i].second);
    }

    if (n % 2 == 0) {
        cout << base + (r_sum - half_sum) << '\n';
    } else {
        ll ans = 0;

        int mid = ord[n / 2].second;
        rep(i, 0, n) {
            auto cur_r_sum = r_sum - segs[i].second;
            ll cur_half_sum;
            if (in_half.count(i)) {
                cur_half_sum = half_sum 
                    - (segs[i].first + segs[i].second)
                    + (segs[mid].first + segs[mid].second);
            } else {
                cur_half_sum = half_sum;
            }

            ans = max(ans, base + (cur_r_sum - cur_half_sum));
        }
        
        cout << ans << '\n';
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
