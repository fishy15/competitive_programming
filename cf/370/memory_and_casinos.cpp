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
#define MAXN 1000000

using namespace std;

int n, q;

struct Prob {
    bool id;
    ld l, r;
    Prob() : id(true) {}
    Prob(int n, int d) : Prob((ld) n / d, (ld) n / d) {}
    Prob(ld l, ld r) : id(false), l(l), r(r) {}

    ld get() { return l; }

    Prob operator+(const Prob &p2) const {
        if (id) return p2;
        if (p2.id) return *this;
        ld new_l = l * p2.l / (1 - r * (1 - p2.l));    
        ld new_r = p2.r + (1 - p2.r) * (r * p2.l / (1 - r * (1 - p2.l)));
        return Prob(new_l, new_r);
    }
};

template<typename Node>
struct segtree {
    int n;
    vector<Node> st;

    segtree(int n, const vector<Node> &nums) : n(n), st(4 * n) {
        build(1, 0, n, nums);
    }

    void build(int v, int l, int r, const vector<Node> &nums) {
        if (l + 1 == r) {
            st[v] = nums[l];
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, nums);
            build(2 * v + 1, m, r, nums);
            st[v] = st[2 * v] + st[2 * v + 1];
        }
    }

    void upd(int x, Node y) { upd(1, 0, n, x, y); }
    void upd(int v, int l, int r, int x, Node y) {
        if (l + 1 == r) {
            st[v] = y;
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

    decltype(declval<Node>().get()) qry(int x, int y) const { return qry(1, 0, n, x, y).get(); }
    Node qry(int v, int l, int r, int x, int y) const {
        if (r <= x || y <= l) {
            return Node();
        } else if (x <= l && r <= y) {
            return st[v];
        } else {
            int m = (l + r) / 2;
            auto q = qry(2 * v, l, m, x, y) + qry(2 * v + 1, m, r, x, y);
            return q;
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q; cin >> n >> q;
    vector<Prob> nums;
    
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        nums.emplace_back(a, b);
    }

    segtree<Prob> st(n, nums);

    cout << fixed << setprecision(10);

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int i, a, b; cin >> i >> a >> b;
            st.upd(i - 1, Prob(a, b));
        } else {
            int l, r; cin >> l >> r;
            l--;
            cout << st.qry(l, r) << '\n';
        }
    }

    return 0;
}
