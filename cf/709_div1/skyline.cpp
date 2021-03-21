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
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 300010

using namespace std;

int n;
int h[MAXN];
ll b[MAXN];
int pmin[MAXN];

struct st {
    ll st[4 * MAXN];
    void upd(int x, ll y, int v = 1, int l = 0, int r = n - 1) {
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
    ll qry(int x, int y, int v = 1, int l = 0, int r = n - 1) {
        if (r < x || l > y) {
            return -INFLL;
        } else if (x <= l && r <= y) {
            return st[v];
        } else {
            int m = (l + r) / 2;
            return max(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m + 1, r));
        }
    }
} st;

void calc_pmin() {
    vector<int> h_idx(n);
    iota(h_idx.begin(), h_idx.end(), 0);
    sort(h_idx.begin(), h_idx.end(), [](int x, int y) { return h[x] < h[y]; });
    set<int> idx = {-1};

    for (int i : h_idx) {
        auto it = idx.lower_bound(i);
        pmin[i] = *prev(it);
        idx.insert(i);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    calc_pmin();

    for (int i = 0; i < n; i++) {
        ll best = -INFLL;
        if (pmin[i] == -1) {
            best = b[i];
        } else {
            best = st.qry(pmin[i], pmin[i]);
        }

        int lo = max(pmin[i], 0);
        int hi = i - 1;
        
        if (lo <= hi) {
            best = max(best, st.qry(lo, hi) + b[i]);
        }

        st.upd(i, best);
    }

    cout << st.qry(n - 1, n - 1) << '\n';

    return 0;
}
