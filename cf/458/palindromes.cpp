/*
 * We can use centroid decomposition to solve this problem. For each centroid's component, we can calculate
 * a hash value where the 1 bit being equal to 1 means there is an odd number of occurences of 'a' on the 
 * path from the centroid to that node (2's place for 'b', 4's place for 'c', etc.). We can then figure out
 * how many hash values of from different subtrees of the centroid pair up such that xor = 0 (or 1, 2, 4, for
 * odd length palindromes). This general strategy tells us how many paths go through the centroid and have
 * and endpoint at a given node, so we can DFS to apply the values to the middle of the path.
 */

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
#define MAXN 200010

using namespace std;

int n;
vector<int> adj[MAXN];
string s;

int sz[MAXN];
bool vis[MAXN];

ll tmp[MAXN];
ll ans[MAXN];
int cnt[1 << 20];

int dfs_sz(int v, int p) {
    sz[v] = 1;
    for (int e : adj[v]) {
        if (e != p && !vis[e]) {
            sz[v] += dfs_sz(e, v);
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

vector<pair<int, int>> dfs_val(int v, int p, int cur) {
    int pp = s[v] - 'a';
    cur ^= 1 << pp;
    vector<pair<int, int>> res = {{cur, v}};
    tmp[v] = 0; // clearing out for later use

    for (int e : adj[v]) {
        if (e != p && !vis[e]) {
            auto vals = dfs_val(e, v, cur);
            if (vals.size() > res.size()) vals.swap(res);
            for (auto x : vals) res.push_back(x);
        }
    }

    return res;
}

void calc(int cur, int root, int on, int to_eq) {
    if (on == to_eq) {
        tmp[cur]++;
        tmp[root] += 2;
    }

    tmp[cur] += cnt[on ^ to_eq];
    tmp[root] += cnt[on ^ to_eq];
}

ll dfs_add(int v, int p) {
    for (int e : adj[v]) {
        if (e != p && !vis[e]) {
            tmp[v] += dfs_add(e, v);
        }
    }
    ans[v] += tmp[v];
    return tmp[v];
}

void proc(int v) {
    dfs_sz(v, -1);
    v = dfs_root(v, -1, sz[v]);
    vis[v] = true;

    vector<vector<pair<int, int>>> vals;
    for (int e : adj[v]) {
        if (!vis[e]) {
            vals.push_back(dfs_val(e, v, 0));
            for (auto p : vals.back()) {
                cnt[p.first]++;
            }
        }
    }

    tmp[v] = 2; // just node by itself, intentionally storing double to half later
    int root_on = 1 << (s[v] - 'a');
    for (const auto &arr : vals) {
        for (const auto &p : arr) {
            cnt[p.first]--;
        }

        for (const auto &p : arr) {
            calc(p.second, v, p.first, root_on);
            for (int i = 0; i < 20; i++) {
                calc(p.second, v, p.first, root_on ^ (1 << i));
            }
        }

        for (const auto &p : arr) {
            cnt[p.first]++;
        }
    }

    for (int e : adj[v]) {
        if (!vis[e]) {
            dfs_add(e, v);
        }
    }

    for (const auto &arr : vals) {
        for (const auto &p : arr) {
            cnt[p.first]--;
        }
    }

    ans[v] += tmp[v] / 2;

    for (int e : adj[v]) {
        if (!vis[e]) {
            proc(e);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    
    cin >> s;

    proc(0);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';

    return 0;
}
