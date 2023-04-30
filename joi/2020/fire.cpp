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

struct st {
    ll seg[8 * MAXN];
    ll lazy[8 * MAXN];
    st() { 
        memset(seg, 0, sizeof seg);
        memset(lazy, 0, sizeof lazy);
    }
    void push(int v, int l, int r) {
        if (l != r) {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
        }
        seg[v] += (r - l + 1) * lazy[v];
        lazy[v] = 0;
    }
    void upd(int x, int y, ll val, int v = 1, int l = -MAXN+1, int r = MAXN-1) {
        if (y < l || x > r) return;
        if (x <= l && r <= y) {
            lazy[v] += val;
            push(v, l, r);
        } else {
            int m = l + (r - l) / 2;
            push(v, l, r);
            upd(x, y, val, 2 * v, l, m);
            upd(x, y, val, 2 * v + 1, m + 1, r);
        }
    }
    ll qry(int x, int y, int v = 1, int l = -MAXN+1, int r = MAXN-1) {
        if (y < l || x > r) return 0;
        push(v, l, r);
        if (x <= l && r <= y) return seg[v];
        else {
            int m = l + (r - l) / 2;
            return qry(x, y, v, l, m) + qry(x, y, v, m + 1, r);
        }
    }
};

int n, q;
ll nums[MAXN];
ll ans[MAXN];
vector<array<ll, 3>> to_del[MAXN];
vector<array<int, 3>> query[MAXN];

st l, r;

void add_triangle(int x, int y, ll v) {
    l.upd(x, MAXN - 1, v);
    r.upd(y + 1, MAXN - 1, -v);
    int t = y - x + 1;
    if (t < MAXN) {
        to_del[t].push_back({x, y, v});
    }
}

void remove_triangle(int x, int y, ll v) {
    l.upd(x, MAXN - 1, -v);
    r.upd(y + 1, MAXN - 1, v);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = 0; i < n; i++) {
        int t, a, b; cin >> t >> a >> b;
        t--; a--; b--;
        query[t].push_back({i, a, b});
    }

    for (int i = 0; i < n; i++) {
        for (auto &del : to_del[i]) {
            remove_triangle(del[0], del[1], del[2]);
        }

        for (auto &q : query[i]) {
            ans[q[0]] = l.qry(q[1] - i, q[2] - i);
            ans[q[0]] -= r.qry(q[1], q[2]);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
