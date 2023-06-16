#include <iostream>
#include <algorithm>
#include <array>

#define ll long long
#define MAXN 200010

using namespace std;

int n;
int nums[MAXN];
ll ans;
array<int, 2> pre[MAXN];

struct node {
    int valid;
    ll ans;
    ll lazy;

    node() : node(1, 0) {}
    node(int v, ll a) : valid(v), ans(a), lazy(0) {}

    node operator+(const node &n2) {
        return node(valid + n2.valid, ans + n2.ans);
    }
};

struct segtree {
    node st[4 * MAXN];

    void push(int v, int l, int r) {
        if (l != r) {
            st[2 * v].lazy += st[v].lazy;
            st[2 * v + 1].lazy += st[v].lazy;
        }
        st[v].ans += st[v].valid * st[v].lazy;
        st[v].lazy = 0;
    }

    void upd_sum(int x, int y, ll z, int v = 1, int l = 0, int r = n - 1) {
        push(v, l, r);
        if (x > r || y < l) {
            return;
        } else if (x <= l && r <= y) {
            st[v].lazy += z;
            push(v, l, r);
        } else {
            int m = (l + r) / 2;
            upd_sum(x, y, z, 2 * v, l, m);
            upd_sum(x, y, z, 2 * v + 1, m + 1, r);
            st[v] = st[2 * v] + st[2 * v + 1];
        }
    }

    void invalidate(int x, int v = 1, int l = 0, int r = n - 1) {
        push(v, l, r);
        if (l == r) {
            st[v] = node(0, 0);
        } else {
            int m = (l + r) / 2;
            if (x <= m) {
                invalidate(x, 2 * v, l, m);
            } else {
                invalidate(x, 2 * v + 1, m + 1, r);
            }

            // pushing just in case
            push(2 * v, l, m);
            push(2 * v + 1, m + 1, r);
            st[v] = st[2 * v] + st[2 * v + 1];
        }
    }

    node qry(int x, int y, int v = 1, int l = 0, int r = n - 1) {
        push(v, l, r);
        if (x > r || y < l) {
            return node(0, 0);
        } else if (x <= l && r <= y) {
            return st[v];
        } else {
            int m = (l + r) / 2;
            return qry(x, y, 2 * v, l, m) + qry(x, y, 2 * v + 1, m + 1, r);
        }
    }
} st;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    fill(pre, pre + n + 1, array<int, 2>{-1, -1});    

    for (int i = 0; i < n; i++) {
        int c = nums[i];
        if (pre[c][1] != -1) {
            st.upd_sum(pre[c][0] + 1, pre[c][1], -1);
            st.invalidate(pre[c][1]);
        }

        if (i >= 2) {
            node res = st.qry(pre[c][1] + 1, i - 1);
            ans += res.ans - res.valid;
        }

        pre[c][0] = pre[c][1];
        pre[c][1] = i;
        st.upd_sum(pre[c][0] + 1, pre[c][1], 1);
    }

    cout << ans << '\n';

    return 0;
}
