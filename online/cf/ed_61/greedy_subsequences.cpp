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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

struct lazy_segtree {
    int n;
    mutable vector<int> st;
    mutable vector<int> lazy;
    lazy_segtree(int n) : n(n), st(4 * n), lazy(4 * n) {}
    lazy_segtree(vector<int> &nums) : lazy_segtree(sz(nums)) { build(1, 0, n - 1, nums); }
    void build(int v, int l, int r, const vector<int> &nums) {
        if (l == r) {
            st[v] = nums[l];
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, nums);
            build(2 * v + 1, m + 1, r, nums);
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }
    void push(int v, int l, int r) const {
        if (l != r) {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
        }
        st[v] += lazy[v];
        lazy[v] = 0;
    }
    void upd(int x, int y, int q) { upd(x, y, q, 1, 0, n - 1); }
    void upd(int x, int y, int q, int v, int l, int r) {
        push(v, l, r);
        if (r < x || l > y) return;
        if (x <= l && r <= y) {
            lazy[v] += q;
            push(v, l, r);
        } else {
            int m = (l + r) / 2;
            upd(x, y, q, 2 * v, l, m);
            upd(x, y, q, 2 * v + 1, m + 1, r);
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }
    int qry(int x, int y) const { return qry(x, y, 1, 0, n - 1); }
    int qry(int x, int y, int v, int l, int r) const {
        push(v, l, r);
        if (r < x || l > y) return 0;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return max(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m + 1, r));
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    vector<int> nxt_bigger(n, n);
    vector<int> cur;
    for (int i = n-1; i >= 0; i--) {
        while (!cur.empty() && nums[cur.back()] <= nums[i]) {
            cur.pop_back();
        }
        if (!cur.empty()) {
            nxt_bigger[i] = cur.back();
        }
        cur.push_back(i);
    }

    cur.clear();
    vector<int> prev_geq(n, -1);
    rep(i, 0, n) {
        while (!cur.empty() && nums[cur.back()] < nums[i]) {
            cur.pop_back();
        }
        if (!cur.empty()) {
            prev_geq[i] = cur.back();
            if (nums[cur.back()] == nums[i]) {
                cur.pop_back();
            }
        }
        cur.push_back(i);
    }

    vector<int> full_value(n+1, 0);
    for (int i = n-1; i >= 0; i--) {
        full_value[i] = full_value[nxt_bigger[i]] + 1;
    }

    lazy_segtree st(full_value);
    vector<int> ans(n - k + 1);
    for (int i = n - k; i >= 0; i--) {
        ans[i] = st.qry(i, i + k - 1);

        // remove last element
        auto last = i + k - 1;
        st.upd(prev_geq[last] + 1, last, -1);
    }

    for (auto x : ans) {
        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}
