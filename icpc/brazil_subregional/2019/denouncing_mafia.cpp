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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    vector<vector<int>> child(n);
    rep(i, 1, n) {
        int p;
        cin >> p;
        p--;
        child[p].push_back(i);
    }

    vector<int> d(n);
    auto dfs = [&](auto &&self, int v) -> void {
        d[v] = 1;
        for (auto e : child[v]) {
            self(self, e);
            d[v] = max(d[v], d[e] + 1);
        }
    };

    dfs(dfs, 0);

    // depth, node
    priority_queue<pair<int, int>> pq;
    pq.push({d[0], 0});

    // returns best child, -1 if empty
    auto process_node = [&](int v) -> int {
        pair<int, int> best = {0, -1};
        for (auto e : child[v]) {
            best = max(best, pair{d[e], e});
        }

        for (auto e : child[v]) {
            if (e != best.second) {
                // split this off into its own component
                pq.push({d[e], e});
            }
        }

        return best.second;
    };

    auto process_path = [&](int root) {
        while (root != -1) {
            root = process_node(root);
        }
    };

    int ans = 0;
    int taken = 0;
    while (!pq.empty() && taken < k) {
        auto [depth, v] = pq.top();
        pq.pop();

        ans += depth;
        process_path(v);
        taken++;
    }

    cout << ans << '\n';

    return 0;
}
