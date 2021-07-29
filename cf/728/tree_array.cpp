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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 210

using namespace std;

int n;
vector<int> adj[MAXN];

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int v) : v(v) {}

    mi &operator+=(const mi &m2) {
        v += m2.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }

    mi operator+(const mi &m2) const {
        mi m = *this;
        return m += m2;
    }

    mi &operator-=(const mi &m2) {
        v -= m2.v;
        if (v < 0) v += MOD;
        return *this;
    }

    mi operator-(const mi &m2) const {
        mi m = *this;
        return m -= m2;
    }

    mi &operator*=(const mi &m2) {
        v = (ll) v * m2.v % MOD;
        return *this;
    }

    mi operator*(const mi &m2) const {
        mi m = *this;
        return m *= m2;
    }

    mi pow(ll e) const {
        mi res = 1;
        mi n = *this;
        while (e) {
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

mi p_win[MAXN][MAXN];

void precalc() {
    mi inv2 = mi(2).inv();
    for (int s = 1; s <= 200; s++) {
        for (int i = 0; i <= s; i++) {
            int j = s - i;
            if (i == 0) {
                p_win[i][j] = 1;
            } else if (j == 0) {
                p_win[i][j] = 0;
            } else {
                p_win[i][j] = (p_win[i - 1][j] + p_win[i][j - 1]) * inv2;
            }
        }
    }
}

mi solve(int root) {
    vector<int> d(n);
    vector<int> in(n);
    vector<int> out(n);
    vector<vector<int>> up(n, vector<int>(9));
    int t = 0;
    
    function<void(int, int)> dfs = [&](int v, int p) {
        in[v] = t++;

        up[v][0] = p;
        for (int i = 1; i < 9; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }

        for (int e : adj[v]) {
            if (e != p) {
                d[e] = d[v] + 1;
                dfs(e, v);
            }
        }

        out[v] = t++;
    };

    auto anc = [&](int u, int v) {
        return in[u] <= in[v] && out[v] <= out[u];
    };

    auto lca = [&](int u, int v) {
        if (anc(u, v)) return u;
        if (anc(v, u)) return v;
        for (int i = 8; i >= 0; i--) {
            if (!anc(up[v][i], u)) v = up[v][i];
        }
        return up[v][0];
    };

    dfs(root, root);
    mi ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int l = lca(i, j);
            int d1 = d[i] - d[l];
            int d2 = d[j] - d[l];
            ans += p_win[d2][d1];
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    mi ans = 0;
    mi invn = mi(n).inv();
    for (int i = 0; i < n; i++) {
        ans += solve(i) * invn;
    }

    cout << ans.v << '\n';

    return 0;
}
