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

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int n;
    cin >> n;
    
    vector<ll> a(n);
    for (auto &x : a) {
        cin >> x;
    }

    int q;
    cin >> q;
    vector<vector<pair<int, int>>> ops_at(n + 1);
    for (int i = 1; i <= q; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        l--;
        ops_at[l].push_back({x, i});
        ops_at[r].push_back({-x, i});
    }

    set<int> valid;
    for (int i = 0; i <= q; i++) {
        valid.insert(i);
    }

    for (int i = 0; i <= n; i++) {
        vector<pair<ll, int>> ranges = {{0, 0}};
        ll cur = 0;
        for (auto [x, t] : ops_at[i]) {
            cur += x;
            ranges.push_back({cur, t});
        }

        ll best_val = INFLL;
        int sz = ranges.size();

        // only want to min if range contains number
        for (int i = 0; i < sz; i++) {
            auto [v, start] = ranges[i];
            int end = (i == sz - 1) ? q+1 : ranges[i+1].second;

            auto it = valid.lower_bound(start);
            if (it != valid.lower_bound(end)) {
                best_val = min(best_val, v);
            }
        }

        for (int i = 0; i < sz; i++) {
            auto [v, start] = ranges[i];
            if (v != best_val) {
                int end = (i == sz - 1) ? q+1 : ranges[i+1].second;
                auto start_it = valid.lower_bound(start);
                auto end_it = valid.lower_bound(end);
                valid.erase(start_it, end_it);
            }
        }
    }

    int ans = *valid.begin();
    vector<ll> psum(n+1);
    for (int i = 0; i <= n; i++) {
        for (auto [x, t] : ops_at[i]) {
            if (t <= ans) {
                psum[i] += x;
            }
        }
    }

    ll cur = 0;
    for (int i = 0; i < n; i++) {
        cur += psum[i];
        cout << a[i] + cur << ' ';
    }
    cout << '\n';
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
