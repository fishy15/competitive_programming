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
using vi = vector<int>;

constexpr int MAXN = 50000;

template<typename F> vi scc(const vector<vi> &adj, F f) {
    int n = sz(adj);
    vi val(n), comp(n, -1), z, cont;
    int time = 0, ncomps = 0;
    auto dfs = [&](auto &&self, int u) -> int {
        int low = val[u] = ++time, x; z.push_back(u);
        for (auto e : adj[u]) if (comp[e] < 0)
            low = min(low, val[e] ?: self(self, e));
        if (low == val[u]) {
            do {
                x = z.back(); z.pop_back();
                comp[x] = ncomps;
                cont.push_back(x);
            } while (x != u);
            f(cont); cont.clear();
            ncomps++;
        }
        return val[u] = low;
    };
    rep(i, 0, n) {
        if (comp[i] < 0) dfs(dfs, i);
    }
    return comp;
}

template<int N>
void solve(int n, int m, const vector<vector<int>> &adj, const vector<pair<int, int>> &qry) {
    if (N < n) {
        solve<min(2 * N, MAXN)>(n, m, adj, qry);
        return;
    }

    vector<int> vis(n);
    vector<bitset<N>> reachable(n);

    scc(adj, [&](const vi &comp) {
        bitset<N> cur_comp;
        for (auto v : comp) {
            cur_comp[v] = 1;
            for (auto e : adj[v]) {
                cur_comp |= reachable[e];
            }
        }
        for (auto v : comp) {
            reachable[v] = cur_comp;
        }
    });

    for (auto [a, b] : qry) {
        if (reachable[a][b]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, q;
    cin >> n >> m >> q;;

    vector adj(n, vector<int>{});
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
    }

    vector<pair<int, int>> qry(q);
    for (auto &[a, b] : qry) {
        cin >> a >> b;
        a--;
        b--;
    }

    solve<1>(n, m, adj, qry);

    return 0;
}
