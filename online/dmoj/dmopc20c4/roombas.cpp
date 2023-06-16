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

int n, m;
map<int, pair<vector<int>, vector<int>>> stuff; // list of x for each y
ll ans;

struct segtree {
    struct node {
        int l, r;
        ll v;
        node *c[2];
    };

    deque<node> dq;
    node *new_node(int l, int r) {
        dq.push_back({l, r, 0, {nullptr, nullptr}});
        return &dq.back();
    }

    segtree() {
        new_node(0, INF);
    }

    ll get_val(node *cur) {
        if (cur) {
            return cur->v;
        } else {
            return 0;
        }
    }

    void upd(node *cur, ll x, int v) {
        if (cur->l == cur->r) {
            cur->v += v;
        } else {
            int m = (cur->l + cur->r) / 2;
            if (x <= m) {
                if (!cur->c[0]) cur->c[0] = new_node(cur->l, m);
                upd(cur->c[0], x, v);
            } else {
                if (!cur->c[1]) cur->c[1] = new_node(m + 1, cur->r);
                upd(cur->c[1], x, v);
            }
            cur->v = get_val(cur->c[0]) + get_val(cur->c[1]);
        }
    }

    void upd(ll x, int v) {
        upd(&dq[0], x, v);
    }

    ll qry(node *cur, ll x, ll y) {
        if (!cur) return 0;
        if (cur->r < x || cur->l > y) return 0;
        if (x <= cur->l && cur->r <= y) return cur->v;
        return qry(cur->c[0], x, y) + qry(cur->c[1], x, y);
    }

    ll qry(ll x, ll y) {
        return qry(&dq[0], x, y);
    }
};

segtree st;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        stuff[y].first.push_back(x);
    }

    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        stuff[y].second.push_back(x);
        st.upd(x, 1);
    }

    for (auto &[_, p] : stuff) {
        auto &[roomba, cord] = p;
        for (auto x : roomba) {
            ans += st.qry(0, x);
        }

        for (auto x : cord) {
            st.upd(x, -1);
        }
    }

    cout << ans << '\n';

    return 0;
}
