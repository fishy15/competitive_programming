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

    int n, q;
    cin >> n >> q;

    vector<vector<pair<int, int>>> adj1(n), adj2(n);

    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;

        adj1[a].push_back({b, w});
        adj1[b].push_back({a, w});
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;

        adj2[a].push_back({b, w});
        adj2[b].push_back({a, w});
    }

    auto solve = [&](int s, auto &adj, auto &d) {
        auto dfs = [&](auto self, int v, int p, ll tot_d) {
            d[v] = tot_d;
            for (auto [e, w] : adj[v]) {
                if (e != p) {
                    self(e, v, tot_d + w);
                }
            }
        };

        dfs(dfs, s, -1);
    };

    sove(

    return 0;
}
