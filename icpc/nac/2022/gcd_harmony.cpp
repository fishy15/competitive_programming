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
#include <cassert>

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

constexpr int MAXN = 100;

bool isprime[MAXN + 1];
vector<int> primes;
vector<int> try_nxt;

void precomp() {
    fill(begin(isprime) + 2, end(isprime), true);
    for (int i = 2; i <= MAXN; i++) {
        if (isprime[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= MAXN; j += i) {
                isprime[j] = false;
            }
        }
    }

    constexpr int LIMIT = 2 * 5000;

    for (int m = 0; m < (1 << 25); m++) {
        ll res = 1;
        rep(i, 0, 25) {
            if ((m >> i) & 1) {
                res *= primes[i];
                if (res > LIMIT) break;
            }
        }
        if (res <= LIMIT) {
            try_nxt.push_back(res);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();
    assert(sz(primes) == 25);

    int n;
    cin >> n;

    vector<int> init(n);
    rep(i, 0, n) {
        cin >> init[i];
    }

    vector<vector<int>> adj(n);
    rep(i, 0, n-1) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // dp[v][p] = min cost to solve subtree with multiple of p at root
    vector<array<ll, 101>> dp(n);
    for (auto &v : dp) {
        v.fill(INF);
    }

    vector<int> factors;
    factors.reserve(25);

    auto dfs = [&](auto &&self, int u, int par) -> void {
        for (auto v : adj[u]) {
            if (v != par) {
                self(self, v, u);
            }
        }

        // add this temporarily as an option
        try_nxt.push_back(init[u]);

        for (auto new_val : try_nxt) {
            ll cost = new_val == init[u] ? 0 : new_val;

            factors.clear();
            for (auto p : primes) {
                if (new_val % p == 0) {
                    factors.push_back(p);
                }
            }

            for (auto v : adj[u]) {
                if (v != par) {
                    ll best = INF;
                    for (auto p : factors) {
                        best = min(best, dp[v][p]);
                    }
                    cost += best;
                }
            }

            for (auto p : factors) {
                dp[u][p] = min(dp[u][p], cost);
            }
        }

        try_nxt.pop_back();
    };
    dfs(dfs, 0, -1);

    cout << *min_element(all(dp[0])) << '\n';

    return 0;
}
