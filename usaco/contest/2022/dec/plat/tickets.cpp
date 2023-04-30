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
#include <set>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct segtree {
    int n;
    vector<set<int>> st;

    segtree(int n) : n(n), st(4 * n) {}

    void add(int x, int y, int idx) { add(1, 0, n, x, y, idx); }
    void add(int v, int l, int r, int x, int y, int idx) { 
        if (y <= l || r <= x) {
            return;
        } else if (x <= l && r <= y) {
            st[v].insert(idx);
        } else {
            int m = (l + r) / 2;
            add(2 * v, l, m, x, y, idx);
            add(2 * v + 1, m, r, x, y, idx);
        }
    }

    void rem(int x, int y, int idx) { rem(1, 0, n, x, y, idx); }
    void rem(int v, int l, int r, int x, int y, int idx) { 
        if (y <= l || r <= x) {
            return;
        } else if (x <= l && r <= y) {
            st[v].erase(idx);
        } else {
            int m = (l + r) / 2;
            rem(2 * v, l, m, x, y, idx);
            rem(2 * v + 1, m, r, x, y, idx);
        }
    }

    void get(int x, vector<int> &s) { get(1, 0, n, x, s); }
    void get(int v, int l, int r, int x, vector<int> &s) {
        if (l + 1 == r) {
            for (int x : st[v]) s.push_back(x);
        } else {
            int m = (l + r) / 2;
            if (x < m) {
                get(2 * v, l, m, x, s);
            } else {
                get(2 * v + 1, m, r, x, s);
            }

            for (int y : st[v]) {
                s.push_back(y);
            }
        }
    }
};

// min segtree
struct min_segtree {
    int n;
    vector<ll> st;

    min_segtree(int n, const vector<ll> &nums) : n(n), st(4 * n) {
        build(1, 0, n, nums);
    }

    void build(int v, int l, int r, const vector<ll> &nums) {
        if (l + 1 == r) {
            st[v] = nums[l];
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, nums);
            build(2 * v + 1, m, r, nums);
            st[v] = min(st[2 * v], st[2 * v + 1]);
        }
    }

    ll qry(int x, int y) { return qry(1, 0, n, x, y); }
    ll qry(int v, int l, int r, int x, int y) {
        if (y <= l || r <= x) {
            return INFLL;
        } else if (x <= l && r <= y) {
            return st[v];
        } else {
            int m = (l + r) / 2;
            return min(qry(2 * v, l, m, x, y), qry(2 * v + 1, m, r, x, y));
        }
    }
};

int n, k;
array<ll, 4> edge[MAXN];

void solve(vector<ll> &dist) {
    segtree st(n);
    for (int i = 0; i < k; i++) {
        st.add(edge[i][2], edge[i][3], i);
    }

    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    for (int i = 0; i < n; i++) {
        pq.push({dist[i], i});
    }

    vector<bool> vis(n);
    int cnt = 0;
    while (cnt < n) {
        auto [d, v] = pq.top();
        pq.pop();

        if (vis[v]) continue;
        vis[v] = true;
        cnt++;

        vector<int> ed_idx;
        st.get(v, ed_idx);
        for (int i : ed_idx) st.rem(edge[i][2], edge[i][3], i);

        for (int i : ed_idx) {
            ll nd = d + edge[i][1];
            int nxt = edge[i][0];

            if (nd < dist[nxt]) {
                dist[nxt] = nd;
                pq.push({nd, nxt});
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        cin >> edge[i][0] >> edge[i][1] >> edge[i][2] >> edge[i][3];
        edge[i][0]--;
        edge[i][2]--;
    }

    vector<ll> min_one(n, INFLL);
    min_one[0] = 0;
    solve(min_one);

    vector<ll> min_n(n, INFLL);
    min_n[n - 1] = 0;
    solve(min_n);

    vector<ll> min_both(n);
    for (int i = 0; i < n; i++) {
        min_both[i] = min<ll>(INFLL, min_one[i] + min_n[i]);
    }

    min_segtree st1(n, min_one);
    min_segtree st2(n, min_n);

    for (int i = 0; i < k; i++) {
        ll a = st1.qry(edge[i][2], edge[i][3]);
        ll b = st2.qry(edge[i][2], edge[i][3]);
        min_both[edge[i][0]] = min(min_both[edge[i][0]], a + b + edge[i][1]);
    }

    solve(min_both);

    for (int i = 0; i < n; i++) {
        if (min_both[i] == INFLL) {
            cout << "-1\n";
        } else {
            cout << min_both[i] << '\n';
        }
    }

    return 0;
}
