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
#define MOD 998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

using vi = vector<int>;
template<class F> vi scc(const vector<vi> &adj, F f) {
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

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi(ll _v) : mi((int)(_v % MOD)) {}
    mi operator+(const mi &m2) const { return mi(v + m2.v); }
    mi operator-(const mi &m2) const { return mi(v - m2.v); }
    mi operator*(const mi &m2) const { return mi((ll) v * m2.v); }
    mi operator/(const mi &m2) const { return mi((ll) v * m2.inv().v); }
    mi &operator+=(const mi &m2) { return *this = *this + m2; }
    mi &operator-=(const mi &m2) { return *this = *this - m2; }
    mi &operator*=(const mi &m2) { return *this = *this * m2; }
    mi &operator/=(const mi &m2) { return *this = *this / m2; }
    mi pow(ll e) const {
        mi res = 1;
        mi n = *this;
        while (e > 0) {
            if (e & 1) res *= n;
            n *= n;
            e >>= 1;
        }
        return res;
    }
    mi inv() const {
        return pow(MOD - 2);
    }
};

void solve() {
    int n;
    cin >> n;

    vector<int> c(2 * n);
    vector locs(n, array{-1, -1});
    rep(i, 0, 2*n) {
        cin >> c[i];
        c[i]--;
        if (locs[c[i]][0] == -1) {
            locs[c[i]][0] = i;
        } else {
            locs[c[i]][1] = i;
        }
    }

    vector radj(n, vector<int>{});
    rep(i, 0, n) {
        rep(j, locs[i][0] + 1, locs[i][1]) {
            radj[c[j]].push_back(i);
        }
    }

    vector<vector<int>> comps;
    auto comp_id = scc(radj, [&](const vector<int> &comp) {
        comps.push_back(comp);
    });

    int ans = 0;
    mi combos = 1;
    rep(i, 0, sz(comps)) {
        bool ok = true;
        for (auto v : comps[i]) {
            for (auto e : radj[v]) {
                if (comp_id[e] != i) {
                    ok = false;
                    break;
                }
            }
        }

        if (ok) {
            ans++;
            combos *= 2 * sz(comps[i]);
        }
    }

    cout << ans << ' ' << combos.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
