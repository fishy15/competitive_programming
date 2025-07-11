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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> a(n);
    rep(i, 0, n) {
        cin >> a[i].first;
        a[i].second = i;
    }

    sort(all(a), greater<>{});

    vector<int> b(m);
    rep(i, 0, m) {
        cin >> b[i];
    }

    vector<vector<pair<int, int>>> best_ints;
    rep(i, 0, m) {
        auto diff = b[i];
        // start and size
        vector<pair<int, int>> last_ints;
        for (int j = n; j >= 1; j--) {
            auto goal = (diff + j - 1) / j;
            auto last_works = (int) (upper_bound(all(a), pair{goal, -1}, greater<>{}) - begin(a));
            if (last_works >= j) {
                while (!last_ints.empty() && last_ints.back().first <= last_works - j) {
                    last_ints.pop_back();
                }
                last_ints.push_back({last_works - j, j});
            }
        }
        reverse(all(last_ints));
        best_ints.push_back(last_ints);
    }

    vector<int> dp(1 << m, INF);
    vector<int> used(1 << m, -1);
    dp[0] = 0;
    rep(mask, 1, 1 << m) {
        rep(i, 0, m) {
            if ((mask >> i) & 1) {
                auto prev_mask = mask ^ (1 << i);
                auto prev_end = dp[prev_mask];
                auto it = lower_bound(all(best_ints[i]), pair{prev_end, 0});
                if (it != end(best_ints[i])) {
                    auto cost = prev_end + it->second;
                    if (cost < dp[mask]) {
                        dp[mask] = cost;
                        used[mask] = i;
                    }
                }
            }
        }
    }

    auto last = (1 << m) - 1;
    if (dp[last] == INF) {
        cout << "NO\n";
        return 0;
    }

    vector<vector<int>> per_project(m);
    int cur_mask = last;
    while (used[cur_mask] != -1) {
        auto i = used[cur_mask];
        auto prev_mask = cur_mask ^ (1 << i);
        rep(j, dp[prev_mask], dp[cur_mask]) {
            per_project[i].push_back(a[j].second);
        }
        cur_mask = prev_mask;
    }

    cout << "YES\n";
    rep(i, 0, m) {
        cout << sz(per_project[i]) << ' ';
        for (auto x : per_project[i]) {
            cout << x+1 << ' ';
        }
        cout << '\n';
    }


    return 0;
}
