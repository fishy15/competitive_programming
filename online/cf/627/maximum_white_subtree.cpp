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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<bool> white(n);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        white[i] = (a == 1);
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> best(n);
    auto dfs_best = [&](auto self, int v, int p) -> void {
        for (auto e : adj[v]) {
            if (e != p) {
                self(self, e, v);
                best[v] += max(0, best[e]);
            }
        }

        if (white[v]) {
            best[v]++;
        } else {
            best[v]--;
        }
    };

    dfs_best(dfs_best, 0, 0);

    vector<int> ans(n);
    auto dfs_ans = [&](auto self, int v, int p, int best_up) -> void {
        ans[v] = best[v] + best_up;
        best_up += best[v];
        for (auto e : adj[v]) {
            if (e != p) {
                best_up -= max(0, best[e]);
                self(self, e, v, max(0, best_up));
                best_up += max(0, best[e]);
            }
        }
    };

    dfs_ans(dfs_ans, 0, 0, 0);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';

    return 0;
}
