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

constexpr int MAXA = 500'000;

struct segtree {
    int n;
    vector<int> st;
    segtree(int n) : n(n), st(4 * n) {}
    segtree(int n, vector<int> &nums) : segtree(n) { build(1, 0, n, nums); }
    void build(int v, int l, int r, vector<int> &nums) {
        if (l + 1 == r) {
            st[v] = nums[l];
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, nums);
            build(2 * v + 1, m, r, nums);
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }
    void upd(int x, int y) { upd(1, 0, n, x, y); }
    void upd(int v, int l, int r, int x, int y) {
        if (l + 1 == r) {
            st[v] = y;
        } else {
            int m = (l + r) / 2;
            if (x < m) {
                upd(2 * v, l, m, x, y);
            } else {
                upd(2 * v + 1, m, r, x, y);
            }
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }
    int qry(int x, int y) const { return qry(1, 0, n, x, y); }
    int qry(int v, int l, int r, int x, int y) const {
        if (r <= x || y <= l) return 0;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return max(qry(2 * v, l, m, x, y), qry(2 * v + 1, m, r, x, y));
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, d;
    cin >> n >> d;

    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }

    segtree st(MAXA + 1);
    for (auto x : a) {
        int l = max(0, x - d);
        int h = min(MAXA, x + d);
        st.upd(x, st.qry(l, h + 1) + 1);
    }

    cout << st.qry(0, MAXA + 1) << '\n';

    return 0;
}
