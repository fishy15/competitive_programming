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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n, k;
vector<vector<pair<int ,int>>> adj;
// 0 not included, 1 included
vector<array<ll, 2>> dp;

void dfs(int v, int p) {
    if (v != 1 && adj[v].size() == 1) {
        dp[v][1] = adj[v][0].second;
    } else {
        vector<pair<ll, ll>> diff;
        ll sum = 0;
        for (auto e : adj[v]) {
            if (e.first != p) {
                dfs(e.first, v);
                if (dp[e.first][0] < dp[e.first][1]) {
                    diff.push_back({dp[e.first][0], dp[e.first][1]});
                } else {
                    sum += dp[e.first][0]; 
                }
            } else {
                dp[v][1] = e.second;
            }
        }

        sort(diff.begin(), diff.end(), [](const pair<ll, ll> &p1, const pair<ll, ll> &p2){
            return (p1.first - p1.second) < (p2.first - p2.second);
        });

        dp[v][0] = sum;
        dp[v][1] += sum;

        for (int i = 0; i < diff.size(); i++) {
            // cout << diff[i].first << ' ' << diff[i].second << '\n';
            if (i < k) {
                dp[v][0] += diff[i].second;
            } else {
                dp[v][0] += diff[i].first;
            }

            if (i < k - 1) {
                dp[v][1] += diff[i].second;
            } else {
                dp[v][1] += diff[i].first;
            }
        }
    }

    // cout << '\t' << v << ' ' << dp[v][0] << ' ' << dp[v][1] << '\n';

}

void solve() {
    cin >> n >> k;
    adj = vector<vector<pair<int, int>>>(n + 1);
    dp = vector<array<ll, 2>>(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int a, b, w; cin >> a >> b >> w;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }

    dfs(1, 1);

    cout << dp[1][0] << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int q; cin >> q;
    while (q--) {
        solve();
    }
    

    return 0;
}
