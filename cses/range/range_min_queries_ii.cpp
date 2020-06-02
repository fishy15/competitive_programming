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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200010

using namespace std;

int n, q;
ll nums[MAXN];
ll segtree[4 * MAXN];

void build(int n, int l, int r) {
    if (l == r) segtree[n] = nums[l];
    else {
        int m = (l + r) / 2;
        build(2 * n, l, m);
        build(2 * n + 1, m + 1, r);
        segtree[n] = min(segtree[2 * n], segtree[2 * n + 1]);
    }
}

void update(int n, int l, int r, int x, int v) {
    if (l == r) {
        segtree[n] = v;
        nums[l] = v;
    } else {
        int m = (l + r) / 2;
        if (x <= m) {
            update(2 * n, l, m, x, v);
        } else {
            update(2 * n + 1, m + 1, r, x, v);
        }
        segtree[n] = min(segtree[2 * n], segtree[2 * n + 1]);
    }
}

ll query(int n, int l, int r, int x, int y) {
    if (x <= l && r <= y) return segtree[n];
    if (r < x || l > y) return INFLL;
    int m = (l + r) / 2;
    return min(query(2 * n, l, m, x, y), query(2 * n + 1, m + 1, r, x, y));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
    }

    build(1, 1, n);

    for (int i = 0; i < q; i++) {
        int t, a, b; cin >> t >> a >> b;
        if (t == 1) {
            update(1, 1, n, a, b);
        } else {
            cout << query(1, 1, n, a, b) << '\n';
        }
    }

    return 0;
}
