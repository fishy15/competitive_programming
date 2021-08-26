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

struct segtree {
    int n;
    vector<pair<int, int>> st;
    vector<int> lazy;

    segtree(int n) : n(n), st(4 * n), lazy(4 * n) {
        build(1, 1, n);
    }

    void build(int v, int l, int r) {
        if (l + 1 == r) {
            st[v] = {0, l};
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m);
            build(2 * v + 1, m, r);
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }

    void push(int v, int l, int r) {
        if (l + 1 != r) {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
        }
        st[v].first += lazy[v];
        lazy[v] = 0;
    }

    void upd(int x, int y, int q) { upd(1, 1, n, x, y, q); }
    void upd(int v, int l, int r, int x, int y, int q) {
        push(v, l, r);
        if (r <= x || l >= y) return;
        if (x <= l && r <= y) {
            lazy[v] += q;
            push(v, l, r);
        } else {
            int m = (l + r) / 2;
            upd(2 * v, l, m, x, y, q);
            upd(2 * v + 1, m, r, x, y, q);
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }

    pair<int, int> qry() { return st[1]; }
};

int n;
array<int, 3> nums[MAXN];
segtree st(MAXN);

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i][0] >> nums[i][1] >> nums[i][2];
    }

    map<int, vector<array<int, 3>>> events;
    for (int i = 0; i < n; i++) {
        auto [l, v, r] = nums[i];
        events[v].push_back({l, v + 1, 1});
        events[r + 1].push_back({l, v + 1, -1});
    }

    array<int, 3> ans{};
    for (auto &[x, v] : events) {
        for (auto [l, r, c] : v) {
            st.upd(l, r, c);
        }
        
        auto cur = st.qry();
        if (cur.first > ans[0]) {
            ans[0] = cur.first;
            ans[1] = cur.second;
            ans[2] = x;
        }
    }

    cout << ans[0] << '\n';
    for (int i = 0; i < n; i++) {
        if (nums[i][0] <= ans[1] && ans[2] <= nums[i][2] && (ans[1] <= nums[i][1] && nums[i][1] <= ans[2])) {
            cout << i + 1 << ' ';
        }
    }
    cout << '\n';

    return 0;
}
