/*
 * We can create a persistent segtree that for each index i, root[i] stores 1 at each index >= i that is the
 * first occurence of that value (similar to what we do for finding number of distinct values offline using
 * a BIT). If we are solving for a limit of k distinct values, we just need to binary search on this 
 * segtree to find the rightmost endpoint that has k distinct values. We can find each individual endpoint
 * since there are O(n / 1 + n / 2 + ... + n / n) = O(n log n) endpoints in the worst case, so the solution
 * is O(n log^2 n).
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

struct pst {
    struct node {
        int v;
        node *l, *r;
        node() : node(0) {}
        node(int v) : v(v), l(nullptr), r(nullptr) {}
        node(const node &n) {
            v = n.v;
            l = n.l;
            r = n.r;
        }
    };

    int n;
    vector<node*> root;
    deque<node> buffer;

    pst() {} // do nothing
    pst(int n) : n(n) {
        root.push_back(build(0, n));
    }

    node *build(int l, int r) {
        node *cur = new_node();
        if (l + 1 != r) {
            int m = (l + r) / 2;
            cur->l = build(l, m);
            cur->r = build(m, r);
        }
        return cur;
    }

    void copy(int pt, int t) {
        if ((int)(root.size()) <= t) {
            root.resize(t + 1);
        }
        root[t] = new_node(*root[pt]);
    }

    void upd(int pt, int t, int x, int v) {
        if ((int)(root.size()) <= t) {
            root.resize(t + 1);
        }
        root[t] = upd(root[pt], x, v, 0, n);
    }

    node *upd(node *p, int x, int v, int l, int r) {
        node *cur = new_node(*p);
        if (l + 1 == r) {
            cur->v = v;
        } else {
            int m = (l + r) / 2;
            if (x < m) {
                cur->l = upd(cur->l, x, v, l, m);
            } else {
                cur->r = upd(cur->r, x, v, m, r);
            }
            cur->v = cur->l->v + cur->r->v;
        }
        return cur;
    }

    int qry(int t, int x, int y) {
        return qry(root[t], x, y, 0, n);
    }

    int qry(node *p, int x, int y, int l, int r) {
        if (y <= l || x >= r) {
            return 0;
        } else if (x <= l && r <= y) {
            return p->v;
        } else {
            int m = (l + r) / 2;
            return qry(p->l, x, y, l, m) + qry(p->r, x, y, m, r);
        }
    }

    template<typename F>
    int max_right(int t, int l, F &&f) { 
        int acc = 0;
        return max_right(root[t], l, 0, n, acc, f);
    }

    template<typename F>
    int max_right(node *p, int l, int x, int y, int &acc, F &&f) {
        if (y <= l) {
            return y;
        } else if (x >= l) {
            if (f(acc + p->v)) {
                acc += p->v;
                return y;
            } else if (x + 1 == y) {
                return x;
            }
        }
        int m = (x + y) / 2;
        int res = max_right(p->l, l, x, m, acc, f);
        return res == m ? max_right(p->r, l, m, y, acc, f) : res;
    }

    template<typename... Args>
    node *new_node(Args... args) {
        buffer.emplace_back(args...);
        return &buffer.back();
    }
};

int n;
int nums[MAXN];
pst st;
map<int, int> pre;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    st = pst(n);
    st.copy(0, n);

    for (int i = n - 1; i >= 0; i--) {
        st.upd(i + 1, i, i, 1);
        if (pre[nums[i]] != 0) {
            st.upd(i, i, pre[nums[i]], 0);
        }
        pre[nums[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        int cur = 0;
        auto check = [i](int x) { return x <= i; };
        while (cur != n) {
            cur = st.max_right(cur, cur, check);
            cnt++;
        }
        cout << cnt << ' ';
    }
    cout << '\n';

    return 0;
}
