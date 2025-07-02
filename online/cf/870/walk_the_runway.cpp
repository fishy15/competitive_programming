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

    int m, n;
    cin >> m >> n;

    vector<ll> p(n);
    rep(i, 0, n) {
        cin >> p[i];
    }

    vector rating(m, vector<short>(n));
    rep(show, 0, m) {
        rep(model, 0, n) {
            cin >> rating[show][model];
            rating[show][model]--;
        }
    }

    bitset<5000> all_ones;
    rep(i, 0, n) {
        all_ones[i] = 1;
    }

    vector works(n, all_ones);
    vector<bitset<5000>> smaller_models(n);
    rep(show, 0, m) {
        for (auto &bs : smaller_models) bs.reset();
        rep(model, 0, n) {
            auto r = rating[show][model];
            if (r < n-1) {
                smaller_models[r+1][model] = 1;
            }
        }
        rep(r, 1, n) {
            smaller_models[r] |= smaller_models[r-1];
        }
        rep(model, 0, n) {
            works[model] &= smaller_models[rating[show][model]];
        }
    }

    vector<vector<short>> smaller_adj(n);
    rep(i, 0, n) {
        rep(model, 0, n) {
            if (works[i][model]) {
                smaller_adj[i].push_back(model);
            }
        }
    }

    vector<bool> vis(n);
    vector<ll> ans(n);

    auto solve = [&](auto &&self, int model) -> ll {
        if (!vis[model]) {
            vis[model] = true;
            ll best = 0;
            for (auto nxt : smaller_adj[model]) {
                best = max(best, self(self, nxt));
            }
            ans[model] = best + p[model];
        }
        return ans[model];
    };

    rep(i, 0, n) {
        solve(solve, i); 
    }

    cout << *max_element(all(ans)) << '\n';

    return 0;
}
