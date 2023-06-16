/*
 * Similar idea to max subarray sum w/ updates (https://cses.fi/problemset/task/1190). In a segtree 
 * representing the entire array, store the answer for the interval as well as 2 vectors for the prefix and
 * the suffix. The vectors hold {bitmask, length}, where the bitmask marks which numbers are present. At
 * each level, we can then combine the prefix and suffix arrays as well as calculating the best suffix from
 * the left and the prefix from the right that covers all the numbers.
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

int n, k, m;

struct node {
    vector<pair<ll, int>> pre, suf;
    int ans;
};

int nums[MAXN];
node st[4 * MAXN];

node comb(const node &l, const node &r, int len1, int len2) {
    node res;
    res.pre = l.pre;
    for (auto p : r.pre) {
        pair<ll, int> p2 = {p.first | l.pre.back().first, len1 + p.second};
        if (p2.first != res.pre.back().first) res.pre.push_back(p2);
    }

    res.suf = r.suf;
    for (auto p : l.suf) {
        pair<ll, int> p2 = {p.first | r.suf.back().first, len2 + p.second};
        if (p2.first != res.suf.back().first) res.suf.push_back(p2);
    }

    int cur_p = 0;
    res.ans = min(l.ans, r.ans);
    int lsz = l.suf.size();
    int rsz = r.pre.size();
    for (int i = lsz - 1; i >= 0; i--) {
        while (cur_p < rsz && (l.suf[i].first | r.pre[cur_p].first) != ((1LL << k) - 1)) cur_p++;
        if (cur_p == rsz) return res;
        res.ans = min(res.ans, l.suf[i].second + r.pre[cur_p].second);
    }

    return res;
}

void build(int v = 1, int l = 0, int r = n - 1) {
    if (l == r) {
        if (k == 1) st[v].ans = 1;
        else st[v].ans = INF;
        st[v].pre = {{1LL << nums[l], 1}};
        st[v].suf = {{1LL << nums[l], 1}};
    } else {
        int m = (l + r) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        st[v] = comb(st[2 * v], st[2 * v + 1], m - l + 1, r - m);
    }
}

void upd(int x, int y, int v = 1, int l = 0, int r = n - 1) {
    if (l == r) {
        nums[x] = y;
        st[v].pre = {{1LL << y, 1}};
        st[v].suf = {{1LL << y, 1}};
    } else {
        int m = (l + r) / 2;
        if (x <= m) {
            upd(x, y, 2 * v, l, m);
        } else {
            upd(x, y, 2 * v + 1, m + 1, r);
        }
        st[v] = comb(st[2 * v], st[2 * v + 1], m - l + 1, r - m);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k >> m;

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        nums[i]--;
    }

    build();

    for (int i = 0; i < m; i++) {
        int t; cin >> t;
        if (t == 1) {
            int p, v; cin >> p >> v;
            p--; v--;
            upd(p, v);
        } else {
            int x = st[1].ans;
            if (x == INF) {
                cout << -1 << '\n';
            } else {
                cout << x << '\n';
            }
        }
    }

    return 0;
}
