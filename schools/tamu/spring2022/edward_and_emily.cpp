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

struct DSU {
    vector<int> dsu;
    vector<int> sz;

    DSU(int n) {
        dsu.resize(n);
        sz.resize(n);
        iota(dsu.begin(), dsu.end(), 0);
        fill(sz.begin(), sz.end(), 1); 
    }

    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }

    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (sz[x] < sz[y]) swap(x, y);
            dsu[y] = x;
            sz[x] += sz[y];
        }
    }
};

ll n, m, k;
int x, y;
int p[MAXN];
array<int, 2> adj[MAXN];

int x_idx[MAXN];
int y_idx[MAXN];

ll egcd(ll a, ll b, ll& x, ll& y) {
    x = 1, y = 0;
    ll x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        ll q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> k;

    cin >> x >> y; 
    x--; y--;

    DSU dsu(n);

    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;

        dsu.join(i, p[i]);
    }

    memset(x_idx, -1, sizeof x_idx);
    memset(y_idx, -1, sizeof y_idx);

    int x_cur = x;
    int x_sz = dsu.sz[dsu.find(x)];
    for (int i = 0; i < x_sz; i++) {
        x_idx[x_cur] = i;
        x_cur = p[x_cur];
    }

    int y_cur = y;
    int y_sz = dsu.sz[dsu.find(y)];
    for (int i = 0; i < y_sz; i++) {
        y_idx[y_cur] = i;
        y_cur = p[y_cur];
    }

    set<pair<int, int>> done;

    ll ans = 0;
    while (k--) {
        int a, b; cin >> a >> b;
        a--; b--;

        if (a > b) swap(a, b);
        if (done.count({a, b})) {
            continue;
        }

        done.insert({a, b});

        for (int i = 0; i < 2; i++) {
            if (x_idx[a] != -1 && y_idx[b] != -1) {
                ll m1 = x_sz;
                ll m2 = y_sz;
                ll b1 = x_idx[a];
                ll b2 = y_idx[b];

                ll x1, y1;
                ll g = egcd(m1, m2, x1, y1);
                ll l = m1 * m2 / g;

                if ((b1 - b2) % g == 0) {
                    ll d = b2 - b1;
                    ll first_m = x1 * d / g * m1 + b1;
                    first_m = (first_m % l + l) % l;
                    ans += (m - first_m + l - 1) / l;
                }
            }

            swap(a, b);
        }
    }

    cout << ans << '\n';

    return 0;
}
