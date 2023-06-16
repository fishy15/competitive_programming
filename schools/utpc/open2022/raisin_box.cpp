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
#define MAXN 100010

using namespace std;

int n;
int nums[MAXN];
ll ans[MAXN];

struct segtree {
    int n;
    vector<pair<int, int>> st;

    segtree(int n, int *nums) : n(n), st(4 * n) {
        build(1, 0, n, nums);
    }

    void build(int v, int l, int r, int *nums) {
        if (l + 1 == r) {
            st[v] = {nums[l], l};
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, nums);
            build(2 * v + 1, m, r, nums);
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }

    int qry(int l, int r) const { return qry(1, 0, n, l, r).second; }
    pair<int, int> qry(int v, int x, int y, int l, int r) const {
        if (r <= x || y <= l) {
            return {-1, -1};
        } else if (l <= x && y <= r) {
            return st[v];
        } else {
            int m = (x + y) / 2;
            return max(qry(2 * v, x, m, l, r), qry(2 * v + 1, m, y, l, r));
        }
    }
};

void solve(int l, int r, segtree &st) {
    if (l < r) {
        int x = st.qry(l, r);
        ans[x] = (ll) (x - l + 1) * (r - x);
        solve(l, x, st);
        solve(x + 1, r, st);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    segtree st(n, nums);
    solve(0, n, st);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';

    return 0;
}
