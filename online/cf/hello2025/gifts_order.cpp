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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

struct node {
    ll min_minus, min_plus, max_minus, max_plus;
    ll ans;
 
    node(ll a, ll b, ll c, ll d, ll e) : min_minus{a}, min_plus{b}, max_minus{c}, max_plus{d}, ans{e} {}
    node() : node(INFLL, INFLL, -INFLL, -INFLL, 0) {}
    node(int v, int idx) : node(-idx - v, -idx + v, -idx - v, -idx + v, 0) {}

    node operator+(const node &o) const {
        auto new_ans = max({
            ans,
            o.ans,
            o.max_plus - min_plus,
            o.max_minus - min_minus,
        });
        return node(
            min(min_minus, o.min_minus),
            min(min_plus, o.min_plus),
            max(max_minus, o.max_minus),
            max(max_plus, o.max_plus),
            new_ans
        );
    }
};

struct segtree {
    int n;
    vector<node> st;
    segtree(int n) : n(n), st(4 * n) {}
    segtree(int n, vector<int> &nums) : segtree(n) { build(1, 0, n, nums); }
    void build(int v, int l, int r, vector<int> &nums) {
        if (l + 1 == r) {
            st[v] = node(nums[l], l);
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, nums);
            build(2 * v + 1, m, r, nums);
            st[v] = st[2 * v] + st[2 * v + 1];
        }
    }
    void upd(int x, int y) { upd(1, 0, n, x, y); }
    void upd(int v, int l, int r, int x, int y) {
        if (l + 1 == r) {
            st[v] = node(y, l);
        } else {
            int m = (l + r) / 2;
            if (x < m) {
                upd(2 * v, l, m, x, y);
            } else {
                upd(2 * v + 1, m, r, x, y);
            }
            st[v] = st[2 * v] + st[2 * v + 1];
        }
    }
    ll qry(int x, int y) const { return qry(1, 0, n, x, y + 1).ans; }
    node qry(int v, int l, int r, int x, int y) const {
        if (r <= x || y <= l) return node{};
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return qry(2 * v, l, m, x, y) + qry(2 * v + 1, m, r, x, y);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    segtree st(n, nums);
    cout << st.qry(0, n) << '\n';
    while (q--) {
        int p, x;
        cin >> p >> x;
        p--;
        st.upd(p, x);
        cout << st.qry(0, n) << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
