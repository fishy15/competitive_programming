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
        for (x += n, st[x] = y; x > 1; x >>= 1) {
            st[x>>1] = op(st[x], st[x^1]);
        }
    }
    T qry(int l, int r) const {
        T ans = id;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans = op(ans, st[l++]);
            if (r & 1) ans = op(st[--r], ans);
        }
        return ans;
    }
};

struct basis : public array<array<int, 2>, 20> {
    basis() {
        fill({-1, -1});
    }
};

void add_to_basis(basis &b, int x, int idx) {
    for (int i = 19; i >= 0; i--) {
        if ((x >> i) & 1) {
            if (b[i][0] == -1) {
                b[i][0] = x;
                b[i][1] = idx;
                return;
            } else {
                if (idx > b[i][1]) {
                    swap(x, b[i][0]);
                    swap(idx, b[i][1]);
                }
                x ^= b[i][0];
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> c(n);
    rep(i, 0, n) {
        cin >> c[i];
    }

    int q;
    cin >> q;
    
    // {r, idx}
    vector<vector<array<int, 2>>> queries(n);
    vector<int> ans(q);
    rep(i, 0, q) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        queries[r].push_back({l, i});
    }

    basis b;
    rep(i, 0, n) {
        add_to_basis(b, c[i], i);
        for (auto [l, idx] : queries[i]) {
            int res = 0;
            for (int i = 19; i >= 0; i--) {
                if (b[i][0] != -1 && b[i][1] >= l) {
                    if ((res & (1 << i)) == 0) {
                        res ^= b[i][0];
                    }
                }
            }
            ans[idx] = res;
        }
    }

    for (auto x : ans) {
        cout << x << '\n';
    }

    return 0;
}
