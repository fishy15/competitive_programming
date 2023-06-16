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
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct segtree {
    struct node {
        ll v;
        node *l, *r;
        node() : node(-INFLL) {}
        node(ll v) : v(v), l(nullptr), r(nullptr) {}
    };

    node *root;
    deque<node> buffer;

    template<typename... Args>
    node *new_node(Args... args) {
        buffer.emplace_back(args...);
        return &buffer.back();
    }

    ll get(node *v) {
        if (v == nullptr) return -INFLL;
        return v->v;
    }

    segtree() : root(new_node()) {}

    void upd(ll x, ll y) { upd(root, -INF, INF, x, y); }
    void upd(node *v, ll l, ll r, ll x, ll y) {
        if (l + 1 == r) {
            v->v  = y;
        } else {
            ll m = (l + r) / 2;
            if (x < m) {
                if (v->l == nullptr) v->l = new_node();
                upd(v->l, l, m, x, y);
            } else {
                if (v->r == nullptr) v->r = new_node();
                upd(v->r, m, r, x, y);
            }

            v->v = max(get(v->l), get(v->r));
        }
    }

    ll qry(ll x, ll y) { return qry(root, -INF, INF, x, y); }
    ll qry(node *v, ll l, ll r, ll x, ll y) {
        if (v == nullptr || x > r || y < l) {
            return -INFLL;
        } else if (x <= l && y <= r) {
            return v->v;
        } else {
            ll m = (l + r) / 2;
            return max(qry(v->l, l, m, x, y), qry(v->r, m, r, x, y));
        }
    }
};

void solve() {
    int n, m; cin >> n >> m;
    vector<array<int, 2>> rain(n);
    map<ll, ll> psum;
    map<ll, ll> val;

    /* segtree same, inc, dec; */

    for (int i = 0; i < n; i++) {
        cin >> rain[i][0] >> rain[i][1];

        ll l = rain[i][0] - rain[i][1];
        ll r = rain[i][0] + rain[i][1];

        psum[l]++;
        psum[rain[i][0]] -= 2;
        psum[r]++;
    }

    ll cur = 0;
    ll slope = 0;
    ll prev = psum.begin()->first;

    for (auto [x, v] : psum) {
        cur += (x - prev) * slope;
        val[x - 1] = cur - slope;
        val[x] = cur;

        slope += v;
        val[x + 1] = cur + slope;
        prev = x;

        cout << "slope: " << x << ' ' << slope << '\n';
    }

    for (auto [x, v] : val) {
        cout << x << ' ' << v << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
