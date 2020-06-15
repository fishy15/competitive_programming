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
int nums[MAXN];
array<int, 2> st[4 * MAXN];

inline array<int, 2> mm(const array<int, 2> &a, const array<int, 2> &b) {
    if (a[0] == b[0]) return min(a, b);
    return max(a, b);
}

array<int, 2> build(int v, int l, int r) {
    if (l == r) {
        return (st[v] = {nums[l], l});
    } else {
        int m = (l + r) / 2;
        return st[v] = mm(build(2 * v, l, m), build(2 * v + 1, m + 1, r));
    }
}

void upd(int v, int l, int r, int x, int y) {
    if (l == r) {
        st[v] = {y, x};
        nums[x] = y;
    } else {
        int m = (l + r) / 2;
        if (x <= m) {
            upd(2 * v, l, m, x, y);
        } else {
            upd(2 * v + 1, m + 1, r, x, y);
        }
        st[v] = mm(st[2 * v], st[2 * v + 1]);
    }
}

array<int, 2> qry(int v, int l, int r, int x, int y) {
    if (r < x || l > y) return {0, 0};
    if (x <= l && r <= y) return st[v];
    int m = (l + r) / 2;
    return mm(qry(2 * v, l, m, x, y), qry(2 * v + 1, m + 1, r, x, y));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
    }

    build(1, 1, n);

    while (q--) {
        int x; cin >> x;
        int l = 1;
        int r = n;
        int ans = -1;

        while (l <= r) {
            int m = (l + r) / 2;
            auto p = qry(1, 1, n, 1, m);
            if (p[0] >= x) {
                ans = p[1];
                r = m - 1;
            } else {
                l = m + 1;
            }
        }

        if (ans == -1) {
            cout << "0 ";
        } else {
            cout << ans << ' ';
            upd(1, 1, n, ans, nums[ans] - x);
        }
    }
    cout << '\n';

    return 0;
}
