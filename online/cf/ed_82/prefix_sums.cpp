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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 150000

using namespace std;

int n;
vector<int> adj[MAXN];
ll val[MAXN];
bool vis[MAXN];
int sz[MAXN];
ll ans;
int croot;

ll sum[MAXN];
// up and down are switched oops
ll up[MAXN];
ll down[MAXN];
int depth[MAXN];
int par[MAXN];

struct line {
    mutable ll m, b, l;
    line(ll m, ll b) : m(m), b(b), l(0) {}
    bool operator<(const line& other) const { return m < other.m; }
    bool operator<(const ll x) const { return l < x; }
};
template<bool GET_MAX>
struct cht : multiset<line, less<>> {
    // double: inf = 1/.0, div(a, b) = a / b
    static const ll inf = INFLL;
    ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a & b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) { x->l = inf; return false; }
        if (x->m == y->m) x->l = x->b > y->b ? inf : -inf;
        else x->l = div(y->b - x->b, x->m - y->m);
        return x->l >= y->l;
    }
    void add(line l) {
        if (!GET_MAX) l.m = -l.m, l.b = -l.b; 
        auto z = insert(l), y = z++, x = y;
        while(isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->l >= y->l) isect(x, erase(y));
    }
    ll qry(ll x) {
        auto l = *lower_bound(x);
        return (l.m * x + l.b) * (GET_MAX ? 1 : -1);
    }
};

void dfs_calc(int v, int p, vector<vector<int>> &cc) {
    par[v] = p;
    if (p != -1) {
        sum[v] = sum[p];
        up[v] = up[p] + sum[p];
        down[v] = down[p];
        depth[v] = depth[p];
        cc.rbegin()->push_back(v);
    } else {
        sum[v] = 0;
        up[v] = 0;
        down[v] = 0;
        depth[v] = 0;
    }
    sum[v] += val[v];
    up[v] += val[v];
    depth[v]++;
    down[v] += depth[v] * val[v];
    ans = max(up[v], ans);
    ans = max(down[v], ans);

    for (int e : adj[v]) {
        if (e != p && !vis[e]) {
            if (p == -1) {
                cc.push_back({});
            }
            dfs_calc(e, v, cc);
        }
    }
}

int dfs_size(int v, int p) {
    sz[v] = 1;
    for (int e : adj[v]) {
        if (e != p && !vis[e]) {
            sz[v] += dfs_size(e, v);
        }
    }
    return sz[v];
}

int dfs_root(int v, int p, int n) {
    for (int e : adj[v]) {
        if (e != p && !vis[e] && 2 * sz[e] > n) {
            return dfs_root(e, v, n);
        }
    }
    return v;
}

void proc(int v) {
    dfs_size(v, -1);
    int c = dfs_root(v, -1, sz[v]);
    vis[c] = true;
    vector<vector<int>> cc = {};
    dfs_calc(c, -1, cc);

    // get info for this tree
    cht<true> cht;
    for (int i = 0; i < (int)(cc.size()); i++) {
        for (int j : cc[i]) {
            if (!cht.empty()) {
                ans = max(ans, cht.qry(depth[j] - 1) + up[j] - depth[j] * val[c]);
            }
        }
        for (int j : cc[i]) {
            cht.add({sum[j], down[j]});
        }
    }

    cht = {};
    for (int i = (int)(cc.size()) - 1; i >= 0; i--) {
        for (int j : cc[i]) {
            if (!cht.empty()) {
                ans = max(ans, cht.qry(depth[j] - 1) + up[j] - depth[j] * val[c]);
            }
        }
        for (int j : cc[i]) {
            cht.add({sum[j], down[j]});
        }
    }

    // solve children of centroid 
    for (int e : adj[c]) {
        if (!vis[e]) {
            proc(e);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }

    dfs_size(0, -1);
    croot = dfs_root(0, -1, sz[0]);
    proc(croot);

    cout << ans << '\n';

    return 0;
}
