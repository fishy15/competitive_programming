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
#define MOD 10007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100001

using namespace std;

int n, c, q;
short a[MAXN];
short b[MAXN];

struct node {
    short nums[21];
    node() { memset(nums, 0, sizeof nums); nums[0] = 1; }
    node(int a, int b) {
        memset(nums, 0, sizeof nums);
        nums[0] = b % MOD;
        nums[1] = a % MOD;
    }
    node operator*(const node &b) {
        node ans;
        ans.nums[0] = 0;
        for (int i = 0; i <= c; i++) {
            for (int j = 0; j <= c; j++) {
                int p = min(i + j, c);
                ans.nums[p] += (int) nums[i] * b.nums[j] % MOD;
                if (ans.nums[p] >= MOD) ans.nums[p] -= MOD;
            }
        }
        return ans;
    }
};

node st[4 * MAXN];

void build(int v, int l, int r) {
    if (l == r) {
        st[v] = node(a[l], b[r]);
    } else {
        int m = (l + r) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        st[v] = st[2 * v] * st[2 * v + 1];
    }
}

void upd(int v, int l, int r, int x, int a, int b) {
    if (l == r) {
        st[v] = node(a, b);
        ::a[x] = a;
        ::b[x] = b;
    } else {
        int m = (l + r) / 2;
        if (x <= m) {
            upd(2 * v, l, m, x, a, b);
        } else {
            upd(2 * v + 1, m + 1, r, x, a, b);
        }
        st[v] = st[2 * v] * st[2 * v + 1];
    }
}

node qry(int v, int l, int r, int x, int y) {
    if (x <= l && r <= y) {
        return st[v];
    } else if (r < x || l > y) {
        return node();
    } else {
        int m = (l + r) / 2;
        return qry(2 * v, l, m, x, y) * qry(2 * v + 1, m + 1, r, x, y);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> c;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = x % MOD;
    }
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        b[i] = x % MOD;
    }

    build(1, 0, n - 1);

    cin >> q;
    while (q--) {
        int p, a, b; cin >> p >> a >> b;
        p--;
        upd(1, 0, n - 1, p, a, b);
        cout << qry(1, 0, n - 1, 0, n - 1).nums[c] << '\n';
    }

    return 0;
}
