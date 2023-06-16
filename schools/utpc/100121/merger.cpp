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
#define MAXN 500010

using namespace std;

int n;
int a[MAXN];
int b[MAXN];

struct segtree {
    int st[4 * MAXN];
    void upd(int x, int y, int v = 1, int l = 0, int r = n - 1) {
        if (l == r) {
            st[v] = y;
        } else {
            int m = (l + r) / 2;
            if (x <= m) {
                upd(x, y, 2 * v, l, m);
            } else {
                upd(x, y, 2 * v + 1, m + 1, r);
            }
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }
    int qry(int x, int y, int v = 1, int l = 0, int r = n - 1) {
        if (r < x || l > y) return 0;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return max(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m + 1, r));
    }
};


int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        b[x] = i;
    }

    for (int i = 0; i < n; i++) {
        a[i] = b[a[i]];
    }

    segtree st;

    for (int i = 0; i < n; i++) {
        int m = st.qry(0, a[i]);
        st.upd(a[i], m + 1);
    }

    cout << st.qry(0, n - 1) << '\n';

    return 0;
}
