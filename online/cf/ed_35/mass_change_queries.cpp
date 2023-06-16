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
#define MAXN 200010

using namespace std;

struct f {
    array<char, 100> func;

    f() {
        reset();
    }

    f(int old, int now) : f() {
        func[old] = now;
    }

    void reset() {
        iota(func.begin(), func.end(), 0);
    }

    int operator()(int x) const {
        return func[x];
    }

    f compose(const f &f2) {
        f res;
        for (int i = 0; i < 100; i++) {
            res.func[i] = f2(func[i]);
        }
        return res;
    }
};

struct segtree {
    int n;
    vector<f> st;

    segtree(int n) : n(n) {
        st.resize(4 * n);
    }

    void upd(int x, const f &q) { upd(1, 0, n, x, q); }
    void upd(int v, int l, int r, int x, const f &q) {
        if (l + 1 == r) {
            st[v] = q;
        } else {
            int m = (l + r) / 2;
            if (x < m) {
                upd(2 * v, l, m, x, q);
            } else {
                upd(2 * v + 1, m, r, x, q);
            }
            st[v] = st[2 * v].compose(st[2 * v + 1]);
        }
    }

    int qry(int x) { return st[1](x); }
};

int n, q;
int nums[MAXN];
vector<array<int, 3>> change[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        nums[i]--;
    }

    cin >> q;
    segtree st(q);

    for (int i = 0; i < q; i++) {
        int l, r, x, y; cin >> l >> r >> x >> y;
        l--; x--; y--;
        change[l].push_back({i, x, y});
        change[r].push_back({i, x, x});
    }

    for (int i = 0; i < n; i++) {
        for (auto [i, x, y] : change[i]) {
            st.upd(i, f(x, y));
        }

        cout << st.qry(nums[i]) + 1 << ' ';
    }
    cout << '\n';

    return 0;
}
