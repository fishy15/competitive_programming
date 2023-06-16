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

struct segtree {
    int n;
    vector<pair<ll, ll>> st; // {prefix, sum}

    segtree(int n, vector<int> &arr) : n(n) {
        st.resize(4 * n);
        build(1, 0, n - 1, arr);
    }

    pair<ll, ll> comb(const pair<ll, ll> &p1, const pair<ll, ll> &p2) const {
        pair<ll, ll> res;
        res.first = max(p1.first, p1.second + p2.first);
        res.second = p1.second + p2.second;
        return res;
    }

    void build(int v, int l, int r, vector<int> &arr) {
        if (l == r) {
            st[v] = {max(0, arr[l]), arr[l]};
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, arr);
            build(2 * v + 1, m + 1, r, arr);
            st[v] = comb(st[2 * v], st[2 * v + 1]);
        }
    }

    void upd(int x, int y) { upd(1, x, y, 0, n - 1); }
    void upd(int v, int x, int y, int l, int r) {
        if (l == r) {
            st[v] = {max(0, y), y};
        } else {
            int m = (l + r) / 2;
            if (x <= m) {
                upd(2 * v, x, y, l, m);
            } else {
                upd(2 * v + 1, x, y, m + 1, r);
            }
            st[v] = comb(st[2 * v], st[2 * v + 1]);
        }
    }

    ll qry(int x, int y) const { return qry(1, x, y, 0, n - 1).first; } 
    pair<ll, ll> qry(int v, int x, int y, int l, int r) const {
        if (y < l || x > r) {
            return {0, 0};
        } else if (x <= l && r <= y) {
            return st[v];
        } else {
            int m = (l + r) / 2;
            return comb(qry(2 * v, x, y, l, m), qry(2 * v + 1, x, y, m + 1, r));
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;
    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    segtree st(n, nums);

    while (q--) {
        int t, a, b; cin >> t >> a >> b;
        if (t == 1) {
            a--;
            st.upd(a, b);
        } else {
            a--; b--;
            cout << st.qry(a, b) << '\n';
        }
    }

    return 0;
}
