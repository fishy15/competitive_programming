/*
 * We can process each garland independently. For each garland, we can mark which are the relevant queries
 * (all of the queries + the relevant switches). Then for each garland, we can use a 2D BIT to add the
 * values, perform all the queries, and then reset the BIT.
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
#include <cassert>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 2010

using namespace std;

struct BIT {
    int n, m;
    vector<vector<ll>> bit;

    BIT(int n, int m) : n(n), m(m) {
        bit = vector<vector<ll>>(n, vector<ll>(m));
    }

    void upd(int x, int y, ll v) {
        x++;
        while (x <= n) {
            int y2 = y + 1;
            while (y2 <= m) {
                bit[x - 1][y2 - 1] += v;
                y2 += y2 & -y2;
            }
            x += x & -x;
        }
    }

    ll qry(int x, int y) {
        ll res = 0;
        while (x > 0) {
            int y2 = y;
            while (y2 > 0) {
                res += bit[x - 1][y2 - 1];
                y2 -= y2 & -y2;
            }
            x -= x & -x;
        }
        return res;
    }

    ll qry(int x1, int x2, int y1, int y2) {
        return qry(x2, y2) - qry(x2, y1) - qry(x1, y2) + qry(x1, y1);
    }
};

struct garland {
    bool on;
    BIT bit;
    garland(int n, int m) : on(true), bit(n, m) {}
};

struct query {
    bool is_switch;
    int a, b, c, d;
    int pos;
    query() : is_switch(true) {}
    query(int a, int b, int c, int d, int p) : is_switch(false), a(a), b(b), c(c), d(d), pos(p) {}
};

int n, m, k, q;
vector<vector<array<int, 3>>> garlands;
vector<vector<query>> queries;
ll ans[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        int len; cin >> len;

        garlands.emplace_back();
        for (int j = 0; j < len; j++) {
            int x, y, w; cin >> x >> y >> w;
            x--; y--;
            garlands.back().push_back({x, y, w});
        }
    }

    queries.resize(k);

    cin >> q;
    int cnt_ans = 0;
    for (int i = 0; i < q; i++) {
        string qry; cin >> qry;
        if (qry == "SWITCH") {
            int x; cin >> x;
            x--;
            queries[x].emplace_back();
        } else {
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            x1--; y1--;
            for (int j = 0; j < k; j++) {
                queries[j].emplace_back(x1, y1, x2, y2, cnt_ans);
            }
            cnt_ans++;
        }
    }

    garland g(n, m);
    for (int i = 0; i < k; i++) {
        for (auto [x, y, w] : garlands[i]) {
            g.bit.upd(x, y, w);
        }

        for (auto &qry : queries[i]) {
            if (qry.is_switch) {
                g.on = !g.on;
            } else {
                if (g.on) {
                    ans[qry.pos] += g.bit.qry(qry.a, qry.c, qry.b, qry.d);
                }
            }
        }

        // reset
        g.on = true;
        for (auto [x, y, w] : garlands[i]) {
            g.bit.upd(x, y, -w);
        }
    }

    for (int i = 0; i < cnt_ans; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
