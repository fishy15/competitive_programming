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
#include <cassert>
#include <climits>

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

struct Line {
    mutable ll k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    static const ll inf = LLONG_MAX;
    ll div(ll a, ll b) {
        return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};

bool earlier(const pair<ll, ll> &a_diff, const pair<ll, ll> &b_diff) {
    // intersection point is -second/first
    return -a_diff.second * b_diff.first < -b_diff.second * a_diff.first;
}

LineContainer conv(const LineContainer &a, const LineContainer &b) {
    LineContainer res;
    auto it_a = begin(a);
    auto it_b = begin(b);
    while (it_a != end(a) && it_b != end(b)) {
        res.add(it_a->k + it_b->k, it_a->m + it_b->m);
        if (next(it_a) == end(a)) {
            it_b++;
        } else if (next(it_b) == end(b)) {
            it_a++;
        } else {
            auto a_diff = pair{
                next(it_a)->k - it_a->k,
                next(it_a)->m - it_a->m,
            };
            auto b_diff = pair{
                next(it_b)->k - it_b->k,
                next(it_b)->m - it_b->m,
            };
            if (earlier(a_diff, b_diff)) {
                it_a++;
            } else {
                it_b++;
            }
        }
    }

    return res;
}

struct Result {
    ll sum, ans, left, right;
    static Result comb(const Result &a, const Result &b) {
        return Result {
            a.sum + b.sum,
            max({a.ans, b.ans, a.right + b.left}),
            max(a.left, a.sum + b.left),
            max(a.right + b.sum, b.right),
        };
    }
};

struct Node {
    Line sum;
    LineContainer ans, left, right;

    Node() {}
    Node(ll x) {
        sum = {1, x};
        LineContainer c;
        c.add(0, 0);
        c.add(1, x);
        ans = left = right = c;
    }

    Node(Line s, LineContainer a, LineContainer l, LineContainer r) : sum(s), ans(a), left(l), right(r) {}

    static Node comb(const Node &a, const Node &b) {
        Line sum = {a.sum.k + b.sum.k, a.sum.m + b.sum.m};

        auto ans = conv(a.right, b.left);
        for (auto l : a.ans) {
            ans.add(l.k, l.m);
        }
        for (auto l : b.ans) {
            ans.add(l.k, l.m);
        }

        auto left = a.left;
        for (auto l : b.left) {
            left.add(a.sum.k + l.k, a.sum.m + l.m);
        }

        auto right = b.right;
        for (auto l : a.right) {
            right.add(l.k + b.sum.k, l.m + b.sum.m);
        }

        return Node{sum, ans, left, right};
    }

    Result get_res(ll x) {
        auto res = Result {
            sum.k * x + sum.m,
            ans.query(x),
            left.query(x),
            right.query(x),
        };
        return res;
    }
};

struct segtree {
    int n;
    vector<Node> st;
    segtree(vector<ll> &nums) : n(sz(nums)), st(2 * sz(nums)) {
        rep(i, 0, n) {
            st[i+n] = Node(nums[i]);
        }
        for (int i = n-1; i >= 0; i--) {
            st[i] = Node::comb(st[i<<1], st[i<<1|1]);
        }
    }
    ll qry(int l, int r, ll x) {
        Result ans_l{0, 0, 0, 0};
        Result ans_r{0, 0, 0, 0};
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans_l = Result::comb(ans_l, st[l++].get_res(x));
            if (r & 1) ans_r = Result::comb(st[--r].get_res(x), ans_r);
        }
        return Result::comb(ans_l, ans_r).ans;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<ll> a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }

    auto st = segtree(a);

    ll diff = 0;
    while (q--) {
        string typ;
        cin >> typ;
        if (typ == "ASSESS") {
            int l, r;
            cin >> l >> r;
            l--;
            cout << st.qry(l, r, diff) << '\n';
        } else {
            int x;
            cin >> x;
            diff += x;
        }
    }

    return 0;
}
