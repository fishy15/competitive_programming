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

int n;
ll a[MAXN];
vector<pair<int, int>> adj[MAXN];
bool vis[MAXN];
int sz[MAXN];
ll ans;

struct bit {
    int sz;
    vector<int> b;
    bit (int sz) : sz(sz) {
        b = vector<int>(sz);
    }
    void upd(int x, int v) {
        while (x < sz) {
            b[x] += v;
            x += x & -x;
        }
    }
    int qry(int x) {
        int res = 0;
        while (x) {
            res += b[x];
            x -= x & -x;
        }
        return res;
    }
};

int dfs_size(int v, int p) {
    sz[v] = 1;
    for (auto [e, w] : adj[v]) {
        if (e != p && !vis[e]) {
            sz[v] += dfs_size(e, v);
        }
    }
    return sz[v];
}

int dfs_root(int v, int p, int n) {
    for (auto [e, w] : adj[v]) {
        if (e != p && !vis[e] && 2 * sz[e] > n) {
            return dfs_root(e, v, n);
        }
    }
    return v;
}

// how much you need to go from centroid to v
map<ll, int> dfs_need(int v, int p, ll prev_min, ll cur, ll w) {
    map<ll, int> ans;
    ll nxt = cur - w;
    prev_min = min(prev_min, nxt);
    if (prev_min < 0) {
        ans[-prev_min] = 1;
    } else {
        ans[0] = 1;
    }
    nxt += a[v];

    for (auto [e, w] : adj[v]) {
        if (e != p && !vis[e]) {
            map<ll, int> res = dfs_need(e, v, prev_min, nxt, w);
            if (res.size() > ans.size()) swap(res, ans);
            for (auto p : res) {
                ans[p.first] += p.second;
            }
        }
    }

    return ans;
}

// how much extra you will have from going v to centroid
map<ll, int> dfs_extra(int v, int p, ll prev_min, ll cur, ll w) {
    map<ll, int> ans;
    ll nxt_min = min(a[v] - w, prev_min + a[v] - w);
    ll nxt = cur + a[v] - w;
    if (nxt_min >= 0) {
        ans[nxt] = 1;
    }

    for (auto [e, w] : adj[v]) {
        if (e != p && !vis[e]) {
            map<ll, int> res = dfs_extra(e, v, nxt_min, nxt, w);
            if (res.size() > ans.size()) swap(res, ans);
            for (auto p : res) {
                ans[p.first] += p.second;
            }
        }
    }

    return ans;
}

void solve(int v) {
    dfs_size(v, -1);
    int c = dfs_root(v, -1, sz[v]);
    vis[c] = true;

    vector<map<ll, int>> need;
    vector<map<ll, int>> extra;
    set<ll> nums;
    map<ll, int> comp;

    for (auto [e, w] : adj[c]) {
        if (!vis[e]) {
            need.push_back(dfs_need(e, c, a[c], a[c], w));
            extra.push_back(dfs_extra(e, c, 0, 0, w));
            for (auto p : need.back()) {
                nums.insert(p.first);
                if (p.first == 0) ans += p.second;
            }
            for (auto p : extra.back()) {
                nums.insert(p.first);
                ans += p.second;
            }
        }
    }

    int t = 1;
    for (ll x : nums) {
        comp[x] = t++;
    }

    bit b(t + 5);
    for (auto &m : need) {
        for (auto p : m) {
            b.upd(comp[p.first], p.second);
        }
    }

    for (int i = 0; i < (int)(extra.size()); i++) {
        for (auto p : need[i]) {
            b.upd(comp[p.first], -p.second);
        }
        for (auto p : extra[i]) {
            ans += p.second * b.qry(comp[p.first]);
        }
        for (auto p : need[i]) {
            b.upd(comp[p.first], p.second);
        }
    }

    for (auto [e, w] : adj[c]) {
        if (!vis[e]) {
            solve(e);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    solve(0);
    cout << ans << '\n';

    return 0;
}
