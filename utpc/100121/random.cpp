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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100010

using namespace std;

struct mi {
    ll v;
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

int n;
int nums[MAXN];
vector<int> adj[MAXN];
mi sum;

int sz[MAXN];
bool vis[MAXN];

int dfs_size(int v, int p) {
    sz[v] = 1;
    for (auto e : adj[v]) {
        if (e != p && !vis[e]) {
            sz[v] += dfs_size(e, v);
        }
    }
    return sz[v];
}

int dfs_root(int v, int p, int n) {
    for (auto e : adj[v]) {
        if (e != p && !vis[e] && 2 * sz[e] > n) {
            return dfs_root(e, v, n);
        }
    }
    return v;
}

void dfs_max(int v, int p, int w, vector<pair<int, int>> &mm, int par) {
    w = max(w, nums[v]);
    mm.push_back({w, par});
    for (int e : adj[v]) {
        if (e != p && !vis[e]) {
            dfs_max(e, v, w, mm, par);
        }
    }
}

void dfs_min(int v, int p, int w, vector<pair<int, int>> &mm, int par) {
    w = min(w, nums[v]);
    mm.push_back({w, par});
    for (int e : adj[v]) {
        if (e != p && !vis[e]) {
            dfs_min(e, v, w, mm, par);
        }
    }
}

void solve(int v) {
    dfs_size(v, -1);
    v = dfs_root(v, -1, sz[v]);
    vis[v] = true;

    vector<pair<int, int>> max;
    vector<pair<int, int>> min;
    for (int e : adj[v]) {
        if (!vis[e]) {
            dfs_max(e, v, nums[v], max, e);
            dfs_min(e, v, nums[v], min, e);
        }
    }

    sort(max.begin(), max.end());
    sort(min.rbegin(), min.rend());

    int tot = 0;
    map<int, int> cnt;
    for (auto [x, p] : max) {
        sum += mi(x) * (tot - cnt[p] + 1);
        cnt[p]++;
        tot++;
    }
    
    tot = 0;
    cnt.clear();
    for (auto [x, p] : min) {
        sum -= mi(x) * (tot - cnt[p] + 1);
        cnt[p]++;
        tot++;
    }

    for (int e : adj[v]) {
        if (!vis[e]) {
            solve(e);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b; 
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    solve(0);
    cout << sum.v << '\n';
    sum *= 2;
    sum /= n;
    sum /= n - 1;

    cout << sum.v << '\n';

    return 0;
}
