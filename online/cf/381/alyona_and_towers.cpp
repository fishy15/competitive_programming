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

template<typename T, typename F>
struct segtree {
    int n;
    vector<T> st;
    F op;
    T id;
    segtree(int n, F op, T id) : n(n), st(2 * n, id), op(op), id(id) {}
    segtree(vector<T> &nums, F op, T id) : segtree(sz(nums), op, id) {
        copy(all(nums), begin(st) + n);
        for (int i = n-1; i >= 0; i--) {
            st[i] = op(st[i<<1], st[i<<1|1]);
        }
    }
    void upd(int x, T y) {
        for (x += n, st[x] = y; x >>= 1;) {
            st[x] = op(st[x<<1], st[x<<1|1]);
        }
    }
    T qry(int l, int r) const {
        T ans_l = id, ans_r = id;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans_l = op(ans_l, st[l++]);
            if (r & 1) ans_r = op(st[--r], ans_r);
        }
        return op(ans_l, ans_r);
    }
};

enum cmp {
    LT,
    EQ,
    GT,
};

ostream &operator<<(ostream &os, cmp c) {
    if (c == LT) os << "LT";
    else if (c == EQ) os << "EQ";
    else os << "GT";
    return os;
}

cmp compare(ll x, ll y) {
    if (x < y) return LT;
    else if (x == y) return EQ;
    else return GT;
}

struct node {
    int ans;
    int pre_ltgt;
    int pre_gt;
    int suf_ltgt;
    int suf_lt;
    int cnt_lt;
    int cnt_gt;
    int tot;
    
    node(cmp c) {
        if (c == LT) {
            ans = pre_ltgt = suf_ltgt = suf_lt = 1;
            pre_gt = 0;
            cnt_lt = tot = 1;
            cnt_gt = 0;
        } else if (c == EQ) {
            ans = 1;
            pre_ltgt = pre_gt = suf_ltgt = suf_lt = 0;
            cnt_lt = cnt_gt = 0;
            tot = 1;
        } else {
            ans = pre_ltgt = pre_gt = suf_ltgt = 1;
            suf_lt = 0;
            cnt_gt = tot = 1;
            cnt_lt = 0;
        }
    }

    node(int a, int b, int c, int d, int e, int f, int g, int h) : ans(a), pre_ltgt(b), pre_gt(c), suf_ltgt(d), suf_lt(e), cnt_lt(f), cnt_gt(g), tot(h) {}
    node() : node(0, 0, 0, 0, 0, 0, 0, 0) {}

};

ostream &operator<<(ostream &os, const node &n) {
    os << "(" << n.ans << ' ' << n.pre_ltgt << ' ' << n.pre_gt << ' ' << n.suf_ltgt << ' ' << n.suf_lt << ' ' << n.cnt_lt << ' ' << n.cnt_gt << ' ' << n.tot << ") ";
    return os;
}

node comb(const node &left, const node &right) {
    int a = max({left.ans, right.ans, left.suf_ltgt + right.pre_gt, left.suf_lt + right.pre_ltgt});
    
    int b = left.pre_ltgt;
    if (left.cnt_lt == left.tot) {
        b = max(b, left.pre_ltgt + right.pre_ltgt);
    } else if (left.pre_ltgt == left.tot) {
        b = max(b, left.pre_ltgt + right.pre_gt);
    }

    int c = left.pre_gt;
    if (left.cnt_gt == left.tot) {
        c += right.pre_gt;
    }

    int d = right.suf_ltgt;
    if (right.cnt_gt == right.tot) {
        d = max(d, left.suf_ltgt + right.suf_ltgt);
    } else if (right.suf_ltgt == right.tot) {
        d = max(d, left.suf_lt + right.suf_ltgt);
    }

    int e = right.suf_lt;
    if (right.cnt_lt == right.tot) {
        e += left.suf_lt;
    }

    int f = left.cnt_lt + right.cnt_lt;
    int g = left.cnt_gt + right.cnt_gt;
    int h = left.tot + right.tot;

    auto res = node{a, b, c, d, e, f, g, h};
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<ll> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    vector<ll> diff(n + 1);
    rep(i, 0, n) {
        if (i == 0) {
            diff[i] = nums[i];
        } else {
            diff[i] = nums[i] - nums[i - 1];
        }
    }

    segtree vals_st(diff, plus{}, 0LL);
    auto val_at = [&](int i) {
        return vals_st.qry(0, i + 1);
    };

    vector<node> compares;
    compares.reserve(n - 1);
    rep(i, 0, n-1) {
        compares.push_back(compare(nums[i], nums[i+1]));
    }

    segtree compare_st(compares, &comb, node{});

    int q;
    cin >> q;

    while (q--) {
        int l, r, v;
        cin >> l >> r >> v;
        l--;

        diff[l] += v;
        diff[r] -= v;
        vals_st.upd(l, diff[l]);
        vals_st.upd(r, diff[r]);

        if (l > 0) {
            compares[l - 1] = compare(val_at(l - 1), val_at(l));
            compare_st.upd(l - 1, compares[l - 1]);
        }

        if (r < n) {
            compares[r - 1] = compare(val_at(r - 1), val_at(r));
            compare_st.upd(r - 1, compares[r - 1]);
        }

        auto res = compare_st.qry(0, n - 1).ans;
        cout << res + 1 << '\n';
    }

    return 0;
}
