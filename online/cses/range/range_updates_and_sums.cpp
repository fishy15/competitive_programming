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
#define MAXN 200010

using namespace std;

int n, q;
int nums[MAXN];
ll st[4 * MAXN];
ll lazy_sum[4 * MAXN];
ll lazy_set[4 * MAXN];
bool to_set[4 * MAXN];

void push(int v, int l, int r) {
    if (l != r) {
        int m = (l + r) / 2;
        if (to_set[v]) {
            st[2 * v] = (m - l + 1) * lazy_set[v];
            st[2 * v + 1] = (r - m) * lazy_set[v];
            to_set[2 * v] = true;
            to_set[2 * v + 1] = true;
            lazy_set[2 * v] = lazy_set[v];
            lazy_set[2 * v + 1] = lazy_set[v];
            lazy_sum[2 * v] = 0;
            lazy_sum[2 * v + 1] = 0;
        }
        st[2 * v] += (m - l + 1) * lazy_sum[v];
        st[2 * v + 1] += (r - m) * lazy_sum[v];
        lazy_sum[2 * v] += lazy_sum[v];
        lazy_sum[2 * v + 1] += lazy_sum[v];
    }

    to_set[v] = false;
    lazy_sum[v] = 0;
    lazy_set[v] = 0;
}

ll build(int v, int l, int r) {
    if (l == r) {
        return st[v] = nums[l];
    }
    int m = (l + r) / 2;
    return st[v] = build(2 * v, l, m) + build(2 * v + 1, m + 1, r);
}

void upd_sum(int v, int l, int r, int x, int y, ll n) {
    if (y < l || x > r) return;
    push(v, l, r);
    if (x <= l && r <= y) {
        lazy_sum[v] += n;
        st[v] += (r - l + 1) * n;
    } else {
        int m = (l + r) / 2;
        upd_sum(2 * v, l, m, x, y, n);
        upd_sum(2 * v + 1, m + 1, r, x, y, n);
        st[v] = st[2 * v] + st[2 * v + 1];
    }
}

void upd_set(int v, int l, int r, int x, int y, ll n) {
    if (y < l || x > r) return;
    push(v, l, r);
    if (x <= l && r <= y) {
        to_set[v] = true;
        lazy_set[v] = n;
        st[v] = (r - l + 1) * n;
    } else {
        int m = (l + r) / 2;
        upd_set(2 * v, l, m, x, y, n);
        upd_set(2 * v + 1, m + 1, r, x, y, n);
        st[v] = st[2 * v] + st[2 * v + 1];
    }
}

ll qry(int v, int l, int r, int x, int y) {
    if (y < l || x > r) return 0;
    if (x <= l && r <= y) {
        return st[v];
    } else {
        int m = (l + r) / 2;
        push(v, l, r);
        return qry(2 * v, l, m, x, y) + qry(2 * v + 1, m + 1, r, x, y);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
    }
    
    build(1, 1, n);

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int a, b, x; cin >> a >> b >> x;
            upd_sum(1, 1, n, a, b, x);
        } else if (t == 2) {
            int a, b, x; cin >> a >> b >> x;
            upd_set(1, 1, n, a, b, x);
        } else {
            int a, b; cin >> a >> b;
            cout << qry(1, 1, n, a, b) << '\n';
        }
    }

    return 0;
}
