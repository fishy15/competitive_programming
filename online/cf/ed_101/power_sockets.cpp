/*
 * We note that if the tree with the answer has x chains, then we can use the x longest chains. This is 
 * because we only care about the depth of the kth white node, so any additional nodes do not affect the 
 * answer. In addition, it is best to place the each chain at the highest white node to minimize the 
 * distances of the new white nodes from the root. We can simulate adding each chain in order from 
 * biggest to smallest and calculate the location of the kth white node. Since only the depth matters, we
 * only need to store a segtree that specifies the count at each depth (which supports adding a chain and
 * searching for the kth node as well).
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
#define MAXN 200010

using namespace std;

int n, k;
int nums[MAXN];

struct lazy_segtree {
    ll st[8 * MAXN];
    ll lazy[8 * MAXN];
    void push(int v, int l, int r) {
        if (l != r) {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
        }
        st[v] += lazy[v] * (r - l + 1);
        lazy[v] = 0;
    }
    void upd(int x, int y, ll q, int v = 1, int l = 0, int r = 2 * MAXN - 1) {
        push(v, l, r);
        if (r < x || l > y) return;
        if (x <= l && r <= y) {
            lazy[v] += q;
            push(v, l, r);
        } else {
            int m = (l + r) / 2;
            upd(x, y, q, 2 * v, l, m);
            upd(x, y, q, 2 * v + 1, m + 1, r);
            st[v] = st[2 * v] + st[2 * v + 1];
        }
    }
    int qry(int x, int y, int v = 1, int l = 0, int r = 2 * MAXN - 1) {
        push(v, l, r);
        if (r < x || l > y) return 0;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return qry(x, y, 2 * v, l, m) + qry(x, y, 2 * v + 1, m + 1, r);
    }
    int search(int v = 1, int l = 0, int r = 2 * MAXN - 1, ll psum = 0) {
        push(v, l, r);
        if (psum + st[v] < k) {
            return INF;
        } else if (l == r) {
            return l;
        } else {
            int m = (l + r) / 2;
            int left = search(2 * v, l, m, psum);
            if (left == INF) {
                return search(2 * v + 1, m + 1, r, psum + st[2 * v]);
            } else {
                return left;
            }
        }
    }
};

lazy_segtree st;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    sort(nums, nums + n);

    st.upd(0, 0, 1);
    int cur = 0;
    int ans = INF;
    for (int i = n - 1; i >= 0; i--) {
        while (st.qry(cur, cur) == 0) cur++;
        st.upd(cur, cur, -1);
        st.upd(cur + 2, cur + 1 + (nums[i] / 2), 1);
        st.upd(cur + 2, cur + 1 + ((nums[i] - 1) / 2), 1);
        ans = min(ans, st.search());
    }

    if (ans == INF) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }

    return 0;
}
