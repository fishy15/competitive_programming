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

vector<int> get_subtree_sz(const vector<vector<int>> &adj) {
    int n = adj.size();

    vector<int> sz(n, 1);
    auto dfs = [&](auto self, int v, int p) -> void {
        for (auto e : adj[v]) {
            if (e != p) {
                self(self, e, v);
                sz[v] += sz[e];
            }
        }
    };

    dfs(dfs, 0, 0);
    return sz;
}

int find_centroid(const vector<vector<int>> &adj, const vector<int> &sz) {
    int n = adj.size();

    auto dfs = [&](auto self, int v, int p) -> int {
        for (auto e : adj[v]) {
            if (e != p && sz[e] > n / 2) {
                return self(self, e, v);
            }
        }
        return v;
    };

    return dfs(dfs, 0, 0);
}

ll best_split(int C, vector<int> &sizes) {
    // apply C sqrt(C) / 64 knapsack trick
    vector<int> counts(C + 1);
    for (auto x : sizes) {
        counts[x]++;
    }

    for (int i = 1; i <= C; i++) {
        if (counts[i] > 0) {
            auto extra = (counts[i] - 1) / 2;
            if (extra > 0) {
                counts[i] -= 2 * extra;
                counts[2 * i] += extra;
            }
        }
    }

    vector<int> new_sizes;
    for (int i = 1; i <= C; i++) {
        for (int j = 0; j < counts[i]; j++) {
            new_sizes.push_back(i);
        }
    }

    bitset<1'000'001> dp;

    dp[0] = 1;
    for (auto x : new_sizes) {
        dp |= dp << x;
    }

    int set1 = 0;
    for (int i = C / 2; i >= 0; i--) {
        if (dp[i]) {
            set1 = i;
            break;
        }
    }

    auto set2 = C - set1;
    return (ll) set1 * set2;
}

ll sum_paths_to(const vector<vector<int>> &adj, int c) {
    ll sum = 0;

    auto dfs = [&](auto self, int v, int p, int dist) -> void {
        sum += dist + 1;
        for (auto e : adj[v]) {
            if (e != p) {
                self(self, e, v, dist + 1);
            }
        }
    };

    dfs(dfs, c, c, 0);
    return sum;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector adj(n, vector<int>());
    vector par(n, 0);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;

        adj[p].push_back(i);
        adj[i].push_back(p);
        par[i] = p;
    }

    auto sz = get_subtree_sz(adj);
    auto c = find_centroid(adj, sz);

    int tot = 0;
    vector<int> szs;
    for (auto e : adj[c]) {
        if (e != par[c]) {
            tot += sz[e];
            szs.push_back(sz[e]);
        }
    }

    if (tot != n - 1) {
        szs.push_back((n - 1) - tot);
    }

    auto ans = best_split(n - 1, szs);
    ans += sum_paths_to(adj, c);

    cout << ans << '\n';

    return 0;
}
