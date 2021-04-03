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

int n;
array<int, 2> ppl[MAXN];

struct segtree {
    int n;
    vector<ll> st;

    segtree(int n) : n(n) {
        st.resize(4 * n, INFLL);
    }

    void upd(int x, ll y) { upd(x, y, 1, 0, n - 1); }
    void upd(int x, ll y, int v, int l, int r) {
        if(l == r) {
            st[v] = y;
        } else {
            int m = (l + r) / 2;
            if (x <= m) {
                upd(x, y, 2 * v, l, m);
            } else {
                upd(x, y, 2 * v + 1, m + 1, r);
            }
            st[v] = min(st[2 * v], st[2 * v + 1]);
        }
    }

    ll qry(int x, int y) { return qry(x, y, 1, 0, n - 1); }
    ll qry(int x, int y, int v, int l, int r) {
        if (r < x || l > y) {
            return INFLL;
        } else if (x <= l && r <= y) {
            return st[v];
        } else {
            int m = (l + r) / 2;
            return min(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m + 1, r));
        }
    }
};

int get_up(int i) {
    int l = 0;
    int r = i - 1;
    int ans = -1;

    while (l <= r) {
        int m = (l + r) / 2;
        if (ppl[m][0] > ppl[i][0] + ppl[i][1]) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> ppl[i][0] >> ppl[i][1];
    }

    sort(ppl, ppl + n, [](const array<int, 2> &a, const array<int, 2> &b) {
        return a[0] > b[0];
    });

    segtree same(n), shift(n);
    same.upd(0, 0);
    shift.upd(0, ppl[0][0]);

    for (int i = 1; i < n; i++) {
        int x = get_up(i);
        ll ans = INFLL;
        if (x != -1) {
            ans = min(ans, shift.qry(0, x) - ppl[i][0]);
        }

        if (x + 1 < i) {
            ans = min(ans, same.qry(x + 1, i - 1) + ppl[i][1]);
        }
        
        ans -= ppl[i][1]; // so we can add all back later
        same.upd(i, ans);
        shift.upd(i, ans + ppl[i][0]);
    }

    ll ans = same.qry(n - 1, n - 1);
    for (int i = 0; i < n; i++) {
        ans += ppl[i][1];
    }

    cout << ans << '\n';

    return 0;
}
