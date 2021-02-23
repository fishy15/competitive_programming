/*
 * Note that if two segments overlap and one is not contained in the other, then they cannot be on the
 * same side. If we draw an edge between them, then the resulting graph must be bipartite. We can't 
 * construct the entire graph in time, but we can do a DFS to determine a possible way of arranging the 
 * segments. We then have to check if both stacks created by this work. If this arrangement works, then
 * the answer is 2^(# of components), otherwise it is 0.
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
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define NINF 0xc0c0c0c0
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000010

using namespace std;

int n;
pair<int, int> pts[MAXN];
int l_inv[MAXN];
int r_inv[MAXN];
int vis[MAXN]; // 0 unvis, 1 in first stack, 2 in second stack

struct segtree {
    int st[8 * MAXN];
    segtree() { memset(st, NINF, sizeof st); }
    void upd(int x, int y, int v = 1, int l = 0, int r = 2 * n) {
        if (l == r) {
            st[v] = y;
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
    int qry(int x, int y, int v = 1, int l = 0, int r = 2 * n) {
        if (r < x || l > y) {
            return NINF;
        } else if (x <= l && r <= y) {
            return st[v];
        } else {
            int m = (l + r) / 2;
            return max(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m + 1, r));
        }
    }
};

ll modpow(ll x, ll e) {
    ll res = 1;
    while (e) {
        if (e & 1) res = res * x % MOD;
        x = x * x % MOD;
        e >>= 1;
    }
    return res;
}

// left_end is min left end whose right is within a given range
// right_end is max right end whose left is within a given range
segtree left_end, right_end;

void dfs(int x, int c) {
    left_end.upd(pts[x].second, NINF);
    right_end.upd(pts[x].first, NINF);
    vis[x] = c;

    int q;
    while ((q = -left_end.qry(pts[x].first, pts[x].second)) < pts[x].first) {
        int left_loc = l_inv[q];
        dfs(left_loc, 3 - c);
    }

    while ((q = right_end.qry(pts[x].first, pts[x].second)) > pts[x].second) {
        int right_loc = r_inv[q];
        dfs(right_loc, 3 - c);
    }
}

int sz_a, sz_b;
int a[2 * MAXN];
int b[2 * MAXN];
int cur_stack[MAXN];
int r = 0;
bool check(int *tot, int sz) {
    sort(tot, tot + sz);

    for (int i = 0; i < sz; i++) {
        int x = tot[i];
        if (l_inv[x] != -1) {
            cur_stack[r++] = l_inv[x];
        } else {
            if (r == 0 || cur_stack[r - 1] != r_inv[x]) {
                return false;
            }
            r--;
        }
    }
    
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    memset(l_inv, -1, sizeof l_inv);
    memset(r_inv, -1, sizeof r_inv);
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        pts[i] = {a, b};
        l_inv[a] = i;
        r_inv[b] = i;
    }

    for (int i = 0; i < n; i++) {
        left_end.upd(pts[i].second, -pts[i].first);
        right_end.upd(pts[i].first, pts[i].second);
    }

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            cnt++;
            dfs(i, 1);
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (vis[i] == 1) {
            a[sz_a++] = pts[i].first;
            a[sz_a++] = pts[i].second;
        } else {
            b[sz_b++] = pts[i].first;
            b[sz_b++] = pts[i].second;
        }
    }

    if (check(a, sz_a) && check(b, sz_b)) {
        cout << modpow(2, cnt) << '\n';
    } else {
        cout << "0\n";
    }

    return 0;
}
