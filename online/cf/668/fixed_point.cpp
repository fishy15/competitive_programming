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
#define MAXN 300010

using namespace std;

int n, q;
int nums[MAXN];
int torem[MAXN];
bool zero[MAXN];
vector<int> child[MAXN];
bool add[MAXN];


array<int, 3> qq[MAXN];
int ans[MAXN];

// lazy segtree
int st[4 * MAXN];
int lazy[4 * MAXN];
bool to_push[4 * MAXN];

void push(int v, int l, int r) {
    if (l != r && to_push[v]) {
        int a = lazy[v];
        st[2 * v] += a;
        st[2 * v + 1] += a;
        lazy[2 * v] += a;
        lazy[2 * v + 1] += a;
        to_push[2 * v] = true;
        to_push[2 * v + 1] = true;
    }
    lazy[v] = 0;
    to_push[v] = false;
}

void build(int v, int l, int r) {
    if (l == r) {
        st[v] = torem[l];
    } else {
        int m = (l + r) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        st[v] = min(st[2 * v], st[2 * v + 1]);
    }
}

void upd(int v, int l, int r, int x, int y, int a) {
    if (x <= l && r <= y) {
        st[v] += a;
        lazy[v] += a;
        to_push[v] = true;
    } else if (r >= x && l <= y) {
        int m = (l + r) / 2;
        push(v, l, r);
        upd(2 * v, l, m, x, y, a);
        upd(2 * v + 1, m + 1, r, x, y, a);
        st[v] = min(st[2 * v], st[2 * v + 1]);
    }
}

int qry(int v, int l, int r, int x, int y) {
    if (x <= l && r <= y) {
        return st[v];
    } else if (r < x || l > y) {
        return INF;
    } else {
        int m = (l + r) / 2;
        push(v, l, r);
        int v1 = qry(2 * v, l, m, x, y);
        int v2 = qry(2 * v + 1, m + 1, r, x, y);
        return min(v1, v2);
    }
}

int get(int v, int l, int r) {
    push(v, l, r);
    if (l == r) {
        return l;
    } else if (st[v] > 0) {
        return -1;
    } else {
        int m = (l + r) / 2;
        if (st[2 * v] <= 0) {
            return get(2 * v, l, m);
        } else {
            return get(2 * v + 1, m + 1, r);
        }
    }
}

void rem(int i) {
    upd(1, 0, n - 1, i, i, INF);
    upd(1, 0, n - 1, i + 1, n - 1, -1);
    child[i] = {i};
    int x;
    while ((x = get(1, 0, n - 1)) > i) {
        upd(1, 0, n - 1, x, x, INF);
        if (x < n - 1) {
            upd(1, 0, n - 1, x + 1, n - 1, -1);
        }
        child[i].push_back(x);
    }
}

struct bit {
    int n; 
    vector<int> b;
    bit(int n): n(n + 10) {
        b = vector<int>(n + 10);
    }
    void upd(int x, int v) {
        x++;
        while (x < n) {
            b[x] += v;
            x += x & -x;
        }
    }
    int qry(int x) {
        int res = 0;
        x++;
        while (x) {
            res += b[x];
            x -= x & -x;
        }
        return res;
    }
};

bit bb(MAXN);

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        torem[i] = i + 1 - nums[i];
        if (torem[i] < 0) {
            torem[i] = INF;
        } else if (torem[i] == 0) {
            torem[i] = INF;
            zero[i] = true;
        }
    }

    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        qq[i] = {a, b, i};
    }

    sort(qq, qq + q, greater<array<int, 3>>());
    build(1, 0, n - 1);

    for (int i = n - 1; i >= 0; i--) {
        if (zero[i]) {
            rem(i);
        }
    }

    int curpos = n - 1;
    for (int i = 0; i < q; i++) {
        auto [a, b, c] = qq[i];
        while (curpos >= a) {
            if (!child[curpos].empty()) {
                for (int j : child[curpos]) {
                    bb.upd(j + 1, 1);
                }
            }
            curpos--;
        }
        ans[c] = bb.qry(n - b) - bb.qry(a);
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
