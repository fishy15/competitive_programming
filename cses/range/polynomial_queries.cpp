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

ll n, q;
ll nums[MAXN];
ll st[4 * MAXN];
ll lazy[4 * MAXN][2];

inline ll sum(ll n) {
    return n * (n + 1) / 2;
}

void push(ll v, ll l, ll r) {
    if (l != r) {
        ll m = (l + r) / 2;
        lazy[2 * v][0] += lazy[v][0];
        lazy[2 * v + 1][0] += lazy[v][0] + lazy[v][1] * (m - l + 1);
        lazy[2 * v][1] += lazy[v][1];
        lazy[2 * v + 1][1] += lazy[v][1];
        st[2 * v] += sum(m - l + 1) * lazy[v][1] + lazy[v][0] * (m - l + 1);
        st[2 * v + 1] += sum(r - m) * lazy[v][1] + (lazy[v][0] + lazy[v][1] * (m - l + 1)) * (r - m);
    }
    lazy[v][0] = 0;
    lazy[v][1] = 0;
}

ll build(ll v, ll l, ll r) {
    if (l == r) {
        return st[v] = nums[l];
    } else {
        ll m = (l + r) / 2;
        return st[v] = build(2 * v, l, m) + build(2 * v + 1, m + 1, r);
    }
}

void upd(ll v, ll l, ll r, ll x, ll y) {
    if (r < x || l > y) return;
    if (x <= l && r <= y) {
        st[v] += sum(r - l + 1) + (l - x) * (r - l + 1);
        lazy[v][0] += (l - x);
        lazy[v][1]++;
    } else {
        ll m = (l + r) / 2;
        push(v, l, r);
        upd(2 * v, l, m, x, y);
        upd(2 * v + 1, m + 1, r, x, y);
        st[v] = st[2 * v] + st[2 * v + 1];
    }
}

ll qry(ll v, ll l, ll r, ll x, ll y) {
    if (r < x || l > y) return 0;
    if (x <= l && r <= y) return st[v];
    ll m = (l + r) / 2;
    push(v, l, r);
    return qry(2 * v, l, m, x, y) + qry(2 * v + 1, m + 1, r, x, y);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    for (ll i = 1; i <= n; i++) {
        cin >> nums[i];
    }

    build(1, 1, n);

    while (q--) {
        ll t, a, b; cin >> t >> a >> b;
        if (t == 1) {
            upd(1, 1, n, a, b);
        } else {
            cout << qry(1, 1, n, a, b) << '\n';
        }
    }

    return 0;
}
