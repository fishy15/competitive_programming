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

    int n;
    cin >> n;

    vector<int> c(n);
    rep(i, 0, n) {
        cin >> c[i];
    }

    vector adj(n, vector<int>{});
    rep(i, 0, n-1) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int t = 0;
    vector<int> par(n);
    vector<int> in(n), out(n);
    vector<int> csum(n);

    auto dfs = [&](auto &&self, int v, int p) -> void {
        in[v] = t++;
        par[v] = p;
        csum[v] = c[v];
        for (auto e : adj[v]) {
            if (e != p) {
                self(self, e, v);
                csum[v] += csum[e];
            }
        }
        out[v] = t++;
    };
    dfs(dfs, 0, 0);

    // gets the c sum in the subtree rooted at v, away from p
    auto get_count = [&](int v, int p) {
        if (par[v] == p) {
            return csum[v];
        } else {
            return csum[0] - csum[p];
        }
    };

    vector<int> true_cnt(2 * n);

    // mark true in the subtree of v, away from p
    auto mark_subtree = [&](int v, int p, int delta) {
        if (par[v] == p) {
            true_cnt[in[v]] += delta;
            true_cnt[out[v]] -= delta;
        } else {
            true_cnt[in[0]] += delta;
            true_cnt[out[0]] -= delta;
            true_cnt[in[p]] -= delta;
            true_cnt[out[p]] += delta;
        }
    };

    auto check_center = [&](int v) {
        int cnt = 0;
        for (auto e : adj[v]) {
            if (c[e] == 1 && cnt < 2) {
                cnt++;
                if (c[v] == 1 || get_count(e, v) > 1) {
                    // we can reach everything except for in the direction of e
                    mark_subtree(v, e, 1);
                } else {
                    for (auto e2 : adj[v]) {
                        if (e != e2) {
                            if (get_count(e2, v) > 0) {
                                // we can get everything except for in the direction of e and e2
                                mark_subtree(v, e, 1);
                                mark_subtree(e2, v, -1);
                            }
                        }
                    }
                }
            }
        }
    };

    rep(i, 0, n) {
        check_center(i);
    }

    rep(i, 1, 2*n) {
        true_cnt[i] += true_cnt[i-1];
    }

    rep(i, 0, n) {
        auto works = (true_cnt[in[i]] > 0) || (c[i] == 1);
        cout << works << ' ';
    }
    cout << '\n';

    return 0;
}
