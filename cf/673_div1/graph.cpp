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
#define MAXN 500010

using namespace std;

int n, m, q;

int dsu[MAXN];
int sz[MAXN];
pair<int, int> edge[MAXN];
pair<int, int> qry[MAXN];
int val[MAXN];
pair<int, int> st[8 * MAXN];
vector<int> adj[MAXN];
int in[MAXN];
int out[MAXN];
int t;
bool vis[MAXN];

int cur;

int get(int x) {
    if (x == dsu[x]) return x;
    return dsu[x] = get(dsu[x]);
}

void join(int i, int j) {
    if ((i = get(i)) != (j = get(j))) {
        dsu[j] = i;
        sz[i] += sz[j];
    }
}

void mk_edge(int i, int j) {
    if ((i = get(i)) != (j = get(j))) {
        cur++;
        join(cur, i);
        join(cur, j);
        adj[cur].push_back(i);
        adj[i].push_back(cur);
        adj[cur].push_back(j);
        adj[j].push_back(cur);
    }
}

void dfs(int v) {
    vis[v] = true;
    in[v] = ++t;
    for (int i : adj[v]) {
        if (!vis[i]) dfs(i);
    }
    out[v] = t;
}

void build(int v = 1, int l = 0, int r = t) {
    if (l == r) {
        st[v] = {0, l};
    } else {
        int m = (l + r) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        st[v] = max(st[2 * v], st[2 * v + 1]);
    }
}

void upd(int x, int y, int v = 1, int l = 0, int r = t) {
    if (l == r) {
        st[v] = {y, x};
    } else {
        int m = (l + r) / 2;
        if (x <= m) {
            upd(x, y, 2 * v, l, m);
        } else {
            upd(x, y, 2 * v + 1, m + 1, r);
        }
        st[v] = max(st[2 * v], st[2 * v + 1]);
    }
}

pair<int, int> qry_max(int x, int y, int v = 1, int l = 0, int r = t) {
    if (y < l || x > r) {
        return {-INF, -1};
    } else if (x <= l && r <= y) {
        return st[v];
    } else {
        int m = (l + r) / 2;
        return max(qry_max(x, y, 2 * v, l, m), qry_max(x, y, 2 * v + 1, m + 1, r));
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int i = 0; i < MAXN; i++) {
        dsu[i] = i;
        sz[i] = 1;
    }

    cin >> n >> m >> q;
    cur = n - 1;

    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }

    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        edge[i] = {x, y};
    }

    set<int> to_rem;
    for (int i = 0; i < q; i++) {
        cin >> qry[i].first >> qry[i].second;
        qry[i].second--;
        if (qry[i].first == 2) to_rem.insert(qry[i].second);
    }

    for (int i = 0; i < m; i++) {
        if (!to_rem.count(i)) {
            mk_edge(edge[i].first, edge[i].second);
        }
    }


    for (int i = q - 1; i >= 0; i--) {
        if (qry[i].first == 1) {
            qry[i].second = get(qry[i].second);
        } else {
            int j = qry[i].second;
            mk_edge(edge[j].first, edge[j].second);
        }
    }

    for (int i = cur; i >= 0; i--) {
        if (!vis[i]) dfs(i);
    }

    build();

    for (int i = 0; i < n; i++) {
        upd(in[i], val[i]);
    }

    for (int i = 0; i < q; i++) {
        if (qry[i].first == 1) {
            int loc = qry[i].second;
            auto res = qry_max(in[loc], out[loc]);
            cout << res.first << '\n';
            upd(res.second, 0);
        }
    }

    return 0;
}
