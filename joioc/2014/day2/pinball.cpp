/*
 * Each funnel moves the left and right end points closer together, so this means that the relative order 
 * of the elements is preserved. This means that the ball released at 1 and the ball released at n
 * both must reach the same point, and the rest of the locations will fit there as well. 
 * We can coordinate compress + use segtree to figure out the minimum cost for the ball released
 * at 1 and the ball released at n to reach that funnel, min(sum of those + cost of funnel) is answer.
 */

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
#define MAXN 100010

using namespace std;

int n, m;
array<int, 4> nums[MAXN];
map<int, int> x;
ll st[12 * MAXN][2];
ll ans = INFLL;

ll ckmin(ll &a, ll b) {
    return a = min(a, b);
}

void build(int v = 1, int l = 1, int r = 3 * m) {
    st[v][0] = INFLL;
    st[v][1] = INFLL;

    if (l != r) {
        int m = (l + r) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
    }
}

void upd(int x, ll y, int idx, int v = 1, int l = 1, int r = 3 * m) {
    if (l == r) {
        ckmin(st[v][idx], y);
    } else {
        int m = (l + r) / 2;
        if (x <= m) {
            upd(x, y, idx, 2 * v, l, m);
        } else {
            upd(x, y, idx, 2 * v + 1, m + 1, r);
        }
        st[v][idx] = min(st[2 * v][idx], st[2 * v + 1][idx]);
    }
}

ll qry(int x, int y, int idx, int v = 1, int l = 1, int r = 3 * m) {
    if (x <= l && r <= y) {
        return st[v][idx];
    } else if (r < x || l > y) {
        return INFLL;
    } else {
        int m = (l + r) / 2;
        return min(qry(x, y, idx, 2 * v, l, m), qry(x, y, idx, 2 * v + 1, m + 1, r));
    }
}

int main() {
    /* cin.tie(0)->sync_with_stdio(0); */

    cin >> m >> n;
    x[1] = 0;
    x[n] = 0;
    for (int i = 0; i < m; i++) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        x[a] = 0;
        x[b] = 0;
        x[c] = 0;
        nums[i] = {a, b, c, d};
    }

    int t = 0;
    for (auto &p : x) {
        p.second = ++t;
    }

    build();

    upd(x[1], 0, 0);
    upd(x[n], 0, 1);

    for (int i = 0; i < m; i++) {
        int a = x[nums[i][0]];
        int b = x[nums[i][1]];
        int c = x[nums[i][2]];
        int d = nums[i][3];

        ll min_1 = qry(a, b, 0);
        ll min_n = qry(a, b, 1);
        ckmin(ans, min_1 + min_n + d);
        upd(c, min_1 + d, 0);
        upd(c, min_n + d, 1);
    }

    if (ans == INFLL) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }

    return 0;
}
