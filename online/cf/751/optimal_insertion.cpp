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

struct lazy_segtree {
    int n;
    mutable vector<int> st;
    mutable vector<int> lazy;
    lazy_segtree(int n) : n(n), st(4 * n), lazy(4 * n) {}
    lazy_segtree(int n, vector<int> &nums) : lazy_segtree(n) { build(1, 0, n - 1, nums); }
    void build(int v, int l, int r, const vector<int> &nums) {
        if (l == r) {
            st[v] = nums[l];
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, nums);
            build(2 * v + 1, m + 1, r, nums);
            st[v] = min(st[2 * v], st[2 * v + 1]);
        }
    }
    void push(int v, int l, int r) const {
        if (l != r) {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
        }
        st[v] += lazy[v];
        lazy[v] = 0;
    }
    void upd(int x, int y, int q) { upd(x, y, q, 1, 0, n - 1); }
    void upd(int x, int y, int q, int v, int l, int r) {
        push(v, l, r);
        if (r < x || l > y) return;
        if (x <= l && r <= y) {
            lazy[v] += q;
            push(v, l, r);
        } else {
            int m = (l + r) / 2;
            upd(x, y, q, 2 * v, l, m);
            upd(x, y, q, 2 * v + 1, m + 1, r);
            st[v] = min(st[2 * v], st[2 * v + 1]);
        }
    }
    int qry(int x, int y) const { return qry(x, y, 1, 0, n - 1); }
    int qry(int x, int y, int v, int l, int r) const {
        push(v, l, r);
        if (r < x || l > y) return INF;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return min(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m + 1, r));
    }
};

template<typename T>
struct BIT {
    int n;
    vector<T> bit;

    BIT(int n) : n(n), bit(n + 1) {}

    void upd(int x, int v) {
        x++;
        while (x <= n) {
            bit[x] += v;
            x += x & -x;
        }
    }

    T qry(int r) {
        T res{};
        while (r > 0) {
            res += bit[r];
            r -= r & -r;
        }
        return res;
    }

    T qry(int l, int r) {
        return qry(r) - qry(l);
    }
};

struct info_t {
    vector<int> a_idx;
    int b_cnt{};
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }

    vector<int> b(m);
    for (auto &x : b) {
        cin >> x;
    }

    vector<int> comb;
    comb.insert(comb.end(), a.begin(), a.end());
    comb.insert(comb.end(), b.begin(), b.end());
    sort(comb.begin(), comb.end());
    comb.erase(unique(comb.begin(), comb.end()), comb.end());

    auto g = [&](int x) { return lower_bound(comb.begin(), comb.end(), x) - comb.begin(); };

    vector<info_t> info(comb.size());
    for (int i = 0; i < n; i++) {
        info[g(a[i])].a_idx.push_back(i);
    }

    for (auto x : b) {
        info[g(x)].b_cnt++;
    }

    vector<int> init_f(n + 1);
    iota(init_f.begin(), init_f.end(), 0);
    lazy_segtree f(n + 1, init_f);
    BIT<int> a_only(n);

    ll ans = 0;
    for (auto &ii : info) {
        for (auto idx : ii.a_idx) {
            f.upd(idx+1, n, -1);
            ans += a_only.qry(idx, n);
        }

        ans += (ll) ii.b_cnt * f.qry(0, n);

        f.upd(0, n, (int) ii.a_idx.size());
        for (auto idx : ii.a_idx) {
            f.upd(idx, n, -1);
            a_only.upd(idx, 1);
        }
    }

    cout << ans << '\n';
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
