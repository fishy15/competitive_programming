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
    vector<int> st;
    segtree(int n) : n(n), st(4 * n) {}

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

    int qry(int x) { return qry(1, 0, n, 0, x); }
    int qry(int v, int l, int r, int x, int y) {
        if (y <= l || x >= r) {
            return 0;
        } else if (x <= l && r <= y) {
            return st[v];
        } else {
            int m = (l + r) / 2;
            return max(qry(2 * v, l, m, x, y), qry(2 * v + 1, m, r, x, y));
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    vector<array<int, 2>> nums;

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        nums.push_back({a, b});
    }

    sort(nums.begin(), nums.end(), [&](auto a, auto b) {
        if (a[0] == b[0]) {
            return a[1] > b[1];
        }
        return a[0] < b[0];
    });

    segtree st(n);
    for (auto [a, b] : nums) {
        int before = st.qry(b);
        st.upd(b, before + 1);
    }

    cout << st.qry(n) << '\n';

    return 0;
}
