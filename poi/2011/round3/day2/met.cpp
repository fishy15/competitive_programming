/*
 * We can add one final range that adds an infinite amount to each location, and this means that there must
 * be some value that works for each member state. At the beginning, we know that each member state will be
 * satisfied somewhere in [1, k + 1]. We can then check if each member state will be satisfied at the 
 * midpoint or not, which subdivides this range into 2 parts. Repeating this process on the new ranges, we 
 * will eventually narrow each member state into an interval of size 1. To process a set of ranges, we can
 * sweep from left to right in overall O(n log n) time. There are log n sweeps that we will have to do, so
 * the overall time complexity is O(n log^2 n).
 *
 * Note: This technique is referred to as parallel binary search. Instead of binary searching for each
 * set indepedently, we can process them all at the same time by marking marking the region each query
 * belongs to.
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
#define MAXN 300010

using namespace std;

int n, m, k;
vector<int> own[MAXN];
ll need[MAXN];
array<ll, 3> range[MAXN];
int ans[MAXN];

struct level {
    int l;
    int r;
    vector<int> pts;
};

vector<level> cur;

struct BIT {
    ll bit[MAXN];
    void reset() { memset(bit, 0, sizeof bit); }
    void upd(int x, ll v) {
        x++;
        while (x < MAXN) {
            bit[x] += v;
            x += x & -x;
        }
    }
    void upd(int l, int r, ll v) {
        if (l <= r) {
            upd(l, v);
            upd(r + 1, -v);
        } else {
            upd(0, r, v);
            upd(l, m, v);
        }
    }
    ll qry(int x) {
        x++;
        ll res = 0;
        while (x) {
            res += bit[x];
            x -= x & -x;
        }
        return res;
    }
} bit;

bool solve() {
    vector<level> nxt;
    bit.reset();
    
    bool not_done = false;
    for (const auto &[l, r, pts] : cur) {
        if (l == r) {
            nxt.push_back({l, r, pts});
            bit.upd(range[l][0], range[l][1], range[l][2]);
        } else {
            int m = (l + r) / 2;
            for (int i = l; i <= m; i++) {
                bit.upd(range[i][0], range[i][1], range[i][2]);
            }

            level l1 = {l, m};
            level l2 = {m + 1, r};
            for (auto &x : pts) {
                ll cnt = 0;
                for (int q : own[x]) {
                    cnt += min<ll>(bit.qry(q), INFLL);
                    cnt = min<ll>(cnt, INFLL);
                }
                if (cnt >= need[x]) {
                    l1.pts.push_back(x);
                } else {
                    l2.pts.push_back(x);
                }
            }

            nxt.push_back(l1);
            nxt.push_back(l2);
            for (int i = m + 1; i <= r; i++) {
                bit.upd(range[i][0], range[i][1], range[i][2]);
            }

            not_done = true;
        }
    }

    cur.swap(nxt);
    return not_done;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int o; cin >> o;
        own[o - 1].push_back(i);
    }

    for (int i = 0; i < n; i++) {
        cin >> need[i];
    }

    cin >> k;
    for (int i = 0; i < k; i++) {
        int a, b, c; cin >> a >> b >> c;
        range[i] = {a - 1, b - 1, c};
    }
    range[k] = {0, m - 1, INF};

    cur.push_back({0, k});
    for (int i = 0; i < n; i++) {
        cur.back().pts.push_back(i);
    }

    while (solve()) {}

    for (int i = 0; i <= k; i++) {
        for (int x : cur[i].pts) {
            ans[x] = i;
        }
    }

    for (int i = 0; i < n; i++) {
        if (ans[i] == k) {
            cout << "NIE\n";
        } else {
            cout << ans[i] + 1 << '\n';
        }
    }

    return 0;
}
