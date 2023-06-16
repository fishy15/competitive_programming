/*
 * For each tree in the forest, we can calculate m[len] = {tot_len, cnt}. Specifically, for each possible 
 * path between two nodes in the tree, len is the length of the path (if the length is longer than y, it is
 * stored as y), tot_len is the sum of the lengths of all of the paths of that length, and cnt is the number
 * of paths of that length. To calculate the map after we combine two trees, we note that for given lengths
 * len1 and len2 for each tree, the total length combined is tot_len1 * cnt2 + tot_len2 * cnt1, and the total
 * count is cnt1 * cnt2. We can use this procedure to merge all of the trees' information. 
 *
 * To see why this runs in time, if the size of the tree is small enough, then the map will be sparsely 
 * populated, which reduces the time of merging. On the other hand, if the size of the tree is large, then 
 * there will be fewer trees total, but the number of values in the map will be capped at Y. The worst case 
 * is when there are sqrt(Y) values in the tree and Y values in the map. Therefore, the time complexity is
 * O(N^2 log N + NY^1.5) overall.
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
#include <unordered_map>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 3000

using namespace std;

struct mll {
    ll v;
    mll() : mll(0) {}
    mll(ll v) : v(v) {}
    mll &operator+=(const mll &m2) {
        v += m2.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    mll operator+(const mll &m2) {
        mll m(v);
        return m += m2;
    }
    mll &operator*=(const mll &m2) {
        v *= m2.v;
        v %= MOD;
        return *this;
    }
    mll operator*(const mll &m2) {
        mll m(v);
        return m *= m2;
    }
};

typedef unordered_map<int, pair<mll, mll>> mi;

int n, m, x, y;
vector<array<int, 2>> adj[MAXN];
bool vis[MAXN];
int d[MAXN];

int k;
vector<mi> combo;
mi ans;
mi cur_comp;

void dfs(int v, int p) {
    mi res;
    auto &val = cur_comp[min(d[v], y)];
    val.first += d[v];
    val.second += 1;
    for (auto e : adj[v]) {
        if (e[0] != p) {
            d[e[0]] = d[v] + e[1];
            dfs(e[0], v);
        }
    }
}

void calc_dist(int v, int p) {
    d[v] = 0;
    dfs(v, -1);
    vis[v] = true;
    for (auto e : adj[v]) {
        if (e[0] != p) {
            calc_dist(e[0], v);
        }
    }
    cur_comp[0].second += -1;
}

mi merge(const mi &m1, const mi &m2) {
    mi res;
    for (auto p1 : m1) {
        for (auto p2 : m2) {
            int val = min(p1.first + p2.first, y);
            mll ways = p1.second.second * p2.second.second;
            mll tot_len = p1.second.first * p2.second.second + p1.second.second * p2.second.first;
            
            auto &loc = res[val];
            loc.first += tot_len;
            loc.second += ways;
        }
    }
    return res;
}

mll modpow(mll n, ll e) {
    mll ans = 1;
    while (e) {
        if (e & 1) ans = ans * n;
        n = n * n;
        e >>= 1;
    }
    return ans;
}

int main() {
    ifstream fin("mooriokart.in");
    ofstream fout("mooriokart.out");

    fin >> n >> m >> x >> y;
    
    for (int i = 0; i < m; i++) {
        int a, b, w; fin >> a >> b >> w;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            cur_comp = {};
            calc_dist(i, -1);
            combo.push_back(cur_comp);
        }
    }

    k = (int)(combo.size());
    ans[min(k * x, y)] = {k * x, 1};

    for (const auto &m : combo) {
        ans = merge(ans, m);
    }

    mll ans_combo = ans[y].first;
    for (int i = 1; i < k; i++) {
        ans_combo *= i;
    }

    ans_combo *= modpow(2, MOD - 2);

    fout << ans_combo.v << '\n';

    return 0;
}
