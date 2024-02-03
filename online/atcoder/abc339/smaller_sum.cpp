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
#define MAXN 1000000

using namespace std;

struct pst {
    struct node {
        ll v;
        int l, r;
        node *c[2];
    };

    deque<node> all;

    void upd(node *p, int x, ll v) {
        if (p->l == p->r) {
            p->v = v;
        } else {
            int m = (p->l + p->r) / 2;
            if (x <= m) {
                p->c[0] = new_node(p->c[0]);
                upd(p->c[0], x, v);
            } else {
                p->c[1] = new_node(p->c[1]);
                upd(p->c[1], x, v);
            }
            p->v = p->c[0]->v + p->c[1]->v;
        }
    }

    ll qry(node *p, int x, int y) {
        if (x <= p->l && p->r <= y) return p->v;
        if (x > p->r || y < p->l) return 0;
        return qry(p->c[0], x, y) + qry(p->c[1], x, y);
    }

    node *new_node(int l, int r) {
        node n;
        n.l = l;
        n.r = r;
        n.v = 0;
        if (l != r) {
            int m = (l + r) / 2;
            n.c[0] = new_node(l, m);
            n.c[1] = new_node(m + 1, r);
        } else {
            n.c[0] = nullptr;
            n.c[1] = nullptr;
        }
        all.push_back(n);
        return &all.back();
    }

    node *new_node(const node *n2) {
        all.push_back(*n2);
        return &all.back();
    }

    map<int, node*> st; 
    node* cur;

    pst(int l, int r) {
        st[-100] = cur = new_node(l, r);
    }

    void upd(int t, int x, ll v) {
        if (st[t] != cur) {
            cur = new_node(cur);
            st[t] = cur;
        }
        upd(cur, x, v);
    }

    ll qry(int t, int x, int y) {
        auto it = prev(st.upper_bound(t));
        return qry(it->second, x, y);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n;
    cin >> n;

    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }

    pst st(0, n - 1);
    sort(a.begin(), a.end());
    for (auto [x, i] : a) {
        st.upd(x, i, x);
    }

    int q;
    cin >> q;

    ll prev_ans = 0;
    while (q--) {
        ll a, b, g;
        cin >> a >> b >> g;

        int l = a ^ prev_ans;
        int r = b ^ prev_ans;
        int x = g ^ prev_ans;
        l--;
        r--;

        auto ans = st.qry(x, l, r);
        cout << ans << '\n';
        prev_ans = ans;
    }

    return 0;
}
