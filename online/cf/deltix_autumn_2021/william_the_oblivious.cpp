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

struct node {
    int a, b, c, ab, bc, abc;
    node(char q) {
        if (q == 'a') {
            tie(a, b, c, ab, bc, abc) = tuple{1, 0, 0, 0, 0, 0};
        } else if (q == 'b') {
            tie(a, b, c, ab, bc, abc) = tuple{0, 1, 0, 0, 0, 0};
        } else {
            tie(a, b, c, ab, bc, abc) = tuple{0, 0, 1, 0, 0, 0};
        }
    }
    friend ostream &operator<<(ostream &os, node n) {
        os << "[ " << n.a << ' ' << n.b << ' ' << n.c << ' ' << n.ab << ' ' << n.bc << ' ' << n.abc << " ]";
        return os;
    }
};

node comb(const node &x, const node &y) {
    node res{'a'};
    tie(res.a, res.b, res.c, res.ab, res.bc, res.abc) = 
        tuple {
            x.a + y.a,
            x.b + y.b,
            x.c + y.c,
            min(x.a + y.ab, x.ab + y.b),
            min(x.b + y.bc, x.bc + y.c),
            min({x.abc + y.c, x.ab + y.bc, x.a + y.abc}),
        };
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;

    vector<node> sv;
    rep(i, 0, n) {
        sv.push_back(s[i]);
    }

    node id{'a'};
    tie(id.a, id.b, id.c, id.ab, id.bc, id.abc) = tuple{0, 0, 0, 0, 0, 0};

    segtree st(sv, &comb, id);

    while (q--) {
        int idx;
        char c;
        cin >> idx >> c;
        idx--;
        st.upd(idx, node{c});
        cout << st.qry(0, n).abc << '\n';
    }

    return 0;
}
