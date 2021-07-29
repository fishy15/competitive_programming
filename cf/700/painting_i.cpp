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
int nums[MAXN];

struct lazy_segtree {
    int st[4 * MAXN];
    int lazy[4 * MAXN];
    lazy_segtree() {
        memset(st, 0, sizeof st);
        memset(lazy, 0, sizeof lazy);
    }
    void push(int v, int l, int r) {
        if (l != r) {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
        }
        st[v] += lazy[v];
        lazy[v] = 0;
    }
    void upd(int x, int y, int q, int v = 1, int l = 0, int r = n) {
        push(v, l, r);
        if (r < x || l > y) return;
        if (x <= l && r <= y) {
            lazy[v] += q;
            push(v, l, r);
        } else {
            int m = (l + r) / 2;
            upd(x, y, q, 2 * v, l, m);
            upd(x, y, q, 2 * v + 1, m + 1, r);
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }
    int qry(int x, int y, int v = 1, int l = 0, int r = n) {
        push(v, l, r);
        if (r < x || l > y) return 0;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return max(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m + 1, r));
    }
};

lazy_segtree st[2];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    for (int i = 0; i < n; i++) {
        int c = nums[i];
        vector<array<int, 2>> to_upd;
        for (int j = 0; j < 2; j++) {
            int o = 1 - j;
            int b = max({st[o].qry(0, c - 1) + 1, st[o].qry(c + 1, n) + 1, st[o].qry(c, c)});
            int p = i ? nums[i - 1] : 0;
            to_upd.push_back({p, b}); 
        }
        if (i == 0 || nums[i - 1] != nums[i]) {
            st[0].upd(0, n, 1);
            st[1].upd(0, n, 1);
        }
        for (int j = 0; j < 2; j++) {
            auto [p, b] = to_upd[j];
            int v = st[j].qry(p, p);
            if (b > v) {
                st[j].upd(p, p, b - v);
            }
        }
    }

    cout << st[0].qry(0, n) << '\n';

    return 0;
}
